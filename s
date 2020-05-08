#!/bin/bash
history 2 > /tmp/term-hist
OUTPUT="$(/usr/share/term-shortcuts/schelper $@)"
eval $OUTPUT
