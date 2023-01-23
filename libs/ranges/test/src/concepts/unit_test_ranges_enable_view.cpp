/**
 *	@file	unit_test_ranges_enable_view.cpp
 *
 *	@brief	ranges::enable_view のテスト
 */

#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/ranges/views/view_base.hpp>
#include <hamon/ranges/views/view_interface.hpp>

namespace hamon_ranges_test {
namespace enable_view_test {

// Doesn't derive from view_base
struct Empty { };
static_assert(!HAMON_RANGES_ENABLE_VIEW(Empty), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(Empty&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(Empty&&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const Empty), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const Empty&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const Empty&&), "");

// Derives from view_base, but privately
struct PrivateViewBase : private hamon::ranges::view_base { };
static_assert(!HAMON_RANGES_ENABLE_VIEW(PrivateViewBase), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(PrivateViewBase&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(PrivateViewBase&&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const PrivateViewBase), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const PrivateViewBase&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const PrivateViewBase&&), "");

// Derives from view_base, but specializes enable_view to false
struct EnableViewFalse : hamon::ranges::view_base { };

}	// namespace enable_view_test
}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE
template <> HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(false, hamon_ranges_test::enable_view_test::EnableViewFalse);
HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test {
namespace enable_view_test {

static_assert(!HAMON_RANGES_ENABLE_VIEW(EnableViewFalse), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(EnableViewFalse&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(EnableViewFalse&&), "");
static_assert( HAMON_RANGES_ENABLE_VIEW(const EnableViewFalse), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const EnableViewFalse&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const EnableViewFalse&&), "");

// Derives from view_base
struct PublicViewBase : hamon::ranges::view_base { };
static_assert( HAMON_RANGES_ENABLE_VIEW(PublicViewBase), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(PublicViewBase&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(PublicViewBase&&), "");
static_assert( HAMON_RANGES_ENABLE_VIEW(const PublicViewBase), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const PublicViewBase&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const PublicViewBase&&), "");

// Does not derive from view_base, but specializes enable_view to true
struct EnableViewTrue { };

}	// namespace enable_view_test
}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE
template <> HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(true, hamon_ranges_test::enable_view_test::EnableViewTrue);
HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test {
namespace enable_view_test {

static_assert( HAMON_RANGES_ENABLE_VIEW(EnableViewTrue), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(EnableViewTrue&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(EnableViewTrue&&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const EnableViewTrue), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const EnableViewTrue&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const EnableViewTrue&&), "");

struct V1 : hamon::ranges::view_interface<V1> {};
static_assert( HAMON_RANGES_ENABLE_VIEW(V1), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(V1&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(V1&&), "");
static_assert( HAMON_RANGES_ENABLE_VIEW(const V1), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V1&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V1&&), "");

#if !defined(HAMON_MSVC)
// TODO MSVCだとview_interface<T>をpublicで1つだけ継承しているかどうか判定ができていない
// ※MSVC STL の enable_view でもできていない
struct V2 : hamon::ranges::view_interface<V1>, hamon::ranges::view_interface<V2> {};
static_assert(!HAMON_RANGES_ENABLE_VIEW(V2), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(V2&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(V2&&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V2), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V2&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V2&&), "");
#endif

struct V3 : hamon::ranges::view_interface<V1> {};
static_assert( HAMON_RANGES_ENABLE_VIEW(V3), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(V3&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(V3&&), "");
static_assert( HAMON_RANGES_ENABLE_VIEW(const V3), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V3&), "");
static_assert(!HAMON_RANGES_ENABLE_VIEW(const V3&&), "");

struct PrivateInherit : private hamon::ranges::view_interface<PrivateInherit> {};
static_assert(!HAMON_RANGES_ENABLE_VIEW(PrivateInherit), "");

// ADL-proof
#if defined(HAMON_HAS_CXX20_CONCEPTS)
struct Incomplete;
template<class T> struct Holder { T t; };
static_assert(!HAMON_RANGES_ENABLE_VIEW(Holder<Incomplete>*), "");
#endif

static_assert(!HAMON_RANGES_ENABLE_VIEW(void), "");

}	// namespace enable_view_test
}	// namespace hamon_ranges_test
