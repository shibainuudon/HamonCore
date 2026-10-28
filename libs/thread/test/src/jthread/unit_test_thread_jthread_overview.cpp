/**
 *	@file	unit_test_thread_jthread_overview.cpp
 *
 *	@brief	jthread のテスト
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/chrono.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/stop_token.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace overview_test
{

hamon::uint64_t sum1 = 0;
hamon::uint64_t sum2 = 0;

void f1(hamon::stop_token stoken, hamon::uint64_t n)
{
	sum1 = 0;
	for (hamon::uint64_t i = 1; i < n; ++i)
	{
		if (stoken.stop_requested())
		{
			// 中断リクエストがきたのでスレッドを終了する
			break;
		}
		sum1 += i;
	}
}

void f2(hamon::uint64_t n)
{
	sum2 = 0;
	for (hamon::uint64_t i = 1; i < n; ++i)
	{
		sum2 += i;
	}
}

GTEST_TEST(JThreadTest, OverviewTest)
{
	{
		// 関数の第1引数がhamon::stop_token型である場合、
		// スレッドに中断リクエストを送れるようになる
		hamon::jthread jt1{ f1, 1'000'000ULL };
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds{ 3 });
		jt1.request_stop(); // スレッドの中断要求を発行

		// スレッド実行する関数がhamon::stop_tokenを受け取らない場合、
		// 中断リクエストを使用せず、
		// デストラクタで自動的にjoinするスレッドオブジェクトとして使用する
		hamon::jthread jt2{[] { f2(1'000'000ULL); }};
	} // jthreadのデストラクタでは、中断要求を発行し、スレッドの終了を待機する

	EXPECT_LE(sum1, 499999500000);	// sum1 <= 499999500000
	EXPECT_EQ(sum2, 499999500000);

	{
		int x = 0, y = 0;

		hamon::jthread jt([&](hamon::stop_token /*st*/) { x++; });

		// スレッドに対する停止要求の作成に合わせて呼び出される
		// コールバックを定義する。
		auto f = [&] { y++; };
		hamon::stop_callback<decltype(f)> sc{ jt.get_stop_token(), f };

		EXPECT_TRUE(y == 0);

		// 明示的にjoin()を呼び出さずにtを上書きする。
		// このとき、ムーブ代入演算子の呼び出しの中で、
		// 自動で停止要求の作成とjoin()の呼び出しが行われる。
		jt = hamon::jthread{};

		EXPECT_TRUE(x == 1);
		EXPECT_TRUE(y == 1);
	}
}

}	// namespace overview_test

}	// namespace hamon_jthread_test
