/**
 *	@file	type_info.hpp
 *
 *	@brief
 */

#ifndef HAMON_TYPE_INFO_TYPE_INFO_HPP
#define HAMON_TYPE_INFO_TYPE_INFO_HPP

#include <hamon/type_info/detail/type_info_access_fwd.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/string_view/string_view.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/config.hpp>

namespace hamon
{

class type_info
{
private:
	HAMON_CONSTEXPR
	type_info(hamon::string_view name) HAMON_NOEXCEPT
		: m_name(name)
	{}

public:
	HAMON_NODISCARD HAMON_CONSTEXPR
	hamon::string_view name() const HAMON_NOEXCEPT
	{
		return m_name;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR
	hamon::size_t hash() const HAMON_NOEXCEPT
	{
		return hamon::hash(m_name);
	}

	HAMON_NODISCARD friend HAMON_CONSTEXPR bool
	operator==(type_info const& lhs, type_info const& rhs) HAMON_NOEXCEPT
	{
		return lhs.hash() == rhs.hash();
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CONSTEXPR bool
	operator!=(type_info const& lhs, type_info const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif

private:
	hamon::string_view	m_name;

private:
	friend class hamon::detail::type_info_access;
};

}	// namespace hamon

#endif // HAMON_TYPE_INFO_TYPE_INFO_HPP
