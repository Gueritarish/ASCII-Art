#!/bin/sh

if [ $# -lt 1 ]; then
	echo "Missing arguments, please give a gif"
	exit 1
fi


convert $1 frame_%03d.jpg
echo "\033[?25l"
for file in frame_[0-9][0-9]*.jpg; do
	echo "\033[H"
	build/src/ascii $file $2 $3
	sleep 0.06
done
echo "\033[?25h"
rm frame_[0-9][0-9]*.jpg
