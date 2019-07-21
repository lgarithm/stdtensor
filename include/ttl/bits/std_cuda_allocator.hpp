#pragma once
#include <stdexcept>

#ifndef USE_FAKE_CUDA_RUNTIME
#include <cuda_runtime.h>
#endif

namespace ttl
{
namespace internal
{

struct cuda_copier {
    static constexpr auto h2d = cudaMemcpyHostToDevice;
    static constexpr auto d2h = cudaMemcpyDeviceToHost;

    template <cudaMemcpyKind dir>
    static void copy(void *dst, const void *src, size_t size)
    {
        const cudaError_t err = cudaMemcpy(dst, src, size, dir);
        if (err != cudaSuccess) {
            throw std::runtime_error("cudaMemcpy failed");
        }
    }
};

template <typename R> struct cuda_mem_allocator {
    R *operator()(int count)
    {
        void *deviceMem;
        // cudaMalloc<R>(&deviceMem, count);
        // https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__MEMORY.html#group__CUDART__MEMORY
        const cudaError_t err = cudaMalloc(&deviceMem, count * sizeof(R));
        if (err != cudaSuccess) {
            throw std::runtime_error("cudaMalloc failed");
        }
        return reinterpret_cast<R *>(deviceMem);
    }
};

struct cuda_mem_deleter {
    void operator()(void *ptr)
    {
        const cudaError_t err = cudaFree(ptr);
        if (err != cudaSuccess) { throw std::runtime_error("cudaFree failed"); }
    }
};

}  // namespace internal
}  // namespace ttl
