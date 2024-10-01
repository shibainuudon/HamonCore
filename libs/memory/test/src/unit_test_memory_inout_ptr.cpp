/**
 *	@file	unit_test_memory_inout_ptr.cpp
 *
 *	@brief	inout_ptr のテスト
 */

#include <hamon/memory/inout_ptr.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace inout_ptr_test
{

inline void replace_int_p(int** pp)
{
	delete *pp;
	*pp = new int{42};
}

inline void replace_int_p_nullptr(int** pp)
{
	delete *pp;
	*pp = nullptr;
}

inline void replace_void_p(void** pp)
{
	delete static_cast<int*>(*pp);
	*(reinterpret_cast<int**>(pp)) = new int{43};
}

inline void replace_void_p_nullptr(void** pp)
{
	delete static_cast<int*>(*pp);
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

GTEST_TEST(MemoryTest, InOutPtrTest)
{
	// replace_int_p
	{
		hamon::unique_ptr<int> up{new int{10}};
		replace_int_p(hamon::inout_ptr(up));
		EXPECT_EQ(42, *up);
	}
	{
		MoveOnlyDeleter d;
		hamon::unique_ptr<int, MoveOnlyDeleter> up{new int{20}};
		replace_int_p(hamon::inout_ptr(up, hamon::move(d)));
		EXPECT_EQ(42, *up);
	}
	{
		auto p = new int{30};
		replace_int_p(hamon::inout_ptr<int*>(p));
		EXPECT_EQ(42, *p);
		delete p;
	}

	// replace_int_p_nullptr
	{
		hamon::unique_ptr<int> up{new int{10}};
		replace_int_p_nullptr(hamon::inout_ptr(up));
		EXPECT_TRUE(up == nullptr);
	}
	{
		auto p = new int{20};
		replace_int_p_nullptr(hamon::inout_ptr<int*>(p));
		EXPECT_TRUE(p == nullptr);
	}

	// replace_void_p
	{
		hamon::unique_ptr<int> up{new int{10}};
		replace_void_p(hamon::inout_ptr(up));
		EXPECT_EQ(43, *up);
	}
	{
		MoveOnlyDeleter d;
		hamon::unique_ptr<int, MoveOnlyDeleter> up{new int{20}};
		replace_void_p(hamon::inout_ptr(up, hamon::move(d)));
		EXPECT_EQ(43, *up);
	}
	{
		auto p = new int{30};
		replace_void_p(hamon::inout_ptr<int*>(p));
		EXPECT_EQ(43, *p);
		delete p;
	}

	// replace_void_p_nullptr
	{
		hamon::unique_ptr<int> up{new int{10}};
		replace_void_p_nullptr(hamon::inout_ptr(up));
		EXPECT_TRUE(up == nullptr);
	}
	{
		auto p = new int{20};
		replace_void_p_nullptr(hamon::inout_ptr<int*>(p));
		EXPECT_TRUE(p == nullptr);
	}
}

}	// namespace inout_ptr_test

}	// namespace hamon_memory_test
