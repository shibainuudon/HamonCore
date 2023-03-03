/**
 *	@file	unit_test_qvm_matrix_iterator.cpp
 *
 *	@brief	iteratorのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "constexpr_test.hpp"
#include "matrix_test.hpp"
#include <utility>

namespace hamon_qvm_test
{

namespace matrix_test
{

TYPED_TEST(MatrixTest, IteratorTest)
{
	using T = TypeParam;
	using matrix3x3 = hamon::qvm::matrix<T, 3, 3>;
	using matrix3x4 = hamon::qvm::matrix<T, 3, 4>;
	using matrix4x3 = hamon::qvm::matrix<T, 4, 3>;
	using matrix4x4 = hamon::qvm::matrix<T, 4, 4>;
	using vector3 = hamon::qvm::vector<T, 3>;
	using vector4 = hamon::qvm::vector<T, 4>;

	static_assert(hamon::contiguous_iterator_t<typename matrix3x3::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix3x3::const_iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix3x4::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix3x4::const_iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix4x3::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix4x3::const_iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix4x4::iterator>::value, "");
	static_assert(hamon::contiguous_iterator_t<typename matrix4x4::const_iterator>::value, "");

	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix3x3::iterator>>::value, "");
	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix3x3::const_iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix3x4::iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix3x4::const_iterator>>::value, "");
	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix4x3::iterator>>::value, "");
	static_assert(hamon::is_same<vector3, hamon::iter_value_t<typename matrix4x3::const_iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix4x4::iterator>>::value, "");
	static_assert(hamon::is_same<vector4, hamon::iter_value_t<typename matrix4x4::const_iterator>>::value, "");

	static_assert(hamon::is_same<vector3      &, hamon::iter_reference_t<typename matrix3x3::iterator>>::value, "");
	static_assert(hamon::is_same<vector3 const&, hamon::iter_reference_t<typename matrix3x3::const_iterator>>::value, "");
	static_assert(hamon::is_same<vector4      &, hamon::iter_reference_t<typename matrix3x4::iterator>>::value, "");
	static_assert(hamon::is_same<vector4 const&, hamon::iter_reference_t<typename matrix3x4::const_iterator>>::value, "");
	static_assert(hamon::is_same<vector3      &, hamon::iter_reference_t<typename matrix4x3::iterator>>::value, "");
	static_assert(hamon::is_same<vector3 const&, hamon::iter_reference_t<typename matrix4x3::const_iterator>>::value, "");
	static_assert(hamon::is_same<vector4      &, hamon::iter_reference_t<typename matrix4x4::iterator>>::value, "");
	static_assert(hamon::is_same<vector4 const&, hamon::iter_reference_t<typename matrix4x4::const_iterator>>::value, "");

	static_assert(hamon::is_same<typename matrix3x3::iterator,       decltype(std::declval<matrix3x3>().begin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::iterator,       decltype(std::declval<matrix3x3>().end())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_iterator, decltype(std::declval<matrix3x3>().cbegin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_iterator, decltype(std::declval<matrix3x3>().cend())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_iterator, decltype(std::declval<matrix3x3 const>().begin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_iterator, decltype(std::declval<matrix3x3 const>().end())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_iterator, decltype(std::declval<matrix3x3 const>().cbegin())>::value, "");
	static_assert(hamon::is_same<typename matrix3x3::const_iterator, decltype(std::declval<matrix3x3 const>().cend())>::value, "");

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

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(m1.begin(), m1.end(), m1.begin(), m1.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(m1.begin(), m1.end(), m2.begin(), m2.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.begin(), m1.end(), m3.begin(), m3.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.begin(), m1.end(), m4.begin(), m4.end()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.begin(), m1.end(), m5.begin(), m5.end()));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(m1.cbegin(), m1.cend(), m1.cbegin(), m1.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::equal(m1.cbegin(), m1.cend(), m2.cbegin(), m2.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.cbegin(), m1.cend(), m3.cbegin(), m3.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.cbegin(), m1.cend(), m4.cbegin(), m4.cend()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::equal(m1.cbegin(), m1.cend(), m5.cbegin(), m5.cend()));
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

		EXPECT_TRUE (hamon::equal(m1.begin(), m1.end(), m1.begin(), m1.end()));
		EXPECT_TRUE (hamon::equal(m1.begin(), m1.end(), m2.begin(), m2.end()));
		EXPECT_FALSE(hamon::equal(m1.begin(), m1.end(), m3.begin(), m3.end()));
		EXPECT_FALSE(hamon::equal(m1.begin(), m1.end(), m4.begin(), m4.end()));
		EXPECT_FALSE(hamon::equal(m1.begin(), m1.end(), m5.begin(), m5.end()));

		EXPECT_TRUE (hamon::equal(m1.cbegin(), m1.cend(), m1.cbegin(), m1.cend()));
		EXPECT_TRUE (hamon::equal(m1.cbegin(), m1.cend(), m2.cbegin(), m2.cend()));
		EXPECT_FALSE(hamon::equal(m1.cbegin(), m1.cend(), m3.cbegin(), m3.cend()));
		EXPECT_FALSE(hamon::equal(m1.cbegin(), m1.cend(), m4.cbegin(), m4.cend()));
		EXPECT_FALSE(hamon::equal(m1.cbegin(), m1.cend(), m5.cbegin(), m5.cend()));
	}
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
