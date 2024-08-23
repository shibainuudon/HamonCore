/**
 *	@file	owner_equal.hpp
 *
 *	@brief	owner_equal の定義
 */

#ifndef HAMON_MEMORY_OWNER_EQUAL_HPP
#define HAMON_MEMORY_OWNER_EQUAL_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR)

namespace hamon
{

using std::owner_equal;

}	// namespace hamon

#else

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.6 Struct owner_equal[util.smartptr.owner.equal]
struct owner_equal
{
	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, shared_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.owner.equal]/2
		return x.owner_equal(y);
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, weak_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.owner.equal]/2
		return x.owner_equal(y);
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, shared_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.owner.equal]/2
		return x.owner_equal(y);
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, weak_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.owner.equal]/2
		return x.owner_equal(y);
	}

	using is_transparent = void;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_OWNER_EQUAL_HPP
