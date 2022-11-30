/**
 *	@file	unit_test_qvm_vector_reverse_iterator.cpp
 *
 *	@brief	reverse_iteratorのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/algorithm/equal.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, ReverseIteratorTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::contiguous_iterator_t<typename vector2::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename vector2::const_reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename vector3::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename vector3::const_reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename vector4::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename vector4::const_reverse_iterator>::value, "");

	static_assert(hamon::random_access_iterator_t<typename vector2::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename vector2::const_reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename vector3::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename vector3::const_reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename vector4::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename vector4::const_reverse_iterator>::value, "");

	static_assert(std::is_same<T, hamon::iter_value_t<typename vector2::reverse_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector2::const_reverse_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector3::reverse_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector3::const_reverse_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector4::reverse_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector4::const_reverse_iterator>>::value, "");

	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename vector2::reverse_iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename vector2::const_reverse_iterator>>::value, "");
	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename vector3::reverse_iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename vector3::const_reverse_iterator>>::value, "");
	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename vector4::reverse_iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename vector4::const_reverse_iterator>>::value, "");

	static_assert(std::is_same<typename vector2::reverse_iterator,       decltype(std::declval<vector2>().rbegin())>::value, "");
	static_assert(std::is_same<typename vector2::reverse_iterator,       decltype(std::declval<vector2>().rend())>::value, "");
	static_assert(std::is_same<typename vector2::const_reverse_iterator, decltype(std::declval<vector2>().crbegin())>::value, "");
	static_assert(std::is_same<typename vector2::const_reverse_iterator, decltype(std::declval<vector2>().crend())>::value, "");
	static_assert(std::is_same<typename vector2::const_reverse_iterator, decltype(std::declval<vector2 const>().rbegin())>::value, "");
	static_assert(std::is_same<typename vector2::const_reverse_iterator, decltype(std::declval<vector2 const>().rend())>::value, "");
	static_assert(std::is_same<typename vector2::const_reverse_iterator, decltype(std::declval<vector2 const>().crbegin())>::value, "");
	static_assert(std::is_same<typename vector2::const_reverse_iterator, decltype(std::declval<vector2 const>().crend())>::value, "");

	{
		HAMON_CONSTEXPR vector2 v1 { 10, 20};
		HAMON_CONSTEXPR vector2 v2 { 10, 20};
		HAMON_CONSTEXPR vector2 v3 {-10, 20};
		HAMON_CONSTEXPR vector2 v4 { 20, 10};

		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v1.begin(), v1.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v2.begin(), v2.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v3.begin(), v3.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.rbegin(), v1.rend(), v4.begin(), v4.end()));

		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v1.cbegin(), v1.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v2.cbegin(), v2.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v3.cbegin(), v3.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.crbegin(), v1.crend(), v4.cbegin(), v4.cend()));
	}
	{
		vector3 v1 {0,1,2};
		vector3 v2 {0,1,2};
		vector3 v3 {0,1,3};
		vector3 v4 {2,1,0};

		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v1.begin(), v1.end()));
		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v2.begin(), v2.end()));
		EXPECT_FALSE(hamon::equal(v1.rbegin(), v1.rend(), v3.begin(), v3.end()));
		EXPECT_TRUE (hamon::equal(v1.rbegin(), v1.rend(), v4.begin(), v4.end()));

		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v1.cbegin(), v1.cend()));
		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v2.cbegin(), v2.cend()));
		EXPECT_FALSE(hamon::equal(v1.crbegin(), v1.crend(), v3.cbegin(), v3.cend()));
		EXPECT_TRUE (hamon::equal(v1.crbegin(), v1.crend(), v4.cbegin(), v4.cend()));
	}
	{
		HAMON_CONSTEXPR vector4 v1 {1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 v2 {0, 2, 3, 4};
		HAMON_CONSTEXPR vector4 v3 {1, 1, 3, 4};
		HAMON_CONSTEXPR vector4 v4 {4, 3, 2, 1};
		HAMON_CONSTEXPR vector4 v5 {1, 2, 3, 8};

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
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
