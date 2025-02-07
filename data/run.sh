#!/bin/sh
APP_NAME=$1

CURR_DIR=$(dirname $0)

export LD_LIBRARY_PATH="${CURR_DIR}/lib:${LD_LIBRARY_PATH}"

./bin/${APP_NAME}
