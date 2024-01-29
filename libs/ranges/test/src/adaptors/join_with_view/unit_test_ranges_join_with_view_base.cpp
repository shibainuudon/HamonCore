/**
 *	@file	unit_test_ranges_join_with_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr View base() const & requires copy_constructible<View> { return base_; }
 *	constexpr View base() && { return std::move(base_); }
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace base_test
{

template <typename T>
struct MoveOnlyView : hamon::ranges::view_base
{
	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using View = test_input_view<test_input_view<int>>;
	using JV = hamon::ranges::join_with_view<View, test_forward_view<int>>;
	
	static_assert( has_base<JV&>::value, "");
	static_assert( has_base<JV&&>::value, "");
	static_assert( has_base<JV const&>::value, "");
	static_assert( has_base<JV const&&>::value, "");

	static_assert(hamon::is_same<View, decltype(hamon::declval<JV&>().base())>::value, "");
	static_assert(hamon::is_same<View, decltype(hamon::declval<JV&&>().base())>::value, "");
	static_assert(hamon::is_same<View, decltype(hamon::declval<JV const&>().base())>::value, "");
	static_assert(hamon::is_same<View, decltype(hamon::declval<JV const&&>().base())>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using View = MoveOnlyView<test_input_view<int>>;
	using JV = hamon::ranges::join_with_view<View, test_forward_view<int>>;
	
	static_assert(!has_base<JV&>::value, "");
	static_assert( has_base<JV&&>::value, "");
	static_assert(!has_base<JV const&>::value, "");
	static_assert(!has_base<JV const&&>::value, "");

//	static_assert(hamon::is_same<View, decltype(hamon::declval<JV&>().base())>::value, "");
	static_assert(hamon::is_same<View, decltype(hamon::declval<JV&&>().base())>::value, "");
//	static_assert(hamon::is_same<View, decltype(hamon::declval<JV const&>().base())>::value, "");
//	static_assert(hamon::is_same<View, decltype(hamon::declval<JV const&&>().base())>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::string_view a[] = {{}, "The", {}, "quick", {}, "fox", };
	using View = test_input_view<hamon::string_view>;
	using JV = hamon::ranges::join_with_view<View, hamon::string_view>;
	View v(a);
	JV jv(v, hamon::string_view{", "});
	{
		auto b = jv.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(jv).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace base_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
