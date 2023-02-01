/**
 *	@file	unit_test_iterator_concepts_mergeable.cpp
 *
 *	@brief	mergeable のテスト
 */

#include <hamon/iterator/concepts/mergeable.hpp>
#include <hamon/config.hpp>
#include <array>
#include <list>
#include <memory>
#include <vector>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_MERGEABLE_TEST(B, ...)	\
	static_assert(B == hamon::mergeable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::mergeable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_MERGEABLE_TEST(B, ...)	\
	static_assert(B == hamon::mergeable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::mergeable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace mergeable_test
{

HAMON_MERGEABLE_TEST(true,  int*, int*, int*);
HAMON_MERGEABLE_TEST(true,  int const*, int const*, int*);
HAMON_MERGEABLE_TEST(false, int const*, int const*, int const*);
HAMON_MERGEABLE_TEST(false, std::shared_ptr<int>, int*, int*);
HAMON_MERGEABLE_TEST(false, int*, std::unique_ptr<int>, int*);
HAMON_MERGEABLE_TEST(false, int*, int*, std::shared_ptr<int>);
HAMON_MERGEABLE_TEST(true,  std::list<int>::iterator, std::array<int, 2>::iterator, std::vector<int>::iterator);
HAMON_MERGEABLE_TEST(false, std::list<int>::iterator, std::array<int, 2>::iterator, std::vector<int>::const_iterator);
HAMON_MERGEABLE_TEST(true,  std::list<int>::iterator, std::array<int, 2>::iterator, std::list<int>::iterator);
HAMON_MERGEABLE_TEST(false, std::list<int>::iterator, std::array<int, 2>::iterator, std::list<int>::const_iterator);

}	// namespace mergeable_test

}	// namespace hamon_iterator_test

#undef HAMON_MERGEABLE_TEST
