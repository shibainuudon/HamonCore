/**
 *	@file	unit_test_qvm_quaternion_iterator.cpp
 *
 *	@brief	iteratorのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <utility>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, IteratorTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(hamon::contiguous_iterator_t<typename quaternion::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename quaternion::const_iterator>::value, "");

	static_assert(hamon::is_same<T, hamon::iter_value_t<typename quaternion::iterator>>::value, "");
	static_assert(hamon::is_same<T, hamon::iter_value_t<typename quaternion::const_iterator>>::value, "");

	static_assert(hamon::is_same<T      &, hamon::iter_reference_t<typename quaternion::iterator>>::value, "");
	static_assert(hamon::is_same<T const&, hamon::iter_reference_t<typename quaternion::const_iterator>>::value, "");

	static_assert(hamon::is_same<typename quaternion::iterator,       decltype(std::declval<quaternion>().begin())>::value, "");
	static_assert(hamon::is_same<typename quaternion::iterator,       decltype(std::declval<quaternion>().end())>::value, "");
	static_assert(hamon::is_same<typename quaternion::const_iterator, decltype(std::declval<quaternion>().cbegin())>::value, "");
	static_assert(hamon::is_same<typename quaternion::const_iterator, decltype(std::declval<quaternion>().cend())>::value, "");
	static_assert(hamon::is_same<typename quaternion::const_iterator, decltype(std::declval<quaternion const>().begin())>::value, "");
	static_assert(hamon::is_same<typename quaternion::const_iterator, decltype(std::declval<quaternion const>().end())>::value, "");
	static_assert(hamon::is_same<typename quaternion::const_iterator, decltype(std::declval<quaternion const>().cbegin())>::value, "");
	static_assert(hamon::is_same<typename quaternion::const_iterator, decltype(std::declval<quaternion const>().cend())>::value, "");

	// const
	{
		HAMON_CONSTEXPR quaternion v1 {1, 2, 3, 4};
		HAMON_CONSTEXPR quaternion v2 {0, 2, 3, 4};
		HAMON_CONSTEXPR quaternion v3 {1, 1, 3, 4};
		HAMON_CONSTEXPR quaternion v4 {4, 3, 2, 1};
		HAMON_CONSTEXPR quaternion v5 {1, 2, 3, 8};

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::ranges::equal(v1, v1));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::ranges::equal(v1, v2));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::ranges::equal(v1, v3));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::ranges::equal(v1, v4));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::ranges::equal(v1, v5));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.begin(), v1.end(), v1.begin(), v1.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v2.begin(), v2.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v3.begin(), v3.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v4.begin(), v4.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v5.begin(), v5.end()));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.cbegin(), v1.cend(), v1.cbegin(), v1.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v3.cbegin(), v3.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v4.cbegin(), v4.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v5.cbegin(), v5.cend()));
	}

	// non const
	{
		quaternion v1 {1, 2, 3, 4};
		quaternion v2 {0, 2, 3, 4};
		quaternion v3 {1, 1, 3, 4};
		quaternion v4 {4, 3, 2, 1};
		quaternion v5 {1, 2, 3, 8};

		EXPECT_TRUE (hamon::ranges::equal(v1, v1));
		EXPECT_FALSE(hamon::ranges::equal(v1, v2));
		EXPECT_FALSE(hamon::ranges::equal(v1, v3));
		EXPECT_FALSE(hamon::ranges::equal(v1, v4));
		EXPECT_FALSE(hamon::ranges::equal(v1, v5));

		EXPECT_TRUE (hamon::equal(v1.begin(), v1.end(), v1.begin(), v1.end()));
		EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v2.begin(), v2.end()));
		EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v3.begin(), v3.end()));
		EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v4.begin(), v4.end()));
		EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v5.begin(), v5.end()));

		EXPECT_TRUE (hamon::equal(v1.cbegin(), v1.cend(), v1.cbegin(), v1.cend()));
		EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend()));
		EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v3.cbegin(), v3.cend()));
		EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v4.cbegin(), v4.cend()));
		EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v5.cbegin(), v5.cend()));
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
