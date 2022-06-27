#!/usr/bin/env bash

# build the project

cortos build "$@" --ramstart 0x40000000 | tee -a buildrun.res;


