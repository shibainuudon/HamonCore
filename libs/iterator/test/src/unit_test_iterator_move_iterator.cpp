/**
 *	@file	unit_test_iterator_move_iterator.cpp
 *
 *	@brief	move_iterator のテスト
 */

#include <hamon/iterator/move_iterator.hpp>
#include <hamon/iterator/move_sentinel.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/concepts.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/concepts.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_iterator_test
{

namespace move_iterator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

GTEST_TEST(MoveIteratorTest, ConceptTest)
{
	{
		using iterator = hamon::move_iterator<input_iterator_wrapper<int>>;

		static_assert( hamon::default_initializable_t<iterator>::value, "");
		static_assert( hamon::copyable_t<iterator>::value, "");
		static_assert( hamon::input_iterator_t<iterator>::value, "");
		static_assert(!hamon::forward_iterator_t<iterator>::value, "");
		static_assert( hamon::sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_storable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_storable_t<int*, iterator>::value, "");
		static_assert( hamon::indirectly_readable_t<iterator>::value, "");
		static_assert(!hamon::indirectly_writable_t<iterator, int>::value, "");
		static_assert( hamon::indirectly_swappable_t<iterator, iterator>::value, "");
	}
	{
		using iterator = hamon::move_iterator<forward_iterator_wrapper<int>>;

		static_assert( hamon::default_initializable_t<iterator>::value, "");
		static_assert( hamon::copyable_t<iterator>::value, "");
		static_assert( hamon::input_iterator_t<iterator>::value, "");
		static_assert( hamon::forward_iterator_t<iterator>::value, "");
		static_assert(!hamon::bidirectional_iterator_t<iterator>::value, "");
		static_assert( hamon::sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_storable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_storable_t<int*, iterator>::value, "");
		static_assert( hamon::indirectly_readable_t<iterator>::value, "");
		static_assert(!hamon::indirectly_writable_t<iterator, int>::value, "");
		static_assert( hamon::indirectly_swappable_t<iterator, iterator>::value, "");
	}
	{
		using iterator = hamon::move_iterator<bidirectional_iterator_wrapper<int>>;

		static_assert( hamon::default_initializable_t<iterator>::value, "");
		static_assert( hamon::copyable_t<iterator>::value, "");
		static_assert( hamon::input_iterator_t<iterator>::value, "");
		static_assert( hamon::forward_iterator_t<iterator>::value, "");
		static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
		static_assert(!hamon::random_access_iterator_t<iterator>::value, "");
		static_assert( hamon::sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_storable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_storable_t<int*, iterator>::value, "");
		static_assert( hamon::indirectly_readable_t<iterator>::value, "");
		static_assert(!hamon::indirectly_writable_t<iterator, int>::value, "");
		static_assert( hamon::indirectly_swappable_t<iterator, iterator>::value, "");
	}
	{
		using iterator = hamon::move_iterator<random_access_iterator_wrapper<int>>;

		static_assert( hamon::default_initializable_t<iterator>::value, "");
		static_assert( hamon::copyable_t<iterator>::value, "");
		static_assert( hamon::input_iterator_t<iterator>::value, "");
		static_assert( hamon::forward_iterator_t<iterator>::value, "");
		static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
		static_assert( hamon::random_access_iterator_t<iterator>::value, "");
		static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
		static_assert( hamon::sentinel_for_t<iterator, iterator>::value, "");
		static_assert( hamon::sized_sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_storable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_storable_t<int*, iterator>::value, "");
		static_assert( hamon::indirectly_readable_t<iterator>::value, "");
		static_assert(!hamon::indirectly_writable_t<iterator, int>::value, "");
		static_assert( hamon::indirectly_swappable_t<iterator, iterator>::value, "");
	}
	{
		using iterator = hamon::move_iterator<contiguous_iterator_wrapper<int>>;

		static_assert( hamon::default_initializable_t<iterator>::value, "");
		static_assert( hamon::copyable_t<iterator>::value, "");
		static_assert( hamon::input_iterator_t<iterator>::value, "");
		static_assert( hamon::forward_iterator_t<iterator>::value, "");
		static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
		static_assert( hamon::random_access_iterator_t<iterator>::value, "");
		static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
		static_assert( hamon::sentinel_for_t<iterator, iterator>::value, "");
		static_assert( hamon::sized_sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_storable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_storable_t<int*, iterator>::value, "");
		static_assert( hamon::indirectly_readable_t<iterator>::value, "");
		static_assert(!hamon::indirectly_writable_t<iterator, int>::value, "");
		static_assert( hamon::indirectly_swappable_t<iterator, iterator>::value, "");
	}
	{
		using iterator = hamon::move_iterator<int*>;

		static_assert( hamon::default_initializable_t<iterator>::value, "");
		static_assert( hamon::copyable_t<iterator>::value, "");
		static_assert( hamon::input_iterator_t<iterator>::value, "");
		static_assert( hamon::forward_iterator_t<iterator>::value, "");
		static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
		static_assert( hamon::random_access_iterator_t<iterator>::value, "");
		static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
		static_assert( hamon::sentinel_for_t<iterator, iterator>::value, "");
		static_assert( hamon::sized_sentinel_for_t<iterator, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_movable_storable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_t<int*, iterator>::value, "");
		static_assert(!hamon::indirectly_copyable_storable_t<int*, iterator>::value, "");
		static_assert( hamon::indirectly_readable_t<iterator>::value, "");
		static_assert(!hamon::indirectly_writable_t<iterator, int>::value, "");
		static_assert( hamon::indirectly_swappable_t<iterator, iterator>::value, "");
	}
}

template <typename Iter, typename Category>
inline HAMON_CXX14_CONSTEXPR bool TypesTest()
{
	using MoveIter = hamon::move_iterator<Iter>;

	static_assert(hamon::is_same<typename MoveIter::iterator_type,    Iter>::value, "");
	static_assert(hamon::is_same<typename MoveIter::iterator_concept, Category>::value, "");
	static_assert(hamon::is_same<typename MoveIter::iterator_category, Category>::value, "");
	static_assert(hamon::is_same<typename MoveIter::value_type,       hamon::iter_value_t<Iter>>::value, "");
	static_assert(hamon::is_same<typename MoveIter::difference_type,  hamon::iter_difference_t<Iter>>::value, "");
	static_assert(hamon::is_same<typename MoveIter::pointer,          Iter>::value, "");
	static_assert(hamon::is_same<typename MoveIter::reference,        hamon::iter_rvalue_reference_t<Iter>>::value, "");

	return true;
}

GTEST_TEST(MoveIteratorTest, TypesTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<input_iterator_wrapper<int>,         hamon::input_iterator_tag>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<forward_iterator_wrapper<int>,       hamon::forward_iterator_tag>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<bidirectional_iterator_wrapper<int>, hamon::bidirectional_iterator_tag>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<random_access_iterator_wrapper<int>, hamon::random_access_iterator_tag>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<contiguous_iterator_wrapper<int>,    hamon::random_access_iterator_tag>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<int*,       hamon::random_access_iterator_tag>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((TypesTest<int const*, hamon::random_access_iterator_tag>()));
}

struct Base {};
struct Derived : Base {};

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)

struct NoDefaultCtr : public input_iterator_wrapper<int>
{
	NoDefaultCtr() = delete;
};

static_assert( hamon::is_default_constructible<hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::move_iterator<NoDefaultCtr>>::value, "");

struct ThrowDefaultCtr : public input_iterator_wrapper<int>
{
	ThrowDefaultCtr() {}
};

static_assert( hamon::is_default_constructible<hamon::move_iterator<ThrowDefaultCtr>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::move_iterator<ThrowDefaultCtr>>::value, "");

#endif

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	static_assert(hamon::is_nothrow_default_constructible<
		hamon::move_iterator<Iter>>::value, "");

	hamon::move_iterator<Iter> it;
	(void)it;
	return true;
}

GTEST_TEST(MoveIteratorTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<input_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<forward_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<bidirectional_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<random_access_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<contiguous_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<int*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest<int const*>());
}

template <typename T, template <typename> class IteratorWrapper>
struct MoveOnly : public IteratorWrapper<T>
{
public:
	HAMON_CXX14_CONSTEXPR MoveOnly() : IteratorWrapper<T>{} {}
	HAMON_CXX14_CONSTEXPR MoveOnly(T* p) : IteratorWrapper<T>{p} {}
	HAMON_CXX14_CONSTEXPR MoveOnly(MoveOnly&& other) = default;
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly&& other) = default;
private:
	MoveOnly(MoveOnly const&) = delete;
	MoveOnly& operator=(MoveOnly const&) = delete;
};

