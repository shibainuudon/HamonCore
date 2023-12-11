/**
 *	@file	as_rvalue_view.hpp
 *
 *	@brief	as_rvalue_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_AS_RVALUE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_AS_RVALUE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	(defined(__cpp_lib_ranges_as_rvalue) && (__cpp_lib_ranges_as_rvalue >= 202207L))	// P2446R2

#define HAMON_USE_STD_RANGES_AS_RVALUE_VIEW

namespace hamon {
namespace ranges {

using std::ranges::as_rvalue_view;

namespace views {

using std::ranges::views::as_rvalue;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/iterator/make_move_sentinel.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.7.2 Class template as_rvalue_view	[range.as.rvalue.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires hamon::ranges::input_range<V>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view<V>,
		hamon::ranges::input_range<V>
	>::value>
>
#endif
class as_rvalue_view : public hamon::ranges::view_interface<as_rvalue_view<V>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	as_rvalue_view() requires hamon::default_initializable<V> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR
	as_rvalue_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V2>::value)
	{}
#endif
	
	HAMON_CXX11_CONSTEXPR explicit
	as_rvalue_view(V base)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value)
		// [range.as.rvalue.view]
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR V base() const&
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<V>::value)
//		requires hamon::copy_constructible<V>
	{
		return m_base;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR V base() &&
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto begin()
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			hamon::make_move_iterator(hamon::ranges::begin(hamon::declval<V2&>())))
	->decltype(hamon::make_move_iterator(hamon::ranges::begin(hamon::declval<V2&>())))
//		requires (!hamon::ranges::detail::simple_view<V>)
	{
		return hamon::make_move_iterator(hamon::ranges::begin(m_base));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto begin() const
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			hamon::make_move_iterator(hamon::ranges::begin(hamon::declval<V2&>())))
	->decltype(hamon::make_move_iterator(hamon::ranges::begin(hamon::declval<V2&>())))
//		requires hamon::ranges::range<V const>
	{
		return hamon::make_move_iterator(hamon::ranges::begin(m_base));
	}

private:
	template <typename V2, typename = hamon::enable_if_t<hamon::ranges::common_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl(V2& base, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::make_move_iterator(hamon::ranges::end(base)))
	->decltype(hamon::make_move_iterator(hamon::ranges::end(base)))
	{
		return hamon::make_move_iterator(hamon::ranges::end(base));
	}

	template <typename V2>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl(V2& base, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::make_move_sentinel(hamon::ranges::end(base)))
	->decltype(hamon::make_move_sentinel(hamon::ranges::end(base)))
	{
		return hamon::make_move_sentinel(hamon::ranges::end(base));
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto end()
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
//		requires (!hamon::ranges::detail::simple_view<V>)
	{
		return end_impl(m_base, hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto end() const
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
//		requires hamon::ranges::range<V const>
	{
		return end_impl(m_base, hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto size()
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			hamon::ranges::size(hamon::declval<V2&>()))
	->decltype(hamon::ranges::size(hamon::declval<V2&>()))
//		requires hamon::ranges::sized_range<V>
	{
		return hamon::ranges::size(m_base);
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto size() const
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			hamon::ranges::size(hamon::declval<V2&>()))
	->decltype(hamon::ranges::size(hamon::declval<V2&>()))
//		requires hamon::ranges::sized_range<V const>
	{
		return hamon::ranges::size(m_base);
	}
};

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
as_rvalue_view(R&&) -> as_rvalue_view<hamon::views::all_t<R>>;

#endif

// extension: deduction guides が使えないときのために追加
template <typename R>
HAMON_CXX11_CONSTEXPR auto
make_as_rvalue_view(R&& r)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		as_rvalue_view<hamon::views::all_t<R>>(hamon::forward<R>(r)))

// [range.as.rvalue], as rvalue view
template <typename R>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(R),
	hamon::ranges::as_rvalue_view<R>);

namespace views {

namespace detail {

// 26.7.7 As rvalue view[range.as.rvalue]

struct as_rvalue_fn : public hamon::ranges::range_adaptor_closure<as_rvalue_fn>
{
private:
	// [range.as.rvalue.overview]/2.1
	template <typename T,
		typename = hamon::enable_if_t<
			hamon::same_as_t<
				hamon::ranges::range_rvalue_reference_t<T>,
				hamon::ranges::range_reference_t<T>
			>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::views::all(hamon::forward<T>(t)))

	// [range.as.rvalue.overview]/2.2
	template <typename T>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::make_as_rvalue_view(hamon::forward<T>(t)))
public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::as_rvalue_fn as_rvalue{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_AS_RVALUE_VIEW_HPP
