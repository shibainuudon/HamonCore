/**
 *	@file	unit_test_expected_void_transform.cpp
 *
 *	@brief	transform() のテスト
 *
 *	template<class F> constexpr auto transform(F&& f) &;
 *	template<class F> constexpr auto transform(F&& f) const &;
 *	template<class F> constexpr auto transform(F&& f) &&;
 *	template<class F> constexpr auto transform(F&& f) const &&;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace transform_test
{

struct NonCopyable
{
	constexpr NonCopyable(int){}
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable(NonCopyable&&) = default;
};

struct NonMovable
{
	int value;
	constexpr NonMovable(int v) : value(v) {}
	NonMovable(NonMovable const&) = delete;
	NonMovable(NonMovable&&) = delete;
};

template <typename E, typename F, typename = void>
struct has_transform
	: hamon::false_type{};

template <typename E, typename F>
struct has_transform<E, F, hamon::void_t<decltype(hamon::declval<E>().transform(hamon::declval<F>()))>>
	: hamon::true_type{};

static_assert( has_transform<hamon::expected<void, int        >&,       int(void)>::value, "");
static_assert(!has_transform<hamon::expected<void, NonCopyable>&,       int(void)>::value, "");
static_assert( has_transform<hamon::expected<void, int        > const&, int(void)>::value, "");
static_assert(!has_transform<hamon::expected<void, NonCopyable> const&, int(void)>::value, "");
static_assert( has_transform<hamon::expected<void, int       >&&,       int(void)>::value, "");
static_assert(!has_transform<hamon::expected<void, NonMovable>&&,       int(void)>::value, "");
static_assert( has_transform<hamon::expected<void, int       > const&&, int(void)>::value, "");
static_assert(!has_transform<hamon::expected<void, NonMovable> const&&, int(void)>::value, "");

// [LWG 3877] https://cplusplus.github.io/LWG/issue3877, check constraint failing but not compile error inside the function body.
static_assert(!has_transform<const hamon::expected<void, hamon::unique_ptr<int>>&, int()>::value, "");
static_assert(!has_transform<const hamon::expected<void, hamon::unique_ptr<int>>&&, int()>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");

	struct F
	{
		constexpr int operator()() const
		{
			return 42;
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &      >().transform(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const& >().transform(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &&     >().transform(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const&&>().transform(f)), hamon::expected<int, E>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &      >().transform(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const& >().transform(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &&     >().transform(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const&&>().transform(f)), "");

	{
		hamon::expected<Void, E> e1;
		auto e2 = e1.transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 42);
	}
	{
		hamon::expected<Void, E> e1 = hamon::unexpected<E>{E{10}};
		auto e2 = e1.transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{10});
	}
	{
		hamon::expected<Void, E> const e1;
		auto e2 = e1.transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 42);
	}
	{
		hamon::expected<Void, E> const e1 = hamon::unexpected<E>{E{11}};
		auto e2 = e1.transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{11});
	}
	{
		hamon::expected<Void, E> e1;
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 42);
	}
	{
		hamon::expected<Void, E> e1 = hamon::unexpected<E>{E{12}};
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{12});
	}
	{
		hamon::expected<Void, E> const e1;
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 42);
	}
	{
		hamon::expected<Void, E> const e1 = hamon::unexpected<E>{E{13}};
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{13});
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_return_void()
{
	struct F
	{
		bool invoked = false;
		HAMON_CXX14_CONSTEXPR void operator()()
		{
			invoked = true;
		}
	};

	{
		F f;
		hamon::expected<void, int> e(hamon::in_place);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> e(hamon::unexpect, 1);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> const e(hamon::in_place);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> const e(hamon::unexpect, 1);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> e(hamon::in_place);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> e(hamon::unexpect, 1);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> const e(hamon::in_place);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<void, int> const e(hamon::unexpect, 1);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_direct_non_list_init()
{
#if defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	{
		hamon::expected<void, int> e;
		auto r = e.transform([](){return NonMovable(42);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 42);
	}
	{
		hamon::expected<void, int> const e;
		auto r = e.transform([](){return NonMovable(43);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 43);
	}
	{
		hamon::expected<void, int> e;
		auto r = hamon::move(e).transform([](){return NonMovable(17);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 17);
	}
	{
		hamon::expected<void, int> const e;
		auto r = hamon::move(e).transform([](){return NonMovable(0);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 0);
	}
#endif
	return true;
}

HAMON_CXX20_CONSTEXPR int get_answer()
{
	return 42;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<void, hamon::string> v1;
	VERIFY(v1.transform(get_answer).value() == 42);

	hamon::expected<void, hamon::string> e1 = hamon::unexpected<hamon::string>{"galaxy"};
	VERIFY(e1.transform(get_answer).error() == "galaxy");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, TransformTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, short>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_return_void()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_direct_non_list_init()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace transform_test

}	// namespace hamon_expected_void_test
