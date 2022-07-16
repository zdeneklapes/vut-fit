#!/bin/sh
# set -x

test()
{
	echo "NORMAL"
	cd ../"$1"/ || exit 0
	make clean
	make
	make run

	echo "ADVANCED"
	make advanced
	cd ../scripts || exit 0
}

for i in "$@"; do
	case "$i" in 
		1) test "c202";;
		2) test "c204";;
		3) test "c206";;
	esac
done

exit 0
