#!/bin/bash

#set -x # debug

complete -c timedatectl -s h -l help -d 'Print a short help text and exit'

RM="rm -rfd"
RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
ZIP_NAME='xlapes02'
ERROR_LOG='../debug/error.log'

##### FUNCTIONS
function error_exit() {
    printf "${RED}ERROR: $1${NC}\n"
    usage
    exit 1
}

function clean() {
    find . -type f -iname "*.zip" | xargs ${RM}
    find . -type d -iname "venv" | xargs ${RM}
    find . -type d -iname ".idea" | xargs ${RM}
    find . -type d -iname "__pycache__" | xargs ${RM}
    find . -type f -iname ".DS_Store" | xargs ${RM}
    find . -type d -iname ".git" -mindepth 2  | xargs ${RM}
    find . -type f -iname ".gitignore" -mindepth 2 | xargs ${RM}
}

function ssh() {
    zip_project
    scp "$(pwd)/${ZIP_NAME}.zip" $1@eva.fit.vutbr.cz:/homes/eva/xl/$1
}

function line_of_codes() {
    if [[ "$(uname -s)" == "Darwin" ]]; then
        (brew list | grep "cloc") && cloc src/** # cloc src/**/*.{py,yaml}
    elif [[ "$(uname -s)" == "Linux" ]]; then
        echo "$(uname -s)"
    else
        echo "$(uname -s)"
    fi
}

function tags() {
    ctags -R .
    cscope -Rb
}

function usage() {
    echo "USAGE:
    '-r' | '--run') run ;;
    '-c' | '--clean') clean ;;
    '-z' | '--zip') zip_project ;;
    '-sz' | '--ssh-zdenek') ssh 'xlapes02' ;;
    '--cloc') line_of_codes ;;
    '--tags') tags ;;
    '-h' | '--help' | *) usage ;;"
}

##### PARSE CLI-ARGS
[[ "$#" -eq 0 ]] && usage && exit 0
while [ "$#" -gt 0 ]; do
    case "$1" in
    '-c' | '--clean') clean ;;
    '-z' | '--zip') zip_project ;;
    '-sz' | '--ssh-zdenek') ssh 'xlapes02' ;;
    '--cloc') line_of_codes ;;
    '--tags') tags ;;
    '-h' | '--help' | *) usage ;;
    esac
    shift
done
