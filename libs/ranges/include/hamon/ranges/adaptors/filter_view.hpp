/**
 *	@file	filter_view.hpp
 *
 *	@brief	filter_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_FILTER_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_FILTER_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::filter_view;

namespace views {

using std::ranges::views::filter;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/detail/cached_value.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/has_arrow.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/algorithm/ranges/find_if.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon {
namespace ranges {

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V, hamon::indirect_unary_predicate<hamon::ranges::iterator_t<V>> Pred>
	requires hamon::ranges::view<V> && hamon::is_object_v<Pred>
#else
template <typename V, typename Pred,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range<V>,
		hamon::indirect_unary_predicate<Pred, hamon::ranges::iterator_t<V>>,
		hamon::ranges::view<V>,
		hamon::is_object<Pred>
	>::value>
>
#endif
class filter_view : public hamon::ranges::view_interface<filter_view<V, Pred>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::movable_box<Pred> m_pred;

	using cache_type =
		hamon::ranges::detail::cached_value<
			hamon::ranges::forward_range_t<V>::value,
			hamon::ranges::iterator_t<V>
		>;
	HAMON_NO_UNIQUE_ADDRESS cache_type m_cache;
	
	class sentinel;

	template <typename V2, typename = void>
	struct iterator_category_base {};

	// [range.filter.iterator]/3
	template <typename V2>
	struct iterator_category_base<V2, hamon::enable_if_t<hamon::ranges::forward_range_t<V2>::value>>
	{
	private:
		// [range.filter.iterator]/3.1
		using C = typename hamon::iterator_traits<
			hamon::ranges::iterator_t<V2>
		>::iterator_category;

	public:
		using iterator_category =
			hamon::conditional_t<hamon::derived_from_t<C, hamon::bidirectional_iterator_tag>::value,
				hamon::bidirectional_iterator_tag,	// [range.filter.iterator]/3.2
			hamon::conditional_t<hamon::derived_from_t<C, hamon::forward_iterator_tag>::value,
				hamon::forward_iterator_tag,		// [range.filter.iterator]/3.3
				C									// [range.filter.iterator]/3.4
		>>;
	};

	// [range.filter.iterator], class filter_view​::​iterator
	class iterator : public iterator_category_base<V>
	{
	private:
		using I = hamon::ranges::iterator_t<V>;

		friend sentinel;

		HAMON_NO_UNIQUE_ADDRESS I m_current = I();
		filter_view* m_parent = nullptr;

	public:
		// [range.filter.iterator]/2
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<V>::value,
				hamon::bidirectional_iterator_tag,	// [range.filter.iterator]/2.1
			hamon::conditional_t<hamon::ranges::forward_range_t<V>::value,
				hamon::forward_iterator_tag,		// [range.filter.iterator]/2.2
				hamon::input_iterator_tag			// [range.filter.iterator]/2.3
		>>;
		//using iterator_category = ;        // defined in iterator_category_base
		using value_type      = hamon::ranges::range_value_t<V>;
		using difference_type = hamon::ranges::range_difference_t<V>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator() requires hamon::default_initializable<I> = default;
#else
		template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I2, I)>
		HAMON_CXX11_CONSTEXPR
		iterator()
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<I2>::value)
		{}
#endif
	
		HAMON_CXX11_CONSTEXPR
		iterator(filter_view& parent, I current)
			HAMON_NOEXCEPT_IF(				// noexcept as an extension
				hamon::is_nothrow_move_constructible<I>::value)
			// [range.filter.iterator]/4
			: m_current(hamon::move(current))
			, m_parent(hamon::addressof(parent))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR I const&	// nodiscard as an extension
		base() const& HAMON_NOEXCEPT
		{
			// [range.filter.iterator]/5
			return m_current;
		}

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR I	// nodiscard as an extension
		base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
			hamon::is_nothrow_move_constructible<I>::value)
		{
			// [range.filter.iterator]/6
			return hamon::move(m_current);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_reference_t<V>
		operator*() const
			HAMON_NOEXCEPT_IF_EXPR(*m_current)	// noexcept as an extension
		{
			// [range.filter.iterator]/7
			return *m_current;
		}

		template <typename I2 = I,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::ranges::detail::has_arrow_t<I2>,
				hamon::copyable_t<I2>
			>::value>
		>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR I	// nodiscard as an extension
		operator->() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<I>::value)
			//requires
			//	hamon::ranges::detail::has_arrow<I> &&
			//	hamon::copyable<I>
		{
			// [range.filter.iterator]/8
			return m_current;
		}

		HAMON_CXX14_CONSTEXPR iterator& operator++()
		{
			// [range.filter.iterator]/9
			m_current = hamon::ranges::find_if(
				hamon::move(++m_current),
				hamon::ranges::end(m_parent->m_base),
				hamon::ref(*m_parent->m_pred));
			return *this;
		}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		HAMON_CXX14_CONSTEXPR void operator++(int)
		{
			// [range.filter.iterator]/10
			++*this;
		}

		HAMON_CXX14_CONSTEXPR iterator operator++(int)
			requires hamon::ranges::forward_range<V>
		{
			// [range.filter.iterator]/11
			auto tmp = *this;
			++*this;
			return tmp;
		}
#else
	private:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V)>
		HAMON_CXX14_CONSTEXPR iterator
		increment_impl(hamon::detail::overload_priority<1>)
		{
			// [range.filter.iterator]/11
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		increment_impl(hamon::detail::overload_priority<0>)
		{
			// [range.filter.iterator]/10
			++*this;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto operator++(int)
		->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return increment_impl(hamon::detail::overload_priority<1>{});
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, V2, V)>
		HAMON_CXX14_CONSTEXPR iterator& operator--()
			//requires hamon::ranges::bidirectional_range<V>
		{
			// [range.filter.iterator]/12
			do
			{
				--m_current;
			}
			while (!hamon::invoke(*m_parent->m_pred, *m_current));

			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, V2, V)>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
			//requires hamon::ranges::bidirectional_range<V>
		{
			// [range.filter.iterator]/13
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, I)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current == y.m_current)	// noexcept as an extension
			//requires hamon::equality_comparable<I>
		{
			// [range.filter.iterator]/14
			return x.m_current == y.m_current;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, I)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_rvalue_reference_t<V>
		iter_move(iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_move(i.m_current))
		{
			// [range.filter.iterator]/15
			return hamon::ranges::iter_move(i.m_current);
		}

#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだと以下のコードがエラーになる
		template <HAMON_CONSTRAINED_PARAM_D(hamon::indirectly_swappable, I2, I)>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_swap(x.m_current, y.m_current))
			//requires hamon::indirectly_swappable<I>
		{
			// [range.filter.iterator]/16
			hamon::ranges::iter_swap(x.m_current, y.m_current);
		}
#endif
#endif
	};

	// [range.filter.sentinel], class filter_view​::​sentinel
	class sentinel
	{
	private:
		using Sent = hamon::ranges::sentinel_t<V>;

		HAMON_NO_UNIQUE_ADDRESS Sent m_end = Sent();

	public:
		sentinel() = default;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(filter_view& parent)
			HAMON_NOEXCEPT_IF(			// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::ranges::end(parent.m_base)) &&
				hamon::is_nothrow_move_constructible<Sent>::value)
			// [range.filter.sentinel]/1
			: m_end(hamon::ranges::end(parent.m_base))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Sent	// nodiscard as an extension
		base() const HAMON_NOEXCEPT_IF(				// noexcept as an extension
			hamon::is_nothrow_copy_constructible<Sent>::value)
		{
			// [range.filter.sentinel]/2
			return m_end;
		}

	private:
		HAMON_CXX11_CONSTEXPR bool
		equal(iterator const& x) const
			HAMON_NOEXCEPT_IF_EXPR(x.m_current == m_end)	// noexcept as an extension
		{
			// [range.filter.sentinel]/3
			return x.m_current == m_end;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.equal(x))				// noexcept as an extension
		{
			return y.equal(x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))				// noexcept as an extension
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)					// noexcept as an extension
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))				// noexcept as an extension
		{
			return !(x == y);
		}
#endif
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	filter_view()
		requires hamon::default_initializable<V> &&
			hamon::default_initializable<Pred>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, Pred2, Pred)>
	HAMON_CXX11_CONSTEXPR
	filter_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<V>::value &&
			hamon::is_nothrow_default_constructible<Pred>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	filter_view(V base, Pred pred_)	// predという名前だと、GCCで"-Wshadow"の警告が出る(なぜかbaseは大丈夫)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value &&
			hamon::is_nothrow_move_constructible<Pred>::value)
		// [range.filter.view]/1
		: m_base(hamon::move(base))
		, m_pred(hamon::move(pred_))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR V		// nodiscard as an extension
	base() const& HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
		//requires hamon::copy_constructible<V>
	{
		return m_base;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR V		// nodiscard as an extension
	base() && HAMON_NOEXCEPT_IF(				// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Pred const&	// nodiscard as an extension
	pred() const HAMON_NOEXCEPT_IF_EXPR(*m_pred)		// noexcept as an extension
	{
		// [range.filter.view]/2
		return *m_pred;
	}

private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator
	begin_impl(hamon::detail::overload_priority<1>)
	{
		// [range.filter.view]/5
		if (m_cache.has_value())
		{
			return {*this, m_cache.value()};
		}

		// [range.filter.view]/4
		auto it = hamon::ranges::find_if(m_base, hamon::ref(*m_pred));
		m_cache = it;

		return {*this, hamon::move(it)};
	}

	HAMON_CXX14_CONSTEXPR iterator
	begin_impl(hamon::detail::overload_priority<0>)
	{
		// [range.filter.view]/4
		return {*this, hamon::ranges::find_if(m_base, hamon::ref(*m_pred))};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
	begin()
	{
		// [range.filter.view]/3
		HAMON_ASSERT(m_pred.has_value());

		return begin_impl(hamon::detail::overload_priority<1>{});
	}

private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator
	end_impl(hamon::detail::overload_priority<1>)
	{
		return iterator{*this, hamon::ranges::end(m_base)};
	}

	HAMON_CXX14_CONSTEXPR sentinel
	end_impl(hamon::detail::overload_priority<0>)
	{
		return sentinel{*this};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	end()
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}
};

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename Pred>
filter_view(R&&, Pred) -> filter_view<views::all_t<R>, Pred>;

#endif

// extension: deduction guides が使えないときのために追加
template <typename R, typename Pred>
HAMON_CXX11_CONSTEXPR auto
make_filter_view(R&& r, Pred pred)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		filter_view<hamon::views::all_t<R>, Pred>(hamon::forward<R>(r), pred))

namespace views {

namespace detail {

struct filter_fn
{
public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename Pred>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, Pred&& pred) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::make_filter_view(
			hamon::forward<R>(r), hamon::forward<Pred>(pred)))

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

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::filter_fn filter{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_FILTER_VIEW_HPP
