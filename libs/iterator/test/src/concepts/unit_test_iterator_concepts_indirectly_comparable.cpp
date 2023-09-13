/**
 *	@file	unit_test_iterator_concepts_indirectly_comparable.cpp
 *
 *	@brief	indirectly_comparable のテスト
 */

#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECTLY_COMPARABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_comparable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirectly_comparable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECTLY_COMPARABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_comparable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirectly_comparable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirectly_comparable_test
{

struct Pred1
{
	bool operator()(int, int) const;
};
struct Pred2
{
	bool operator()(int) const;
	void operator()(int, int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int, int) const;
};

HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int      *, int      *,                 bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int const*, int      *,                 bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int      *, int const*,                 bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int const*, int const*,                 bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, float*,                           bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, char*,                            bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, void*,                            bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int**,                            bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int,                              bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int&,                             bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int&&,                            bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int[],                            bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int[2],                           bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, std::unique_ptr<int>,             bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, std::shared_ptr<int>,             bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, hamon::vector<int>::iterator,       bool(*)(int, int));
HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, hamon::vector<int>::const_iterator, bool(*)(int, int));

HAMON_INDIRECTLY_COMPARABLE_TEST(true,  int*, int*, Pred1);
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int*, Pred2);
HAMON_INDIRECTLY_COMPARABLE_TEST(false, int*, int*, Pred3);

}	// namespace indirectly_comparable_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECTLY_COMPARABLE_TEST
