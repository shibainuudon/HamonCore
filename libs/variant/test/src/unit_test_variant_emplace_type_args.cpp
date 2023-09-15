/**
 *	@file	unit_test_variant_emplace_type_args.cpp
 *
 *	@brief	型を指定するemplaceのテスト
 * 
 *	template <typename T, typename... Args>
 *	constexpr T& emplace(Args&&...);
 */

#include <hamon/variant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace emplace_type_args_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Variant, typename T, typename... Args>
using invoke_emplace =
	decltype(hamon::declval<Variant>().template emplace<T>(hamon::declval<Args>()...));

struct Vec2
{
	float x;
	float y;

	HAMON_CXX11_CONSTEXPR Vec2(float xx, float yy)
		: x(xx) , y(yy) {}
};

inline HAMON_CXX20_CONSTEXPR bool EmplaceTypeArgsTest()
{
	{
		hamon::variant<int> v(42);
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 42);
		auto& ref1 = v.emplace<int>();
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		VERIFY(&ref1 == &hamon::adl_get<0>(v));
		auto& ref2 = v.emplace<int>(43);
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 43);
		VERIFY(&ref2 == &hamon::adl_get<0>(v));
	}
	{
		hamon::variant<int, float, long, Vec2> v;
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		auto& ref1 = v.emplace<float>(0.5f);
		VERIFY(v.index() == 1u);
		VERIFY(hamon::adl_get<1>(v) == 0.5f);
		VERIFY(&ref1 == &hamon::adl_get<1>(v));
		auto& ref2 = v.emplace<long>(42);
		VERIFY(v.index() == 2u);
		VERIFY(hamon::adl_get<2>(v) == 42);
		VERIFY(&ref2 == &hamon::adl_get<2>(v));
		auto& ref3 = v.emplace<int>();
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		VERIFY(&ref3 == &hamon::adl_get<0>(v));
		auto& ref4 = v.emplace<Vec2>(41.0f, 42.0f);
		VERIFY(v.index() == 3u);
		VERIFY(hamon::adl_get<3>(v).x == 41);
		VERIFY(hamon::adl_get<3>(v).y == 42);
		VERIFY(&ref4 == &hamon::adl_get<3>(v));
	}

	return true;
}

GTEST_TEST(VariantTest, EmplaceTypeArgsTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION) && !defined(HAMON_APPLE_CLANG)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EmplaceTypeArgsTest());
#else
	EXPECT_TRUE(EmplaceTypeArgsTest());
#endif

	{
		using V = hamon::variant<int>;
		static_assert( hamon::is_detected<invoke_emplace, V, int>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, int, int>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, int, float>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, float, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, int, decltype(nullptr)>::value, "");
	}
	{
		using V = hamon::variant<int, char, void*, hamon::string, char>;
		static_assert( hamon::is_detected<invoke_emplace, V, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, char>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, void*>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, hamon::string>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, int, int>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, int, char>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, int, void*>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, char, char>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, char, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, char, void*>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, void*, void*>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, void*, int*>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, void*, const int*>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, void*, int>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, hamon::string, const char*>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, hamon::string, hamon::size_t, char>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, hamon::string, const void*>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, hamon::string, hamon::size_t, char, std::allocator<char>>::value, "");
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		struct S { operator int() { throw 42; } };
		hamon::variant<float, int> v{12.f};
		EXPECT_THROW(v.emplace<int>(S()), int);
#if !defined(HAMON_USE_STD_VARIANT)
		EXPECT_TRUE(v.valueless_by_exception());
#endif
	}
#endif
}

#undef VERIFY

}	// namespace emplace_type_args_test

}	// namespace hamon_variant_test
