/**
 *	@file	unit_test_expected_transform_error.cpp
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
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/algorithm/reverse.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace transform_error_test
{

struct LVal
{
	HAMON_CXX14_CONSTEXPR int operator()(int&) { return 1; }
	int operator()(const int&)  = delete;
	int operator()(int&&)       = delete;
	int operator()(const int&&) = delete;
};

struct CLVal
{
	int operator()(int&) = delete;
	HAMON_CXX14_CONSTEXPR int operator()(const int&) { return 1; }
	int operator()(int&&)       = delete;
	int operator()(const int&&) = delete;
};

struct RVal
{
	int operator()(int&)       = delete;
	int operator()(const int&) = delete;
	HAMON_CXX14_CONSTEXPR int operator()(int&&) { return 1; }
	int operator()(const int&&) = delete;
};

struct CRVal
{
	int operator()(int&)       = delete;
	int operator()(const int&) = delete;
	int operator()(int&&)      = delete;
	HAMON_CXX14_CONSTEXPR int operator()(const int&&) { return 1; }
};

struct RefQual
{
	HAMON_CXX14_CONSTEXPR int operator()(int) & { return 1; }
	int operator()(int) const&  = delete;
	int operator()(int) &&      = delete;
	int operator()(int) const&& = delete;
};

struct CRefQual
{
	int operator()(int) & = delete;
	HAMON_CXX14_CONSTEXPR int operator()(int) const& { return 1; }
	int operator()(int) &&      = delete;
	int operator()(int) const&& = delete;
};

struct RVRefQual
{
	int operator()(int) &      = delete;
	int operator()(int) const& = delete;
	HAMON_CXX14_CONSTEXPR int operator()(int) && { return 1; }
	int operator()(int) const&& = delete;
};

struct RVCRefQual
{
	int operator()(int) &      = delete;
	int operator()(int) const& = delete;
	int operator()(int) &&     = delete;
	HAMON_CXX14_CONSTEXPR int operator()(int) const&& { return 1; }
};

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
struct has_transform_error
	: hamon::false_type{};

template <typename E, typename F>
struct has_transform_error<E, F, hamon::void_t<decltype(hamon::declval<E>().transform_error(hamon::declval<F>()))>>
	: hamon::true_type{};

static_assert( has_transform_error<hamon::expected<int,         int>&,       int(int&)>::value, "");
static_assert(!has_transform_error<hamon::expected<NonCopyable, int>&,       int(int&)>::value, "");
static_assert( has_transform_error<hamon::expected<int,         int> const&, int(int const&)>::value, "");
static_assert(!has_transform_error<hamon::expected<NonCopyable, int> const&, int(int const&)>::value, "");
static_assert( has_transform_error<hamon::expected<int,        int>&&,       int(int)>::value, "");
static_assert(!has_transform_error<hamon::expected<NonMovable, int>&&,       int(int)>::value, "");
static_assert( has_transform_error<hamon::expected<int,        int> const&&, int(int const)>::value, "");
static_assert(!has_transform_error<hamon::expected<NonMovable, int> const&&, int(int const)>::value, "");

// [LWG 3877] https://cplusplus.github.io/LWG/issue3877, check constraint failing but not compile error inside the function body.
static_assert(!has_transform_error<const hamon::expected<hamon::unique_ptr<int>, int>&, int()>::value, "");
static_assert(!has_transform_error<const hamon::expected<hamon::unique_ptr<int>, int>&&, int()>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	struct F
	{
		constexpr int operator()(E n) const
		{
			return static_cast<int>(n * 2);
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &      >().transform_error(f)), hamon::expected<T, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const& >().transform_error(f)), hamon::expected<T, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &&     >().transform_error(f)), hamon::expected<T, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const&&>().transform_error(f)), hamon::expected<T, int>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &      >().transform_error(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const& >().transform_error(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &&     >().transform_error(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const&&>().transform_error(f)), "");

	{
		hamon::expected<T, E> e1 = T{2};
		auto e2 = e1.transform_error(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{2});
	}
	{
		hamon::expected<T, E> e1 = hamon::unexpected<E>{E{10}};
		auto e2 = e1.transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 20);
	}
	{
		hamon::expected<T, E> const e1 = T{3};
		auto e2 = e1.transform_error(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{3});
	}
	{
		hamon::expected<T, E> const e1 = hamon::unexpected<E>{E{11}};
		auto e2 = e1.transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 22);
	}
	{
		hamon::expected<T, E> e1 = T{4};
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{4});
	}
	{
		hamon::expected<T, E> e1 = hamon::unexpected<E>{E{12}};
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 24);
	}
	{
		hamon::expected<T, E> const e1 = T{5};
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{5});
	}
	{
		hamon::expected<T, E> const e1 = hamon::unexpected<E>{E{13}};
		auto e2 = hamon::move(e1).transform_error(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == 26);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_val_types()
{
	// Test & overload
	{
		// Without & qualifier on F's operator()
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = e.transform_error(LVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}

		// With & qualifier on F's operator()
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			RefQual l{};
			auto val = e.transform_error(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}
	}

	// Test const& overload
	{
		// Without const& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = e.transform_error(CLVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}

		// With const& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			const CRefQual l{};
			auto val = e.transform_error(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}
	}

	// Test && overload
	{
		// Without && qualifier on F's operator()
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = hamon::move(e).transform_error(RVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}

		// With && qualifier on F's operator()
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = hamon::move(e).transform_error(RVRefQual{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}
	}

	// Test const&& overload
	{
		// Without const&& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = hamon::move(e).transform_error(CRVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}

		// With const&& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			const RVCRefQual l{};
			auto val = hamon::move(e).transform_error(hamon::move(l));
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.error() == 1);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_direct_non_list_init()
{
#if defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	{
		hamon::expected<int, int> e(hamon::unexpect, 42);
		auto r = e.transform_error([](int i){return NonMovable(i);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<int, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 42);
	}
	{
		hamon::expected<int, int> const e(hamon::unexpect, 42);
		auto r = e.transform_error([](int i){return NonMovable(i - 1);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<int, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 41);
	}
	{
		hamon::expected<int, int> e(hamon::unexpect, 42);
		auto r = hamon::move(e).transform_error([](int i){return NonMovable(i + 2);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<int, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 44);
	}
	{
		hamon::expected<int, int> const e(hamon::unexpect, 42);
		auto r = hamon::move(e).transform_error([](int i){return NonMovable(i * 2);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<int, NonMovable>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error().value == 84);
	}
#endif
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::string revstr(hamon::string str)
{
	hamon::reverse(str.begin(), str.end());
	return str;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<int, hamon::string> v1 = 42;
	VERIFY(v1.transform_error(revstr).value() == 42);

	hamon::expected<int, hamon::string> e1 = hamon::unexpected<hamon::string>{"Oops"};
	VERIFY(e1.transform_error(revstr).error() == "spoO");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, TransformErrorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_direct_non_list_init()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace transform_error_test

}	// namespace hamon_expected_test
