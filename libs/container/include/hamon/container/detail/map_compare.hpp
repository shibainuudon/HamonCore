/**
 *	@file	map_compare.hpp
 *
 *	@brief	map_compare の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_MAP_COMPARE_HPP
#define HAMON_CONTAINER_DETAIL_MAP_COMPARE_HPP

#include <hamon/container/detail/map_get_key.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

template <typename Compare>
struct map_compare
{
private:
	Compare m_comp;

public:
	HAMON_CXX11_CONSTEXPR
	map_compare()
		: m_comp() {}

	HAMON_CXX11_CONSTEXPR
	map_compare(Compare const& c)
		: m_comp(c) {}

	HAMON_CXX11_CONSTEXPR
	operator Compare() const
	{
		return m_comp;
	}

	template <typename Lhs, typename Rhs>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(Lhs const& x, Rhs const& y) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		m_comp(hamon::detail::map_get_key(x), hamon::detail::map_get_key(y)))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_MAP_COMPARE_HPP
