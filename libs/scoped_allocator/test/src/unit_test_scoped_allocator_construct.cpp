/**
 *	@file	unit_test_scoped_allocator_construct.cpp
 *
 *	@brief	construct のテスト
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

namespace construct_test
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

template <class T>
using pair_of_vector = hamon::vector<
	T,
	hamon::scoped_allocator_adaptor<alloc_t<T>>
>;

inline HAMON_CXX20_CONSTEXPR bool test1()
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

	// (1) 以下のコンストラクタを呼び出し、アロケータオブジェクトを伝播させる
	// basic_string(const char*, Allocator)
	alloc.construct(p, str);

	// オブジェクトを破棄
	alloc.destroy(p);

	// メモリを解放
	alloc.deallocate(p, n);

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool test2()
{
	const char* str1 = "hello";
	const char* str2 = "world";

	pair_of_vector<hamon::pair<string, string>>::allocator_type alloc;

	const hamon::size_t n = 5;
	hamon::pair<string, string>* p = alloc.allocate(n);

	// (2)
	// pairの各要素に対して以下のコンストラクタを呼び出し、
	// アロケータオブジェクトを伝播させる。
	// basic_string(const char*, Allocator)
	hamon::pair<string, string>* pair_p = p;
	alloc.construct(p, hamon::piecewise_construct,
		hamon::forward_as_tuple(str1),
		hamon::forward_as_tuple(str2));
	VERIFY(pair_p->first == str1);
	VERIFY(pair_p->second == str2);

	// (3)
	// pairの要素をデフォルト構築する。
	pair_p = hamon::next(pair_p);
	alloc.construct(pair_p);
	VERIFY(pair_p->first == "");
	VERIFY(pair_p->second == "");

	// (4)
	// pairの各要素のコンストラクタ引数をひとつずつ受け取って構築
	pair_p = hamon::next(pair_p);
	alloc.construct(pair_p, str1, str2);
	VERIFY(pair_p->first == str1);
	VERIFY(pair_p->second == str2);

	// (5)
	// pairの各要素のコンストラクタ引数をひとつずつ、
	// まとめてpairとして受け取り、それぞれをtupleに分解して構築
	pair_p = hamon::next(pair_p);
	hamon::pair<const char*, const char*> fifth_args(str1, str2);
	alloc.construct(pair_p, fifth_args);

	// (6)
	// pairの各要素のコンストラクタ引数をひとつずつ、
	// まとめてpairとして受け取り、それぞれをtupleに分解して転送して構築
	pair_p = hamon::next(pair_p);
	alloc.construct(pair_p, hamon::make_pair(str1, str2));

	for (hamon::size_t i = 0; i < n; ++i)
	{
		alloc.destroy(p + i);
	}

	alloc.deallocate(p, n);

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, ConstructTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
}

}	// namespace construct_test

}	// namespace hamon_scoped_allocator_test
