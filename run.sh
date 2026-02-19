#!/bin/bash
cd `dirname $0`
echo RUN ......................
./hp35simulator
echo RC=$?
echo WAIT .....................
read X
