﻿/**
 *	@file	subrange.hpp
 *
 *	@brief	subrange の定義
 */

#ifndef HAMON_RANGES_UTILITY_SUBRANGE_HPP
#define HAMON_RANGES_UTILITY_SUBRANGE_HPP

#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::subrange;
using std::ranges::get;

}	// namespace ranges

using ranges::get;

}	// namespace hamon

#else

#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/ranges/utility/detail/make_unsigned_like_t.hpp>
#include <hamon/ranges/utility/detail/convertible_to_non_slicing.hpp>
#include <hamon/ranges/utility/detail/different_from.hpp>
#include <hamon/ranges/utility/detail/pair_like_convertible_from.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename It2, typename It, bool StoreSize>
concept subrange_constructible_from_iter_sent =
	hamon::ranges::detail::convertible_to_non_slicing<It2, It> &&
	!StoreSize;

template <typename It2, typename It, ranges::subrange_kind Kind>
concept subrange_constructible_from_iter_sent_size =
	hamon::ranges::detail::convertible_to_non_slicing<It2, It> &&
	Kind == ranges::subrange_kind::sized;

template <typename Rng, typename It, typename Sent, typename Subrange, bool StoreSize>
concept subrange_constructible_from_range =
	hamon::ranges::detail::different_from<Rng, Subrange> &&
	hamon::ranges::borrowed_range<Rng> &&
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It> &&
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent> &&
	(!StoreSize || hamon::ranges::sized_range<Rng>);

template <typename Rng, typename It, typename Sent, ranges::subrange_kind Kind>
concept subrange_constructible_from_range_size =
	hamon::ranges::borrowed_range<Rng> &&
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It> &&
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent> &&
	(Kind == ranges::subrange_kind::sized);

template <typename PairLike, typename It, typename Sent, typename Subrange>
concept subrange_convertible_to_pair_like =
	hamon::ranges::detail::different_from<PairLike, Subrange> &&
	detail::pair_like_convertible_from<PairLike, It const&, Sent const&>;

#else

template <typename It2, typename It, bool StoreSize>
using subrange_constructible_from_iter_sent = hamon::conjunction<
	hamon::ranges::detail::convertible_to_non_slicing<It2, It>,
	hamon::bool_constant<!StoreSize>
>;

template <typename It2, typename It, ranges::subrange_kind Kind>
using subrange_constructible_from_iter_sent_size = hamon::conjunction<
	hamon::ranges::detail::convertible_to_non_slicing<It2, It>,
	hamon::bool_constant<Kind == ranges::subrange_kind::sized>
>;

template <typename Rng, typename It, typename Sent, typename Subrange, bool StoreSize>
using subrange_constructible_from_range = hamon::conjunction<
	hamon::ranges::detail::different_from<Rng, Subrange>,
	hamon::ranges::borrowed_range<Rng>,
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It>,
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent>,
	hamon::bool_constant<(!StoreSize || hamon::ranges::sized_range<Rng>::value)>
>;

template <typename Rng, typename It, typename Sent, ranges::subrange_kind Kind>
using subrange_constructible_from_range_size = hamon::conjunction<
	hamon::ranges::borrowed_range<Rng>,
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It>,
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent>,
	hamon::bool_constant<Kind == ranges::subrange_kind::sized>
>;

template <typename PairLike, typename It, typename Sent, typename Subrange>
using subrange_convertible_to_pair_like = hamon::conjunction<
	hamon::ranges::detail::different_from<PairLike, Subrange>,
	detail::pair_like_convertible_from<PairLike, It const&, Sent const&>
>;

#endif

template <hamon::size_t N>
struct subrange_get;

template <>
struct subrange_get<0>
{
	template <typename R>
	HAMON_CXX11_CONSTEXPR auto operator()(R&& r) const
	->decltype(r.begin())
	{
		return r.begin();
	}
};
template <>
struct subrange_get<1>
{
	template <typename R>
	HAMON_CXX11_CONSTEXPR auto operator()(R&& r) const
	->decltype(r.end())
	{
		return r.end();
	}
};

}	// namespace detail

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <
	hamon::input_or_output_iterator It,
	hamon::sentinel_for<It> Sent = It,
	ranges::subrange_kind Kind =
		hamon::sized_sentinel_for_t<Sent, It>::value ?
			ranges::subrange_kind::sized :
			ranges::subrange_kind::unsized

