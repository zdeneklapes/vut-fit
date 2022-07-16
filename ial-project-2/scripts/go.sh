#!/bin/sh
set -x

cd ../..


if [[ $PWD/ == /Users/zdeneklapes/Desktop/ ]]; then
	cp -R ial_2021_du2 xlapes02
fi

cd xlapes02

if [[ $PWD/ == /Users/zdeneklapes/Desktop/xlapes02/ ]]; then
	find . -type f -not \( -name 'go.sh' -or -name 'btree.c' -or -name 'hashtable.c' \) -delete
	find . -type d -not \( -name 'go.sh' -or -name 'btree.c' -or -name 'hashtable.c' \) -delete
fi

cd ..

if [[ $PWD/ == /Users/zdeneklapes/Desktop/ ]]; then
	tar cvf xlapes02.tar --exclude=xlapes02/scripts --exclude=xlapes02/btree/btree.c xlapes02
	rm -rfd xlapes02
fi



