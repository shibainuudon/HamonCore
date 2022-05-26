/**
 *	@file	unit_test_concepts_semiregular.cpp
 *
 *	@brief	semiregular のテスト
 */

#include <hamon/concepts/semiregular.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SEMIREGULAR_TEST(B, T)	\
	static_assert(B == hamon::semiregular<T>, "");	\
	static_assert(B == hamon::semiregular_t<T>::value, "")
#else
#  define HAMON_SEMIREGULAR_TEST(B, T)	\
	static_assert(B == hamon::semiregular<T>::value, "");	\
	static_assert(B == hamon::semiregular_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace semiregular_test
{

HAMON_SEMIREGULAR_TEST(true,  int);
HAMON_SEMIREGULAR_TEST(true,  int*);
HAMON_SEMIREGULAR_TEST(false, int&);
HAMON_SEMIREGULAR_TEST(false, void);
HAMON_SEMIREGULAR_TEST(false, void());
HAMON_SEMIREGULAR_TEST(false, void() noexcept);
HAMON_SEMIREGULAR_TEST(false, void() const);

struct Trivial { };
HAMON_SEMIREGULAR_TEST(true,  Trivial);

struct NotTrivial
{
	NotTrivial() { }
	~NotTrivial() { }
};
HAMON_SEMIREGULAR_TEST(true,  NotTrivial);

struct NotDefaultConstructible
{
	NotDefaultConstructible(int) { }
};
HAMON_SEMIREGULAR_TEST(false, NotDefaultConstructible);

struct HasReference
{
	int& ref;
};
HAMON_SEMIREGULAR_TEST(false, HasReference);

}	// namespace semiregular_test

}	// namespace hamon_concepts_test

#undef HAMON_SEMIREGULAR_TEST
