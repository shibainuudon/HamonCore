/**
 *	@file	hash_impl.hpp
 *
 *	@brief	hash_impl の定義
 */

#ifndef HAMON_ARRAY_DETAIL_HASH_IMPL_HPP
#define HAMON_ARRAY_DETAIL_HASH_IMPL_HPP

#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/functional/detail/disabled_hash.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/functional/hash_combine.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace array_detail
{

template <typename T, hamon::size_t N, typename U, typename = void>
struct hash_impl : public hamon::detail::disabled_hash
{};

template <typename T, hamon::size_t N, typename U>
struct hash_impl<T, N, U,
	hamon::enable_if_t<hamon::detail::cpp17_hash<hamon::hash<U>, U>>>
{
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	hamon::size_t operator()(hamon::array<T, N> const& arr) const
	HAMON_NOEXCEPT_IF_EXPR((hamon::hash<U>{}(hamon::declval<T>())))
	{
		hamon::size_t result = 0;
		for (auto& t : arr)
		{
			result = hamon::hash_combine(result, hamon::hash<U>{}(t));
		}
		return result;
	}
};

}	// namespace array_detail
}	// namespace hamon

#endif // HAMON_ARRAY_DETAIL_HASH_IMPL_HPP
