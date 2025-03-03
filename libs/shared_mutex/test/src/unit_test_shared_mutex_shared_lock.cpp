/**
 *	@file	unit_test_shared_mutex_shared_lock.cpp
 *
 *	@brief	shared_lock のテスト
 */

#include <hamon/shared_mutex/shared_lock.hpp>
#include <hamon/shared_mutex/shared_mutex.hpp>
#include <hamon/shared_mutex/shared_timed_mutex.hpp>
#include <hamon/chrono.hpp>
#include <hamon/utility.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_shared_mutex_test
{

namespace shared_lock_test
{

template <typename Mutex>
void ctor_test1()
{
	static_assert( hamon::is_default_constructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<hamon::shared_lock<Mutex>>::value, "");

	static_assert(!hamon::is_copy_constructible<hamon::shared_lock<Mutex>>::value, "");

	static_assert( hamon::is_move_constructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_nothrow_move_constructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_implicitly_move_constructible<hamon::shared_lock<Mutex>>::value, "");

	static_assert( hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::shared_lock<Mutex>, Mutex&>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::shared_lock<Mutex>, Mutex&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<hamon::shared_lock<Mutex>, Mutex&>::value, "");

	static_assert(!hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex const&>::value, "");
	static_assert(!hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&&>::value, "");
	static_assert(!hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex const&&>::value, "");

	static_assert( hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&, std::defer_lock_t>::value, "");
	static_assert( hamon::is_nothrow_constructible<hamon::shared_lock<Mutex>, Mutex&, std::defer_lock_t>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::shared_lock<Mutex>, Mutex&, std::defer_lock_t>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::shared_lock<Mutex>, Mutex&, std::defer_lock_t>::value, "");

	static_assert( hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&, std::try_to_lock_t>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::shared_lock<Mutex>, Mutex&, std::try_to_lock_t>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::shared_lock<Mutex>, Mutex&, std::try_to_lock_t>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::shared_lock<Mutex>, Mutex&, std::try_to_lock_t>::value, "");

	static_assert( hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&, std::adopt_lock_t>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::shared_lock<Mutex>, Mutex&, std::adopt_lock_t>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::shared_lock<Mutex>, Mutex&, std::adopt_lock_t>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::shared_lock<Mutex>, Mutex&, std::adopt_lock_t>::value, "");

	Mutex mtx;

	// default ctor
	{
		hamon::shared_lock<Mutex> lk;
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == nullptr);
	}

	// ref mutex ctor
	{
		hamon::shared_lock<Mutex> lk(mtx);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// defer lock ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, std::defer_lock);
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// try to lock ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, std::try_to_lock);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// adopt lock ctor
	{
		mtx.lock_shared();
		hamon::shared_lock<Mutex> lk(mtx, std::adopt_lock);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// move ctor
	{
		hamon::shared_lock<Mutex> lk1(mtx);
		hamon::shared_lock<Mutex> lk2 = hamon::move(lk1);
		EXPECT_FALSE(lk1.owns_lock());
		EXPECT_FALSE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == nullptr);
		EXPECT_TRUE(lk2.owns_lock());
		EXPECT_TRUE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == &mtx);
	}
}

template <typename Mutex>
void ctor_test2()
{
	static_assert( hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::sys_days const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::sys_days const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::sys_days const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::sys_days const&>::value, "");

	static_assert( hamon::is_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::seconds const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::seconds const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::seconds const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::shared_lock<Mutex>, Mutex&, hamon::chrono::seconds const&>::value, "");

	Mutex mtx;

	// try lock shared until ctor
	{
		auto t = hamon::chrono::system_clock::now();
		auto tt = t + hamon::chrono::seconds(3);
		hamon::shared_lock<Mutex> lk(mtx, tt);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// try lock shared for ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, hamon::chrono::seconds(3));
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
}

template <typename Mutex>
void dtor_test()
{
	static_assert( hamon::is_destructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_nothrow_destructible<hamon::shared_lock<Mutex>>::value, "");
	static_assert(!hamon::is_trivially_destructible<hamon::shared_lock<Mutex>>::value, "");
}

template <typename Mutex>
void assign_test()
{
	static_assert(!hamon::is_copy_assignable<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_move_assignable<hamon::shared_lock<Mutex>>::value, "");
	static_assert( hamon::is_nothrow_move_assignable<hamon::shared_lock<Mutex>>::value, "");
	static_assert(!hamon::is_trivially_move_assignable<hamon::shared_lock<Mutex>>::value, "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk1(mtx);
		hamon::shared_lock<Mutex> lk2;
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == &mtx);
		EXPECT_FALSE(lk2.owns_lock());
		EXPECT_FALSE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == nullptr);

		lk2 = hamon::move(lk1);
		EXPECT_FALSE(lk1.owns_lock());
		EXPECT_FALSE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == nullptr);
		EXPECT_TRUE(lk2.owns_lock());
		EXPECT_TRUE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == &mtx);

		lk2 = hamon::shared_lock<Mutex>();
		EXPECT_FALSE(lk1.owns_lock());
		EXPECT_FALSE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == nullptr);
		EXPECT_FALSE(lk2.owns_lock());
		EXPECT_FALSE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == nullptr);
	}
}