>
requires (
	Kind == ranges::subrange_kind::sized ||
	!hamon::sized_sentinel_for<Sent, It>)
#else
template <
	typename It,
	typename Sent = It,
	ranges::subrange_kind Kind =
		hamon::sized_sentinel_for_t<Sent, It>::value ?
			ranges::subrange_kind::sized :
			ranges::subrange_kind::unsized,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::input_or_output_iterator<It>,
		hamon::sentinel_for<Sent, It>,
		hamon::bool_constant<
			Kind == ranges::subrange_kind::sized ||
			!hamon::sized_sentinel_for<Sent, It>::value
		>
	>::value>
>
#endif
class subrange : public ranges::view_interface<subrange<It, Sent, Kind>>
{
private:
	static constexpr bool StoreSize =
		Kind == ranges::subrange_kind::sized &&
		!hamon::sized_sentinel_for_t<Sent, It>::value;

	using size_type = detail::make_unsigned_like_t<hamon::iter_difference_t<It>>;

	template <typename I, typename S, bool = StoreSize>
	struct Impl
	{
		HAMON_NO_UNIQUE_ADDRESS I m_begin = I();
		HAMON_NO_UNIQUE_ADDRESS S m_end   = S();
		
		Impl() = default;

		template <typename I2, typename S2>
		HAMON_CXX11_CONSTEXPR Impl(I2&& begin, S2&& end)
			HAMON_NOEXCEPT_IF((
				hamon::is_nothrow_constructible<I, I2>::value &&
				hamon::is_nothrow_constructible<S, S2>::value))
			: m_begin(hamon::forward<I2>(begin))
			, m_end(hamon::forward<S2>(end))
		{}

		template <typename I2, typename S2>
		HAMON_CXX11_CONSTEXPR Impl(I2&& begin, S2&& end, size_type)
			HAMON_NOEXCEPT_IF_EXPR(Impl(hamon::forward<I2>(begin), hamon::forward<S2>(end)))
			: Impl(hamon::forward<I2>(begin), hamon::forward<S2>(end))
		{}

		template <typename Rng>
		HAMON_CXX11_CONSTEXPR Impl(Rng&& r)
			HAMON_NOEXCEPT_IF_EXPR(Impl(ranges::begin(r), ranges::end(r)))
			: Impl(ranges::begin(r), ranges::end(r))
		{}

		template <typename Rng>
		HAMON_CXX11_CONSTEXPR
		Impl(Rng&& r, size_type n)
			HAMON_NOEXCEPT_IF_EXPR(Impl(ranges::begin(r), ranges::end(r), n))
			: Impl{ ranges::begin(r), ranges::end(r), n }
		{}

		HAMON_CXX11_CONSTEXPR size_type get_size() const
		{
			return detail::to_unsigned_like(m_end - m_begin);
		}

		HAMON_CXX14_CONSTEXPR void increment_size(size_type) {}
		HAMON_CXX14_CONSTEXPR void decrement_size(size_type) {}
	};

	template <typename I, typename S>
	struct Impl<I, S, true>
	{
		HAMON_NO_UNIQUE_ADDRESS I m_begin = I();
		HAMON_NO_UNIQUE_ADDRESS S m_end   = S();
		size_type m_size {};

		Impl() = default;

		template <typename I2, typename S2>
		HAMON_CXX11_CONSTEXPR Impl(I2&& begin, S2&& end, size_type n)
			HAMON_NOEXCEPT_IF((
				hamon::is_nothrow_constructible<I, I2>::value &&
				hamon::is_nothrow_constructible<S, S2>::value))
			: m_begin(hamon::forward<I2>(begin))
			, m_end(hamon::forward<S2>(end))
			, m_size(n)
		{}

		template <typename Rng>
		HAMON_CXX11_CONSTEXPR Impl(Rng&& r)
			HAMON_NOEXCEPT_IF_EXPR(Impl(r, ranges::size(r)))
			: Impl(r, ranges::size(r))
		{}

		template <typename Rng>
		HAMON_CXX11_CONSTEXPR
		Impl(Rng&& r, size_type n)
			HAMON_NOEXCEPT_IF_EXPR(Impl(ranges::begin(r), ranges::end(r), n))
			: Impl{ ranges::begin(r), ranges::end(r), n }
		{}

		HAMON_CXX11_CONSTEXPR size_type get_size() const
		{
			return m_size;
		}

		HAMON_CXX14_CONSTEXPR void increment_size(size_type n)
		{
			m_size += n;
		}

