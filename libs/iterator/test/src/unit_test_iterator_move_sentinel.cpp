/**
 *	@file	unit_test_iterator_move_sentinel.cpp
 *
 *	@brief	move_sentinel のテスト
 */

#include <hamon/iterator/move_sentinel.hpp>
#include <hamon/iterator/move_iterator.hpp>
#include <hamon/iterator/default_sentinel.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_iterator_test
{

namespace move_sentinel_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if 0//defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept HasMoveSentinel =
requires
{
	typename hamon::move_sentinel<T>;
};

#else

template <typename T>
struct HasMoveSentinelImpl
{
private:
	template <typename U,
		typename = hamon::move_sentinel<U>
	>
	static auto test(int) -> std::true_type;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using HasMoveSentinel =
	typename HasMoveSentinelImpl<T>::type;

#endif

struct Semiregular {};

struct NotSemiregular
{
	NotSemiregular(int);
};

static_assert( HasMoveSentinel<int>::value, "");
static_assert( HasMoveSentinel<int*>::value, "");
static_assert( HasMoveSentinel<Semiregular>::value, "");
static_assert(!HasMoveSentinel<NotSemiregular>::value, "");

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
// CTAD test
static_assert(std::is_same<
	decltype(hamon::move_sentinel(hamon::default_sentinel_t{})),
	hamon::move_sentinel<hamon::default_sentinel_t>>::value, "");

static_assert(std::is_same<
	decltype(hamon::move_sentinel(test_sentinel<int*>{})),
	hamon::move_sentinel<test_sentinel<int*>>>::value, "");
#endif

GTEST_TEST(MoveSentinelTest, ConceptTest)
{
	// Pointer.
	{
		using It = int*;
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
	}

	// `std::input_iterator`.
	{
		using It = input_iterator_wrapper<int>;
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
	}

	// `std::forward_iterator`.
	{
		using It = forward_iterator_wrapper<int>;
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
	}

	// `std::bidirectional_iterator`.
	{
		using It = bidirectional_iterator_wrapper<int>;
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		static_assert(!hamon::sized_sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
	}

	// `std::random_access_iterator`.
	{
		using It = random_access_iterator_wrapper<int>;
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
	}

	// `std::contiguous_iterator`.
	{
		using It = contiguous_iterator_wrapper<int>;
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<It>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<test_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
		//static_assert( hamon::sized_sentinel_for_t<hamon::move_sentinel<sized_sentinel<It>>, hamon::move_iterator<It>>::value, "");
	}
}

inline HAMON_CXX14_CONSTEXPR bool CtorDefaultTest()
{
	// The underlying sentinel is an integer.
	{
		static_assert(std::is_nothrow_default_constructible<hamon::move_sentinel<int>>::value, "");
		hamon::move_sentinel<int> m;
		VERIFY(m.base() == 0);
	}

	// The underlying sentinel is a pointer.
	{
		static_assert(std::is_nothrow_default_constructible<hamon::move_sentinel<int*>>::value, "");
		hamon::move_sentinel<int*> m;
		VERIFY(m.base() == nullptr);
	}

	// The underlying sentinel is a user-defined type with an explicit default constructor.
	{
		struct S
		{
			explicit S() = default;
			int i = 3;
		};
		static_assert(std::is_nothrow_default_constructible<hamon::move_sentinel<S>>::value, "");
		hamon::move_sentinel<S> m;
		VERIFY(m.base().i == 3);
	}

	{
		struct S
		{
			S() noexcept(false);
		};
		static_assert(std::is_default_constructible<hamon::move_sentinel<S>>::value, "");
		static_assert(!std::is_nothrow_default_constructible<hamon::move_sentinel<S>>::value, "");
	}

	return true;
}

GTEST_TEST(MoveSentinelTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorDefaultTest());
}

inline HAMON_CXX14_CONSTEXPR bool CtorSentinelTest()
{
	// The underlying sentinel is an integer.
	{
		using Sent = hamon::move_sentinel<int>;
		static_assert(!std::is_convertible<int, Sent>::value, "");
		static_assert( std::is_constructible<Sent, int>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<Sent, int>::value, "");
#endif
		Sent m(42);
		VERIFY(m.base() == 42);
	}

	// The underlying sentinel is a pointer.
	{
		using Sent = hamon::move_sentinel<int*>;
		static_assert(!std::is_convertible<int*, Sent>::value, "");
		static_assert( std::is_constructible<Sent, int*>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<Sent, int*>::value, "");
#endif
		int i = 42;
		Sent m(&i);
		VERIFY(m.base() == &i);
	}

	// The underlying sentinel is a user-defined type with an explicit default constructor.
	{
		struct S {
			explicit S() = default;
			constexpr explicit S(int j) : i(j) {}
			int i = 3;
		};
		using Sent = hamon::move_sentinel<S>;
		static_assert(!std::is_convertible<S, Sent>::value, "");
		static_assert( std::is_constructible<Sent, S>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<Sent, S>::value, "");
#endif
		Sent m(S(42));
		VERIFY(m.base().i == 42);
	}

	{
		struct S
		{
			S() = default;
			S(S const&) = default;
			S& operator=(S const&) = default;
			S(S &&)     noexcept(true);
		};
		using Sent = hamon::move_sentinel<S>;
		static_assert(!std::is_convertible<S, Sent>::value, "");
		static_assert( std::is_constructible<Sent, S>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<Sent, S>::value, "");
#endif
	}
	{
		struct S
		{
			S() = default;
			S(S const&) = default;
			S& operator=(S const&) = default;
			S(S &&) noexcept(false);
		};
		using Sent = hamon::move_sentinel<S>;
		static_assert(!std::is_convertible<S, Sent>::value, "");
		static_assert( std::is_constructible<Sent, S>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert(!std::is_nothrow_constructible<Sent, S>::value, "");
#endif
	}

	return true;
}

GTEST_TEST(MoveSentinelTest, CtorSentinelTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorSentinelTest());
}

struct NonConvertible
{
	explicit NonConvertible();
	NonConvertible(int i);
	explicit NonConvertible(long i) = delete;
};
static_assert( hamon::semiregular_t<NonConvertible>::value, "");
static_assert( std::is_convertible<long, NonConvertible>::value, "");
static_assert(!hamon::convertible_to_t<long, NonConvertible>::value, "");

inline HAMON_CXX14_CONSTEXPR bool CtorConvertTest()
{
	// Constructing from an lvalue.
	{
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<
			hamon::move_sentinel<long>,
			hamon::move_sentinel<int> const&
		>::value, "");
#endif
		hamon::move_sentinel<int> m(42);
		hamon::move_sentinel<long> m2 = m;
		VERIFY(m2.base() == 42L);
	}

	// Constructing from an rvalue.
	{
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<
			hamon::move_sentinel<long>,
			hamon::move_sentinel<int>&&
		>::value, "");
#endif
		hamon::move_sentinel<long> m2 = hamon::move_sentinel<int>(43);
		VERIFY(m2.base() == 43L);
	}

	{
		struct S1
		{
			S1() = default;
			S1(S1 const&) = default;
			S1& operator=(S1 const&) = default;
		};
		struct S2
		{
			S2() = default;
			S2(S2 const&) = default;
			S2& operator=(S2 const&) = default;

			S2(S1 const&) noexcept(true);
		};
		using Sent1 = hamon::move_sentinel<S1>;
		using Sent2 = hamon::move_sentinel<S2>;
		static_assert( std::is_constructible<Sent2, Sent1 const&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_constructible<Sent2, Sent1 const&>::value, "");
#endif
	}
	{
		struct S1
		{
			S1() = default;
			S1(S1 const&) = default;
			S1& operator=(S1 const&) = default;
		};
		struct S2
		{
			S2() = default;
			S2(S2 const&) = default;
			S2& operator=(S2 const&) = default;

			S2(S1 const&) noexcept(false);
		};
		using Sent1 = hamon::move_sentinel<S1>;
		using Sent2 = hamon::move_sentinel<S2>;
		static_assert( std::is_constructible<Sent2, Sent1 const&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert(!std::is_nothrow_constructible<Sent2, Sent1 const&>::value, "");
#endif
	}

	// SFINAE checks.
	{
		static_assert( std::is_convertible<hamon::move_sentinel<int>, hamon::move_sentinel<long>>::value, "");
		static_assert( std::is_convertible<hamon::move_sentinel<int*>, hamon::move_sentinel<const int*>>::value, "");
		static_assert(!std::is_convertible<hamon::move_sentinel<const int*>, hamon::move_sentinel<int*>>::value, "");
		static_assert( std::is_convertible<hamon::move_sentinel<int>, hamon::move_sentinel<NonConvertible>>::value, "");
		static_assert(!std::is_convertible<hamon::move_sentinel<long>, hamon::move_sentinel<NonConvertible>>::value, "");
	}
	return true;
}

GTEST_TEST(MoveSentinelTest, CtorConvertTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorConvertTest());
}

