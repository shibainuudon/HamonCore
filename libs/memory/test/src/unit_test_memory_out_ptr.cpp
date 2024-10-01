/**
 *	@file	unit_test_memory_out_ptr.cpp
 *
 *	@brief	out_ptr のテスト
 */

#include <hamon/memory/out_ptr.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <memory>

namespace hamon_memory_test
{

namespace out_ptr_test
{

inline void get_int_p(int** pp)
{
	*pp = new int{42};
}

inline void get_int_p_nullptr(int** pp)
{
	*pp = nullptr;
}

inline void get_void_p(void** pp)
{
	*(reinterpret_cast<int**>(pp)) = new int{43};
}

inline void get_void_p_nullptr(void** pp)
{
	*pp = nullptr;
}

struct Deleter
{
	template <typename T>
	void operator()(T* p) const { delete p; }
};

struct MoveOnlyDeleter
{
	MoveOnlyDeleter()                                  = default;
	MoveOnlyDeleter(const MoveOnlyDeleter&)            = delete;
	MoveOnlyDeleter& operator=(const MoveOnlyDeleter&) = delete;
	MoveOnlyDeleter(MoveOnlyDeleter&&)                 = default;
	MoveOnlyDeleter& operator=(MoveOnlyDeleter&&)      = default;

	template <typename T>
	void operator()(T* p) const { delete p; }
};

GTEST_TEST(MemoryTest, OutPtrTest)
{
	// get_int_p
	{
		hamon::unique_ptr<int> up;
		get_int_p(hamon::out_ptr(up));
		EXPECT_EQ(42, *up);
	}
	{
		std::unique_ptr<int> up;
		get_int_p(hamon::out_ptr(up));
		EXPECT_EQ(42, *up);
	}
	{
		MoveOnlyDeleter d;
		hamon::unique_ptr<int, MoveOnlyDeleter> up;
		get_int_p(hamon::out_ptr(up, hamon::move(d)));
		EXPECT_EQ(42, *up);
	}
	{
		hamon::shared_ptr<int> sp;
		get_int_p(hamon::out_ptr(sp, Deleter{}));
		EXPECT_EQ(42, *sp);
	}
	{
		std::shared_ptr<int> sp;
		get_int_p(hamon::out_ptr(sp, Deleter{}));
		EXPECT_EQ(42, *sp);
	}
	{
		int* p;
		get_int_p(hamon::out_ptr<int*>(p));
		EXPECT_EQ(42, *p);
		delete p;
	}

	// get_int_p_nullptr
	{
		hamon::unique_ptr<int> up;
		get_int_p_nullptr(hamon::out_ptr(up));
		EXPECT_TRUE(up == nullptr);
	}
	{
		hamon::shared_ptr<int> sp;
		get_int_p_nullptr(hamon::out_ptr(sp, Deleter{}));
		EXPECT_TRUE(sp == nullptr);
	}
	{
		int* p;
		get_int_p_nullptr(hamon::out_ptr<int*>(p));
		EXPECT_TRUE(p == nullptr);
		delete p;
	}

	// get_void_p
	{
		hamon::unique_ptr<int> up;
		get_void_p(hamon::out_ptr(up));
		EXPECT_EQ(43, *up);
	}
	{
		hamon::shared_ptr<int> sp;
		get_void_p(hamon::out_ptr(sp, Deleter{}));
		EXPECT_EQ(43, *sp);
	}
	{
		int* p;
		get_void_p(hamon::out_ptr<int*>(p));
		EXPECT_EQ(43, *p);
		delete p;
	}

	// get_void_p_nullptr
	{
		hamon::unique_ptr<int> up;
		get_void_p_nullptr(hamon::out_ptr(up));
		EXPECT_TRUE(up == nullptr);
	}
	{
		hamon::shared_ptr<int> sp;
		get_void_p_nullptr(hamon::out_ptr(sp, Deleter{}));
		EXPECT_TRUE(sp == nullptr);
	}
	{
		int* p;
		get_void_p_nullptr(hamon::out_ptr<int*>(p));
		EXPECT_TRUE(p == nullptr);
		delete p;
	}
}

}	// namespace out_ptr_test

}	// namespace hamon_memory_test
