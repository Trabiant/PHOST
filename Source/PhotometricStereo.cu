#include "PhotometricStereo.h"
#include "device_launch_parameters.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

__global__ void ComputeNormalKernel(
	const float* __restrict__ d_img_data,
	const uchar* __restrict__ d_mask,
	const float* __restrict__ d_Lpinv,
	uchar* d_out,
	int M, int h, int w)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;
	if (x >= w || y >= h) return;
	int idx = y * w + x;
	if (d_mask[idx] > 127) return;

	float g0 = 0, g1 = 0, g2 = 0;
#pragma unroll
	for (int i = 0; i < M; ++i) {
		float v = d_img_data[size_t(i) * h * w + idx];
		g0 += d_Lpinv[0 * M + i] * v;
		g1 += d_Lpinv[1 * M + i] * v;
		g2 += d_Lpinv[2 * M + i] * v;
	}

	float nrm = sqrtf(g0 * g0 + g1 * g1 + g2 * g2);
	float nx = 0, ny = 0, nz = 1;
	if (nrm > 1e-6f) { nx = g0 / nrm; ny = g1 / nrm; nz = g2 / nrm; }

	int o = idx * 3;
	d_out[o + 0] = uchar((nz + 1) * 0.5f * 255);
	d_out[o + 1] = uchar((ny + 1) * 0.5f * 255);
	d_out[o + 2] = uchar((nx + 1) * 0.5f * 255);
}



void PhotometricStereo::ComputeNormal_GPU() {
	int M = images_.size(), h = images_[0].rows, w = images_[0].cols;
	size_t npix = size_t(h) * w;

	cv::Mat l_pinv;
	cv::invert(lightDirs_, l_pinv, cv::DECOMP_SVD);
	std::vector<float> h_Lpinv(3 * M);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < M; ++j)
			h_Lpinv[i * M + j] = l_pinv.at<float>(i, j);

	std::vector<float> h_img_data(M * npix);
	for (int i = 0; i < M; ++i) {
		const float* ptr = images_[i].ptr<float>(0);
		std::copy(ptr, ptr + npix, h_img_data.begin() + i * npix);
	}

	float* d_img_data = nullptr, * d_Lpinv = nullptr;
	uchar* d_mask = nullptr, * d_out = nullptr;
	cudaMalloc(&d_img_data, M * npix * sizeof(float));
	cudaMalloc(&d_Lpinv, 3 * M * sizeof(float));
	cudaMalloc(&d_mask, npix * sizeof(uchar));
	cudaMalloc(&d_out, 3 * npix * sizeof(uchar));

	cudaMemcpy(d_img_data, h_img_data.data(), M * npix * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_Lpinv, h_Lpinv.data(), 3 * M * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_mask, mask_.ptr<uchar>(0), npix * sizeof(uchar), cudaMemcpyHostToDevice);

	dim3 block(16, 16), grid((w + 15) / 16, (h + 15) / 16);
	size_t shmem = M * sizeof(float);
    ComputeNormalKernel << <grid, block, shmem >> > (d_img_data, d_mask, d_Lpinv, d_out, M, h, w);
	cudaDeviceSynchronize();

	normalMap_.create(h, w, CV_8UC3);
	cudaMemcpy(normalMap_.ptr<uchar>(0), d_out, 3 * npix * sizeof(uchar), cudaMemcpyDeviceToHost);

	cudaFree(d_img_data);
	cudaFree(d_Lpinv);
	cudaFree(d_mask);
	cudaFree(d_out);

}
