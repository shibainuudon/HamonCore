/**
 *	@file	unit_test_scoped_allocator_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
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

namespace ctor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
class MyAlloc : public hamon::allocator<T>
{
public:
	constexpr MyAlloc(hamon::allocator<T> const&){}
};

inline HAMON_CXX20_CONSTEXPR bool test()
{
	using Alloc1 = hamon::scoped_allocator_adaptor<hamon::allocator<hamon::string>, hamon::allocator<char>>;
	using Alloc2 = hamon::scoped_allocator_adaptor<MyAlloc<hamon::string>, hamon::allocator<char>>;

	// (1)
	// デフォルト構築。
	// 各アロケータを値初期化する。
	Alloc1 alloc1;

	// (2)
	// 外側のアロケータと内側のアロケータ、それぞれを渡す
	Alloc1 alloc2
	{
		hamon::allocator<hamon::string>(), // vector自体のアロケータオブジェクト
		hamon::allocator<char>()    // vectorの全ての要素に使用するアロケータオブジェクト
	};

	// (3)
	// コピー構築。対応するアロケータオブジェクトにコピーする。
	Alloc1 alloc3 = alloc2;

	// (4)
	// ムーブ構築。対応するアロケータオブジェクトにムーブする。
	Alloc1 alloc4 = hamon::move(alloc3);

	Alloc2 alloc5 = alloc1;
	(void)alloc5;

	Alloc2 alloc6 = hamon::move(alloc4);
	(void)alloc6;

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, CtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace ctor_test

}	// namespace hamon_scoped_allocator_test