template <typename T> using move_only_input_iterator_wrapper         = MoveOnly<T, input_iterator_wrapper>;
template <typename T> using move_only_forward_iterator_wrapper       = MoveOnly<T, forward_iterator_wrapper>;
template <typename T> using move_only_bidirectional_iterator_wrapper = MoveOnly<T, bidirectional_iterator_wrapper>;
template <typename T> using move_only_random_access_iterator_wrapper = MoveOnly<T, random_access_iterator_wrapper>;
template <typename T> using move_only_contiguous_iterator_wrapper    = MoveOnly<T, contiguous_iterator_wrapper>;

static_assert(!hamon::is_copy_constructible<move_only_input_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_constructible<move_only_forward_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_constructible<move_only_bidirectional_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_constructible<move_only_random_access_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_constructible<move_only_contiguous_iterator_wrapper<int>>::value, "");

static_assert( hamon::is_move_constructible<move_only_input_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_constructible<move_only_forward_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_constructible<move_only_bidirectional_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_constructible<move_only_random_access_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_constructible<move_only_contiguous_iterator_wrapper<int>>::value, "");

static_assert(!hamon::is_copy_assignable<move_only_input_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_assignable<move_only_forward_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_assignable<move_only_bidirectional_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_assignable<move_only_random_access_iterator_wrapper<int>>::value, "");
static_assert(!hamon::is_copy_assignable<move_only_contiguous_iterator_wrapper<int>>::value, "");

static_assert( hamon::is_move_assignable<move_only_input_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_assignable<move_only_forward_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_assignable<move_only_bidirectional_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_assignable<move_only_random_access_iterator_wrapper<int>>::value, "");
static_assert( hamon::is_move_assignable<move_only_contiguous_iterator_wrapper<int>>::value, "");

template <typename T, template <typename> class IteratorWrapper>
struct Convertible : public IteratorWrapper<T>
{
public:
	using pointer = typename IteratorWrapper<T>::pointer;

	HAMON_CXX14_CONSTEXPR Convertible(pointer p)
		: IteratorWrapper<T>{p} {}

    template <typename U,
		typename Other = Convertible<U, IteratorWrapper>
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<U, T>>,
			hamon::convertible_to_t<decltype(base(hamon::declval<Other const&>())), pointer>
		>::value>
	>
    HAMON_CXX14_CONSTEXPR
	Convertible(Convertible<U, IteratorWrapper> const& u)
	//requires (!hamon::is_same<U, T>::value) &&
	//	hamon::convertible_to<decltype(base(u)), pointer>
		: IteratorWrapper<T>{base(u)} {}
};

template <typename T> using convertible_input_iterator_wrapper         = Convertible<T, input_iterator_wrapper>;
template <typename T> using convertible_forward_iterator_wrapper       = Convertible<T, forward_iterator_wrapper>;
template <typename T> using convertible_bidirectional_iterator_wrapper = Convertible<T, bidirectional_iterator_wrapper>;
template <typename T> using convertible_random_access_iterator_wrapper = Convertible<T, random_access_iterator_wrapper>;
template <typename T> using convertible_contiguous_iterator_wrapper    = Convertible<T, contiguous_iterator_wrapper>;

static_assert(!hamon::is_constructible<
	input_iterator_wrapper<int>,
	input_iterator_wrapper<int const> const&
>::value, "");

static_assert( hamon::is_constructible<
	convertible_input_iterator_wrapper<int const>,
	convertible_input_iterator_wrapper<int> const&
>::value, "");

static_assert(!hamon::is_constructible<
	convertible_input_iterator_wrapper<int>,
	convertible_input_iterator_wrapper<int const> const&
>::value, "");


static_assert(!hamon::is_constructible<
	input_iterator_wrapper<Base>,
	input_iterator_wrapper<Derived> const&
>::value, "");

static_assert( hamon::is_constructible<
	convertible_input_iterator_wrapper<Base>,
	convertible_input_iterator_wrapper<Derived> const&
>::value, "");

static_assert(!hamon::is_constructible<
	convertible_input_iterator_wrapper<Derived>,
	convertible_input_iterator_wrapper<Base> const&
>::value, "");

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool CtorIterTest()
{
	static_assert( hamon::is_constructible<hamon::move_iterator<Iter>, Iter const&>::value, "");
	static_assert( hamon::is_constructible<hamon::move_iterator<Iter>, Iter &&>::value, "");
	static_assert(!hamon::is_convertible<Iter const&, hamon::move_iterator<Iter>>::value, "");
	static_assert(!hamon::is_convertible<Iter &&,     hamon::move_iterator<Iter>>::value, "");

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	static_assert( hamon::is_nothrow_constructible<hamon::move_iterator<Iter>, Iter const&>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::move_iterator<Iter>, Iter &&>::value, "");
#endif

	// explicitly constructible
	static_assert(!hamon::is_implicitly_constructible<hamon::move_iterator<Iter>, Iter const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::move_iterator<Iter>, Iter &&>::value, "");
	
	char s[] = "123";
	{
		Iter it = Iter{s};
		hamon::move_iterator<Iter> r(it);
		VERIFY(base(r.base()) == s);
	}
	{
		Iter it = Iter{s};
		hamon::move_iterator<Iter> r(hamon::move(it));
		VERIFY(base(r.base()) == s);
	}

	return true;
}

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool CtorIterMoveOnlyTest()
{
	static_assert(!hamon::is_constructible<hamon::move_iterator<Iter>, Iter const&>::value, "");
	static_assert( hamon::is_constructible<hamon::move_iterator<Iter>, Iter &&>::value, "");
	static_assert(!hamon::is_convertible<Iter const&, hamon::move_iterator<Iter>>::value, "");
	static_assert(!hamon::is_convertible<Iter &&,     hamon::move_iterator<Iter>>::value, "");

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	static_assert( hamon::is_nothrow_constructible<hamon::move_iterator<Iter>, Iter &&>::value, "");
#endif

	// explicitly constructible
	static_assert(!hamon::is_implicitly_constructible<hamon::move_iterator<Iter>, Iter const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::move_iterator<Iter>, Iter &&>::value, "");

	char s[] = "123";
	{
		Iter it = Iter(s);
		hamon::move_iterator<Iter> r(hamon::move(it));
		VERIFY(base(r.base()) == s);
	}

	return true;
}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowMoveCtor : public IteratorWrapper<T>
{
public:
	using pointer = typename IteratorWrapper<T>::pointer;

	HAMON_CXX14_CONSTEXPR MayThrowMoveCtor(pointer p) noexcept;
	HAMON_CXX14_CONSTEXPR MayThrowMoveCtor(MayThrowMoveCtor const&) = default;
	HAMON_CXX14_CONSTEXPR MayThrowMoveCtor(MayThrowMoveCtor && other) noexcept(Noexcept);
};

#endif

GTEST_TEST(MoveIteratorTest, CtorIterTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<input_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<forward_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<bidirectional_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<random_access_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<contiguous_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<char*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterTest<char const*>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterMoveOnlyTest<move_only_input_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterMoveOnlyTest<move_only_forward_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterMoveOnlyTest<move_only_bidirectional_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterMoveOnlyTest<move_only_random_access_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIterMoveOnlyTest<move_only_contiguous_iterator_wrapper<char>>());

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowMoveCtor<true, int, input_iterator_wrapper>;
		static_assert( hamon::is_constructible<hamon::move_iterator<Iter>, Iter>::value, "");
		static_assert( hamon::is_nothrow_constructible<hamon::move_iterator<Iter>, Iter>::value, "");
	}
	{
		using Iter = MayThrowMoveCtor<false, int, input_iterator_wrapper>;
		static_assert( hamon::is_constructible<hamon::move_iterator<Iter>, Iter>::value, "");
		static_assert(!hamon::is_nothrow_constructible<hamon::move_iterator<Iter>, Iter>::value, "");
	}
