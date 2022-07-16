#!/bin/bash

complete -c timedatectl -s h -l help -d 'Print a short help text and exit'

RM="rm -rfd"
RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
PROJECT_NAME="diagram-editor"
ZIP_NAME="xbinov00-xlapes02"

##### FUNCTIONS
function usage() {
    echo "USAGE:"
    echo "
    '-b' | '--build') build ;;
    '-r' | '--run') run ;;
    '-c' | '--clean') clean ;;
    '-z' | '--zip') zip_project ;;
    '-sz' | '--ssh-zdenek') ssh 'xlapes02';;
    '-sa' | '--ssh-andrej') ssh 'xbinov00';;
    '-h' | '--help' | *) usage ;;
	"
}

function error_exit() {
    printf "${RED}ERROR: $1${NC}\n"
    usage
    exit 1
}

function build() {
    if [ ! -d "build/" ]; then mkdir build; fi
    cd build || error_exit "cd command"
    eval "cmake .."
    eval "make -j"
    cd .. || error_exit "cd command"
}

function run() {
    if [[ $(uname -s) == "Darwin" ]]; then
        eval "./build/${PROJECT_NAME}.app/Contents/MacOS/${PROJECT_NAME}"
    elif [[ $(uname -s) == "Linux" ]]; then
        eval "./build/${PROJECT_NAME}"
    else
        error_exit "RUN: can't be performed"
    fi
}

function clean() {
    ${RM} build
    ${RM} build-icp_prj1-vut-fit-Desktop_Qt_5_9_9_clang_64bit-Debug
    ${RM} cmake-build-debug
    ${RM} .cache
    ${RM} .qmake.stash
    ${RM} CMakeLists.txt.user
#    ${RM} *.pro
    ${RM} *.app
    ${RM} *.o
    ${RM} *.zip
    ${RM} *.out
    ${RM} *.idea
    ${RM} tags
    ${RM} moc_predefs.h
    ${RM} moc_side_toolbox.cpp
    ${RM} moc_window.cpp
    ${RM} diagram_editor
}

function zip_project() {
    make pack
}

function ssh() {
	scp "$(pwd)/${ZIP_NAME}.zip" $1@eva.fit.vutbr.cz:/homes/eva/xl/$1
}

function count_loc() {
	cloc src/**/*.{cpp,hpp,h}
}

function tags() {
	ctags -R .
	cscope -Rb
}

##### PARSE CLI-ARGS
[[ "$#" -eq 0 ]] && usage && exit 0
while [ "$#" -gt 0 ]; do
    case "$1" in
    '-b'  | '--build'		) build ;;
    '-r'  | '--run'			) run ;;
    '-c'  | '--clean'		) clean ;;
    '-z'  | '--zip'			) zip_project ;;
    '-sz' | '--ssh-zdenek'	) ssh "xlapes02" ;;
    '-sa' | '--ssh-andrej'	) ssh "xbinov00";;
    '--cloc'              	) count_loc ;;
    '--tags'              	) tags ;;
    '-h'  | '--help' | *	) usage ;;
    esac
    shift
done
