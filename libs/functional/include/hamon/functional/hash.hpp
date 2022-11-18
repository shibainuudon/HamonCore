/**
 *	@file	hash.hpp
 *
 *	@brief	hash
 */

#ifndef HAMON_FUNCTIONAL_HASH_HPP
#define HAMON_FUNCTIONAL_HASH_HPP

#include <hamon/functional/detail/has_adl_hash.hpp>
#include <hamon/functional/detail/has_member_hash.hpp>
#include <hamon/bit/bit_cast.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/make_uint_n.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <tuple>
#include <climits>
#include <limits>
#include <array>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4293)
HAMON_WARNING_DISABLE_CLANG("-Wshift-count-overflow")
HAMON_WARNING_DISABLE_GCC("-Wshift-count-overflow")

namespace hamon
{

template <typename... T>
HAMON_CXX11_CONSTEXPR std::size_t
hash_combine(std::size_t seed, T const&... args) HAMON_NOEXCEPT;

/**
 *	@brief	hash_t
 */
struct hash_t
{
private:
	template <typename Iterator>
	static HAMON_CXX14_CONSTEXPR std::size_t
	hash_range(Iterator first, Iterator last)
	{
		std::size_t result = 0;
		for (; first != last; ++first)
		{
			result = hash_combine(result, *first);
		}
		return result;
	}

	template <typename T>
	static HAMON_CXX11_CONSTEXPR std::size_t
	hash_combine_integral(std::size_t seed, T x, std::size_t n)
	{
		return n <= sizeof(std::size_t) ?
			seed :
			hash_combine_integral(
				hash_combine(seed, static_cast<std::size_t>(x >> (sizeof(std::size_t) * CHAR_BIT))),
				x >> (sizeof(std::size_t) * CHAR_BIT),
				n - sizeof(std::size_t));
	}

	template <typename T, std::size_t... Is>
	static HAMON_CXX11_CONSTEXPR std::size_t
	hash_combine_tuple(T&& x, hamon::index_sequence<Is...>)
	{
		return hash_combine(0, std::get<Is>(std::forward<T>(x))...);
	}

	template <typename T, std::size_t Digits = std::numeric_limits<hamon::remove_cvref_t<T>>::digits>
	struct hash_float
	{
		static HAMON_CXX11_CONSTEXPR std::size_t
		impl(T&& x)
		{
			using type = std::array<unsigned char, sizeof(T)>;
			return hash_t{}(hamon::bit_cast<type>(x));
		}
	};

	// long double が 拡張倍精度(80bit) の場合、パディングが入る
	template <typename T>
	struct hash_float<T, 64>
	{
		static HAMON_CXX14_CONSTEXPR std::size_t
		impl(T&& x)
		{
			using type = std::array<unsigned char, sizeof(T)>;
			auto const arr = hamon::bit_cast<type>(x);
			return hash_range(arr.begin(), arr.begin() + 10);
		}
	};

	// (1) メンバーのhash関数が呼び出せるならx.hash()
	template <HAMON_CONSTRAINED_PARAM(detail::has_member_hash, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<9>)
	{
		return std::forward<T>(x).hash();
	}

	// (2) ADL経由でhash関数が呼び出せるならhash(x)
	template <HAMON_CONSTRAINED_PARAM(detail::has_adl_hash, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<8>)
	{
		return hash(std::forward<T>(x));
	}

	// (3) integral なら static_cast
	template <HAMON_CONSTRAINED_PARAM(hamon::integral, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<7>)
	{
		return hash_combine_integral(static_cast<std::size_t>(x), x, sizeof(T));
	}
	
	// (4) floating_pointなら同じサイズのarrayにbit_castしてhash
	template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<6>)
	{
		return hash_float<T>::impl(std::forward<T>(x));
	}

	// (5) enum なら underlying_type_t<T> にキャストしてhash
	template <typename RawT, typename T, typename = hamon::enable_if_t<std::is_enum<RawT>::value>>
	static HAMON_CXX11_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<5>)
	{
		return hash_t{}(hamon::underlying_type_t<T>(x));
	}

	// (6) nullptr_tなら0
	template <HAMON_CONSTRAINED_PARAM(hamon::same_as, std::nullptr_t, RawT), typename T>
	static HAMON_CXX11_CONSTEXPR std::size_t
	impl(T&&, hamon::detail::overload_priority<4>)
	{
		return 0;
	}

	// (7) ポインターなら同じサイズのarrayにbit_castしてhash
	template <typename RawT, typename T, typename = hamon::enable_if_t<std::is_pointer<RawT>::value>>
	static HAMON_CXX14_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<3>)
	{
		using type = std::array<unsigned char, sizeof(T)>;
		return hash_t{}(hamon::bit_cast<type>(x));
	}

	// (8) range なら hash_combine(begin(x)...end(x))
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, RawT), typename T>
	static HAMON_CXX14_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<2>)
	{
		return hash_range(std::begin(x), std::end(x));
	}

	// (9) tuple-like なら hash_combine(get<I>(x)...)
	template <HAMON_CONSTRAINED_PARAM(hamon::tuple_like, RawT), typename T>
	static HAMON_CXX14_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<1>)
	{
		return hash_combine_tuple(
			std::forward<T>(x),
			hamon::make_index_sequence<std::tuple_size<RawT>::value>{});
	}

	// (10) std::hash<T>が呼び出せるなら std::hash<T>{}(x)
	template <typename RawT, typename T>
	static HAMON_CXX14_CONSTEXPR std::size_t
	impl(T&& x, hamon::detail::overload_priority<0>)
	{
		return std::hash<RawT>{}(std::forward<T>(x));
	}

public:
	template <typename T>
	constexpr std::size_t operator()(T&& x) const
	{
		using raw_type = hamon::remove_cvref_t<T>;
		return impl<raw_type>(std::forward<T>(x), hamon::detail::overload_priority<9>{});
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
hash_t hash{};

}	// inline namespace cpo

}	// namespace hamon

HAMON_WARNING_POP()

#include <hamon/functional/hash_combine.hpp>

#endif // HAMON_FUNCTIONAL_HASH_HPP
