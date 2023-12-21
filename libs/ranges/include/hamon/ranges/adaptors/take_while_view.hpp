/**
 *	@file	take_while_view.hpp
 *
 *	@brief	take_while_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_TAKE_WHILE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_TAKE_WHILE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::take_while_view;

namespace views {

using std::ranges::views::take_while;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

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
class take_while_view : public hamon::ranges::view_interface<take_while_view<V, Pred>>
{
	// [range.take.while.sentinel], class template take_while_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend sentinel<!Const>;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;

		template <bool OtherConst>
		using Iter = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<OtherConst, V>>;

		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end = BaseSent();
		Pred const* m_pred = nullptr;

	public:
		sentinel() = default;
		
		HAMON_CXX11_CONSTEXPR explicit
		sentinel(BaseSent end, Pred const* pred)
			HAMON_NOEXCEPT_IF(		// noexcept as an extension
				hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.take.while.sentinel]/1
			: m_end(hamon::move(end))
			, m_pred(pred)
		{}
		
		template <bool C2 = Const,
			typename = hamon::enable_if_t<C2 &&
				hamon::convertible_to_t<hamon::ranges::sentinel_t<V>, BaseSent>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> s)
			HAMON_NOEXCEPT_IF(		// noexcept as an extension
				hamon::is_nothrow_constructible<BaseSent, hamon::ranges::sentinel_t<V>>::value)
			// [range.take.while.sentinel]/2
			: m_end(hamon::move(s.m_end))
			, m_pred(s.m_pred)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
		BaseSent base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseSent>::value)
		{
			return m_end;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(BaseIter const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.m_end == x || !hamon::invoke(*y.m_pred, *x))	// noexcept as an extension
		{
			// [range.take.while.sentinel]/3
			return y.m_end == x || !hamon::invoke(*y.m_pred, *x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(BaseIter const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, BaseIter const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)				// noexcept as an extension
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, BaseIter const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(Iter<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.m_end == x || !hamon::invoke(*y.m_pred, *x))	// noexcept as an extension
		{
			// [range.take.while.sentinel]/3
			return y.m_end == x || !hamon::invoke(*y.m_pred, *x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(Iter<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, Iter<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)			// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, Iter<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}
#endif
	};

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::movable_box<Pred> m_pred;

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	take_while_view()
		requires hamon::default_initializable<V> && hamon::default_initializable<Pred>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, Pred2, Pred)
	>
	HAMON_CXX11_CONSTEXPR
	take_while_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<V2>::value &&
			hamon::is_nothrow_default_constructible<Pred2>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	take_while_view(V base, Pred pred_)	// predという名前だと、GCCで"-Wshadow"の警告が出る(なぜかbaseは大丈夫)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value &&
			hamon::is_nothrow_move_constructible<Pred>::value)
		// [range.take.while.view]/1
		: m_base(hamon::move(base))
		, m_pred(hamon::move(pred_))
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
		// [range.take.while.view]/2
		return *m_pred;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::begin(hamon::declval<V2&>()))
	->decltype(hamon::ranges::begin(hamon::declval<V2&>()))
	{
		return hamon::ranges::begin(m_base);
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::range_t<V2>,
			hamon::indirect_unary_predicate_t<Pred const, hamon::ranges::iterator_t<V2>>
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto begin() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::begin(hamon::declval<V2&>()))
	->decltype(hamon::ranges::begin(hamon::declval<V2&>()))
	{
		return hamon::ranges::begin(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF(			// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::end(m_base)) &&
		hamon::is_nothrow_move_constructible<sentinel<false>>::value)
	-> sentinel<false>
	{
		return sentinel<false>(hamon::ranges::end(m_base), hamon::addressof(*m_pred));
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::range_t<V2>,
			hamon::indirect_unary_predicate_t<Pred const, hamon::ranges::iterator_t<V2>>
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF(		// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::end(m_base)) &&
		hamon::is_nothrow_move_constructible<sentinel<true>>::value)
	-> sentinel<true>
	{
		return sentinel<true>(hamon::ranges::end(m_base), hamon::addressof(*m_pred));
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename Pred>
take_while_view(R&&, Pred) -> take_while_view<hamon::views::all_t<R>, Pred>;

#endif

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// extension: deduction guides が使えないときのために追加
template <typename R, typename Pred>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_take_while_view(R&& r, Pred pred)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		take_while_view<hamon::views::all_t<R>, Pred>(hamon::forward<R>(r), hamon::move(pred)))

namespace views {

namespace detail {

struct take_while_fn
{
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename Pred>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, Pred pred) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.while.overview]/2
		hamon::ranges::make_take_while_view(
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
detail::take_while_fn take_while{};

}	// inline namespace cpo

}	// namespace views

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_TAKE_WHILE_VIEW_HPP
