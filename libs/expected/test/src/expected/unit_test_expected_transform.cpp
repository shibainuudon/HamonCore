/**
 *	@file	unit_test_expected_transform.cpp
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
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/numeric/iota.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace transform_test
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
struct has_transform
	: hamon::false_type{};

template <typename E, typename F>
struct has_transform<E, F, hamon::void_t<decltype(hamon::declval<E>().transform(hamon::declval<F>()))>>
	: hamon::true_type{};

static_assert( has_transform<hamon::expected<int, int        >&,       int(int&)>::value, "");
static_assert(!has_transform<hamon::expected<int, NonCopyable>&,       int(int&)>::value, "");
static_assert( has_transform<hamon::expected<int, int        > const&, int(int const&)>::value, "");
static_assert(!has_transform<hamon::expected<int, NonCopyable> const&, int(int const&)>::value, "");
static_assert( has_transform<hamon::expected<int, int       >&&,       int(int)>::value, "");
static_assert(!has_transform<hamon::expected<int, NonMovable>&&,       int(int)>::value, "");
static_assert( has_transform<hamon::expected<int, int       > const&&, int(int const)>::value, "");
static_assert(!has_transform<hamon::expected<int, NonMovable> const&&, int(int const)>::value, "");

// [LWG 3877] https://cplusplus.github.io/LWG/issue3877, check constraint failing but not compile error inside the function body.
static_assert(!has_transform<const hamon::expected<int, hamon::unique_ptr<int>>&, int()>::value, "");
static_assert(!has_transform<const hamon::expected<int, hamon::unique_ptr<int>>&&, int()>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	struct F
	{
		constexpr int operator()(T n) const
		{
			return static_cast<int>(n * n);
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &      >().transform(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const& >().transform(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> &&     >().transform(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<T, E> const&&>().transform(f)), hamon::expected<int, E>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &      >().transform(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const& >().transform(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> &&     >().transform(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<T, E> const&&>().transform(f)), "");

	{
		hamon::expected<T, E> e1 = T{2};
		auto e2 = e1.transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 4);
	}
	{
		hamon::expected<T, E> e1 = hamon::unexpected<E>{E{10}};
		auto e2 = e1.transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{10});
	}
	{
		hamon::expected<T, E> const e1 = T{3};
		auto e2 = e1.transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 9);
	}
	{
		hamon::expected<T, E> const e1 = hamon::unexpected<E>{E{11}};
		auto e2 = e1.transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{11});
	}
	{
		hamon::expected<T, E> e1 = T{4};
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 16);
	}
	{
		hamon::expected<T, E> e1 = hamon::unexpected<E>{E{12}};
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(!e2.has_value());
		VERIFY(e2.error() == E{12});
	}
	{
		hamon::expected<T, E> const e1 = T{5};
		auto e2 = hamon::move(e1).transform(f);
		VERIFY(e2.has_value());
		VERIFY(e2.value() == 25);
	}
	{
		hamon::expected<T, E> const e1 = hamon::unexpected<E>{E{13}};
		auto e2 = hamon::move(e1).transform(f);
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
			hamon::expected<int, int> e(0);
			auto val = e.transform(LVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With & qualifier on F's operator()
		{
			hamon::expected<int, int> e(0);
			RefQual l{};
			auto val = e.transform(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}

	// Test const& overload
	{
		// Without & qualifier on F's operator()
		{
			const hamon::expected<int, int> e(0);
			auto val = e.transform(CLVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With & qualifier on F's operator()
		{
			const hamon::expected<int, int> e(0);
			const CRefQual l{};
			auto val = e.transform(l);
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}

	// Test && overload
	{
		// Without & qualifier on F's operator()
		{
			hamon::expected<int, int> e(0);
			auto val = hamon::move(e).transform(RVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With & qualifier on F's operator()
		{
			hamon::expected<int, int> e(0);
			auto val = hamon::move(e).transform(RVRefQual{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}

	// Test const&& overload
	{
		// Without & qualifier on F's operator()
		{
			const hamon::expected<int, int> e(0);
			auto val = hamon::move(e).transform(CRVal{});
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}

		// With & qualifier on F's operator()
		{
			const hamon::expected<int, int> e(0);
			const RVCRefQual l{};
			auto val = e.transform(hamon::move(l));
			static_assert(hamon::is_same<decltype(val), hamon::expected<int, int>>::value, "");
			VERIFY(val.value() == 1);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_return_void()
{
	struct F
	{
		bool invoked = false;
		HAMON_CXX14_CONSTEXPR void operator()(int)
		{
			invoked = true;
		}
	};

	{
		F f;
		hamon::expected<int, int> e(hamon::in_place, 1);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> e(hamon::unexpect, 1);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> const e(hamon::in_place, 1);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> const e(hamon::unexpect, 1);
		auto r = e.transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> e(hamon::in_place, 1);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> e(hamon::unexpect, 1);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(!r.has_value());
		VERIFY(r.error() == 1);
		VERIFY(!f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> const e(hamon::in_place, 1);
		auto r = hamon::move(e).transform(f);
		static_assert(hamon::is_same<decltype(r), hamon::expected<void, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(f.invoked);
	}
	{
		F f;
		hamon::expected<int, int> const e(hamon::unexpect, 1);
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
		hamon::expected<int, int> e(42);
		auto r = e.transform([](int i){return NonMovable(i);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 42);
	}
	{
		hamon::expected<int, int> const e(42);
		auto r = e.transform([](int i){return NonMovable(i + 1);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 43);
	}
	{
		hamon::expected<int, int> e(42);
		auto r = hamon::move(e).transform([](int i){return NonMovable(i * 2);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 84);
	}
	{
		hamon::expected<int, int> const e(42);
		auto r = hamon::move(e).transform([](int i){return NonMovable(i - 1);});
		static_assert(hamon::is_same<decltype(r), hamon::expected<NonMovable, int>>::value, "");
		VERIFY(r.has_value());
		VERIFY(r.value().value == 41);
	}
#endif
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::vector<int> make_seq(int n)
{
	hamon::vector<int> seq(static_cast<hamon::size_t>(n), 0);
	hamon::iota(seq.begin(), seq.end(), 1);
	return seq;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<int, hamon::string> v1 = 3;
	VERIFY((v1.transform(make_seq).value() == hamon::vector<int>{1, 2, 3}));

	hamon::expected<int, hamon::string> e1 = hamon::unexpected<hamon::string>{"NaN"};
	VERIFY(e1.transform(make_seq).error() == "NaN");

	return true;
}

#undef VERIFY


GTEST_TEST(ExpectedTest, TransformTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_return_void()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_direct_non_list_init()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace transform_test

}	// namespace hamon_expected_test
