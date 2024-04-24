/**
 *	@file	unit_test_complex_tuple.cpp
 *
 *	@brief	Tuple interfaceのテスト
 *
 *	template<class T>
 *	struct tuple_size<complex<T>>;
 *
 *	template<size_t I, class T>
 *	struct tuple_element<I, complex<T>>;
 *
 *	template<size_t I, class T>
 *	constexpr T& get(complex<T>& z) noexcept;
 *	template<size_t I, class T>
 *	constexpr T&& get(complex<T>&& z) noexcept;
 *	template<size_t I, class T>
 *	constexpr const T& get(const complex<T>& z) noexcept;
 *	template<size_t I, class T>
 *	constexpr const T&& get(const complex<T>&& z) noexcept;
 */

#include <hamon/complex/complex.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace tuple_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Complex = hamon::complex<T>;
	static_assert(std::tuple_size<Complex>::value == 2, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<0, Complex>, T>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Complex>, T>::value, "");

	static_assert(hamon::is_same<decltype(hamon::get<0>(hamon::declval<Complex&>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<1>(hamon::declval<Complex&>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<0>(hamon::declval<Complex&&>())), T&&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<1>(hamon::declval<Complex&&>())), T&&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<0>(hamon::declval<Complex const&>())), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<1>(hamon::declval<Complex const&>())), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<0>(hamon::declval<Complex const&&>())), T const&&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::get<1>(hamon::declval<Complex const&&>())), T const&&>::value, "");

	{
		Complex c{1, 2};
		VERIFY(hamon::get<0>(c) == 1);
		VERIFY(hamon::get<1>(c) == 2);

		VERIFY(hamon::get<0>(hamon::move(c)) == 1);
		VERIFY(hamon::get<1>(hamon::move(c)) == 2);
	}
	{
		Complex const c{3, 4};
		VERIFY(hamon::get<0>(c) == 3);
		VERIFY(hamon::get<1>(c) == 4);

		VERIFY(hamon::get<0>(hamon::move(c)) == 3);
		VERIFY(hamon::get<1>(hamon::move(c)) == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ComplexTest, TupleTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<double>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<long double>());
}

}	// namespace tuple_test

}	// namespace hamon_complex_test
