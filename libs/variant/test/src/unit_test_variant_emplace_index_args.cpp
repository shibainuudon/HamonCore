/**
 *	@file	unit_test_variant_emplace_index_args.cpp
 *
 *	@brief	インデックスを指定するemplaceのテスト
 * 
 *	template <size_t I, typename... Args>
 *	constexpr variant_alternative_t<I, variant<Types...>>&
 *	emplace(Args&&...);
 */

#include <hamon/variant.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace emplace_index_args_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename AlwaysVoid, typename Variant, hamon::size_t I, typename... Args>
struct is_detected_impl
	: public hamon::false_type
{};

template <typename Variant, hamon::size_t I, typename... Args>
struct is_detected_impl<hamon::void_t<
	decltype(hamon::declval<Variant>().template emplace<I>(hamon::declval<Args>()...))>, Variant, I, Args...>
	: public hamon::true_type
{};

template <typename Variant, hamon::size_t I, typename... Args>
using is_detected_emplace = is_detected_impl<void, Variant, I, Args...>;

struct Vec2
{
	float x;
	float y;

	HAMON_CXX11_CONSTEXPR Vec2(float xx, float yy)
		: x(xx) , y(yy) {}
};

inline HAMON_CXX20_CONSTEXPR bool EmplaceIndexArgsTest()
{
	{
		hamon::variant<int> v(42);
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 42);
		auto& ref1 = v.emplace<0>();
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		VERIFY(&ref1 == &hamon::adl_get<0>(v));
		auto& ref2 = v.emplace<0>(43);
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 43);
		VERIFY(&ref2 == &hamon::adl_get<0>(v));
	}
	{
		hamon::variant<int, float, int, Vec2> v;
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		auto& ref1 = v.emplace<1>(0.5f);
		VERIFY(v.index() == 1u);
		VERIFY(hamon::adl_get<1>(v) == 0.5f);
		VERIFY(&ref1 == &hamon::adl_get<1>(v));
		auto& ref2 = v.emplace<2>(42);
		VERIFY(v.index() == 2u);
		VERIFY(hamon::adl_get<2>(v) == 42);
		VERIFY(&ref2 == &hamon::adl_get<2>(v));
		auto& ref3 = v.emplace<0>();
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		VERIFY(&ref3 == &hamon::adl_get<0>(v));
		auto& ref4 = v.emplace<3>(41.0f, 42.0f);
		VERIFY(v.index() == 3u);
		VERIFY(hamon::adl_get<3>(v).x == 41);
		VERIFY(hamon::adl_get<3>(v).y == 42);
		VERIFY(&ref4 == &hamon::adl_get<3>(v));
	}

	return true;
}

GTEST_TEST(VariantTest, EmplaceIndexArgsTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION) && !defined(HAMON_APPLE_CLANG)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EmplaceIndexArgsTest());
#else
	EXPECT_TRUE(EmplaceIndexArgsTest());
#endif

	{
		using V = hamon::variant<int>;
		static_assert( is_detected_emplace<V, 0>::value, "");
		static_assert( is_detected_emplace<V, 0, int>::value, "");
		static_assert( is_detected_emplace<V, 0, float>::value, "");
		static_assert(!is_detected_emplace<V, 0, decltype(nullptr)>::value, "");
		static_assert(!is_detected_emplace<V, 1, int>::value, "");
	}
	{
		using V = hamon::variant<int, char, void*, std::string, char>;
		static_assert( is_detected_emplace<V, 0>::value, "");
		static_assert( is_detected_emplace<V, 1>::value, "");
		static_assert( is_detected_emplace<V, 2>::value, "");
		static_assert( is_detected_emplace<V, 3>::value, "");
		static_assert( is_detected_emplace<V, 4>::value, "");
		static_assert( is_detected_emplace<V, 0, int>::value, "");
		static_assert( is_detected_emplace<V, 0, char>::value, "");
		static_assert(!is_detected_emplace<V, 0, void*>::value, "");
		static_assert( is_detected_emplace<V, 1, char>::value, "");
		static_assert( is_detected_emplace<V, 1, int>::value, "");
		static_assert(!is_detected_emplace<V, 1, void*>::value, "");
		static_assert( is_detected_emplace<V, 2, void*>::value, "");
		static_assert( is_detected_emplace<V, 2, int*>::value, "");
		static_assert(!is_detected_emplace<V, 2, const int*>::value, "");
		static_assert(!is_detected_emplace<V, 2, int>::value, "");
		static_assert( is_detected_emplace<V, 3, const char*>::value, "");
		static_assert( is_detected_emplace<V, 3, hamon::size_t, char>::value, "");
		static_assert(!is_detected_emplace<V, 3, const void*>::value, "");
		static_assert( is_detected_emplace<V, 3, hamon::size_t, char, std::allocator<char>>::value, "");
		static_assert( is_detected_emplace<V, 4, char>::value, "");
		static_assert( is_detected_emplace<V, 4, int>::value, "");
		static_assert(!is_detected_emplace<V, 4, void*>::value, "");
		static_assert(!is_detected_emplace<V, 5, char>::value, "");
		static_assert(!is_detected_emplace<V, 5, int>::value, "");
		static_assert(!is_detected_emplace<V, 5, void*>::value, "");
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		struct S { operator int() { throw 42; } };
		hamon::variant<float, int> v{12.f};
		EXPECT_THROW(v.emplace<1>(S()), int);
#if !defined(HAMON_USE_STD_VARIANT)
		EXPECT_TRUE(v.valueless_by_exception());
#endif
	}
#endif
}

#undef VERIFY

}	// namespace emplace_index_args_test

}	// namespace hamon_variant_test
