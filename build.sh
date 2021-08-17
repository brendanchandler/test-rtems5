#!/bin/bash

set -e
set -x

source /local/bchandler/src/rsb/rtems/rtems-shell.env
cd ~/src/test-rtems5/
./waf configure --rtems=/local/bchandler/rtems/5 --rtems-bsp=powerpc/qoriq_e500
./waf build -v

