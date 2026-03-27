# CI Workflows

## Overview

| Workflow | Runner |
|----------|--------|
| `linux.yml` | 32-core Ubuntu (CentOS 9 container) |
| `macos.yml` | macOS 15 (arm64, 3 CPUs) |

Both workflows trigger on pushes to main and PRs that modify `axiom/`,
`velox`, `CMakeLists.txt`, or `Makefile`. Both build debug and release
configurations and run all Axiom tests.

## ccache

Both workflows use [ccache](https://ccache.dev/) to cache compilation results
across CI runs. The cache is stored using the
`apache/infrastructure-actions/stash` action.

Cache keys:
- Linux: `ccache-ubuntu-{build_type}-default-gcc`
- macOS: `ccache-macos-{build_type}`

The stash action automatically scopes keys by git ref. Caches from the
base branch (`main`) are available as fallback for new PRs, so the first
run on a new PR typically gets a warm cache.

- **Cache size limit**: 5 GB for debug, 1 GB for release.
- **Cold cache build**: ~50 min.
- **Warm cache build**: ~1-2 min.

Stale entries (not used in the current build) are evicted before saving
via `ccache --evict-older-than 1d` to keep the cache lean and reduce
upload/download times.

Known issue: cache restore is slow for debug (~2-4 min). The cache is
large (~2.5 GB, ~9K files). Wrapping in a tar before uploading does
not help — the stash action internally archives files.

Typical warm-cache run times (may vary):

| | release | debug |
|---|---|---|
| Deps install | ~1 min | ~1 min |
| Cache restore | ~1 min | ~2-4 min |
| Build | ~1 min | ~2 min |
| Tests | ~2 min | ~3 min |
| **Total** | **~5 min** | **~8-10 min** |

Linux uses a container with pre-installed deps, so the deps install
step is skipped.

## Linux (`linux.yml`)

Uses the pre-built `ghcr.io/facebookincubator/velox-dev:centos9` container
with all dependencies pre-installed. Dependencies are resolved as `SYSTEM`.

## macOS (`macos.yml`)

### Dependencies

Installs minimal dependencies from the Velox setup scripts:

- **Homebrew packages** (`install_velox_deps_from_brew`): gtest, icu4c,
  libevent, libsodium, lz4, openssl, protobuf, simdjson, snappy, xz,
  xxhash, zstd, bison, flex, ninja, cmake.
- **Built from source** (`install_gflags`, `install_glog`,
  `install_double_conversion`): installed to `/tmp/deps-install`.

Everything else (folly, boost, re2, arrow, xsimd, fmt, stemmer, geos, duckdb)
is bundled automatically via CMake FetchContent during the configure step.

### Build configuration

```
cmake \
    -DVELOX_MONO_LIBRARY=ON \
    -DVELOX_BUILD_SHARED=ON \
    -DVELOX_BUILD_TESTING=OFF \
    -DVELOX_ENABLE_PARQUET=ON \
    -DAXIOM_BUILD_TESTING=ON
```

- `VELOX_MONO_LIBRARY=ON` + `VELOX_BUILD_SHARED=ON`: builds Velox as a single
  shared library (`libvelox.dylib`). This avoids gflags/folly static/dynamic
  linking conflicts that occur when a static mono library is combined with
  shared system libraries.
- `VELOX_BUILD_TESTING=OFF`: skips building Velox test targets not needed
  by Axiom.
- `fmt_SOURCE=BUNDLED` (set as env var): Homebrew's fmt version is not
  compatible.

### ICU discovery

Homebrew installs ICU as a versioned keg (`icu4c@78`) that is not linked into
`/opt/homebrew/lib`. The cmake configure step adds the ICU prefix to
`CMAKE_PREFIX_PATH` via `$(brew --prefix icu4c)` so bundled re2 can find it.

### Known issues

Flaky `SqlTest.set_*` tests in debug builds
([#1170](https://github.com/facebookincubator/axiom/issues/1170)).
These are excluded from macOS debug CI via `GTEST_FILTER=-SqlTest.set_*`.
They still run in release and on Linux.

## Troubleshooting Slow Builds

### Was the ccache used?

Check the **Restore Ccache** step in the GitHub Actions log:

- **Cache hit**: The step takes 30s+ (downloading the cache).
- **Cache miss**: The step completes in < 1 second with
  `Stash not found for key: ...`.

### Where did the cache come from?

The stash action appends a ref suffix to the key (e.g.,
`ccache-macos-debug-1168_merge` for PR #1168). It searches in this order:

1. Exact key match from the current PR's previous runs.
2. Fallback to the base branch (`main`) cache.

If you see `Stash not found`, neither was available — expect a cold build
(~50 min).

### How large was the cache?

Check the **CCache Statistics After Build** step. It logs:

- `Cache dir size:` — the on-disk size before and after eviction.
- `Hits:` / `Misses:` — how many compilations used the cache vs compiled
  from scratch. A warm build should show >95% hits.

You can also check artifact sizes in the **Summary** tab of the workflow
run.

### Build is slow despite cache hit

Possible causes:

- **Velox submodule updated** — A large Velox version bump invalidates
  most cache entries. The build will be slow once, then fast again.
- **ccache eviction** — If the cache limit was exceeded, old entries were
  dropped. Check `Misses` count in the ccache stats.
- **New bundled dependencies** — Adding or upgrading a FetchContent
  dependency rebuilds it from scratch on the first run.
