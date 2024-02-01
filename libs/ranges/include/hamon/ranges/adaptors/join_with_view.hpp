/**
 *	@file	join_with_view.hpp
 *
 *	@brief	join_with_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_JOIN_WITH_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_JOIN_WITH_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

#define HAMON_USE_STD_RANGES_join_with_VIEW

namespace hamon {
namespace ranges {

using std::ranges::join_with_view;

namespace views {

using std::ranges::views::join_with;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/as_lvalue.hpp>
#include <hamon/ranges/adaptors/detail/non_propagating_cache.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/concepts/common_with.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/variant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

template <typename V, bool = hamon::ranges::forward_range_t<V>::value>
struct join_with_view_outer_iter_base
{
private:
	using OuterIter = hamon::ranges::iterator_t<V>;
protected:
	// present only when !hamon::ranges::forward_range<V>
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::non_propagating_cache<OuterIter> m_outer_it;
};

template <typename V>
struct join_with_view_outer_iter_base<V, true>
{
};

template <typename V, bool = hamon::is_reference<hamon::ranges::range_reference_t<V>>::value>
struct join_with_view_inner_iter_base
{
private:
	using InnerRng = hamon::remove_cv_t<hamon::ranges::range_reference_t<V>>;
protected:
	// present only if is_reference_v<InnerRng> is false
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::non_propagating_cache<InnerRng> m_inner;
};

template <typename V>
struct join_with_view_inner_iter_base<V, true>
{
};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R, typename P>
concept compatible_joinable_ranges =
	hamon::common_with<
		hamon::ranges::range_value_t<R>,
		hamon::ranges::range_value_t<P>> &&
	hamon::common_reference_with<
		hamon::ranges::range_reference_t<R>,
		hamon::ranges::range_reference_t<P>> &&
	hamon::common_reference_with<
		hamon::ranges::range_rvalue_reference_t<R>,
		hamon::ranges::range_rvalue_reference_t<P>>;

#else

template <typename R, typename P>
using compatible_joinable_ranges = hamon::conjunction<
	hamon::common_with<
		hamon::ranges::range_value_t<R>,
		hamon::ranges::range_value_t<P>>,
	hamon::common_reference_with<
		hamon::ranges::range_reference_t<R>,
		hamon::ranges::range_reference_t<P>>,
	hamon::common_reference_with<
		hamon::ranges::range_rvalue_reference_t<R>,
		hamon::ranges::range_rvalue_reference_t<P>>>;

#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R>
concept bidirectional_common =
	hamon::ranges::bidirectional_range<R> && hamon::ranges::common_range<R>;

template <typename R>
using bidirectional_common_t = hamon::bool_constant<bidirectional_common<R>>;

#else

template <typename R>
using bidirectional_common = hamon::conjunction<
	hamon::ranges::bidirectional_range<R>, hamon::ranges::common_range<R>>;

template <typename R>
using bidirectional_common_t = bidirectional_common<R>;

#endif

}	// namespace detail

// 26.7.15.2 Class template join_with_view[range.join.with.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V, hamon::ranges::forward_range Pattern>
	requires hamon::ranges::view<V> &&
		hamon::ranges::input_range<hamon::ranges::range_reference_t<V>> &&
		hamon::ranges::view<Pattern> &&
		hamon::ranges::detail::compatible_joinable_ranges<hamon::ranges::range_reference_t<V>, Pattern>
#else
template <typename V, typename Pattern,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range<V>,
		hamon::ranges::forward_range<Pattern>,
		hamon::ranges::view<V>,
		hamon::ranges::input_range<hamon::ranges::range_reference_t<V>>,
		hamon::ranges::view<Pattern>,
		hamon::ranges::detail::compatible_joinable_ranges<hamon::ranges::range_reference_t<V>, Pattern>
	>::value>>
#endif
class join_with_view : public hamon::ranges::view_interface<join_with_view<V, Pattern>>
	, private hamon::ranges::detail::join_with_view_outer_iter_base<V>
	, private hamon::ranges::detail::join_with_view_inner_iter_base<V>
{
	using InnerRng = hamon::ranges::range_reference_t<V>;

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	//non_propagating_cache<ranges::iterator_t<V>> outer_it_;	// present only when !ranges::forward_range<V>
	//non_propagating_cache<remove_cv_t<InnerRng>> inner_;		// present only if is_reference_v<InnerRng> is false
	HAMON_NO_UNIQUE_ADDRESS Pattern m_pattern = Pattern();

	// [range.join.with.iterator]/2
	template <typename Base, typename InnerBase, typename PatternBase,
		bool = hamon::is_reference<InnerBase>::value &&
			hamon::ranges::forward_range_t<Base>::value &&
			hamon::ranges::forward_range_t<InnerBase>::value>
	struct iterator_category_base
	{
	private:
		using OuterIter = hamon::ranges::iterator_t<Base>;
		using InnerIter = hamon::ranges::iterator_t<InnerBase>;
		using PatternIter = hamon::ranges::iterator_t<PatternBase>;

		// [range.join.with.iterator]/2.1
		using OUTERC = typename hamon::iterator_traits<OuterIter>::iterator_category;
		using INNERC = typename hamon::iterator_traits<InnerIter>::iterator_category;
		using PATTERNC = typename hamon::iterator_traits<PatternIter>::iterator_category;

	public:
		using iterator_category =
			hamon::conditional_t<
				// [range.join.with.iterator]/2.2
				!hamon::is_reference<
					hamon::common_reference_t<
						hamon::iter_reference_t<InnerIter>,
						hamon::iter_reference_t<PatternIter>>
				>::value,
				hamon::input_iterator_tag,
			hamon::conditional_t<
				// [range.join.with.iterator]/2.3
				hamon::derived_from_t<OUTERC, hamon::bidirectional_iterator_tag>::value &&
				hamon::derived_from_t<INNERC, hamon::bidirectional_iterator_tag>::value &&
				hamon::derived_from_t<PATTERNC, hamon::bidirectional_iterator_tag>::value &&
				hamon::ranges::common_range_t<InnerBase>::value &&
				hamon::ranges::common_range_t<PatternBase>::value,
				hamon::bidirectional_iterator_tag,
			hamon::conditional_t<
				// [range.join.with.iterator]/2.4
				hamon::derived_from_t<OUTERC, hamon::forward_iterator_tag>::value &&
				hamon::derived_from_t<INNERC, hamon::forward_iterator_tag>::value &&
				hamon::derived_from_t<PATTERNC, hamon::forward_iterator_tag>::value,
				hamon::forward_iterator_tag,
				// [range.join.with.iterator]/2.5
				hamon::input_iterator_tag
			>>>;
	};
	
	template <typename Base, typename InnerBase, typename PatternBase>
	struct iterator_category_base<Base, InnerBase, PatternBase, false>
	{
	};

	// [range.join.with.iterator], class template join_with_view​::​iterator
	template <bool Const>
	struct iterator : public iterator_category_base<
		hamon::ranges::detail::maybe_const<Const, V>,
		hamon::ranges::range_reference_t<hamon::ranges::detail::maybe_const<Const, V>>,
		hamon::ranges::detail::maybe_const<Const, Pattern>>
	{
	private:
		friend join_with_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, join_with_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using InnerBase = hamon::ranges::range_reference_t<Base>;
		using PatternBase = hamon::ranges::detail::maybe_const<Const, Pattern>;

		using OuterIter = hamon::ranges::iterator_t<Base>;
		using InnerIter = hamon::ranges::iterator_t<InnerBase>;
		using PatternIter = hamon::ranges::iterator_t<PatternBase>;

		using Reference = hamon::common_reference_t<
			hamon::iter_reference_t<InnerIter>,
			hamon::iter_reference_t<PatternIter>>;
		using RValueReference = hamon::common_reference_t<
			hamon::iter_rvalue_reference_t<InnerIter>,
			hamon::iter_rvalue_reference_t<PatternIter>>;

		template <typename B2>
		using ref_is_glvalue =
			hamon::is_reference<hamon::ranges::range_reference_t<B2>>;

		struct Empty{};

		Parent* m_parent = nullptr;
		HAMON_NO_UNIQUE_ADDRESS hamon::conditional_t<
			hamon::ranges::forward_range_t<Base>::value,
			OuterIter,
			Empty> m_outer_it{};	// present only if Base models forward_range
		hamon::variant<PatternIter, InnerIter> m_inner_it;

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR
		iterator(Parent& parent, OuterIter outer)
			// [range.join.with.iterator]/9
			: m_parent(hamon::addressof(parent))
			, m_outer_it(hamon::move(outer))
		{
			if (this->outer() != hamon::ranges::end(m_parent->m_base))
			{
				m_inner_it.template emplace<1>(hamon::ranges::begin(update_inner()));
				satisfy();
			}
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::not_forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR explicit
		iterator(Parent& parent)
			// [range.join.with.iterator]/9
			: m_parent(hamon::addressof(parent))
		{
			if (this->outer() != hamon::ranges::end(m_parent->m_base))
			{
				m_inner_it.template emplace<1>(hamon::ranges::begin(update_inner()));
				satisfy();
			}
		}

		// [range.join.with.iterator]/5
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR OuterIter&
		outer_impl(hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
		{
			return m_outer_it;
		}

		HAMON_CXX14_CONSTEXPR OuterIter&
		outer_impl(hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
		{
			return *m_parent->m_outer_it;
		}

		// [range.join.with.iterator]/5
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX11_CONSTEXPR OuterIter const&
		outer_const_impl(hamon::detail::overload_priority<1>) const HAMON_NOEXCEPT
		{
			return m_outer_it;
		}

		HAMON_CXX11_CONSTEXPR OuterIter const&
		outer_const_impl(hamon::detail::overload_priority<0>) const HAMON_NOEXCEPT
		{
			return *m_parent->m_outer_it;
		}

#if defined(HAMON_MSVC) || \
	defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000)
		// MSVCとGCC(12まで)は、friend指定してもエラーになってしまうので、
		// 仕方なくpublicにする。
	public:
#endif
		HAMON_CXX14_CONSTEXPR OuterIter&
		outer() HAMON_NOEXCEPT
		{
			return outer_impl(hamon::detail::overload_priority<1>{});
		}

		HAMON_CXX11_CONSTEXPR OuterIter const&
		outer() const HAMON_NOEXCEPT
		{
			return outer_const_impl(hamon::detail::overload_priority<1>{});
		}

	private:
		// [range.join.with.iterator]/6
		template <typename B2 = Base,
			typename = hamon::enable_if_t<ref_is_glvalue<B2>::value>>
		HAMON_CXX14_CONSTEXPR auto
		update_inner_impl(hamon::detail::overload_priority<1>)
		->decltype(hamon::ranges::detail::as_lvalue(*outer()))
		{
			return hamon::ranges::detail::as_lvalue(*outer());
		}

		HAMON_CXX14_CONSTEXPR InnerRng&
		update_inner_impl(hamon::detail::overload_priority<0>)
		{
			return m_parent->m_inner.emplace_deref(outer());
		}

		HAMON_CXX14_CONSTEXPR auto
		update_inner()
		->decltype(update_inner_impl(hamon::detail::overload_priority<1>{}))
		{
			return update_inner_impl(hamon::detail::overload_priority<1>{});
		}

		// [range.join.with.iterator]/7
		template <typename B2 = Base,
			typename = hamon::enable_if_t<ref_is_glvalue<B2>::value>>
		HAMON_CXX14_CONSTEXPR auto
		get_inner_impl(hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
		->decltype(hamon::ranges::detail::as_lvalue(*outer()))
		{
			return hamon::ranges::detail::as_lvalue(*outer());
		}

		HAMON_CXX14_CONSTEXPR InnerRng&
		get_inner_impl(hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
		{
			return *m_parent->m_inner;
		}

		HAMON_CXX14_CONSTEXPR auto
		get_inner() HAMON_NOEXCEPT
		->decltype(get_inner_impl(hamon::detail::overload_priority<1>{}))
		{
			return get_inner_impl(hamon::detail::overload_priority<1>{});
		}

		HAMON_CXX14_CONSTEXPR void
		satisfy()
		{
			// [range.join.with.iterator]/8
			while (true)
			{
				if (m_inner_it.index() == 0)
				{
					if (hamon::get<0>(m_inner_it) != hamon::ranges::end(m_parent->m_pattern))
					{
						break;
					}

					m_inner_it.template emplace<1>(hamon::ranges::begin(update_inner()));
				}
				else
				{
					if (hamon::get<1>(m_inner_it) != hamon::ranges::end(get_inner()))
					{
						break;
					}

					if (++outer() == hamon::ranges::end(m_parent->m_base))
					{
						// TODO
						if /*constexpr*/ (ref_is_glvalue<Base>::value)
						{
							m_inner_it.template emplace<0>();
						}

						break;
					}

					m_inner_it.template emplace<0>(hamon::ranges::begin(m_parent->m_pattern));
				}
			}
		}

	public:
		using iterator_concept =
			hamon::conditional_t<
				// [range.join.with.iterator]/1.1
				ref_is_glvalue<Base>::value &&
				hamon::ranges::bidirectional_range_t<Base>::value &&
				hamon::ranges::detail::bidirectional_common_t<InnerBase>::value &&
				hamon::ranges::detail::bidirectional_common_t<PatternBase>::value,
				hamon::bidirectional_iterator_tag,
			hamon::conditional_t<
				// [range.join.with.iterator]/1.2
				ref_is_glvalue<Base>::value &&
				hamon::ranges::forward_range_t<Base>::value &&
				hamon::ranges::forward_range_t<InnerBase>::value,
				hamon::forward_iterator_tag,
				// [range.join.with.iterator]/1.3
				hamon::input_iterator_tag
			>>;
		//using iterator_category = see below;	// not always present
		using value_type = hamon::common_type_t<		// [range.join.with.iterator]/3
			hamon::iter_value_t<InnerIter>,
			hamon::iter_value_t<PatternIter>>;
		using difference_type = hamon::common_type_t<	// [range.join.with.iterator]/4
			hamon::iter_difference_t<OuterIter>,
			hamon::iter_difference_t<InnerIter>,
			hamon::iter_difference_t<PatternIter>>;

		iterator() = default;

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<V2>, OuterIter>::value &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<InnerRng>, InnerIter>::value &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<Pattern>, PatternIter>::value>>
		HAMON_CXX14_CONSTEXPR
		iterator(iterator<!Const> i)
			// [range.join.with.iterator]/10
			: m_parent(i.m_parent)
			, m_outer_it(hamon::move(i.m_outer_it))
		{
			if (i.m_inner_it.index() == 0)
			{
				m_inner_it.template emplace<0>(hamon::get<0>(hamon::move(i.m_inner_it)));
			}
			else
			{
				m_inner_it.template emplace<1>(hamon::get<1>(hamon::move(i.m_inner_it)));
			}
		}

	private:
		struct DereferenceVisitor
		{
			template <typename T>
			HAMON_CXX11_CONSTEXPR Reference
			operator()(T& it) const
			{
				return *it;
			}
		};

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		Reference operator*() const
		{
			// [range.join.with.iterator]/12
			return hamon::visit(DereferenceVisitor{}, m_inner_it);
		}

	private:
		struct IncrementVisitor
		{
			template <typename T>
			HAMON_CXX14_CONSTEXPR void
			operator()(T& it) const
			{
				++it;
			}
		};

	public:
		HAMON_CXX14_CONSTEXPR iterator&
		operator++()
		{
			// [range.join.with.iterator]/13
			hamon::visit(IncrementVisitor{}, m_inner_it);
			satisfy();
			return *this;
		}

	private:
		template <typename B2 = Base,
			typename = hamon::enable_if_t<hamon::conjunction<
				ref_is_glvalue<B2>,
				hamon::forward_iterator_t<OuterIter>,
				hamon::forward_iterator_t<InnerIter>
			>::value>>
		HAMON_CXX14_CONSTEXPR iterator
		post_increment_impl(hamon::detail::overload_priority<1>)
		{
			// [range.join.with.iterator]/15
			iterator tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		post_increment_impl(hamon::detail::overload_priority<0>)
		{
			// [range.join.with.iterator]/14
			++*this;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto
		operator++(int)
		->decltype(post_increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return post_increment_impl(hamon::detail::overload_priority<1>{});
		}

	private:
		struct DecrementVisitor
		{
			template <typename T>
			HAMON_CXX14_CONSTEXPR void
			operator()(T& it) const
			{
				--it;
			}
		};

	public:
		template <typename B2 = Base,
			typename = hamon::enable_if_t<hamon::conjunction<
				ref_is_glvalue<B2>,
				hamon::ranges::bidirectional_range_t<Base>,
				hamon::ranges::detail::bidirectional_common_t<InnerBase>,
				hamon::ranges::detail::bidirectional_common_t<PatternBase>
			>::value>>
		HAMON_CXX14_CONSTEXPR iterator&
		operator--()
		{
			// [range.join.with.iterator]/16
			if (m_outer_it == hamon::ranges::end(m_parent->m_base))
			{
				auto&& inner = *--m_outer_it;
				m_inner_it.template emplace<1>(hamon::ranges::end(inner));
			}

			while (true)
			{
				if (m_inner_it.index() == 0)
				{
					auto& it = hamon::get<0>(m_inner_it);
					if (it == hamon::ranges::begin(m_parent->m_pattern))
					{
						auto&& inner = *--m_outer_it;
						m_inner_it.template emplace<1>(hamon::ranges::end(inner));
					}
					else
					{
						break;
					}
				}
				else
				{
					auto& it = hamon::get<1>(m_inner_it);
					auto&& inner = *m_outer_it;
					if (it == hamon::ranges::begin(inner))
					{
						m_inner_it.template emplace<0>(hamon::ranges::end(m_parent->m_pattern));
					}
					else
					{
						break;
					}
				}
			}

			hamon::visit(DecrementVisitor{}, m_inner_it);
			return *this;
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<hamon::conjunction<
				ref_is_glvalue<B2>,
				hamon::ranges::bidirectional_range_t<Base>,
				hamon::ranges::detail::bidirectional_common_t<InnerBase>,
				hamon::ranges::detail::bidirectional_common_t<PatternBase>
			>::value>>
		HAMON_CXX14_CONSTEXPR iterator
		operator--(int)
		{
			// [range.join.with.iterator]/17
			iterator tmp = *this;
			--*this;
			return tmp;
		}

	private:
		template <typename B2>
		using EqualityComparable = hamon::conjunction<
			ref_is_glvalue<B2>,
			hamon::ranges::forward_range_t<B2>,
			hamon::equality_comparable_t<InnerIter>
		>;

		template <typename B2 = Base,
			typename = hamon::enable_if_t<EqualityComparable<B2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
				bool(x.m_outer_it == y.m_outer_it && x.m_inner_it == y.m_inner_it))
		{
			// [range.join.with.iterator]/18
			return x.m_outer_it == y.m_outer_it && x.m_inner_it == y.m_inner_it;
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

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		RValueReference iter_move(iterator const& x)
		{
			return hamon::visit<RValueReference>(hamon::ranges::iter_move, x.m_inner_it);
		}

#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだと以下のコードがエラーになる
		template <typename InnerIter2 = InnerIter,
			typename = hamon::enable_if_t<
				hamon::indirectly_swappable_t<InnerIter2, PatternIter>::value
			>>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(iterator const& x, iterator const& y)
		{
			hamon::visit(hamon::ranges::iter_swap, x.m_inner_it, y.m_inner_it);
		}
#endif
#endif
	};

	// [range.join.with.sentinel], class template join_with_view​::​sentinel
	template <bool Const>
	struct sentinel
	{
	private:
		friend join_with_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, join_with_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using Sent = hamon::ranges::sentinel_t<Base>;

		HAMON_NO_UNIQUE_ADDRESS Sent m_end = Sent();

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(Parent& parent) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<Sent>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(hamon::declval<V&>())))
			// [range.join.with.sentinel]/1
			: m_end(hamon::ranges::end(parent.m_base))
		{}

	public:
		sentinel() = default;

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::sentinel_t<V>,
					hamon::ranges::sentinel_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> s)
			// [range.join.with.sentinel]/2
			: m_end(hamon::move(s.m_end))
		{}

	private:
		template <bool OtherConst>
		using EqualityComparable = hamon::sentinel_for_t<
			Sent,
			hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<OtherConst, V>>>;

		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(bool(x.outer() == y.m_end))		// noexcept as an extension
		{
			// [range.join.with.sentinel]/3
			return x.outer() == y.m_end;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)		// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<EqualityComparable<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}
