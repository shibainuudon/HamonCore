/**
 *	@file	drop_while_view.hpp
 *
 *	@brief	drop_while_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DROP_WHILE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_DROP_WHILE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::drop_while_view;

namespace views {

using std::ranges::views::drop_while;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/cached_value.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/algorithm/ranges/find_if_not.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/cref.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.13.2 Class template drop_while_view[range.drop.while.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V, typename Pred>
	requires hamon::ranges::input_range<V> && hamon::is_object_v<Pred> &&
		hamon::indirect_unary_predicate<Pred const, hamon::ranges::iterator_t<V>>
#else
template <typename V, typename Pred,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view_t<V>,
		hamon::ranges::input_range_t<V>,
		hamon::is_object<Pred>,
		hamon::indirect_unary_predicate_t<Pred const, hamon::ranges::iterator_t<V>>
	>::value>
>
#endif
class drop_while_view : public hamon::ranges::view_interface<drop_while_view<V, Pred>>
{
public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	drop_while_view()
		requires hamon::default_initializable<V> && hamon::default_initializable<Pred>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, Pred2, Pred)>
	HAMON_CXX11_CONSTEXPR
	drop_while_view() HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_default_constructible<V2>::value &&
		hamon::is_nothrow_default_constructible<Pred2>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	drop_while_view(V base, Pred pred)
		HAMON_NOEXCEPT_IF(			// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value &&
			hamon::is_nothrow_move_constructible<Pred>::value)
		// [range.drop.while.view]/1
		: m_base(hamon::move(base))
		, m_pred(hamon::move(pred))
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

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Pred const& pred() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [range.drop.while.view]/2
		return *m_pred;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin()
	-> hamon::ranges::iterator_t<V>
	{
		// [range.drop.while.view]/5
		if (m_cache.has_value())
		{
			return m_cache.value();
		}

		// [range.drop.while.view]/3
		HAMON_ASSERT(m_pred.has_value());

		// [range.drop.while.view]/4
		auto it = hamon::ranges::find_if_not(m_base, hamon::cref(*m_pred));
		m_cache = it;

		return it;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		hamon::ranges::end(hamon::declval<V&>()))
	-> hamon::ranges::sentinel_t<V>
	{
		return hamon::ranges::end(m_base);
	}

private:
	using cache_type =
		hamon::ranges::detail::cached_value<
			hamon::ranges::forward_range_t<V>::value,
			hamon::ranges::iterator_t<V>
		>;

	HAMON_NO_UNIQUE_ADDRESS cache_type m_cache;
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	hamon::ranges::detail::movable_box<Pred> m_pred;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename Pred>
drop_while_view(R&&, Pred) -> drop_while_view<views::all_t<R>, Pred>;

#endif

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// extension: deduction guides が使えないときのために追加
template <typename R, typename Pred>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_drop_while_view(R&& r, Pred pred)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		drop_while_view<hamon::views::all_t<R>, Pred>(hamon::forward<R>(r), hamon::move(pred)))

// enable_borrowed_range の特殊化
template <typename T, typename Pred>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::drop_while_view<T, Pred>);

namespace views {

namespace detail {

struct drop_while_fn
{
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename Pred>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, Pred pred) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.drop.while.overview]/2
		hamon::ranges::make_drop_while_view(
			hamon::forward<R>(r), hamon::move(pred)))

	template <typename Pred,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<Pred>, Pred
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(Pred&& pred) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::detail::make_range_adaptor(
			hamon::bind_back(*this, hamon::forward<Pred>(pred))))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::drop_while_fn drop_while{};

}	// inline namespace cpo

}	// namespace views

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_DROP_WHILE_VIEW_HPP
