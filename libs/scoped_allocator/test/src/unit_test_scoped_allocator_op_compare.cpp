/**
 *	@file	unit_test_scoped_allocator_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
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

namespace op_compare_test
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
constexpr bool operator==(const MyAlloc<T>& lhs, const MyAlloc<U>& rhs)
{
	return lhs.getState() == rhs.getState();
}

template <class T, class U>
constexpr bool operator!=(const MyAlloc<T>& lhs, const MyAlloc<U>& rhs)
{
	return !(lhs == rhs);
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
	vector<string>::allocator_type a1
	{
		alloc_t<string>(3),
		alloc_t<char>(4)
	};
	vector<string>::allocator_type a2
	{
		alloc_t<string>(3),
		alloc_t<char>(4)
	};
	vector<string>::allocator_type a3
	{
		alloc_t<string>(2),
		alloc_t<char>(4)
	};
	vector<string>::allocator_type a4
	{
		alloc_t<string>(3),
		alloc_t<char>(5)
	};

	VERIFY( (a1 == a2));
	VERIFY(!(a1 == a3));
	VERIFY(!(a1 == a4));

	VERIFY(!(a1 != a2));
	VERIFY( (a1 != a3));
	VERIFY( (a1 != a4));

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, OpCompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace op_compare_test

}	// namespace hamon_scoped_allocator_test
