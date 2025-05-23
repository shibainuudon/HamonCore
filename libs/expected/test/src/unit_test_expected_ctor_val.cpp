/**
 *	@file	unit_test_expected_ctor_val.cpp
 *
 *	@brief	正常値からのコンストラクタのテスト
 */

#include <hamon/expected/expected.hpp>
#include <hamon/memory.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_val_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		T const src{17};
		hamon::expected<T, E> dst = src;
		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{17});
	}
	{
		hamon::expected<T, E> dst{T{18}};
		VERIFY(dst.has_value());
		VERIFY(dst.value() == T{18});
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;
	{
		IntPair const src{1, 2};
		hamon::expected<IntTuple, int> dst = src;
		VERIFY(dst.has_value());
		VERIFY((dst.value() == IntTuple{1, 2}));
	}
	{
		IntPair src{1, 2};
		hamon::expected<IntTuple, int> dst = hamon::move(src);
		VERIFY(dst.has_value());
		VERIFY((dst.value() == IntTuple{1, 2}));
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	using UniquePtr = hamon::unique_ptr<int>;
	using SharedPtr = hamon::shared_ptr<int>;
	{
		UniquePtr src2 = hamon::make_unique<int>(42);
		hamon::expected<SharedPtr, int> dst2 = hamon::move(src2);
		VERIFY(dst2.has_value());
		VERIFY(*dst2.value() == 42);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, CtorValTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3()));
}

}	// namespace ctor_val_test

}	// namespace hamon_expected_test
