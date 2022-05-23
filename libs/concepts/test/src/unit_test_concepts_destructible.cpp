/**
 *	@file	unit_test_concepts_destructible.cpp
 *
 *	@brief	destructible のテスト
 */

#include <hamon/concepts/destructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_DESTRUCTIBLE_TEST(B, T)	\
	static_assert(B == hamon::destructible<T>, "");	\
	static_assert(B == hamon::destructible_t<T>::value, "")
#else
#  define HAMON_DESTRUCTIBLE_TEST(B, T) \
	static_assert(B == hamon::destructible<T>::value, "");	\
	static_assert(B == hamon::destructible_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace destructible_test
{

HAMON_DESTRUCTIBLE_TEST(false, void);
HAMON_DESTRUCTIBLE_TEST(true,  char);
HAMON_DESTRUCTIBLE_TEST(true,  float);
HAMON_DESTRUCTIBLE_TEST(true,  int*);
HAMON_DESTRUCTIBLE_TEST(true,  int&);
HAMON_DESTRUCTIBLE_TEST(true,  int&&);
HAMON_DESTRUCTIBLE_TEST(true,  const int&);
HAMON_DESTRUCTIBLE_TEST(false, int[]);
HAMON_DESTRUCTIBLE_TEST(true,  int[2]);
HAMON_DESTRUCTIBLE_TEST(false, int());
HAMON_DESTRUCTIBLE_TEST(true,  int(*)());
HAMON_DESTRUCTIBLE_TEST(true,  int(&)());

enum E { };
HAMON_DESTRUCTIBLE_TEST(true,  E);
enum class CE { };
HAMON_DESTRUCTIBLE_TEST(true,  CE);
struct A { };
HAMON_DESTRUCTIBLE_TEST(true,  A);
union B { };
HAMON_DESTRUCTIBLE_TEST(true,  B);

struct C
{
	~C() noexcept(false) { }
};
HAMON_DESTRUCTIBLE_TEST(false, C);

class D
{
public:
	D() { }
private:
	~D() { }
};
HAMON_DESTRUCTIBLE_TEST(false, D);

}	// namespace destructible_test

}	// namespace hamon_concepts_test

#undef HAMON_DESTRUCTIBLE_TEST
