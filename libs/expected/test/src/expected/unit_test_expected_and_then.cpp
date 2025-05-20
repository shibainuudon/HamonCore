/**
 *	@file	unit_test_expected_and_then.cpp
 *
 *	@brief	and_then() のテスト
 *
 *	template<class F> constexpr auto and_then(F&& f) &;
 *	template<class F> constexpr auto and_then(F&& f) const &;
 *	template<class F> constexpr auto and_then(F&& f) &&;
 *	template<class F> constexpr auto and_then(F&& f) const &&;
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
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace and_then_test
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

struct UnexpectedLVal
{
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int&) { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
	hamon::expected<int, int> operator()(int const&)  = delete;
	hamon::expected<int, int> operator()(int&&)       = delete;
	hamon::expected<int, int> operator()(int const&&) = delete;
};

struct UnexpectedCLVal
{
	hamon::expected<int, int> operator()(int&) = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int const&) { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
	hamon::expected<int, int> operator()(int&&)       = delete;
	hamon::expected<int, int> operator()(int const&&) = delete;
};

struct UnexpectedRVal
{
	hamon::expected<int, int> operator()(int&)       = delete;
	hamon::expected<int, int> operator()(int const&) = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int&&) { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
	hamon::expected<int, int> operator()(int const&&) = delete;
};

struct UnexpectedCRVal
{
	hamon::expected<int, int> operator()(int&)       = delete;
	hamon::expected<int, int> operator()(int const&) = delete;
	hamon::expected<int, int> operator()(int&&)      = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int const&&) { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
};

struct UnexpectedRefQual
{
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) & { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
	hamon::expected<int, int> operator()(int) const&  = delete;
	hamon::expected<int, int> operator()(int) &&      = delete;
	hamon::expected<int, int> operator()(int) const&& = delete;
};

struct UnexpectedCRefQual
{
	hamon::expected<int, int> operator()(int) & = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) const& { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
	hamon::expected<int, int> operator()(int) &&      = delete;
	hamon::expected<int, int> operator()(int) const&& = delete;
};

struct UnexpectedRVRefQual
{
	hamon::expected<int, int> operator()(int) &      = delete;
	hamon::expected<int, int> operator()(int) const& = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) && { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
	hamon::expected<int, int> operator()(int) const&& = delete;
};

struct UnexpectedRVCRefQual
{
	hamon::expected<int, int> operator()(int) &      = delete;
	hamon::expected<int, int> operator()(int) const& = delete;
	hamon::expected<int, int> operator()(int) &&     = delete;
	HAMON_CXX14_CONSTEXPR hamon::expected<int, int> operator()(int) const&& { return hamon::expected<int, int>(hamon::unexpected<int>(5)); }
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
struct has_and_then
	: hamon::false_type{};

template <typename E, typename F>
struct has_and_then<E, F, hamon::void_t<decltype(hamon::declval<E>().and_then(hamon::declval<F>()))>>
	: hamon::true_type{};

static_assert( has_and_then<hamon::expected<int, int        >&,       hamon::expected<int, int        >(int&)>::value, "");
static_assert(!has_and_then<hamon::expected<int, NonCopyable>&,       hamon::expected<int, NonCopyable>(int&)>::value, "");
static_assert( has_and_then<hamon::expected<int, int        > const&, hamon::expected<int, int        >(int const&)>::value, "");
static_assert(!has_and_then<hamon::expected<int, NonCopyable> const&, hamon::expected<int, NonCopyable>(int const&)>::value, "");
static_assert( has_and_then<hamon::expected<int, int       >&&,       hamon::expected<int, int       >(int)>::value, "");
static_assert(!has_and_then<hamon::expected<int, NonMovable>&&,       hamon::expected<int, NonMovable>(int)>::value, "");
static_assert( has_and_then<hamon::expected<int, int       > const&&, hamon::expected<int, int       >(int const)>::value, "");
static_assert(!has_and_then<hamon::expected<int, NonMovable> const&&, hamon::expected<int, NonMovable>(int const)>::value, "");

// [LWG 3877] https://cplusplus.github.io/LWG/issue3877, check constraint failing but not compile error inside the function body.
static_assert(!has_and_then<const hamon::expected<int, hamon::unique_ptr<int>>&, int()>::value, "");
static_assert(!has_and_then<const hamon::expected<int, hamon::unique_ptr<int>>&&, int()>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	struct F
	{
		HAMON_CXX14_CONSTEXPR hamon::expected<T, E> operator()(T n) const
		{
			if (n > 0)
			{
				return T{n * 2};
			}
			else
			{
				return hamon::unexpected<E>{E{-1}};
			}
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &      >().and_then(f)), hamon::expected<T, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const& >().and_then(f)), hamon::expected<T, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &&     >().and_then(f)), hamon::expected<T, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const&&>().and_then(f)), hamon::expected<T, E>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &      >().and_then(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const& >().and_then(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &&     >().and_then(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const&&>().and_then(f)), "");

	{
		hamon::expected<T, E> e1 = T{1};
		auto e2 = e1.and_then(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{2});
	}
	{
		hamon::expected<T, E> e1 = T{0};
		auto e2 = e1.and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{-1});
	}
	{
		hamon::expected<T, E> e1 = hamon::unexpected<E>{E{10}};
		auto e2 = e1.and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{10});
	}
	{
		hamon::expected<T, E> const e1 = T{2};
		auto e2 = e1.and_then(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{4});
	}
	{
		hamon::expected<T, E> const e1 = T{-1};
		auto e2 = e1.and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{-1});
	}
	{
		hamon::expected<T, E> const e1{hamon::unexpect, E{11}};
		auto e2 = e1.and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{11});
	}
	{
		hamon::expected<T, E> e1 = T{3};
		auto e2 = hamon::move(e1).and_then(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{6});
	}
	{
		hamon::expected<T, E> e1 = T{-2};
		auto e2 = hamon::move(e1).and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{-1});
	}
	{
		hamon::expected<T, E> e1{hamon::unexpect, E{12}};
		auto e2 = hamon::move(e1).and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{12});
	}
	{
		hamon::expected<T, E> const e1 = T{4};
		auto e2 = hamon::move(e1).and_then(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == T{8});
	}
	{
		hamon::expected<T, E> const e1 = T{-3};
		auto e2 = hamon::move(e1).and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{-1});
	}
	{
		hamon::expected<T, E> const e1{hamon::unexpect, E{13}};
		auto e2 = hamon::move(e1).and_then(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{13});
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_val_types()
{
	// Test & overload
	{
		// Without & qualifier on F's operator()
		{
			hamon::expected<int, int> e {0};
			auto val = e.and_then(LVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			VERIFY(e.and_then(UnexpectedLVal{}).error() == 5);
		}

		// With & qualifier on F's operator()
		{
			hamon::expected<int, int> e {0};
			RefQual l{};
			auto val = e.and_then(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			UnexpectedRefQual nl{};
			VERIFY(e.and_then(nl).error() == 5);
		}
	}

	// Test const& overload
	{
		// Without & qualifier on F's operator()
		{
			const hamon::expected<int, int> e {0};
			auto val = e.and_then(CLVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			VERIFY(e.and_then(UnexpectedCLVal{}).error() == 5);
		}

		// With & qualifier on F's operator()
		{
			const hamon::expected<int, int> e {0};
			const CRefQual l{};
			auto val = e.and_then(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			const UnexpectedCRefQual nl{};
			VERIFY(e.and_then(nl).error() == 5);
		}
	}

	// Test && overload
	{
		// Without & qualifier on F's operator()
		{
			hamon::expected<int, int> e {0};
			auto val = hamon::move(e).and_then(RVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			VERIFY(hamon::move(e).and_then(UnexpectedRVal{}).error() == 5);
		}

		// With & qualifier on F's operator()
		{
			hamon::expected<int, int> e {0};
			auto val = hamon::move(e).and_then(RVRefQual{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			VERIFY(e.and_then(UnexpectedRVRefQual{}).error() == 5);
		}
	}

	// Test const&& overload
	{
		// Without & qualifier on F's operator()
		{
			const hamon::expected<int, int> e {0};
			auto val = hamon::move(e).and_then(CRVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			VERIFY(hamon::move(e).and_then(UnexpectedCRVal{}).error() == 5);
		}

		// With & qualifier on F's operator()
		{
			const hamon::expected<int, int> e {0};
			const RVCRefQual l{};
			auto val = hamon::move(e).and_then(hamon::move(l));
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
			const UnexpectedRVCRefQual nl{};
			VERIFY(hamon::move(e).and_then(hamon::move(nl)).error() == 5);
		}
	}
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::expected<int, hamon::string> twice(int n)
{
	if (0 < n)
	{
		return n * 2;
	}
	else
	{
		return hamon::unexpected<hamon::string>{"out of domain"};
	}
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<int, hamon::string> v1 = 1;
	VERIFY(v1.and_then(twice).value() == 2);

	hamon::expected<int, hamon::string> v2 = 0;
	VERIFY(v2.and_then(twice).error() == "out of domain");

	hamon::expected<int, hamon::string> e1 = hamon::unexpected<hamon::string>{"NaN"};
	VERIFY(e1.and_then(twice).error() == "NaN");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, AndThenTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace and_then_test

}	// namespace hamon_expected_test