#endif
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool CtorConvertTest()
{
	static_assert( hamon::is_constructible<
		hamon::move_iterator<IteratorWrapper<Base>>,
		hamon::move_iterator<IteratorWrapper<Derived>>>::value, "");
	static_assert(!hamon::is_constructible<
		hamon::move_iterator<IteratorWrapper<Derived>>,
		hamon::move_iterator<IteratorWrapper<Base>>>::value, "");
	{
		Derived d;
		IteratorWrapper<Derived> it0{&d};
		hamon::move_iterator<IteratorWrapper<Derived>> it1{it0};
		hamon::move_iterator<IteratorWrapper<Base>> it2(it1);
		VERIFY(base(it2.base()) == base(it0));
	}
	return true;
}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowConvCtor : public IteratorWrapper<T>
{
public:
	using pointer = typename IteratorWrapper<T>::pointer;

	HAMON_CXX14_CONSTEXPR MayThrowConvCtor(pointer p) noexcept;
	HAMON_CXX14_CONSTEXPR MayThrowConvCtor(MayThrowConvCtor const&) = default;
	HAMON_CXX14_CONSTEXPR MayThrowConvCtor(MayThrowConvCtor &&) = default;

    template <typename U>
    HAMON_CXX14_CONSTEXPR
	MayThrowConvCtor(MayThrowConvCtor<Noexcept, U, IteratorWrapper> const& u)
		 noexcept(Noexcept);
};
#endif

GTEST_TEST(MoveIteratorTest, CtorConvertTest)
{
	static_assert( hamon::is_constructible<Base*, Derived*>::value, "");
	static_assert(!hamon::is_constructible<Derived*, Base*>::value, "");

	static_assert( hamon::is_constructible<hamon::move_iterator<Base*>, hamon::move_iterator<Derived*>>::value, "");
	static_assert(!hamon::is_constructible<hamon::move_iterator<Derived*>, hamon::move_iterator<Base*>>::value, "");

	static_assert( hamon::is_constructible<hamon::move_iterator<Base*>, hamon::move_iterator<Derived*> const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::move_iterator<Derived*>, hamon::move_iterator<Base*> const&>::value, "");

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	static_assert( hamon::is_nothrow_constructible<hamon::move_iterator<Base*>, hamon::move_iterator<Derived*>>::value, "");
#endif

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorConvertTest<convertible_input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorConvertTest<convertible_forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorConvertTest<convertible_bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorConvertTest<convertible_random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorConvertTest<convertible_contiguous_iterator_wrapper>());

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter1 = MayThrowConvCtor<true, Base, input_iterator_wrapper>;
		using Iter2 = MayThrowConvCtor<true, Derived, input_iterator_wrapper>;
		static_assert( hamon::is_constructible<hamon::move_iterator<Iter1>, hamon::move_iterator<Iter2>>::value, "");
		static_assert( hamon::is_nothrow_constructible<hamon::move_iterator<Iter1>, hamon::move_iterator<Iter2>>::value, "");
	}
	{
		using Iter1 = MayThrowConvCtor<false, Base, input_iterator_wrapper>;
		using Iter2 = MayThrowConvCtor<false, Derived, input_iterator_wrapper>;
		static_assert( hamon::is_constructible<hamon::move_iterator<Iter1>, hamon::move_iterator<Iter2>>::value, "");
		static_assert(!hamon::is_nothrow_constructible<hamon::move_iterator<Iter1>, hamon::move_iterator<Iter2>>::value, "");
	}
#endif
}

GTEST_TEST(MoveIteratorTest, CtorCTADTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		int* p = nullptr;
		hamon::move_iterator it(p);
		static_assert(hamon::is_same<decltype(it), hamon::move_iterator<int*>>::value, "");
	}
