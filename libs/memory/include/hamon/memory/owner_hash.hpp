/**
 *	@file	owner_hash.hpp
 *
 *	@brief	owner_hash の定義
 */

#ifndef HAMON_MEMORY_OWNER_HASH_HPP
#define HAMON_MEMORY_OWNER_HASH_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR)

namespace hamon
{

using std::owner_hash;

}	// namespace hamon

#else

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.5 Struct owner_hash[util.smartptr.owner.hash]
struct owner_hash
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t	// nodiscard as an extension
	operator()(shared_ptr<T> const& x) const noexcept
	{
		// [util.smartptr.owner.hash]/2
		return x.owner_hash();
	}

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t	// nodiscard as an extension
	operator()(weak_ptr<T> const& x) const noexcept
	{
		// [util.smartptr.owner.hash]/2
		return x.owner_hash();
	}

	using is_transparent = void;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_OWNER_HASH_HPP
