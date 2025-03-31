/**
 *	@file	hash.hpp
 *
 *	@brief	hash
 */

#ifndef HAMON_FUNCTIONAL_RANGES_HASH_HPP
#define HAMON_FUNCTIONAL_RANGES_HASH_HPP

#include <hamon/functional/hash.hpp>
#include <hamon/functional/detail/has_member_hash.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <functional>	// std::hash
#include <tuple>		// std::tuple_size

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

	template <typename T, hamon::size_t... Is>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	hash_combine_tuple(T&& x, hamon::index_sequence<Is...>)
	{
		return hash_combine(0, hamon::adl_get<Is>(hamon::forward<T>(x))...);
	}

	// (1) メンバーのhash関数が呼び出せるならx.hash()
	template <HAMON_CONSTRAINED_PARAM(hamon::detail::has_member_hash, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<5>)
	HAMON_HASH_RETURN(
		hamon::forward<T>(x).hash())

	// (2) 配列 なら hash_combine(x[0]...x[N-1])
	template <typename RawT, typename T,
		typename = hamon::enable_if_t<hamon::is_array<RawT>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<4>)
	HAMON_HASH_RETURN(
		hash_combine_array(
			hamon::forward<T>(x),
			hamon::make_index_sequence<hamon::extent<RawT>::value>{}))

	// (3) tuple-like なら hash_combine(get<I>(x)...)
	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<3>)
	HAMON_HASH_RETURN(
		hash_combine_tuple(
			hamon::forward<T>(x),
			hamon::make_index_sequence<std::tuple_size<RawT>::value>{}))

	// (4) range なら begin(x)からend(x)までループしてhash_combine
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<2>)
	HAMON_HASH_RETURN(
		hash_range(hamon::ranges::begin(x), hamon::ranges::end(x)))

	// (5) hamon::hash<T>が呼び出せるなら hamon::hash<T>{}(x)
	template <typename RawT, typename T,
		typename = hamon::enable_if_t<
			hamon::detail::cpp17_hash_t<hamon::hash<RawT>, T>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<1>)
	HAMON_HASH_RETURN(
		hamon::hash<RawT>{}(hamon::forward<T>(x)))

	// (6) std::hash<T>が呼び出せるなら std::hash<T>{}(x)
	template <typename RawT, typename T,
		typename = hamon::enable_if_t<
			hamon::detail::cpp17_hash_t<std::hash<RawT>, T>::value>>
	static HAMON_CXX14_CONSTEXPR hamon::size_t
	impl(T&& x, hamon::detail::overload_priority<0>)
	HAMON_HASH_RETURN(
		std::hash<RawT>{}(hamon::forward<T>(x)))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T&& x) const
	HAMON_HASH_RETURN(impl<hamon::remove_cvref_t<T>>(
		hamon::forward<T>(x), hamon::detail::overload_priority<5>{}))

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

#include <hamon/functional/ranges/hash_combine.hpp>

#endif // HAMON_FUNCTIONAL_RANGES_HASH_HPP
