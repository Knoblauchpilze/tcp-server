#!/bin/sh

APP_NAME=$1

if [ "$#" -ge 2 ]; then
  PORT=$2
  export PORT=$PORT
fi

./bin/${APP_NAME}
