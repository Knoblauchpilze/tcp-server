#!/bin/sh

CURR_DIR=$(dirname $0)

export LD_LIBRARY_PATH="${CURR_DIR}/lib:${LD_LIBRARY_PATH}"

# https://stackoverflow.com/questions/9057387/process-all-arguments-except-the-first-one-in-a-bash-script
APP_NAME=$1
shift

./bin/${APP_NAME} "$@"
