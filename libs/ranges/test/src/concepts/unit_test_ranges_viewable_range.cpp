/**
 *	@file	unit_test_ranges_viewable_range.cpp
 *
 *	@brief	ranges::viewable_range のテスト
 */

#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/vector.hpp>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_VIEWABLE_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::viewable_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::viewable_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_VIEWABLE_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::viewable_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::viewable_range_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_ranges_test
{

namespace viewable_range_test
{

// viewable_range<T> is not satisfied for (range=false, view=*, constructible_from=*, lvalue-or-movable=*)
struct T1 { };
static_assert(!hamon::ranges::range_t<T1>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T1);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T1&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T1&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T1 const);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T1 const&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T1 const&&);

// viewable_range<T> is satisfied for (range=true, view=true, constructible_from=true, lvalue-or-movable=true)
struct T2 : test_input_range<int>, hamon::ranges::view_base
{
	T2(T2 const&) = default;
};
static_assert(hamon::ranges::range_t<T2>::value, "");
static_assert(hamon::ranges::view_t<T2>::value, "");
static_assert(hamon::constructible_from_t<T2, T2>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T2);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T2&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T2&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T2 const);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T2 const&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T2 const&&);

// viewable_range<T> is satisfied for (range=true, view=true, constructible_from=true, lvalue-or-movable=false)
struct T3 : test_input_range<int>, hamon::ranges::view_base
{
	T3(T3 const&) = default;
};
static_assert(hamon::ranges::range_t<T3>::value, "");
static_assert(hamon::ranges::view_t<T3>::value, "");
static_assert(hamon::constructible_from_t<T3, T3>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T3);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T3&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T3&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T3 const);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T3 const&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true, T3 const&&);

// viewable_range<T> is not satisfied for (range=true, view=true, constructible_from=false, lvalue-or-movable=true)
struct T4 : test_input_range<int>, hamon::ranges::view_base
{
	T4(T4 const&) = delete;
	T4(T4&&) = default;             // necessary to model view
	T4& operator=(T4&&) = default;  // necessary to model view
};
static_assert(hamon::ranges::range_t<T4 const&>::value, "");
static_assert(hamon::ranges::view_t<hamon::remove_cvref_t<T4 const&>>::value, "");
static_assert(!hamon::constructible_from_t<hamon::remove_cvref_t<T4 const&>, T4 const&>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T4 const&);

// A type that satisfies (range=true, view=true, constructible_from=false, lvalue-or-movable=false) can't be formed,
// because views are movable by definition

// viewable_range<T> is satisfied for (range=true, view=false, constructible_from=true, lvalue-or-movable=true)...
struct T5 : test_input_range<int> { };
static_assert( hamon::ranges::range_t<T5>::value, "");
static_assert(!hamon::ranges::view_t<T5>::value, "");
static_assert( hamon::constructible_from_t<T5, T5>::value, "");
static_assert( hamon::movable_t<T5>::value, "");
static_assert(!hamon::movable_t<const T5>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  T5); // movable
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  T5&); // movable
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  T5&&); // movable
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T5);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  const T5&); // lvalue
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T5&&);

// ...but not if the (non-view, lvalue-or-movable) range is an initializer_list.
static_assert( hamon::ranges::range_t<std::initializer_list<int>>::value, "");
static_assert(!hamon::ranges::view_t<std::initializer_list<int>>::value, "");
static_assert( hamon::constructible_from_t<std::initializer_list<int>, std::initializer_list<int>>::value, "");
static_assert( hamon::movable_t<std::initializer_list<int>>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, std::initializer_list<int>);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  std::initializer_list<int>&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, std::initializer_list<int>&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, std::initializer_list<int> const);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  std::initializer_list<int> const&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, std::initializer_list<int> const&&);

// viewable_range<T> is not satisfied for (range=true, view=false, constructible_from=true, lvalue-or-movable=false)
struct T6 : test_input_range<int> { T6(T6&&); T6& operator=(T6&&) = delete; };
static_assert( hamon::ranges::range_t<T6>::value, "");
static_assert(!hamon::ranges::view_t<T6>::value, "");
static_assert( hamon::constructible_from_t<T6, T6>::value, "");
static_assert(!hamon::movable_t<T6>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T6);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  T6&); // lvalue
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T6&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T6);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  const T6&); // lvalue
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T6&&);

// viewable_range<T> is satisfied for (range=true, view=false, constructible_from=false, lvalue-or-movable=true)
struct T7 : test_input_range<int>
{
	T7(T7 const&) = delete;
};
static_assert(hamon::ranges::range_t<T7&>::value, "");
static_assert(!hamon::ranges::view_t<hamon::remove_cvref_t<T7&>>::value, "");
static_assert(!hamon::constructible_from_t<hamon::remove_cvref_t<T7&>, T7&>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T7);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  T7&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T7&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T7);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  const T7&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T7&&);

// viewable_range<T> is not satisfied for (range=true, view=false, constructible_from=false, lvalue-or-movable=false)
struct T8 : test_input_range<int>
{
	T8(T8 const&) = delete;
};
static_assert(hamon::ranges::range_t<T8>::value, "");
static_assert(!hamon::ranges::view_t<T8>::value, "");
static_assert(!hamon::constructible_from_t<T8, T8>::value, "");

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T8);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  T8&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, T8&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T8);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  const T8&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, const T8&&);

// Test with a few degenerate types
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, void);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int (*)(char));
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int[]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int[10]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int(&)[]); // not a range
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  int(&)[10]); // OK, lvalue
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int(&&)[]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, int(&&)[10]);

// TODO
#if 0//defined(HAMON_HAS_CXX20_CONCEPTS)
// Test ADL-proofing.
struct Incomplete;
template<class T> struct Holder { T t; };

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>*);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>*&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>*&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>* const);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>* const&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>* const&&);

HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>*[10]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  Holder<Incomplete>*(&)[10]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>*(&&)[10]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>* const[10]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  Holder<Incomplete>* const(&)[10]);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, Holder<Incomplete>* const(&&)[10]);
#endif

// Verify P2415R2 "What is a view?" changes.
// In particular, rvalue non-view non-borrowed ranges are now viewable.
HAMON_RANGES_VIEWABLE_RANGE_TEST(true,  hamon::vector<int>&&);
HAMON_RANGES_VIEWABLE_RANGE_TEST(false, hamon::vector<int> const&&);

}	// namespace viewable_range_test

}	// namespace hamon_ranges_test

#undef HAMON_RANGES_VIEWABLE_RANGE_TEST