template <typename Mutex>
void lock_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex>&>().lock()), void>::value, "");
	static_assert(!noexcept(hamon::declval<hamon::shared_lock<Mutex>&>().lock()), "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk(mtx, std::defer_lock);
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);

		lk.lock();

		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::shared_lock<Mutex> lk;
		bool caught_expected = false;
		try
		{
			lk.lock();
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::operation_not_permitted, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
	{
		hamon::shared_lock<Mutex> lk(mtx);
		bool caught_expected = false;
		try
		{
			lk.lock();
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::resource_deadlock_would_occur, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
#endif
}

template <typename Mutex>
void try_lock_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex>&>().try_lock()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<hamon::shared_lock<Mutex>&>().try_lock()), "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk(mtx, std::defer_lock);
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);

		EXPECT_TRUE(lk.try_lock());

		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::shared_lock<Mutex> lk;
		bool caught_expected = false;
		try
		{
			lk.try_lock();
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::operation_not_permitted, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
	{
		hamon::shared_lock<Mutex> lk(mtx);
		bool caught_expected = false;
		try
		{
			lk.try_lock();
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::resource_deadlock_would_occur, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
#endif
}

template <typename Mutex>
void try_lock_until_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex>&>().try_lock_until(hamon::chrono::sys_days{})), bool>::value, "");
	static_assert(!noexcept(hamon::declval<hamon::shared_lock<Mutex>&>().try_lock_until(hamon::chrono::sys_days{})), "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk(mtx, std::defer_lock);
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);

		EXPECT_TRUE(lk.try_lock_until(hamon::chrono::system_clock::now() + hamon::chrono::seconds(3)));

		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::shared_lock<Mutex> lk;
		bool caught_expected = false;
		try
		{
			lk.try_lock_until(hamon::chrono::system_clock::now() + hamon::chrono::seconds(3));
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::operation_not_permitted, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
	{
		hamon::shared_lock<Mutex> lk(mtx);
		bool caught_expected = false;
		try
		{
			lk.try_lock_until(hamon::chrono::system_clock::now() + hamon::chrono::seconds(3));
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::resource_deadlock_would_occur, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
#endif
}

template <typename Mutex>
void try_lock_for_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex>&>().try_lock_for(hamon::chrono::seconds{})), bool>::value, "");
	static_assert(!noexcept(hamon::declval<hamon::shared_lock<Mutex>&>().try_lock_for(hamon::chrono::seconds{})), "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk(mtx, std::defer_lock);
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);

		EXPECT_TRUE(lk.try_lock_for(hamon::chrono::seconds(3)));

		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::shared_lock<Mutex> lk;
		bool caught_expected = false;
		try
		{
			lk.try_lock_for(hamon::chrono::seconds(3));
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::operation_not_permitted, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
	{
		hamon::shared_lock<Mutex> lk(mtx);
		bool caught_expected = false;
		try
		{
			lk.try_lock_for(hamon::chrono::seconds(3));
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::resource_deadlock_would_occur, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
#endif
}

template <typename Mutex>
void unlock_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex>&>().unlock()), void>::value, "");
	static_assert(!noexcept(hamon::declval<hamon::shared_lock<Mutex>&>().unlock()), "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk(mtx);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);

		lk.unlock();

		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::shared_lock<Mutex> lk;
		bool caught_expected = false;
		try
		{
			lk.unlock();
		}
		catch (hamon::system_error const& ex)
		{
			caught_expected = true;
			EXPECT_EQ(hamon::errc::operation_not_permitted, ex.code());
		}
		catch (...)
		{
			ADD_FAILURE();
		}
		EXPECT_TRUE(caught_expected);
	}
