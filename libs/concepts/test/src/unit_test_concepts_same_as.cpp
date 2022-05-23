/**
 *	@file	unit_test_concepts_same_as.cpp
 *
 *	@brief	same_as のテスト
 */

#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>
#include <type_traits>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SAME_AS_TEST(B, T1, T2)	\
	static_assert(B == hamon::same_as<T1, T2>, "");	\
	static_assert(B == hamon::same_as_t<T1, T2>::value, "")
#else
#  define HAMON_SAME_AS_TEST(B, T1, T2)	\
	static_assert(B == hamon::same_as<T1, T2>::value, "");	\
	static_assert(B == hamon::same_as_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace same_as_test
{

HAMON_SAME_AS_TEST(true,  int, int);
HAMON_SAME_AS_TEST(false, int&, int);
HAMON_SAME_AS_TEST(false, int, int&);
HAMON_SAME_AS_TEST(false, int&&, int&);
HAMON_SAME_AS_TEST(false, const int, int);
HAMON_SAME_AS_TEST(true,  const int, const int);

struct A { };
HAMON_SAME_AS_TEST(true,  A, A);
HAMON_SAME_AS_TEST(false, A, const A);
HAMON_SAME_AS_TEST(true,  A const, const A);
HAMON_SAME_AS_TEST(false, volatile A, const A);

struct B : A { };
HAMON_SAME_AS_TEST(false, A, B);

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
constexpr int
check_subsumption()
{
	return 0;
}

template <typename T, typename U>
requires hamon::same_as<T, U>
constexpr int
check_subsumption()
{
	return 1;
}

template <typename T, typename U>
requires hamon::same_as<U, T>&& std::is_const<T>::value
constexpr int
check_subsumption()
{
	return 2;
}

template <typename T, typename U>
requires hamon::same_as<U, T>&& std::is_volatile<T>::value
constexpr int
check_subsumption()
{
	return 3;
}

static_assert( check_subsumption<short, long>() == 0, "");
static_assert( check_subsumption<unsigned, unsigned>() == 1, "");
// These will be ambiguous if same_as<T,U> doesn't subsume same_as<U,T>:
static_assert( check_subsumption<const char, const char>() == 2, "");
static_assert( check_subsumption<volatile int, volatile int>() == 3, "");

#endif

}	// namespace same_as_test

}	// namespace hamon_concepts_test

#undef HAMON_SAME_AS_TEST
