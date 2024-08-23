/**
 *	@file	sp_access.hpp
 *
 *	@brief	sp_access を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SP_ACCESS_HPP
#define HAMON_MEMORY_DETAIL_SP_ACCESS_HPP

#include <hamon/memory/allocator.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct sp_access
{
	template <typename D, typename T>
	static HAMON_CXX14_CONSTEXPR D*
	get_deleter(shared_ptr<T> const& p) noexcept
	{
		if (p.m_ref_count)
		{
			return p.m_ref_count->template get_deleter<D>();
		}
		return nullptr;
	}

	template <typename T, typename... Args>
	static HAMON_CXX14_CONSTEXPR shared_ptr<T>
	make_shared(Args&&... args)
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return shared_ptr<T>(new T(hamon::forward<Args>(args)...));
		}
#endif
		shared_ptr<T> ret;
		ret.template ConstructStorage<T>(hamon::allocator<T>{}, 1);
		hamon::construct_at(ret.get(), hamon::forward<Args>(args)...);
		return ret;
	}

	template <typename T, typename A, typename... Args>
	static HAMON_CXX14_CONSTEXPR shared_ptr<T>
	allocate_shared(A const& a, Args&&... args)
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return shared_ptr<T>(new T(hamon::forward<Args>(args)...), hamon::default_delete<T>{}, a);
		}
#endif
		shared_ptr<T> ret;
		ret.template ConstructStorage<T>(a, 1);
		hamon::construct_at(ret.get(), hamon::forward<Args>(args)...);
		return ret;
	}

	template <typename T, hamon::enable_if_t<!hamon::is_array<T>::value>* = nullptr>
	static HAMON_CXX14_CONSTEXPR shared_ptr<T>
	make_shared_for_overwrite()
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return shared_ptr<T>(new T);
		}
#endif
		shared_ptr<T> ret;
		ret.template ConstructStorage<T>(hamon::allocator<T>{}, 1);
		return ret;
	}

	template <typename T, hamon::enable_if_t<hamon::is_array<T>::value>* = nullptr>
	static HAMON_CXX14_CONSTEXPR shared_ptr<T>
	make_shared_for_overwrite(hamon::size_t N = hamon::extent<T>::value)
	{
		using U = hamon::remove_extent_t<T>;
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return shared_ptr<T>(new U[N]);
		}
#endif
		shared_ptr<T> ret;
		ret.template ConstructStorage<U>(hamon::allocator<T>{}, N);
		return ret;
	}

	template <typename T, hamon::enable_if_t<!hamon::is_array<T>::value>* = nullptr, typename A>
	static HAMON_CXX14_CONSTEXPR shared_ptr<T>
	allocate_shared_for_overwrite(A const& a)
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return shared_ptr<T>(new T, hamon::default_delete<T>{}, a);
		}
#endif
		shared_ptr<T> ret;
		ret.template ConstructStorage<T>(a, 1);
		return ret;
	}

	template <typename T, hamon::enable_if_t<hamon::is_array<T>::value>* = nullptr, typename A>
	static HAMON_CXX14_CONSTEXPR shared_ptr<T>
	allocate_shared_for_overwrite(A const& a, hamon::size_t N = hamon::extent<T>::value)
	{
		using U = hamon::remove_extent_t<T>;
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return shared_ptr<T>(new U[N], hamon::default_delete<U[]>{}, a);
		}
#endif
		shared_ptr<T> ret;
		ret.template ConstructStorage<U>(a, N);
		return ret;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SP_ACCESS_HPP