#endif
}

template <typename Mutex>
void swap_test()
{
	static_assert(hamon::is_swappable<hamon::shared_lock<Mutex>>::value, "");
	static_assert(hamon::is_nothrow_swappable<hamon::shared_lock<Mutex>>::value, "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk1(mtx);
		hamon::shared_lock<Mutex> lk2;
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == &mtx);
		EXPECT_FALSE(lk2.owns_lock());
		EXPECT_FALSE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == nullptr);

		lk1.swap(lk2);
		EXPECT_FALSE(lk1.owns_lock());
		EXPECT_FALSE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == nullptr);
		EXPECT_TRUE(lk2.owns_lock());
		EXPECT_TRUE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == &mtx);

		swap(lk1, lk2);
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == &mtx);
		EXPECT_FALSE(lk2.owns_lock());
		EXPECT_FALSE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == nullptr);
	}

	Mutex mtx2;
	{
		hamon::shared_lock<Mutex> lk1(mtx);
		hamon::shared_lock<Mutex> lk2(mtx2);
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == &mtx);
		EXPECT_TRUE(lk2.owns_lock());
		EXPECT_TRUE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == &mtx2);

		lk1.swap(lk2);
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == &mtx2);
		EXPECT_TRUE(lk2.owns_lock());
		EXPECT_TRUE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == &mtx);

		swap(lk1, lk2);
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE((bool)lk1);
		EXPECT_TRUE(lk1.mutex() == &mtx);
		EXPECT_TRUE(lk2.owns_lock());
		EXPECT_TRUE((bool)lk2);
		EXPECT_TRUE(lk2.mutex() == &mtx2);
	}
}

template <typename Mutex>
void release_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex>&>().release()), Mutex*>::value, "");
	static_assert(noexcept(hamon::declval<hamon::shared_lock<Mutex>&>().release()), "");

	Mutex mtx;
	{
		hamon::shared_lock<Mutex> lk(mtx);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);

		auto p = lk.release();

		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == nullptr);

		p->unlock_shared();
	}
}

template <typename Mutex>
void owns_lock_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex> const&>().owns_lock()), bool>::value, "");
	static_assert(noexcept(hamon::declval<hamon::shared_lock<Mutex> const&>().owns_lock()), "");
}

template <typename Mutex>
void operator_bool_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex> const&>().operator bool()), bool>::value, "");
	static_assert(noexcept(hamon::declval<hamon::shared_lock<Mutex> const&>().operator bool()), "");
}

template <typename Mutex>
void mutex_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::shared_lock<Mutex> const&>().mutex()), Mutex*>::value, "");
	static_assert(noexcept(hamon::declval<hamon::shared_lock<Mutex> const&>().mutex()), "");
}

GTEST_TEST(SharedMutexTest, SharedLockTest)
{
	ctor_test1<hamon::shared_mutex>();
	ctor_test1<hamon::shared_timed_mutex>();
	ctor_test2<hamon::shared_timed_mutex>();

	dtor_test<hamon::shared_mutex>();
	dtor_test<hamon::shared_timed_mutex>();

	assign_test<hamon::shared_mutex>();
	assign_test<hamon::shared_timed_mutex>();

	lock_test<hamon::shared_mutex>();
	lock_test<hamon::shared_timed_mutex>();

	try_lock_test<hamon::shared_mutex>();
	try_lock_test<hamon::shared_timed_mutex>();

	try_lock_until_test<hamon::shared_timed_mutex>();

	try_lock_for_test<hamon::shared_timed_mutex>();

	unlock_test<hamon::shared_mutex>();
	unlock_test<hamon::shared_timed_mutex>();

	swap_test<hamon::shared_mutex>();
	swap_test<hamon::shared_timed_mutex>();

	release_test<hamon::shared_mutex>();
	release_test<hamon::shared_timed_mutex>();

	owns_lock_test<hamon::shared_mutex>();
	owns_lock_test<hamon::shared_timed_mutex>();

	operator_bool_test<hamon::shared_mutex>();
	operator_bool_test<hamon::shared_timed_mutex>();

	mutex_test<hamon::shared_mutex>();
	mutex_test<hamon::shared_timed_mutex>();
}

}	// namespace shared_lock_test

}	// namespace hamon_shared_mutex_test