struct NonAssignable
{
	NonAssignable& operator=(int i);
};
static_assert( hamon::semiregular_t<NonAssignable>::value, "");
static_assert( std::is_assignable<NonAssignable, int>::value, "");
static_assert(!hamon::assignable_from_t<NonAssignable, int>::value, "");

inline HAMON_CXX14_CONSTEXPR bool AssignConvertTest()
{
	// Assigning from an lvalue.
	{
		hamon::move_sentinel<int> m(42);
		hamon::move_sentinel<long> m2;
		m2 = m;
		VERIFY(m2.base() == 42L);
		static_assert( std::is_assignable<
			hamon::move_sentinel<long>&,
			hamon::move_sentinel<int> const&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_assignable<
			hamon::move_sentinel<long>&,
			hamon::move_sentinel<int> const&>::value, "");
#endif
	}

	// Assigning from an rvalue.
	{
		hamon::move_sentinel<long> m2;
		m2 = hamon::move_sentinel<int>(43);
		VERIFY(m2.base() == 43L);
		static_assert( std::is_assignable<
			hamon::move_sentinel<long>&,
			hamon::move_sentinel<int> &&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_assignable<
			hamon::move_sentinel<long>&,
			hamon::move_sentinel<int> &&>::value, "");
#endif
	}

	{
		struct S1
		{
			S1() = default;
			S1(S1 const&) = default;
			S1& operator=(S1 const&) = default;
		};
		struct S2
		{
			S2() = default;
			S2(S2 const&) = default;
			S2& operator=(S2 const&) = default;

			S2(S1 const&);
			S2& operator=(S1 const&) noexcept(true);
		};
		using Sent1 = hamon::move_sentinel<S1>;
		using Sent2 = hamon::move_sentinel<S2>;
		static_assert( std::is_assignable<Sent2&, Sent1 const&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert( std::is_nothrow_assignable<Sent2&, Sent1 const&>::value, "");
#endif
	}
	{
		struct S1
		{
			S1() = default;
			S1(S1 const&) = default;
			S1& operator=(S1 const&) = default;
		};
		struct S2
		{
			S2() = default;
			S2(S2 const&) = default;
			S2& operator=(S2 const&) = default;

			S2(S1 const&);
			S2& operator=(S1 const&) noexcept(false);
		};
		using Sent1 = hamon::move_sentinel<S1>;
		using Sent2 = hamon::move_sentinel<S2>;
		static_assert( std::is_assignable<Sent2&, Sent1 const&>::value, "");
#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
		static_assert(!std::is_nothrow_assignable<Sent2&, Sent1 const&>::value, "");
#endif
	}

	// SFINAE checks.
	{
		static_assert( std::is_assignable<hamon::move_sentinel<int>, hamon::move_sentinel<long>>::value, "");
		static_assert(!std::is_assignable<hamon::move_sentinel<int*>, hamon::move_sentinel<const int*>>::value, "");
		static_assert( std::is_assignable<hamon::move_sentinel<const int*>, hamon::move_sentinel<int*>>::value, "");
		static_assert(!std::is_assignable<hamon::move_sentinel<NonAssignable>, hamon::move_sentinel<int>>::value, "");
	}

	return true;
}

GTEST_TEST(MoveSentinelTest, AssignConvertTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AssignConvertTest());
}

