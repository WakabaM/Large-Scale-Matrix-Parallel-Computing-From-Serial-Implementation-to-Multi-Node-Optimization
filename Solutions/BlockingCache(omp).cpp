#include<iostream>
#include<iomanip>
#include<chrono>
#include<vector>
const int BLOCK=16;//这里按照要求 换成16，32，64，128，256
const int N=512;
using namespace std;
int main()
{
    vector<double>A(N*N);
    vector<double>B(N*N);
    vector<double>C(N*N,0);
    
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i*N+j]=((i*17+j*13)%1000)/1000.0;
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            B[i*N+j]=((i*11+j*19)%1000)/1000.0;
        }
    }
    auto start=chrono::high_resolution_clock::now();
    #pragma omp parallel for//OMP
     for (int ii = 0; ii < N; ii += BLOCK) {
        for (int kk = 0; kk < N; kk += BLOCK) {
            for (int jj = 0; jj < N; jj += BLOCK) {
                // 
                for (int i = ii; i < ii + BLOCK; i++) {
                    for (int k = kk; k < kk + BLOCK; k++) {
                        double temp = A[i * N + k]; // 
                        for (int j = jj; j < jj + BLOCK; j++) {
                            C[i * N + j] += temp * B[k * N + j];
                        }
                    }
                }
            }
        }
    }
    auto end=chrono::high_resolution_clock::now();
    long double checksum=0.0;
    for(int i=0;i<N*N;i++)
    {
        checksum+=C[i];
    }
    chrono::duration<double>elapsed=end-start;
    cout<<"N = "<<N<<endl;
    cout<<"checksum = "<<fixed<<setprecision(6)<<(double)checksum<<endl;
    cout<<"Time = "<<setprecision(2)<<elapsed.count()<<"s"<<endl;
}
    
