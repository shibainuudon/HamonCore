/**
 *	@file	chunk_by_view.hpp
 *
 *	@brief	chunk_by_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_CHUNK_BY_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_CHUNK_BY_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_chunk_by) && (__cpp_lib_ranges_chunk_by >= 202202L)

namespace hamon {
namespace ranges {

using std::ranges::chunk_by_view;

namespace views {

using std::ranges::views::chunk_by;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/detail/cached_value.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/algorithm/ranges/adjacent_find.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/not_fn.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_object.hpp>
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

// 26.7.30.2 Class template chunk_by_view[range.chunk.by.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <
	hamon::ranges::forward_range V,
	hamon::indirect_binary_predicate<hamon::ranges::iterator_t<V>, hamon::ranges::iterator_t<V>> Pred>
	requires hamon::ranges::view<V> && hamon::is_object_v<Pred>
#else
template <typename V, typename Pred,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::forward_range_t<V>,
		hamon::indirect_binary_predicate_t<Pred, hamon::ranges::iterator_t<V>, hamon::ranges::iterator_t<V>>,
		hamon::ranges::view_t<V>,
		hamon::is_object<Pred>
	>::value>
>
#endif
class chunk_by_view : public hamon::ranges::view_interface<chunk_by_view<V, Pred>>
{
private:
	using BaseIter = hamon::ranges::iterator_t<V>;
	using CacheType = hamon::ranges::detail::cached_value<true, BaseIter>;

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::movable_box<Pred> m_pred;
	HAMON_NO_UNIQUE_ADDRESS CacheType m_cache;

private:
	// [range.chunk.by.iter], class chunk_by_view​::​iterator
	class iterator
	{
	private:
		friend chunk_by_view;

	private:
		chunk_by_view* m_parent = nullptr;
		HAMON_NO_UNIQUE_ADDRESS BaseIter m_current{};
		HAMON_NO_UNIQUE_ADDRESS BaseIter m_next{};

	private:
		HAMON_CXX11_CONSTEXPR
		iterator(chunk_by_view& parent, BaseIter current, BaseIter next)
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<BaseIter>::value)	// noexcept as an extension
			// [range.chunk.by.iter]/2
			: m_parent(hamon::addressof(parent))
			, m_current(hamon::move(current))
			, m_next(hamon::move(next))
		{}

	public:
		using value_type = hamon::ranges::subrange<BaseIter>;
		using difference_type  = hamon::ranges::range_difference_t<V>;
		using iterator_category = hamon::input_iterator_tag;
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<V>::value,
				hamon::bidirectional_iterator_tag,	// [range.chunk.by.iter]/1.1
				hamon::forward_iterator_tag			// [range.chunk.by.iter]/1.2
			>;

		iterator() = default;

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
		value_type operator*() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
#if HAMON_CXX_STANDARD >= 14
			// [range.chunk.by.iter]/3
			HAMON_ASSERT(m_current != m_next);
#endif

			// [range.chunk.by.iter]/4
			return hamon::ranges::make_subrange(m_current, m_next);
		}

		HAMON_CXX14_CONSTEXPR iterator& operator++()
		{
			// [range.chunk.by.iter]/5
			HAMON_ASSERT(m_current != m_next);

			// [range.chunk.by.iter]/6
			m_current = m_next;
			m_next = m_parent->find_next(m_current);
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator operator++(int)
		{
			// [range.chunk.by.iter]/7
			auto tmp = *this;
			++*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, V2, V)>
		HAMON_CXX14_CONSTEXPR iterator& operator--()
		{
			// [range.chunk.by.iter]/8
			m_next = m_current;
			m_current = m_parent->find_prev(m_next);
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, V2, V)>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
		{
			// [range.chunk.by.iter]/9
			auto tmp = *this;
			--*this;
			return tmp;
		}

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			// [range.chunk.by.iter]/10
			HAMON_NOEXCEPT_RETURN(x.m_current == y.m_current)	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, hamon::default_sentinel_t)
			// [range.chunk.by.iter]/11
			HAMON_NOEXCEPT_RETURN(x.m_current == x.m_next)	// noexcept as an extension

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
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	chunk_by_view()
		requires hamon::default_initializable<V> && hamon::default_initializable<Pred>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, P2, Pred)
	>
	HAMON_CXX11_CONSTEXPR
	chunk_by_view() HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_default_constructible<V>::value &&
		hamon::is_nothrow_default_constructible<Pred>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	chunk_by_view(V base, Pred pred) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value &&
		hamon::is_nothrow_move_constructible<Pred>::value)
		// [range.chunk.by.view]/1
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
		// [range.chunk.by.view]/2
		return *m_pred;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin()
	{
		// [range.chunk.by.view]/3
		HAMON_ASSERT(m_pred.has_value());

		// [range.chunk.by.view]/5
		auto first = hamon::ranges::begin(m_base);
		if (m_cache.has_value())
		{
			return iterator(*this, hamon::move(first), m_cache.value());
		}

		auto next = find_next(first);
		m_cache = next;

		// [range.chunk.by.view]/4
		return iterator(*this, hamon::move(first), hamon::move(next));
	}

private:
	// [range.chunk.by.view]/6
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator
	end_impl(hamon::detail::overload_priority<1>)
	{
		return iterator(*this, hamon::ranges::end(m_base), hamon::ranges::end(m_base));
	}

	HAMON_CXX14_CONSTEXPR hamon::default_sentinel_t
	end_impl(hamon::detail::overload_priority<0>) HAMON_NOEXCEPT	// noexcept as an extension
	{
		return hamon::default_sentinel;
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		end_impl(hamon::detail::overload_priority<1>{}))

private:
	HAMON_CXX14_CONSTEXPR BaseIter
	find_next(BaseIter current)
	{
		// [range.chunk.by.view]/7
		HAMON_ASSERT(m_pred.has_value());

		auto last = hamon::ranges::end(m_base);

		// [range.chunk.by.view]/8
		auto it = hamon::ranges::adjacent_find(
			current,
			last,
			hamon::not_fn(hamon::ref(*m_pred)));
		return hamon::ranges::next(it, 1, hamon::move(last));
	}

	struct BindReverse
	{
		Pred& pred;

		template <typename T>
		HAMON_CXX11_CONSTEXPR auto operator()(T&& lhs, T&& rhs) const
			HAMON_NOEXCEPT_DECLTYPE_RETURN(
				hamon::invoke(pred, hamon::forward<T>(rhs), hamon::forward<T>(lhs)))
	};

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, V2, V)>
	HAMON_CXX14_CONSTEXPR BaseIter
	find_prev(BaseIter current)
	{
		// [range.chunk.by.view]/9.2
		HAMON_ASSERT(m_pred.has_value());

		// [range.chunk.by.view]/9.1
		auto first = hamon::ranges::begin(m_base);
		HAMON_ASSERT(current != first);

		//using namespace std::placeholders;

		// [range.chunk.by.view]/10
		auto it = hamon::ranges::adjacent_find(
			hamon::make_reverse_iterator(current),
			hamon::make_reverse_iterator(first),
			//hamon::not_fn(std::bind(hamon::ref(*m_pred), _2, _1))	// TODO hamon::bind を実装してconstexpr対応したらこう書きたい
			hamon::not_fn(BindReverse{*m_pred})
		).base();
		return hamon::ranges::prev(it, 1, hamon::move(first));
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename Pred>
chunk_by_view(R&&, Pred) -> chunk_by_view<hamon::views::all_t<R>, Pred>;

#endif

namespace views {

namespace detail {

struct chunk_by_fn
{
public:
	// [range.chunk_by.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename Pred>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, Pred pred) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::chunk_by_view<hamon::views::all_t<R>, Pred>(
				hamon::forward<R>(r), hamon::move(pred)))

	template <typename Pred,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<Pred>, Pred>::value>>
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
detail::chunk_by_fn chunk_by{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN
#undef HAMON_NOEXCEPT_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_CHUNK_BY_VIEW_HPP
