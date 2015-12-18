// From PTT

// (單一區塊, 多執行緒)

#include <cuda.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////////////////////////////////////
// 向量加法的運算核心 (GPU)
// 函式前加 __global__ 即為核心
// 核心只傳回 void
////////////////////////////////////////

__global__ void gpu_add(float* c, float* a, float* b, int n){
    for (int k=threadIdx.x; k<n; k+=blockDim.x) {
        c[k] = a[k]+b[k];
    }
}

////////////////////////////////////////
// 向量加法的一般函式 (Host)
////////////////////////////////////////

void host_add(float* c, float* a, float* b, int n){
    for (int k=0; k<n; k++) {
        c[k] = a[k]+b[k];
    }
}


////////////////////////////////////////
// 計算誤差用的函式
////////////////////////////////////////

double diff(float* a, float* b, int n){
    double s=0, r=0;
    for (int k=0; k<n; k++) {
        double w=a[k]-b[k];
        s += w*w;
        r += a[k]*a[k];
    }
    return sqrt(s/r); //相對誤差
}

////////////////////////////////////////
// 時間函數 (傳回單位:千分之一秒)
////////////////////////////////////////

double ms_time(){
    return (double)clock()/CLOCKS_PER_SEC*1000.0;
}

////////////////////////////////////////
// 主程式
////////////////////////////////////////

int main(){
    // 設定向量大小
    int n = 1024*1024;
    int size = n*sizeof(float);

    // 網格與區塊設定
    int grid  = 1;      // gridDim  (每個網格具有的區塊數)
    int block = 512;    // blockDim (每個區塊具有的執行緒數)

    // 設定呼叫次數 (測量平均效能)
    int loop=100;

    // 配置主機記憶體
    float *a,*b,*c,*d;
    a = (float*)malloc(size);
    b = (float*)malloc(size);
    c = (float*)malloc(size);
    d = (float*)malloc(size);

    // 設定亂數的輸入向量
    srand(time(0));

    for (int k=0; k<n; k++) {
        a[k] = (float)rand()/RAND_MAX*2-1;
        b[k] = (float)rand()/RAND_MAX*2-1;
    }

    // 配置顯示卡記憶體
    float  *ga,*gb,*gc;
    cudaMalloc((void**)&ga, size);
    cudaMalloc((void**)&gb, size);
    cudaMalloc((void**)&gc, size);

    // 載入向量 a,b 到顯示卡記憶體中
    cudaMemcpy(ga, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(gb, b, size, cudaMemcpyHostToDevice);

    ////////////////////////////////////////
    // part 1 : 測量精確度
    ////////////////////////////////////////

    // 呼叫核心來運算 (GPU)
    gpu_add<<<grid, block>>>(gc, ga, gb, n);

    // 呼叫一般函數來運算 (Host)
    host_add(d, a, b, n);

    // 把計算結果存回主機
    cudaMemcpy(c, gc, size, cudaMemcpyDeviceToHost);

    // 比較兩者差異
    printf("vector add N(%d) elements, diff = %g\n", n, diff(c,d,n));



    ////////////////////////////////////////
    // part 2 : 測量效能
    ////////////////////////////////////////

    // 測量 GPU 核心效能
    double gpu_dt = ms_time();
    for (int w=0; w<loop; w++) {
        gpu_add<<<grid, block>>>(gc, ga, gb, n);
        cudaThreadSynchronize();    //避免核心執行不完全
    }
    gpu_dt = (ms_time()-gpu_dt)/loop;   //平均時間


    // 測量 Host 函數效能
    double host_dt = ms_time();
    for (int w=0; w<loop; w++) {
        host_add(d, a, b, n);
    }
    host_dt = (ms_time()-host_dt)/loop; //平均時間


    // 輸出平均執行時間
    printf("host time: %g ms\n", host_dt);
    printf("gpu  time: %g ms\n", gpu_dt);


    // 釋放主機記憶體
    free(a);
    free(b);
    free(c);
    free(d);

    // 釋放顯示卡記憶體
    cudaFree(ga);
    cudaFree(gb);
    cudaFree(gc);

    return 0;
}


// vector add N(1048576) elements, diff = 0
// host time: 3.41618 ms
// gpu  time: 1.32161 ms
