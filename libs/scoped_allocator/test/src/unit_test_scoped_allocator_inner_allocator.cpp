/**
 *	@file	unit_test_scoped_allocator_inner_allocator.cpp
 *
 *	@brief	inner_allocator のテスト
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

namespace inner_allocator_test
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

inline HAMON_CXX20_CONSTEXPR bool test()
{
	{
		// コンテナの要素(Inner)
		using string = hamon::basic_string<
			char,
			hamon::char_traits<char>,
			alloc_t<char>
		>;

		// コンテナ(Outer)
		using vector = hamon::vector<
			string,
			hamon::scoped_allocator_adaptor<alloc_t<string>>
		>;

		int state = 5;
		vector::allocator_type alloc{state};

		// 内側(vectorの全ての要素)のアロケータオブジェクトを取得
		auto& inner_alloc = alloc.inner_allocator();
		VERIFY(inner_alloc.getState() == state);
		auto const& ca = alloc;
		auto const& inner_alloc2 = ca.inner_allocator();
		VERIFY(inner_alloc2.getState() == state);
	}
	{
		// コンテナの要素(Inner)
		using string = hamon::basic_string<
			char,
			hamon::char_traits<char>,
			alloc_t<char>
		>;

		// コンテナ(Outer)
		using vector = hamon::vector<
			string,
			hamon::scoped_allocator_adaptor<alloc_t<string>, alloc_t<typename string::value_type>>
		>;

		int outer_state = 5;
		int inner_state = 2;
		vector::allocator_type alloc
		{
			alloc_t<string>(outer_state), // vector自体のアロケータオブジェクト
			alloc_t<char>(inner_state)    // vectorの全ての要素に使用するアロケータオブジェクト
		};

		// 内側(vectorの全ての要素)のアロケータオブジェクトを取得
		auto& inner_alloc = alloc.inner_allocator();
		VERIFY(inner_alloc.getState() == inner_state);
		auto const& ca = alloc;
		auto const& inner_alloc2 = ca.inner_allocator();
		VERIFY(inner_alloc2.getState() == inner_state);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ScopedAllocatorTest, InnerAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace inner_allocator_test

}	// namespace hamon_scoped_allocator_test