		HAMON_CXX14_CONSTEXPR void decrement_size(size_type n)
		{
			m_size -= n;
		}
	};

	using ImplType = Impl<It, Sent>;
	ImplType m_impl = {};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX11_CONSTEXPR subrange() requires hamon::default_initializable<It> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, It2, It)>
	HAMON_CXX11_CONSTEXPR subrange()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<It>::value)
	{}
#endif

	template <HAMON_CONSTRAINED_PARAM(detail::subrange_constructible_from_iter_sent, It, StoreSize, It2)>
	HAMON_CXX11_CONSTEXPR
	subrange(It2 i, Sent s)
		HAMON_NOEXCEPT_IF_EXPR(ImplType(hamon::move(i), hamon::move(s)))
		: m_impl(hamon::move(i), hamon::move(s))
	{}

	template <HAMON_CONSTRAINED_PARAM(detail::subrange_constructible_from_iter_sent_size, It, Kind, It2)>
	HAMON_CXX11_CONSTEXPR
	subrange(It2 i, Sent s, size_type n)
		HAMON_NOEXCEPT_IF_EXPR(ImplType(hamon::move(i), hamon::move(s), n))
		: m_impl(hamon::move(i), hamon::move(s), n)
	{
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (hamon::sized_sentinel_for_t<Sent, It>::value)
		{
			HAMON_ASSERT((s - i) == static_cast<hamon::iter_difference_t<It>>(n));
		}
#endif
	}

	template <HAMON_CONSTRAINED_PARAM(detail::subrange_constructible_from_range, It, Sent, subrange, StoreSize, Rng)>
	HAMON_CXX11_CONSTEXPR
	subrange(Rng&& r)
		HAMON_NOEXCEPT_IF_EXPR(ImplType(r))
		: m_impl(r)
	{}

	template <HAMON_CONSTRAINED_PARAM(detail::subrange_constructible_from_range_size, It, Sent, Kind, Rng)>
	HAMON_CXX11_CONSTEXPR
	subrange(Rng&& r, size_type n)
		HAMON_NOEXCEPT_IF_EXPR(ImplType(r, n))
		: m_impl(r, n)
	{}

	template <HAMON_CONSTRAINED_PARAM(detail::subrange_convertible_to_pair_like, It, Sent, subrange, PairLike)>
	HAMON_CXX11_CONSTEXPR operator PairLike() const
	{
		return PairLike(m_impl.m_begin, m_impl.m_end);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copyable, I, It)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR It begin() const
	{
		return m_impl.m_begin;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::not_copyable, I, It)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR It begin()
	{
		return hamon::move(m_impl.m_begin);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Sent end() const
	{
		return m_impl.m_end;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool empty() const
	{
		return m_impl.m_begin == m_impl.m_end;
	}

#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	template <ranges::subrange_kind K = Kind,
		typename = hamon::enable_if_t<K == ranges::subrange_kind::sized>
	>
#endif
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type size() const
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (Kind == ranges::subrange_kind::sized)
#endif
	{
		return m_impl.get_size();
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::forward_iterator, I, It)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR subrange
	next(hamon::iter_difference_t<It> n = 1) const &
	{
		auto tmp = *this;
		tmp.advance(n);
		return tmp;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR subrange
	next(hamon::iter_difference_t<It> n = 1) &&
	{
		advance(n);
		return hamon::move(*this);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::bidirectional_iterator, I, It)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR subrange
	prev(hamon::iter_difference_t<It> n = 1) const
	{
		auto tmp = *this;
		tmp.advance(-n);
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR subrange&
	advance(hamon::iter_difference_t<It> n)
	{
		HAMON_ASSERT(hamon::bidirectional_iterator_t<It>{} || n >= 0);
		
		if (n < 0)
		{
			ranges::advance(m_impl.m_begin, n);
			m_impl.increment_size(detail::to_unsigned_like(-n));
		}
		else
		{
			auto d = n - ranges::advance(m_impl.m_begin, n, m_impl.m_end);
			m_impl.decrement_size(detail::to_unsigned_like(d));
		}

		return *this;
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
subrange(It, Sent)
-> subrange<It, Sent>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
subrange(It, Sent, detail::make_unsigned_like_t<hamon::iter_difference_t<It>>)
-> subrange<It, Sent, ranges::subrange_kind::sized>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::borrowed_range, Rng)>
subrange(Rng&&)
-> subrange<hamon::ranges::iterator_t<Rng>, hamon::ranges::sentinel_t<Rng>,
	(hamon::ranges::sized_range_t<Rng>::value ||
	 hamon::sized_sentinel_for_t<hamon::ranges::sentinel_t<Rng>, hamon::ranges::iterator_t<Rng>>::value) ?
		ranges::subrange_kind::sized :
		ranges::subrange_kind::unsized>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::borrowed_range, Rng)>
subrange(Rng&&, detail::make_unsigned_like_t<hamon::ranges::range_difference_t<Rng>>)
-> subrange<hamon::ranges::iterator_t<Rng>, hamon::ranges::sentinel_t<Rng>, ranges::subrange_kind::sized>;

#endif	// defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <hamon::size_t N, typename It, typename Sent, ranges::subrange_kind Kind>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires (N < 2)
#endif
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
get(subrange<It, Sent, Kind> const& r)
->decltype(detail::subrange_get<N>()(r))
{
	return detail::subrange_get<N>()(r);
}

template <hamon::size_t N, typename It, typename Sent, ranges::subrange_kind Kind>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires (N < 2)
#endif
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
get(subrange<It, Sent, Kind>&& r)
->decltype(detail::subrange_get<N>()(hamon::move(r)))
{
	return detail::subrange_get<N>()(hamon::move(r));
}

}	// namespace ranges

using ranges::get;

}	// namespace hamon

#include <hamon/ranges/concepts/enable_borrowed_range.hpp>

HAMON_RANGES_START_NAMESPACE

template <typename It, typename Sent, hamon::ranges::subrange_kind Kind>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::ranges::subrange<It, Sent, Kind>);

