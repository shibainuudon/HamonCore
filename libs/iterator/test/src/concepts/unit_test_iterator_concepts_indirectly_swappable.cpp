/**
 *	@file	unit_test_iterator_concepts_indirectly_swappable.cpp
 *
 *	@brief	indirectly_swappable のテスト
 */

#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/config.hpp>
#include <memory>
#include <vector>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECTLY_SWAPPABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_swappable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirectly_swappable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECTLY_SWAPPABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_swappable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirectly_swappable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirectly_swappable_test
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

HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  int      *, int*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int const*, int*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int      *, int const*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int const*, int const*);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  int*, float*);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  int*, char*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int*, int);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int*, int&);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int*, int&&);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int*, int[]);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int*, int[2]);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, int*, void*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  int*, std::unique_ptr<int>);
HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  int*, std::shared_ptr<int>);
HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  std::vector<int>::iterator,       int*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  std::vector<int>::iterator,       std::vector<int>::iterator);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::iterator,       std::vector<int>::const_iterator);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::const_iterator, int*);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::const_iterator, std::vector<int>::iterator);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::const_iterator, std::vector<int>::const_iterator);
HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  CopyableMovable<true,  true >*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  true >*);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(true,  CopyableMovable<false, true >*, CopyableMovable<false, true >*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<false, false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  true >*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  false>*);
HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, true >*);
//HAMON_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, false>*);

}	// namespace indirectly_swappable_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECTLY_SWAPPABLE_TEST
