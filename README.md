# Terminal shortcuts
Fast and easily changeable shortcuts to run Linux shell commands

## Quckstart
*WARNING: Works fine, but still may contain some bugs; be careful*
1. Clone repository
2. Enter the folder "install" and run `sudo ./install-sc`.
3. Open a new terminal and type `s`. You should get some usage output.
4. Run `s -a hw echo hello world`. This sets the shortcut with token hw.
5. Run `s hw`. You should see hello world being echoed.
6. Run `s -l`. The program wil print a list of valid commands (there should be only one so far).
7. Run `s -r hw` to remove the command to print hello world.

## Usage
- s &lt;token>
  - Run command with name token
- s -a &lt;token> \[-p\] \[&lt;command>]
  - Add new command with name token
  - Use -p to get the previously-run command
  - Without -p, the rest of the line is treated as the command
- s -r &lt;token>
  - Remove command with name token
- s -l
  - List all possible commands