#endif
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool ConvAssignTest()
{
	static_assert( hamon::is_assignable<
		hamon::move_iterator<IteratorWrapper<Base>>&,
		hamon::move_iterator<IteratorWrapper<Derived>>
	>::value, "");

	static_assert(!hamon::is_assignable<
		hamon::move_iterator<IteratorWrapper<Derived>>&,
		hamon::move_iterator<IteratorWrapper<Base>>
	>::value, "");

	{
		Derived d;
		IteratorWrapper<Derived> it0{&d};
		hamon::move_iterator<IteratorWrapper<Derived>> it1{it0};
		hamon::move_iterator<IteratorWrapper<Base>> it2{IteratorWrapper<Base>{nullptr}};
		hamon::move_iterator<IteratorWrapper<Base>>& r = (it2 = it1);
		VERIFY(base(it2.base()) == base(it0));
		VERIFY(&r == &it2);
	}
	{
		Derived d;
		hamon::move_iterator<Derived*> it1{&d};
		hamon::move_iterator<Base*> it2{nullptr};
		hamon::move_iterator<Base*>& r = (it2 = it1);
		VERIFY(base(it2.base()) == &d);
		VERIFY(&r == &it2);
	}
	return true;
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool CopyAssignTest()
{
	static_assert( hamon::is_copy_assignable<hamon::move_iterator<IteratorWrapper<int>>>::value, "");
	static_assert( hamon::is_move_assignable<hamon::move_iterator<IteratorWrapper<int>>>::value, "");

	{
		char s[] = "123";
		IteratorWrapper<char> it0{s};
		hamon::move_iterator<IteratorWrapper<char>> it1{it0};
		hamon::move_iterator<IteratorWrapper<char>> it2;
		hamon::move_iterator<IteratorWrapper<char>>& r = (it2 = it1);
		VERIFY(base(it2.base()) == base(it0));
		VERIFY(&r == &it2);
	}
	{
		char s[] = "123";
		IteratorWrapper<char> it0{s};
		hamon::move_iterator<IteratorWrapper<char>> it1{it0};
		hamon::move_iterator<IteratorWrapper<char>> it2;
		hamon::move_iterator<IteratorWrapper<char>>& r = (it2 = hamon::move(it1));
		VERIFY(base(it2.base()) == base(it0));
		VERIFY(&r == &it2);
	}

	return true;
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool MoveAssignTest()
{
	static_assert(!hamon::is_copy_assignable<hamon::move_iterator<IteratorWrapper<int>>>::value, "");
	static_assert( hamon::is_move_assignable<hamon::move_iterator<IteratorWrapper<int>>>::value, "");

	{
		char s[] = "123";
		hamon::move_iterator<IteratorWrapper<char>> it1{IteratorWrapper<char>{s}};
		hamon::move_iterator<IteratorWrapper<char>> it2;
		VERIFY(base(it2.base()) == nullptr);
		hamon::move_iterator<IteratorWrapper<char>>& r = (it2 = hamon::move(it1));
		VERIFY(base(it2.base()) == s);
		VERIFY(&r == &it2);
	}

	return true;
}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowAssign : public IteratorWrapper<T>
{
public:
	using pointer = typename IteratorWrapper<T>::pointer;

	HAMON_CXX14_CONSTEXPR MayThrowAssign(pointer p) noexcept;
	HAMON_CXX14_CONSTEXPR MayThrowAssign(MayThrowAssign const&) = default;
	HAMON_CXX14_CONSTEXPR MayThrowAssign(MayThrowAssign &&) = default;

    template <typename U,
		typename Other = MayThrowAssign<Noexcept, U, IteratorWrapper>
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<U, T>>,
			hamon::convertible_to_t<decltype(base(hamon::declval<Other const&>())), pointer>
		>::value>
	>
    HAMON_CXX14_CONSTEXPR
	MayThrowAssign(MayThrowAssign<Noexcept, U, IteratorWrapper> const& u) noexcept;

	template <typename U>
    HAMON_CXX14_CONSTEXPR
	MayThrowAssign& operator=(MayThrowAssign<Noexcept, U, IteratorWrapper> const& u)
		noexcept(Noexcept);
};
#endif

GTEST_TEST(MoveIteratorTest, AssignTest)
{
	static_assert( hamon::is_assignable<Base*&, Derived*>::value, "");
	static_assert(!hamon::is_assignable<Derived*&, Base*>::value, "");

	static_assert( hamon::is_assignable<hamon::move_iterator<Base*>&, hamon::move_iterator<Derived*>>::value, "");
	static_assert(!hamon::is_assignable<hamon::move_iterator<Derived*>&, hamon::move_iterator<Base*>>::value, "");
	static_assert( hamon::is_assignable<hamon::move_iterator<Base*>&, hamon::move_iterator<Derived*> &&>::value, "");
	static_assert(!hamon::is_assignable<hamon::move_iterator<Derived*>&, hamon::move_iterator<Base*> &&>::value, "");
	static_assert( hamon::is_assignable<hamon::move_iterator<Base*>&, hamon::move_iterator<Derived*> const&>::value, "");
	static_assert(!hamon::is_assignable<hamon::move_iterator<Derived*>&, hamon::move_iterator<Base*> const&>::value, "");

	static_assert( hamon::is_copy_assignable<hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_move_assignable<hamon::move_iterator<int*>>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConvAssignTest<convertible_input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConvAssignTest<convertible_forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConvAssignTest<convertible_bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConvAssignTest<convertible_random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConvAssignTest<convertible_contiguous_iterator_wrapper>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<contiguous_iterator_wrapper>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MoveAssignTest<move_only_input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MoveAssignTest<move_only_forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MoveAssignTest<move_only_bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MoveAssignTest<move_only_random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MoveAssignTest<move_only_contiguous_iterator_wrapper>());

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter1 = MayThrowAssign<true, Base, input_iterator_wrapper>;
		using Iter2 = MayThrowAssign<true, Derived, input_iterator_wrapper>;
		static_assert( hamon::is_assignable<hamon::move_iterator<Iter1>&, hamon::move_iterator<Iter2>>::value, "");
		static_assert( hamon::is_nothrow_assignable<hamon::move_iterator<Iter1>&, hamon::move_iterator<Iter2>>::value, "");
	}
	{
		using Iter1 = MayThrowAssign<false, Base, input_iterator_wrapper>;
		using Iter2 = MayThrowAssign<false, Derived, input_iterator_wrapper>;
		static_assert( hamon::is_assignable<hamon::move_iterator<Iter1>&, hamon::move_iterator<Iter2>>::value, "");
		static_assert(!hamon::is_nothrow_assignable<hamon::move_iterator<Iter1>&, hamon::move_iterator<Iter2>>::value, "");
	}
#endif
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool BaseTest()
{
	using It = IteratorWrapper<int>;

	int a[] = { 1, 2, 3 };

	// Non-const lvalue.
	{
		auto i = hamon::move_iterator<It>{It{a}};
		static_assert(hamon::is_same<decltype(i.base()), const It&>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(i.base());
		VERIFY(i.base() == It{a});

		++i;
		VERIFY(i.base() == It{a + 1});
	}

	// Const lvalue.
	{
		const auto i = hamon::move_iterator<It>{It{a}};
		static_assert(hamon::is_same<decltype(i.base()), const It&>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(i.base());
		VERIFY(i.base() == It{a});
	}

	// Rvalue.
	{
		auto i = hamon::move_iterator<It>{It{a}};
		static_assert(hamon::is_same<decltype(hamon::move(i).base()), It>::value, "");
		VERIFY(hamon::move(i).base() == It{a});
	}

	return true;
}

GTEST_TEST(MoveIteratorTest, BaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BaseTest<input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BaseTest<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BaseTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BaseTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BaseTest<contiguous_iterator_wrapper>());

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowMoveCtor<true, int, input_iterator_wrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_TRUE (hamon::declval<MoveIter &>().base());
		HAMON_ASSERT_NOEXCEPT_TRUE (hamon::declval<MoveIter const&>().base());
		HAMON_ASSERT_NOEXCEPT_TRUE (hamon::declval<MoveIter &&>().base());
	}
	{
		using Iter = MayThrowMoveCtor<false, int, input_iterator_wrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_TRUE (hamon::declval<MoveIter &>().base());
		HAMON_ASSERT_NOEXCEPT_TRUE (hamon::declval<MoveIter const&>().base());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter &&>().base());
	}
#endif
}

struct MoveOnlyObject
{
	int m_value = 0;

	HAMON_CXX14_CONSTEXPR MoveOnlyObject() = default;
	HAMON_CXX14_CONSTEXPR MoveOnlyObject(int v) : m_value(v) {}

	HAMON_CXX14_CONSTEXPR MoveOnlyObject(MoveOnlyObject&& other)
		: m_value(other.m_value) 
	{}

	MoveOnlyObject(MoveOnlyObject const&) = delete;
	MoveOnlyObject& operator=(MoveOnlyObject const&) = delete;
};

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct IterMoveOnly : public IteratorWrapper<T>
{
public:
	using difference_type = typename IteratorWrapper<T>::difference_type;

	HAMON_CXX14_CONSTEXPR IterMoveOnly() : IteratorWrapper<T>{} {}
	HAMON_CXX14_CONSTEXPR IterMoveOnly(T* p) : IteratorWrapper<T>{p} {}
	HAMON_CXX14_CONSTEXPR IterMoveOnly(IterMoveOnly&& other) = default;
	HAMON_CXX14_CONSTEXPR IterMoveOnly& operator=(IterMoveOnly&& other) = default;
	HAMON_CXX14_CONSTEXPR IterMoveOnly(IterMoveOnly const&) = delete;
	HAMON_CXX14_CONSTEXPR IterMoveOnly& operator=(IterMoveOnly const&) = delete;

	HAMON_CXX11_CONSTEXPR IterMoveOnly operator+(difference_type n) const noexcept
	{
		return {base(*this) + n};
	}

	// operator*が実装されていないので、*itで間接参照することはできない
	HAMON_CXX14_CONSTEXPR T&& operator*() const;

	// iter_moveによって間接参照が可能
	friend HAMON_CXX14_CONSTEXPR T&&
	iter_move(IterMoveOnly const& it)
		noexcept(Noexcept)
	{
		return hamon::move(*base(it));
	}
};

//template <typename T> using iter_move_only_input_iterator_wrapper         = IterMoveOnly<T, input_iterator_wrapper>;
//template <typename T> using iter_move_only_forward_iterator_wrapper       = IterMoveOnly<T, forward_iterator_wrapper>;
//template <typename T> using iter_move_only_bidirectional_iterator_wrapper = IterMoveOnly<T, bidirectional_iterator_wrapper>;
//template <typename T> using iter_move_only_random_access_iterator_wrapper = IterMoveOnly<T, random_access_iterator_wrapper>;
//template <typename T> using iter_move_only_contiguous_iterator_wrapper    = IterMoveOnly<T, contiguous_iterator_wrapper>;

inline HAMON_CXX14_CONSTEXPR bool OperatorStarTest()
{
	{
		int n = 3;
		int* p = &n;
		hamon::move_iterator<int*> it{p};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(*it);
#endif
		VERIFY(*it == 3);
	}
	{
		const char *p = "123456789";
		hamon::move_iterator<const char*> it1(p);
		hamon::move_iterator<const char*> it2(p+1);
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(*it1);
		HAMON_ASSERT_NOEXCEPT_TRUE(*it2);
#endif
		VERIFY(*it1 == p[0]);
		VERIFY(*it2 == p[1]);
	}
	{
		MoveOnlyObject o(42);
		hamon::move_iterator<MoveOnlyObject*> it{&o};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(*it);
#endif
		auto o2 = *it;
		VERIFY(o2.m_value == 42);
	}
	{
		int n = 3;
		hamon::move_iterator<move_only_input_iterator_wrapper<int>> it{&n};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_FALSE(*it);
#endif
		VERIFY(*it == 3);
	}
	{
		using Iter = IterMoveOnly<true, int, input_iterator_wrapper>;
		int n = 4;
		hamon::move_iterator<Iter> it{&n};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(*it);
#endif
		VERIFY(*it == 4);
	}
	{
		using Iter = IterMoveOnly<false, int, input_iterator_wrapper>;
		int n = 4;
		hamon::move_iterator<Iter> it{&n};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_FALSE(*it);
#endif
		VERIFY(*it == 4);
	}

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorStarTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorStarTest());
}

inline HAMON_CXX14_CONSTEXPR bool OperatorIndexTest()
{
	{
		int a[] = {1, 2, 3};
		hamon::move_iterator<int*> it{a};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it[0]);
#endif
		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
	}
	{
		MoveOnlyObject a[]
		{
			{4},
			{5},
			{6},
			{7},
		};
		hamon::move_iterator<MoveOnlyObject*> it{a};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it[0]);
#endif
		VERIFY(it[0].m_value == 4);
		VERIFY(it[1].m_value == 5);
		VERIFY(it[2].m_value == 6);
		VERIFY(it[3].m_value == 7);
	}
	{
		int a[] = {0, 2, 4, 6, 8};
		hamon::move_iterator<move_only_random_access_iterator_wrapper<int>> it{a};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_FALSE(it[0]);
#endif
		VERIFY(it[0] == 0);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 4);
		VERIFY(it[3] == 6);
		VERIFY(it[4] == 8);
	}
	{
		using Iter = IterMoveOnly<true, int, random_access_iterator_wrapper>;
		int a[] = {41,42};
		hamon::move_iterator<Iter> it{a};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it[0]);
#endif
		VERIFY(it[0] == 41);
		VERIFY(it[1] == 42);
	}
	{
		using Iter = IterMoveOnly<false, int, random_access_iterator_wrapper>;
		int a[] = {41,42};
		hamon::move_iterator<Iter> it{a};
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_FALSE(it[0]);
#endif
		VERIFY(it[0] == 41);
		VERIFY(it[1] == 42);
	}

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorIndexTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorIndexTest());
}

