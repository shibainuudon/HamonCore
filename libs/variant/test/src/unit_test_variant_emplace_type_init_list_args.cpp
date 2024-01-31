/**
 *	@file	unit_test_variant_emplace_type_init_list_args.cpp
 *
 *	@brief	型を指定してinitializer_listを第1引数に取るemplaceのテスト
 * 
 *	template <typename T, typename U, typename... Args>
 *	constexpr T& emplace(initializer_list<U>, Args&&...);
 */

#include <hamon/variant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace emplace_type_init_list_args_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Variant, typename T, typename... Args>
using invoke_emplace =
	decltype(hamon::declval<Variant>().template emplace<T>(hamon::declval<Args>()...));

struct X
{
	hamon::size_t m_size;
	HAMON_CXX14_CONSTEXPR X(std::initializer_list<int> il)
		: m_size(il.size()) {}
};

struct Y
{
	hamon::size_t m_size;
	int           m_value;
	HAMON_CXX14_CONSTEXPR Y(std::initializer_list<int> il, int v)
		: m_size(il.size()), m_value(v) {}
};

inline HAMON_CXX20_CONSTEXPR bool EmplaceTypeInitListArgsTest()
{
	{
		hamon::variant<int, X, Y> v;
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		auto& ref1 = v.emplace<X>({1,2,3});
		VERIFY(v.index() == 1u);
		VERIFY(hamon::adl_get<1>(v).m_size == 3u);
		VERIFY(&ref1 == &hamon::adl_get<1>(v));
		auto& ref2 = v.emplace<Y>({1,2,3,4},42);
		VERIFY(v.index() == 2u);
		VERIFY(hamon::adl_get<2>(v).m_size == 4u);
		VERIFY(hamon::adl_get<2>(v).m_value == 42);
		VERIFY(&ref2 == &hamon::adl_get<2>(v));
	}

	return true;
}

GTEST_TEST(VariantTest, EmplaceTypeInitListArgsTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EmplaceTypeInitListArgsTest());
#else
	EXPECT_TRUE(EmplaceTypeInitListArgsTest());
#endif

	{
		using V = hamon::variant<int>;
		static_assert(!hamon::is_detected<invoke_emplace, V, int, std::initializer_list<int>>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, int, std::initializer_list<int>, int>::value, "");
	}
	{
		using V = hamon::variant<int, X, Y>;
		static_assert(!hamon::is_detected<invoke_emplace, V, int, std::initializer_list<int>>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, int, std::initializer_list<int>, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, X, int>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, X, std::initializer_list<int>>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, X, std::initializer_list<char>>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, X, std::initializer_list<int>, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, Y, std::initializer_list<int>>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, Y, int>::value, "");
		static_assert( hamon::is_detected<invoke_emplace, V, Y, std::initializer_list<int>, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, Y, std::initializer_list<char>, int>::value, "");
		static_assert(!hamon::is_detected<invoke_emplace, V, Y, std::initializer_list<int>, int, int>::value, "");
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		struct S { operator int() { throw 42; } };
		hamon::variant<float, Y> v{12.f};
		EXPECT_THROW(v.emplace<Y>({1,2,3}, S()), int);
#if !defined(HAMON_USE_STD_VARIANT)
		EXPECT_TRUE(v.valueless_by_exception());
#endif
	}
#endif
}

#undef VERIFY

}	// namespace emplace_type_init_list_args_test

}	// namespace hamon_variant_test