inline HAMON_CXX14_CONSTEXPR bool BaseTest()
{
	// The sentinel type is a value.
	{
		auto m = hamon::move_sentinel<int>(42);
		const auto& cm = m;
		VERIFY(m.base() == 42);
		VERIFY(cm.base() == 42);
		VERIFY(std::move(m).base() == 42);
		VERIFY(std::move(cm).base() == 42);
		static_assert(std::is_same<decltype(m.base()), int>::value, "");
		static_assert(std::is_same<decltype(cm.base()), int>::value, "");
		static_assert(std::is_same<decltype(std::move(m).base()), int>::value, "");
		static_assert(std::is_same<decltype(std::move(cm).base()), int>::value, "");
	}

	// The sentinel type is a pointer.
	{
		int a[] = { 1, 2, 3 };
		auto m = hamon::move_sentinel<const int*>(a);
		const auto& cm = m;
		VERIFY(m.base() == a);
		VERIFY(cm.base() == a);
		VERIFY(std::move(m).base() == a);
		VERIFY(std::move(cm).base() == a);
		static_assert(std::is_same<decltype(m.base()), const int*>::value, "");
		static_assert(std::is_same<decltype(cm.base()), const int*>::value, "");
		static_assert(std::is_same<decltype(std::move(m).base()), const int*>::value, "");
		static_assert(std::is_same<decltype(std::move(cm).base()), const int*>::value, "");
	}
	return true;
}