template <bool NoexceptCopy, bool NoexceptIncrement, typename T, template <typename> class IteratorWrapper>
struct MayThrowIncrement : public IteratorWrapper<T>
{
	MayThrowIncrement() = default;
	MayThrowIncrement(MayThrowIncrement const&) noexcept(NoexceptCopy);
	MayThrowIncrement& operator++() noexcept(NoexceptIncrement);
	MayThrowIncrement  operator++(int) noexcept(NoexceptIncrement);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPreIncrementTest()
{
	int a[] = {1,2,3,4,5};

	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a}};
		static_assert(hamon::is_same<decltype(++it), hamon::move_iterator<It>&>::value, "");
		VERIFY(base(it.base()) == a);
		auto r = ++it;
		VERIFY(base(it.base()) == a+1);
		VERIFY(base(r.base()) == a+1);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowIncrement<true, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(++hamon::declval<hamon::move_iterator<Iter>>());
	}
	{
		using Iter = MayThrowIncrement<true, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(++hamon::declval<hamon::move_iterator<Iter>>());
	}
	{
		using Iter = MayThrowIncrement<false, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(++hamon::declval<hamon::move_iterator<Iter>>());
	}
	{
		using Iter = MayThrowIncrement<false, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(++hamon::declval<hamon::move_iterator<Iter>>());
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreIncrementTest<input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreIncrementTest<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreIncrementTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreIncrementTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreIncrementTest<contiguous_iterator_wrapper>());
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPostIncrementTest()
{
	int a[] = {1,2,3,4,5};

	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a}};
		static_assert(hamon::is_same<decltype(it++), hamon::move_iterator<It>>::value, "");
		VERIFY(base(it.base()) == a);
		auto r = it++;
		VERIFY(base(it.base()) == a+1);
		VERIFY(base(r.base()) == a);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowIncrement<true, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
	{
		using Iter = MayThrowIncrement<true, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
	{
		using Iter = MayThrowIncrement<false, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
	{
		using Iter = MayThrowIncrement<false, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
#endif

	return true;
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPostIncrementTest2()
{
	int a[] = {1,2,3,4,5};

	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a}};
		static_assert(hamon::is_same<decltype(it++), void>::value, "");
		VERIFY(base(it.base()) == a);
		it++;
		VERIFY(base(it.base()) == a+1);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowIncrement<true, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
	{
		using Iter = MayThrowIncrement<true, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
	{
		using Iter = MayThrowIncrement<false, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
	{
		using Iter = MayThrowIncrement<false, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()++);
	}
#endif
	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostIncrementTest2<input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostIncrementTest<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostIncrementTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostIncrementTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostIncrementTest<contiguous_iterator_wrapper>());
}

template <bool NoexceptCopy, bool NoexceptDecrement, typename T, template <typename> class IteratorWrapper>
struct MayThrowDecrement : public IteratorWrapper<T>
{
	MayThrowDecrement() = default;
	MayThrowDecrement(MayThrowDecrement const&) noexcept(NoexceptCopy);
	MayThrowDecrement& operator--() noexcept(NoexceptDecrement);
	MayThrowDecrement  operator--(int) noexcept(NoexceptDecrement);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPreDecrementTest()
{
	int a[] = {1,2,3,4,5};
	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a+3}};
		static_assert(hamon::is_same<decltype(--it), hamon::move_iterator<It>&>::value, "");
		VERIFY(base(it.base()) == a+3);
		auto r = --it;
		VERIFY(base(it.base()) == a+2);
		VERIFY(base(r.base()) == a+2);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowDecrement<true, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(--hamon::declval<hamon::move_iterator<Iter>>());
	}
	{
		using Iter = MayThrowDecrement<true, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(--hamon::declval<hamon::move_iterator<Iter>>());
	}
	{
		using Iter = MayThrowDecrement<false, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(--hamon::declval<hamon::move_iterator<Iter>>());
	}
	{
		using Iter = MayThrowDecrement<false, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(--hamon::declval<hamon::move_iterator<Iter>>());
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorPreDecrementTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreDecrementTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreDecrementTest<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreDecrementTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreDecrementTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPreDecrementTest<contiguous_iterator_wrapper>());
}

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPostDecrementTest()
{
	int a[] = {1,2,3,4,5};
	using It = IteratorWrapper<int>;
	{
		hamon::move_iterator<It> it{It{a+3}};
		static_assert(hamon::is_same<decltype(it--), hamon::move_iterator<It>>::value, "");
		VERIFY(base(it.base()) == a+3);
		auto r = it--;
		VERIFY(base(it.base()) == a+2);
		VERIFY(base(r.base()) == a+3);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowDecrement<true, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::move_iterator<Iter>>()--);
	}
	{
		using Iter = MayThrowDecrement<true, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()--);
	}
	{
		using Iter = MayThrowDecrement<false, true, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()--);
	}
	{
		using Iter = MayThrowDecrement<false, false, int, IteratorWrapper>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::move_iterator<Iter>>()--);
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorPostDecrementTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostDecrementTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostDecrementTest<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostDecrementTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostDecrementTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPostDecrementTest<contiguous_iterator_wrapper>());
}

template <bool NoexceptCtor, bool NoexceptPlus, typename T, template <typename> class IteratorWrapper>
struct MayThrowPlus : public IteratorWrapper<T>
{
	using pointer = typename IteratorWrapper<T>::pointer;
	using difference_type = typename IteratorWrapper<T>::difference_type;

	MayThrowPlus() = default;
	MayThrowPlus(pointer p) noexcept(NoexceptCtor);
	MayThrowPlus(MayThrowPlus const&) noexcept(NoexceptCtor);
	MayThrowPlus operator+(difference_type n) const noexcept(NoexceptPlus);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPlusTest()
{
	int a[] = {1,2,3,4,5};
	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a}};
		static_assert(hamon::is_same<decltype(it + 2), hamon::move_iterator<It>>::value, "");
		VERIFY(base(it.base()) == a);
		auto r = it + 2;
		VERIFY(base(it.base()) == a);
		VERIFY(base(r.base()) == a+2);
	}
	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a}};
		static_assert(hamon::is_same<decltype(3 + it), hamon::move_iterator<It>>::value, "");
		VERIFY(base(it.base()) == a);
		auto r = 3 + it;
		VERIFY(base(it.base()) == a);
		VERIFY(base(r.base()) == a+3);
	}
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowPlus<true, true, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter>() + 1);
		HAMON_ASSERT_NOEXCEPT_TRUE(1 + hamon::declval<MoveIter>());
	}
	{
		using Iter = MayThrowPlus<true, false, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter>() + 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(1 + hamon::declval<MoveIter>());
	}
	{
		using Iter = MayThrowPlus<false, true, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter>() + 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(1 + hamon::declval<MoveIter>());
	}
	{
		using Iter = MayThrowPlus<false, false, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter>() + 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(1 + hamon::declval<MoveIter>());
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorPlusTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusTest<forward_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusTest<contiguous_iterator_wrapper>());

	{
		int a[] = {1,2,3,4,5};
		hamon::move_iterator<int*> it{a};
		static_assert(hamon::is_same<decltype(it + 1), hamon::move_iterator<int*>>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it + 1);
		HAMON_ASSERT_NOEXCEPT_TRUE(1 + it);
#endif
		auto r = it + 2;
		EXPECT_TRUE(base(it.base()) == a);
		EXPECT_TRUE(base(r.base()) == a+2);
	}
}

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowNext : public IteratorWrapper<T>
{
	using difference_type = typename IteratorWrapper<T>::difference_type;
	MayThrowNext& operator+=(difference_type n) const noexcept(Noexcept);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorPlusAssignTest()
{
	int a[] = {1,2,3,4,5};

	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a}};
		static_assert(hamon::is_same<decltype(it += 2), hamon::move_iterator<It>&>::value, "");
		VERIFY(base(it.base()) == a);
		auto r = (it += 2);
		VERIFY(base(it.base()) == a+2);
		VERIFY(base(r.base()) == a+2);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowNext<true, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter&>() += 1);
	}
	{
		using Iter = MayThrowNext<false, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter&>() += 1);
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorPlusAssignTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusAssignTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusAssignTest<forward_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusAssignTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusAssignTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorPlusAssignTest<contiguous_iterator_wrapper>());

	{
		int a[] = {1,2,3,4,5};
		hamon::move_iterator<int*> it{a};
		static_assert(hamon::is_same<decltype(it += 2), hamon::move_iterator<int*>&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it += 1);
#endif
		EXPECT_TRUE(base(it.base()) == a);
		auto r = (it += 2);
		EXPECT_TRUE(base(it.base()) == a+2);
		EXPECT_TRUE(base(r.base()) == a+2);
	}
}

