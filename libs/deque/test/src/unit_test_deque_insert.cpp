/**
 *	@file	unit_test_deque_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(const_iterator position, const T& x);
 *	iterator insert(const_iterator position, T&& x);
 *	iterator insert(const_iterator position, size_type n, const T& x);
 *	template<class InputIterator>
 *	iterator insert(const_iterator position, InputIterator first, InputIterator last);
 *	iterator insert(const_iterator position, initializer_list<T> il);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_deque_test
{

namespace insert_test
{

template <typename T, typename Deque>
HAMON_CXX20_CONSTEXPR bool ValidReference(T const& t, Deque const& d)
{
	for (auto& x : d)
	{
		if (t == x)
		{
			return true;
		}
	}
	return false;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T const&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T const&>())), "");

	{
		Deque v;
		T const x = 10;
		auto ret = v.insert(v.end(), x);
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);
	}
	{
		Deque v{1,2,3};
		T const x = 10;
		auto ret = v.insert(v.begin() + 1, x);
		VERIFY(ret == v.begin() + 1);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin(), x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 1, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 2, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
	}
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 3, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 20);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T&&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<T&&>())), "");

	{
		Deque v;
		auto ret = v.insert(v.begin(), T{10});
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);
	}
	{
		Deque v{1,2,3};
		{
			auto ret = v.insert(v.begin() + 2, T{20});
			VERIFY(ret == v.begin() + 2);
		}
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
		{
			auto ret = v.insert(v.end(), T{30});
			VERIFY(ret == v.begin() + 4);
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
		VERIFY(v[4] == 30);
		{
			auto ret = v.insert(v.begin(), T{40});
			VERIFY(ret == v.begin());
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 40);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 3);
		VERIFY(v[5] == 30);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin(), T{20});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 20);
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
		v.insert(v.begin() + 1, T{20});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 20);
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
		v.insert(v.begin() + 2, T{20});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 3);
		VERIFY(v[4] == 4);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin() + 3, T{20});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 4);
	}
	{
		Deque v{1,2,3,4};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin() + 4, T{20});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
		VERIFY(v[4] == 20);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using Deque = hamon::deque<T>;
	using SizeType = typename Deque::size_type;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<SizeType>(), hamon::declval<T const&>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	{
		Deque v;
		auto ret = v.insert(v.begin(), 3, 13);
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 13);
		VERIFY(v[1] == 13);
		VERIFY(v[2] == 13);
	}
	{
		Deque v{1,2,3};
		{
			auto ret = v.insert(v.begin() + 2, 4, 42);
			VERIFY(ret == v.begin() + 2);
		}
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 42);
		VERIFY(v[3] == 42);
		VERIFY(v[4] == 42);
		VERIFY(v[5] == 42);
		VERIFY(v[6] == 3);
		{
			auto ret = v.insert(v.begin(), 3, 43);
			VERIFY(ret == v.begin());
		}
		VERIFY(v.size() == 10);
		VERIFY(v[0] == 43);
		VERIFY(v[1] == 43);
		VERIFY(v[2] == 43);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 42);
		VERIFY(v[6] == 42);
		VERIFY(v[7] == 42);
		VERIFY(v[8] == 42);
		VERIFY(v[9] == 3);
		{
			auto ret = v.insert(v.end(), 5, 44);
			VERIFY(ret == v.begin() + 10);
		}
		VERIFY(v.size() == 15);
		VERIFY(v[0] == 43);
		VERIFY(v[1] == 43);
		VERIFY(v[2] == 43);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 42);
		VERIFY(v[6] == 42);
		VERIFY(v[7] == 42);
		VERIFY(v[8] == 42);
		VERIFY(v[9] == 3);
		VERIFY(v[10] == 44);
		VERIFY(v[11] == 44);
		VERIFY(v[12] == 44);
		VERIFY(v[13] == 44);
		VERIFY(v[14] == 44);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin(), 2, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 1);
		VERIFY(v[3] == 2);
		VERIFY(v[4] == 3);
	}
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 1, 2, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 2);
		VERIFY(v[4] == 3);
	}
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 2, 2, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 3);
	}
	{
		Deque v{1,2,3};
		T const x = 20;
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 3, 2, x);
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 20);
	}

	return true;
}

template <template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test4()
{
	using T = int;
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;
	using InputIterator = IteratorWrapper<int>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<InputIterator>(), hamon::declval<InputIterator>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

	{
		Deque v;
		int a[] = {11,12,13,14,15};
		auto ret = v.insert(v.begin(), InputIterator{a}, InputIterator{a + 4});
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 14);
	}
	{
		Deque v{1,2,3};
		int a[] = {11,12,13,14,15};
		{
			auto ret = v.insert(v.begin() + 1, InputIterator{a}, InputIterator{a + 3});
			VERIFY(ret == v.begin() + 1);
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
		{
			auto ret = v.insert(v.end(), InputIterator{a + 2}, InputIterator{a + 5});
			VERIFY(ret == v.begin() + 6);
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
		VERIFY(v[6] == 13);
		VERIFY(v[7] == 14);
		VERIFY(v[8] == 15);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3,4};
		int a[] = {11,12,13};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin(), InputIterator{a}, InputIterator{a + 3});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
		VERIFY(v[6] == 4);
	}
	{
		Deque v{1,2,3,4};
		int a[] = {11,12,13};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin() + 1, InputIterator{a}, InputIterator{a + 3});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
		VERIFY(v[6] == 4);
	}
	{
		Deque v{1,2,3,4};
		int a[] = {11,12,13};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin() + 2, InputIterator{a}, InputIterator{a + 3});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 11);
		VERIFY(v[3] == 12);
		VERIFY(v[4] == 13);
		VERIFY(v[5] == 3);
		VERIFY(v[6] == 4);
	}
	{
		Deque v{1,2,3,4};
		int a[] = {11,12,13};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin() + 3, InputIterator{a}, InputIterator{a + 3});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 11);
		VERIFY(v[4] == 12);
		VERIFY(v[5] == 13);
		VERIFY(v[6] == 4);
	}
	{
		Deque v{1,2,3,4};
		int a[] = {11,12,13};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];
		v.insert(v.begin() + 4, InputIterator{a}, InputIterator{a + 3});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(ValidReference(r3, v));
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
		VERIFY(v[4] == 11);
		VERIFY(v[5] == 12);
		VERIFY(v[6] == 13);
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test5()
{
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<std::initializer_list<T>>())),
		Iterator
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().insert(hamon::declval<ConstIterator>(), hamon::declval<std::initializer_list<T>>())), "");

	{
		Deque v;
		auto ret = v.insert(v.begin(), {1,2,3});
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}
	{
		Deque v{1,2,3};
		auto ret = v.insert(v.begin() + 2, {11,12,13,14});
		VERIFY(ret == v.begin() + 2);
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 11);
		VERIFY(v[3] == 12);
		VERIFY(v[4] == 13);
		VERIFY(v[5] == 14);
		VERIFY(v[6] == 3);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin(), {11,12,13});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
	}
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 1, {11,12,13});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
	}
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 2, {11,12,13});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 11);
		VERIFY(v[3] == 12);
		VERIFY(v[4] == 13);
		VERIFY(v[5] == 3);
	}
	{
		Deque v{1,2,3};
		auto& r0 = v[0];
		auto& r1 = v[1];
		auto& r2 = v[2];
		v.insert(v.begin() + 3, {11,12,13});
		VERIFY(ValidReference(r0, v));
		VERIFY(ValidReference(r1, v));
		VERIFY(ValidReference(r2, v));
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 11);
		VERIFY(v[4] == 12);
		VERIFY(v[5] == 13);
	}

	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy() : value(13)
	{
	}

	ThrowOnCopy(int v) : value(v)
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}

	ThrowOnCopy(ThrowOnCopy&& other) noexcept
		: value(other.value)
	{
	}

	ThrowOnCopy& operator=(ThrowOnCopy const&)
	{
		throw Exception{};
	}
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove() : value(14)
	{
	}

	ThrowOnMove(int v) : value(v)
	{
	}

	ThrowOnMove(ThrowOnMove const& other)
		: value(other.value)
	{
	}

	ThrowOnMove& operator=(ThrowOnMove const&) = default;

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}

	ThrowOnMove& operator=(ThrowOnMove&&)
	{
		throw Exception{};
	}
};
#endif

GTEST_TEST(DequeTest, InsertTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<double>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<cpp17_input_iterator_wrapper>());
//	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<input_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<forward_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<bidirectional_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<random_access_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4<contiguous_iterator_wrapper>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test5<double>());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::deque<ThrowOnCopy> v;

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.insert(v.end(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.insert(v.end(), ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v(2);

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.insert(v.end(), t), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.insert(v.end(), ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::deque<ThrowOnCopy> v(2);

		EXPECT_THROW(v.insert(v.end(), 3, ThrowOnCopy(2)), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
	}
	{
		hamon::deque<ThrowOnCopy> v1(3);
		hamon::deque<ThrowOnCopy> v2(2);

		EXPECT_THROW(v2.insert(v2.end(), v1.begin(), v1.end()), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
	{
		hamon::deque<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.insert(v.end(), t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		EXPECT_THROW(v.insert(v.end(), ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
#endif
}

}	// namespace insert_test

}	// namespace hamon_deque_test
