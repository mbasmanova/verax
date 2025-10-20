# Copyright (c) Meta Platforms, Inc. and its affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
find_path(
  READLINE_INCLUDE_DIR
  readline/readline.h
  HINTS ${READLINE_ROOT_DIR}
  PATH_SUFFIXES include
  REQUIRED
)
find_library(READLINE_LIBRARY readline HINTS ${READLINE_ROOT_DIR} PATH_SUFFIXES lib REQUIRED)
find_library(NCURSES_LIBRARY ncurses REQUIRED) # readline depends on libncurses

mark_as_advanced(READLINE_INCLUDE_DIR READLINE_LIBRARY NCURSES_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  Readline
  DEFAULT_MSG
  READLINE_LIBRARY
  NCURSES_LIBRARY
  READLINE_INCLUDE_DIR
)

set(READLINE_INCLUDE_DIRS ${READLINE_INCLUDE_DIR})
set(READLINE_LIBRARIES ${READLINE_LIBRARY} ${NCURSES_LIBRARY})