template <bool NoexceptCtor, bool NoexceptMinus, typename T, template <typename> class IteratorWrapper>
struct MayThrowMinus : public IteratorWrapper<T>
{
	using pointer = typename IteratorWrapper<T>::pointer;
	using difference_type = typename IteratorWrapper<T>::difference_type;

	MayThrowMinus() = default;
	MayThrowMinus(pointer p) noexcept(NoexceptCtor);
	MayThrowMinus(MayThrowMinus const&) noexcept(NoexceptCtor);
	MayThrowMinus operator-(difference_type n) const noexcept(NoexceptMinus);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorMinusTest()
{
	int a[] = {1,2,3,4,5};
	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a+3}};
		static_assert(hamon::is_same<decltype(it - 2), hamon::move_iterator<It>>::value, "");
		VERIFY(base(it.base()) == a+3);
		auto r = it - 2;
		VERIFY(base(it.base()) == a+3);
		VERIFY(base(r.base()) == a+1);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowMinus<true, true, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter>() - 1);
	}
	{
		using Iter = MayThrowMinus<true, false, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter>() - 1);
	}
	{
		using Iter = MayThrowMinus<false, true, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter>() - 1);
	}
	{
		using Iter = MayThrowMinus<false, false, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter>() - 1);
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorMinusTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<forward_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<contiguous_iterator_wrapper>());

	int a[] = {1,2,3,4,5};
	{
		hamon::move_iterator<int*> it{a+3};
		static_assert(hamon::is_same<decltype(it - 1), hamon::move_iterator<int*>>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it - 1);
#endif
		auto r = it - 1;
		EXPECT_TRUE(base(it.base()) == a+3);
		EXPECT_TRUE(base(r.base()) == a+2);
	}
}

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowSubtract : public IteratorWrapper<T>
{
	using difference_type = typename IteratorWrapper<T>::difference_type;

	template <bool B>
	friend difference_type
	operator-(MayThrowSubtract const&, MayThrowSubtract<B, T, IteratorWrapper> const&)
		noexcept(B && Noexcept);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorSubtractTest()
{
	int a[] = {1,2,3,4,5};
	using It = IteratorWrapper<int>;
	using Difference = hamon::iter_difference_t<It>;
	{
		hamon::move_iterator<It> it1{It{a+3}};
		hamon::move_iterator<It> it2{It{a+1}};
		static_assert(hamon::is_same<decltype(it1 - it2), Difference>::value, "");
		auto n = it1 - it2;
		VERIFY(n == 2);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter1 = MayThrowSubtract<true, int, IteratorWrapper>;
		using Iter2 = MayThrowSubtract<true, int, IteratorWrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1>() - hamon::declval<MoveIter2>());
	}
	{
		using Iter1 = MayThrowSubtract<true,  int, IteratorWrapper>;
		using Iter2 = MayThrowSubtract<false, int, IteratorWrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1>() - hamon::declval<MoveIter2>());
	}
	{
		using Iter1 = MayThrowSubtract<false, int, IteratorWrapper>;
		using Iter2 = MayThrowSubtract<true,  int, IteratorWrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1>() - hamon::declval<MoveIter2>());
	}
	{
		using Iter1 = MayThrowSubtract<false, int, IteratorWrapper>;
		using Iter2 = MayThrowSubtract<false, int, IteratorWrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1>() - hamon::declval<MoveIter2>());
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorSubtractTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSubtractTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSubtractTest<forward_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSubtractTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSubtractTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSubtractTest<contiguous_iterator_wrapper>());

	int a[] = {1,2,3,4,5};
	{
		hamon::move_iterator<int*> it1{a+3};
		hamon::move_iterator<int*> it2{a+1};
		static_assert(hamon::is_same<decltype(it1 - it2), hamon::ptrdiff_t>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it1 - it2);
#endif
		auto n = it1 - it2;
		EXPECT_TRUE(n == 2);
	}
	{
		hamon::move_iterator<int*> it1{a+3};
		hamon::move_iterator<int const*> it2{a+1};
		static_assert(hamon::is_same<decltype(it1 - it2), hamon::ptrdiff_t>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it1 - it2);
#endif
		auto n = it1 - it2;
		EXPECT_TRUE(n == 2);
	}
}

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowPrev : public IteratorWrapper<T>
{
	using difference_type = typename IteratorWrapper<T>::difference_type;
	MayThrowPrev& operator-=(difference_type n) const noexcept(Noexcept);
};

template <template <typename> class IteratorWrapper>
inline HAMON_CXX14_CONSTEXPR bool OperatorMinusAssignTest()
{
	int a[] = {1,2,3,4,5};
	{
		using It = IteratorWrapper<int>;
		hamon::move_iterator<It> it{It{a+3}};
		static_assert(hamon::is_same<decltype(it -= 2), hamon::move_iterator<It>&>::value, "");
		VERIFY(base(it.base()) == a+3);
		auto r = (it -= 2);
		VERIFY(base(it.base()) == a+1);
		VERIFY(base(r.base()) == a+1);
	}

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = MayThrowPrev<true, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter&>() -= 1);
	}
	{
		using Iter = MayThrowPrev<false, int, IteratorWrapper>;
		using MoveIter = hamon::move_iterator<Iter>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter&>() -= 1);
	}
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorMinusAssignTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusAssignTest<input_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusAssignTest<forward_iterator_wrapper>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusAssignTest<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusAssignTest<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusAssignTest<contiguous_iterator_wrapper>());

	{
		int a[] = {1,2,3,4,5};
		hamon::move_iterator<int*> it{a+3};
		static_assert(hamon::is_same<decltype(it -= 2), hamon::move_iterator<int*>&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		HAMON_ASSERT_NOEXCEPT_TRUE(it -= 1);
#endif
		EXPECT_TRUE(base(it.base()) == a+3);
		auto r = (it -= 2);
		EXPECT_TRUE(base(it.base()) == a+1);
		EXPECT_TRUE(base(r.base()) == a+1);
	}
}

template <typename T, typename U>
using HasEq = decltype(hamon::declval<T const&>() == hamon::declval<U const&>());
template <typename T, typename U>
using HasNe = decltype(hamon::declval<T const&>() != hamon::declval<U const&>());
template <typename T, typename U>
using HasLt = decltype(hamon::declval<T const&>() < hamon::declval<U const&>());
template <typename T, typename U>
using HasGt = decltype(hamon::declval<T const&>() > hamon::declval<U const&>());
template <typename T, typename U>
using HasLe = decltype(hamon::declval<T const&>() <= hamon::declval<U const&>());
template <typename T, typename U>
using HasGe = decltype(hamon::declval<T const&>() >= hamon::declval<U const&>());

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct MayThrowCompare : public IteratorWrapper<T>
{
	template <bool B>
	bool operator==(MayThrowCompare<B, T, IteratorWrapper> const&) const
		noexcept(Noexcept && B);

	template <bool B>
	bool operator<(MayThrowCompare<B, T, IteratorWrapper> const&) const
		noexcept(Noexcept && B);
};

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool OperatorEqNeTest()
{
	int a[] = {3,1,4};
	hamon::move_iterator<Iter> i1{Iter{a+0}};
	hamon::move_iterator<Iter> i2{Iter{a+0}};
	hamon::move_iterator<Iter> i3{Iter{a+1}};
	hamon::move_iterator<Iter> i4{Iter{a+2}};

	VERIFY( (i1 == i1));
	VERIFY( (i1 == i2));
	VERIFY(!(i1 == i3));
	VERIFY(!(i1 == i4));

	VERIFY(!(i1 != i1));
	VERIFY(!(i1 != i2));
	VERIFY( (i1 != i3));
	VERIFY( (i1 != i4));

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorEqNeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<input_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<forward_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<bidirectional_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<random_access_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<contiguous_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<int*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorEqNeTest<int const*>());

	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<int*>, hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<int*>, hamon::move_iterator<int const*>>::value, "");
	static_assert(!hamon::is_detected<HasEq, hamon::move_iterator<int*>, hamon::move_iterator<char*>>::value, "");
	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<input_iterator_wrapper<int>>,         hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<forward_iterator_wrapper<int>>,       hamon::move_iterator<forward_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<bidirectional_iterator_wrapper<int>>, hamon::move_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<random_access_iterator_wrapper<int>>, hamon::move_iterator<random_access_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasEq, hamon::move_iterator<contiguous_iterator_wrapper<int>>,    hamon::move_iterator<contiguous_iterator_wrapper<int>>>::value, "");

	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<int*>, hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<int*>, hamon::move_iterator<int const*>>::value, "");
	static_assert(!hamon::is_detected<HasNe, hamon::move_iterator<int*>, hamon::move_iterator<char*>>::value, "");
	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<input_iterator_wrapper<int>>,         hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<forward_iterator_wrapper<int>>,       hamon::move_iterator<forward_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<bidirectional_iterator_wrapper<int>>, hamon::move_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<random_access_iterator_wrapper<int>>, hamon::move_iterator<random_access_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasNe, hamon::move_iterator<contiguous_iterator_wrapper<int>>,    hamon::move_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using MoveIter = hamon::move_iterator<int*>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() == hamon::declval<MoveIter const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() != hamon::declval<MoveIter const&>());
	}
	{
		using Iter1 = MayThrowCompare<true, int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<true, int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1 const&>() == hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1 const&>() != hamon::declval<MoveIter2 const&>());
	}
	{
		using Iter1 = MayThrowCompare<true,  int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() == hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() != hamon::declval<MoveIter2 const&>());
	}
	{
		using Iter1 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<true,  int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() == hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() != hamon::declval<MoveIter2 const&>());
	}
	{
		using Iter1 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() == hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() != hamon::declval<MoveIter2 const&>());
	}
