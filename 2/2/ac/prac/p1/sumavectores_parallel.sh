#!/bin/bash

echo "Para N = 8"
$PBS_O_WORKDIR/sumavectores_parallel 8
echo "Para N = 11"
$PBS_O_WORKDIR/sumavectores_parallel 11
