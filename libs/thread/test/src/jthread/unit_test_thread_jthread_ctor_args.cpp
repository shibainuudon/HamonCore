/**
 *	@file	unit_test_thread_jthread_ctor_args.cpp
 *
 *	@brief	argsを引数に取るコンストラクタのテスト
 *
 *	template<class... Args>
 *	explicit jthread(Args&&... args);
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace ctor_args_test
{

template <class... Args>
struct Func
{
	void operator()(Args...) const;
};

static_assert( hamon::is_constructible_v<hamon::jthread, Func<>>, "");
static_assert( hamon::is_constructible_v<hamon::jthread, Func<int>, int>, "");
static_assert(!hamon::is_constructible_v<hamon::jthread, hamon::jthread const&>, "");

static_assert( hamon::is_constructible_v<hamon::jthread, Func<>>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::jthread, Func<>>, "");
static_assert(!hamon::is_trivially_constructible_v<hamon::jthread, Func<>>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::jthread, Func<>>, "");

GTEST_TEST(JThreadTest, CtorArgsTest)
{
	// Effects: Initializes ssource
	// Postconditions: get_id() != id() is true and ssource.stop_possible() is true
	// and *this represents the newly started thread.
	{
		hamon::jthread jt{ [] {} };
		EXPECT_TRUE(jt.get_stop_source().stop_possible());
		EXPECT_TRUE(jt.get_id() != hamon::jthread::id());
	}

	// The new thread of execution executes
	// invoke(auto(hamon::forward<F>(f)), get_stop_token(), auto(hamon::forward<Args>(args))...)
	// if that expression is well-formed,
	{
		int result = 0;
		hamon::jthread jt
		{
			[&result](hamon::stop_token st, int i)
			{
				EXPECT_TRUE(st.stop_possible());
				EXPECT_FALSE(st.stop_requested());
				result += i;
			},
			5
		};
		jt.join();
		EXPECT_TRUE(result == 5);
	}

	// otherwise
	// invoke(auto(hamon::forward<F>(f)), auto(hamon::forward<Args>(args))...)
	{
		int result = 0;
		hamon::jthread jt{ [&result](int i) { result += i; }, 5 };
		jt.join();
		EXPECT_TRUE(result == 5);
	}

	// with the values produced by auto being materialized ([conv.rval]) in the constructing thread.
	{
		struct TrackThread
		{
			hamon::jthread::id threadId;
			bool copyConstructed = false;
			bool moveConstructed = false;

			TrackThread() : threadId(hamon::this_thread::get_id()) {}
			TrackThread(const TrackThread&) : threadId(hamon::this_thread::get_id()), copyConstructed(true) {}
			TrackThread(TrackThread&&) : threadId(hamon::this_thread::get_id()), moveConstructed(true) {}
		};

		auto mainThread = hamon::this_thread::get_id();

		TrackThread arg1;
		hamon::jthread jt1
		{
			[mainThread](const TrackThread& arg)
			{
				EXPECT_TRUE(arg.threadId == mainThread);
				EXPECT_TRUE(arg.threadId != hamon::this_thread::get_id());
				EXPECT_TRUE(arg.copyConstructed);
			},
			arg1
		};

		TrackThread arg2;
		hamon::jthread jt2
		{
			[mainThread](const TrackThread& arg)
			{
				EXPECT_TRUE(arg.threadId == mainThread);
				EXPECT_TRUE(arg.threadId != hamon::this_thread::get_id());
				EXPECT_TRUE(arg.moveConstructed);
			},
			hamon::move(arg2)
		};
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	// [Note 1: This implies that any exceptions not thrown from the invocation of the copy
	// of f will be thrown in the constructing thread, not the new thread. - end note]
	{
		struct Exception
		{
			hamon::jthread::id threadId;
		};
		struct ThrowOnCopyFunc
		{
			ThrowOnCopyFunc() = default;
			ThrowOnCopyFunc(const ThrowOnCopyFunc&) { throw Exception{ hamon::this_thread::get_id() }; }
			void operator()() const {}
		};
		ThrowOnCopyFunc f1;
		try
		{
			hamon::jthread jt{ f1 };
			EXPECT_TRUE(false);
		}
		catch (const Exception& e)
		{
			EXPECT_TRUE(e.threadId == hamon::this_thread::get_id());
		}
	}
#endif

	// Synchronization: The completion of the invocation of the constructor
	// synchronizes with the beginning of the invocation of the copy of f.
	{
		int flag = 0;
		struct Arg
		{
			int& flag_;
			Arg(int& f) : flag_(f) {}

			Arg(const Arg& other) : flag_(other.flag_) { flag_ = 5; }
		};

		Arg arg(flag);
		hamon::jthread jt(
			[&flag](const auto&)
			{
				EXPECT_TRUE(flag == 5); // happens-after the copy-construction of arg
			},
			arg);
	}

	// Per https://eel.is/c++draft/thread.jthread.class#thread.jthread.cons-8:
	//
	// Throws: system_error if unable to start the new thread.
	// Error conditions:
	// resource_unavailable_try_again - the system lacked the necessary resources to create another thread,
	// or the system-imposed limit on the number of threads in a process would be exceeded.
	//
	// Unfortunately, this is extremely hard to test portably so we don't have a test for this error condition right now.

	{
		class CopyOnly
		{
		public:
			CopyOnly() {}
			CopyOnly(const CopyOnly&) = default;
			CopyOnly(CopyOnly&&) = delete;

			void operator()(const CopyOnly&) const {}
		};
		CopyOnly c;
		hamon::jthread t(c, c);
	}

	{
		class MoveOnly
		{
		public:
			MoveOnly() {}
			MoveOnly(const MoveOnly&) = delete;
			MoveOnly(MoveOnly&&) = default;

			void operator()(MoveOnly&&) const {}
		};
		hamon::jthread t(MoveOnly{}, MoveOnly{});
	}

	{
		// スレッド名とスタックサイズのヒントを指定してスレッドを生成する。
		// スレッド名はデバッガのスレッド一覧などに表示される
		hamon::jthread t{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES) && defined(HAMON_HAS_CXX20_CTAD_ALIAS_TEMPLATE)
			hamon::jthread::name_hint("Worker"),
#else
			hamon::jthread::name_hint<char>("Worker"),
#endif
			hamon::jthread::stack_size_hint(512 * 1024),
			[](int){},
			42
		};

		// 標準ライブラリにスレッド名を取得するAPIはないが、
		// ネイティブハンドルを通じてプラットフォームのAPIで取得できる
#if 0
		{
			char name[16]{};
			pthread_getname_np(t.native_handle(), name, sizeof(name));
			EXPECT_STREQ("Worker", name);
		}
#endif
#if 0
		{
			wchar_t* name = nullptr;
			GetThreadDescription(t.native_handle(), &name);
			EXPECT_STREQ(L"Worker", name);
			LocalFree(name);
		}
#endif
	}
	{
		hamon::jthread t{
			hamon::jthread::stack_size_hint(512 * 1024),
			hamon::jthread::name_hint<char>("Worker"),
			[](int, int){},
			1, 2
		};
	}
	{
		hamon::jthread t{
			hamon::jthread::stack_size_hint(512 * 1024),
			[](){}
		};
	}
	{
		hamon::jthread t{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES) && defined(HAMON_HAS_CXX20_CTAD_ALIAS_TEMPLATE)
			hamon::jthread::name_hint("Worker"),
#else
			hamon::jthread::name_hint<char>("Worker"),
#endif
			[](int){},
			10
		};
	}
}

}	// namespace ctor_args_test

}	// namespace hamon_jthread_test