#endif
}

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool OperatorLtGtTest()
{
	int a[] = {3,1,4};
	hamon::move_iterator<Iter> i1{Iter{a+0}};
	hamon::move_iterator<Iter> i2{Iter{a+0}};
	hamon::move_iterator<Iter> i3{Iter{a+1}};
	hamon::move_iterator<Iter> i4{Iter{a+2}};

	VERIFY(!(i1 < i1));
	VERIFY(!(i1 < i2));
	VERIFY( (i1 < i3));
	VERIFY( (i1 < i4));

	VERIFY(!(i2 < i1));
	VERIFY(!(i2 < i2));
	VERIFY( (i2 < i3));
	VERIFY( (i2 < i4));

	VERIFY(!(i3 < i1));
	VERIFY(!(i3 < i2));
	VERIFY(!(i3 < i3));
	VERIFY( (i3 < i4));

	VERIFY(!(i4 < i1));
	VERIFY(!(i4 < i2));
	VERIFY(!(i4 < i3));
	VERIFY(!(i4 < i4));

	VERIFY( (i1 <= i1));
	VERIFY( (i1 <= i2));
	VERIFY( (i1 <= i3));
	VERIFY( (i1 <= i4));

	VERIFY( (i2 <= i1));
	VERIFY( (i2 <= i2));
	VERIFY( (i2 <= i3));
	VERIFY( (i2 <= i4));

	VERIFY(!(i3 <= i1));
	VERIFY(!(i3 <= i2));
	VERIFY( (i3 <= i3));
	VERIFY( (i3 <= i4));

	VERIFY(!(i4 <= i1));
	VERIFY(!(i4 <= i2));
	VERIFY(!(i4 <= i3));
	VERIFY( (i4 <= i4));

	VERIFY(!(i1 > i1));
	VERIFY(!(i1 > i2));
	VERIFY(!(i1 > i3));
	VERIFY(!(i1 > i4));

	VERIFY(!(i2 > i1));
	VERIFY(!(i2 > i2));
	VERIFY(!(i2 > i3));
	VERIFY(!(i2 > i4));

	VERIFY( (i3 > i1));
	VERIFY( (i3 > i2));
	VERIFY(!(i3 > i3));
	VERIFY(!(i3 > i4));

	VERIFY( (i4 > i1));
	VERIFY( (i4 > i2));
	VERIFY( (i4 > i3));
	VERIFY(!(i4 > i4));

	VERIFY( (i1 >= i1));
	VERIFY( (i1 >= i2));
	VERIFY(!(i1 >= i3));
	VERIFY(!(i1 >= i4));

	VERIFY( (i2 >= i1));
	VERIFY( (i2 >= i2));
	VERIFY(!(i2 >= i3));
	VERIFY(!(i2 >= i4));

	VERIFY( (i3 >= i1));
	VERIFY( (i3 >= i2));
	VERIFY( (i3 >= i3));
	VERIFY(!(i3 >= i4));

	VERIFY( (i4 >= i1));
	VERIFY( (i4 >= i2));
	VERIFY( (i4 >= i3));
	VERIFY( (i4 >= i4));

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorLtGtTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<input_iterator_wrapper<int>>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<forward_iterator_wrapper<int>>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<bidirectional_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<random_access_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<contiguous_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<int*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorLtGtTest<int const*>());

	static_assert( hamon::is_detected<HasLt, hamon::move_iterator<int*>, hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_detected<HasLt, hamon::move_iterator<int*>, hamon::move_iterator<int const*>>::value, "");
	static_assert(!hamon::is_detected<HasLt, hamon::move_iterator<input_iterator_wrapper<int>>,         hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasLt, hamon::move_iterator<forward_iterator_wrapper<int>>,       hamon::move_iterator<forward_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasLt, hamon::move_iterator<bidirectional_iterator_wrapper<int>>, hamon::move_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasLt, hamon::move_iterator<random_access_iterator_wrapper<int>>, hamon::move_iterator<random_access_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasLt, hamon::move_iterator<contiguous_iterator_wrapper<int>>,    hamon::move_iterator<contiguous_iterator_wrapper<int>>>::value, "");

	static_assert( hamon::is_detected<HasGt, hamon::move_iterator<int*>, hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_detected<HasGt, hamon::move_iterator<int*>, hamon::move_iterator<int const*>>::value, "");
	static_assert(!hamon::is_detected<HasGt, hamon::move_iterator<input_iterator_wrapper<int>>,         hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasGt, hamon::move_iterator<forward_iterator_wrapper<int>>,       hamon::move_iterator<forward_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasGt, hamon::move_iterator<bidirectional_iterator_wrapper<int>>, hamon::move_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasGt, hamon::move_iterator<random_access_iterator_wrapper<int>>, hamon::move_iterator<random_access_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasGt, hamon::move_iterator<contiguous_iterator_wrapper<int>>,    hamon::move_iterator<contiguous_iterator_wrapper<int>>>::value, "");

	static_assert( hamon::is_detected<HasLe, hamon::move_iterator<int*>, hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_detected<HasLe, hamon::move_iterator<int*>, hamon::move_iterator<int const*>>::value, "");
	static_assert(!hamon::is_detected<HasLe, hamon::move_iterator<input_iterator_wrapper<int>>,         hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasLe, hamon::move_iterator<forward_iterator_wrapper<int>>,       hamon::move_iterator<forward_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasLe, hamon::move_iterator<bidirectional_iterator_wrapper<int>>, hamon::move_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasLe, hamon::move_iterator<random_access_iterator_wrapper<int>>, hamon::move_iterator<random_access_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasLe, hamon::move_iterator<contiguous_iterator_wrapper<int>>,    hamon::move_iterator<contiguous_iterator_wrapper<int>>>::value, "");

	static_assert( hamon::is_detected<HasGe, hamon::move_iterator<int*>, hamon::move_iterator<int*>>::value, "");
	static_assert( hamon::is_detected<HasGe, hamon::move_iterator<int*>, hamon::move_iterator<int const*>>::value, "");
	static_assert(!hamon::is_detected<HasGe, hamon::move_iterator<input_iterator_wrapper<int>>,         hamon::move_iterator<input_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasGe, hamon::move_iterator<forward_iterator_wrapper<int>>,       hamon::move_iterator<forward_iterator_wrapper<int>>>::value, "");
	static_assert(!hamon::is_detected<HasGe, hamon::move_iterator<bidirectional_iterator_wrapper<int>>, hamon::move_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasGe, hamon::move_iterator<random_access_iterator_wrapper<int>>, hamon::move_iterator<random_access_iterator_wrapper<int>>>::value, "");
	static_assert( hamon::is_detected<HasGe, hamon::move_iterator<contiguous_iterator_wrapper<int>>,    hamon::move_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 110000))
	// gcc10 でコンパイルエラーになってしまう
	static_assert(!hamon::is_detected<HasLt, hamon::move_iterator<int*>, hamon::move_iterator<char*>>::value, "");
	static_assert(!hamon::is_detected<HasGt, hamon::move_iterator<int*>, hamon::move_iterator<char*>>::value, "");
	static_assert(!hamon::is_detected<HasLe, hamon::move_iterator<int*>, hamon::move_iterator<char*>>::value, "");
	static_assert(!hamon::is_detected<HasGe, hamon::move_iterator<int*>, hamon::move_iterator<char*>>::value, "");
