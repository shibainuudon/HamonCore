/**
 *	@file	unit_test_ranges_enable_view.cpp
 *
 *	@brief	ranges::enable_view のテスト
 */

#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/utility/view_interface.hpp>

namespace hamon_ranges_test {
namespace enable_view_test {

// Doesn't derive from view_base
struct Empty { };
static_assert(!hamon::ranges::enable_view<Empty>, "");
static_assert(!hamon::ranges::enable_view<Empty&>, "");
static_assert(!hamon::ranges::enable_view<Empty&&>, "");
static_assert(!hamon::ranges::enable_view<const Empty>, "");
static_assert(!hamon::ranges::enable_view<const Empty&>, "");
static_assert(!hamon::ranges::enable_view<const Empty&&>, "");

// Derives from view_base, but privately
struct PrivateViewBase : private hamon::ranges::view_base { };
static_assert(!hamon::ranges::enable_view<PrivateViewBase>, "");
static_assert(!hamon::ranges::enable_view<PrivateViewBase&>, "");
static_assert(!hamon::ranges::enable_view<PrivateViewBase&&>, "");
static_assert(!hamon::ranges::enable_view<const PrivateViewBase>, "");
static_assert(!hamon::ranges::enable_view<const PrivateViewBase&>, "");
static_assert(!hamon::ranges::enable_view<const PrivateViewBase&&>, "");

// Derives from view_base, but specializes enable_view to false
struct EnableViewFalse : hamon::ranges::view_base { };

}	// namespace enable_view_test
}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool enable_view<hamon_ranges_test::enable_view_test::EnableViewFalse> = false;

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test {
namespace enable_view_test {

static_assert(!hamon::ranges::enable_view<EnableViewFalse>, "");
static_assert(!hamon::ranges::enable_view<EnableViewFalse&>, "");
static_assert(!hamon::ranges::enable_view<EnableViewFalse&&>, "");
static_assert( hamon::ranges::enable_view<const EnableViewFalse>, "");
static_assert(!hamon::ranges::enable_view<const EnableViewFalse&>, "");
static_assert(!hamon::ranges::enable_view<const EnableViewFalse&&>, "");

// Derives from view_base
struct PublicViewBase : hamon::ranges::view_base { };
static_assert( hamon::ranges::enable_view<PublicViewBase>, "");
static_assert(!hamon::ranges::enable_view<PublicViewBase&>, "");
static_assert(!hamon::ranges::enable_view<PublicViewBase&&>, "");
static_assert( hamon::ranges::enable_view<const PublicViewBase>, "");
static_assert(!hamon::ranges::enable_view<const PublicViewBase&>, "");
static_assert(!hamon::ranges::enable_view<const PublicViewBase&&>, "");

// Does not derive from view_base, but specializes enable_view to true
struct EnableViewTrue { };

}	// namespace enable_view_test
}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool enable_view<hamon_ranges_test::enable_view_test::EnableViewTrue> = true;

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test {
namespace enable_view_test {

static_assert( hamon::ranges::enable_view<EnableViewTrue>, "");
static_assert(!hamon::ranges::enable_view<EnableViewTrue&>, "");
static_assert(!hamon::ranges::enable_view<EnableViewTrue&&>, "");
static_assert(!hamon::ranges::enable_view<const EnableViewTrue>, "");
static_assert(!hamon::ranges::enable_view<const EnableViewTrue&>, "");
static_assert(!hamon::ranges::enable_view<const EnableViewTrue&&>, "");

struct V1 : hamon::ranges::view_interface<V1> {};
static_assert( hamon::ranges::enable_view<V1>, "");
static_assert(!hamon::ranges::enable_view<V1&>, "");
static_assert(!hamon::ranges::enable_view<V1&&>, "");
static_assert( hamon::ranges::enable_view<const V1>, "");
static_assert(!hamon::ranges::enable_view<const V1&>, "");
static_assert(!hamon::ranges::enable_view<const V1&&>, "");

#if !defined(HAMON_MSVC)
// TODO MSVCだとview_interface<T>をpublicで1つだけ継承しているかどうか判定ができていない
// ※MSVC STL の enable_view でもできていない
struct V2 : hamon::ranges::view_interface<V1>, hamon::ranges::view_interface<V2> {};
static_assert(!hamon::ranges::enable_view<V2>, "");
static_assert(!hamon::ranges::enable_view<V2&>, "");
static_assert(!hamon::ranges::enable_view<V2&&>, "");
static_assert(!hamon::ranges::enable_view<const V2>, "");
static_assert(!hamon::ranges::enable_view<const V2&>, "");
static_assert(!hamon::ranges::enable_view<const V2&&>, "");
#endif

struct V3 : hamon::ranges::view_interface<V1> {};
static_assert( hamon::ranges::enable_view<V3>, "");
static_assert(!hamon::ranges::enable_view<V3&>, "");
static_assert(!hamon::ranges::enable_view<V3&&>, "");
static_assert( hamon::ranges::enable_view<const V3>, "");
static_assert(!hamon::ranges::enable_view<const V3&>, "");
static_assert(!hamon::ranges::enable_view<const V3&&>, "");

struct PrivateInherit : private hamon::ranges::view_interface<PrivateInherit> {};
static_assert(!hamon::ranges::enable_view<PrivateInherit>, "");

// ADL-proof
#if defined(HAMON_HAS_CXX20_CONCEPTS)
struct Incomplete;
template<class T> struct Holder { T t; };
static_assert(!hamon::ranges::enable_view<Holder<Incomplete>*>, "");
#endif

static_assert(!hamon::ranges::enable_view<void>, "");

}	// namespace enable_view_test
}	// namespace hamon_ranges_test
