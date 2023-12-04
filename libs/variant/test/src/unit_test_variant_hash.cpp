/**
 *	@file	unit_test_variant_hash.cpp
 *
 *	@brief	hashのテスト
 */

#include <hamon/variant.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>

namespace hamon_variant_test
{

namespace hash_test
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

}	// namespace hash_test
}	// namespace hamon_variant_test

#include <functional>

namespace std
{

template <>
struct hash<hamon_variant_test::hash_test::MakeEmptyT>
{
	hamon::size_t operator()(hamon_variant_test::hash_test::MakeEmptyT const&) const
	{
		return 0;
	}
};

}	// namespace std

namespace hamon_variant_test
{
namespace hash_test
{

#endif

GTEST_TEST(VariantTest, HashTest)
{
	{
		using V = hamon::variant<int>;
		V const v1(13);
		V const v2(13);
		V const v3(14);
		EXPECT_EQ(std::hash<V>{}(v1), std::hash<V>{}(v2));
		EXPECT_NE(std::hash<V>{}(v1), std::hash<V>{}(v3));
		EXPECT_NE(std::hash<V>{}(v2), std::hash<V>{}(v3));
	}
	{
		using V = hamon::variant<float>;
		V const v1(2.5f);
		V const v2(3.5f);
		V const v3(3.5f);
		EXPECT_NE(std::hash<V>{}(v1), std::hash<V>{}(v2));
		EXPECT_NE(std::hash<V>{}(v1), std::hash<V>{}(v3));
		EXPECT_EQ(std::hash<V>{}(v2), std::hash<V>{}(v3));
	}
#if !defined(HAMON_USE_STD_VARIANT)
	{
		using V = hamon::variant<int, int, int>;
		V const v1(hamon::in_place_index_t<0>{}, 42);
		V const v2(hamon::in_place_index_t<0>{}, 42);
		V const v3(hamon::in_place_index_t<1>{}, 42);
		V const v4(hamon::in_place_index_t<2>{}, 42);
		EXPECT_EQ(std::hash<V>{}(v1), std::hash<V>{}(v2));
		EXPECT_NE(std::hash<V>{}(v1), std::hash<V>{}(v3));
		EXPECT_NE(std::hash<V>{}(v1), std::hash<V>{}(v4));
		EXPECT_NE(std::hash<V>{}(v3), std::hash<V>{}(v4));
	}
#endif
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using V = hamon::variant<int, MakeEmptyT>;
		V v1(hamon::in_place_index_t<0>{}, 42);
		V v2(hamon::in_place_index_t<0>{}, 43);
		V v3(hamon::in_place_index_t<0>{}, 43);
		MakeEmpty(v1);
		MakeEmpty(v2);
		EXPECT_TRUE( v1.valueless_by_exception());
		EXPECT_TRUE( v2.valueless_by_exception());
		EXPECT_TRUE(!v3.valueless_by_exception());

		EXPECT_EQ(std::hash<V>{}(v1), std::hash<V>{}(v2));
		EXPECT_NE(std::hash<V>{}(v1), std::hash<V>{}(v3));
		EXPECT_NE(std::hash<V>{}(v2), std::hash<V>{}(v3));
	}
#endif
}

}	// namespace hash_test

}	// namespace hamon_variant_test
