/**
 *	@file	join_view.hpp
 *
 *	@brief	join_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_JOIN_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_JOIN_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::join_view;

namespace views {

using std::ranges::views::join;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/adaptors/detail/as_lvalue.hpp>
#include <hamon/ranges/adaptors/detail/non_propagating_cache.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/has_arrow.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/optional.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

template <typename V, bool = hamon::ranges::forward_range_t<V>::value>
struct join_view_outer_iter_base
{
private:
	using OuterIter = hamon::ranges::iterator_t<V>;
protected:
	// present only when !forward_range<V>
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::non_propagating_cache<OuterIter> m_outer;
};

template <typename V>
struct join_view_outer_iter_base<V, true>
{
};

template <typename V, bool = hamon::is_reference<hamon::ranges::range_reference_t<V>>::value>
struct join_view_inner_iter_base
{
private:
	using InnerRng = hamon::remove_cv_t<hamon::ranges::range_reference_t<V>>;
protected:
	// present only if is_reference_v<InnerRng> is false
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::non_propagating_cache<InnerRng> m_inner;
};

template <typename V>
struct join_view_inner_iter_base<V, true>
{
};

}	// namespace detail

inline namespace join_view_ns
{

// 26.7.14.3 Class template join_view​::​iterator[range.join.iterator]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V>
	requires hamon::ranges::view<V> &&
		hamon::ranges::input_range<hamon::ranges::range_reference_t<V>>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range_t<V>,
		hamon::ranges::view_t<V>,
		hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V>>
	>::value>
>
#endif
class join_view : public hamon::ranges::view_interface<join_view<V>>
	, private hamon::ranges::detail::join_view_outer_iter_base<V>
	, private hamon::ranges::detail::join_view_inner_iter_base<V>
{
private:
	using InnerRng = hamon::ranges::range_reference_t<V>;

	template <typename Base,
		bool = hamon::is_reference<hamon::ranges::range_reference_t<Base>>::value &&
			hamon::ranges::forward_range_t<Base>::value &&
			hamon::ranges::forward_range_t<hamon::ranges::range_reference_t<Base>>::value
	>
	struct iterator_category_base
	{
	private:
		using OuterIter = hamon::ranges::iterator_t<Base>;
		using InnerIter = hamon::ranges::iterator_t<hamon::ranges::range_reference_t<Base>>;

		// [range.join.iterator]/2.1
		using OUTERC = typename hamon::iterator_traits<OuterIter>::iterator_category;
		using INNERC = typename hamon::iterator_traits<InnerIter>::iterator_category;

	public:
		using iterator_category =
			hamon::conditional_t<
				hamon::derived_from_t<OUTERC, hamon::bidirectional_iterator_tag>::value &&
				hamon::derived_from_t<INNERC, hamon::bidirectional_iterator_tag>::value &&
				hamon::ranges::common_range_t<hamon::ranges::range_reference_t<Base>>::value,
					hamon::bidirectional_iterator_tag,	// [range.join.iterator]/2.2
			hamon::conditional_t<
				hamon::derived_from_t<OUTERC, hamon::forward_iterator_tag>::value &&
				hamon::derived_from_t<INNERC, hamon::forward_iterator_tag>::value,
					hamon::forward_iterator_tag,		// [range.join.iterator]/2.3
					hamon::input_iterator_tag			// [range.join.iterator]/2.4
			>>;
	};

	template <typename Base>
	struct iterator_category_base<Base, false>
	{};

	// [range.join.iterator], class template join_view​::​iterator
	template <bool Const>
	struct iterator
		: public iterator_category_base<hamon::ranges::detail::maybe_const<Const, V>>
	{
	private:
		friend join_view;

		using Parent    = hamon::ranges::detail::maybe_const<Const, join_view>;
		using Base      = hamon::ranges::detail::maybe_const<Const, V>;
		using OuterIter = hamon::ranges::iterator_t<Base>;
		using InnerIter = hamon::ranges::iterator_t<hamon::ranges::range_reference_t<Base>>;

		template <typename B2>
		using ref_is_glvalue =
			hamon::is_reference<hamon::ranges::range_reference_t<B2>>;

		struct Empty{};
		HAMON_NO_UNIQUE_ADDRESS hamon::conditional_t<
			hamon::ranges::forward_range_t<Base>::value,
			OuterIter,
			Empty>	m_outer {};	// present only if Base models forward_range
		hamon::optional<InnerIter> m_inner;
		Parent* m_parent  = nullptr;

		// [range.join.iterator]/6
		template <typename B2 = Base,
			typename = hamon::enable_if_t<ref_is_glvalue<B2>::value>>
		HAMON_CXX14_CONSTEXPR auto
		update_inner_impl(OuterIter const& x, hamon::detail::overload_priority<1>)
		->decltype(*x)
		{
			return *x;	// *x is a reference
		}

		HAMON_CXX14_CONSTEXPR hamon::remove_cv_t<InnerRng>&
		update_inner_impl(OuterIter const& x, hamon::detail::overload_priority<0>)
		{
			return m_parent->m_inner.emplace_deref(x);
		}

		HAMON_CXX14_CONSTEXPR auto
		update_inner(OuterIter const& x)
		->decltype(update_inner_impl(x, hamon::detail::overload_priority<1>{}))
		{
			return update_inner_impl(x, hamon::detail::overload_priority<1>{});
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<ref_is_glvalue<B2>::value>>
		HAMON_CXX14_CONSTEXPR void
		satisfy_epilogue_impl(hamon::detail::overload_priority<1>)
		{
			m_inner.reset();
		}

		HAMON_CXX14_CONSTEXPR void
		satisfy_epilogue_impl(hamon::detail::overload_priority<0>)
		{
		}

		HAMON_CXX14_CONSTEXPR void
		satisfy_epilogue()
		{
			satisfy_epilogue_impl(hamon::detail::overload_priority<1>{});
		}

		HAMON_CXX14_CONSTEXPR void
		satisfy()
		{
			for (; outer() != hamon::ranges::end(m_parent->m_base); ++outer())
			{
				auto&& inner = update_inner(outer());
				m_inner = hamon::ranges::begin(inner);
				if (*m_inner != hamon::ranges::end(inner))
				{
					return;
				}
			}

			satisfy_epilogue();
		}

		// [range.join.iterator]/5
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR OuterIter&
		outer_impl(hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
		{
			return this->m_outer;
		}

		HAMON_CXX14_CONSTEXPR OuterIter&
		outer_impl(hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
		{
			return *m_parent->m_outer;
		}

		// [range.join.iterator]/5
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX11_CONSTEXPR OuterIter const&
		outer_impl(hamon::detail::overload_priority<1>) const HAMON_NOEXCEPT
		{
			return this->m_outer;
		}

		HAMON_CXX11_CONSTEXPR OuterIter const&
		outer_impl(hamon::detail::overload_priority<0>) const HAMON_NOEXCEPT
		{
			return *m_parent->m_outer;
		}

		HAMON_CXX14_CONSTEXPR OuterIter&
		outer() HAMON_NOEXCEPT	// noexcept as an extension
		{
			return outer_impl(hamon::detail::overload_priority<1>{});
		}

		HAMON_CXX11_CONSTEXPR OuterIter const&
		outer() const HAMON_NOEXCEPT	// noexcept as an extension
		{
			return outer_impl(hamon::detail::overload_priority<1>{});
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator(Parent& parent, OuterIter outer)
			// [range.join.iterator]/7
			: m_outer(hamon::move(outer))
			, m_parent(hamon::addressof(parent))
		{
			satisfy();
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::not_forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR explicit iterator(Parent& parent)
			// [range.join.iterator]/8
			: m_parent(hamon::addressof(parent))
		{
			satisfy();
		}

	public:
		using iterator_concept  = hamon::conditional_t<
			ref_is_glvalue<Base>::value &&
			hamon::ranges::bidirectional_range_t<Base>::value &&
			hamon::ranges::bidirectional_range_t<hamon::ranges::range_reference_t<Base>>::value &&
			hamon::ranges::common_range_t<hamon::ranges::range_reference_t<Base>>::value,
				hamon::bidirectional_iterator_tag,	// [range.join.iterator]/1.1
			hamon::conditional_t<
			ref_is_glvalue<Base>::value &&
			hamon::ranges::forward_range_t<Base>::value &&
			hamon::ranges::forward_range_t<hamon::ranges::range_reference_t<Base>>::value,
				hamon::forward_iterator_tag,		// [range.join.iterator]/1.2
				hamon::input_iterator_tag			// [range.join.iterator]/1.3
			>>;
		//using iterator_category = see below;                        // not always present
		using value_type        = hamon::ranges::range_value_t<hamon::ranges::range_reference_t<Base>>;
		using difference_type   = hamon::common_type_t<	// [range.join.iterator]/3
			hamon::ranges::range_difference_t<Base>,
			hamon::ranges::range_difference_t<hamon::ranges::range_reference_t<Base>>>;

		iterator() = default;

		template <typename V2 = V, typename InnerRng2 = InnerRng,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<V2>, OuterIter>::value &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<InnerRng2>, InnerIter>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i)
			HAMON_NOEXCEPT_IF(		// noexcept as an extension
				hamon::is_nothrow_move_constructible<OuterIter>::value &&
				hamon::is_nothrow_move_constructible<InnerIter>::value)
			// [range.join.iterator]/9
			: m_outer(hamon::move(i.m_outer))
			, m_inner(hamon::move(i.m_inner))
			, m_parent(i.m_parent)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator*() const HAMON_NOEXCEPT_IF_EXPR(**m_inner)	// noexcept as an extension
		->decltype(**m_inner)
		{
			return **m_inner;
		}

		template <typename InnerIter2 = InnerIter,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::has_arrow_t<InnerIter2>::value &&
				hamon::copyable_t<InnerIter2>::value>>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR InnerIter	// nodiscard as an extension
		operator->() const HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<InnerIter>::value)
		{
			// [range.join.iterator]/11
			return *m_inner;
		}

	private:
		// [range.join.iterator]/12
		template <typename B2 = Base,
			typename = hamon::enable_if_t<ref_is_glvalue<B2>::value>>
		HAMON_CXX14_CONSTEXPR auto
		get_inner_range_impl(hamon::detail::overload_priority<1>)
		->decltype(*outer())
		{
			return *outer();
		}

		HAMON_CXX14_CONSTEXPR hamon::remove_cv_t<InnerRng>&
		get_inner_range_impl(hamon::detail::overload_priority<0>)
		{
			return *m_parent->m_inner;
		}

		HAMON_CXX14_CONSTEXPR auto//decltype(auto)
		get_inner_range()
		->decltype(get_inner_range_impl(hamon::detail::overload_priority<1>{}))
		{
			return get_inner_range_impl(hamon::detail::overload_priority<1>{});
		}

	public:
		HAMON_CXX14_CONSTEXPR iterator& operator++()
		{
			// [range.join.iterator]/12
			auto& inner_range = get_inner_range();

			// [range.join.iterator]/13
			if (++*m_inner == hamon::ranges::end(hamon::ranges::detail::as_lvalue(inner_range)))
			{
				++outer();
				satisfy();
			}

			return *this;
		}

	private:
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				ref_is_glvalue<B2>::value &&
				hamon::ranges::forward_range_t<B2>::value &&
				hamon::ranges::forward_range_t<hamon::ranges::range_reference_t<B2>>::value>>
		HAMON_CXX14_CONSTEXPR iterator
		increment_impl(hamon::detail::overload_priority<1>)
		{
			// [range.join.iterator]/15
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		increment_impl(hamon::detail::overload_priority<0>)
		{
			// [range.join.iterator]/14
			++*this;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto operator++(int)
		->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return increment_impl(hamon::detail::overload_priority<1>{});
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				ref_is_glvalue<B2>::value &&
				hamon::ranges::bidirectional_range_t<B2>::value &&
				hamon::ranges::bidirectional_range_t<hamon::ranges::range_reference_t<B2>>::value &&
				hamon::ranges::common_range_t<hamon::ranges::range_reference_t<B2>>::value>>
		HAMON_CXX14_CONSTEXPR iterator& operator--()
		{
			// [range.join.iterator]/16
			if (this->m_outer == hamon::ranges::end(m_parent->m_base))
			{
				m_inner = hamon::ranges::end(hamon::ranges::detail::as_lvalue(*--this->m_outer));
			}

			while (*m_inner == hamon::ranges::begin(hamon::ranges::detail::as_lvalue(*this->m_outer)))
			{
				*m_inner = hamon::ranges::end(hamon::ranges::detail::as_lvalue(*--this->m_outer));
			}

			--*m_inner;
			return *this;
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				ref_is_glvalue<B2>::value &&
				hamon::ranges::bidirectional_range_t<B2>::value &&
				hamon::ranges::bidirectional_range_t<hamon::ranges::range_reference_t<B2>>::value &&
				hamon::ranges::common_range_t<hamon::ranges::range_reference_t<B2>>::value>>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
		{
			// [range.join.iterator]/17
			auto tmp = *this;
			--*this;
			return tmp;
		}

	private:
		template <typename B2>
		using EqualityComparable = hamon::conjunction<
			ref_is_glvalue<B2>,
			hamon::ranges::forward_range_t<B2>,
			hamon::equality_comparable_t<hamon::ranges::iterator_t<hamon::ranges::range_reference_t<B2>>>
		>;

		template <typename B2 = Base,
			typename = hamon::enable_if_t<EqualityComparable<B2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
				bool(x.m_outer == y.m_outer && x.m_inner == y.m_inner))
		{
			// [range.join.iterator]/18
			return x.m_outer == y.m_outer && x.m_inner == y.m_inner;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <typename B2 = Base,
			typename = hamon::enable_if_t<EqualityComparable<B2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		iter_move(iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(ranges::iter_move(*i.m_inner))
		->decltype(ranges::iter_move(hamon::declval<InnerIter&>()))
		{
			return ranges::iter_move(*i.m_inner);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::indirectly_swappable, InnerIter2, InnerIter)>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(ranges::iter_swap(*x.m_inner, *y.m_inner))
		{
			// [range.join.iterator]/19
			return ranges::iter_swap(*x.m_inner, *y.m_inner);
		}
	};

	// [range.join.sentinel], class template join_view​::​sentinel
	template <bool Const>
	struct sentinel
	{
	private:
		friend sentinel<!Const>;

		using Parent = hamon::ranges::detail::maybe_const<Const, join_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using Sent = hamon::ranges::sentinel_t<Base>;

		HAMON_NO_UNIQUE_ADDRESS Sent m_end = Sent();

	public:
		sentinel() = default;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(Parent& parent) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<Sent>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(hamon::declval<V&>())))
			// [range.join.sentinel]/1
			: m_end(hamon::ranges::end(parent.m_base))
		{}
		
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::sentinel_t<V>,
					hamon::ranges::sentinel_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> s) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_constructible<Sent, hamon::ranges::sentinel_t<V>>::value)
			// [range.join.sentinel]/2
			: m_end(hamon::move(s.m_end))
		{}

	private:
		template <bool OtherConst>
		using EqualityComparable = hamon::sentinel_for_t<
			Sent,
			hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<OtherConst, V>>>;

		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR bool
		equal(iterator<OtherConst> const& x) const
			HAMON_NOEXCEPT_IF_EXPR(bool(x.outer() == m_end))
		{
			// [range.join.sentinel]/3
			return x.outer() == m_end;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.equal(x))			// noexcept as an extension
		{
			return y.equal(x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)				// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}
#endif
	};

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();

	//non-propagating-cache<hamon::ranges::iterator_t<V>> outer_;    // present only when !forward_range<V>
	//non-propagating-cache<hamon::remove_cv_t<InnerRng>> inner_;    // present only if is_reference_v<InnerRng> is false

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	join_view() requires hamon::default_initializable<V> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR join_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	join_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR V	// nodiscard as an extension
	base() const& HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
	{
		return m_base;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR V	// nodiscard as an extension
	base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V),
		bool UseConst =
			hamon::ranges::detail::simple_view_t<V2>::value &&
			hamon::is_reference<InnerRng>::value>
	HAMON_CXX14_CONSTEXPR iterator<UseConst>
	begin_impl(hamon::detail::overload_priority<1>)
	{
		return iterator<UseConst>{*this, hamon::ranges::begin(m_base)};
	}

	HAMON_CXX14_CONSTEXPR iterator<false>
	begin_impl(hamon::detail::overload_priority<0>)
	{
		this->m_outer = hamon::ranges::begin(m_base);
		return iterator<false>{*this};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin()
	->decltype(begin_impl(hamon::detail::overload_priority<1>{}))
	{
		return begin_impl(hamon::detail::overload_priority<1>{});
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<V2>::value &&
			hamon::is_reference<hamon::ranges::range_reference_t<V2>>::value &&
			hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V2>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const
	{
		return iterator<true>{*this, hamon::ranges::begin(m_base)};
	}

private:
	template <typename V2 = V,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<V2>::value &&
			hamon::is_reference<InnerRng>::value &&
			hamon::ranges::forward_range_t<InnerRng>::value &&
			hamon::ranges::common_range_t<V2>::value &&
			hamon::ranges::common_range_t<InnerRng>::value
		>,
		bool UseConst = hamon::ranges::detail::simple_view_t<V2>::value>
	HAMON_CXX14_CONSTEXPR iterator<UseConst>
	end_impl(hamon::detail::overload_priority<1>)
	{
		return iterator<UseConst>{*this, hamon::ranges::end(m_base)};
	}

	template <typename V2 = V,
		bool UseConst = hamon::ranges::detail::simple_view_t<V2>::value>
	HAMON_CXX14_CONSTEXPR sentinel<UseConst>
	end_impl(hamon::detail::overload_priority<0>)
	{
		return sentinel<UseConst>{*this};
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<hamon::ranges::range_reference_t<V2>>::value &&
			hamon::ranges::common_range_t<V2>::value &&
			hamon::ranges::common_range_t<hamon::ranges::range_reference_t<V2>>::value>>
	HAMON_CXX11_CONSTEXPR iterator<true>
	end_const_impl(hamon::detail::overload_priority<1>) const
	{
		return iterator<true>{*this, hamon::ranges::end(m_base)};
	}

	HAMON_CXX11_CONSTEXPR sentinel<true>
	end_const_impl(hamon::detail::overload_priority<0>) const
	{
		return sentinel<true>{*this};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR 	// nodiscard as an extension
	auto end()
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<V2>::value &&
			hamon::is_reference<hamon::ranges::range_reference_t<V2>>::value &&
			hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V2>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR 	// nodiscard as an extension
	auto end() const
	->decltype(end_const_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_const_impl(hamon::detail::overload_priority<1>{});
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
explicit join_view(R&&)->join_view<hamon::views::all_t<R>>;

#endif

}	// inline namespace join_view_ns

namespace views {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct join_fn : public hamon::ranges::range_adaptor_closure<join_fn>
{
public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::join_view<views::all_t<R>>(hamon::forward<R>(r)))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::join_fn join{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_JOIN_VIEW_HPP
