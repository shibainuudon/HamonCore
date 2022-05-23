/**
 *	@file	unit_test_concepts_constructible_from.cpp
 *
 *	@brief	constructible_from のテスト
 */

#include <hamon/concepts/constructible_from.hpp>
#include <hamon/config.hpp>
#include <cstddef>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CONSTRUCTIBLE_FROM_TEST(B, ...)	\
	static_assert(B == hamon::constructible_from<__VA_ARGS__>, "");	\
	static_assert(B == hamon::constructible_from_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CONSTRUCTIBLE_FROM_TEST(B, ...)	\
	static_assert(B == hamon::constructible_from<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::constructible_from_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace constructible_from_test
{

HAMON_CONSTRUCTIBLE_FROM_TEST(false, void);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, void, void);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  void*, int*);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, void*, const int*);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  const void*, const int*);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  char);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  float);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  float, float);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  float, double);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int*);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int*, int*);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, int&);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int&, int&);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, int&&);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int&&, int);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, const int&);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  const int&, int);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  const int&, int&);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  const int&, const int);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  const int&, const int&);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, const int&, int, int);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, int[]);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int[2]);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, int());
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(*)());
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), std::nullptr_t);
#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), int(*)() noexcept);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), int(&)() noexcept);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(&)(), int(&)() noexcept);
#else
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), int(*)());
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), int(&)());
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  int(&)(), int(&)());
#endif
HAMON_CONSTRUCTIBLE_FROM_TEST(false, int(&)());

enum E { };
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  E);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  E, E&);
enum class CE { };
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  CE);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  CE, CE&);
struct A { };
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  A);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  A, A);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  A, A&);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  A, const A&);
union B { };
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  B);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  B, B);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  B, B&);
HAMON_CONSTRUCTIBLE_FROM_TEST(true,  B, const B&);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
HAMON_CONSTRUCTIBLE_FROM_TEST(false, C);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, C, void*);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, C, std::nullptr_t);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
HAMON_CONSTRUCTIBLE_FROM_TEST(false, D);
HAMON_CONSTRUCTIBLE_FROM_TEST(false, D, int);

}	// namespace constructible_from_test

}	// namespace hamon_concepts_test

#undef HAMON_CONSTRUCTIBLE_FROM_TEST