#endif
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	join_with_view()
		requires
			hamon::default_initializable<V> &&
			hamon::default_initializable<Pattern>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, Pattern2, Pattern)>
	HAMON_CXX11_CONSTEXPR join_with_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<V>::value &&
			hamon::is_nothrow_default_constructible<Pattern>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	join_with_view(V base, Pattern pattern) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value &&
		hamon::is_nothrow_move_constructible<Pattern>::value)
		// [range.join.with.hamon::ranges::view]/1
		: m_base(hamon::move(base))
		, m_pattern(hamon::move(pattern))
	{}

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::input_range_t<R>,
			hamon::constructible_from_t<V, hamon::views::all_t<R>>,
			hamon::constructible_from_t<Pattern, hamon::ranges::single_view<hamon::ranges::range_value_t<InnerRng>>>
		>::value>>
	HAMON_CXX11_CONSTEXPR explicit
	join_with_view(R&& r, hamon::ranges::range_value_t<InnerRng> e)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(V(hamon::views::all(hamon::forward<R>(r)))) &&
			HAMON_NOEXCEPT_EXPR(Pattern(hamon::views::single(hamon::move(e)))))
		// [range.join.with.hamon::ranges::view]/2
		: m_base(hamon::views::all(hamon::forward<R>(r)))
		, m_pattern(hamon::views::single(hamon::move(e)))
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
			hamon::is_reference<InnerRng>::value &&
			hamon::ranges::detail::simple_view_t<Pattern>::value
	>
	HAMON_CXX14_CONSTEXPR iterator<UseConst>
	begin_impl(hamon::detail::overload_priority<1>)
	{
		return iterator<UseConst>{*this, hamon::ranges::begin(m_base)};
	}

	HAMON_CXX14_CONSTEXPR iterator<false>
	begin_impl(hamon::detail::overload_priority<0>)
	{
		this->m_outer_it = hamon::ranges::begin(m_base);
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
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<V2>,
			hamon::ranges::forward_range_t<Pattern const>,
			hamon::is_reference<hamon::ranges::range_reference_t<V2>>,
			hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V2>>
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto begin() const
	-> iterator<true>
	{
		return iterator<true>{*this, hamon::ranges::begin(m_base)};
	}

private:
	template <typename V2 = V,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_reference<InnerRng>,
			hamon::ranges::forward_range_t<V2>,
			hamon::ranges::forward_range_t<InnerRng>,
			hamon::ranges::common_range_t<V2>,
			hamon::ranges::common_range_t<InnerRng>
		>::value>,
		bool UseConst =
			hamon::ranges::detail::simple_view_t<V2>::value &&
			hamon::ranges::detail::simple_view_t<Pattern>::value>
	HAMON_CXX14_CONSTEXPR iterator<UseConst>
	end_impl(hamon::detail::overload_priority<1>)
	{
		return iterator<UseConst>{*this, hamon::ranges::end(m_base)};
	}

	template <typename V2 = V,
		bool UseConst =
			hamon::ranges::detail::simple_view_t<V2>::value &&
			hamon::ranges::detail::simple_view_t<Pattern>::value>
	HAMON_CXX14_CONSTEXPR sentinel<UseConst>
	end_impl(hamon::detail::overload_priority<0>)
	{
		return sentinel<UseConst>{*this};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end()
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}

private:
	template <typename V2 = V const,
		typename InnerConstRng = hamon::ranges::range_reference_t<V2>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<InnerConstRng>,
			hamon::ranges::common_range_t<V2>,
			hamon::ranges::common_range_t<InnerConstRng>
		>::value>
	>
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
	template <typename V2 = V const,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<V2>,
			hamon::ranges::forward_range_t<Pattern const>,
			hamon::is_reference<hamon::ranges::range_reference_t<V2>>,
			hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V2>>
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const
	->decltype(end_const_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_const_impl(hamon::detail::overload_priority<1>{});
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename P>
join_with_view(R&&, P&&)
-> join_with_view<hamon::views::all_t<R>, hamon::views::all_t<P>>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
join_with_view(R&&, hamon::ranges::range_value_t<hamon::ranges::range_reference_t<R>>)
-> join_with_view<
	hamon::views::all_t<R>,
	hamon::ranges::single_view<hamon::ranges::range_value_t<hamon::ranges::range_reference_t<R>>>>;

#endif

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// extension: deduction guides が使えないときのために追加
template <typename R, typename P>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_join_with_view(R&& r, P&& p)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		join_with_view<hamon::views::all_t<R>, hamon::views::all_t<P>>(
			hamon::forward<R>(r), hamon::forward<P>(p)))

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_join_with_view(R&& r, hamon::ranges::range_value_t<hamon::ranges::range_reference_t<R>> v)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		join_with_view<
			hamon::views::all_t<R>,
			hamon::ranges::single_view<hamon::ranges::range_value_t<hamon::ranges::range_reference_t<R>>>
		>(hamon::forward<R>(r), hamon::move(v)))

namespace views {

namespace detail {

struct join_with_fn
{
public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename P>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, P&& p) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::make_join_with_view(
			hamon::forward<R>(r), hamon::forward<P>(p)))

	template <typename Delim,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<Delim>, Delim
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(Delim&& delim) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::detail::make_range_adaptor(
			hamon::bind_back(*this, hamon::forward<Delim>(delim))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::join_with_fn join_with{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_JOIN_WITH_VIEW_HPP
