#include<iostream>
#include<mpi.h>
using namespace std;
int main(int argc char** argv)
{
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    cout<<"helloworld from process "<<rank<<" of "<<size<<endl;
    return 0;
}