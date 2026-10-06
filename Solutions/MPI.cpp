#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <mpi.h>
using namespace std;
const int N = 4096;
int main(int argc,char** argv) {
    MPI_Init(&argc,&argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rpp=N/size; 
    vector<double>Alocal(rpp*N);
    vector<double>B(N*N);
    vector<double>Clocal(rpp*N,0.0); // ⭐ 修正：必须是 rpp * N
    vector<double>A(N*N);
    vector<double>C(N*N,0.0);
    if (rank==0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i * N + j] = ((i * 17 + j * 13) % 1000) / 1000.0;
                B[i * N + j] = ((i * 11 + j * 19) % 1000) / 1000.0;
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD); 
    auto start = chrono::high_resolution_clock::now();

    MPI_Bcast(B.data(), N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Scatter(A.data(), rpp * N, MPI_DOUBLE,
                Alocal.data(), rpp * N, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    #pragma omp parallel for
    for (int i = 0; i < rpp; i++) {
        for (int k = 0; k < N; k++) {
            double temp = Alocal[i * N + k];
            for (int j = 0; j < N; j++) {
                Clocal[i * N + j] += temp * B[k * N + j];
            }
        }
    }
    MPI_Gather(Clocal.data(), rpp * N, MPI_DOUBLE,
               C.data(), rpp * N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD); 
    auto end = chrono::high_resolution_clock::now();
    if (rank == 0) {
        long double checksum = 0.0;
        for (int i = 0; i < N * N; i++) {
            checksum += C[i];
        }
        chrono::duration<double> elapsed = end - start;
        cout << "N = " << N << endl;
        cout << "checksum = " << fixed << setprecision(6) << (double)checksum << endl;
        cout << "Time = " << setprecision(2) << elapsed.count() << "s" << endl;
    }

    MPI_Finalize();
    return 0;
}