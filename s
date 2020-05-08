#!/bin/bash
OUTPUT="$(./schelper $@)"
eval $OUTPUT

#eval x=\`${OUTPUT}\`
#echo $x
#`${OUTPUT}`