GTEST_TEST(MoveSentinelTest, BaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BaseTest());
}

template <typename T, typename U>
using HasEq = decltype(std::declval<T const&>() == std::declval<U const&>());
template <typename T, typename U>
using HasNe = decltype(std::declval<T const&>() != std::declval<U const&>());
template <typename T, typename U>
using HasLt = decltype(std::declval<T const&>() < std::declval<U const&>());
template <typename T, typename U>
using HasGt = decltype(std::declval<T const&>() > std::declval<U const&>());
template <typename T, typename U>
using HasLe = decltype(std::declval<T const&>() <= std::declval<U const&>());
template <typename T, typename U>
using HasGe = decltype(std::declval<T const&>() >= std::declval<U const&>());

static_assert( hamon::is_detected<HasEq, hamon::move_iterator<int*>,       hamon::move_sentinel<int*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_iterator<int*>,       hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_iterator<int*>,       hamon::move_sentinel<char*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_iterator<int const*>, hamon::move_sentinel<int*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_iterator<int const*>, hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_iterator<int const*>, hamon::move_sentinel<char*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_iterator<char*>,      hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_iterator<char*>,      hamon::move_sentinel<int const*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_iterator<char*>,      hamon::move_sentinel<char*>>::value, "");

static_assert( hamon::is_detected<HasEq, hamon::move_sentinel<int*>,       hamon::move_iterator<int*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_sentinel<int*>,       hamon::move_iterator<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int*>,       hamon::move_iterator<char*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_sentinel<int const*>, hamon::move_iterator<int*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_sentinel<int const*>, hamon::move_iterator<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int const*>, hamon::move_iterator<char*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<char*>,      hamon::move_iterator<int*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<char*>,      hamon::move_iterator<int const*>>::value, "");
static_assert( hamon::is_detected<HasEq, hamon::move_sentinel<char*>,      hamon::move_iterator<char*>>::value, "");

