/**
 *	@file	unit_test_ranges_istream_view.cpp
 *
 *	@brief	ranges::istream_view のテスト
 */

#include <hamon/ranges/factories/istream_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/concepts.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <istream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "constexpr_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace istream_view_test
{

struct NotStreamExtratable {};

struct StreamExtratable {};

template <typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, StreamExtratable&)
{
	return is;
}

struct CharStreamExtratable {};

std::istream&
operator>>(std::istream& is, CharStreamExtratable&)
{
	return is;
}

struct WCharStreamExtratable {};

std::wistream&
operator>>(std::wistream& is, WCharStreamExtratable&)
{
	return is;
}

struct NonMovable
{
	NonMovable() = default;
	NonMovable(NonMovable const&) = default;
	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable const&) = default;
	NonMovable& operator=(NonMovable &&) = delete;
};
static_assert( hamon::default_initializable<NonMovable>, "");
static_assert(!hamon::movable<NonMovable>, "");

template <typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, NonMovable&)
{
	return is;
}

struct NoDefaultCtor
{
	NoDefaultCtor() = delete;
	NoDefaultCtor(NoDefaultCtor const&) = default;
	NoDefaultCtor(NoDefaultCtor&&) = default;
	NoDefaultCtor& operator=(NoDefaultCtor const&) = default;
	NoDefaultCtor& operator=(NoDefaultCtor &&) = default;
};
static_assert(!hamon::default_initializable<NoDefaultCtor>, "");
static_assert( hamon::movable<NoDefaultCtor>, "");

template <typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, NoDefaultCtor&)
{
	return is;
}

template <typename Val, typename CharT, typename = void>
struct CanInstantiateIstreamView
	: hamon::false_type {};

template <typename Val, typename CharT>
struct CanInstantiateIstreamView<Val, CharT, hamon::void_t<hamon::ranges::basic_istream_view<Val, CharT>>>
	: hamon::true_type {};

static_assert( CanInstantiateIstreamView<int, char>::value, "");
static_assert( CanInstantiateIstreamView<float, char>::value, "");
static_assert(!CanInstantiateIstreamView<NotStreamExtratable, char>::value, "");
static_assert( CanInstantiateIstreamView<StreamExtratable, char>::value, "");
static_assert( CanInstantiateIstreamView<CharStreamExtratable, char>::value, "");
static_assert(!CanInstantiateIstreamView<WCharStreamExtratable, char>::value, "");
static_assert(!CanInstantiateIstreamView<NonMovable, char>::value, "");
static_assert(!CanInstantiateIstreamView<NoDefaultCtor, char>::value, "");

static_assert( CanInstantiateIstreamView<int, wchar_t>::value, "");
static_assert( CanInstantiateIstreamView<float, wchar_t>::value, "");
static_assert(!CanInstantiateIstreamView<NotStreamExtratable, wchar_t>::value, "");
static_assert( CanInstantiateIstreamView<StreamExtratable, wchar_t>::value, "");
static_assert(!CanInstantiateIstreamView<CharStreamExtratable, wchar_t>::value, "");
static_assert( CanInstantiateIstreamView<WCharStreamExtratable, wchar_t>::value, "");
static_assert(!CanInstantiateIstreamView<NonMovable, wchar_t>::value, "");
static_assert(!CanInstantiateIstreamView<NoDefaultCtor, wchar_t>::value, "");

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::istream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), std::ostream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::iostream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::istringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), std::ostringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::stringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::ifstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), std::ofstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::fstream&>, "");

static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::stringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), std::stringstream&&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), std::stringstream const&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), std::stringstream const&&>, "");

static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::stringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<float>), std::stringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<NotStreamExtratable>), std::stringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<StreamExtratable>), std::stringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<CharStreamExtratable>), std::stringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<WCharStreamExtratable>), std::stringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<NonMovable>), std::stringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<NoDefaultCtor>), std::stringstream&>, "");

static_assert( hamon::invocable<decltype(hamon::views::istream<int>), std::wstringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<float>), std::wstringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<NotStreamExtratable>), std::wstringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<StreamExtratable>), std::wstringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<CharStreamExtratable>), std::wstringstream&>, "");
static_assert( hamon::invocable<decltype(hamon::views::istream<WCharStreamExtratable>), std::wstringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<NonMovable>), std::wstringstream&>, "");
static_assert(!hamon::invocable<decltype(hamon::views::istream<NoDefaultCtor>), std::wstringstream&>, "");

static_assert(!hamon::invocable<decltype(hamon::views::istream<int>), int&>, "");
#endif

