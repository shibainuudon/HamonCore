/**
 *	@file	unit_test_memory_unique_ptr_get_deleter.cpp
 *
 *	@brief	get_deleter のテスト
 *
 *	constexpr deleter_type& get_deleter() noexcept;
 *	constexpr const deleter_type& get_deleter() const noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace get_deleter_test
{

struct D1
{
	int value;

	HAMON_CXX11_CONSTEXPR D1(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	int value;

	HAMON_CXX11_CONSTEXPR D2(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete[] p; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int, D1> up(new int{10}, D1{11});
		VERIFY(up.get_deleter().value == 11);
	}
	{
		hamon::unique_ptr<int, D1> const up(new int{12}, D1{13});
		VERIFY(up.get_deleter().value == 13);
	}
	{
		D1 d{15};
		hamon::unique_ptr<int, D1&> up(new int{14}, d);
		VERIFY(up.get_deleter().value == 15);
		VERIFY(&up.get_deleter() == &d);
	}
	{
		D1 d{17};
		hamon::unique_ptr<int, D1&> const up(new int{16}, d);
		VERIFY(up.get_deleter().value == 17);
		VERIFY(&up.get_deleter() == &d);
	}
	{
		hamon::unique_ptr<int[], D2> up(new int[3], D2{21});
		VERIFY(up.get_deleter().value == 21);
	}
	{
		hamon::unique_ptr<int[], D2> const up(new int[4], D2{22});
		VERIFY(up.get_deleter().value == 22);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, GetDeleterTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	{
		using UP = hamon::unique_ptr<int, D1>;
		static_assert( hamon::is_same<D1&, decltype(hamon::declval<UP>().get_deleter())>::value, "");
		static_assert( hamon::is_same<D1 const&, decltype(hamon::declval<UP const>().get_deleter())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().get_deleter()), "");
		static_assert( noexcept(hamon::declval<UP const>().get_deleter()), "");
	}
	{
		using UP = hamon::unique_ptr<int[], D2>;
		static_assert( hamon::is_same<D2&, decltype(hamon::declval<UP>().get_deleter())>::value, "");
		static_assert( hamon::is_same<D2 const&, decltype(hamon::declval<UP const>().get_deleter())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().get_deleter()), "");
		static_assert( noexcept(hamon::declval<UP const>().get_deleter()), "");
	}
}

}	// namespace get_deleter_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
