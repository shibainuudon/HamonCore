/**
 *	@file	unit_test_forward_list_insert_after.cpp
 *
 *	@brief	insert_after のテスト
 *
 *	iterator insert_after(const_iterator position, const T& x);
 *	iterator insert_after(const_iterator position, T&& x);
 *	iterator insert_after(const_iterator position, size_type n, const T& x);
 *	template<class InputIterator>
 *	iterator insert_after(const_iterator position, InputIterator first, InputIterator last);
 *	iterator insert_after(const_iterator position, initializer_list<T> il);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_forward_list_test
{

namespace insert_after_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator it;
		T const t{};
		static_assert(hamon::is_same<decltype(v.insert_after(it, t)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_after(it, t)), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		{
			T x{10};
			auto ret = v.insert_after(v.before_begin(), x);
			VERIFY(ret == v.begin());
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			T x{20};
			auto ret = v.insert_after(v.before_begin(), x);
			VERIFY(ret == v.begin());
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			T x{30};
			auto ret = v.insert_after(v.begin(), x);
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator it;
		T t{};
		static_assert(hamon::is_same<decltype(v.insert_after(it, hamon::move(t))), Iterator>::value, "");
		static_assert(!noexcept(v.insert_after(it, hamon::move(t))), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		{
			auto ret = v.insert_after(v.before_begin(), T{10});
			VERIFY(ret == v.begin());
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.insert_after(v.begin(), T{20});
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.insert_after(v.begin(), T{30});
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{30});
			VERIFY(*it++ == T{20});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test3()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;
	using SizeType = typename ForwardList::size_type;

	{
		ForwardList v;
		ConstIterator it;
		SizeType s;
		T const t{};
		static_assert(hamon::is_same<decltype(v.insert_after(it, s, t)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_after(it, s, t)), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		{
			T x{10};
			auto ret = v.insert_after(v.before_begin(), 2, x);
			VERIFY(ret == hamon::next(v.begin(), 1));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
		{
			T x{20};
			auto ret = v.insert_after(v.begin(), 3, x);
			VERIFY(ret == hamon::next(v.begin(), 3));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{10});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{20});
			VERIFY(*it++ == T{10});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T, template <typename> class IteratorWrapper>
FORWARD_LIST_TEST_CONSTEXPR bool test4()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;
	using InputIterator = IteratorWrapper<T>;

	{
		ForwardList v;
		ConstIterator pos;
		InputIterator first;
		InputIterator last;
		static_assert(hamon::is_same<decltype(v.insert_after(pos, first, last)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_after(pos, first, last)), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		{
			T a[] = {T{1},T{2},T{3}};
			auto ret = v.insert_after(v.before_begin(), InputIterator{a}, InputIterator{a + 3});
			VERIFY(ret == hamon::next(v.begin(), 2));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
		{
			T a[] = {T{4},T{5},T{6},T{7}};
			auto ret = v.insert_after(v.begin(), InputIterator{a}, InputIterator{a + 4});
			VERIFY(ret == hamon::next(v.begin(), 4));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{6});
			VERIFY(*it++ == T{7});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test5()
{
	using ForwardList = hamon::forward_list<T>;
	using Iterator = typename ForwardList::iterator;
	using ConstIterator = typename ForwardList::const_iterator;

	{
		ForwardList v;
		ConstIterator it;
		std::initializer_list<T> il;
		static_assert(hamon::is_same<decltype(v.insert_after(it, il)), Iterator>::value, "");
		static_assert(!noexcept(v.insert_after(it, il)), "");
	}
	{
		ForwardList v;
		VERIFY(v.empty());

		{
			auto ret = v.insert_after(v.before_begin(), {T{1},T{2},T{3}});
			VERIFY(ret == hamon::next(v.begin(), 2));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
		{
			auto ret = v.insert_after(v.begin(), {T{4},T{5}});
			VERIFY(ret == hamon::next(v.begin(), 2));
			VERIFY(!v.empty());
			auto it = v.begin();
			VERIFY(*it++ == T{1});
			VERIFY(*it++ == T{4});
			VERIFY(*it++ == T{5});
			VERIFY(*it++ == T{2});
			VERIFY(*it++ == T{3});
			VERIFY(it == v.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	VERIFY(test1<T>());
	VERIFY(test2<T>());
	VERIFY(test3<T>());
	VERIFY(test4<T, cpp17_input_iterator_wrapper>());
//	VERIFY(test4<T, input_iterator_wrapper>());
	VERIFY(test4<T, forward_iterator_wrapper>());
	VERIFY(test4<T, bidirectional_iterator_wrapper>());
	VERIFY(test4<T, random_access_iterator_wrapper>());
	VERIFY(test4<T, contiguous_iterator_wrapper>());
	VERIFY(test5<T>());
	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;
	static int s_instance_count;
	static int s_instance_max_count;

	MayThrow() : value(0)
	{
		Ctor();
	}

	MayThrow(int v) : value(v)
	{
		Ctor();
	}

	MayThrow(MayThrow const& other)
		: value(other.value)
	{
		Ctor();
	}

	MayThrow(MayThrow&& other)
		: value(other.value)
	{
		Ctor();
	}

	~MayThrow()
	{
		--s_instance_count;
	}

private:
	void Ctor()
	{
		if (s_instance_count >= s_instance_max_count)
		{
			throw Exception{};
		}
		++s_instance_count;
	}
};

int MayThrow::s_instance_count = 0;
int MayThrow::s_instance_max_count = 0;
#endif

GTEST_TEST(ForwardListTest, InsertAfterTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());

// 操作中に例外が発生した場合、副作用は発生しない
#if !defined(HAMON_NO_EXCEPTIONS)
	MayThrow::s_instance_count = 0;
	MayThrow::s_instance_max_count = 0;
	{
		MayThrow::s_instance_max_count = 3;

		hamon::forward_list<MayThrow> v;

		MayThrow const t(1);
		EXPECT_EQ(1, MayThrow::s_instance_count);

		v.insert_after(v.before_begin(), t);
		EXPECT_EQ(2, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.insert_after(v.begin(), t);
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_after(v.begin(), t), MayThrow::Exception);
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	EXPECT_EQ(0, MayThrow::s_instance_count);
	{
		MayThrow::s_instance_max_count = 3;

		hamon::forward_list<MayThrow> v;

		MayThrow t(1);
		EXPECT_EQ(1, MayThrow::s_instance_count);

		v.insert_after(v.before_begin(), hamon::move(t));
		EXPECT_EQ(2, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		v.insert_after(v.begin(), hamon::move(t));
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_after(v.begin(), hamon::move(t)), MayThrow::Exception);
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	EXPECT_EQ(0, MayThrow::s_instance_count);
	{
		MayThrow::s_instance_max_count = 5;

		hamon::forward_list<MayThrow> v;

		MayThrow const t(1);
		EXPECT_EQ(1, MayThrow::s_instance_count);

		v.insert_after(v.before_begin(), 2, t);
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_after(v.before_begin(), 3, t), MayThrow::Exception);
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(1, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	EXPECT_EQ(0, MayThrow::s_instance_count);
	{
		MayThrow::s_instance_max_count = 8;

		hamon::forward_list<MayThrow> v;

		MayThrow const t[] {MayThrow(1), MayThrow(2), MayThrow(3)};
		EXPECT_EQ(3, MayThrow::s_instance_count);

		v.insert_after(v.before_begin(), t, t + 3);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_after(v.before_begin(), t, t + 3), MayThrow::Exception);
		EXPECT_EQ(6, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	EXPECT_EQ(0, MayThrow::s_instance_count);
	{
		MayThrow::s_instance_max_count = 6;

		hamon::forward_list<MayThrow> v;

		EXPECT_EQ(0, MayThrow::s_instance_count);

		v.insert_after(v.before_begin(), {MayThrow(1), MayThrow(2), MayThrow(3)});
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}

		EXPECT_THROW(v.insert_after(v.before_begin(), {MayThrow(4), MayThrow(5)}), MayThrow::Exception);
		EXPECT_EQ(3, MayThrow::s_instance_count);
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(3, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
	EXPECT_EQ(0, MayThrow::s_instance_count);
#endif
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace insert_after_test

}	// namespace hamon_forward_list_test
