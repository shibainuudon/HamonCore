/**
 *	@file	unit_test_concepts_movable.cpp
 *
 *	@brief	movable のテスト
 */

#include <hamon/concepts/movable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_MOVABLE_TEST(B, T)	\
	static_assert(B == hamon::movable<T>, "");	\
	static_assert(B == hamon::movable_t<T>::value, "")
#else
#  define HAMON_MOVABLE_TEST(B, T)	\
	static_assert(B == hamon::movable<T>::value, "");	\
	static_assert(B == hamon::movable_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace movable_test
{

HAMON_MOVABLE_TEST(true,  int);
HAMON_MOVABLE_TEST(true,  int*);
HAMON_MOVABLE_TEST(false, int&);
HAMON_MOVABLE_TEST(false, void);
HAMON_MOVABLE_TEST(false, void());
HAMON_MOVABLE_TEST(false, void() noexcept);
HAMON_MOVABLE_TEST(false, void() const);

struct Trivial { };
HAMON_MOVABLE_TEST(true,  Trivial);

struct NotTrivial
{
	NotTrivial(int) { }
	NotTrivial(NotTrivial&&) noexcept { }
	NotTrivial& operator=(NotTrivial&&) noexcept { return *this; }
	~NotTrivial() { }
};
HAMON_MOVABLE_TEST(true,  NotTrivial);

namespace N1
{
struct Immovable
{
	Immovable() = default;
	Immovable(Immovable&&) = delete;
};
}
HAMON_MOVABLE_TEST(false, N1::Immovable);

namespace N2
{
struct Swappable
{
	Swappable() = default;
	Swappable(Swappable&&) = delete;
	Swappable& operator=(Swappable&&) = default;
	friend void swap(Swappable&, Swappable&) { }
};
}
HAMON_MOVABLE_TEST(false, N2::Swappable);

struct NotAssignable
{
	NotAssignable() = default;
	NotAssignable(NotAssignable&&) = default;
	NotAssignable& operator=(NotAssignable&&) = delete;
	friend void swap(NotAssignable&, NotAssignable&) { }
};
HAMON_MOVABLE_TEST(false, NotAssignable);

struct NotSwappable
{
	NotSwappable() = default;
	NotSwappable(NotSwappable&&) = default;
	NotSwappable& operator=(NotSwappable&&) = default;
};
void swap(NotSwappable&, NotSwappable&) = delete;
HAMON_MOVABLE_TEST(true,  NotSwappable); // ranges::swap still works!

}	// namespace movable_test

}	// namespace hamon_concepts_test

#undef HAMON_MOVABLE_TEST
