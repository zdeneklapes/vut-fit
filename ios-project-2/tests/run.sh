#! /bin/sh

POKUS=0
CALL="./proj2 999 1 0 10"

if [ "$(uname)" = "Linux" ]; then
    echo "LINUX"
    eval "make clean-all-linux"
    eval "make clean"
    eval "make"
else
    echo "MACOS"
    eval "make clean-all"
    eval "make clean"
    eval "make"
fi

while true; do
    POKUS=$((POKUS+1))
    echo "-------------------------------------------------------------------------------"
    echo "POKUS: ${POKUS}"
    echo "-------------------------------------------------------------------------------"

    echo "${CALL}"
    eval "${CALL}"
done

exit 0