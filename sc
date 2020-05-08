#!/bin/bash

# INFO: bashrc: PROMPT_COMMAND='history -a'
# https://www.shellhacks.com/tune-command-line-history-bash/

# cat ~/.bash_history

OUTPUT="$(./schelper $@)"
#OUTPUT="ls | less"

#eval x=\`${OUTPUT}\`
#echo $x
#`${OUTPUT}`
eval $OUTPUT
