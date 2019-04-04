#!/bin/bash

echo "Para N = 10"
$PBS_O_WORKDIR/sumavectores 10
echo "Para N = 10000000"
$PBS_O_WORKDIR/sumavectores 10000000