HAMON_RANGES_END_NAMESPACE

#include <hamon/cstddef/size_t.hpp>
#include <tuple>

namespace std
{

template <typename Iter, typename Sent, hamon::ranges::subrange_kind Kind>
struct tuple_size<hamon::ranges::subrange<Iter, Sent, Kind>>
	: std::integral_constant<hamon::size_t, 2>
{};

template <typename Iter, typename Sent, hamon::ranges::subrange_kind Kind>
struct tuple_element<0, hamon::ranges::subrange<Iter, Sent, Kind>>
{
	using type = Iter;
};

template <typename Iter, typename Sent, hamon::ranges::subrange_kind Kind>
struct tuple_element<1, hamon::ranges::subrange<Iter, Sent, Kind>>
{
	using type = Sent;
};

template <typename Iter, typename Sent, hamon::ranges::subrange_kind Kind>
struct tuple_element<0, hamon::ranges::subrange<Iter, Sent, Kind> const>
{
	using type = Iter;
};

template <typename Iter, typename Sent, hamon::ranges::subrange_kind Kind>
struct tuple_element<1, hamon::ranges::subrange<Iter, Sent, Kind> const>
{
	using type = Sent;
};

}	// namespace std

#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// is_specialization_of_subrange の特殊化
template <typename Iter, typename Sent, hamon::ranges::subrange_kind Kind>
struct is_specialization_of_subrange<hamon::ranges::subrange<Iter, Sent, Kind>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#endif

#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/ranges/utility/detail/make_unsigned_like_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_subrange(It i, Sent s)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	subrange<It, Sent>(hamon::move(i), hamon::move(s)))

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_subrange(It i, Sent s, detail::make_unsigned_like_t<hamon::iter_difference_t<It>> n)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	subrange<It, Sent, ranges::subrange_kind::sized>(hamon::move(i), hamon::move(s), hamon::move(n)))

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::borrowed_range, Rng)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_subrange(Rng&& r)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	subrange<
		hamon::ranges::iterator_t<Rng>,
		hamon::ranges::sentinel_t<Rng>,
		(hamon::ranges::sized_range_t<Rng>::value ||
		 hamon::sized_sentinel_for_t<hamon::ranges::sentinel_t<Rng>, hamon::ranges::iterator_t<Rng>>::value) ?
			ranges::subrange_kind::sized :
			ranges::subrange_kind::unsized
	>(hamon::forward<Rng>(r)))

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::borrowed_range, Rng)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_subrange(Rng&& r, detail::make_unsigned_like_t<hamon::ranges::range_difference_t<Rng>> n)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	subrange<
		hamon::ranges::iterator_t<Rng>,
		hamon::ranges::sentinel_t<Rng>,
		ranges::subrange_kind::sized
	>(hamon::forward<Rng>(r), hamon::move(n)))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_SUBRANGE_HPP
