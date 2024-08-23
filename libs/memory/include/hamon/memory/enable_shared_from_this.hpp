/**
 *	@file	enable_shared_from_this.hpp
 *
 *	@brief	enable_shared_from_this の定義
 */

#ifndef HAMON_MEMORY_ENABLE_SHARED_FROM_THIS_HPP
#define HAMON_MEMORY_ENABLE_SHARED_FROM_THIS_HPP

#include <hamon/memory/enable_shared_from_this_fwd.hpp>
#include <hamon/memory/config.hpp>

#if !defined(HAMON_USE_STD_SHARED_PTR)

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.7 Class template enable_shared_from_this[util.smartptr.enab]
template <typename T>
class enable_shared_from_this
{
protected:
	HAMON_CXX11_CONSTEXPR
	enable_shared_from_this() noexcept {}

	HAMON_CXX11_CONSTEXPR
	enable_shared_from_this(enable_shared_from_this const&) noexcept {}

	HAMON_CXX14_CONSTEXPR enable_shared_from_this&
	operator=(enable_shared_from_this const&) noexcept
	{
		// [util.smartptr.enab]/5
		return *this;
	}

	HAMON_CXX20_CONSTEXPR ~enable_shared_from_this() {}

public:
	HAMON_CXX14_CONSTEXPR
	hamon::shared_ptr<T> shared_from_this()
	{
		// [util.smartptr.enab]/7
		return hamon::shared_ptr<T>(weak_this);
	}

	HAMON_CXX11_CONSTEXPR
	hamon::shared_ptr<T const> shared_from_this() const
	{
		// [util.smartptr.enab]/7
		return hamon::shared_ptr<T>(weak_this);
	}

	HAMON_CXX14_CONSTEXPR
	hamon::weak_ptr<T> weak_from_this() noexcept
	{
		// [util.smartptr.enab]/8
		return weak_this;
	}

	HAMON_CXX11_CONSTEXPR
	hamon::weak_ptr<T const> weak_from_this() const noexcept
	{
		// [util.smartptr.enab]/8
		return weak_this;
	}

private:
	mutable hamon::weak_ptr<T> weak_this;  // exposition only

private:
	template <typename U>
	friend class shared_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ENABLE_SHARED_FROM_THIS_HPP
