/**
 *	@file	unit_test_concepts_move_constructible.cpp
 *
 *	@brief	move_constructible のテスト
 */

#include <hamon/concepts/move_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_MOVE_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == hamon::move_constructible<T>, "");	\
	static_assert(B == hamon::move_constructible_t<T>::value, "")
#else
#  define HAMON_MOVE_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == hamon::move_constructible<T>::value, "");	\
	static_assert(B == hamon::move_constructible_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace move_constructible_test
{

HAMON_MOVE_CONSTRUCTIBLE_TEST(false, void);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  void*);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  const void*);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  char);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  const float);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  int&);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  int&&);
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  const int&);
HAMON_MOVE_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_MOVE_CONSTRUCTIBLE_TEST(false, int[2]);
HAMON_MOVE_CONSTRUCTIBLE_TEST(false, int());
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  int(*)());
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)());
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)() noexcept);

enum E { };
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  E);
enum class CE { };
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  CE);
struct A { };
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  A);
union B { };
HAMON_MOVE_CONSTRUCTIBLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
HAMON_MOVE_CONSTRUCTIBLE_TEST(false, C);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
HAMON_MOVE_CONSTRUCTIBLE_TEST(false, D);

}	// namespace move_constructible_test

}	// namespace hamon_concepts_test

#undef HAMON_MOVE_CONSTRUCTIBLE_TEST
