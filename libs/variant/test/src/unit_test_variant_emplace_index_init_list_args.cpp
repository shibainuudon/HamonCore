/**
 *	@file	unit_test_variant_emplace_index_init_list_args.cpp
 *
 *	@brief	インデックスを指定してinitializer_listを第1引数に取るemplaceのテスト
 * 
 *	template <size_t I, typename U, typename... Args>
 *	constexpr variant_alternative_t<I, variant<Types...>>&
 *	emplace(initializer_list<U>, Args&&...);
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

namespace emplace_index_init_list_args_test
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

inline HAMON_CXX20_CONSTEXPR bool EmplaceIndexInitListArgsTest()
{
	{
		hamon::variant<int, X, Y> v;
		VERIFY(v.index() == 0u);
		VERIFY(hamon::adl_get<0>(v) == 0);
		auto& ref1 = v.emplace<1>({1,2,3});
		VERIFY(v.index() == 1u);
		VERIFY(hamon::adl_get<1>(v).m_size == 3u);
		VERIFY(&ref1 == &hamon::adl_get<1>(v));
		auto& ref2 = v.emplace<2>({1,2,3,4},42);
		VERIFY(v.index() == 2u);
		VERIFY(hamon::adl_get<2>(v).m_size == 4u);
		VERIFY(hamon::adl_get<2>(v).m_value == 42);
		VERIFY(&ref2 == &hamon::adl_get<2>(v));
	}

	return true;
}

GTEST_TEST(VariantTest, EmplaceIndexInitListArgsTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION) && !defined(HAMON_APPLE_CLANG)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(EmplaceIndexInitListArgsTest());
#else
	EXPECT_TRUE(EmplaceIndexInitListArgsTest());
#endif

	{
		using V = hamon::variant<int>;
		static_assert(!is_detected_emplace<V, 0, std::initializer_list<int>>::value, "");
		static_assert(!is_detected_emplace<V, 0, std::initializer_list<int>, int>::value, "");
	}
	{
		using V = hamon::variant<int, X, Y>;
		static_assert(!is_detected_emplace<V, 0, std::initializer_list<int>>::value, "");
		static_assert(!is_detected_emplace<V, 0, std::initializer_list<int>, int>::value, "");
		static_assert(!is_detected_emplace<V, 1, int>::value, "");
		static_assert( is_detected_emplace<V, 1, std::initializer_list<int>>::value, "");
		static_assert(!is_detected_emplace<V, 1, std::initializer_list<char>>::value, "");
		static_assert(!is_detected_emplace<V, 1, std::initializer_list<int>, int>::value, "");
		static_assert(!is_detected_emplace<V, 2, std::initializer_list<int>>::value, "");
		static_assert(!is_detected_emplace<V, 2, int>::value, "");
		static_assert( is_detected_emplace<V, 2, std::initializer_list<int>, int>::value, "");
		static_assert(!is_detected_emplace<V, 2, std::initializer_list<char>, int>::value, "");
		static_assert(!is_detected_emplace<V, 2, std::initializer_list<int>, int, int>::value, "");
		static_assert(!is_detected_emplace<V, 3, int>::value, "");
		static_assert(!is_detected_emplace<V, 3, std::initializer_list<int>>::value, "");
		static_assert(!is_detected_emplace<V, 3, std::initializer_list<int>, int>::value, "");
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		struct S { operator int() { throw 42; } };
		hamon::variant<float, Y> v{12.f};
		EXPECT_THROW(v.emplace<1>({1,2,3}, S()), int);
#if !defined(HAMON_USE_STD_VARIANT)
		EXPECT_TRUE(v.valueless_by_exception());
#endif
	}
#endif
}

#undef VERIFY

}	// namespace emplace_index_init_list_args_test

}	// namespace hamon_variant_test
