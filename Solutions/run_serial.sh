#!/bin/bash
#DSUB -n my_serial_job
#DSUB -N 1
#DSUB -A root.gppx9pzp
#DSUB -R 'cpu=1;mem=8192'
#DSUB -o serial_%J.log

./cd_hpc