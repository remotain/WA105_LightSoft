#!/bin/bash

export WLS_PATH=$(cd -P $(dirname "${BASH_SOURCE[0]}") > /dev/null && pwd -P)
export WLS_DATA=${WLS_PATH}/examples/