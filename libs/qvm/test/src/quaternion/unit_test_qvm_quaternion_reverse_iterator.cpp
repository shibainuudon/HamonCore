/**
 *	@file	unit_test_qvm_quaternion_reverse_iterator.cpp
 *
 *	@brief	reverse_iteratorのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/algorithm/equal.hpp>
#include "constexpr_test.hpp"
#include "quaternion_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace quaternion_test
{

TYPED_TEST(QuaternionTest, ReverseIteratorTest)
{
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	static_assert(!hamon::contiguous_iterator_t<typename quaternion::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename quaternion::const_reverse_iterator>::value, "");

	static_assert(hamon::random_access_iterator_t<typename quaternion::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename quaternion::const_reverse_iterator>::value, "");

	static_assert(std::is_same<T, hamon::iter_value_t<typename quaternion::reverse_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename quaternion::const_reverse_iterator>>::value, "");

	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename quaternion::reverse_iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename quaternion::const_reverse_iterator>>::value, "");

	static_assert(std::is_same<typename quaternion::reverse_iterator,       decltype(std::declval<quaternion>().rbegin())>::value, "");
	static_assert(std::is_same<typename quaternion::reverse_iterator,       decltype(std::declval<quaternion>().rend())>::value, "");
	static_assert(std::is_same<typename quaternion::const_reverse_iterator, decltype(std::declval<quaternion>().crbegin())>::value, "");
	static_assert(std::is_same<typename quaternion::const_reverse_iterator, decltype(std::declval<quaternion>().crend())>::value, "");
	static_assert(std::is_same<typename quaternion::const_reverse_iterator, decltype(std::declval<quaternion const>().rbegin())>::value, "");
	static_assert(std::is_same<typename quaternion::const_reverse_iterator, decltype(std::declval<quaternion const>().rend())>::value, "");
	static_assert(std::is_same<typename quaternion::const_reverse_iterator, decltype(std::declval<quaternion const>().crbegin())>::value, "");
	static_assert(std::is_same<typename quaternion::const_reverse_iterator, decltype(std::declval<quaternion const>().crend())>::value, "");

	// const
	{
		HAMON_CONSTEXPR quaternion v1 {1, 2, 3, 4};
		HAMON_CONSTEXPR quaternion v2 {0, 2, 3, 4};
		HAMON_CONSTEXPR quaternion v3 {1, 1, 3, 4};
		HAMON_CONSTEXPR quaternion v4 {4, 3, 2, 1};
		HAMON_CONSTEXPR quaternion v5 {1, 2, 3, 8};

		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v1.begin(), v1.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v2.begin(), v2.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v3.begin(), v3.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.rbegin(), v1.rend(), v4.begin(), v4.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v5.begin(), v5.end()));

		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v1.cbegin(), v1.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v2.cbegin(), v2.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v3.cbegin(), v3.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.crbegin(), v1.crend(), v4.cbegin(), v4.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v5.cbegin(), v5.cend()));
	}

	// non const
	{
		quaternion v1 {1, 2, 3, 4};
		quaternion v2 {0, 2, 3, 4};
		quaternion v3 {1, 1, 3, 4};
		quaternion v4 {4, 3, 2, 1};
		quaternion v5 {1, 2, 3, 8};

		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v1.begin(), v1.end()));
		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v2.begin(), v2.end()));
		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v3.begin(), v3.end()));
		EXPECT_TRUE (hamon::equal(v1.rbegin(), v1.rend(), v4.begin(), v4.end()));
		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v5.begin(), v5.end()));

		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v1.cbegin(), v1.cend()));
		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v2.cbegin(), v2.cend()));
		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v3.cbegin(), v3.cend()));
		EXPECT_TRUE (hamon::equal(v1.crbegin(), v1.crend(), v4.cbegin(), v4.cend()));
		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v5.cbegin(), v5.cend()));
	}
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
