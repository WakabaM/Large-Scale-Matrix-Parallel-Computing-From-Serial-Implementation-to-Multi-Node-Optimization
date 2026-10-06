#!/bin/bash
#DSUB -n my_omp_job
#DSUB -N 1
#DSUB -A root.gppx9pzp
#DSUB -R 'cpu=8;mem=8192'
#DSUB -o omp_%J.log

export OMP_NUM_THREADS=8
./cd_hpc_omp