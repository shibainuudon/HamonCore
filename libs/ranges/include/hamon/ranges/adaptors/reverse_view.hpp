/**
 *	@file	reverse_view.hpp
 *
 *	@brief	reverse_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_REVERSE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_REVERSE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::reverse_view;

namespace views {

using std::ranges::views::reverse;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/adaptors/detail/cached_value.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.20.2 Class template reverse_view[range.reverse.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires hamon::ranges::bidirectional_range<V>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view_t<V>,
		hamon::ranges::bidirectional_range_t<V>
	>::value>>
#endif
class reverse_view : public hamon::ranges::view_interface<reverse_view<V>>
{
private:
	using cache_type =
		hamon::ranges::detail::cached_value<
			!hamon::ranges::common_range_t<V>::value,
			hamon::ranges::iterator_t<V>
		>;

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS cache_type m_cache;

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	reverse_view()
		requires hamon::default_initializable<V>
	= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR reverse_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	reverse_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.reverse.view]/1
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
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin_impl(hamon::detail::overload_priority<0>)
	->hamon::reverse_iterator<hamon::ranges::iterator_t<V>>
	{
		// [range.reverse.view]/3
		if (!m_cache.has_value())
		{
			m_cache = hamon::ranges::next(hamon::ranges::begin(m_base), hamon::ranges::end(m_base));
		}

		// [range.reverse.view]/2
		return hamon::make_reverse_iterator(m_cache.value());
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto begin_impl(hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			hamon::make_reverse_iterator(hamon::ranges::end(hamon::declval<V2&>())))
	->hamon::reverse_iterator<hamon::ranges::iterator_t<V2>>
	{
		// [range.reverse.view]/4
		return hamon::make_reverse_iterator(hamon::ranges::end(m_base));
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		begin_impl(hamon::detail::overload_priority<1>{}))
	->hamon::reverse_iterator<hamon::ranges::iterator_t<V>>
	{
		return begin_impl(hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto begin() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::make_reverse_iterator(hamon::ranges::end(hamon::declval<V2&>())))
	->hamon::reverse_iterator<hamon::ranges::iterator_t<V2>>
	{
		// [range.reverse.view]/4
		return hamon::make_reverse_iterator(hamon::ranges::end(m_base));
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		hamon::make_reverse_iterator(hamon::ranges::begin(hamon::declval<V&>())))
	->hamon::reverse_iterator<hamon::ranges::iterator_t<V>>
	{
		// [range.reverse.view]/5
		return hamon::make_reverse_iterator(hamon::ranges::begin(m_base));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::make_reverse_iterator(hamon::ranges::begin(hamon::declval<V2&>())))
	->hamon::reverse_iterator<hamon::ranges::iterator_t<V2>>
	{
		// [range.reverse.view]/5
		return hamon::make_reverse_iterator(hamon::ranges::begin(m_base));
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
reverse_view(R&&) -> reverse_view<hamon::views::all_t<R>>;

#endif

// enable_borrowed_range の特殊化
template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::reverse_view<T>);

namespace views {

namespace detail {

template <typename T>
struct is_specialization_of_reverse_view
	: public hamon::false_type {};

template <typename R>
struct is_specialization_of_reverse_view<hamon::ranges::reverse_view<R>>
	: public hamon::true_type {};

template <typename T>
struct is_reversed_sized_subrange
	: public hamon::false_type {};

template <typename I>
struct is_reversed_sized_subrange<
	hamon::ranges::subrange<
		hamon::reverse_iterator<I>,
		hamon::reverse_iterator<I>,
		hamon::ranges::subrange_kind::sized>>
	: public hamon::true_type{};

template <typename T>
struct is_reversed_unsized_subrange
	: public hamon::false_type {};

template <typename I>
struct is_reversed_unsized_subrange<
	hamon::ranges::subrange<
		hamon::reverse_iterator<I>,
		hamon::reverse_iterator<I>,
		hamon::ranges::subrange_kind::unsized>>
	: public hamon::true_type{};

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.20.1 Overview[range.reverse.overview]

struct reverse_fn : public hamon::ranges::range_adaptor_closure<reverse_fn>
{
private:
	// [range.reverse.overview]/2.1
	template <typename R,
		typename T = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			is_specialization_of_reverse_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::forward<R>(r).base())

	// [range.reverse.overview]/2.2.1
	template <typename R,
		typename T = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			is_reversed_sized_subrange<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::make_subrange(r.end().base(), r.begin().base(), r.size()))

	// [range.reverse.overview]/2.2.2
	template <typename R,
		typename T = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			is_reversed_unsized_subrange<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::make_subrange(r.end().base(), r.begin().base()))

	// [range.reverse.overview]/2.3
	template <typename R>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::reverse_view<hamon::views::all_t<R>>{hamon::forward<R>(r)})

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<R>(r), hamon::detail::overload_priority<3>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::reverse_fn reverse{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_REVERSE_VIEW_HPP
