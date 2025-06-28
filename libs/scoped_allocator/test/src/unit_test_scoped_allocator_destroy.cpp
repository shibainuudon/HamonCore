/**
 *	@file	unit_test_scoped_allocator_destroy.cpp
 *
 *	@brief	destroy のテスト
 */

#include <hamon/scoped_allocator/scoped_allocator_adaptor.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_scoped_allocator_test
{

namespace destroy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <class T>
using alloc_t = hamon::allocator<T>;

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
	const char* str = "hello";

	vector<string>::allocator_type alloc
	{
		alloc_t<string>(), // vector自体のアロケータオブジェクト
		alloc_t<char>()    // vectorの全ての要素に使用するアロケータオブジェクト
	};

	// 外側のアロケータを使用し、stringが1要素入るメモリを確保
	const hamon::size_t n = 1;
	string* p = alloc.allocate(n);

	// オブジェクトを構築
	alloc.construct(p, str);

	// オブジェクトを破棄
	alloc.destroy(p);

	// メモリを解放
	alloc.deallocate(p, n);

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, DestroyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace destroy_test

}	// namespace hamon_scoped_allocator_test