static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int*>,       hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int*>,       hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int*>,       hamon::move_sentinel<char*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int const*>, hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int const*>, hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<int const*>, hamon::move_sentinel<char*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<char*>,      hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<char*>,      hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasEq, hamon::move_sentinel<char*>,      hamon::move_sentinel<char*>>::value, "");

static_assert( hamon::is_detected<HasNe, hamon::move_iterator<int*>,       hamon::move_sentinel<int*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_iterator<int*>,       hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_iterator<int*>,       hamon::move_sentinel<char*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_iterator<int const*>, hamon::move_sentinel<int*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_iterator<int const*>, hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_iterator<int const*>, hamon::move_sentinel<char*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_iterator<char*>,      hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_iterator<char*>,      hamon::move_sentinel<int const*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_iterator<char*>,      hamon::move_sentinel<char*>>::value, "");

static_assert( hamon::is_detected<HasNe, hamon::move_sentinel<int*>,       hamon::move_iterator<int*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_sentinel<int*>,       hamon::move_iterator<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int*>,       hamon::move_iterator<char*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_sentinel<int const*>, hamon::move_iterator<int*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_sentinel<int const*>, hamon::move_iterator<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int const*>, hamon::move_iterator<char*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<char*>,      hamon::move_iterator<int*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<char*>,      hamon::move_iterator<int const*>>::value, "");
static_assert( hamon::is_detected<HasNe, hamon::move_sentinel<char*>,      hamon::move_iterator<char*>>::value, "");

static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int*>,       hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int*>,       hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int*>,       hamon::move_sentinel<char*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int const*>, hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int const*>, hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<int const*>, hamon::move_sentinel<char*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<char*>,      hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<char*>,      hamon::move_sentinel<int const*>>::value, "");
static_assert(!hamon::is_detected<HasNe, hamon::move_sentinel<char*>,      hamon::move_sentinel<char*>>::value, "");

static_assert(!hamon::is_detected<HasLt, hamon::move_iterator<int*>, hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasLt, hamon::move_sentinel<int*>, hamon::move_iterator<int*>>::value, "");
static_assert(!hamon::is_detected<HasLt, hamon::move_sentinel<int*>, hamon::move_sentinel<int*>>::value, "");

static_assert(!hamon::is_detected<HasGt, hamon::move_iterator<int*>, hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasGt, hamon::move_sentinel<int*>, hamon::move_iterator<int*>>::value, "");
static_assert(!hamon::is_detected<HasGt, hamon::move_sentinel<int*>, hamon::move_sentinel<int*>>::value, "");

static_assert(!hamon::is_detected<HasLe, hamon::move_iterator<int*>, hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasLe, hamon::move_sentinel<int*>, hamon::move_iterator<int*>>::value, "");
static_assert(!hamon::is_detected<HasLe, hamon::move_sentinel<int*>, hamon::move_sentinel<int*>>::value, "");

static_assert(!hamon::is_detected<HasGe, hamon::move_iterator<int*>, hamon::move_sentinel<int*>>::value, "");
static_assert(!hamon::is_detected<HasGe, hamon::move_sentinel<int*>, hamon::move_iterator<int*>>::value, "");
static_assert(!hamon::is_detected<HasGe, hamon::move_sentinel<int*>, hamon::move_sentinel<int*>>::value, "");

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<hamon::move_iterator<int*>>() == std::declval<hamon::move_sentinel<int*>>());
HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<hamon::move_iterator<int*>>() != std::declval<hamon::move_sentinel<int*>>());
HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<hamon::move_sentinel<int*>>() == std::declval<hamon::move_iterator<int*>>());
HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<hamon::move_sentinel<int*>>() != std::declval<hamon::move_iterator<int*>>());
#endif

