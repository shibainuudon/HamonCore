/**
 *	@file	unit_test_concepts_cpp17_destructible.cpp
 *
 *	@brief	cpp17_destructible のテスト
 */

#include <hamon/concepts/detail/cpp17_destructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_DESTRUCTIBLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_destructible<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_destructible_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_DESTRUCTIBLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_destructible<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_destructible_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_destructible_test
{

HAMON_CPP17_DESTRUCTIBLE_TEST(false, void);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  void*);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  char);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  float);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  int);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  int const);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  int volatile);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  int const volatile);
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  int*);
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int&);			// different from `destructible`
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int&&);		// different from `destructible`
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int const&);	// different from `destructible`
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int[]);
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int[2]);		// different from `destructible`
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int());
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  int(*)());
HAMON_CPP17_DESTRUCTIBLE_TEST(false, int(&)());		// different from `destructible`

enum E { };
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  E);
enum class CE { };
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  CE);
struct A { };
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  A);
union B { };
HAMON_CPP17_DESTRUCTIBLE_TEST(true,  B);

struct C
{
	~C() noexcept(false) { }
};
HAMON_CPP17_DESTRUCTIBLE_TEST(true, C);				// different from `destructible`

class D
{
public:
	D() { }
private:
	~D() { }
};
HAMON_CPP17_DESTRUCTIBLE_TEST(false, D);

}	// namespace cpp17_destructible_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_DESTRUCTIBLE_TEST
