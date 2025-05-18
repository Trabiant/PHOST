#include "NormalConverter.h"
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <cmath>

__global__ void CamToObjectKernel(
    const uchar3* inNormal, uchar3* outNormal,
    int width, int height, Mat3x3 rotM)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x >= width || y >= height) return;
    int idx = y * width + x;

    double nx = inNormal[idx].z / 127.5 - 1.0;
    double ny = inNormal[idx].y / 127.5 - 1.0;
    double nz = inNormal[idx].x / 127.5 - 1.0;

    double ox = rotM.m[0] * nx + rotM.m[1] * ny + rotM.m[2] * nz;
    double oy = rotM.m[3] * nx + rotM.m[4] * ny + rotM.m[5] * nz;
    double oz = rotM.m[6] * nx + rotM.m[7] * ny + rotM.m[8] * nz;

    double len = sqrt(ox * ox + oy * oy + oz * oz);
    if (len > 1e-6) { ox /= len; oy /= len; oz /= len; }
    else { ox = 0; oy = 0; oz = 1; }

    uchar3 out;
    float vx = (oz * 0.5f + 0.5f) * 255.0f;
    float vy = (-oy * 0.5f + 0.5f) * 255.0f;
    float vz = (ox * 0.5f + 0.5f) * 255.0f;
    out.x = static_cast<unsigned char>(fminf(fmaxf(vx, 0.0f), 255.0f));
    out.y = static_cast<unsigned char>(fminf(fmaxf(vy, 0.0f), 255.0f));
    out.z = static_cast<unsigned char>(fminf(fmaxf(vz, 0.0f), 255.0f));
    outNormal[idx] = out;
}

void NormalConverter::convertGPU(
    const cv::Mat& src, cv::Mat& dst) const
{
    int width = src.cols, height = src.rows;
    dst.create(height, width, src.type());

    size_t buf = width * height * sizeof(uchar3);
    uchar3* d_in = nullptr, * d_out = nullptr;
    cudaMalloc(&d_in, buf);
    cudaMalloc(&d_out, buf);
    cudaMemcpy(d_in, src.data, buf, cudaMemcpyHostToDevice);

    dim3 block(16, 16), grid((width + 15) / 16, (height + 15) / 16);
    CamToObjectKernel <<<grid, block >>> (d_in, d_out, width, height, rotPOD_);
    cudaDeviceSynchronize();

    cudaMemcpy(dst.data, d_out, buf, cudaMemcpyDeviceToHost);
    cudaFree(d_in); cudaFree(d_out);
}
