/**
 *	@file	common_view.hpp
 *
 *	@brief	common_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_COMMON_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_COMMON_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::common_view;

namespace views {

using std::ranges::views::common;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.19.2 Class template common_view[range.common.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires (!hamon::ranges::common_range<V> && hamon::copyable<hamon::ranges::iterator_t<V>>)
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view_t<V>,
		hamon::negation<hamon::ranges::common_range_t<V>>,
		hamon::copyable_t<hamon::ranges::iterator_t<V>>
	>::value>>
#endif
class common_view : public hamon::ranges::view_interface<common_view<V>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	common_view()
		requires hamon::default_initializable<V>
	= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR common_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	common_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.common.view]/1
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const& HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
	{
		return m_base;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

private:
	template <typename V2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::random_access_range_t<V2>,
			hamon::ranges::sized_range_t<V2>
		>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl2(V2& base, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::begin(base))

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, V2)>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl2(V2& base, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::common_iterator<
			hamon::ranges::iterator_t<V2>,
			hamon::ranges::sentinel_t<V2>
		>(hamon::ranges::begin(base)))

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, V2)>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl(V2& base)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		begin_impl2(base, hamon::detail::overload_priority<1>{}))

	template <typename V2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::random_access_range_t<V2>,
			hamon::ranges::sized_range_t<V2>
		>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl2(V2& base, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::begin(base) + hamon::ranges::distance(base))

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, V2)>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl2(V2& base, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::common_iterator<
			hamon::ranges::iterator_t<V2>,
			hamon::ranges::sentinel_t<V2>
		>(hamon::ranges::end(base)))

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, V2)>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl(V2& base)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		end_impl2(base, hamon::detail::overload_priority<1>{}))

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto begin() HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		begin_impl(hamon::declval<V&>()))
	->decltype(begin_impl(hamon::declval<V&>()))
	{
		return begin_impl(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto begin() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		begin_impl(hamon::declval<V2&>()))
	->decltype(begin_impl(hamon::declval<V2&>()))
	{
		return begin_impl(m_base);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		end_impl(hamon::declval<V&>()))
	->decltype(end_impl(hamon::declval<V&>()))
	{
		return end_impl(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		end_impl(hamon::declval<V2&>()))
	->decltype(end_impl(hamon::declval<V2&>()))
	{
		return end_impl(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto size() HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2&>()))
	->decltype(hamon::ranges::size(hamon::declval<V2&>()))
	{
		return hamon::ranges::size(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto size() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2&>()))
	->decltype(hamon::ranges::size(hamon::declval<V2&>()))
	{
		return hamon::ranges::size(m_base);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
common_view(R&&) -> common_view<hamon::views::all_t<R>>;

#endif

// enable_borrowed_range の特殊化
template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::common_view<T>);

namespace views {

namespace detail {

// 26.7.19.1 Overview[range.common.overview]

struct common_fn : public hamon::ranges::range_adaptor_closure<common_fn>
{
private:
	// [range.common.overview]/3.1
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::common_range, R)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::views::all(hamon::forward<R>(r)))

	// [range.common.overview]/3.2
	template <typename R>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::common_view<hamon::views::all_t<R>>{hamon::forward<R>(r)})

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<R>(r), hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::common_fn common{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_COMMON_VIEW_HPP
