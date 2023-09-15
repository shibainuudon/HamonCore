/**
 *	@file	unit_test_ranges_view.cpp
 *
 *	@brief	ranges::view のテスト
 */

#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/ranges/views/view_base.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/default_initializable.hpp>
//#include <hamon/string_view.hpp>
#include <hamon/span.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/set.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <string>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_VIEW_TEST(B, ...)	\
	static_assert(B == hamon::ranges::view<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::view_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_VIEW_TEST(B, ...)	\
	static_assert(B == hamon::ranges::view<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::view_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_ranges_test {
namespace view_test {

// The type would be a view, but it's not moveable.
struct NotMoveable : hamon::ranges::view_base
{
	NotMoveable() = default;
	NotMoveable(NotMoveable&&) = delete;
	NotMoveable& operator=(NotMoveable&&) = delete;
	friend int* begin(NotMoveable&);
	friend int* begin(NotMoveable const&);
	friend int* end(NotMoveable&);
	friend int* end(NotMoveable const&);
};
static_assert(hamon::ranges::range_t<NotMoveable>::value, "");
static_assert(!hamon::movable_t<NotMoveable>::value, "");
static_assert(hamon::default_initializable_t<NotMoveable>::value, "");
static_assert(HAMON_RANGES_ENABLE_VIEW(NotMoveable), "");
HAMON_RANGES_VIEW_TEST(false, NotMoveable);
HAMON_RANGES_VIEW_TEST(false, NotMoveable&);
HAMON_RANGES_VIEW_TEST(false, NotMoveable&&);
HAMON_RANGES_VIEW_TEST(false, NotMoveable const);
HAMON_RANGES_VIEW_TEST(false, NotMoveable const&);
HAMON_RANGES_VIEW_TEST(false, NotMoveable const&&);

// The type would be a view, but it's not default initializable
struct NotDefaultInit : hamon::ranges::view_base
{
	NotDefaultInit() = delete;
	friend int* begin(NotDefaultInit&);
	friend int* begin(NotDefaultInit const&);
	friend int* end(NotDefaultInit&);
	friend int* end(NotDefaultInit const&);
};
static_assert(hamon::ranges::range_t<NotDefaultInit>::value, "");
static_assert(hamon::movable_t<NotDefaultInit>::value, "");
static_assert(!hamon::default_initializable_t<NotDefaultInit>::value, "");
static_assert(HAMON_RANGES_ENABLE_VIEW(NotDefaultInit), "");
HAMON_RANGES_VIEW_TEST(true,  NotDefaultInit);
HAMON_RANGES_VIEW_TEST(false, NotDefaultInit&);
HAMON_RANGES_VIEW_TEST(false, NotDefaultInit&&);
HAMON_RANGES_VIEW_TEST(false, NotDefaultInit const);
HAMON_RANGES_VIEW_TEST(false, NotDefaultInit const&);
HAMON_RANGES_VIEW_TEST(false, NotDefaultInit const&&);

// The type would be a view, but it doesn't enable it with enable_view
struct NotExplicitlyEnabled
{
	NotExplicitlyEnabled() = default;
	NotExplicitlyEnabled(NotExplicitlyEnabled&&) = default;
	NotExplicitlyEnabled& operator=(NotExplicitlyEnabled&&) = default;
	friend int* begin(NotExplicitlyEnabled&);
	friend int* begin(NotExplicitlyEnabled const&);
	friend int* end(NotExplicitlyEnabled&);
	friend int* end(NotExplicitlyEnabled const&);
};

static_assert(hamon::ranges::range_t<NotExplicitlyEnabled>::value, "");
static_assert(hamon::movable_t<NotExplicitlyEnabled>::value, "");
static_assert(hamon::default_initializable_t<NotExplicitlyEnabled>::value, "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(NotExplicitlyEnabled), "");
HAMON_RANGES_VIEW_TEST(false, NotExplicitlyEnabled);
HAMON_RANGES_VIEW_TEST(false, NotExplicitlyEnabled&);
HAMON_RANGES_VIEW_TEST(false, NotExplicitlyEnabled&&);
HAMON_RANGES_VIEW_TEST(false, NotExplicitlyEnabled const);
HAMON_RANGES_VIEW_TEST(false, NotExplicitlyEnabled const&);
HAMON_RANGES_VIEW_TEST(false, NotExplicitlyEnabled const&&);

// The type enable it with enable_view
struct ExplicitlyEnabled
{
	ExplicitlyEnabled() = default;
	ExplicitlyEnabled(ExplicitlyEnabled&&) = default;
	ExplicitlyEnabled& operator=(ExplicitlyEnabled&&) = default;
	friend int* begin(ExplicitlyEnabled&);
	friend int* begin(ExplicitlyEnabled const&);
	friend int* end(ExplicitlyEnabled&);
	friend int* end(ExplicitlyEnabled const&);
};

}	// namespace view_test
}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE
template <> HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(true, hamon_ranges_test::view_test::ExplicitlyEnabled);
HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test {
namespace view_test {

static_assert(hamon::ranges::range_t<ExplicitlyEnabled>::value, "");
static_assert(hamon::movable_t<ExplicitlyEnabled>::value, "");
static_assert(hamon::default_initializable_t<ExplicitlyEnabled>::value, "");
static_assert(HAMON_RANGES_ENABLE_VIEW(ExplicitlyEnabled), "");
HAMON_RANGES_VIEW_TEST(true,  ExplicitlyEnabled);
HAMON_RANGES_VIEW_TEST(false, ExplicitlyEnabled&);
HAMON_RANGES_VIEW_TEST(false, ExplicitlyEnabled&&);
HAMON_RANGES_VIEW_TEST(false, ExplicitlyEnabled const);
HAMON_RANGES_VIEW_TEST(false, ExplicitlyEnabled const&);
HAMON_RANGES_VIEW_TEST(false, ExplicitlyEnabled const&&);

// The type has everything else, but it's not a range
struct NotARange : hamon::ranges::view_base
{
	NotARange() = default;
	NotARange(NotARange&&) = default;
	NotARange& operator=(NotARange&&) = default;
};
static_assert(!hamon::ranges::range_t<NotARange>::value, "");
static_assert(hamon::movable_t<NotARange>::value, "");
static_assert(hamon::default_initializable_t<NotARange>::value, "");
static_assert(HAMON_RANGES_ENABLE_VIEW(NotARange), "");
HAMON_RANGES_VIEW_TEST(false, NotARange);
HAMON_RANGES_VIEW_TEST(false, NotARange&);
HAMON_RANGES_VIEW_TEST(false, NotARange&&);
HAMON_RANGES_VIEW_TEST(false, NotARange const);
HAMON_RANGES_VIEW_TEST(false, NotARange const&);
HAMON_RANGES_VIEW_TEST(false, NotARange const&&);

// The type satisfies all requirements
struct View : hamon::ranges::view_base
{
	View() = default;
	View(View&&) = default;
	View& operator=(View&&) = default;
	friend int* begin(View&);
	friend int* begin(View const&);
	friend int* end(View&);
	friend int* end(View const&);
};
static_assert(hamon::ranges::range_t<View>::value, "");
static_assert(hamon::movable_t<View>::value, "");
static_assert(hamon::default_initializable_t<View>::value, "");
static_assert(HAMON_RANGES_ENABLE_VIEW(View), "");
HAMON_RANGES_VIEW_TEST(true,  View);
HAMON_RANGES_VIEW_TEST(false, View&);
HAMON_RANGES_VIEW_TEST(false, View&&);
HAMON_RANGES_VIEW_TEST(false, View const);
HAMON_RANGES_VIEW_TEST(false, View const&);
HAMON_RANGES_VIEW_TEST(false, View const&&);

}	// namespace view_test
}	// namespace hamon_ranges_test

HAMON_RANGES_VIEW_TEST(false, int      [2]);
HAMON_RANGES_VIEW_TEST(false, int const[2]);
HAMON_RANGES_VIEW_TEST(false, int      []);
HAMON_RANGES_VIEW_TEST(false, int const[]);
HAMON_RANGES_VIEW_TEST(false, int      (&)[2]);
HAMON_RANGES_VIEW_TEST(false, int const(&)[2]);
HAMON_RANGES_VIEW_TEST(false, int      (&&)[2]);
HAMON_RANGES_VIEW_TEST(false, int const(&&)[2]);
HAMON_RANGES_VIEW_TEST(false, int      (*)[2]);
HAMON_RANGES_VIEW_TEST(false, int const(*)[2]);
HAMON_RANGES_VIEW_TEST(false, int      *);
HAMON_RANGES_VIEW_TEST(false, int const*);

HAMON_RANGES_VIEW_TEST(false, hamon::array<int, 2>);
HAMON_RANGES_VIEW_TEST(false, hamon::vector<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::deque<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::list<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::forward_list<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::set<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::multiset<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::unordered_set<int>);
HAMON_RANGES_VIEW_TEST(false, hamon::unordered_multiset<int>);
HAMON_RANGES_VIEW_TEST(false, std::string);
#if 0	// TODO
HAMON_RANGES_VIEW_TEST(true,  hamon::string_view);
HAMON_RANGES_VIEW_TEST(true,  hamon::wstring_view);
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_RANGES_VIEW_TEST(true,  hamon::u8string_view);
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_RANGES_VIEW_TEST(true,  hamon::u16string_view);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_RANGES_VIEW_TEST(true,  hamon::u32string_view);
#endif
#endif
HAMON_RANGES_VIEW_TEST(true,  hamon::span<int>);
HAMON_RANGES_VIEW_TEST(true,  hamon::span<int, 0>);
HAMON_RANGES_VIEW_TEST(true,  hamon::span<int, 1>);

HAMON_RANGES_VIEW_TEST(false, test_contiguous_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_contiguous_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_contiguous_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_random_access_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_random_access_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_random_access_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_bidirectional_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_bidirectional_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_bidirectional_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_forward_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_forward_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_forward_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_input_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_input_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_input_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_output_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_output_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_output_range<int>&&);

HAMON_RANGES_VIEW_TEST(false, test_contiguous_sized_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_contiguous_sized_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_contiguous_sized_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_random_access_sized_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_random_access_sized_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_random_access_sized_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_bidirectional_sized_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_bidirectional_sized_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_bidirectional_sized_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_forward_sized_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_forward_sized_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_forward_sized_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_input_sized_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_input_sized_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_input_sized_range<int>&&);
HAMON_RANGES_VIEW_TEST(false, test_output_sized_range<int>);
HAMON_RANGES_VIEW_TEST(false, test_output_sized_range<int>&);
HAMON_RANGES_VIEW_TEST(false, test_output_sized_range<int>&&);

#undef HAMON_RANGES_VIEW_TEST
