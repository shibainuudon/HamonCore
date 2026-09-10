/**
 *	@file	unit_test_thread_name_hint.cpp
 *
 *	@brief	thread::name_hint のテスト
 */

#include <hamon/thread/thread.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace name_hint_test
{

void work(int n)
{
	(void)n;
}

GTEST_TEST(ThreadTest, NameHintTest)
{
	// スレッド名"Worker"を指定してスレッドを生成する
	hamon::thread t{ hamon::thread::name_hint("Worker"), work, 42 };

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

	t.join();
}

}	// namespace name_hint_test

}	// namespace hamon_thread_test
