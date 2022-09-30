/**
 *	@file	unit_test_concepts_equivalence_relation.cpp
 *
 *	@brief	equivalence_relation のテスト
 */

#include <hamon/concepts/equivalence_relation.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == hamon::equivalence_relation<__VA_ARGS__>, "");	\
	static_assert(B == hamon::equivalence_relation_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == hamon::equivalence_relation<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::equivalence_relation_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace equivalence_relation_test
{

struct F
{
	void operator()(long, long) const;
	bool& operator()(int, const int&) const;
};

HAMON_EQUIVALENCE_RELATION_TEST(true,  bool(*)(int, int), short, long);
HAMON_EQUIVALENCE_RELATION_TEST(false, F, long, long);
HAMON_EQUIVALENCE_RELATION_TEST(true,  const F&, const int, const int);

}	// namespace equivalence_relation_test

}	// namespace hamon_concepts_test

#undef HAMON_EQUIVALENCE_RELATION_TEST
