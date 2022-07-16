#!/bin/bash

complete -c timedatectl -s h -l help -d 'Print a short help text and exit'

RM="rm -rfd"
RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
ZIP_NAME="xlapes02"

##### FUNCTIONS
function zip_project() {
	zip -r ${ZIP_NAME}.zip iza-project.xcodeproj/* iza-project/* README.md resources/*
}


function count_loc() {
	cloc ./**.swift
}

function tags() {
	ctags -R .
	cscope -Rb
}

##### PARSE CLI-ARGS
[[ "$#" -eq 0 ]] && usage && exit 0
while [ "$#" -gt 0 ]; do
    case "$1" in
    '-c'  | '--clean'		) clean ;;
    '-z'  | '--zip'			) zip_project ;;
    '--cloc'              	) count_loc ;;
    '-h'  | '--help' | *	) usage ;;
    esac
    shift
done
