/**
 *	@file	unit_test_variant_get_type.cpp
 *
 *	@brief	get<T>(v) のテスト
 *
 *	template<class T, class... Types> constexpr T& get(variant<Types...>& v);
 *	template<class T, class... Types> constexpr T&& get(variant<Types...>&& v);
 *	template<class T, class... Types> constexpr const T& get(const variant<Types...>& v);
 *	template<class T, class... Types> constexpr const T&& get(const variant<Types...>&& v);
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

namespace get_type_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ConstLvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		const V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<float>(v));
		static_assert(hamon::is_same<decltype(get<float>(v)), const float&>::value, "");
		VERIFY(get<float>(v) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(v));
		static_assert(hamon::is_same<decltype(get<int>(v)), const int&>::value, "");
		VERIFY(get<int>(v) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const long>(v));
		static_assert(hamon::is_same<decltype(get<const long>(v)), const long&>::value, "");
		VERIFY(get<const long>(v) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(v));
		static_assert(hamon::is_same<decltype(get<int>(v)), const int&>::value, "");
		VERIFY(get<int>(v) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const float>(v));
		static_assert(hamon::is_same<decltype(get<const float>(v)), const float&>::value, "");
		VERIFY(get<const float>(v) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<long>(v));
		static_assert(hamon::is_same<decltype(get<long>(v)), const long&>::value, "");
		VERIFY(get<long>(v) == 3);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool LvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<float>(v));
		static_assert(hamon::is_same<decltype(get<float>(v)), float&>::value, "");
		VERIFY(get<float>(v) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(v));
		static_assert(hamon::is_same<decltype(get<int>(v)), int&>::value, "");
		VERIFY(get<int>(v) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const long>(v));
		static_assert(hamon::is_same<decltype(get<const long>(v)), const long&>::value, "");
		VERIFY(get<const long>(v) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(v));
		static_assert(hamon::is_same<decltype(get<int>(v)), int&>::value, "");
		VERIFY(get<int>(v) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const float>(v));
		static_assert(hamon::is_same<decltype(get<const float>(v)), const float&>::value, "");
		VERIFY(get<const float>(v) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<long>(v));
		static_assert(hamon::is_same<decltype(get<long>(v)), long&>::value, "");
		VERIFY(get<long>(v) == 3);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ConstRvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		const V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<float>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<float>(hamon::move(v))), const float&&>::value, "");
		VERIFY(get<float>(hamon::move(v)) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<int>(hamon::move(v))), const int&&>::value, "");
		VERIFY(get<int>(hamon::move(v)) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		const V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const long>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<const long>(hamon::move(v))), const long&&>::value, "");
		VERIFY(get<const long>(hamon::move(v)) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<int>(hamon::move(v))), const int&&>::value, "");
		VERIFY(get<int>(hamon::move(v)) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const float>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<const float>(hamon::move(v))), const float&&>::value, "");
		VERIFY(get<const float>(hamon::move(v)) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		const V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<long>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<long>(hamon::move(v))), const long&&>::value, "");
		VERIFY(get<long>(hamon::move(v)) == 3);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RvalueTest()
{
	using hamon::get;
	{
		using V = hamon::variant<float>;
		V v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<float>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<float>(hamon::move(v))), float&&>::value, "");
		VERIFY(get<float>(hamon::move(v)) == 0.5f);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<int>(hamon::move(v))), int&&>::value, "");
		VERIFY(get<int>(hamon::move(v)) == 42);
	}
	{
		using V = hamon::variant<int, const long>;
		V v(hamon::in_place_index_t<1>{}, 43);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const long>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<const long>(hamon::move(v))), const long&&>::value, "");
		VERIFY(get<const long>(hamon::move(v)) == 43);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<0>{}, 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<int>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<int>(hamon::move(v))), int&&>::value, "");
		VERIFY(get<int>(hamon::move(v)) == 1);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<1>{}, 2.0f);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<const float>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<const float>(hamon::move(v))), const float&&>::value, "");
		VERIFY(get<const float>(hamon::move(v)) == 2.0f);
	}
	{
		using V = hamon::variant<int, const float, long>;
		V v(hamon::in_place_index_t<2>{}, 3);
		HAMON_ASSERT_NOEXCEPT_FALSE(get<long>(hamon::move(v)));
		static_assert(hamon::is_same<decltype(get<long>(hamon::move(v))), long&&>::value, "");
		VERIFY(get<long>(hamon::move(v)) == 3);
	}
	return true;
}

GTEST_TEST(VariantTest, GetTypeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConstLvalueTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(LvalueTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConstRvalueTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RvalueTest());

#if !defined(HAMON_NO_EXCEPTIONS)
	using hamon::get;
	{
		using V = hamon::variant<int, const int>;
		V v(hamon::in_place_index_t<0>{}, 42);
		const V& cv = v;
		EXPECT_NO_THROW((void)get<int>(v));
		EXPECT_NO_THROW((void)get<int>(cv));
		EXPECT_NO_THROW((void)get<int>(hamon::move(v)));
		EXPECT_NO_THROW((void)get<int>(hamon::move(cv)));
		EXPECT_THROW((void)get<const int>(v), hamon::bad_variant_access);
		EXPECT_THROW((void)get<const int>(cv), hamon::bad_variant_access);
		EXPECT_THROW((void)get<const int>(hamon::move(v)), hamon::bad_variant_access);
		EXPECT_THROW((void)get<const int>(hamon::move(cv)), hamon::bad_variant_access);
	}
	{
		using V = hamon::variant<int, const int>;
		V v(hamon::in_place_index_t<1>{}, 42);
		const V& cv = v;
		EXPECT_NO_THROW((void)get<const int>(v));
		EXPECT_NO_THROW((void)get<const int>(cv));
		EXPECT_NO_THROW((void)get<const int>(hamon::move(v)));
		EXPECT_NO_THROW((void)get<const int>(hamon::move(cv)));
		EXPECT_THROW((void)get<int>(v), hamon::bad_variant_access);
		EXPECT_THROW((void)get<int>(cv), hamon::bad_variant_access);
		EXPECT_THROW((void)get<int>(hamon::move(v)), hamon::bad_variant_access);
		EXPECT_THROW((void)get<int>(hamon::move(cv)), hamon::bad_variant_access);
	}
#endif
}

#undef VERIFY

}	// namespace get_type_test

}	// namespace hamon_variant_test
