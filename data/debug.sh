#!/bin/sh

CURR_DIR=$(dirname $0)

export LD_LIBRARY_PATH="${CURR_DIR}/lib:${LD_LIBRARY_PATH}"

APP_NAME=$1
shift

gdb --args ./bin/${APP_NAME} "$@"
