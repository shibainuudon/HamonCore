/**
 *	@file	unit_test_memory_make_shared.cpp
 *
 *	@brief	make_shared のテスト
 *
 *	template<class T, class... Args>
 *	shared_ptr<T> make_shared(Args&&... args);
 *
 *	template<class T>
 *	shared_ptr<T> make_shared(size_t N);
 *
 *	template<class T>
 *	shared_ptr<T> make_shared();
 *
 *	template<class T>
 *	shared_ptr<T> make_shared(size_t N, const remove_extent_t<T>& u);
 *
 *	template<class T>
 *	shared_ptr<T> make_shared(const remove_extent_t<T>& u);
 */

#include <hamon/memory/make_shared.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace make_shared_test
{

struct X
{
	int x;
	int y;
	int z;

	constexpr X(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	// (1)
	{
		auto sp = hamon::make_shared<int>(2);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(*sp == 2);
	}
	{
		auto sp = hamon::make_shared<X>(10, 20, 30);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<X>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp->x == 10);
		VERIFY(sp->y == 20);
		VERIFY(sp->z == 30);
	}

	// (2)
	{
		auto sp = hamon::make_shared<int[]>(3);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0] == 0);
		VERIFY(sp[1] == 0);
		VERIFY(sp[2] == 0);
	}
	{
		auto sp = hamon::make_shared<long[][3]>(4);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<long[][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0] == 0);
		VERIFY(sp[0][1] == 0);
		VERIFY(sp[0][2] == 0);
		VERIFY(sp[1][0] == 0);
		VERIFY(sp[1][1] == 0);
		VERIFY(sp[1][2] == 0);
		VERIFY(sp[2][0] == 0);
		VERIFY(sp[2][1] == 0);
		VERIFY(sp[2][2] == 0);
		VERIFY(sp[3][0] == 0);
		VERIFY(sp[3][1] == 0);
		VERIFY(sp[3][2] == 0);
	}
	{
		auto sp = hamon::make_shared<int[][2][3]>(4);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[][2][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0][0] == 0);
		VERIFY(sp[0][0][1] == 0);
		VERIFY(sp[0][0][2] == 0);
		VERIFY(sp[0][1][0] == 0);
		VERIFY(sp[0][1][1] == 0);
		VERIFY(sp[0][1][2] == 0);
		VERIFY(sp[1][0][0] == 0);
		VERIFY(sp[1][0][1] == 0);
		VERIFY(sp[1][0][2] == 0);
		VERIFY(sp[1][1][0] == 0);
		VERIFY(sp[1][1][1] == 0);
		VERIFY(sp[1][1][2] == 0);
		VERIFY(sp[2][0][0] == 0);
		VERIFY(sp[2][0][1] == 0);
		VERIFY(sp[2][0][2] == 0);
		VERIFY(sp[2][1][0] == 0);
		VERIFY(sp[2][1][1] == 0);
		VERIFY(sp[2][1][2] == 0);
		VERIFY(sp[3][0][0] == 0);
		VERIFY(sp[3][0][1] == 0);
		VERIFY(sp[3][0][2] == 0);
		VERIFY(sp[3][1][0] == 0);
		VERIFY(sp[3][1][1] == 0);
		VERIFY(sp[3][1][2] == 0);
	}

	// (3)
	{
		auto sp = hamon::make_shared<long[4]>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<long[4]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0] == 0);
		VERIFY(sp[1] == 0);
		VERIFY(sp[2] == 0);
		VERIFY(sp[3] == 0);
	}
	{
		auto sp = hamon::make_shared<float[3][2]>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<float[3][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0] == 0);
		VERIFY(sp[0][1] == 0);
		VERIFY(sp[1][0] == 0);
		VERIFY(sp[1][1] == 0);
		VERIFY(sp[2][0] == 0);
		VERIFY(sp[2][1] == 0);
	}
	{
		auto sp = hamon::make_shared<int[2][3][4]>();
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[2][3][4]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0][0] == 0);
		VERIFY(sp[0][0][1] == 0);
		VERIFY(sp[0][0][2] == 0);
		VERIFY(sp[0][0][3] == 0);
		VERIFY(sp[0][1][0] == 0);
		VERIFY(sp[0][1][1] == 0);
		VERIFY(sp[0][1][2] == 0);
		VERIFY(sp[0][1][3] == 0);
		VERIFY(sp[0][2][0] == 0);
		VERIFY(sp[0][2][1] == 0);
		VERIFY(sp[0][2][2] == 0);
		VERIFY(sp[0][2][3] == 0);
		VERIFY(sp[1][0][0] == 0);
		VERIFY(sp[1][0][1] == 0);
		VERIFY(sp[1][0][2] == 0);
		VERIFY(sp[1][0][3] == 0);
		VERIFY(sp[1][1][0] == 0);
		VERIFY(sp[1][1][1] == 0);
		VERIFY(sp[1][1][2] == 0);
		VERIFY(sp[1][1][3] == 0);
		VERIFY(sp[1][2][0] == 0);
		VERIFY(sp[1][2][1] == 0);
		VERIFY(sp[1][2][2] == 0);
		VERIFY(sp[1][2][3] == 0);
	}

	// (4)
	{
		auto sp = hamon::make_shared<int[]>(3, 42);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0] == 42);
		VERIFY(sp[1] == 42);
		VERIFY(sp[2] == 42);
	}
	{
		auto sp = hamon::make_shared<double[][2]>(4, {3.0, 4.0});
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<double[][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0] == 3.0);
		VERIFY(sp[0][1] == 4.0);
		VERIFY(sp[1][0] == 3.0);
		VERIFY(sp[1][1] == 4.0);
		VERIFY(sp[2][0] == 3.0);
		VERIFY(sp[2][1] == 4.0);
		VERIFY(sp[3][0] == 3.0);
		VERIFY(sp[3][1] == 4.0);
	}
	{
		int a[2][3] = {{1,2,3},{4,5,6}};
		auto sp = hamon::make_shared<int[][2][3]>(4, a);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int[][2][3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0][0] == 1);
		VERIFY(sp[0][0][1] == 2);
		VERIFY(sp[0][0][2] == 3);
		VERIFY(sp[0][1][0] == 4);
		VERIFY(sp[0][1][1] == 5);
		VERIFY(sp[0][1][2] == 6);
		VERIFY(sp[1][0][0] == 1);
		VERIFY(sp[1][0][1] == 2);
		VERIFY(sp[1][0][2] == 3);
		VERIFY(sp[1][1][0] == 4);
		VERIFY(sp[1][1][1] == 5);
		VERIFY(sp[1][1][2] == 6);
		VERIFY(sp[2][0][0] == 1);
		VERIFY(sp[2][0][1] == 2);
		VERIFY(sp[2][0][2] == 3);
		VERIFY(sp[2][1][0] == 4);
		VERIFY(sp[2][1][1] == 5);
		VERIFY(sp[2][1][2] == 6);
		VERIFY(sp[3][0][0] == 1);
		VERIFY(sp[3][0][1] == 2);
		VERIFY(sp[3][0][2] == 3);
		VERIFY(sp[3][1][0] == 4);
		VERIFY(sp[3][1][1] == 5);
		VERIFY(sp[3][1][2] == 6);
	}

	// (5)
	{
		auto sp = hamon::make_shared<float[3]>(5);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<float[3]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0] == 5);
		VERIFY(sp[1] == 5);
		VERIFY(sp[2] == 5);
	}
	{
		auto sp = hamon::make_shared<double[3][2]>({3.0, 4.0});
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<double[3][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0] == 3.0);
		VERIFY(sp[0][1] == 4.0);
		VERIFY(sp[1][0] == 3.0);
		VERIFY(sp[1][1] == 4.0);
		VERIFY(sp[2][0] == 3.0);
		VERIFY(sp[2][1] == 4.0);
	}
	{
		double a[3][2] = {{1.0, 2.0},{3.0, 4.0},{5.0, 6.0}};
		auto sp = hamon::make_shared<double[4][3][2]>(a);
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<double[4][3][2]>>::value, "");
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(sp[0][0][0] == 1.0);
		VERIFY(sp[0][0][1] == 2.0);
		VERIFY(sp[0][1][0] == 3.0);
		VERIFY(sp[0][1][1] == 4.0);
		VERIFY(sp[0][2][0] == 5.0);
		VERIFY(sp[0][2][1] == 6.0);
		VERIFY(sp[1][0][0] == 1.0);
		VERIFY(sp[1][0][1] == 2.0);
		VERIFY(sp[1][1][0] == 3.0);
		VERIFY(sp[1][1][1] == 4.0);
		VERIFY(sp[1][2][0] == 5.0);
		VERIFY(sp[1][2][1] == 6.0);
		VERIFY(sp[2][0][0] == 1.0);
		VERIFY(sp[2][0][1] == 2.0);
		VERIFY(sp[2][1][0] == 3.0);
		VERIFY(sp[2][1][1] == 4.0);
		VERIFY(sp[2][2][0] == 5.0);
		VERIFY(sp[2][2][1] == 6.0);
		VERIFY(sp[3][0][0] == 1.0);
		VERIFY(sp[3][0][1] == 2.0);
		VERIFY(sp[3][1][0] == 3.0);
		VERIFY(sp[3][1][1] == 4.0);
		VERIFY(sp[3][2][0] == 5.0);
		VERIFY(sp[3][2][1] == 6.0);
	}
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(MemoryTest, MakeSharedTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace make_shared_test

}	// namespace hamon_memory_test
