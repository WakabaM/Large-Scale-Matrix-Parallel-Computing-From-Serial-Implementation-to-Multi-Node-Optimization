#!/bin/bash
#DSUB -n my_hybrid_job
#DSUB -N 2
#DSUB -A root.gppx9pzp
#DSUB -R 'cpu=8;mem=16384'
#DSUB -o hybrid_%J.log

source /home/HPCBase/tools/module-5.2.0/init/profile.sh
module purge
module use /home/HPCBase/modulefiles/
module load mpi/openmpi/4.1.2_gcc9.3.0

export OMP_NUM_THREADS=8
mpirun -np 2 $HOME/mpi_new/matrix_hybrid