Verax is an experimental frontend for the Velox ecosystem.

## License

Verax is licensed under the Apache 2.0 License. A copy of the license
[can be found here.](LICENSE)

To build, run make debug or make release in root of checkout.



To build:

Check out git@github.com:facebookexperimental/verax.git.

Checkout branch init-dev if main is empty.

Run make debug or make release in the verax checkout directory. This fetches the velox submodule and builds verax. To build faster, you can just build the velox\_plan\_test and velox\_sql targets.

To generate a toy dataset:

Velox\_plan\_\_test --data\_path /home/user/plan\_test

This makes a TPC H qualification dataset in the specified path. It optimizes a few queries and prints out the resulting plans.

To run SQL against the data just generated:

Velox\_sql --data\_path /home/user/plan\_test

SQL\> select \* from nation;

Will print out the 25 rows from the nation table.




