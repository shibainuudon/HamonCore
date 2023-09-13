﻿/**
 *	@file	unit_test_iterator_concepts_indirectly_movable.cpp
 *
 *	@brief	indirectly_movable のテスト
 */

#include <hamon/iterator/concepts/indirectly_movable.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECTLY_MOVABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_movable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirectly_movable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECTLY_MOVABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_movable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirectly_movable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirectly_movable_test
{

template <bool, bool>
struct CopyableMovable;

template <>
struct CopyableMovable<true, true>
{
	CopyableMovable(CopyableMovable const&);
	CopyableMovable& operator=(CopyableMovable const&);
	CopyableMovable(CopyableMovable&&);
	CopyableMovable& operator=(CopyableMovable&&);
};
template <>
struct CopyableMovable<true, false>
{
	CopyableMovable(CopyableMovable const&);
	CopyableMovable& operator=(CopyableMovable const&);
	CopyableMovable(CopyableMovable&&) = delete;
	CopyableMovable& operator=(CopyableMovable&&) = delete;
};
template <>
struct CopyableMovable<false, true>
{
	CopyableMovable(CopyableMovable const&) = delete;
	CopyableMovable& operator=(CopyableMovable const&) = delete;
	CopyableMovable(CopyableMovable&&);
	CopyableMovable& operator=(CopyableMovable&&);
};
template <>
struct CopyableMovable<false, false>
{
	CopyableMovable(CopyableMovable const&) = delete;
	CopyableMovable& operator=(CopyableMovable const&) = delete;
	CopyableMovable(CopyableMovable&&) = delete;
	CopyableMovable& operator=(CopyableMovable&&) = delete;
};

struct A1
{
	A1(A1&&);
	A1& operator=(A1&&);
};
struct A2
{
	A2(A2&&) = delete;
	A2& operator=(A2&&) = delete;
};
struct B1
{
	B1(A1 const&);
	B1(A2 const&);
};
struct B2
{
	B2& operator=(A1 const&);
	B2& operator=(A2 const&);
};
struct C1
{
	C1(A1&&);
	C1(A2&&);
};
struct C2
{
	C2& operator=(A1&&);
	C2& operator=(A2&&);
};

HAMON_INDIRECTLY_MOVABLE_TEST(true,  int      *, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  int const*, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, int      *, int const*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, int const*, int const*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  int*, float*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  int*, char*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, int*, void*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  float*, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  char*, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, void*, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  int*, hamon::vector<int>::iterator);
HAMON_INDIRECTLY_MOVABLE_TEST(false, int*, hamon::vector<int>::const_iterator);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  hamon::vector<int>::iterator, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  hamon::vector<int>::iterator, hamon::vector<int>::iterator);
HAMON_INDIRECTLY_MOVABLE_TEST(false, hamon::vector<int>::iterator, hamon::vector<int>::const_iterator);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  hamon::vector<int>::const_iterator, int*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  hamon::vector<int>::const_iterator, hamon::vector<int>::iterator);
HAMON_INDIRECTLY_MOVABLE_TEST(false, hamon::vector<int>::const_iterator, hamon::vector<int>::const_iterator);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  CopyableMovable<true,  true >*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  CopyableMovable<false, true >*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A1*, B1*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A2*, B1*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A1*, B2*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A2*, B2*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A1*, C1*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A2*, C1*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A1*, C2*);
HAMON_INDIRECTLY_MOVABLE_TEST(true,  A2*, C2*);

}	// namespace indirectly_movable_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECTLY_MOVABLE_TEST
