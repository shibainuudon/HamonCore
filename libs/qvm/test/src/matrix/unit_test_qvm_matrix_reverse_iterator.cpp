/**
 *	@file	unit_test_qvm_matrix_reverse_iterator.cpp
 *
 *	@brief	reverse_iteratorのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, ReverseIteratorTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(!hamon::contiguous_iterator_t<typename matrix3x3::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix3x3::const_reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix3x4::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix3x4::const_reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix4x3::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix4x3::const_reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix4x4::reverse_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<typename matrix4x4::const_reverse_iterator>::value, "");

	static_assert(hamon::random_access_iterator_t<typename matrix3x3::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix3x3::const_reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix3x4::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix3x4::const_reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix4x3::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix4x3::const_reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix4x4::reverse_iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename matrix4x4::const_reverse_iterator>::value, "");

	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix3x3::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix3x3::const_reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix3x4::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix3x4::const_reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix4x3::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix4x3::const_reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix4x4::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix4x4::const_reverse_iterator>>::value, "");

	static_assert(hamon::is_same<vector3      &, hamon::iter_reference_t<typename matrix3x3::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector3 const&, hamon::iter_reference_t<typename matrix3x3::const_reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4      &, hamon::iter_reference_t<typename matrix3x4::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4 const&, hamon::iter_reference_t<typename matrix3x4::const_reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector3      &, hamon::iter_reference_t<typename matrix4x3::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector3 const&, hamon::iter_reference_t<typename matrix4x3::const_reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4      &, hamon::iter_reference_t<typename matrix4x4::reverse_iterator>>::value, "");
	static_assert(hamon::is_same<vector4 const&, hamon::iter_reference_t<typename matrix4x4::const_reverse_iterator>>::value, "");

	static_assert(hamon::is_same<typename matrix3x3::reverse_iterator,       decltype(hamon::declval<matrix3x3>().rbegin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::reverse_iterator,       decltype(hamon::declval<matrix3x3>().rend())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_reverse_iterator, decltype(hamon::declval<matrix3x3>().crbegin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_reverse_iterator, decltype(hamon::declval<matrix3x3>().crend())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_reverse_iterator, decltype(hamon::declval<matrix3x3 const>().rbegin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_reverse_iterator, decltype(hamon::declval<matrix3x3 const>().rend())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_reverse_iterator, decltype(hamon::declval<matrix3x3 const>().crbegin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_reverse_iterator, decltype(hamon::declval<matrix3x3 const>().crend())>::value, "");

	// const
	{
		HAMON_CONSTEXPR matrix3x3 const m1
		{
			 1, 2, 3,
			 4, 5, 6,
			 7, 8, 9,
		};
		HAMON_CONSTEXPR matrix3x3 const m2
		{
			 1, 2, 3,
			 4, 5, 6,
			 7, 8, 9,
		};
		HAMON_CONSTEXPR matrix3x3 const m3
		{
			 2, 2, 3,
			 4, 5, 6,
			 7, 8, 9,
		};
		HAMON_CONSTEXPR matrix3x3 const m4
		{
			 1, 2, 3,
			 4, 5, 6,
			 7, 8, 0,
		};
		HAMON_CONSTEXPR matrix3x3 const m5
		{
			 7, 8, 9,
			 4, 5, 6,
			 1, 2, 3,
		};

		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m1.begin(), m1.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m2.begin(), m2.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m3.begin(), m3.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m4.begin(), m4.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(m1.rbegin(), m1.rend(), m5.begin(), m5.end()));

		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m1.cbegin(), m1.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m2.cbegin(), m2.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m3.cbegin(), m3.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m4.cbegin(), m4.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(m1.crbegin(), m1.crend(), m5.cbegin(), m5.cend()));
	}

	// non const
	{
		matrix3x3 const m1
		{
			 1, 2, 3,
			 4, 5, 6,
			 7, 8, 9,
		};
		matrix3x3 const m2
		{
			 1, 2, 3,
			 4, 5, 6,
			 7, 8, 9,
		};
		matrix3x3 const m3
		{
			 2, 2, 3,
			 4, 5, 6,
			 7, 8, 9,
		};
		matrix3x3 const m4
		{
			 1, 2, 3,
			 4, 5, 6,
			 7, 8, 0,
		};
		matrix3x3 const m5
		{
			 7, 8, 9,
			 4, 5, 6,
			 1, 2, 3,
		};

		EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m1.begin(), m1.end()));
		EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m2.begin(), m2.end()));
		EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m3.begin(), m3.end()));
		EXPECT_FALSE(hamon::equal(m1.rbegin(), m1.rend(), m4.begin(), m4.end()));
		EXPECT_TRUE (hamon::equal(m1.rbegin(), m1.rend(), m5.begin(), m5.end()));

		EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m1.cbegin(), m1.cend()));
		EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m2.cbegin(), m2.cend()));
		EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m3.cbegin(), m3.cend()));
		EXPECT_FALSE(hamon::equal(m1.crbegin(), m1.crend(), m4.cbegin(), m4.cend()));
		EXPECT_TRUE (hamon::equal(m1.crbegin(), m1.crend(), m5.cbegin(), m5.cend()));
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
