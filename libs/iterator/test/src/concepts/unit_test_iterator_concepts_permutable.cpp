/**
 *	@file	unit_test_iterator_concepts_permutable.cpp
 *
 *	@brief	permutable のテスト
 */

#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
//#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <iterator>
#include <memory>
#include <string>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_PERMUTABLE_TEST(B, ...)	\
	static_assert(B == hamon::permutable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::permutable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_PERMUTABLE_TEST(B, ...)	\
	static_assert(B == hamon::permutable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::permutable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace permutable_test
{

HAMON_PERMUTABLE_TEST(true,  int      *);
HAMON_PERMUTABLE_TEST(false, int const*);
HAMON_PERMUTABLE_TEST(false, int      * const);
HAMON_PERMUTABLE_TEST(false, int const* const);
HAMON_PERMUTABLE_TEST(false, void*);
HAMON_PERMUTABLE_TEST(false, void* const);

HAMON_PERMUTABLE_TEST(true,  hamon::array<int, 1>::iterator);
HAMON_PERMUTABLE_TEST(false, hamon::array<int, 1>::const_iterator);
HAMON_PERMUTABLE_TEST(true,  hamon::deque<int>::iterator);
HAMON_PERMUTABLE_TEST(false, hamon::deque<int>::const_iterator);
HAMON_PERMUTABLE_TEST(true,  hamon::forward_list<int>::iterator);
HAMON_PERMUTABLE_TEST(false, hamon::forward_list<int>::const_iterator);
HAMON_PERMUTABLE_TEST(true,  hamon::list<int>::iterator);
HAMON_PERMUTABLE_TEST(false, hamon::list<int>::const_iterator);
HAMON_PERMUTABLE_TEST(true,  std::string::iterator);
HAMON_PERMUTABLE_TEST(false, std::string::const_iterator);
//HAMON_PERMUTABLE_TEST(false, hamon::string_view::iterator);
//HAMON_PERMUTABLE_TEST(false, hamon::string_view::const_iterator);
HAMON_PERMUTABLE_TEST(true,  hamon::vector<int>::iterator);
HAMON_PERMUTABLE_TEST(false, hamon::vector<int>::const_iterator);
HAMON_PERMUTABLE_TEST(false, std::istreambuf_iterator<char>);
HAMON_PERMUTABLE_TEST(false, std::ostreambuf_iterator<char>);
HAMON_PERMUTABLE_TEST(false, std::shared_ptr<int>);
HAMON_PERMUTABLE_TEST(false, std::unique_ptr<int>);

}	// namespace permutable_test

}	// namespace hamon_iterator_test

#undef HAMON_PERMUTABLE_TEST
