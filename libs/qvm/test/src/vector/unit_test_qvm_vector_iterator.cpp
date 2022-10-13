/**
 *	@file	unit_test_qvm_vector_iterator.cpp
 *
 *	@brief	iteratorのテスト
 */

#include <hamon/qvm/vector.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, IteratorTest)
{
	using T = TypeParam;
	using vector2 = hamon::qvm::vector<T, 2>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::contiguous_iterator_t<typename vector2::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename vector2::const_iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename vector3::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename vector3::const_iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename vector4::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename vector4::const_iterator>::value, "");

	static_assert(std::is_same<T, hamon::iter_value_t<typename vector2::iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector2::const_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector3::iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector3::const_iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector4::iterator>>::value, "");
	static_assert(std::is_same<T, hamon::iter_value_t<typename vector4::const_iterator>>::value, "");

	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename vector2::iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename vector2::const_iterator>>::value, "");
	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename vector3::iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename vector3::const_iterator>>::value, "");
	static_assert(std::is_same<T      &, hamon::iter_reference_t<typename vector4::iterator>>::value, "");
	static_assert(std::is_same<T const&, hamon::iter_reference_t<typename vector4::const_iterator>>::value, "");

	static_assert(std::is_same<typename vector2::iterator,       decltype(std::declval<vector2>().begin())>::value, "");
	static_assert(std::is_same<typename vector2::iterator,       decltype(std::declval<vector2>().end())>::value, "");
	static_assert(std::is_same<typename vector2::const_iterator, decltype(std::declval<vector2>().cbegin())>::value, "");
	static_assert(std::is_same<typename vector2::const_iterator, decltype(std::declval<vector2>().cend())>::value, "");
	static_assert(std::is_same<typename vector2::const_iterator, decltype(std::declval<vector2 const>().begin())>::value, "");
	static_assert(std::is_same<typename vector2::const_iterator, decltype(std::declval<vector2 const>().end())>::value, "");
	static_assert(std::is_same<typename vector2::const_iterator, decltype(std::declval<vector2 const>().cbegin())>::value, "");
	static_assert(std::is_same<typename vector2::const_iterator, decltype(std::declval<vector2 const>().cend())>::value, "");

	{
		HAMON_CONSTEXPR vector2 v1 { 10, 20};
		HAMON_CONSTEXPR vector2 v2 { 10, 20};
		HAMON_CONSTEXPR vector2 v3 {-10, 20};
		HAMON_CONSTEXPR vector2 v4 { 20, 10};

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::ranges::equal(v1, v1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::ranges::equal(v1, v2));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::ranges::equal(v1, v3));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::ranges::equal(v1, v4));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.begin(), v1.end(), v1.begin(), v1.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.begin(), v1.end(), v2.begin(), v2.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v3.begin(), v3.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v4.begin(), v4.end()));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.cbegin(), v1.cend(), v1.cbegin(), v1.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v3.cbegin(), v3.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v4.cbegin(), v4.cend()));
	}
	{
		vector3 v1 {0,1,2};
		vector3 v2 {0,1,2};
		vector3 v3 {0,1,3};
		vector3 v4 {2,1,0};

		EXPECT_TRUE (hamon::ranges::equal(v1, v1));
		EXPECT_TRUE (hamon::ranges::equal(v1, v2));
		EXPECT_FALSE(hamon::ranges::equal(v1, v3));
		EXPECT_FALSE(hamon::ranges::equal(v1, v4));

		EXPECT_TRUE (hamon::equal(v1.begin(), v1.end(), v1.begin(), v1.end()));
		EXPECT_TRUE (hamon::equal(v1.begin(), v1.end(), v2.begin(), v2.end()));
		EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v3.begin(), v3.end()));
		EXPECT_FALSE(hamon::equal(v1.begin(), v1.end(), v4.begin(), v4.end()));

		EXPECT_TRUE (hamon::equal(v1.cbegin(), v1.cend(), v1.cbegin(), v1.cend()));
		EXPECT_TRUE (hamon::equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend()));
		EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v3.cbegin(), v3.cend()));
		EXPECT_FALSE(hamon::equal(v1.cbegin(), v1.cend(), v4.cbegin(), v4.cend()));
	}
	{
		HAMON_CONSTEXPR vector4 v1 {1, 2, 3, 4};
		HAMON_CONSTEXPR vector4 v2 {0, 2, 3, 4};
		HAMON_CONSTEXPR vector4 v3 {1, 1, 3, 4};
		HAMON_CONSTEXPR vector4 v4 {4, 3, 2, 1};
		HAMON_CONSTEXPR vector4 v5 {1, 2, 3, 8};

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
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
