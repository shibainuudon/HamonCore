/**
 *	@file	unit_test_scoped_allocator_outer_allocator.cpp
 *
 *	@brief	outer_allocator のテスト
 */

#include <hamon/scoped_allocator/scoped_allocator_adaptor.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/tuple.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_scoped_allocator_test
{

namespace outer_allocator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <class T>
class MyAlloc : public hamon::allocator<T>
{
	int state_; // 状態

	using BaseType = hamon::allocator<T>;
	template <class> friend class MyAlloc;
public:
	using BaseType::BaseType;

	constexpr MyAlloc(int state = 0)
		: state_(state) {}

	template <class U>
	constexpr MyAlloc(const MyAlloc<U>& alloc)
		: state_(alloc.state_) {}

	constexpr int getState() const { return state_; }
};

template <class T, class U>
constexpr bool operator==(const MyAlloc<T>&, const MyAlloc<U>&)
{
	return true;
}

template <class T, class U>
constexpr bool operator!=(const MyAlloc<T>&, const MyAlloc<U>&)
{
	return false;
}

template <class T>
using alloc_t = MyAlloc<T>;

// コンテナの要素(Inner)
using string = hamon::basic_string<
	char,
	hamon::char_traits<char>,
	alloc_t<char>
>;

// コンテナ(Outer)
template <class T>
using vector = hamon::vector<
	T,
	hamon::scoped_allocator_adaptor<alloc_t<T>, alloc_t<typename T::value_type>>
>;

inline HAMON_CXX20_CONSTEXPR bool test()
{
	int outer_state = 5;
	int inner_state = 2;
	vector<string>::allocator_type alloc
	{
		alloc_t<string>(outer_state), // vector自体のアロケータオブジェクト
		alloc_t<char>(inner_state)    // vectorの全ての要素に使用するアロケータオブジェクト
	};

	// 外側(vector自体)のアロケータオブジェクトを取得
	auto& outer_alloc = alloc.outer_allocator();
	VERIFY(outer_alloc.getState() == 5);
	auto const& ca = alloc;
	auto const& outer_alloc2 = ca.outer_allocator();
	VERIFY(outer_alloc2.getState() == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, OuterAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace outer_allocator_test

}	// namespace hamon_scoped_allocator_test
