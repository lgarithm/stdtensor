#include "testing.hpp"

#include <ttl/experimental/raw_tensor>
#include <ttl/tensor>

TEST(raw_tensor_test, test1)
{
    using ttl::experimental::raw_tensor;

    using encoder = raw_tensor::encoder_type;
    using raw_shape = raw_tensor::shape_type;

    {
        raw_tensor t(encoder::value<float>());
        ASSERT_EQ(t.shape().size(), static_cast<raw_shape::dimension_type>(1));
        ASSERT_EQ(t.value_type(), encoder::value<float>());
        ASSERT_EQ(t.data<float>(), t.data());
        t.ref_as<float, 0>();
        t.view_as<float, 0>();
    }
    {
        raw_tensor t(encoder::value<float>(), 1);
        ASSERT_EQ(t.shape().size(), static_cast<raw_shape::dimension_type>(1));
        ASSERT_EQ(t.value_type(), encoder::value<float>());
        ASSERT_EQ(t.data<float>(), t.data());
        t.ref_as<float, 1>();
        t.view_as<float, 1>();
    }
    {
        raw_tensor t(encoder::value<float>(), 1, 2);
        ASSERT_EQ(t.shape().size(), static_cast<raw_shape::dimension_type>(2));
        ASSERT_EQ(t.value_type(), encoder::value<float>());
        ASSERT_EQ(t.data<float>(), t.data());
        t.ref_as<float, 2>();
        t.view_as<float, 2>();
    }
    {
        raw_tensor t(encoder::value<float>(), 1, 2, 3);
        ASSERT_EQ(t.value_type(), encoder::value<float>());
        ASSERT_EQ(t.shape().size(), static_cast<raw_shape::dimension_type>(6));
        ASSERT_EQ(t.data<float>(), t.data());
        t.ref_as<float, 3>();
        t.view_as<float, 3>();
    }
}

TEST(raw_tensor_test, test_convert)
{
    using ttl::experimental::raw_ref;
    using ttl::experimental::raw_view;

    using ttl::experimental::raw_tensor;
    using encoder = raw_tensor::encoder_type;

    using ttl::experimental::raw_tensor_ref;
    using ttl::experimental::raw_tensor_view;

    using R = float;
    ttl::tensor<R, 4> t(10, 224, 244, 3);
    {
        raw_tensor_ref r(ref(t));
        raw_tensor_view v(view(t));

        raw_tensor_ref r1 = raw_ref(t);
        raw_tensor_view v1 = raw_view(t);

        ttl::tensor_ref<R, 4> _tr = r.ranked_as<R, 4>();
        UNUSED(_tr);
        ttl::tensor_view<R, 4> _tv = v.ranked_as<R, 4>();
        UNUSED(_tv);
    }
    {
        ttl::tensor_ref<float, 4> rt = ref(t);

        raw_tensor_ref r(rt);
        raw_tensor_view v(view(rt));

        raw_tensor_ref r1 = raw_ref(rt);
        raw_tensor_view v1 = raw_view(rt);
    }
    {
        ttl::tensor_view<float, 4> vt = view(t);

        raw_tensor_view v(vt);
        raw_tensor_view v1 = raw_view(vt);
    }

    {
        raw_tensor t(encoder::value<R>(), 3, 4, 5, 6);
        raw_tensor_ref r(t);
        raw_tensor_view v(t);
        raw_tensor_view v1(r);
    }
}

template <typename R, typename T> void test_raw_accessors(const T &t)
{
    t.shape();
    t.value_type();
    test_data_end_raw<R>(t);
}

TEST(raw_tensor_test, test_data)
{
    using ttl::experimental::raw_tensor;
    using encoder = raw_tensor::encoder_type;

    using ttl::experimental::raw_ref;
    using ttl::experimental::raw_view;

    using ttl::experimental::raw_tensor_ref;
    using ttl::experimental::raw_tensor_view;

    using R = float;
    ttl::tensor<R, 4> t(10, 224, 244, 3);

    raw_tensor rt(encoder::value<R>(), 10, 224, 244, 3);
    raw_tensor_ref rr = raw_ref(t);
    raw_tensor_view rv = raw_view(t);

    test_raw_accessors<R>(rt);
    test_raw_accessors<R>(rr);
    test_raw_accessors<R>(rv);
}
