#include "testing.hpp"

#include <ttl/bits/std_raw_shape.hpp>

TEST(raw_shape_test, test1)
{
    using raw_shape = ttl::internal::basic_raw_shape<std::uint32_t>;
    {
        raw_shape shape;
        ASSERT_EQ(shape.rank(), 0);
        ASSERT_EQ(shape.size(), 1);
        shape.as_ranked<0>();
    }
    {
        raw_shape shape(1);
        ASSERT_EQ(shape.rank(), 1);
        ASSERT_EQ(shape.size(), 1);
        shape.as_ranked<1>();
    }
    {
        raw_shape shape(1, 2);
        ASSERT_EQ(shape.rank(), 2);
        ASSERT_EQ(shape.size(), 2);
        shape.as_ranked<2>();
    }
    {
        raw_shape shape(1, 2, 3);
        ASSERT_EQ(shape.rank(), 3);
        ASSERT_EQ(shape.size(), 6);
        shape.as_ranked<3>();
    }
}
