#include "testing.hpp"

#ifdef USE_FAKE_CUDA_RUNTIME
#include "fake_cuda_runtime.h"
#endif

#include <ttl/cuda_tensor>
#include <ttl/tensor>

using ttl::cuda_tensor;
using ttl::tensor;

TEST(cuda_tensor_test, test1)
{
    using R = float;
    cuda_tensor<R, 2> m1(10, 100);
}

TEST(cuda_tensor_test, test2)
{
    using R = float;
    cuda_tensor<R, 2> m1(10, 100);
    tensor<R, 2> m2(10, 100);

    m1.fromHost(m2.data());
    m1.toHost(m2.data());
}
