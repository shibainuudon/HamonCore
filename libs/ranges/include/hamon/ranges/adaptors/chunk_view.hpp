/**
 *	@file	chunk_view.hpp
 *
 *	@brief	chunk_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_CHUNK_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_CHUNK_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_chunk) && (__cpp_lib_ranges_chunk >= 202202L)

#include <hamon/cstddef/size_t.hpp>

namespace hamon {
namespace ranges {

using std::ranges::chunk_view;

namespace views {

using std::ranges::views::chunk;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/take_view.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/detail/non_propagating_cache.hpp>
#include <hamon/ranges/adaptors/detail/div_ceil.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/algorithm/ranges/min.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

#define HAMON_NOEXCEPT_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {

// 26.7.28.2 Class template chunk_view for input ranges[range.chunk.view.input]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires hamon::ranges::input_range<V>
class chunk_view
#else
template <typename V,
	typename = hamon::ranges::forward_range_t<V>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view_t<V>,
		hamon::ranges::input_range_t<V>
	>::value>>
class chunk_view;

template <typename V>
class chunk_view<V, hamon::false_type>
#endif
	: public hamon::ranges::view_interface<chunk_view<V>>
{
private:
	using UnsignedDifference =
		decltype(hamon::ranges::detail::to_unsigned_like(
			hamon::declval<hamon::ranges::range_difference_t<V>>()));

private:
	HAMON_NO_UNIQUE_ADDRESS V m_base;
	hamon::ranges::range_difference_t<V> m_n;
	hamon::ranges::range_difference_t<V> m_remainder = 0;
	hamon::ranges::detail::non_propagating_cache<hamon::ranges::iterator_t<V>> m_current;

private:
	class inner_iterator;

	// [range.chunk.outer.iter], class chunk_view​::​outer_iterator
	class outer_iterator
	{
	private:
		friend chunk_view;

	private:
		chunk_view* m_parent;

	private:
		HAMON_CXX11_CONSTEXPR explicit
		outer_iterator(chunk_view& parent) HAMON_NOEXCEPT	// noexcept as an extension
			// [range.chunk.outer.iter]/1
			: m_parent(hamon::addressof(parent))
		{}

	public:
		using iterator_concept = hamon::input_iterator_tag;
		using difference_type  = hamon::ranges::range_difference_t<V>;

		// [range.chunk.outer.value], class chunk_view​::​outer_iterator​::​value_type
		struct value_type : public hamon::ranges::view_interface<value_type>
		{
		private:
			friend outer_iterator;

		private:
			chunk_view* m_parent;

		private:
			HAMON_CXX11_CONSTEXPR explicit
			value_type(chunk_view& parent) HAMON_NOEXCEPT	// noexcept as an extension
				// [range.chunk.outer.value]/1
				: m_parent(hamon::addressof(parent))
			{}

		public:
			HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
			inner_iterator begin() const HAMON_NOEXCEPT
			{
				// [range.chunk.outer.value]/2
				return inner_iterator(*m_parent);
			}

			HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
			hamon::default_sentinel_t end() const HAMON_NOEXCEPT
			{
				// [range.chunk.outer.value]/3
				return hamon::default_sentinel;
			}

			template <typename V2 = V,
				typename = hamon::enable_if_t<
					hamon::sized_sentinel_for_t<
						hamon::ranges::sentinel_t<V2>,
						hamon::ranges::iterator_t<V2>
					>::value>>
			HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
			UnsignedDifference size() const
				HAMON_NOEXCEPT_IF_EXPR(				// noexcept as an extension
					hamon::ranges::end(m_parent->m_base) - *m_parent->m_current)
			{
				// [range.chunk.outer.value]/4
				return hamon::ranges::detail::to_unsigned_like(
					hamon::ranges::min(m_parent->m_remainder,
						hamon::ranges::end(m_parent->m_base) - *m_parent->m_current));
			}
		};

		outer_iterator(outer_iterator&&) = default;
		outer_iterator& operator=(outer_iterator&&) = default;

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		value_type operator*() const HAMON_NOEXCEPT	// noexcept as an extension
		{
#if HAMON_CXX_STANDARD >= 14
			// [range.chunk.outer.iter]/2
			HAMON_ASSERT(*this != hamon::default_sentinel);
#endif
			// [range.chunk.outer.iter]/3
			return value_type(*m_parent);
		}

		HAMON_CXX14_CONSTEXPR outer_iterator& operator++()	// noexcept(false)
		{
			// [range.chunk.outer.iter]/4
			HAMON_ASSERT(*this != hamon::default_sentinel);

			// [range.chunk.outer.iter]/5
			hamon::ranges::advance(*m_parent->m_current, m_parent->m_remainder, hamon::ranges::end(m_parent->m_base));
			m_parent->m_remainder = m_parent->m_n;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR void operator++(int)	// noexcept(false)
		{
			// [range.chunk.outer.iter]/6
			++*this;
		}

	private:
		HAMON_CXX11_CONSTEXPR bool equal_impl() const
			// [range.chunk.outer.iter]/7
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				*m_parent->m_current == hamon::ranges::end(m_parent->m_base) &&
				m_parent->m_remainder != 0)

		template <typename D>
		HAMON_CXX11_CONSTEXPR difference_type
		distance_impl2(D dist) const HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.chunk.outer.iter]/8
			return (dist < m_parent->m_remainder) ?
				(dist == 0 ? 0 : 1) :
				(hamon::ranges::detail::div_ceil(dist - m_parent->m_remainder, m_parent->m_n) + 1);
		}

		HAMON_CXX11_CONSTEXPR difference_type distance_impl() const
			// [range.chunk.outer.iter]/8
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				distance_impl2(hamon::ranges::end(m_parent->m_base) - *m_parent->m_current))

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(outer_iterator const& x, hamon::default_sentinel_t)
			HAMON_NOEXCEPT_RETURN(x.equal_impl())		// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(outer_iterator const& x, hamon::default_sentinel_t y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(hamon::default_sentinel_t x, outer_iterator const& y)
			HAMON_NOEXCEPT_RETURN(y == x)				// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(hamon::default_sentinel_t x, outer_iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<V2>,
					hamon::ranges::iterator_t<V2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(hamon::default_sentinel_t, outer_iterator const& x)
			HAMON_NOEXCEPT_RETURN(x.distance_impl())	// noexcept as an extension

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<V2>,
					hamon::ranges::iterator_t<V2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(outer_iterator const& x, hamon::default_sentinel_t y)
			// [range.chunk.outer.iter]/9
			HAMON_NOEXCEPT_RETURN(-(y - x))				// noexcept as an extension
	};

	// [range.chunk.inner.iter], class chunk_view​::​inner_iterator
	class inner_iterator
	{
	private:
		friend chunk_view;

	private:
		chunk_view* m_parent;

	private:
		HAMON_CXX11_CONSTEXPR explicit
		inner_iterator(chunk_view& parent) HAMON_NOEXCEPT
			// [range.chunk.inner.iter]/1
			: m_parent(hamon::addressof(parent))
		{}

	public:
		using iterator_concept = hamon::input_iterator_tag;
		using difference_type = hamon::ranges::range_difference_t<V>;
		using value_type = hamon::ranges::range_value_t<V>;

		inner_iterator(inner_iterator&&) = default;
		inner_iterator& operator=(inner_iterator&&) = default;

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::iterator_t<V> const& base() const&
			// [range.chunk.inner.iter]/2
			HAMON_NOEXCEPT_RETURN(*m_parent->m_current)	// noexcept as an extension

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_reference_t<V> operator*() const
			HAMON_NOEXCEPT_IF_EXPR(**m_parent->m_current)	// noexcept as an extension
		{
#if HAMON_CXX_STANDARD >= 14
			// [range.chunk.inner.iter]/3
			HAMON_ASSERT(*this != hamon::default_sentinel);
#endif

			// [range.chunk.inner.iter]/4
			return **m_parent->m_current;
		}

		HAMON_CXX14_CONSTEXPR inner_iterator& operator++()
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(++*m_parent->m_current) &&
				HAMON_NOEXCEPT_EXPR(static_cast<bool>(*m_parent->m_current == hamon::ranges::end(m_parent->m_base))))
		{
			// [range.chunk.inner.iter]/5
			HAMON_ASSERT(*this != hamon::default_sentinel);

			// [range.chunk.inner.iter]/6
			++*m_parent->m_current;
			if (*m_parent->m_current == hamon::ranges::end(m_parent->m_base))
			{
				m_parent->m_remainder = 0;
			}
			else
			{
				--m_parent->m_remainder;
			}
			return *this;
		}

		HAMON_CXX14_CONSTEXPR void operator++(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(++*m_parent->m_current) &&
				HAMON_NOEXCEPT_EXPR(static_cast<bool>(*m_parent->m_current == hamon::ranges::end(m_parent->m_base))))
		{
			// [range.chunk.inner.iter]/7
			++*this;
		}

	private:
		HAMON_CXX11_CONSTEXPR
		bool equal_impl() const HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.chunk.inner.iter]/8
			return m_parent->m_remainder == 0;
		}

		HAMON_CXX11_CONSTEXPR difference_type
		distance_impl() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::ranges::end(m_parent->m_base) - *m_parent->m_current)
		{
			// [range.chunk.inner.iter]/9
			return hamon::ranges::min(
				m_parent->m_remainder,
				hamon::ranges::end(m_parent->m_base) - *m_parent->m_current);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(inner_iterator const& x, hamon::default_sentinel_t)
			HAMON_NOEXCEPT_RETURN(x.equal_impl())		// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(inner_iterator const& x, hamon::default_sentinel_t y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(hamon::default_sentinel_t x, inner_iterator const& y)
			HAMON_NOEXCEPT_RETURN(y == x)				// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(hamon::default_sentinel_t x, inner_iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<V2>,
					hamon::ranges::iterator_t<V2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(hamon::default_sentinel_t, inner_iterator const& x)
			HAMON_NOEXCEPT_RETURN(x.distance_impl())	// noexcept as an extension

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<V2>,
					hamon::ranges::iterator_t<V2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(inner_iterator const& x, hamon::default_sentinel_t y)
			// [range.chunk.inner.iter]/10
			HAMON_NOEXCEPT_RETURN(-(y - x))				// noexcept as an extension

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		HAMON_CXX11_CONSTEXPR hamon::ranges::range_rvalue_reference_t<V>
		iter_move_impl() const
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_move(*m_parent->m_current))
		{
			// [range.chunk.inner.iter]/11
			return hamon::ranges::iter_move(*m_parent->m_current);
		}

		HAMON_CXX14_CONSTEXPR void
		iter_swap_impl(inner_iterator const& y) const
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_swap(*m_parent->m_current, *y.m_parent->m_current))
		{
			// [range.chunk.inner.iter]/12
			hamon::ranges::iter_swap(*m_parent->m_current, *y.m_parent->m_current);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_rvalue_reference_t<V>
		iter_move(inner_iterator const& i)
			HAMON_NOEXCEPT_RETURN(i.iter_move_impl())

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::indirectly_swappable_t<
					hamon::ranges::iterator_t<V2>
				>::value>>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(inner_iterator const& x, inner_iterator const& y)
			HAMON_NOEXCEPT_RETURN(x.iter_swap_impl(y))
#endif
	};

public:
	HAMON_CXX11_CONSTEXPR explicit
	chunk_view(V base, hamon::ranges::range_difference_t<V> n)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<V>::value)	// noexcept as an extension
		// [range.chunk.view.input]/2
		: m_base(hamon::move(base))
		, m_n(n)
	{
#if HAMON_CXX_STANDARD >= 14
		// [range.chunk.view.input]/1
		HAMON_ASSERT(n > 0);
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

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	outer_iterator begin()
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::begin(m_base))	// noexcept as an extension
	{
		// [range.chunk.view.input]/3
		m_current = hamon::ranges::begin(m_base);
		m_remainder = m_n;
		return outer_iterator(*this);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::default_sentinel_t end() const HAMON_NOEXCEPT
	{
		// [range.chunk.view.input]/4
		return hamon::default_sentinel;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	UnsignedDifference size()
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::distance(m_base))	// noexcept as an extension
	{
		// [range.chunk.view.input]/5
		return hamon::ranges::detail::to_unsigned_like(
			hamon::ranges::detail::div_ceil(hamon::ranges::distance(m_base), m_n));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	UnsignedDifference size() const
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::distance(m_base))	// noexcept as an extension
	{
		// [range.chunk.view.input]/5
		return hamon::ranges::detail::to_unsigned_like(
			hamon::ranges::detail::div_ceil(hamon::ranges::distance(m_base), m_n));
	}
};

// 26.7.28.6 Class template chunk_view for forward ranges[range.chunk.view.fwd]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires hamon::ranges::forward_range<V>
class chunk_view<V>
#else
template <typename V>
class chunk_view<V, hamon::true_type>
#endif
	: public hamon::ranges::view_interface<chunk_view<V>>
{
private:
	using UnsignedDifference =
		decltype(hamon::ranges::detail::to_unsigned_like(
			hamon::declval<hamon::ranges::range_difference_t<V>>()));

private:
	HAMON_NO_UNIQUE_ADDRESS V m_base;
	hamon::ranges::range_difference_t<V> m_n;

private:
	// [range.chunk.fwd.iter], class template chunk_view​::​iterator
	template <bool Const>
	class iterator
	{
	private:
		friend chunk_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, chunk_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;
		using BaseDifference = hamon::ranges::range_difference_t<Base>;

	private:
		HAMON_NO_UNIQUE_ADDRESS BaseIter m_current{};
		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end{};
		BaseDifference m_n = 0;
		BaseDifference m_missing = 0;

	private:
		HAMON_CXX11_CONSTEXPR
		iterator(Parent* parent, BaseIter current, BaseDifference missing = 0)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::ranges::end(parent->m_base)) &&
				hamon::is_nothrow_move_constructible<BaseIter>::value &&
				hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.chunk.fwd.iter]/2
			: m_current(hamon::move(current))
			, m_end(hamon::ranges::end(parent->m_base))
			, m_n(parent->m_n)
			, m_missing(missing)
		{}

	public:
		using iterator_category = hamon::input_iterator_tag;
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,
				hamon::forward_iterator_tag
			>>;
		using value_type = decltype(hamon::views::take(hamon::ranges::make_subrange(m_current, m_end), m_n));
		using difference_type = BaseDifference;

		iterator() = default;

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<V2>, BaseIter>::value &&
				hamon::convertible_to_t<hamon::ranges::sentinel_t<V2>, BaseSent>::value
			>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_constructible<BaseIter, hamon::ranges::iterator_t<V2>>::value &&
				hamon::is_nothrow_constructible<BaseSent, hamon::ranges::sentinel_t<V2>>::value)
			// [range.chunk.fwd.iter]/3
			: m_current(hamon::move(i.m_current))
			, m_end(hamon::move(i.m_end))
			, m_n(i.m_n)
			, m_missing(i.m_missing)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseIter base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.chunk.fwd.iter]/4
			return m_current;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		value_type operator*() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::views::take(hamon::ranges::make_subrange(m_current, m_end), m_n))
		{
#if HAMON_CXX_STANDARD >= 14
			// [range.chunk.fwd.iter]/5
			HAMON_ASSERT(m_current != m_end);
#endif

			// [range.chunk.fwd.iter]/6
			return hamon::views::take(hamon::ranges::make_subrange(m_current, m_end), m_n);
		}

		HAMON_CXX14_CONSTEXPR iterator& operator++()	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/7
			HAMON_ASSERT(m_current != m_end);

			// [range.chunk.fwd.iter]/8
			m_missing = hamon::ranges::advance(m_current, m_n, m_end);
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator operator++(int)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/9
			auto tmp = *this;
			++*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator--()	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/10
			hamon::ranges::advance(m_current, m_missing - m_n);
			m_missing = 0;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/11
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator+=(difference_type x)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/13
			if (x > 0)
			{
				// [range.chunk.fwd.iter]/12
				HAMON_ASSERT(hamon::ranges::distance(m_current, m_end) > m_n * (x - 1));

				hamon::ranges::advance(m_current, m_n * (x - 1));
				m_missing = hamon::ranges::advance(m_current, m_n, m_end);
			}
			else if (x < 0)
			{
				hamon::ranges::advance(m_current, m_n * x + m_missing);
				m_missing = 0;
			}
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator-=(difference_type x)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/14
			return *this += -x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX11_CONSTEXPR value_type operator[](difference_type n) const
			// [range.chunk.fwd.iter]/15
			HAMON_NOEXCEPT_RETURN(*(*this + n))	// noexcept as an extension

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			// [range.chunk.fwd.iter]/16
			HAMON_NOEXCEPT_RETURN(x.m_current == y.m_current)	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, hamon::default_sentinel_t)
			// [range.chunk.fwd.iter]/17
			HAMON_NOEXCEPT_RETURN(x.m_current == x.m_end)	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, hamon::default_sentinel_t y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(hamon::default_sentinel_t x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(y == x)				// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(hamon::default_sentinel_t x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
			// [range.chunk.fwd.iter]/18
			HAMON_NOEXCEPT_RETURN(x.m_current < y.m_current)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			// [range.chunk.fwd.iter]/19
			HAMON_NOEXCEPT_RETURN(y < x)				// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			// [range.chunk.fwd.iter]/20
			HAMON_NOEXCEPT_RETURN(!(y < x))				// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			// [range.chunk.fwd.iter]/21
			HAMON_NOEXCEPT_RETURN(!(x < y))				// noexcept as an extension

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current <=> y.m_current)	// noexcept as an extension
			requires hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<BaseIter>
		{
			// [range.chunk.fwd.iter]/22
			return x.m_current <=> y.m_current;
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& i, difference_type n)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/23
			auto r = i;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator const& i)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/23
			auto r = i;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& i, difference_type n)	// noexcept(false)
		{
			// [range.chunk.fwd.iter]/24
			auto r = i;
			r -= n;
			return r;
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::iterator_t<B2>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current - y.m_current)	// noexcept as an extension
		{
			// [range.chunk.fwd.iter]/25
			return (x.m_current - y.m_current + x.m_missing - y.m_missing) / x.m_n;
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<B2>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(hamon::default_sentinel_t, iterator const& x)
			HAMON_NOEXCEPT_IF_EXPR(x.m_end - x.m_current)	// noexcept as an extension
		{
			// [range.chunk.fwd.iter]/26
			return hamon::ranges::detail::div_ceil(x.m_end - x.m_current, x.m_n);
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<B2>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, hamon::default_sentinel_t y)
			// [range.chunk.fwd.iter]/27
			HAMON_NOEXCEPT_RETURN(-(y - x))				// noexcept as an extension
	};

public:
	HAMON_CXX11_CONSTEXPR explicit
	chunk_view(V base, hamon::ranges::range_difference_t<V> n)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<V>::value)	// noexcept as an extension
		// [range.chunk.view.fwd]/2
		: m_base(hamon::move(base))
		, m_n(n)
	{
#if HAMON_CXX_STANDARD >= 14
		// [range.chunk.view.fwd]/1
		HAMON_ASSERT(n > 0);
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

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	iterator<false> begin() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<false>(this, hamon::ranges::begin(m_base));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<true>(this, hamon::ranges::begin(m_base));
	}

private:
	template <typename This, typename V2, typename D,
		bool Const = hamon::is_const<V2>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::common_range_t<V2>::value &&
			hamon::ranges::sized_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(This* this_, V2& base, D const& n, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::ranges::distance(base)) &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(base)) &&
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<Const>(this_,
			hamon::ranges::end(base),
			(n - hamon::ranges::distance(base) % n) % n);
	}

	template <typename This, typename V2, typename D,
		bool Const = hamon::is_const<V2>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::common_range_t<V2>::value &&
			!hamon::ranges::bidirectional_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(This* this_, V2& base, D const&, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(base)) &&
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<Const>(this_, hamon::ranges::end(base));
	}

	template <typename This, typename V2, typename D>
	static HAMON_CXX11_CONSTEXPR hamon::default_sentinel_t
	end_impl(This*, V2&, D const&, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		return hamon::default_sentinel;
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	end() HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		end_impl(this, m_base, m_n, hamon::detail::overload_priority<2>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		end_impl(this, m_base, m_n, hamon::detail::overload_priority<2>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	UnsignedDifference size()
		// [range.chunk.view.fwd]/3
		HAMON_NOEXCEPT_RETURN(hamon::ranges::detail::to_unsigned_like(	// noexcept as an extension
			hamon::ranges::detail::div_ceil(hamon::ranges::distance(m_base), m_n)))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	UnsignedDifference size() const
		// [range.chunk.view.fwd]/3
		HAMON_NOEXCEPT_RETURN(hamon::ranges::detail::to_unsigned_like(	// noexcept as an extension
			hamon::ranges::detail::div_ceil(hamon::ranges::distance(m_base), m_n)))
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
chunk_view(R&&, hamon::ranges::range_difference_t<R>) -> chunk_view<hamon::views::all_t<R>>;

#endif

// enable_borrowed_range の特殊化
template <typename V>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	hamon::ranges::forward_range_t<V>::value && HAMON_RANGES_ENABLE_BORROWED_RANGE(V),
	hamon::ranges::chunk_view<V>);

namespace views {

namespace detail {

// 26.7.28.1 Overview[range.chunk.overview]

struct chunk_fn
{
public:
	// [range.chunk.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, hamon::ranges::range_difference_t<R> n) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::chunk_view<hamon::views::all_t<R>>(hamon::forward<R>(r), n))

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<T>, T>::value>>
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
detail::chunk_fn chunk{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN
#undef HAMON_NOEXCEPT_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_chunk_VIEW_HPP
