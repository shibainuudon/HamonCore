/**
 *	@file	unit_test_variant_get_if_index.cpp
 *
 *	@brief	get_if<I>(v) のテスト
 *
 *	template<size_t I, class... Types>
 *	constexpr add_pointer_t<variant_alternative_t<I, variant<Types...>>>
 *	get_if(variant<Types...>* v) noexcept;
 *
 *	template<size_t I, class... Types>
 *	constexpr add_pointer_t<const variant_alternative_t<I, variant<Types...>>>
 *	get_if(const variant<Types...>* v) noexcept;
 */

#include <hamon/variant/get_if.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_variant_test
{

namespace get_if_index_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ConstTest()
{
	using hamon::get_if;
	{
		using V = hamon::variant<float>;
		const V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<0>(&v));
		static_assert(hamon::is_same<decltype(get_if<0>(&v)), const float*>::value, "");
		VERIFY(get_if<0>(&v) != nullptr);
		VERIFY(*get_if<0>(&v) == 0.5f);
		VERIFY(get_if<0>((const V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<0>(&v));
		static_assert(hamon::is_same<decltype(get_if<0>(&v)), const int*>::value, "");
		VERIFY(get_if<0>(&v) != nullptr);
		VERIFY(get_if<1>(&v) == nullptr);
		VERIFY(*get_if<0>(&v) == 42);
		VERIFY(get_if<0>((const V*)nullptr) == nullptr);
		VERIFY(get_if<1>((const V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<1>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<1>(&v));
		static_assert(hamon::is_same<decltype(get_if<1>(&v)), const long*>::value, "");
		VERIFY(get_if<0>(&v) == nullptr);
		VERIFY(get_if<1>(&v) != nullptr);
		VERIFY(*get_if<1>(&v) == 42);
		VERIFY(get_if<0>((const V*)nullptr) == nullptr);
		VERIFY(get_if<1>((const V*)nullptr) == nullptr);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool NonConstTest()
{
	using hamon::get_if;
	{
		using V = hamon::variant<float>;
		V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<0>(&v));
		static_assert(hamon::is_same<decltype(get_if<0>(&v)), float*>::value, "");
		VERIFY(get_if<0>(&v) != nullptr);
		VERIFY(*get_if<0>(&v) == 0.5f);
		VERIFY(get_if<0>((V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<0>(&v));
		static_assert(hamon::is_same<decltype(get_if<0>(&v)), int*>::value, "");
		VERIFY(get_if<0>(&v) != nullptr);
		VERIFY(get_if<1>(&v) == nullptr);
		VERIFY(*get_if<0>(&v) == 42);
		VERIFY(get_if<0>((V*)nullptr) == nullptr);
		VERIFY(get_if<1>((V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<1>(&v));
		static_assert(hamon::is_same<decltype(get_if<1>(&v)), const long*>::value, "");
		VERIFY(get_if<0>(&v) == nullptr);
		VERIFY(get_if<1>(&v) != nullptr);
		VERIFY(*get_if<1>(&v) == 42);
		VERIFY(get_if<0>((V*)nullptr) == nullptr);
		VERIFY(get_if<1>((V*)nullptr) == nullptr);
	}
	return true;
}


GTEST_TEST(VariantTest, GetIfIndexTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConstTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NonConstTest());
}

#undef VERIFY

}	// namespace get_if_index_test

}	// namespace hamon_variant_test
