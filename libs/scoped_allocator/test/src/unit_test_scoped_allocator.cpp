/**
 *	@file	unit_test_scoped_allocator_scoped_allocator_adaptor.cpp
 *
 *	@brief	scoped_allocator_adaptor のテスト
 */

#include <hamon/scoped_allocator/scoped_allocator_adaptor.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_scoped_allocator_test
{

namespace scoped_allocator_adaptor_test
{

template <typename T>
class MyAlloc : public hamon::allocator<T>
{
	int state_; // 状態

	template <typename>
	friend class MyAlloc;

public:
	template <typename U>
	struct rebind { using other = MyAlloc<U>; };

	constexpr MyAlloc(int state = 0)
		: state_(state)
	{}

	template <typename U>
	constexpr MyAlloc(const MyAlloc<U>& alloc)
		: state_(alloc.state_)
	{}

	constexpr int getState() const { return state_; }
};

template <typename T, typename U>
constexpr bool operator==(const MyAlloc<T>& lhs, const MyAlloc<U>& rhs)
{
	return lhs.getState() == rhs.getState();
}

template <typename T, typename U>
constexpr bool operator!=(const MyAlloc<T>& lhs, const MyAlloc<U>& rhs)
{
	return lhs.getState() != rhs.getState();
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX20_CONSTEXPR bool test1()
{
	// コンテナの要素(Inner)
	using forward_list = hamon::forward_list<
		int,
		MyAlloc<int>
	>;

	// コンテナ(Outer)
	using vector = hamon::vector<
		forward_list,
		hamon::scoped_allocator_adaptor<MyAlloc<forward_list>>
	>;

	int state = 5;
	MyAlloc<forward_list> alloc(state);
	vector v(alloc);

	v.push_back(forward_list{100});
	v.push_back(forward_list{200});

	// 同じアロケータオブジェクトが使われていることを確認する。
	// getState()の値が、どちらも5になる。
	VERIFY(v.get_allocator().getState() == state);
	VERIFY(v.front().get_allocator().getState() == state);

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool test2()
{
	// コンテナの要素(Inner)
	using forward_list = hamon::forward_list<
		int,
		MyAlloc<int>
	>;

	// コンテナ(Outer)
	using vector = hamon::vector<
		forward_list,
		hamon::scoped_allocator_adaptor<MyAlloc<forward_list>, MyAlloc<typename forward_list::value_type>>
	>;

	int outer_state = 5;
	int inner_state = 2;
	vector::allocator_type alloc
	{
		(MyAlloc<forward_list>(outer_state)), // vector自体のアロケータオブジェクト
		(MyAlloc<int>(inner_state))           // vectorの全ての要素に使用するアロケータオブジェクト
	};
	vector v(alloc);

	v.push_back(forward_list{100});
	v.push_back(forward_list{200});

	// コンテナに使用されるアロケータの状態を確認
	// 5になる(outer_state)
	VERIFY(v.get_allocator().getState() == outer_state);

	// 要素に使用されるアロケータの状態を確認
	// 全ての要素に、アロケータの状態が伝播される
	for (const forward_list& x : v)
	{
		VERIFY(x.get_allocator().getState() == inner_state);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, ScopedAllocatorAdaptorTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test1());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test2());
}

}	// namespace scoped_allocator_adaptor_test

}	// namespace hamon_scoped_allocator_test
