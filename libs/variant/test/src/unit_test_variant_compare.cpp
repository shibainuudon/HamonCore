/**
 *	@file	unit_test_variant_comapre.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template <typename... Types>
 *	constexpr bool
 *	operator==(variant<Types...> const&, variant<Types...> const&);
 *	
 *	template <typename... Types>
 *	constexpr bool
 *	operator!=(variant<Types...> const&, variant<Types...> const&);
 *	
 *	template <typename... Types>
 *	constexpr bool
 *	operator<(variant<Types...> const&, variant<Types...> const&);
 *	
 *	template <typename... Types>
 *	constexpr bool
 *	operator>(variant<Types...> const&, variant<Types...> const&);
 *	
 *	template <typename... Types>
 *	constexpr bool
 *	operator<=(variant<Types...> const&, variant<Types...> const&);
 *	
 *	template <typename... Types>
 *	constexpr bool
 *	operator>=(variant<Types...> const&, variant<Types...> const&);
 *	
 *	template <typename... Types>
 *	requires (three_­way_­comparable<Types> && ...)
 *	constexpr common_comparison_category_t<compare_three_way_result_t<Types>...>
 *	operator<=>(variant<Types...> const&, variant<Types...> const&);
 */

#include <hamon/variant.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace compare_test
{

#if !defined(HAMON_NO_EXCEPTIONS)

struct MakeEmptyT
{
	int value;
	MakeEmptyT(int v) : value(v) {}
	MakeEmptyT(MakeEmptyT const&) = default;
	MakeEmptyT(MakeEmptyT &&) : value() { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT const&) { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT &&) { throw 42; }
};

inline bool operator==(MakeEmptyT const&, MakeEmptyT const&)
{
	return false;
}

inline bool operator!=(MakeEmptyT const&, MakeEmptyT const&)
{
	return false;
}

inline bool operator<(MakeEmptyT const&, MakeEmptyT const&)
{
	return false;
}

inline bool operator>(MakeEmptyT const&, MakeEmptyT const&)
{
	return false;
}

inline bool operator<=(MakeEmptyT const&, MakeEmptyT const&)
{
	return false;
}

inline bool operator>=(MakeEmptyT const&, MakeEmptyT const&)
{
	return false;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
inline std::weak_ordering operator<=>(MakeEmptyT const&, MakeEmptyT const&)
{
	return std::weak_ordering::equivalent;
}
#endif

template <typename Variant>
void MakeEmpty(Variant& v)
{
	Variant v2(hamon::in_place_type_t<MakeEmptyT>{}, 0);
	try
	{
		v = hamon::move(v2);
	}
	catch (...)
	{
	}
}

#endif

GTEST_TEST(VariantTest, CompareTest)
{
	// same index, same value
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v1(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v2(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 == v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 != v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 <  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 >= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 == v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 != v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 >  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 <= v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v1 <=> v2) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v2 <=> v1) == 0);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v1(
			hamon::in_place_index_t<1>{}, 42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v2(
			hamon::in_place_index_t<1>{}, 42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 == v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 != v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 <  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 >= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 == v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 != v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 >  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 <= v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v1 <=> v2) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v2 <=> v1) == 0);
#endif
	}

	// same index, different value
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v1(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v2(
			hamon::in_place_index_t<0>{}, 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 == v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 != v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 == v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 != v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <= v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v1 <=> v2) < 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v2 <=> v1) > 0);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v1(
			hamon::in_place_index_t<1>{}, 42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v2(
			hamon::in_place_index_t<1>{}, 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 == v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 != v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 == v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 != v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <= v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v1 <=> v2) < 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v2 <=> v1) > 0);
#endif
	}

	// different index
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v1(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v2(
			hamon::in_place_index_t<1>{}, 42);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 == v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 != v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >  v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v1 <= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v1 >= v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 == v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 != v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >  v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, v2 <= v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v1 <=> v2) < 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((v2 <=> v1) > 0);
#endif
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	// both empty
	{
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 13);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 13);
		MakeEmpty(v1);
		MakeEmpty(v2);
		EXPECT_EQ(true,  v1 == v2);
		EXPECT_EQ(false, v1 != v2);
		EXPECT_EQ(false, v1 <  v2);
		EXPECT_EQ(false, v1 >  v2);
		EXPECT_EQ(true,  v1 <= v2);
		EXPECT_EQ(true,  v1 >= v2);
		EXPECT_EQ(true,  v2 == v1);
		EXPECT_EQ(false, v2 != v1);
		EXPECT_EQ(false, v2 <  v1);
		EXPECT_EQ(false, v2 >  v1);
		EXPECT_EQ(true,  v2 <= v1);
		EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		EXPECT_TRUE((v1 <=> v2) == 0);
		EXPECT_TRUE((v2 <=> v1) == 0);
#endif
	}

	// only one empty
	{
		hamon::variant<int, MakeEmptyT> v1(hamon::in_place_index_t<0>{}, 13);
		hamon::variant<int, MakeEmptyT> v2(hamon::in_place_index_t<0>{}, 13);
		MakeEmpty(v1);
		EXPECT_EQ(false, v1 == v2);
		EXPECT_EQ(true,  v1 != v2);
		EXPECT_EQ(true,  v1 <  v2);
		EXPECT_EQ(false, v1 >  v2);
		EXPECT_EQ(true,  v1 <= v2);
		EXPECT_EQ(false, v1 >= v2);
		EXPECT_EQ(false, v2 == v1);
		EXPECT_EQ(true,  v2 != v1);
		EXPECT_EQ(false, v2 <  v1);
		EXPECT_EQ(true,  v2 >  v1);
		EXPECT_EQ(false, v2 <= v1);
		EXPECT_EQ(true,  v2 >= v1);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		EXPECT_TRUE((v1 <=> v2) < 0);
		EXPECT_TRUE((v2 <=> v1) > 0);
#endif
	}
#endif
}

}	// namespace compare_test

}	// namespace hamon_variant_test
