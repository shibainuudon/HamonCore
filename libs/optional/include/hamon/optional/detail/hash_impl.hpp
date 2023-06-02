/**
 *	@file	hash_impl.hpp
 *
 *	@brief	hash_impl の定義
 */

#ifndef HAMON_OPTIONAL_DETAIL_HASH_IMPL_HPP
#define HAMON_OPTIONAL_DETAIL_HASH_IMPL_HPP

#include <hamon/optional/optional.hpp>
#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/functional/detail/disabled_hash.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <functional>

namespace hamon
{

namespace optional_detail
{

template <typename T, typename U, typename = void>
struct hash_impl : public hamon::detail::disabled_hash
{};

template <typename T, typename U>
struct hash_impl<T, U,
	hamon::enable_if_t<hamon::detail::cpp17_hash_t<std::hash<U>, U>::value>>
{
	HAMON_NODISCARD	// extension
	std::size_t operator()(hamon::optional<T> const& opt) const
	HAMON_NOEXCEPT_IF_EXPR((std::hash<U>{}(*opt)))
	{
		return opt.has_value() ? std::hash<U>{}(*opt) : 0;
	}
};

}	// namespace optional_detail

}	// namespace hamon

#endif // HAMON_OPTIONAL_DETAIL_HASH_IMPL_HPP
