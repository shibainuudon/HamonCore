/**
 *	@file	unit_test_concepts_swappable_with.cpp
 *
 *	@brief	swappable_with のテスト
 */

#include <hamon/concepts/swappable_with.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SWAPPABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::swappable_with<T1, T2>, "");	\
	static_assert(B == hamon::swappable_with_t<T1, T2>::value, "")
#else
#  define HAMON_SWAPPABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::swappable_with<T1, T2>::value, "");	\
	static_assert(B == hamon::swappable_with_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace swappable_with_test
{

HAMON_SWAPPABLE_WITH_TEST(true,  int&, int&);
HAMON_SWAPPABLE_WITH_TEST(false, int, int);
HAMON_SWAPPABLE_WITH_TEST(false, int*, int*);
HAMON_SWAPPABLE_WITH_TEST(false, int&, const int&);
HAMON_SWAPPABLE_WITH_TEST(false, const int&, const int&);
HAMON_SWAPPABLE_WITH_TEST(false, int&, long&);
HAMON_SWAPPABLE_WITH_TEST(true,  int(&)[2], int(&)[2]);
HAMON_SWAPPABLE_WITH_TEST(false, int(&)[2], int(&)[3]);
HAMON_SWAPPABLE_WITH_TEST(false, const int(&)[2], const int(&)[2]);
#if (defined(_MSC_VER) && (_MSC_VER < 1920))
HAMON_SWAPPABLE_WITH_TEST(true,  int[2], int[2]);	// TODO
#else
HAMON_SWAPPABLE_WITH_TEST(false, int[2], int[2]);
#endif

namespace N1
{
struct Immovable
{
	Immovable() = default;
	Immovable(Immovable&&) = delete;
};
}
HAMON_SWAPPABLE_WITH_TEST(false, N1::Immovable&, N1::Immovable&);
HAMON_SWAPPABLE_WITH_TEST(false, N1::Immovable(&)[2], N1::Immovable(&)[2]);

namespace N2
{
struct Swappable
{
	Swappable() = default;
	Swappable(Swappable&&) = delete;
	friend void swap(Swappable&, Swappable&) { }
};
}
HAMON_SWAPPABLE_WITH_TEST(true,  N2::Swappable&, N2::Swappable&);
HAMON_SWAPPABLE_WITH_TEST(true,  N2::Swappable(&)[3], N2::Swappable(&)[3]);

namespace N3
{
struct A { };
struct Proxy {
	Proxy(A&) { }
	friend void swap(Proxy, Proxy) { }
};
}

HAMON_SWAPPABLE_WITH_TEST(true,  N3::A&, N3::A&);
HAMON_SWAPPABLE_WITH_TEST(true,  N3::A&, N3::Proxy);
HAMON_SWAPPABLE_WITH_TEST(true,  N3::Proxy, N3::A&);
HAMON_SWAPPABLE_WITH_TEST(true,  N3::Proxy, N3::Proxy);

struct C { C(int&) { } };
void swap(int&, C&) { } // not symmetrical
HAMON_SWAPPABLE_WITH_TEST(false, int, C);
HAMON_SWAPPABLE_WITH_TEST(false, C, int);

struct D { D(int&) { } };
void swap(int&, D&) { }
void swap(D&&, int&) { } // only accepts rvalues
HAMON_SWAPPABLE_WITH_TEST(false, int, D);
HAMON_SWAPPABLE_WITH_TEST(false, D, int);

struct E { E(int&) { } };
void swap(int, E&&) { } // only accepts rvalues
void swap(E&, int) { }
HAMON_SWAPPABLE_WITH_TEST(false, int, E);
HAMON_SWAPPABLE_WITH_TEST(false, E, int);

}	// namespace swappable_with_test

}	// namespace hamon_concepts_test

#undef HAMON_SWAPPABLE_WITH_TEST
