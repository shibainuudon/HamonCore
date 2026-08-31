/**
 *	@file	cache_latest_view.hpp
 *
 *	@brief	cache_latest_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_CACHE_LATEST_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_CACHE_LATEST_VIEW_HPP

#include <hamon/ranges/fwd.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/as_lvalue.hpp>
#include <hamon/ranges/adaptors/detail/non_propagating_cache.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/reserve_hint.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 古いバージョンのclangにおいて、iter_swapの再定義エラーになる場合があるので
// inline namespace で囲む。
inline namespace cache_latest_view_ns
{

// 25.7.34.2 Class template cache_latest_view[range.cache.latest.ranges::view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <ranges::input_range V>
	requires ranges::view<V>
#else
template <typename V,
	typename = hamon::enable_if_t<
		hamon::ranges::input_range<V> &&
		hamon::ranges::view<V>
	>>
#endif
class cache_latest_view : public ranges::view_interface<cache_latest_view<V>>
{
private:
	V base_ = V();

	using cache_t = hamon::conditional_t<
		hamon::is_reference_v<ranges::range_reference_t<V>>,
			hamon::add_pointer_t<ranges::range_reference_t<V>>,
			ranges::range_reference_t<V>>;

	ranges::detail::non_propagating_cache<cache_t> cache_;

	// 25.7.34.3 Class cache_latest_view::iterator[range.cache.latest.iterator]
	class iterator
	{
	private:
		friend cache_latest_view;

#if defined(HAMON_MSVC) || \
	(defined(HAMON_GCC_VERSION) && HAMON_GCC_VERSION < 130000)
	public:
#else
	private:
#endif
		cache_latest_view* parent_;
		ranges::iterator_t<V> current_;

		HAMON_CXX11_CONSTEXPR explicit
		iterator(cache_latest_view& parent)
			// [range.cache.latest.iterator]/1
			: parent_(hamon::addressof(parent))
			, current_(ranges::begin(parent.base_))
		{}

	public:
		using difference_type  = ranges::range_difference_t<V>;
		using value_type       = ranges::range_value_t<V>;
		using iterator_concept = hamon::input_iterator_tag;

		iterator(iterator&&) = default;
		iterator& operator=(iterator&&) = default;

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		ranges::iterator_t<V> base() &&
		{
			// [range.cache.latest.iterator]/2
			return hamon::move(current_);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		ranges::iterator_t<V> const& base() const& HAMON_NOEXCEPT
		{
			// [range.cache.latest.iterator]/3
			return current_;
		}

	private:
		// [range.cache.latest.iterator]/6
		template <typename V2 = V, typename = hamon::enable_if_t<
			hamon::is_reference_v<ranges::range_reference_t<V2>>>>
		HAMON_CXX14_CONSTEXPR ranges::range_reference_t<V>&
		dereference(hamon::detail::overload_priority<1>) const
		{
			if (!parent_->cache_)
			{
				parent_->cache_ = hamon::addressof(ranges::detail::as_lvalue(*current_));
			}
			return **parent_->cache_;
		}

		HAMON_CXX14_CONSTEXPR ranges::range_reference_t<V>&
		dereference(hamon::detail::overload_priority<0>) const
		{
			if (!parent_->cache_)
			{
				parent_->cache_.emplace_deref(current_);
			}
			return *parent_->cache_;
		}

	public:
		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		ranges::range_reference_t<V>& operator*() const
		{
			// [range.cache.latest.iterator]/6
			return this->dereference(hamon::detail::overload_priority<1>{});
		}

		HAMON_CXX14_CONSTEXPR
		iterator& operator++()
		{
			// [range.cache.latest.iterator]/4
			parent_->cache_.reset();
			++current_;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR
		void operator++(int)
		{
			// [range.cache.latest.iterator]/5
			++*this;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		ranges::range_rvalue_reference_t<V> iter_move(iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(ranges::iter_move(i.current_))
		{
			// [range.cache.latest.iterator]/7
			return ranges::iter_move(i.current_);
		}

		template <HAMON_CONSTRAINT_D(hamon::indirectly_swappable, I, ranges::iterator_t<V>)>
		friend HAMON_CXX14_CONSTEXPR
		void iter_swap(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(ranges::iter_swap(x.current_, y.current_))
		{
			// [range.cache.latest.iterator]/8
			ranges::iter_swap(x.current_, y.current_);
		}
	};

	class sentinel
	{
	private:
		friend cache_latest_view;

	private:
		ranges::sentinel_t<V> end_ = ranges::sentinel_t<V>();

#if defined(HAMON_MSVC)
	public:
#else
	private:
#endif
		HAMON_CXX11_CONSTEXPR explicit
		sentinel(cache_latest_view& parent)
			// [range.cache.latest.sentinel]/1
			: end_(ranges::end(parent.base_))
		{}

	public:
		sentinel() = default;

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		ranges::sentinel_t<V> base() const
		{
			// [range.cache.latest.sentinel]/2
			return end_;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, sentinel const& y)
		{
			// [range.cache.latest.sentinel]/3
			return x.current_ == y.end_;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator const& y)
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, sentinel const& y)
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator const& y)
		{
			return !(x == y);
		}
#endif

		template <typename V2 = V, typename = hamon::enable_if_t<
			hamon::sized_sentinel_for<ranges::sentinel_t<V2>, ranges::iterator_t<V2>>>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		ranges::range_difference_t<V> operator-(iterator const& x, sentinel const& y)
		{
			// [range.cache.latest.sentinel]/4
			return x.current_ - y.end_;
		}

		template <typename V2 = V, typename = hamon::enable_if_t<
			hamon::sized_sentinel_for<ranges::sentinel_t<V2>, ranges::iterator_t<V2>>>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		ranges::range_difference_t<V> operator-(sentinel const& x, iterator const& y)
		{
			// [range.cache.latest.sentinel]/5
			return x.end_ - y.current_;
		}
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	cache_latest_view()
		requires hamon::default_initializable<V> = default;
#else
	template <HAMON_CONSTRAINT_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR
	cache_latest_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible_v<V>)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	cache_latest_view(V base)
		: base_(hamon::move(base))	// [range.cache.latest.ranges::view]/1
	{}

	template <HAMON_CONSTRAINT_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const&
	{
		return base_;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() &&
	{
		return hamon::move(base_);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin()
	{
		// [range.cache.latest.ranges::view]/2
		return iterator(*this);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end()
	{
		// [range.cache.latest.ranges::view]/3
		return sentinel(*this);
	}

	template <HAMON_CONSTRAINT_D(ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto size()
	{
		// [range.cache.latest.ranges::view]/4
		return ranges::size(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto size() const
	{
		// [range.cache.latest.ranges::view]/4
		return ranges::size(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::approximately_sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto reserve_hint()
	{
		// [range.cache.latest.ranges::view]/5
		return ranges::reserve_hint(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::approximately_sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto reserve_hint() const
	{
		// [range.cache.latest.ranges::view]/5
		return ranges::reserve_hint(base_);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
cache_latest_view(R&&) -> cache_latest_view<views::all_t<R>>;

#endif

}	// inline namespace cache_latest_view_ns

namespace views {

namespace detail {

// 25.7.34.1 Overview[range.cache.latest.overview]
struct cache_latest_fn : public hamon::ranges::range_adaptor_closure<cache_latest_fn>
{
	template <HAMON_CONSTRAINT(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r) const
	{
		return hamon::ranges::cache_latest_view<views::all_t<R>>(hamon::forward<R>(r));
	}
};

} // namespace detail

inline namespace cpo
{

// [range.cache.latest], cache latest ranges::view
HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::cache_latest_fn cache_latest{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_CACHE_LATEST_VIEW_HPP
