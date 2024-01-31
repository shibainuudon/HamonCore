/**
 *	@file	lazy_split_view.hpp
 *
 *	@brief	lazy_split_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_LAZY_SPLIT_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_LAZY_SPLIT_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

#define HAMON_USE_STD_RANGES_LAZY_SPLIT_VIEW

namespace hamon {
namespace ranges {

using std::ranges::lazy_split_view;

namespace views {

using std::ranges::views::lazy_split;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/non_propagating_cache.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/end.hpp>
//#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/algorithm/ranges/find.hpp>
#include <hamon/algorithm/ranges/mismatch.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <auto>
struct require_constant;

template <typename R>
concept tiny_range =
	hamon::ranges::sized_range<R> &&
	requires { typename require_constant<hamon::remove_reference_t<R>::size()>; } &&
	(hamon::remove_reference_t<R>::size() <= 1);

template <typename R>
using tiny_range_t = hamon::bool_constant<tiny_range<R>>;

#else

template <typename T>
struct tiny_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::ranges::sized_range_t<U>::value
		>,
		typename = hamon::enable_if_t<
			(hamon::remove_reference_t<U>::size() <= 1)
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename R>
using tiny_range = typename tiny_range_impl<R>::type;

template <typename R>
using tiny_range_t = tiny_range<R>;

#endif

template <typename V, bool = hamon::ranges::forward_range_t<V>::value>
struct lazy_split_view_base
{
private:
	using Iterator = hamon::ranges::iterator_t<V>;
protected:
	// present only if forward_range<V> is false
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::non_propagating_cache<Iterator> m_current;
};

template <typename V>
struct lazy_split_view_base<V, true>
{
};

}	// namespace detail

// 26.7.16.2 Class template lazy_split_view[range.lazy.split.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V, hamon::ranges::forward_range Pattern>
	requires
		hamon::ranges::view<V> &&
		hamon::ranges::view<Pattern> &&
		hamon::indirectly_comparable<
			hamon::ranges::iterator_t<V>,
			hamon::ranges::iterator_t<Pattern>,
			hamon::ranges::equal_to> &&
		(hamon::ranges::forward_range<V> || hamon::ranges::detail::tiny_range<Pattern>)
#else
template <typename V, typename Pattern,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range_t<V>,
		hamon::ranges::forward_range_t<Pattern>,
		hamon::ranges::view_t<V>,
		hamon::ranges::view_t<Pattern>,
		hamon::indirectly_comparable_t<
			hamon::ranges::iterator_t<V>,
			hamon::ranges::iterator_t<Pattern>,
			hamon::ranges::equal_to>,
		hamon::disjunction<
			hamon::ranges::forward_range_t<V>,
			hamon::ranges::detail::tiny_range_t<Pattern>>
	>::value>>
#endif
class lazy_split_view : public hamon::ranges::view_interface<lazy_split_view<V, Pattern>>
	, private hamon::ranges::detail::lazy_split_view_base<V>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS Pattern m_pattern = Pattern();
//	non_propagating_cache<ranges::iterator_t<V>> m_current;	// present only if forward_range<V> is false

private:
	template <bool Const>
	struct inner_iterator;

	template <typename Base, bool = hamon::ranges::forward_range_t<Base>::value>
	struct outer_iterator_base
	{
	private:
		using Iterator = hamon::ranges::iterator_t<Base>;
	protected:
		HAMON_NO_UNIQUE_ADDRESS Iterator m_current{};
	public:
		using iterator_category = hamon::input_iterator_tag;
		
		outer_iterator_base() = default;
		
		HAMON_CXX11_CONSTEXPR explicit
		outer_iterator_base(Iterator current)
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<Iterator>::value)
			: m_current {hamon::move(current)}
		{}
	};

	template <typename Base>
	struct outer_iterator_base<Base, false>
	{
	};

	// [range.lazy.split.outer], class template lazy_split_view​::​outer-iterator
	template <bool Const, typename Base = hamon::ranges::detail::maybe_const<Const, V>>
	struct outer_iterator
		: public outer_iterator_base<Base>
	{
	private:
		friend inner_iterator<Const>;
		friend outer_iterator<!Const>;

		using Parent = hamon::ranges::detail::maybe_const<Const, lazy_split_view>;

		Parent* m_parent = nullptr;
		//hamon::ranges::iterator_t<Base> m_current{};	// present only if V models forward_range
		bool m_trailing_empty = false;

	private:
		// [range.lazy.split.outer]/1
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR hamon::ranges::iterator_t<Base>&
		get_current_impl(hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
		{
			return this->m_current;
		}

		HAMON_CXX14_CONSTEXPR hamon::ranges::iterator_t<Base>&
		get_current_impl(hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
		{
			return *m_parent->m_current;
		}

		HAMON_CXX14_CONSTEXPR hamon::ranges::iterator_t<Base>&
		get_current() HAMON_NOEXCEPT
		{
			return get_current_impl(hamon::detail::overload_priority<1>{});
		}

		// [range.lazy.split.outer]/1
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX11_CONSTEXPR hamon::ranges::iterator_t<Base> const&
		get_current_impl(hamon::detail::overload_priority<1>) const HAMON_NOEXCEPT
		{
			return this->m_current;
		}

		HAMON_CXX11_CONSTEXPR hamon::ranges::iterator_t<Base> const&
		get_current_impl(hamon::detail::overload_priority<0>) const HAMON_NOEXCEPT
		{
			return *m_parent->m_current;
		}

		HAMON_CXX11_CONSTEXPR hamon::ranges::iterator_t<Base> const&
		get_current() const HAMON_NOEXCEPT
		{
			return get_current_impl(hamon::detail::overload_priority<1>{});
		}

	public:
		using iterator_concept = hamon::conditional_t<
			hamon::ranges::forward_range_t<Base>::value,
			hamon::forward_iterator_tag,
			hamon::input_iterator_tag>;

		//using iterator_category = hamon::input_iterator_tag;	// present only if Base models forward_range

		// [range.lazy.split.outer.value], class lazy_split_view​::​outer-iterator​::​value_type
		struct value_type : public hamon::ranges::view_interface<value_type>
		{
		private:
			HAMON_NO_UNIQUE_ADDRESS outer_iterator m_i = outer_iterator();

		public:
			value_type() = default;

			HAMON_CXX11_CONSTEXPR explicit
			value_type(outer_iterator i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<outer_iterator>::value)
				// [range.lazy.split.outer.value]/1
				: m_i(hamon::move(i))
			{}

			HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
			inner_iterator<Const> begin() const
			{
				// [range.lazy.split.outer.value]/2
				return inner_iterator<Const>{m_i};
			}

			HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
			hamon::default_sentinel_t end() const HAMON_NOEXCEPT
			{
				// [range.lazy.split.outer.value]/3
				return hamon::default_sentinel_t{};
			}
		};

		using difference_type = hamon::ranges::range_difference_t<Base>;

		outer_iterator() = default;

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::not_forward_range, B2, Base)>
		HAMON_CXX11_CONSTEXPR explicit
		outer_iterator(Parent& parent) HAMON_NOEXCEPT	// noexcept as an extension
			// [range.lazy.split.outer]/2
			: m_parent(hamon::addressof(parent))
		{}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX11_CONSTEXPR
		outer_iterator(Parent& parent, hamon::ranges::iterator_t<Base> current)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<Base>>::value)
			// [range.lazy.split.outer]/3
			: outer_iterator_base<Base>(hamon::move(current))
			, m_parent(hamon::addressof(parent))
		{}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::iterator_t<V>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		outer_iterator(outer_iterator<!Const> i)
			// [range.lazy.split.outer]/4
			: outer_iterator_base<Base>(hamon::move(i.m_current))
			, m_parent(i.m_parent)
			, m_trailing_empty(i.m_trailing_empty)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		value_type operator*() const
			HAMON_NOEXCEPT_IF_EXPR(value_type{*this})		// noexcept as an extension
		{
			// [range.lazy.split.outer]/5
			return value_type{*this};
		}

	private:
		template <typename T1, typename T2, typename T3,
			HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::tiny_range, P2, Pattern)>
		HAMON_CXX14_CONSTEXPR
		void pre_increment_impl(
			T1 const& end,
			T2 const& pbegin,
			T3 const& /*pend*/,
			hamon::detail::overload_priority<1>)
		{
			auto& cur = get_current();
			cur = hamon::ranges::find(hamon::move(cur), end, *pbegin);
			if (cur != end)
			{
				++cur;
				if (cur == end)
				{
					m_trailing_empty = true;
				}
			}
		}

		template <typename T1, typename T2, typename T3>
		HAMON_CXX14_CONSTEXPR
		void pre_increment_impl(
			T1 const& end,
			T2 const& pbegin,
			T3 const& pend,
			hamon::detail::overload_priority<0>)
		{
			auto& cur = get_current();
			do
			{
				// 構造化束縛を使うと、VisualStudio 2019で内部コンパイルエラーになる
				//auto [b, p] = hamon::ranges::mismatch(cur, end, pbegin, pend);
				auto res = hamon::ranges::mismatch(cur, end, pbegin, pend);
				auto b = res.in1;
				auto p = res.in2;
				if (p == pend)
				{
					cur = b;
					if (cur == end)
					{
						m_trailing_empty = true;
					}

					break;            // The pattern matched; skip it
				}
			}
			while (++cur != end);
		}

	public:
		HAMON_CXX14_CONSTEXPR outer_iterator&
		operator++()
		{
			// [range.lazy.split.outer]/6

			auto const end = hamon::ranges::end(m_parent->m_base);
			auto& cur = get_current();

			if (cur == end)
			{
				m_trailing_empty = false;
				return *this;
			}

			// 構造化束縛を使うと、VisualStudio 2019で内部コンパイルエラーになる
			//auto const [pbegin, pend] = hamon::ranges::subrange{m_parent->m_pattern};
			auto const pbegin = hamon::ranges::begin(m_parent->m_pattern);
			auto const pend   = hamon::ranges::end(m_parent->m_pattern);

			if (pbegin == pend)
			{
				++cur;
			}
			else
			{
				pre_increment_impl(end, pbegin, pend,
					hamon::detail::overload_priority<1>{});
			}

			return *this;
		}

	private:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR outer_iterator
		post_increment_impl(hamon::detail::overload_priority<1>)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		post_increment_impl(hamon::detail::overload_priority<0>)
		{
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
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(outer_iterator const& x, outer_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current == y.m_current)		// noexcept as an extension
		{
			// [range.lazy.split.outer]/7
			return x.m_current == y.m_current && x.m_trailing_empty == y.m_trailing_empty;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(outer_iterator const& x, outer_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		HAMON_CXX11_CONSTEXPR bool
		at_end() const HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			bool(get_current() == hamon::ranges::end(m_parent->m_base)))
		{
			return get_current() == hamon::ranges::end(m_parent->m_base);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(outer_iterator const& x, hamon::default_sentinel_t)
			HAMON_NOEXCEPT_IF_EXPR(x.at_end())		// noexcept as an extension
		{
			// [range.lazy.split.outer]/8
			return x.at_end() && !x.m_trailing_empty;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(outer_iterator const& x, hamon::default_sentinel_t y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(hamon::default_sentinel_t x, outer_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)		// noexcept as an extension
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(hamon::default_sentinel_t x, outer_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}
#endif
	};

	// [range.lazy.split.inner]/1
	template <typename Base, bool = hamon::ranges::forward_range_t<Base>::value>
	struct inner_iterator_iterator_category
	{
	private:
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseIterCat = typename hamon::iterator_traits<BaseIter>::iterator_category;
	public:
		using iterator_category = hamon::conditional_t<
			hamon::derived_from_t<BaseIterCat, hamon::forward_iterator_tag>::value,
			hamon::forward_iterator_tag,	// [range.lazy.split.inner]/1.1
			BaseIterCat						// [range.lazy.split.inner]/1.2
		>;
	};

	template <typename Base>
	struct inner_iterator_iterator_category<Base, false>
	{
	};

	// [range.lazy.split.inner], class template lazy_split_view​::​inner-iterator
	template <bool Const>
	struct inner_iterator
		: public inner_iterator_iterator_category<hamon::ranges::detail::maybe_const<Const, V>>
	{
	private:
		using Base = hamon::ranges::detail::maybe_const<Const, V>;

		outer_iterator<Const> m_i = outer_iterator<Const>();
		bool m_incremented = false;

	public:
		using iterator_concept  = typename outer_iterator<Const>::iterator_concept;
		//using iterator_category = see below;                    // present only if Base models forward_range
		using value_type        = hamon::ranges::range_value_t<Base>;
		using difference_type   = hamon::ranges::range_difference_t<Base>;

		inner_iterator() = default;

		HAMON_CXX11_CONSTEXPR explicit
		inner_iterator(outer_iterator<Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<outer_iterator<Const>>::value)
			// [range.lazy.split.inner]/2
			: m_i(hamon::move(i))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::iterator_t<Base> const&
		base() const& HAMON_NOEXCEPT
		{
			// [range.lazy.split.inner]/3
			return m_i.get_current();
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V)>
		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::iterator_t<Base>
		base() && HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<Base>>::value)
		{
			// [range.lazy.split.inner]/4
			return hamon::move(m_i.get_current());
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator*() const
		->decltype(*m_i.get_current())
		{
			return *m_i.get_current();
		}

	private:
		// [range.lazy.split.inner]/5
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR void
		pre_increment_impl(hamon::detail::overload_priority<1>)
		{
			++m_i.get_current();
		}

		HAMON_CXX14_CONSTEXPR void
		pre_increment_impl(hamon::detail::overload_priority<0>)
		{
			// TODO
			if /*constexpr*/ (Pattern::size() != 0)
			{
				++m_i.get_current();
			}
		}

	public:
		HAMON_CXX14_CONSTEXPR inner_iterator& operator++()
		{
			// [range.lazy.split.inner]/5
			m_incremented = true;
			pre_increment_impl(hamon::detail::overload_priority<1>{});
			return *this;
		}

	private:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR inner_iterator
		post_increment_impl(hamon::detail::overload_priority<1>)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		post_increment_impl(hamon::detail::overload_priority<0>)
		{
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
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(inner_iterator const& x, inner_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(bool(x.base() == y.base()))		// noexcept as an extension
		{
			// [range.lazy.split.inner]/6
			return x.base() == y.base();
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(inner_iterator const& x, inner_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))		// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		// [range.lazy.split.inner]/7
		template <typename T1, typename T2, typename T3,
			HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::tiny_range, P2, Pattern)>
		HAMON_CXX14_CONSTEXPR bool
		at_end_impl(
			T1 pcur,
			T2 pend,
			T3 end,
			hamon::detail::overload_priority<1>) const
		{
			auto const& cur = m_i.get_current();
			if (cur == end)
			{
				return true;
			}

			if (pcur == pend)
			{
				return m_incremented;
			}

			return *cur == *pcur;
		}

		template <typename T1, typename T2, typename T3>
		HAMON_CXX14_CONSTEXPR bool
		at_end_impl(
			T1 pcur,
			T2 pend,
			T3 end,
			hamon::detail::overload_priority<0>) const
		{
			auto cur = m_i.get_current();
			if (cur == end)
			{
				return true;
			}

			if (pcur == pend)
			{
				return m_incremented;
			}

			do
			{
				if (*cur != *pcur)
				{
					return false;
				}

				if (++pcur == pend)
				{
					return true;
				}
			}
			while (++cur != end);

			return false;
		}

		HAMON_CXX14_CONSTEXPR bool
		at_end() const
		{
			// [range.lazy.split.inner]/7
			return at_end_impl(
				hamon::ranges::begin(m_i.m_parent->m_pattern),
				hamon::ranges::end(m_i.m_parent->m_pattern),
				hamon::ranges::end(m_i.m_parent->m_base),
				hamon::detail::overload_priority<1>{});
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
		operator==(inner_iterator const& x, hamon::default_sentinel_t)
		{
			return x.at_end();
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
		operator!=(inner_iterator const& x, hamon::default_sentinel_t y)
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
		operator==(hamon::default_sentinel_t x, inner_iterator const& y)
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
		operator!=(hamon::default_sentinel_t x, inner_iterator const& y)
		{
			return !(x == y);
		}
#endif

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		iter_move(inner_iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_move(i.base()))
		->decltype(hamon::ranges::iter_move(hamon::declval<hamon::ranges::iterator_t<Base> const&>()))
		{
			return hamon::ranges::iter_move(i.base());
		}

#if !(defined(HAMON_CLANG_VERSION) && defined(HAMON_STDLIB_DINKUMWARE))	// win-clangだと以下のコードがエラーになる
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::indirectly_swappable_t<hamon::ranges::iterator_t<B2>>::value>>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(inner_iterator const& x, inner_iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_swap(x.base(), y.base()))
		{
			// [range.lazy.split.inner]/8
			hamon::ranges::iter_swap(x.base(), y.base());
		}
#endif
#endif
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	lazy_split_view()
		requires
			hamon::default_initializable<V> &&
			hamon::default_initializable<Pattern>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, P2, Pattern)>
	HAMON_CXX11_CONSTEXPR lazy_split_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<V>::value &&
			hamon::is_nothrow_default_constructible<Pattern>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	lazy_split_view(V base, Pattern pattern)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value &&
			hamon::is_nothrow_move_constructible<Pattern>::value)
		// [range.lazy.split.view]/1
		: m_base(hamon::move(base))
		, m_pattern(hamon::move(pattern))
	{}

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::input_range_t<R>,
			hamon::constructible_from_t<V, hamon::views::all_t<R>>,
			hamon::constructible_from_t<Pattern, hamon::ranges::single_view<hamon::ranges::range_value_t<R>>>
		>::value>>
	HAMON_CXX11_CONSTEXPR explicit
	lazy_split_view(R&& r, hamon::ranges::range_value_t<R> e)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(V(hamon::views::all(hamon::forward<R>(r)))) &&
			HAMON_NOEXCEPT_EXPR(Pattern(hamon::views::single(hamon::move(e)))))
		// [range.lazy.split.view]/2
		: m_base(hamon::views::all(hamon::forward<R>(r)))
		, m_pattern(hamon::views::single(hamon::move(e)))
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
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V),
		bool UseConst =
			hamon::ranges::detail::simple_view_t<V>::value &&
			hamon::ranges::detail::simple_view_t<Pattern>::value
	>
	HAMON_CXX14_CONSTEXPR outer_iterator<UseConst>
	begin_impl(hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(
			outer_iterator<UseConst>{*this, hamon::ranges::begin(hamon::declval<V&>())})
	{
		return outer_iterator<UseConst>{*this, hamon::ranges::begin(m_base)};
	}

	HAMON_CXX14_CONSTEXPR outer_iterator<false>
	begin_impl(hamon::detail::overload_priority<0>)
	{
		this->m_current = hamon::ranges::begin(m_base);
		return outer_iterator<false>{*this};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	begin() HAMON_NOEXCEPT_IF_EXPR(				// noexcept as an extension
		begin_impl(hamon::detail::overload_priority<1>{}))
	->decltype(begin_impl(hamon::detail::overload_priority<1>{}))
	{
		return begin_impl(hamon::detail::overload_priority<1>{});
	}

	template <typename V2 = V,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<V2>,
			hamon::ranges::forward_range_t<V2 const>
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	begin() const HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		outer_iterator<true>{*this, hamon::ranges::begin(hamon::declval<V const&>())})
	-> outer_iterator<true>
	{
		return outer_iterator<true>{*this, hamon::ranges::begin(m_base)};
	}

	template <typename V2 = V,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<V2>,
			hamon::ranges::common_range_t<V2>
		>::value>,
		bool UseConst =
			hamon::ranges::detail::simple_view_t<V>::value &&
			hamon::ranges::detail::simple_view_t<Pattern>::value
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	end() HAMON_NOEXCEPT_IF_EXPR(				// noexcept as an extension
		outer_iterator<UseConst>{*this, hamon::ranges::end(hamon::declval<V&>())})
	-> outer_iterator<UseConst>
	{
		return outer_iterator<UseConst>{*this, hamon::ranges::end(m_base)};
	}

private:
	template <typename V2 = V,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<V2>,
			hamon::ranges::forward_range_t<V2 const>,
			hamon::ranges::common_range_t<V2 const>
		>::value>>
	HAMON_CXX11_CONSTEXPR outer_iterator<true>
	end_impl(hamon::detail::overload_priority<1>) const
		HAMON_NOEXCEPT_IF_EXPR(
			outer_iterator<true>{*this, hamon::ranges::end(hamon::declval<V const&>())})
	{
		return outer_iterator<true>{*this, hamon::ranges::end(m_base)};
	}

	HAMON_CXX11_CONSTEXPR hamon::default_sentinel_t
	end_impl(hamon::detail::overload_priority<0>) const HAMON_NOEXCEPT
	{
		return hamon::default_sentinel_t{};
	}

public:
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		end_impl(hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename P>
lazy_split_view(R&&, P&&)
-> lazy_split_view<
	hamon::views::all_t<R>,
	hamon::views::all_t<P>>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
lazy_split_view(R&&, hamon::ranges::range_value_t<R>)
-> lazy_split_view<
	hamon::views::all_t<R>,
	hamon::ranges::single_view<hamon::ranges::range_value_t<R>>>;

#endif

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// extension: deduction guides が使えないときのために追加
template <typename R, typename P>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_lazy_split_view(R&& r, P&& p)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		lazy_split_view<hamon::views::all_t<R>, hamon::views::all_t<P>>(
			hamon::forward<R>(r), hamon::forward<P>(p)))

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_lazy_split_view(R&& r, hamon::ranges::range_value_t<R> v)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		lazy_split_view<
			hamon::views::all_t<R>,
			hamon::ranges::single_view<hamon::ranges::range_value_t<R>>
		>(hamon::forward<R>(r), hamon::move(v)))

namespace views {

namespace detail {

struct lazy_split_fn
{
public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename P>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, P&& p) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::make_lazy_split_view(
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
detail::lazy_split_fn lazy_split{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_LAZY_SPLIT_VIEW_HPP
