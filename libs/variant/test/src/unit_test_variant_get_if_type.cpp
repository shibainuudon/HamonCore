/**
 *	@file	unit_test_variant_get_if_type.cpp
 *
 *	@brief	get_if<T>(v) のテスト
 *
 *	template<class T, class... Types>
 *	constexpr add_pointer_t<T>
 *	get_if(variant<Types...>* v) noexcept;
 *
 *	template<class T, class... Types>
 *	constexpr add_pointer_t<const T>
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

namespace get_if_type_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ConstTest()
{
	using hamon::get_if;
	{
		using V = hamon::variant<float>;
		const V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<float>(&v));
		static_assert(hamon::is_same<decltype(get_if<float>(&v)), const float*>::value, "");
		VERIFY(get_if<float>(&v) != nullptr);
		VERIFY(*get_if<float>(&v) == 0.5f);
		VERIFY(get_if<float>((const V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<int>(&v));
		static_assert(hamon::is_same<decltype(get_if<int>(&v)), const int*>::value, "");
		VERIFY(get_if<int>(&v) != nullptr);
		VERIFY(get_if<const long>(&v) == nullptr);
		VERIFY(*get_if<int>(&v) == 42);
		VERIFY(get_if<int>((const V*)nullptr) == nullptr);
		VERIFY(get_if<const long>((const V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<1>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<const long>(&v));
		static_assert(hamon::is_same<decltype(get_if<const long>(&v)), const long*>::value, "");
		VERIFY(get_if<int>(&v) == nullptr);
		VERIFY(get_if<const long>(&v) != nullptr);
		VERIFY(*get_if<const long>(&v) == 42);
		VERIFY(get_if<int>((const V*)nullptr) == nullptr);
		VERIFY(get_if<const long>((const V*)nullptr) == nullptr);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool NonConstTest()
{
	using hamon::get_if;
	{
		using V = hamon::variant<float>;
		V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<float>(&v));
		static_assert(hamon::is_same<decltype(get_if<float>(&v)), float*>::value, "");
		VERIFY(get_if<float>(&v) != nullptr);
		VERIFY(*get_if<float>(&v) == 0.5f);
		VERIFY(get_if<float>((V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<int>(&v));
		static_assert(hamon::is_same<decltype(get_if<int>(&v)), int*>::value, "");
		VERIFY(get_if<int>(&v) != nullptr);
		VERIFY(get_if<const long>(&v) == nullptr);
		VERIFY(*get_if<int>(&v) == 42);
		VERIFY(get_if<int>((V*)nullptr) == nullptr);
		VERIFY(get_if<const long>((V*)nullptr) == nullptr);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(get_if<const long>(&v));
		static_assert(hamon::is_same<decltype(get_if<const long>(&v)), const long*>::value, "");
		VERIFY(get_if<int>(&v) == nullptr);
		VERIFY(get_if<const long>(&v) != nullptr);
		VERIFY(*get_if<const long>(&v) == 42);
		VERIFY(get_if<int>((V*)nullptr) == nullptr);
		VERIFY(get_if<const long>((V*)nullptr) == nullptr);
	}
	return true;
}


GTEST_TEST(VariantTest, GetIfTypeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConstTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NonConstTest());
}

#undef VERIFY

}	// namespace get_if_type_test

}	// namespace hamon_variant_test
