/**
 *	@file	unit_test_deque_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args> iterator emplace(const_iterator position, Args&&... args);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace emplace_test
{

template <typename T, typename Deque>
HAMON_CXX20_CONSTEXPR bool ValidReference(T const& t, Deque const& d)
{
	for (auto& x : d)
	{
		if (&t == &x)
		{
			return true;
		}
	}
	return false;
}

struct MoveOnly
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnly(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly const& x) : value(x.value) {} //= delete;	// TODO Visual Studio 2019 だけ？
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly && x) noexcept : value(x.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly const&) = delete;
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly && x) noexcept { value = x.value; return *this; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().emplace(hamon::declval<ConstIterator>())),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().emplace(hamon::declval<ConstIterator>(), hamon::declval<T>())),
		Iterator
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().emplace(hamon::declval<ConstIterator>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().emplace(hamon::declval<ConstIterator>(), hamon::declval<T>())), "");

	{

		Deque v;
		{
			auto r = v.emplace(v.begin(), T{10});
			VERIFY(r == v.begin());
		}
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		{
			auto r = v.emplace(v.begin(), T{20});
			VERIFY(r == v.begin());
		}
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 10);

		{
			auto r = v.emplace(v.end(), T{30});
			VERIFY(r == v.begin() + 2);
		}
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 30);

		{
			auto r = v.emplace(v.begin() + 2, T{40});
			VERIFY(r == v.begin() + 2);
		}
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 40);
		VERIFY(v[3] == 30);

		{
			auto r = v.emplace(v.begin() + 1, T{50});
			VERIFY(r == v.begin() + 1);
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 50);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 30);

		{
			auto r = v.emplace(v.begin() + 1, T{60});
			VERIFY(r == v.begin() + 1);
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 60);
		VERIFY(v[2] == 50);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 40);
		VERIFY(v[5] == 30);

		{
			auto r = v.emplace(v.begin() + 3, T{70});
			VERIFY(r == v.begin() + 3);
		}
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 60);
		VERIFY(v[2] == 50);
		VERIFY(v[3] == 70);
		VERIFY(v[4] == 10);
		VERIFY(v[5] == 40);
		VERIFY(v[6] == 30);

		{
			auto r = v.emplace(v.begin() + 5, T{80});
			VERIFY(r == v.begin() + 5);
		}
		VERIFY(v.size() == 8);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 60);
		VERIFY(v[2] == 50);
		VERIFY(v[3] == 70);
		VERIFY(v[4] == 10);
		VERIFY(v[5] == 80);
		VERIFY(v[6] == 40);
		VERIFY(v[7] == 30);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.emplace(v.begin(), T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.emplace(v.begin() + 1, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.emplace(v.begin() + 2, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 3);
	}
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.emplace(v.begin() + 3, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 10);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.emplace(v.begin(), T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
		VERIFY(v[4] == 4);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.emplace(v.begin() + 1, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
		VERIFY(v[4] == 4);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.emplace(v.begin() + 2, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 3);
		VERIFY(v[4] == 4);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.emplace(v.begin() + 3, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 4);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.emplace(v.begin() + 4, T{10});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
		VERIFY(v[4] == 10);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::deque<MoveOnly> v;

		auto r1 = v.emplace(v.begin(), 10);
		VERIFY(r1 == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0].value == 10);

		auto r2 = v.emplace(v.begin(), 11);
		VERIFY(r2 == v.begin());
		VERIFY(v.size() == 2);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 10);

		auto r3 = v.emplace(v.begin() + 1, 12);
		VERIFY(r3 == v.begin() + 1);
		VERIFY(v.size() == 3);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 12);
		VERIFY(v[2].value == 10);

		auto r4 = v.emplace(v.end(), 13);
		VERIFY(r4 == v.begin() + 3);
		VERIFY(v.size() == 4);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 12);
		VERIFY(v[2].value == 10);
		VERIFY(v[3].value == 13);
	}

	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}
};
#endif

GTEST_TEST(DequeTest, EmplaceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::deque<MayThrow> v;

		v.emplace(v.end(), 2);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);

		EXPECT_THROW(v.emplace(v.end(), -2), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
#endif
}

}	// namespace emplace_test

}	// namespace hamon_deque_test