#endif

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using MoveIter = hamon::move_iterator<int*>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() <  hamon::declval<MoveIter const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() >  hamon::declval<MoveIter const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() <= hamon::declval<MoveIter const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() >= hamon::declval<MoveIter const&>());
	}
	{
		using Iter1 = MayThrowCompare<true, int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<true, int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1 const&>() <  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1 const&>() >  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1 const&>() <= hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter1 const&>() >= hamon::declval<MoveIter2 const&>());
	}
	{
		using Iter1 = MayThrowCompare<true,  int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() <  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() >  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() <= hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() >= hamon::declval<MoveIter2 const&>());
	}
	{
		using Iter1 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<true,  int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() <  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() >  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() <= hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() >= hamon::declval<MoveIter2 const&>());
	}
	{
		using Iter1 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using Iter2 = MayThrowCompare<false, int, input_iterator_wrapper>;
		using MoveIter1 = hamon::move_iterator<Iter1>;
		using MoveIter2 = hamon::move_iterator<Iter2>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() <  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() >  hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() <= hamon::declval<MoveIter2 const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<MoveIter1 const&>() >= hamon::declval<MoveIter2 const&>());
	}
#endif
}

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool OperatorSpaceshipTest()
{
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	int a[] = {3,1,4};
	hamon::move_iterator<Iter> i1{Iter(a+0)};
	hamon::move_iterator<Iter> i2{Iter(a+0)};
	hamon::move_iterator<Iter> i3{Iter(a+1)};
	hamon::move_iterator<Iter> i4{Iter(a+2)};

	VERIFY( (i1 <=> i1) == 0);
	VERIFY( (i1 <=> i2) == 0);
	VERIFY( (i1 <=> i3) <  0);
	VERIFY( (i1 <=> i4) <  0);

	VERIFY( (i2 <=> i1) == 0);
	VERIFY( (i2 <=> i2) == 0);
	VERIFY( (i2 <=> i3) <  0);
	VERIFY( (i2 <=> i4) <  0);

	VERIFY( (i3 <=> i1) >  0);
	VERIFY( (i3 <=> i2) >  0);
	VERIFY( (i3 <=> i3) == 0);
	VERIFY( (i3 <=> i4) <  0);

	VERIFY( (i4 <=> i1) >  0);
	VERIFY( (i4 <=> i2) >  0);
	VERIFY( (i4 <=> i3) >  0);
	VERIFY( (i4 <=> i4) == 0);
#endif

	return true;
}

GTEST_TEST(MoveIteratorTest, OperatorSpaceshipTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSpaceshipTest<int*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorSpaceshipTest<int const*>());

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using MoveIter = hamon::move_iterator<int*>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<MoveIter const&>() <=> hamon::declval<MoveIter const&>());
	}
#endif
#endif
}

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct CustomIterMove : public IteratorWrapper<T>
{
public:
	using pointer = typename IteratorWrapper<T>::pointer;

	HAMON_CXX14_CONSTEXPR CustomIterMove(pointer p)
		: IteratorWrapper<T>{p}
	{}

	friend HAMON_CXX14_CONSTEXPR T&&
	iter_move(CustomIterMove const& it)
		noexcept(Noexcept)
	{
		return hamon::move(*base(it));
	}
};

inline HAMON_CXX14_CONSTEXPR bool IterMoveTest()
{
	{
		int a[] = {1, 2, 3};
		hamon::move_iterator<int*> it{a};
		VERIFY(iter_move(it) == 1);
		VERIFY(hamon::ranges::iter_move(it) == 1);
		++it;
		VERIFY(iter_move(it) == 2);
		VERIFY(hamon::ranges::iter_move(it) == 2);
	}
	{
		using Iter = CustomIterMove<true, int, input_iterator_wrapper>;
		int a[] = {1, 2, 3};
		hamon::move_iterator<Iter> it{Iter{a}};
		VERIFY(iter_move(it) == 1);
		VERIFY(hamon::ranges::iter_move(it) == 1);
		HAMON_ASSERT_NOEXCEPT_TRUE(iter_move(it));
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::ranges::iter_move(it));
		++it;
		VERIFY(iter_move(it) == 2);
		VERIFY(hamon::ranges::iter_move(it) == 2);
	}
	{
		using Iter = CustomIterMove<false, int, input_iterator_wrapper>;
		int a[] = {1, 2, 3};
		hamon::move_iterator<Iter> it{Iter{a}};
		VERIFY(iter_move(it) == 1);
		VERIFY(hamon::ranges::iter_move(it) == 1);
		HAMON_ASSERT_NOEXCEPT_FALSE(iter_move(it));
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::ranges::iter_move(it));
		++it;
		VERIFY(iter_move(it) == 2);
		VERIFY(hamon::ranges::iter_move(it) == 2);
	}
	return true;
}

GTEST_TEST(MoveIteratorTest, IterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IterMoveTest());
}

template <bool Noexcept, typename T, template <typename> class IteratorWrapper>
struct CustomIterSwap : public IteratorWrapper<T>
{
public:
	using pointer = typename IteratorWrapper<T>::pointer;

	HAMON_CXX14_CONSTEXPR CustomIterSwap(pointer p)
		: IteratorWrapper<T>{p}
	{}

	template <bool Noexcept2>
	friend HAMON_CXX14_CONSTEXPR void
	iter_swap(CustomIterSwap const& lhs, CustomIterSwap<Noexcept2, T, IteratorWrapper> const& rhs)
		noexcept(Noexcept && Noexcept2)
	{
		return hamon::ranges::iter_swap(base(lhs), base(rhs));
	}
};

inline HAMON_CXX14_CONSTEXPR bool IterSwapTest()
{
	{
		int a[] = {1, 2, 3};
		hamon::move_iterator<int*> it1{a+0};
		hamon::move_iterator<int*> it2{a+1};

		VERIFY(a[0] == 1);
		VERIFY(a[1] == 2);
		VERIFY(a[2] == 3);

		static_assert(hamon::is_same<decltype(iter_swap(it1, it2)), void>::value, "");
		iter_swap(it1, it2);

		VERIFY(a[0] == 2);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 3);
	}
	{
		using Iter = CustomIterSwap<true, int, input_iterator_wrapper>;
		int a[] = {1, 2, 3};
		hamon::move_iterator<Iter> it1{Iter{a+0}};
		hamon::move_iterator<Iter> it2{Iter{a+1}};

		VERIFY(a[0] == 1);
		VERIFY(a[1] == 2);
		VERIFY(a[2] == 3);

		static_assert(hamon::is_same<decltype(iter_swap(it1, it2)), void>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(iter_swap(it1, it2));
		iter_swap(it1, it2);

		VERIFY(a[0] == 2);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 3);
	}
	{
		using Iter = CustomIterSwap<false, int, input_iterator_wrapper>;
		int a[] = {1, 2, 3};
		hamon::move_iterator<Iter> it1{Iter{a+0}};
		hamon::move_iterator<Iter> it2{Iter{a+1}};

		VERIFY(a[0] == 1);
		VERIFY(a[1] == 2);
		VERIFY(a[2] == 3);

		static_assert(hamon::is_same<decltype(iter_swap(it1, it2)), void>::value, "");
		HAMON_ASSERT_NOEXCEPT_FALSE(iter_swap(it1, it2));
		iter_swap(it1, it2);

		VERIFY(a[0] == 2);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 3);
	}
	{
		using Iter1 = CustomIterSwap<true,  int, input_iterator_wrapper>;
		using Iter2 = CustomIterSwap<false, int, input_iterator_wrapper>;
		int a[] = {1, 2, 3};
		hamon::move_iterator<Iter1> it1{Iter1{a+0}};
		hamon::move_iterator<Iter2> it2{Iter2{a+1}};

		VERIFY(a[0] == 1);
		VERIFY(a[1] == 2);
		VERIFY(a[2] == 3);

		static_assert(hamon::is_same<decltype(iter_swap(it1, it2)), void>::value, "");
		HAMON_ASSERT_NOEXCEPT_FALSE(iter_swap(it1, it2));
		iter_swap(it1, it2);

		VERIFY(a[0] == 2);
		VERIFY(a[1] == 1);
		VERIFY(a[2] == 3);
	}
	return true;
}

GTEST_TEST(MoveIteratorTest, IterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IterSwapTest());
}

#undef VERIFY

}	// namespace move_iterator_test

}	// namespace hamon_iterator_test
