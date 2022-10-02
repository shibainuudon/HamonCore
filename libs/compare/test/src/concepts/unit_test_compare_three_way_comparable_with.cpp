/**
 *	@file	unit_test_compare_three_way_comparable_with.cpp
 *
 *	@brief	three_way_comparable_with のテスト
 */

#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/config.hpp>
#include <cstddef>

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace hamon_compare_test
{

namespace three_way_comparable_with_test
{

#if !defined(_MSC_VER)
static_assert(hamon::three_way_comparable_with<int, int>, "");
static_assert(hamon::three_way_comparable_with<int, char>, "");
static_assert(hamon::three_way_comparable_with<int, float>, "");
static_assert(hamon::three_way_comparable_with<char, int>, "");
static_assert(hamon::three_way_comparable_with<char, char>, "");
static_assert(hamon::three_way_comparable_with<char, float>, "");
static_assert(hamon::three_way_comparable_with<float, int>, "");
static_assert(hamon::three_way_comparable_with<float, char>, "");
static_assert(hamon::three_way_comparable_with<float, float>, "");
#endif

struct B
{
	friend auto operator<=>(const B&, const B&) = default;
};

struct S1 : B
{
	std::size_t s;

	friend auto operator<=>(const S1&, const S1&) = default;
};

struct S2 : B
{
	std::size_t s;

	friend auto operator<=>(const S2&, const S2&) = default;
	friend bool operator== (const S2&, const S2&) = default;

	friend auto operator<=>(const S1& a, const S2& b) { return a.s <=> b.s; }
	friend bool operator== (const S1& a, const S2& b) { return a.s ==  b.s; }
};

}	// namespace three_way_comparable_with_test

}	// namespace hamon_compare_test

namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE
{

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	hamon_compare_test::three_way_comparable_with_test::S1,
	hamon_compare_test::three_way_comparable_with_test::S2,
	Qual1, Qual2>
{
	using type = const hamon_compare_test::three_way_comparable_with_test::B&;
};

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	hamon_compare_test::three_way_comparable_with_test::S2,
	hamon_compare_test::three_way_comparable_with_test::S1,
	Qual1, Qual2>
{
	using type = const hamon_compare_test::three_way_comparable_with_test::B&;
};

}	// namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE

namespace hamon_compare_test
{

namespace three_way_comparable_with_test
{

static_assert( hamon::three_way_comparable_with<S1, S1>, "");
//static_assert( hamon::three_way_comparable_with<S1, S2>, "");	// TODO:	MSVCでエラー
static_assert( hamon::three_way_comparable_with<S1, B>, "");
//static_assert( hamon::three_way_comparable_with<S2, S1>, "");	// TODO:	MSVCでエラー
static_assert( hamon::three_way_comparable_with<S2, S2>, "");
static_assert( hamon::three_way_comparable_with<S2, B>, "");
static_assert( hamon::three_way_comparable_with<B, S1>, "");
static_assert( hamon::three_way_comparable_with<B, S2>, "");
static_assert( hamon::three_way_comparable_with<B, B>, "");
static_assert(!hamon::three_way_comparable_with<S1, int>, "");
static_assert(!hamon::three_way_comparable_with<S2, int>, "");
static_assert(!hamon::three_way_comparable_with<int, S1>, "");
static_assert(!hamon::three_way_comparable_with<int, S2>, "");

}	// namespace three_way_comparable_with_test

}	// namespace hamon_compare_test

#endif
