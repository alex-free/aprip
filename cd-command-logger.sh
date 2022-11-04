#!/bin/bash

echo -e "DuckStation CD Command Logger v1.0 For Linux\nBy Alex Free\n"

if [ $# -ne 2]; then
	echo -e "Error: Incorrect number of arguments.\nUsage:\n<duckstation .exe file> <game cue file>\n"
	exit 1
fi

if [ ! -f "$1" ]; then
	echo -e "Error: Can't open the DuckStation executable file: "$1"\n"
else
	echo "Got DuckStation executable file: "$1""
fi

if [ ! -f "$2" ]; then
	echo -e "Error: Can't open the PSX game cue file: "$2"\n"
	exit 1
else
	echo "Got PSX game cue file: "$1""
fi

log="$HOME/.local/share/duckstation/duckstation.log"
rm $log
"$1" "$2"

grep -r "CDROM executing command" $log
echo
echo "Number Of CD Commands Sent:"
grep -rc "CDROM executing command" $log