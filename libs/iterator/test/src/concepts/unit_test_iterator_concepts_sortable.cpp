﻿/**
 *	@file	unit_test_iterator_concepts_sortable.cpp
 *
 *	@brief	sortable のテスト
 */

#include <hamon/iterator/concepts/sortable.hpp>
//#include <hamon/string_view.hpp>
#include <hamon/array.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <deque>
#include <iterator>
#include <memory>
#include <string>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SORTABLE_TEST(B, ...)	\
	static_assert(B == hamon::sortable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::sortable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_SORTABLE_TEST(B, ...)	\
	static_assert(B == hamon::sortable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::sortable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace sortable_test
{

HAMON_SORTABLE_TEST(true,  int               *);
HAMON_SORTABLE_TEST(false, int const         *);
//HAMON_SORTABLE_TEST(true,  int       volatile*);
HAMON_SORTABLE_TEST(false, int const volatile*);
HAMON_SORTABLE_TEST(false, int               * const);
HAMON_SORTABLE_TEST(false, int const         * const);
HAMON_SORTABLE_TEST(false, int       volatile* const);
HAMON_SORTABLE_TEST(false, int const volatile* const);

HAMON_SORTABLE_TEST(true,  int               **);
HAMON_SORTABLE_TEST(true,  int const         **);
HAMON_SORTABLE_TEST(true,  int       volatile**);
HAMON_SORTABLE_TEST(true,  int const volatile**);
HAMON_SORTABLE_TEST(false, int               ** const);
HAMON_SORTABLE_TEST(false, int const         ** const);
HAMON_SORTABLE_TEST(false, int       volatile** const);
HAMON_SORTABLE_TEST(false, int const volatile** const);

HAMON_SORTABLE_TEST(false, void               *);
HAMON_SORTABLE_TEST(false, void const         *);
HAMON_SORTABLE_TEST(false, void       volatile*);
HAMON_SORTABLE_TEST(false, void const volatile*);
HAMON_SORTABLE_TEST(false, void               * const);
HAMON_SORTABLE_TEST(false, void const         * const);
HAMON_SORTABLE_TEST(false, void       volatile* const);
HAMON_SORTABLE_TEST(false, void const volatile* const);

HAMON_SORTABLE_TEST(true,  void               **);
HAMON_SORTABLE_TEST(true,  void const         **);
HAMON_SORTABLE_TEST(true,  void       volatile**);
HAMON_SORTABLE_TEST(true,  void const volatile**);
HAMON_SORTABLE_TEST(false, void               ** const);
HAMON_SORTABLE_TEST(false, void const         ** const);
HAMON_SORTABLE_TEST(false, void       volatile** const);
HAMON_SORTABLE_TEST(false, void const volatile** const);

HAMON_SORTABLE_TEST(true,  hamon::array<int, 1>::iterator);
HAMON_SORTABLE_TEST(false, hamon::array<int, 1>::const_iterator);
HAMON_SORTABLE_TEST(true,  std::deque<int>::iterator);
HAMON_SORTABLE_TEST(false, std::deque<int>::const_iterator);
HAMON_SORTABLE_TEST(true,  hamon::forward_list<int>::iterator);
HAMON_SORTABLE_TEST(false, hamon::forward_list<int>::const_iterator);
HAMON_SORTABLE_TEST(true,  hamon::list<int>::iterator);
HAMON_SORTABLE_TEST(false, hamon::list<int>::const_iterator);
HAMON_SORTABLE_TEST(true,  std::string::iterator);
HAMON_SORTABLE_TEST(false, std::string::const_iterator);
//HAMON_SORTABLE_TEST(false, hamon::string_view::iterator);
//HAMON_SORTABLE_TEST(false, hamon::string_view::const_iterator);
HAMON_SORTABLE_TEST(true,  hamon::vector<int>::iterator);
HAMON_SORTABLE_TEST(false, hamon::vector<int>::const_iterator);
HAMON_SORTABLE_TEST(false, std::istreambuf_iterator<char>);
HAMON_SORTABLE_TEST(false, std::ostreambuf_iterator<char>);
HAMON_SORTABLE_TEST(false, std::shared_ptr<int>);
HAMON_SORTABLE_TEST(false, std::unique_ptr<int>);

}	// namespace sortable_test

}	// namespace hamon_iterator_test

#undef HAMON_SORTABLE_TEST
