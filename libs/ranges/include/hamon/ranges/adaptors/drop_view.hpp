/**
 *	@file	drop_view.hpp
 *
 *	@brief	drop_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DROP_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_DROP_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::drop_view;

namespace views {

using std::ranges::views::drop;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/cached_value.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_empty_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_iota_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_repeat_view.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_size_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/span.hpp>
#include <hamon/span/detail/is_specialization_of_span.hpp>
#include <hamon/string_view.hpp>
#include <hamon/string_view/detail/is_specialization_of_basic_string_view.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon {
namespace ranges {

// 26.7.12.2 Class template drop_view[range.drop.view]

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::view, V)>
class drop_view : public hamon::ranges::view_interface<drop_view<V>>
{
public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	drop_view() requires hamon::default_initializable<V> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR
	drop_view() HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_default_constructible<V2>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	drop_view(V base, hamon::ranges::range_difference_t<V> n)
		HAMON_NOEXCEPT_IF(			// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value)
		// [range.drop.view]/2
		: m_base(hamon::move(base))
		, m_count(n)
	{
#if HAMON_CXX_STANDARD >= 14
		// [range.drop.view]/1
		HAMON_ASSERT(n >= 0);
#endif
	}

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

	template <typename V2 = V const,
		typename = hamon::enable_if_t<!hamon::conjunction<
			hamon::ranges::detail::simple_view_t<V>,
			hamon::ranges::random_access_range_t<V2>,
			hamon::ranges::sized_range_t<V2>
		>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin()
	-> hamon::ranges::iterator_t<V>
	{
		// [range.drop.view]/4
		if (m_cache.has_value())
		{
			return m_cache.value();
		}

		// [range.drop.view]/3
		auto it = hamon::ranges::next(hamon::ranges::begin(m_base), m_count, hamon::ranges::end(m_base));
		m_cache = it;

		return it;
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::random_access_range_t<V2>,
			hamon::ranges::sized_range_t<V2>
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto begin() const
	-> hamon::ranges::iterator_t<V2>
	{
		// [range.drop.view]/3
		return hamon::ranges::next(hamon::ranges::begin(m_base), m_count, hamon::ranges::end(m_base));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto end()
	-> hamon::ranges::sentinel_t<V2>
	{
		return hamon::ranges::end(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto end() const
	-> hamon::ranges::sentinel_t<V2>
	{
		return hamon::ranges::end(m_base);
	}

private:
	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR T size_impl(T s, U c)
	{
		return s < static_cast<T>(c) ? 0 : s - static_cast<T>(c);
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto size()
	-> hamon::ranges::range_size_t<V2>
	{
		return size_impl(hamon::ranges::size(m_base), m_count);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto size() const
	-> hamon::ranges::range_size_t<V2>
	{
		return size_impl(hamon::ranges::size(m_base), m_count);
	}

private:
	using cache_type =
		hamon::ranges::detail::cached_value<
			hamon::ranges::forward_range_t<V>::value &&
			!(hamon::ranges::random_access_range_t<V>::value && hamon::ranges::sized_range_t<V>::value),
			hamon::ranges::iterator_t<V>
		>;

	HAMON_NO_UNIQUE_ADDRESS cache_type m_cache;
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	hamon::ranges::range_difference_t<V> m_count = 0;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
drop_view(R&&, hamon::ranges::range_difference_t<R>)
-> drop_view<hamon::views::all_t<R>>;

#endif

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// extension: deduction guides が使えないときのために追加
template <typename R>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_drop_view(R&& r, hamon::ranges::range_difference_t<R> n)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		drop_view<hamon::views::all_t<R>>(hamon::forward<R>(r), n))

// enable_borrowed_range の特殊化
template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::drop_view<T>);

namespace views {

namespace detail {

template <typename T>
struct is_subrange_store_size
{
	static constexpr bool value = false;
};

template <typename It, typename Sent>
struct is_subrange_store_size<hamon::ranges::subrange<It, Sent, ranges::subrange_kind::sized>>
{
	static constexpr bool value = !hamon::sized_sentinel_for_t<Sent, It>::value;
};

// 26.7.12.1 Overview[range.drop.overview]

struct drop_fn
{
private:
	template <typename R, typename N>
	static HAMON_CXX11_CONSTEXPR hamon::ranges::range_difference_t<R>
	min_distance(R&& r, N&& n)
	{
		using D = hamon::ranges::range_difference_t<R>;
		return hamon::min<D>(hamon::ranges::distance(r), hamon::forward<N>(n));
	}

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_empty_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& /*n*/, hamon::detail::overload_priority<8>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.1
		hamon::detail::decay_copy(hamon::forward<R>(r)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_span<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<7>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.2.1
		hamon::span<typename T::element_type>(
			hamon::ranges::begin(r) + min_distance(r, n),
			hamon::ranges::end(r)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_basic_string_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<6>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.2.2
		T(hamon::ranges::begin(r) + min_distance(r, n),
		  hamon::ranges::end(r)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_iota_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<5>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.2.3
		T(hamon::ranges::begin(r) + min_distance(r, n),
		  hamon::ranges::end(r)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_subrange<T>::value &&
			!is_subrange_store_size<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<4>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.2.4
		T(hamon::ranges::begin(r) + min_distance(r, n),
		  hamon::ranges::end(r)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_subrange<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<3>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.3
		T(hamon::ranges::begin(r) + min_distance(r, n),
		  hamon::ranges::end(r),
		  hamon::ranges::detail::to_unsigned_like(
			hamon::ranges::distance(r) - min_distance(r, n))))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_repeat_view<T>::value &&
			hamon::ranges::sized_range_t<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<2>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.4.1
		hamon::views::repeat(
			*r.begin(),
			hamon::ranges::distance(r) - min_distance(r, n)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_repeat_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& /*n*/, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.4.2
		hamon::detail::decay_copy(hamon::forward<R>(r)))

	template <typename R, typename N>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& n, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.overview]/2.5
		hamon::ranges::make_drop_view(hamon::forward<R>(r), hamon::forward<N>(n)))

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R),
		HAMON_CONSTRAINED_PARAM(hamon::convertible_to, hamon::ranges::range_difference_t<R>, N)
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, N&& n) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
		hamon::forward<R>(r),
		hamon::forward<N>(n),
		hamon::detail::overload_priority<8>{}))

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<T>, T
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& n) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::detail::make_range_adaptor(
			hamon::bind_back(*this, hamon::forward<T>(n))))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::drop_fn drop{};

}	// inline namespace cpo

}	// namespace views

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_DROP_VIEW_HPP
