/**
 *	@file	unit_test_mutex_lock.cpp
 *
 *	@brief	lock のテスト
 *
 *	template<class L1, class L2, class... L3> void lock(L1&, L2&, L3&...);
 */

#include <hamon/mutex/lock.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_lock_test
{

class L0
{
	bool locked_;

public:
	L0() : locked_(false) {}

	void lock()
	{
		locked_ = true;
	}

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

	void lock()
	{
		locked_ = true;
	}

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

	void lock()
	{
		throw 1;
	}

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

GTEST_TEST(LockTest, LockTest)
{
	{
		L0 l0;
		L0 l1;
		static_assert(hamon::is_same_v<decltype(hamon::lock(l0, l1)), void>, "");
		static_assert(!noexcept(hamon::lock(l0, l1)), "");
		hamon::lock(l0, l1);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
	}
	{
		L0 l0;
		L1 l1;
		hamon::lock(l0, l1);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
	}
	{
		L1 l0;
		L0 l1;
		hamon::lock(l0, l1);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L0 l0;
		L2 l1;
		try
		{
			hamon::lock(l0, l1);
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
			hamon::lock(l0, l1);
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
		L1 l0;
		L2 l1;
		try
		{
			hamon::lock(l0, l1);
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
		L1 l1;
		try
		{
			hamon::lock(l0, l1);
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
		L2 l1;
		try
		{
			hamon::lock(l0, l1);
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
		hamon::lock(l0, l1, l2);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L2 l0;
		L2 l1;
		L2 l2;
		try
		{
			hamon::lock(l0, l1, l2);
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
		L0 l0;
		L0 l1;
		L1 l2;
		hamon::lock(l0, l1, l2);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
	}
	{
		L0 l0;
		L1 l1;
		L0 l2;
		hamon::lock(l0, l1, l2);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
	}
	{
		L1 l0;
		L0 l1;
		L0 l2;
		hamon::lock(l0, l1, l2);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L0 l0;
		L0 l1;
		L2 l2;
		try
		{
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
			hamon::lock(l0, l1, l2);
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
		try
		{
			hamon::lock(l0, l1, l2);
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
		L0 l0;
		L0 l1;
		L0 l2;
		L0 l3;
		hamon::lock(l0, l1, l2, l3);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
		EXPECT_TRUE(l3.locked());
	}
	{
		L0 l0;
		L0 l1;
		L0 l2;
		L1 l3;
		hamon::lock(l0, l1, l2, l3);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
		EXPECT_TRUE(l3.locked());
	}
	{
		L0 l0;
		L0 l1;
		L1 l2;
		L0 l3;
		hamon::lock(l0, l1, l2, l3);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
		EXPECT_TRUE(l3.locked());
	}
	{
		L0 l0;
		L1 l1;
		L0 l2;
		L0 l3;
		hamon::lock(l0, l1, l2, l3);
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
		hamon::lock(l0, l1, l2, l3);
		EXPECT_TRUE(l0.locked());
		EXPECT_TRUE(l1.locked());
		EXPECT_TRUE(l2.locked());
		EXPECT_TRUE(l3.locked());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		L0 l0;
		L0 l1;
		L0 l2;
		L2 l3;
		try
		{
			hamon::lock(l0, l1, l2, l3);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
			EXPECT_TRUE(!l3.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
	{
		L0 l0;
		L0 l1;
		L2 l2;
		L0 l3;
		try
		{
			hamon::lock(l0, l1, l2, l3);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
			EXPECT_TRUE(!l3.locked());
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
		L0 l3;
		try
		{
			hamon::lock(l0, l1, l2, l3);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
			EXPECT_TRUE(!l3.locked());
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
		L0 l3;
		try
		{
			hamon::lock(l0, l1, l2, l3);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
			EXPECT_TRUE(!l0.locked());
			EXPECT_TRUE(!l1.locked());
			EXPECT_TRUE(!l2.locked());
			EXPECT_TRUE(!l3.locked());
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
	}
#endif
}

}	// namespace hamon_lock_test
