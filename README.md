# Terminal shortcuts
Fast and easily changeable shortcuts to run Linux shell commands

## Features
- Set and manage shortcuts to run Linux shell commands  
- Speed in running, setting, and removing shortcuts  
- Advantages over alias:
  - Set and remove shortcuts quickly (no need to edit .bashrc)
  - No name collisions
- Save and use instantly in all terminal sessions


## Quickstart
1. Clone repository
2. Enter the folder "install" and run `sudo ./install-sc`.
3. Open a new terminal and type `s -h`. You should get some usage output.
4. Run `s -a hw echo hello world`. This sets the shortcut with token hw.
5. Run `s hw`. You should see hello world being echoed.
6. Run `s`. The program wil print a list of valid commands (there should be only one so far).
7. Run `s -rm hw` to remove the command to print hello world.

## Examples
- Pipes
  1. `s -a ll "ls | less"`
  2. `s ll` executes `ls` and then pipes the output to `less`
- Command arguments
  1. `s -a lg "ls | grep"`
  2. `s lg -i desktop` searches for files matching the pattern "desktop" ignoring case
- Use history
  1. `echo hello`
  2. `s -a e -p` sets shortcut "e" to the previous command
  3. `s e` should echo hello
- Save directory
  1. Go into any directory
  2. `s -a d1 cd $(pwd)` will create a shortcut that will enter the current directory
  3. Go into a different directory
  4. `s d1` will bring you back to the original directory
- Functions
  1. `s -a a2f 'f(){ cat $1>>$2;}; f'` creates a function that will append the content of one file to another
  2. `echo hello > b.txt`
  3. `echo world > a.txt`
  4. `s a2f a.txt b.txt`
  5. `cat b.txt` should now output hello world

## Usage
- `s`
  - List all possible commands
- `s -h`
  - Show usage
- `s <name> [<args>]`
  - Run command with specified name
  - Any arguments are passed to the command
- `s -a <token> [-p] [<command>]`
  - Add new command with name token
  - New token name can be comprised of any alphanumeric sequence (excluding `-h`, `-a`, `-rm-`, spaces, and other bash reserved characters)
  - Use -p to get the previously-run command
  - Without -p, the rest of the line is treated as the command
- `s -rm <name>`
  - Remove command with specified name
