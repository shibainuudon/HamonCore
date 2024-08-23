/**
 *	@file	owner_less.hpp
 *
 *	@brief	owner_less の定義
 */

#ifndef HAMON_MEMORY_OWNER_LESS_HPP
#define HAMON_MEMORY_OWNER_LESS_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR)

namespace hamon
{

using std::owner_less;

}	// namespace hamon

#else

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.4 Class template owner_less[util.smartptr.ownerless]
template <typename T = void>
struct owner_less;

template <typename T>
struct owner_less<shared_ptr<T>>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, shared_ptr<T> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, weak_ptr<T> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, shared_ptr<T> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}
};

template <typename T>
struct owner_less<weak_ptr<T>>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, weak_ptr<T> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, weak_ptr<T> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, shared_ptr<T> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}
};

template <>
struct owner_less<void>
{
	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, shared_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(shared_ptr<T> const& x, weak_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, shared_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator()(weak_ptr<T> const& x, weak_ptr<U> const& y) const noexcept
	{
		// [util.smartptr.ownerless]/2
		return x.owner_before(y);
	}

	using is_transparent = void;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_OWNER_LESS_HPP
