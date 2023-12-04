/**
 *	@file	unit_test_variant_get_index.cpp
 *
 *	@brief	get<I>(v) のテスト
 *
 *	template <size_t I, typename... Types>
 *  constexpr variant_alternative_t<I, variant<Types...>>&
 *	get(variant<Types...>& v);
 *
 *	template <size_t I, typename... Types>
 *  constexpr variant_alternative_t<I, variant<Types...>>&&
 *	get(variant<Types...>&& v);
 *
 *	template <size_t I, typename... Types>
 *  constexpr variant_alternative_t<I, variant<Types...>> const&
 *	get(variant<Types...> const& v);
 *
 *	template <size_t I, typename... Types>
 *  constexpr variant_alternative_t<I, variant<Types...>> const&&
 *	get(variant<Types...> const&& v);
 */

#include <hamon/variant/get.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/variant/bad_variant_access.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_variant_test
{

namespace get_index_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ConstLvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		const V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(v));
		static_assert(hamon::is_same<decltype(get<0>(v)), const float&>::value, "");
		VERIFY(get<0>(v) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(v));
		static_assert(hamon::is_same<decltype(get<0>(v)), const int&>::value, "");
		VERIFY(get<0>(v) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(v));
		static_assert(hamon::is_same<decltype(get<1>(v)), const long&>::value, "");
		VERIFY(get<1>(v) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(v));
		static_assert(hamon::is_same<decltype(get<0>(v)), const int&>::value, "");
		VERIFY(get<0>(v) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(v));
		static_assert(hamon::is_same<decltype(get<1>(v)), const float&>::value, "");
		VERIFY(get<1>(v) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<2>(v));
		static_assert(hamon::is_same<decltype(get<2>(v)), const long&>::value, "");
		VERIFY(get<2>(v) == 3);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool LvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(v));
		static_assert(hamon::is_same<decltype(get<0>(v)), float&>::value, "");
		VERIFY(get<0>(v) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(v));
		static_assert(hamon::is_same<decltype(get<0>(v)), int&>::value, "");
		VERIFY(get<0>(v) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(v));
		static_assert(hamon::is_same<decltype(get<1>(v)), const long&>::value, "");
		VERIFY(get<1>(v) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(v));
		static_assert(hamon::is_same<decltype(get<0>(v)), int&>::value, "");
		VERIFY(get<0>(v) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(v));
		static_assert(hamon::is_same<decltype(get<1>(v)), const float&>::value, "");
		VERIFY(get<1>(v) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<2>(v));
		static_assert(hamon::is_same<decltype(get<2>(v)), long&>::value, "");
		VERIFY(get<2>(v) == 3);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ConstRvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		const V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(v))), const float&&>::value, "");
		VERIFY(get<0>(hamon::move(v)) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(v))), const int&&>::value, "");
		VERIFY(get<0>(hamon::move(v)) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<1>(hamon::move(v))), const long&&>::value, "");
		VERIFY(get<1>(hamon::move(v)) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(v))), const int&&>::value, "");
		VERIFY(get<0>(hamon::move(v)) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<1>(hamon::move(v))), const float&&>::value, "");
		VERIFY(get<1>(hamon::move(v)) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<2>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<2>(hamon::move(v))), const long&&>::value, "");
		VERIFY(get<2>(hamon::move(v)) == 3);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(v))), float&&>::value, "");
		VERIFY(get<0>(hamon::move(v)) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(v))), int&&>::value, "");
		VERIFY(get<0>(hamon::move(v)) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<1>(hamon::move(v))), const long&&>::value, "");
		VERIFY(get<1>(hamon::move(v)) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<0>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(v))), int&&>::value, "");
		VERIFY(get<0>(hamon::move(v)) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<1>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<1>(hamon::move(v))), const float&&>::value, "");
		VERIFY(get<1>(hamon::move(v)) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<2>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<2>(hamon::move(v))), long&&>::value, "");
		VERIFY(get<2>(hamon::move(v)) == 3);
	}
	return true;
}

GTEST_TEST(VariantTest, GetIndexTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConstLvalueTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(LvalueTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConstRvalueTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RvalueTest());

#if !defined(HAMON_NO_EXCEPTIONS)
	using hamon::get;
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		const V& cv = v;
		EXPECT_NO_THROW((void)get<0>(v));
		EXPECT_NO_THROW((void)get<0>(cv));
		EXPECT_NO_THROW((void)get<0>(hamon::move(v)));
		EXPECT_NO_THROW((void)get<0>(hamon::move(cv)));
		EXPECT_THROW((void)get<1>(v), hamon::bad_variant_access);
		EXPECT_THROW((void)get<1>(cv), hamon::bad_variant_access);
		EXPECT_THROW((void)get<1>(hamon::move(v)), hamon::bad_variant_access);
		EXPECT_THROW((void)get<1>(hamon::move(cv)), hamon::bad_variant_access);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 42);
		const V& cv = v;
		EXPECT_NO_THROW((void)get<1>(v));
		EXPECT_NO_THROW((void)get<1>(cv));
		EXPECT_NO_THROW((void)get<1>(hamon::move(v)));
		EXPECT_NO_THROW((void)get<1>(hamon::move(cv)));
		EXPECT_THROW((void)get<0>(v), hamon::bad_variant_access);
		EXPECT_THROW((void)get<0>(cv), hamon::bad_variant_access);
		EXPECT_THROW((void)get<0>(hamon::move(v)), hamon::bad_variant_access);
		EXPECT_THROW((void)get<0>(hamon::move(cv)), hamon::bad_variant_access);
	}
#endif
}

#undef VERIFY

}	// namespace get_index_test

}	// namespace hamon_variant_test
