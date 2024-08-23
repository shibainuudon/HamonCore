/**
 *	@file	default_delete.hpp
 *
 *	@brief	default_delete の定義
 */

#ifndef HAMON_MEMORY_DEFAULT_DELETE_HPP
#define HAMON_MEMORY_DEFAULT_DELETE_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_DEFAULT_DELETE)

namespace hamon
{

using std::default_delete;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/config.hpp>

// 20.3.1.2 Default deleters[unique.ptr.dltr]

namespace hamon
{

// 20.3.1.2.2 default_delete[unique.ptr.dltr.dflt]
template <typename T>
struct default_delete
{
	HAMON_CXX11_CONSTEXPR default_delete() noexcept = default;

	template <typename U,
		typename = hamon::enable_if_t<	// [unique.ptr.dltr.dflt]/1
			hamon::is_convertible<U*, T*>::value>>
	HAMON_CXX11_CONSTEXPR default_delete(default_delete<U> const&) noexcept
	{
		// [unique.ptr.dltr.dflt]/2
	}

	HAMON_CXX14_CONSTEXPR void operator()(T* ptr) const
	{
		// [unique.ptr.dltr.dflt]/3
		static_assert(sizeof(T) > 0, "T must be a complete type.");

		// [unique.ptr.dltr.dflt]/4
		delete ptr;
	}
};

// 20.3.1.2.3 default_delete<T[]>[unique.ptr.dltr.dflt1]
template <typename T>
struct default_delete<T[]>
{
	HAMON_CXX11_CONSTEXPR default_delete() noexcept = default;

	template <typename U,
		typename = hamon::enable_if_t<	// [unique.ptr.dltr.dflt1]/1
			hamon::is_convertible<U(*)[], T(*)[]>::value>>
	HAMON_CXX11_CONSTEXPR default_delete(default_delete<U[]> const&) noexcept
	{
		// [unique.ptr.dltr.dflt1]/2
	}

	template <typename U,
		typename = hamon::enable_if_t<	// [unique.ptr.dltr.dflt1]/3
			hamon::is_convertible<U(*)[], T(*)[]>::value>>
	HAMON_CXX14_CONSTEXPR void operator()(U* ptr) const
	{
		// [unique.ptr.dltr.dflt1]/4
		static_assert(sizeof(T) > 0, "T must be a complete type.");

		// [unique.ptr.dltr.dflt1]/5
		delete[] ptr;
	}
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DEFAULT_DELETE_HPP
