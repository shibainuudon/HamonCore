/**
 *	@file	ref_view.hpp
 *
 *	@brief	ref_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_REF_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_REF_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::ref_view;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/different_from.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.6.2 Class template ref_view	[range.ref.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::range R>
	requires hamon::is_object_v<R>
#else
template <typename R,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::range_t<R>,
		hamon::is_object<R>
	>::value>
>
#endif
class ref_view : public hamon::ranges::view_interface<ref_view<R>>
{
private:
	R* m_r;

	// [range.ref.view]/3
	static void FUN(R&);
	static void FUN(R&&) = delete;

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <hamon::ranges::detail::different_from<ref_view> T>
		// [range.ref.view]/3
		requires hamon::convertible_to<T, R&> &&
			requires { FUN(hamon::declval<T>()); }
#else
	template <typename T,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::detail::different_from_t<T, ref_view>,
			hamon::convertible_to<T, R&>
		>::value>,
		typename = decltype(FUN(hamon::declval<T>()))
	>
#endif
	HAMON_CXX11_CONSTEXPR
	ref_view(T&& t)
	HAMON_NOEXCEPT_IF_EXPR(static_cast<R&>(hamon::declval<T>()))	// noexcept as an extension
		// [range.ref.view]/2
		: m_r(hamon::addressof(static_cast<R&>(hamon::forward<T>(t))))
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	R& base() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return *m_r;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::ranges::iterator_t<R> begin() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::begin(*m_r))	// noexcept as an extension
	{
		return hamon::ranges::begin(*m_r);
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::ranges::sentinel_t<R> end() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::end(*m_r))	// noexcept as an extension
	{
		return hamon::ranges::end(*m_r);
	}

	template <typename R2 = R,
		typename = decltype(hamon::ranges::empty(hamon::declval<R2&>()))>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR 	// nodiscard as an extension
	bool empty() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::empty(hamon::declval<R2&>()))	// noexcept as an extension
//		requires requires { hamon::ranges::empty(*m_r); }
	{
		return hamon::ranges::empty(*m_r);
	}

	template <typename R2 = R,
		typename = hamon::enable_if_t<hamon::ranges::sized_range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR 	// nodiscard as an extension
	auto size() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::size(hamon::declval<R2&>()))	// noexcept as an extension
	->decltype(hamon::ranges::size(hamon::declval<R2&>()))
//		requires hamon::ranges::sized_range<R>
	{
		return hamon::ranges::size(*m_r);
	}

	template <typename R2 = R,
		typename = hamon::enable_if_t<hamon::ranges::contiguous_range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR 	// nodiscard as an extension
	auto data() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::data(hamon::declval<R2&>()))	// noexcept as an extension
	->decltype(hamon::ranges::data(hamon::declval<R2&>()))
//		requires hamon::ranges::contiguous_range<R>
	{
		return hamon::ranges::data(*m_r);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
ref_view(R&) -> ref_view<R>;

#endif

template <typename R>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::ranges::ref_view<R>);

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_REF_VIEW_HPP
