/**
 *	@file	unit_test_expected_void_transform_error.cpp
 *
 *	@brief	transform_error() のテスト
 *
 *	template<class F> constexpr auto transform_error(F&& f) &;
 *	template<class F> constexpr auto transform_error(F&& f) const &;
 *	template<class F> constexpr auto transform_error(F&& f) &&;
 *	template<class F> constexpr auto transform_error(F&& f) const &&;
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
#include <hamon/utility/move.hpp>
#include <hamon/charconv.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace transform_error_test
{

struct NonMovable
{
	int value;
	constexpr NonMovable(int v) : value(v) {}
	NonMovable(NonMovable const&) = delete;
	NonMovable(NonMovable&&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");

	struct F
	{
		constexpr int operator()(E n) const
		{
			return static_cast<int>(n * 2);
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &      >().transform_error(f)), hamon::expected<Void, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const& >().transform_error(f)), hamon::expected<Void, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &&     >().transform_error(f)), hamon::expected<Void, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const&&>().transform_error(f)), hamon::expected<Void, int>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &      >().transform_error(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const& >().transform_error(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &&     >().transform_error(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const&&>().transform_error(f)), "");

	{
		hamon::expected<Void, E> e1;
		auto e2 = e1.transform_error(f);
		VERIFY(e2.has_value());
	}
	{
		hamon::expected<Void, E> e1 = hamon::unexpected<E>{E{10}};
		auto e2 = e1.transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 20);
	}
	{
		hamon::expected<Void, E> const e1;
		auto e2 = e1.transform_error(f);
		VERIFY(e2.has_value());
	}
	{
		hamon::expected<Void, E> const e1 = hamon::unexpected<E>{E{11}};
		auto e2 = e1.transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 22);
	}
	{
		hamon::expected<Void, E> e1;
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(e2.has_value());
	}
	{
		hamon::expected<Void, E> e1 = hamon::unexpected<E>{E{12}};
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 24);
	}
	{
		hamon::expected<Void, E> const e1;
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(e2.has_value());
	}
	{
		hamon::expected<Void, E> const e1 = hamon::unexpected<E>{E{13}};
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 26);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_direct_non_list_init()
{
#if defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	{
		hamon::expected<void, int> e(hamon::unexpect, 42);
		auto r = e.transform_error([](int i){return NonMovable(i);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 42);
	}
	{
		hamon::expected<void, int> const e(hamon::unexpect, 42);
		auto r = e.transform_error([](int i){return NonMovable(i - 1);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 41);
	}
	{
		hamon::expected<void, int> e(hamon::unexpect, 42);
		auto r = hamon::move(e).transform_error([](int i){return NonMovable(i + 2);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 44);
	}
	{
		hamon::expected<void, int> const e(hamon::unexpect, 42);
		auto r = hamon::move(e).transform_error([](int i){return NonMovable(i * 2);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 84);
	}
#endif
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::string int2str(int n)
{
	char buf[256]{};
	hamon::to_chars(buf, buf + 256, n);
	return hamon::string{buf};
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<void, int> v1;
	VERIFY(v1.transform_error(int2str).has_value());

	hamon::expected<void, int> e1 = hamon::unexpected<int>{42};
	VERIFY(e1.transform_error(int2str).error() == "42");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, TransformErrorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, short>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_direct_non_list_init()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace transform_error_test

}	// namespace hamon_expected_void_test
