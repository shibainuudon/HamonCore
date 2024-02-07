/**
 *	@file	as_const_view.hpp
 *
 *	@brief	as_const_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_AS_CONST_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_AS_CONST_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::as_const_view;

namespace views {

using std::ranges::views::as_const;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/cbegin.hpp>
#include <hamon/ranges/cend.hpp>
#include <hamon/ranges/concepts/constant_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_empty_view.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/span.hpp>
#include <hamon/span/detail/is_specialization_of_span.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.21.2 Class template as_const_view[range.as.const.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires hamon::ranges::input_range<V>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view_t<V>,
		hamon::ranges::input_range_t<V>
	>::value>>
#endif
class as_const_view : public hamon::ranges::view_interface<as_const_view<V>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	as_const_view()
		requires hamon::default_initializable<V>
	= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR as_const_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	as_const_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.as.const.view]/1
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	V base() const& HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
	{
		return m_base;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	V base() && HAMON_NOEXCEPT_IF(				// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto begin() HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		hamon::ranges::cbegin(hamon::declval<V2&>()))
	->decltype(hamon::ranges::cbegin(hamon::declval<V2&>()))
	{
		return hamon::ranges::cbegin(m_base);
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto begin() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::cbegin(hamon::declval<V2&>()))
	->decltype(hamon::ranges::cbegin(hamon::declval<V2&>()))
	{
		return hamon::ranges::cbegin(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		hamon::ranges::cend(hamon::declval<V2&>()))
	->decltype(hamon::ranges::cend(hamon::declval<V2&>()))
	{
		return hamon::ranges::cend(m_base);
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::cend(hamon::declval<V2&>()))
	->decltype(hamon::ranges::cend(hamon::declval<V2&>()))
	{
		return hamon::ranges::cend(m_base);
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
as_const_view(R&&) -> as_const_view<hamon::views::all_t<R>>;

#endif

// enable_borrowed_range の特殊化
template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::as_const_view<T>);

namespace views {

namespace detail {

// is_specialization_of_ref_view
template <typename T>
struct is_specialization_of_ref_view
	: public hamon::false_type {};

template <typename R>
struct is_specialization_of_ref_view<hamon::ranges::ref_view<R>>
	: public hamon::true_type {};


#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.21.1 Overview[range.as.const.overview]

struct as_const_fn : public hamon::ranges::range_adaptor_closure<as_const_fn>
{
private:
	// [range.as.const.overview]/2.1
	template <typename R,
		typename = hamon::enable_if_t<
			hamon::ranges::constant_range_t<hamon::views::all_t<R>>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<5>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::views::all(hamon::forward<R>(r)))

	// [range.as.const.overview]/2.2
	template <typename R, typename U = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_empty_view<U>::value>,
		typename X = hamon::remove_reference_t<hamon::ranges::range_reference_t<R>>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& /*r*/, hamon::detail::overload_priority<4>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::empty_view<X const>{})

	// [range.as.const.overview]/2.3
	template <typename R, typename U = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_span<U>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::span<
				typename U::element_type const,
				U::extent
			>(hamon::forward<R>(r)))

	// [range.as.const.overview]/2.4
	template <typename R, typename U = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			is_specialization_of_ref_view<U>::value>,
		typename X = hamon::remove_reference_t<decltype(hamon::declval<R>().base())>,
		typename = hamon::enable_if_t<
			hamon::ranges::constant_range_t<X const>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::ref_view<X const>(
				static_cast<X const&>(hamon::forward<R>(r).base())))

	// [range.as.const.overview]/2.5
	template <typename R, typename U = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_lvalue_reference<R>,
			hamon::ranges::constant_range_t<U const>,
			hamon::negation<hamon::ranges::view_t<U>>
		>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::ref_view<U const>(
				static_cast<U const&>(r)))

	// [range.as.const.overview]/2.6
	template <typename R>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::as_const_view<hamon::views::all_t<R>>(
				hamon::forward<R>(r)))

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<R>(r), hamon::detail::overload_priority<5>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::as_const_fn as_const{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_AS_CONST_VIEW_HPP
