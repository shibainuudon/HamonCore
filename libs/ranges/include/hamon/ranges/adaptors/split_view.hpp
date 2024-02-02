/**
 *	@file	split_view.hpp
 *
 *	@brief	split_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_SPLIT_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_SPLIT_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

#define HAMON_USE_STD_RANGES_SPLIT_VIEW

namespace hamon {
namespace ranges {

using std::ranges::split_view;

namespace views {

using std::ranges::views::split;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/detail/non_propagating_cache.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/algorithm/ranges/search.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.17.2 Class template split_view[range.split.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::forward_range V, hamon::ranges::forward_range Pattern>
	requires
		hamon::ranges::view<V> &&
		hamon::ranges::view<Pattern> &&
		hamon::indirectly_comparable<
			hamon::ranges::iterator_t<V>,
			hamon::ranges::iterator_t<Pattern>,
			hamon::ranges::equal_to>
#else
template <typename V, typename Pattern,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::forward_range_t<V>,
		hamon::ranges::forward_range_t<Pattern>,
		hamon::ranges::view_t<V>,
		hamon::ranges::view_t<Pattern>,
		hamon::indirectly_comparable_t<
			hamon::ranges::iterator_t<V>,
			hamon::ranges::iterator_t<Pattern>,
			hamon::ranges::equal_to>
	>::value>>
#endif
class split_view : public hamon::ranges::view_interface<split_view<V, Pattern>>
{
private:
	using BaseIter = hamon::ranges::iterator_t<V>;
	using BaseSent = hamon::ranges::sentinel_t<V>;
	using IterValueType = hamon::ranges::subrange<BaseIter>;

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS Pattern m_pattern = Pattern();
	hamon::ranges::detail::non_propagating_cache<IterValueType> m_cached_next{};

	struct sentinel;

	// [range.split.iterator], class split_view​::​iterator
	struct iterator
	{
	private:
		friend sentinel;

		split_view*   m_parent         = nullptr;
		BaseIter      m_cur            = BaseIter();
		IterValueType m_next           = IterValueType();
		bool          m_trailing_empty = false;

	public:
		using iterator_concept  = hamon::forward_iterator_tag;
		using iterator_category = hamon::input_iterator_tag;
		using value_type        = IterValueType;
		using difference_type   = hamon::ranges::range_difference_t<V>;

		iterator() = default;
		
		HAMON_CXX11_CONSTEXPR
		iterator(split_view& parent, BaseIter current, IterValueType next)
            HAMON_NOEXCEPT_IF(		// noexcept as an extension
				hamon::is_nothrow_move_constructible<BaseIter>::value)
			// [range.split.iterator]/1
			: m_parent(hamon::addressof(parent))
			, m_cur(hamon::move(current))
			, m_next(hamon::move(next))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
		BaseIter base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.split.iterator]/2
			return m_cur;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
		value_type operator*() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.split.iterator]/3
			return {m_cur, m_next.begin()};
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator++()
		{
			// [range.split.iterator]/4
			m_cur = m_next.begin();
			if (m_cur != hamon::ranges::end(m_parent->m_base))
			{
				m_cur = m_next.end();
				if (m_cur == hamon::ranges::end(m_parent->m_base))
				{
					m_trailing_empty = true;
					m_next = {m_cur, m_cur};
				}
				else
				{
					m_next = m_parent->find_next(m_cur);
				}
			}
			else
			{
				m_trailing_empty = false;
			}

			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator
		operator++(int)
		{
			// [range.split.iterator]/5
			auto tmp = *this;
			++*this;
			return tmp;
		}

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_cur == y.m_cur)		// noexcept as an extension
		{
			// [range.split.iterator]/6
			return x.m_cur == y.m_cur && x.m_trailing_empty == y.m_trailing_empty;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))				// noexcept as an extension
		{
			return !(x == y);
		}
#endif
	};

	// [range.split.sentinel], class split_view​::​sentinel
	struct sentinel
	{
	private:
		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end = BaseSent();

	public:
		sentinel() = default;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(split_view& parent)
			HAMON_NOEXCEPT_IF(		// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::ranges::end(parent.m_base)) &&
				hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.split.sentinel]/1
			: m_end(hamon::ranges::end(parent.m_base))
		{}

	private:
		HAMON_CXX11_CONSTEXPR bool
		equal(iterator const& x) const
			HAMON_NOEXCEPT_IF_EXPR(x.m_cur == this->m_end)	// noexcept as an extension
		{
			// [range.split.sentinel]/2
			return x.m_cur == this->m_end && !x.m_trailing_empty;
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

	HAMON_CXX14_CONSTEXPR IterValueType
	find_next(BaseIter it)
	{
		// [range.split.view]/5
		
		auto last = hamon::ranges::end(m_base);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		auto sr = hamon::ranges::subrange(it, last);
#else
		auto sr = hamon::ranges::subrange<BaseIter, BaseSent>(it, last);
#endif

		// 構造化束縛を使うと、VisualStudio 2019で内部コンパイルエラーになる
		//auto [b, e] = hamon::ranges::search(sr, m_pattern);
		auto res = hamon::ranges::search(sr, m_pattern);
		auto b = res.begin();
		auto e = res.end();

		if (b != last && hamon::ranges::empty(m_pattern))
		{
			++b;
			++e;
		}

		return {b, e};
	}

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	split_view()
		requires
			hamon::default_initializable<V> &&
			hamon::default_initializable<Pattern>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, P2, Pattern)>
	HAMON_CXX11_CONSTEXPR split_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<V>::value &&
			hamon::is_nothrow_default_constructible<Pattern>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	split_view(V base, Pattern pattern)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value &&
			hamon::is_nothrow_move_constructible<Pattern>::value)
		// [range.split.view]/1
		: m_base(hamon::move(base))
		, m_pattern(hamon::move(pattern))
	{}

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::forward_range_t<R>,
			hamon::constructible_from_t<V, hamon::views::all_t<R>>,
			hamon::constructible_from_t<Pattern, hamon::ranges::single_view<hamon::ranges::range_value_t<R>>>
		>::value>>
	HAMON_CXX11_CONSTEXPR explicit
	split_view(R&& r, hamon::ranges::range_value_t<R> e)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<V, hamon::views::all_t<R>>::value &&
			hamon::is_nothrow_constructible<Pattern, hamon::ranges::single_view<hamon::ranges::range_value_t<R>>>::value &&
			hamon::is_nothrow_move_constructible<hamon::ranges::range_value_t<R>>::value)
		// [range.split.view]/2
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

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin()
	{
		auto first = hamon::ranges::begin(m_base);

		// [range.split.view]/4
		if (!m_cached_next.has_value())
		{
			m_cached_next.emplace(find_next(first));
		}

		// [range.split.view]/3
		return {*this, first, *m_cached_next};
	}

private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator
	end_impl(hamon::detail::overload_priority<1>)
	{
		return iterator{*this, hamon::ranges::end(m_base), {}};
	}

	HAMON_CXX14_CONSTEXPR sentinel
	end_impl(hamon::detail::overload_priority<0>)
	{
		return sentinel{*this};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end()
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename P>
split_view(R&&, P&&)
-> split_view<
	hamon::views::all_t<R>,
	hamon::views::all_t<P>>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, R)>
split_view(R&&, hamon::ranges::range_value_t<R>)
-> split_view<
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
make_split_view(R&& r, P&& p)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		split_view<hamon::views::all_t<R>, hamon::views::all_t<P>>(
			hamon::forward<R>(r), hamon::forward<P>(p)))

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, R)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_split_view(R&& r, hamon::ranges::range_value_t<R> v)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		split_view<
			hamon::views::all_t<R>,
			hamon::ranges::single_view<hamon::ranges::range_value_t<R>>
		>(hamon::forward<R>(r), hamon::move(v)))

namespace views {

namespace detail {

struct split_fn
{
public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename P>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, P&& p) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::make_split_view(
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
detail::split_fn split{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_SPLIT_VIEW_HPP
