﻿/**
 *	@file	hash.hpp
 *
 *	@brief	hash
 */

#ifndef HAMON_FUNCTIONAL_HASH_HPP
#define HAMON_FUNCTIONAL_HASH_HPP

#include <hamon/functional/detail/has_adl_hash.hpp>
#include <hamon/functional/detail/has_member_hash.hpp>
#include <hamon/bit/bit_cast.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/make_uint_n.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <functional>
#include <tuple>
#include <climits>
#include <array>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4293)
HAMON_WARNING_DISABLE_CLANG("-Wshift-count-overflow")
HAMON_WARNING_DISABLE_GCC("-Wshift-count-overflow")

namespace hamon
{
namespace ranges
{

template <typename... T>
HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine(hamon::size_t seed, T const&... args) HAMON_NOEXCEPT;

#define HAMON_HASH_RETURN(...) \
    HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)	\
    { return __VA_ARGS__; }

/**
 *	@brief	hash_t
 */
struct hash_t
{
private:
	template <typename T, hamon::size_t... Is>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	hash_combine_array(T&& x, hamon::index_sequence<Is...>)
	{
		return hash_combine(0, x[Is]...);
	}

#if HAMON_CXX_STANDARD < 14
	template <typename Iterator>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	hash_range_impl(Iterator first, Iterator last, hamon::size_t result)
	{
		return first == last ?
			result :
			hash_range_impl(hamon::next(first), last, hash_combine(result, *first));
	}
#endif

	template <typename Iterator>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	hash_range(Iterator first, Iterator last)
	{
#if HAMON_CXX_STANDARD < 14
		return hash_range_impl(first, last, 0);
#else
		hamon::size_t result = 0;
		for (; first != last; ++first)
		{
			result = hash_combine(result, *first);
		}
		return result;
#endif
	}

	template <typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	hash_combine_integral(hamon::size_t seed, T x, hamon::size_t n) HAMON_NOEXCEPT
	{
		return n <= sizeof(hamon::size_t) ?
			seed :
			hash_combine_integral(
				hash_combine(seed, static_cast<hamon::size_t>(x >> (sizeof(hamon::size_t) * CHAR_BIT))),
				x >> (sizeof(hamon::size_t) * CHAR_BIT),
				n - sizeof(hamon::size_t));
	}

	template <typename T, hamon::size_t... Is>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	hash_combine_tuple(T&& x, hamon::index_sequence<Is...>)
	{
		return hash_combine(0, hamon::adl_get<Is>(hamon::forward<T>(x))...);
	}

	template <typename T, hamon::size_t N>
	struct Array
	{
		T buf[N];
	};

	template <typename T, hamon::size_t Digits = hamon::numeric_limits<hamon::remove_cvref_t<T>>::digits>
	struct hash_float
	{
		static HAMON_CXX11_CONSTEXPR hamon::size_t
		impl(T&& x)
		{
			using type = Array<unsigned char, sizeof(T)>;
			return hash_t{}(hamon::bit_cast<type>(x).buf);
		}
	};

	// long double が 拡張倍精度(80bit) の場合、パディングが入る
	template <typename T>
	struct hash_float<T, 64>
	{
	private:
		static HAMON_CXX11_CONSTEXPR hamon::size_t
		impl2(Array<unsigned char, sizeof(T)> const& arr)
		{
			return hash_range(arr.buf, arr.buf + 10);
		}
	public:
		static HAMON_CXX11_CONSTEXPR hamon::size_t
		impl(T&& x)
		{
			using type = Array<unsigned char, sizeof(T)>;
			return impl2(hamon::bit_cast<type>(x));
		}
	};

	// (1) メンバーのhash関数が呼び出せるならx.hash()
	template <HAMON_CONSTRAINED_PARAM(hamon::detail::has_member_hash, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<10>)
	HAMON_HASH_RETURN(
		hamon::forward<T>(x).hash())

	// (2) ADL経由でhash関数が呼び出せるならhash(x)
	template <HAMON_CONSTRAINED_PARAM(hamon::detail::has_adl_hash, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<9>)
	HAMON_HASH_RETURN(
		hash(hamon::forward<T>(x)))

	// (3) integral なら static_cast
	template <HAMON_CONSTRAINED_PARAM(hamon::integral, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<8>)
	HAMON_HASH_RETURN(
		hash_combine_integral(static_cast<hamon::size_t>(x), x, sizeof(T)))
	
	// (4) floating_pointなら同じサイズのarrayにbit_castしてhash
	template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<7>)
	HAMON_HASH_RETURN(
		hash_float<T>::impl(hamon::forward<T>(x)))

	// (5) enum なら underlying_type_t<T> にキャストしてhash
	template <typename RawT, typename T, typename = hamon::enable_if_t<hamon::is_enum<RawT>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<6>)
    HAMON_NOEXCEPT_IF_EXPR(hamon::declval<hash_t>()(hamon::underlying_type_t<T>(x)))
    {
		return hash_t{}(hamon::underlying_type_t<T>(x));
	}

	// (6) nullptr_tなら0
	template <HAMON_CONSTRAINED_PARAM(hamon::same_as, hamon::nullptr_t, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&&, hamon::detail::overload_priority<5>) HAMON_NOEXCEPT
	{
		return 0;
	}

	// (7) ポインターなら同じサイズのarrayにbit_castしてhash
	template <typename RawT, typename T, typename = hamon::enable_if_t<hamon::is_pointer<RawT>::value>>
	static HAMON_CXX14_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<4>)
    HAMON_NOEXCEPT_IF_EXPR(hamon::declval<hash_t>()(hamon::bit_cast<std::array<unsigned char, sizeof(T)>>(x)))
    {
		return hash_t{}(hamon::bit_cast<std::array<unsigned char, sizeof(T)>>(x));
	}

	// (8) 配列 なら hash_combine(x[0]...x[N-1])
	template <typename RawT, typename T, typename = hamon::enable_if_t<hamon::is_array<RawT>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<3>)
	HAMON_HASH_RETURN(
		hash_combine_array(
			hamon::forward<T>(x),
			hamon::make_index_sequence<hamon::extent<RawT>::value>{}))

	// (9) tuple-like なら hash_combine(get<I>(x)...)
	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<2>)
	HAMON_HASH_RETURN(
		hash_combine_tuple(
			hamon::forward<T>(x),
			hamon::make_index_sequence<std::tuple_size<RawT>::value>{}))

	// (10) range なら begin(x)からend(x)までループしてhash_combine
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<1>)
	HAMON_HASH_RETURN(
		hash_range(hamon::ranges::begin(x), hamon::ranges::end(x)))

	// (11) std::hash<T>が呼び出せるなら std::hash<T>{}(x)
	template <typename RawT, typename T>
	static HAMON_CXX14_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<0>)
	HAMON_HASH_RETURN(
		std::hash<RawT>{}(hamon::forward<T>(x)))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T&& x) const
	HAMON_HASH_RETURN(
		impl<hamon::remove_cvref_t<T>>(hamon::forward<T>(x), hamon::detail::overload_priority<10>{}))

	using is_transparent = void;
};

#undef HAMON_HASH_RETURN

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
hash_t hash{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

HAMON_WARNING_POP()

#include <hamon/functional/ranges/hash_combine.hpp>

#endif // HAMON_FUNCTIONAL_HASH_HPP
