/**
 *	@file	unit_test_expected_or_else.cpp
 *
 *	@brief	or_else() のテスト
 *
 *	template<class F> constexpr auto or_else(F&& f) &;
 *	template<class F> constexpr auto or_else(F&& f) const &;
 *	template<class F> constexpr auto or_else(F&& f) &&;
 *	template<class F> constexpr auto or_else(F&& f) const &&;
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
#include <hamon/charconv.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace or_else_test
{

struct LVal
{
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int&) { return 1; }
	hamon::expected<int, int> operator()(int const&)  = delete;
	hamon::expected<int, int> operator()(int&&)       = delete;
	hamon::expected<int, int> operator()(int const&&) = delete;
};

struct CLVal
{
	hamon::expected<int, int> operator()(int&) = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int const&) { return 1; }
	hamon::expected<int, int> operator()(int&&)       = delete;
	hamon::expected<int, int> operator()(int const&&) = delete;
};

struct RVal
{
	hamon::expected<int, int> operator()(int&)       = delete;
	hamon::expected<int, int> operator()(int const&) = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int&&) { return 1; }
	hamon::expected<int, int> operator()(int const&&) = delete;
};

struct CRVal
{
	hamon::expected<int, int> operator()(int&)       = delete;
	hamon::expected<int, int> operator()(int const&) = delete;
	hamon::expected<int, int> operator()(int&&)      = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int const&&) { return 1; }
};

struct RefQual
{
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) & { return 1; }
	hamon::expected<int, int> operator()(int) const&  = delete;
	hamon::expected<int, int> operator()(int) &&      = delete;
	hamon::expected<int, int> operator()(int) const&& = delete;
};

struct CRefQual
{
	hamon::expected<int, int> operator()(int) & = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) const& { return 1; }
	hamon::expected<int, int> operator()(int) &&      = delete;
	hamon::expected<int, int> operator()(int) const&& = delete;
};

struct RVRefQual
{
	hamon::expected<int, int> operator()(int) &      = delete;
	hamon::expected<int, int> operator()(int) const& = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) && { return 1; }
	hamon::expected<int, int> operator()(int) const&& = delete;
};

struct RVCRefQual
{
	hamon::expected<int, int> operator()(int) &      = delete;
	hamon::expected<int, int> operator()(int) const& = delete;
	hamon::expected<int, int> operator()(int) &&     = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) const&& { return 1; }
};

struct NonCopyable
{
	constexpr NonCopyable(int){}
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable(NonCopyable&&) = default;
};

struct NonMovable
{
	constexpr NonMovable(int){}
	NonMovable(NonMovable const&) = delete;
	NonMovable(NonMovable&&) = delete;
};

template <typename E, typename F, typename = void>
struct has_or_else
	: hamon::false_type{};

template <typename E, typename F>
struct has_or_else<E, F, hamon::void_t<decltype(hamon::declval<E>().or_else(hamon::declval<F>()))>>
	: hamon::true_type{};

static_assert( has_or_else<hamon::expected<int,         int>&,       hamon::expected<int,         int>(int&)>::value, "");
static_assert(!has_or_else<hamon::expected<NonCopyable, int>&,       hamon::expected<NonCopyable, int>(int&)>::value, "");
static_assert( has_or_else<hamon::expected<int,         int> const&, hamon::expected<int,         int>(int const&)>::value, "");
static_assert(!has_or_else<hamon::expected<NonCopyable, int> const&, hamon::expected<NonCopyable, int>(int const&)>::value, "");
static_assert( has_or_else<hamon::expected<int,        int>&&,       hamon::expected<int,        int>(int)>::value, "");
static_assert(!has_or_else<hamon::expected<NonMovable, int>&&,       hamon::expected<NonMovable, int>(int)>::value, "");
static_assert( has_or_else<hamon::expected<int,        int> const&&, hamon::expected<int,        int>(int const)>::value, "");
static_assert(!has_or_else<hamon::expected<NonMovable, int> const&&, hamon::expected<NonMovable, int>(int const)>::value, "");

// [LWG 3877] https://cplusplus.github.io/LWG/issue3877, check constraint failing but not compile error inside the function body.
static_assert(!has_or_else<const hamon::expected<hamon::unique_ptr<int>, int>&, int()>::value, "");
static_assert(!has_or_else<const hamon::expected<hamon::unique_ptr<int>, int>&&, int()>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	struct F
	{
		HAMON_CXX14_CONSTEXPR hamon::expected<T, E> operator()(E n) const
		{
			if (n > 0)
			{
				return hamon::unexpected<E>{n * 2};
			}
			else
			{
				return T{42};
			}
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &      >().or_else(f)), hamon::expected<T, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const& >().or_else(f)), hamon::expected<T, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &&     >().or_else(f)), hamon::expected<T, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const&&>().or_else(f)), hamon::expected<T, E>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &      >().or_else(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const& >().or_else(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &&     >().or_else(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const&&>().or_else(f)), "");

	{
		hamon::expected<T, E> e1 = T{1};
		auto e2 = e1.or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{1});
	}
	{
		hamon::expected<T, E> e1{hamon::unexpect, E{1}};
		auto e2 = e1.or_else(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{2});
	}
	{
		hamon::expected<T, E> e1{hamon::unexpect, E{0}};
		auto e2 = e1.or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{42});
	}
	{
		hamon::expected<T, E> const e1 = T{1};
		auto e2 = e1.or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{1});
	}
	{
		hamon::expected<T, E> const e1{hamon::unexpect, E{1}};
		auto e2 = e1.or_else(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{2});
	}
	{
		hamon::expected<T, E> const e1{hamon::unexpect, E{0}};
		auto e2 = e1.or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{42});
	}
	{
		hamon::expected<T, E> e1 = T{1};
		auto e2 = hamon::move(e1).or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{1});
	}
	{
		hamon::expected<T, E> e1{hamon::unexpect, E{1}};
		auto e2 = hamon::move(e1).or_else(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{2});
	}
	{
		hamon::expected<T, E> e1{hamon::unexpect, E{0}};
		auto e2 = hamon::move(e1).or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{42});
	}
	{
		hamon::expected<T, E> const e1 = T{1};
		auto e2 = hamon::move(e1).or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{1});
	}
	{
		hamon::expected<T, E> const e1{hamon::unexpect, E{1}};
		auto e2 = hamon::move(e1).or_else(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{2});
	}
	{
		hamon::expected<T, E> const e1{hamon::unexpect, E{0}};
		auto e2 = hamon::move(e1).or_else(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{42});
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
			auto val = e.or_else(LVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With & qualifier on F's operator
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			RefQual l{};
			auto val = e.or_else(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}

	// Test const& overload
	{
		// Without const& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = e.or_else(CLVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With const& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			const CRefQual l{};
			auto val = e.or_else(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}

	// Test && overload
	{
		// Without && qualifier on F's operator()
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = hamon::move(e).or_else(RVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With && qualifier on F's operator()
		{
			hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = hamon::move(e).or_else(RVRefQual{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}

	// Test const&& overload
	{
		// Without const&& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			auto val = hamon::move(e).or_else(CRVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With const&& qualifier on F's operator()
		{
			const hamon::expected<int, int> e(hamon::unexpected<int>(0));
			const RVCRefQual l{};
			auto val = hamon::move(e).or_else(hamon::move(l));
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::expected<int, hamon::string> parse(hamon::string_view s)
{
	int val{};
	auto ret = hamon::from_chars(s.data(), s.data() + s.length(), val);
	if (ret.ec == hamon::errc{} && ret.ptr == (s.data() + s.length()))
	{
		return val;
	}
	else
	{
		return hamon::unexpected<hamon::string>{s};
	}
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<int, hamon::string> v1 = 1;
	VERIFY(v1.or_else(parse).value() == 1);

	hamon::expected<int, hamon::string> e1 = hamon::unexpected<hamon::string>{"123"};
	VERIFY(e1.or_else(parse) == 123);

	hamon::expected<int, hamon::string> e2 = hamon::unexpected<hamon::string>{"bad"};
	VERIFY(e2.or_else(parse).error() == "bad");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, OrElseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace or_else_test

}	// namespace hamon_expected_test