template <typename Val, typename CharT>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = hamon::ranges::basic_istream_view<Val, CharT>;
	using IStream = std::basic_istream<CharT>;

	static_assert( hamon::ranges::range_t<V>::value, "");
	static_assert(!hamon::ranges::borrowed_range<V>, "");
	static_assert(!hamon::ranges::sized_range_t<V>::value, "");
	static_assert(!hamon::ranges::approximately_sized_range<V>, "");
	static_assert(!hamon::ranges::output_range<V, Val>, "");
	static_assert( hamon::ranges::input_range<V>, "");
	static_assert(!hamon::ranges::forward_range<V>, "");
	static_assert(!hamon::ranges::bidirectional_range<V>, "");
	static_assert(!hamon::ranges::random_access_range<V>, "");
	static_assert(!hamon::ranges::contiguous_range<V>, "");
	static_assert(!hamon::ranges::common_range<V>, "");
	static_assert( hamon::ranges::viewable_range_t<V>::value, "");
	static_assert( hamon::ranges::view_t<V>::value, "");
	static_assert(!hamon::ranges::constant_range<V>, "");

	static_assert(!hamon::default_initializable<V>, "");

	static_assert( hamon::constructible_from<V, IStream &>, "");
	static_assert(!hamon::constructible_from<V, IStream &&>, "");
	static_assert(!hamon::constructible_from<V, IStream const&>, "");
	static_assert(!hamon::constructible_from<V, IStream const&&>, "");

	static_assert(!hamon::is_implicitly_constructible<V, IStream &>::value, "");

	static_assert( has_begin<V>::value, "");
	static_assert(!has_begin<V const>::value, "");
	static_assert( has_end<V>::value, "");
	static_assert( has_end<V const>::value, "");

	static_assert(!noexcept(hamon::declval<V>().begin()), "");
	static_assert( noexcept(hamon::declval<V>().end()), "");
	static_assert( noexcept(hamon::declval<V const>().end()), "");

	using I = decltype(hamon::declval<V>().begin());
	static_assert(hamon::same_as<typename I::iterator_concept, hamon::input_iterator_tag>, "");
	static_assert(hamon::same_as<typename I::difference_type, hamon::ptrdiff_t>, "");
	static_assert(hamon::same_as<typename I::value_type, Val>, "");
	static_assert(!hamon::default_initializable<I>, "");
	static_assert( hamon::constructible_from<I, V &>, "");
	static_assert(!hamon::constructible_from<I, V &&>, "");
	static_assert(!hamon::constructible_from<I, V const&>, "");
	static_assert(!hamon::constructible_from<I, V const&&>, "");
	static_assert(!hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert(!hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");
	static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<I>()++), void>, "");
	static_assert(hamon::same_as<decltype(*hamon::declval<I>()), Val&>, "");

	static_assert(!noexcept(++hamon::declval<I>()), "");
	static_assert(!noexcept(hamon::declval<I>()++), "");

	using S = decltype(hamon::declval<V>().end());
	static_assert(hamon::same_as<S, hamon::default_sentinel_t>, "");
	
	static_assert(has_eq<I, S>::value, "");
	static_assert(has_eq<S, I>::value, "");
	static_assert(has_neq<I, S>::value, "");
	static_assert(has_neq<S, I>::value, "");

	static_assert(!has_eq<I, I>::value, "");
	static_assert(!has_neq<I, I>::value, "");

	return true;
}

GTEST_TEST(RangesTest, IstreamViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<int, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<long, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<float, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<StreamExtratable, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<int, wchar_t>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<long, wchar_t>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<float, wchar_t>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<StreamExtratable, wchar_t>()));

#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
	{
		std::istringstream iss{"1 2 3  4\t5"};
		std::stringstream ss;
		for (int i : hamon::views::istream<int>(iss))
		{
			ss << i;
		}
		EXPECT_EQ("12345", ss.str());
	}
	{
		std::wistringstream iss{L"1 2 3  4\t5"};
		std::wstringstream ss;
		for (int i : hamon::views::istream<int>(iss))
		{
			ss << i;
		}
		EXPECT_EQ(L"12345", ss.str());
	}
#endif
	{
		std::istringstream iss{"1 2 3  4\t5"};
		auto rv = hamon::views::istream<int>(iss);
		auto it = rv.begin();
		EXPECT_FALSE(it == rv.end());
		EXPECT_TRUE (it != rv.end());
		EXPECT_FALSE(rv.end() == it);
		EXPECT_TRUE (rv.end() != it);
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_TRUE(it != rv.end());
		EXPECT_EQ(2, *it);
		it++;
		EXPECT_TRUE(it != rv.end());
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_TRUE(it != rv.end());
		EXPECT_EQ(4, *it);
		it++;
		EXPECT_TRUE(it != rv.end());
		EXPECT_EQ(5, *it);
		++it;
		EXPECT_TRUE (it == rv.end());
		EXPECT_FALSE(it != rv.end());
		EXPECT_TRUE (rv.end() == it);
		EXPECT_FALSE(rv.end() != it);
	}
	{
		float buf[256] {};
		auto floats = std::stringstream {"1.1  2.2\t3.3\v4.4\f55\n66\r7.7  8.8"};
		hamon::ranges::copy(
			hamon::views::istream<float>(floats),
			buf
		);
		EXPECT_EQ(buf[0], 1.1f);
		EXPECT_EQ(buf[1], 2.2f);
		EXPECT_EQ(buf[2], 3.3f);
		EXPECT_EQ(buf[3], 4.4f);
		EXPECT_EQ(buf[4], 55.0f);
		EXPECT_EQ(buf[5], 66.0f);
		EXPECT_EQ(buf[6], 7.7f);
		EXPECT_EQ(buf[7], 8.8f);
	}
	
#if 0	// TODO C++20以前だと、std::ostream_iteratorがweakly_incrementableでない
	// [range.istream.overview]/3
	// Example 1:
	{
		std::stringstream ss;
		auto ints = std::istringstream {"0 1  2   3     4"};
		hamon::ranges::copy(hamon::views::istream<int>(ints), std::ostream_iterator<int>{ss, "-"});
		EXPECT_EQ("0-1-2-3-4-", ss.str());
	}
#endif
}

}	// namespace istream_view_test
}	// namespace hamon_ranges_test