template <bool Noexcept, typename Iterator>
struct MayThrowSentinel
{
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator==(It const&, MayThrowSentinel const&) noexcept(Noexcept);
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator!=(It const&, MayThrowSentinel const&) noexcept(Noexcept);
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator==(MayThrowSentinel const&, It const&) noexcept(Noexcept);
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator!=(MayThrowSentinel const&, It const&) noexcept(Noexcept);
};

template <typename It>
inline HAMON_CXX14_CONSTEXPR bool OperatorTest()
{
	char s[] = "abc";
	const auto it = hamon::move_iterator<It>(It{s});
	const auto sent1 = hamon::move_sentinel<test_sentinel<It>>(test_sentinel<It>{It{s}});
	const auto sent2 = hamon::move_sentinel<test_sentinel<It>>(test_sentinel<It>{It{s + 1}});
	static_assert(std::is_same<decltype(it == sent1), bool>::value ,"");
	VERIFY( (it == sent1));
	VERIFY(!(it != sent1));
	VERIFY(!(it == sent2));
	VERIFY( (it != sent2));
	VERIFY( (sent1 == it));
	VERIFY(!(sent1 != it));
	VERIFY(!(sent2 == it));
	VERIFY( (sent2 != it));

	static_assert(!hamon::is_detected<HasEq, decltype(sent1), decltype(sent1)>::value, "");
	static_assert(!hamon::is_detected<HasNe, decltype(sent1), decltype(sent1)>::value, "");
	static_assert(!hamon::is_detected<HasLt, decltype(sent1), decltype(sent1)>::value, "");
	static_assert(!hamon::is_detected<HasGt, decltype(sent1), decltype(sent1)>::value, "");
	static_assert(!hamon::is_detected<HasLe, decltype(sent1), decltype(sent1)>::value, "");
	static_assert(!hamon::is_detected<HasGe, decltype(sent1), decltype(sent1)>::value, "");

	return true;
}

GTEST_TEST(MoveSentinelTest, OperatorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorTest<input_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorTest<forward_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorTest<bidirectional_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorTest<random_access_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorTest<contiguous_iterator_wrapper<char>>());

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	{
		using Iter = int*;
		using Sent = MayThrowSentinel<true, Iter>;
		using MoveIter = hamon::move_iterator<Iter>;
		using MoveSent = hamon::move_sentinel<Sent>;
		HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<MoveIter const&>() == std::declval<MoveSent const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<MoveIter const&>() != std::declval<MoveSent const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<MoveSent const&>() == std::declval<MoveIter const&>());
		HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<MoveSent const&>() != std::declval<MoveIter const&>());
	}
	{
		using Iter = int*;
		using Sent = MayThrowSentinel<false, Iter>;
		using MoveIter = hamon::move_iterator<Iter>;
		using MoveSent = hamon::move_sentinel<Sent>;
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveIter const&>() == std::declval<MoveSent const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveIter const&>() != std::declval<MoveSent const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveSent const&>() == std::declval<MoveIter const&>());
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveSent const&>() != std::declval<MoveIter const&>());
	}
#endif
}

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR bool OperatorMinusTest()
{
	using Sent = test_sentinel<Iter>;

	int a[] = {3, 1, 4};

	hamon::move_iterator<Iter> i0{Iter{a+0}};
	hamon::move_iterator<Iter> i1{Iter{a+1}};
	hamon::move_iterator<Iter> i2{Iter{a+2}};

	hamon::move_sentinel<Sent> s0{Sent{Iter{a+0}}};
	hamon::move_sentinel<Sent> s1{Sent{Iter{a+1}}};
	hamon::move_sentinel<Sent> s2{Sent{Iter{a+2}}};

	static_assert(std::is_same<decltype(i0 - s0), hamon::iter_difference_t<Iter>>::value, "");
	static_assert(std::is_same<decltype(s0 - i0), hamon::iter_difference_t<Iter>>::value, "");

	VERIFY(i0 - s0 ==  0);
	VERIFY(i0 - s1 == -1);
	VERIFY(i0 - s2 == -2);
	VERIFY(i1 - s0 ==  1);
	VERIFY(i1 - s1 ==  0);
	VERIFY(i1 - s2 == -1);
	VERIFY(i2 - s0 ==  2);
	VERIFY(i2 - s1 ==  1);
	VERIFY(i2 - s2 ==  0);

	VERIFY(s0 - i0 ==  0);
	VERIFY(s0 - i1 == -1);
	VERIFY(s0 - i2 == -2);
	VERIFY(s1 - i0 ==  1);
	VERIFY(s1 - i1 ==  0);
	VERIFY(s1 - i2 == -1);
	VERIFY(s2 - i0 ==  2);
	VERIFY(s2 - i1 ==  1);
	VERIFY(s2 - i2 ==  0);

	return true;
}

