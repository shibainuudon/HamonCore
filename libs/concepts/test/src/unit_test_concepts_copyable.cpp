/**
 *	@file	unit_test_fnd_concepts_copyable.cpp
 *
 *	@brief	copyable のテスト
 */

#include <hamon/concepts/copyable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_COPYABLE_TEST(B, T)	\
	static_assert(B == hamon::copyable<T>, "");	\
	static_assert(B == hamon::copyable_t<T>::value, "")
#else
#  define HAMON_COPYABLE_TEST(B, T)	\
	static_assert(B == hamon::copyable<T>::value, "");	\
	static_assert(B == hamon::copyable_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace copyable_test
{

HAMON_COPYABLE_TEST(true,  int);
HAMON_COPYABLE_TEST(true,  int*);
HAMON_COPYABLE_TEST(false, int&);
HAMON_COPYABLE_TEST(false, void);
HAMON_COPYABLE_TEST(false, void());
HAMON_COPYABLE_TEST(false, void() noexcept);
HAMON_COPYABLE_TEST(false, void() const);

struct Trivial { };
HAMON_COPYABLE_TEST(true,  Trivial);

struct NotTrivial
{
	NotTrivial(int) { }
	NotTrivial(const NotTrivial&) { }
	NotTrivial& operator=(const NotTrivial&) { return *this; }
	~NotTrivial() { }
};
HAMON_COPYABLE_TEST(true,  NotTrivial);

namespace N1
{
struct Immovable
{
	Immovable() = default;
	Immovable(Immovable&&) = delete;
};
}
HAMON_COPYABLE_TEST(false, N1::Immovable);

struct Movable
{
	Movable() = default;
	Movable(Movable&&) = default;
	Movable& operator=(Movable&&) = default;
};
HAMON_COPYABLE_TEST(false, Movable);

struct MovableAndCopyAssignable
{
	MovableAndCopyAssignable() = default;
	MovableAndCopyAssignable(MovableAndCopyAssignable&&) = default;
	MovableAndCopyAssignable& operator=(MovableAndCopyAssignable&&) = default;
	MovableAndCopyAssignable& operator=(const MovableAndCopyAssignable&) = default;
};
HAMON_COPYABLE_TEST(false, MovableAndCopyAssignable);

struct MovableAndCopyConstructible
{
	MovableAndCopyConstructible() = default;
	MovableAndCopyConstructible(MovableAndCopyConstructible&&) = default;
	MovableAndCopyConstructible(const MovableAndCopyConstructible&) = default;
	MovableAndCopyConstructible& operator=(MovableAndCopyConstructible&&) = default;
};
HAMON_COPYABLE_TEST(false, MovableAndCopyConstructible);

namespace N2
{
struct Swappable
{
	Swappable() = default;
	Swappable(Swappable&&) = default;
	friend void swap(Swappable&, Swappable&) { }
};
}
HAMON_COPYABLE_TEST(false, N2::Swappable);

struct NotAssignable
{
	NotAssignable() = default;
	NotAssignable(NotAssignable&&) = default;
	NotAssignable& operator=(NotAssignable&&) = default;
	NotAssignable(const NotAssignable&) = default;
	NotAssignable& operator=(const NotAssignable&) = delete;
	friend void swap(NotAssignable&, NotAssignable&) { }
};
HAMON_COPYABLE_TEST(false, NotAssignable);

struct NotSwappable
{
	NotSwappable() = default;
	NotSwappable(const NotSwappable&) = default;
	NotSwappable& operator=(const NotSwappable&) = default;
};
void swap(NotSwappable&, NotSwappable&) = delete;
HAMON_COPYABLE_TEST(true,  NotSwappable); // ranges::swap still works!

}	// namespace copyable_test

}	// namespace hamon_concepts_test

#undef HAMON_COPYABLE_TEST
