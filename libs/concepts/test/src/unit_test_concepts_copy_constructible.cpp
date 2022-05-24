/**
 *	@file	unit_test_concepts_copy_constructible.cpp
 *
 *	@brief	copy_constructible のテスト
 */

#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_COPY_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == hamon::copy_constructible<T>, "");	\
	static_assert(B == hamon::copy_constructible_t<T>::value, "")
#else
#  define HAMON_COPY_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == hamon::copy_constructible<T>::value, "");	\
	static_assert(B == hamon::copy_constructible_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace copy_constructible_test
{

HAMON_COPY_CONSTRUCTIBLE_TEST(false, void);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  void*);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  const void*);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  char);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  const float);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  int&);
HAMON_COPY_CONSTRUCTIBLE_TEST(false, int&&);
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  const int&);
HAMON_COPY_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_COPY_CONSTRUCTIBLE_TEST(false, int[2]);
HAMON_COPY_CONSTRUCTIBLE_TEST(false, int());
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  int(*)());
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  int(&)());
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  int(&)() noexcept);

enum E { };
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  E);
enum class CE { };
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  CE);
struct A { };
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  A);
union B { };
HAMON_COPY_CONSTRUCTIBLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
HAMON_COPY_CONSTRUCTIBLE_TEST(false, C);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
HAMON_COPY_CONSTRUCTIBLE_TEST(false, D);

}	// namespace copy_constructible_test

}	// namespace hamon_concepts_test

#undef HAMON_COPY_CONSTRUCTIBLE_TEST
