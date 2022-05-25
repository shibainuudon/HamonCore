/**
 *	@file	unit_test_concepts_default_initializable.cpp
 *
 *	@brief	default_initializable のテスト
 */

#include <hamon/concepts/default_initializable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_DEFAULT_INITIALIZABLE_TEST(B, T)	\
	static_assert(B == hamon::default_initializable<T>, "");	\
	static_assert(B == hamon::default_initializable_t<T>::value, "")
#else
#  define HAMON_DEFAULT_INITIALIZABLE_TEST(B, T)	\
	static_assert(B == hamon::default_initializable<T>::value, "");	\
	static_assert(B == hamon::default_initializable_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace default_initializable_test
{

HAMON_DEFAULT_INITIALIZABLE_TEST(false, void);
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  void*);
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  const void*);
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  char);
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  float);
//HAMON_DEFAULT_INITIALIZABLE_TEST(false, const int);	// TODO
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  int*);
HAMON_DEFAULT_INITIALIZABLE_TEST(false, int&);
HAMON_DEFAULT_INITIALIZABLE_TEST(false, int&&);
HAMON_DEFAULT_INITIALIZABLE_TEST(false, const int&);
HAMON_DEFAULT_INITIALIZABLE_TEST(false, int[]);
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  int[2]);
HAMON_DEFAULT_INITIALIZABLE_TEST(false, int());
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  int(*)());
HAMON_DEFAULT_INITIALIZABLE_TEST(false, int(&)());

enum E { };
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  E);
enum class CE { };
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  CE);
struct A { };
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  A);
union B { };
HAMON_DEFAULT_INITIALIZABLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
HAMON_DEFAULT_INITIALIZABLE_TEST(false, C);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
HAMON_DEFAULT_INITIALIZABLE_TEST(false, D);

#if 0	// TODO

struct S0 { explicit S0() = default; };
struct S1 { S0 x; };

HAMON_DEFAULT_INITIALIZABLE_TEST(true,  S0);
HAMON_DEFAULT_INITIALIZABLE_TEST(false, S1);

#endif

}	// namespace default_initializable_test

}	// namespace hamon_concepts_test

#undef HAMON_DEFAULT_INITIALIZABLE_TEST
