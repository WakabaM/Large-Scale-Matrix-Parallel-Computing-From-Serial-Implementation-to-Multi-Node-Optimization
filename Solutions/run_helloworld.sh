#!/bin/bash
#DSUB -n my_hello_job
#DSUB -N 2
#DSUB -A root.gppx9pzp
#DSUB -R 'cpu=4;mem=4096'
#DSUB -o hello_%J.log

source /home/HPCBase/tools/module-5.2.0/init/profile.sh
module purge
module use /home/HPCBase/modulefiles/
module load mpi/openmpi/4.1.2_gcc9.3.0

mpirun -np 8 $HOME/mpi_new/hello