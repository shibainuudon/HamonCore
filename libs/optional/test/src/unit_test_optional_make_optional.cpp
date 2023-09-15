/**
 *	@file	unit_test_optional_make_optional.cpp
 *
 *	@brief	make_optional関数のテスト
 *
 *	template<class T> constexpr optional<decay_t<T>> make_optional(T&& v);
 * 
 *	template<class T, class...Args>
 *	constexpr optional<T> make_optional(Args&&... args);
 *
 *	template<class T, class U, class... Args>
 *	constexpr optional<T> make_optional(initializer_list<U> il, Args&&... args);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace make_optional_test
{

struct S
{
	int value;

	HAMON_CXX11_CONSTEXPR S(int i) : value(i) {}
	HAMON_CXX14_CONSTEXPR S(std::initializer_list<int> il) : value((int)il.size()) {}
};

GTEST_TEST(OptionalTest, MakeOptionalTest)
{
	{
		auto o = hamon::make_optional(42);
		static_assert(hamon::is_same<decltype(o), hamon::optional<int>>::value, "");
		EXPECT_EQ(42, o.value());
	}
	{
		auto o = hamon::make_optional<hamon::string>(3u, 'A');
		static_assert(hamon::is_same<decltype(o), hamon::optional<hamon::string>>::value, "");
		EXPECT_EQ("AAA", o.value());
	}
	{
		std::allocator<char> alloc;
		auto o = hamon::make_optional<hamon::string>({ 'X', 'Y', 'Z' }, alloc);
		static_assert(hamon::is_same<decltype(o), hamon::optional<hamon::string>>::value, "");
		EXPECT_EQ("XYZ", o.value());
	}

	{
		HAMON_CXX11_CONSTEXPR auto o = hamon::make_optional(S(13));
		static_assert(hamon::is_same<hamon::remove_const_t<decltype(o)>, hamon::optional<S>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, o->value);
	}
	{
		HAMON_CXX11_CONSTEXPR auto o = hamon::make_optional<S>(14);
		static_assert(hamon::is_same<hamon::remove_const_t<decltype(o)>, hamon::optional<S>>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, o->value);
	}
	{
		HAMON_CXX14_CONSTEXPR auto o = hamon::make_optional<S>({1, 2, 3});
		static_assert(hamon::is_same<hamon::remove_const_t<decltype(o)>, hamon::optional<S>>::value, "");
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, o->value);
	}
}

}	// namespace make_optional_test

}	// namespace hamon_optional_test
