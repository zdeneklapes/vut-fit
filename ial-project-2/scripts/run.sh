#!/bin/bash 

test()
{
	echo "NORMAL"
	cd ../"$1"/ || exit 0
	make valgrind_all
	cd ../scripts || exit 0
}

for i in "$@"; do
	case "$i" in 
		1) test "btree";;
		2) test "hashtable";;
	esac
done

