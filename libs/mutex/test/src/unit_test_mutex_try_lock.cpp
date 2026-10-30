/**
 *	@file	unit_test_mutex_try_lock.cpp
 *
 *	@brief	try_lock のテスト
 *
 *	template<class L1, class L2, class... L3> int try_lock(L1&, L2&, L3&...);
 */

#include <hamon/mutex/try_lock.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_try_lock_test
{

class L0
{
	bool locked_;

public:
	L0() : locked_(false) {}

	bool try_lock()
	{
		locked_ = true;
		return locked_;
	}

	void unlock() { locked_ = false; }

	bool locked() const { return locked_; }
};

class L1
{
	bool locked_;

public:
	L1() : locked_(false) {}

	bool try_lock()
	{
		locked_ = false;
		return locked_;
	}

	void unlock() { locked_ = false; }

	bool locked() const { return locked_; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
class L2
{
	bool locked_;

public:
	L2() : locked_(false) {}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。
	bool try_lock()
	{
		throw 1;
		return locked_;
	}
HAMON_WARNING_POP()

	void unlock() { locked_ = false; }

	bool locked() const { return locked_; }
};
#endif

GTEST_TEST(TryLockTest, TryLockTest)
{
	{
		L0 l0;
		L0 l1;
		static_assert(hamon::is_same_v<decltype(hamon::try_lock(l0, l1)), int>, "");
		static_assert(!noexcept(hamon::try_lock(l0, l1)), "");
		EXPECT_TRUE(hamon::try_lock(l0, l1) == -1);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
	}
	{
		L0 l0;
		L1 l1;
		EXPECT_TRUE(hamon::try_lock(l0, l1) == 1);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
	}
	{
		L1 l0;
		L0 l1;
		EXPECT_TRUE(hamon::try_lock(l0, l1) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L0 l0;
		L2 l1;
		try
		{
			(void)hamon::try_lock(l0, l1);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L0 l1;
		try
		{
			(void)hamon::try_lock(l0, l1);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
#endif
	{
		L0 l0;
		L0 l1;
		L0 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == -1);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
	}
	{
		L1 l0;
		L1 l1;
		L1 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L2 l0;
		L2 l1;
		L2 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L0 l0;
		L1 l1;
		L2 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 1);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
#endif
	{
		L0 l0;
		L0 l1;
		L1 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 2);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L0 l0;
		L1 l1;
		L0 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 1);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L1 l0;
		L0 l1;
		L0 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L0 l0;
		L0 l1;
		L2 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L0 l0;
		L2 l1;
		L0 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L0 l1;
		L0 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
#endif
	{
		L1 l0;
		L1 l1;
		L0 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L1 l0;
		L0 l1;
		L1 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L0 l0;
		L1 l1;
		L1 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 1);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L1 l0;
		L1 l1;
		L2 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L1 l0;
		L2 l1;
		L1 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L2 l0;
		L1 l1;
		L1 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L2 l1;
		L0 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L0 l1;
		L2 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L0 l0;
		L2 l1;
		L2 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L2 l1;
		L1 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L1 l1;
		L2 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L1 l0;
		L2 l1;
		L2 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L0 l0;
		L2 l1;
		L1 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L1 l0;
		L0 l1;
		L2 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L1 l0;
		L2 l1;
		L0 l2;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
	}
	{
		L2 l0;
		L0 l1;
		L1 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L2 l0;
		L1 l1;
		L0 l2;
		try
		{
			(void)hamon::try_lock(l0, l1, l2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
		}
	}
#endif
	{
		L0 l0;
		L0 l1;
		L0 l2;
		L0 l3;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2, l3) == -1);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
		EXPECT_TRUE(l3.locked());
	}
	{
		L1 l0;
		L0 l1;
		L0 l2;
		L0 l3;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2, l3) == 0);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
		EXPECT_TRUE(!l3.locked());
	}
	{
		L0 l0;
		L1 l1;
		L0 l2;
		L0 l3;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2, l3) == 1);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
		EXPECT_TRUE(!l3.locked());
	}
	{
		L0 l0;
		L0 l1;
		L1 l2;
		L0 l3;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2, l3) == 2);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
		EXPECT_TRUE(!l3.locked());
	}
	{
		L0 l0;
		L0 l1;
		L0 l2;
		L1 l3;
		EXPECT_TRUE(hamon::try_lock(l0, l1, l2, l3) == 3);
		EXPECT_TRUE(!l0.locked());
		EXPECT_TRUE(!l1.locked());
		EXPECT_TRUE(!l2.locked());
		EXPECT_TRUE(!l3.locked());
	}
}

}	// namespace hamon_try_lock_test
