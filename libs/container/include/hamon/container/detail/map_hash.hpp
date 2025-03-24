/**
 *	@file	map_hash.hpp
 *
 *	@brief	map_hash の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_MAP_HASH_HPP
#define HAMON_CONTAINER_DETAIL_MAP_HASH_HPP

#include <hamon/container/detail/map_get_key.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

template <typename Hash>
struct map_hash
{
private:
	Hash	m_hash;

public:
	HAMON_CXX11_CONSTEXPR
	map_hash()
		: m_hash() {}

	HAMON_CXX11_CONSTEXPR
	map_hash(Hash const& h)
		: m_hash(h) {}

	HAMON_CXX11_CONSTEXPR
	operator Hash() const
	{
		return m_hash;
	}

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T const& x) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		m_hash(hamon::detail::map_get_key(x)))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_MAP_HASH_HPP