template <bool B1, bool B2, typename Iterator>
struct MayThrowMinusSentinel
{
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator==(It const&, MayThrowMinusSentinel const&) noexcept;
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator!=(It const&, MayThrowMinusSentinel const&) noexcept;
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator==(MayThrowMinusSentinel const&, It const&) noexcept;
	template <typename It>
	friend HAMON_CONSTEXPR bool
	operator!=(MayThrowMinusSentinel const&, It const&) noexcept;
	
	template <typename It>
	friend HAMON_CONSTEXPR std::ptrdiff_t
	operator-(MayThrowMinusSentinel const&, It const&) noexcept(B1);
	template <typename It>
	friend HAMON_CONSTEXPR std::ptrdiff_t
	operator-(It const&, MayThrowMinusSentinel const&) noexcept(B2);
};

GTEST_TEST(MoveSentinelTest, OperatorMinusTest)
{
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<input_iterator_wrapper<int>>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<forward_iterator_wrapper<int>>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<bidirectional_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<random_access_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<contiguous_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<int*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(OperatorMinusTest<int const*>());

#if !defined(HAMON_USE_STD_MOVE_ITERATOR)
	HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<hamon::move_iterator<int*>>() - std::declval<hamon::move_sentinel<int*>>());
	HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<hamon::move_sentinel<int*>>() - std::declval<hamon::move_iterator<int*>>());

	{
		using Iter = int*;
		using Sent = MayThrowMinusSentinel<true, true, Iter>;
		using MoveIter = hamon::move_iterator<Iter>;
		using MoveSent = hamon::move_sentinel<Sent>;
		HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<MoveIter>() - std::declval<MoveSent>());
		HAMON_ASSERT_NOEXCEPT_TRUE(std::declval<MoveSent>() - std::declval<MoveIter>());
	}
	{
		using Iter = int*;
		using Sent = MayThrowMinusSentinel<true, false, Iter>;
		using MoveIter = hamon::move_iterator<Iter>;
		using MoveSent = hamon::move_sentinel<Sent>;
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveIter>() - std::declval<MoveSent>());
		HAMON_ASSERT_NOEXCEPT_TRUE (std::declval<MoveSent>() - std::declval<MoveIter>());
	}
	{
		using Iter = int*;
		using Sent = MayThrowMinusSentinel<false, true, Iter>;
		using MoveIter = hamon::move_iterator<Iter>;
		using MoveSent = hamon::move_sentinel<Sent>;
		HAMON_ASSERT_NOEXCEPT_TRUE (std::declval<MoveIter>() - std::declval<MoveSent>());
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveSent>() - std::declval<MoveIter>());
	}
	{
		using Iter = int*;
		using Sent = MayThrowMinusSentinel<false, false, Iter>;
		using MoveIter = hamon::move_iterator<Iter>;
		using MoveSent = hamon::move_sentinel<Sent>;
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveIter>() - std::declval<MoveSent>());
		HAMON_ASSERT_NOEXCEPT_FALSE(std::declval<MoveSent>() - std::declval<MoveIter>());
	}
#endif
}

#undef VERIFY

}	// namespace move_sentinel_test

}	// namespace hamon_iterator_test
