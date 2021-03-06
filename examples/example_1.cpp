#include <ttl/tensor>

using ttl::tensor;
using ttl::tensor_ref;
using ttl::tensor_view;

void example_1()
{
    const int h = 3;
    const int w = 4;
    const int c = 5;
    const int n = h * w * c;

    tensor<int, 3> t(h, w, c);
    {
        int idx = 0;
        for (const auto &t1 : t) {
            for (const auto &t2 : t1) {
                for (const auto &t3 : t2) {
                    t3 = idx++;  //
                }
            }
        }
    }
    {
        tensor_ref<int, 3> r(t.data(), t.shape());
        printf("%d\n", r.shape().offset(2, 3, 4));
        // r[2][3][4] = 0; // FIXME: make it work
        r[2][3][4] = static_cast<int>(0);
        r[2][3][4] = 1;
    }

    {
        tensor_view<int, 3> v(t.data(), t.shape());
        int tot = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                for (int k = 0; k < c; ++k) { tot += v[i][j][k]; }
            }
        }

        printf("%d, %d\n", n * (n + 1) / 2, tot);
    }
}

int main()
{
    example_1();
    return 0;
}
