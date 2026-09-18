/**
 *	@file	atomic_base.hpp
 *
 *	@brief	atomic_base の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_HPP

#include <hamon/atomic/detail/atomic_base_general.hpp>
#include <hamon/atomic/detail/atomic_base_integral.hpp>
#include <hamon/atomic/detail/atomic_base_floating_point.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_integral.hpp>

namespace hamon
{
namespace detail
{

template <typename T,
	bool = hamon::is_integral_v<T>,
	bool = hamon::is_floating_point_v<T>
>
struct atomic_base;

// [atomics.types.int]
// [Note 1: The specialization atomic<bool> uses the primary template ([atomics.types.generic]). — end note]
template <>
struct atomic_base<bool>
	: public hamon::detail::atomic_base_general<bool>
{
private:
	using base = hamon::detail::atomic_base_general<bool>;

public:
	using base::base;
	using base::operator=;
};

template <typename T>
struct atomic_base<T, false, false>
	: public hamon::detail::atomic_base_general<T>
{
private:
	using base = hamon::detail::atomic_base_general<T>;

public:
	using base::base;
	using base::operator=;
};

template <typename T>
struct atomic_base<T, true, false>
	: public hamon::detail::atomic_base_integral<T>
{
private:
	using base = hamon::detail::atomic_base_integral<T>;

public:
	using base::base;
	using base::operator=;
};

template <typename T>
struct atomic_base<T, false, true>
	: public hamon::detail::atomic_base_floating_point<T>
{
private:
	using base = hamon::detail::atomic_base_floating_point<T>;

public:
	using base::base;
	using base::operator=;
};

// struct atomic_base<T, true, true> は有り得ない

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_HPP
