# Terminal shortcuts
Fast and easily changeable shortcuts to run Linux shell commands

## Quckstart
*WARNING: Still extremely buggy, be careful and don't use with any sudo or rm commands*
1. Clone repository
2. In the directory, run `./s`. You should get some usage output.
3. Run `./s -a 1 "echo hello world"`. This sets the shortcut named 1 to echo hello world.
4. Run `./s 1`. You should see "hello world" in the terminal. This runs the command set.
5. Run `./s -l`. You should see the list of possible commands (only one so far).
6. Run `./s -r 1`. This will remove the shortcut 1.

Setting to the previous command is also possible, however it requires environment variables and is more complicated.
