/**
 *	@file	atomic_ref_base.hpp
 *
 *	@brief	atomic_ref_base の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_HPP

#include <hamon/atomic/detail/atomic_ref_base_floating_point.hpp>
#include <hamon/atomic/detail/atomic_ref_base_general.hpp>
#include <hamon/atomic/detail/atomic_ref_base_integral.hpp>
#include <hamon/atomic/detail/atomic_ref_base_pointer.hpp>
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
struct atomic_ref_base;

// [atomics.ref.int]
// [Note 1: The specialization atomic_ref<bool> uses the primary template ([atomics.ref.generic]). — end note]
template <>
struct atomic_ref_base<bool>
	: public hamon::detail::atomic_ref_base_general<bool>
{
private:
	using base = hamon::detail::atomic_ref_base_general<bool>;

public:
	using base::base;
	using base::operator=;
};

template <typename T>
struct atomic_ref_base<T, false, false>
	: public hamon::detail::atomic_ref_base_general<T>
{
private:
	using base = hamon::detail::atomic_ref_base_general<T>;

public:
	using base::base;
	using base::operator=;
};

template <typename T>
struct atomic_ref_base<T, true, false>
	: public hamon::detail::atomic_ref_base_integral<T>
{
private:
	using base = hamon::detail::atomic_ref_base_integral<T>;

public:
	using base::base;
	using base::operator=;
};

template <typename T>
struct atomic_ref_base<T, false, true>
	: public hamon::detail::atomic_ref_base_floating_point<T>
{
private:
	using base = hamon::detail::atomic_ref_base_floating_point<T>;

public:
	using base::base;
	using base::operator=;
};

// struct atomic_ref_base<T, true, true> は有り得ない

// Partial specialization for pointers
template <typename T>
struct atomic_ref_base<T*, false, false>
	: public hamon::detail::atomic_ref_base_pointer<T>
{
private:
	using base = hamon::detail::atomic_ref_base_pointer<T>;

public:
	using base::base;
	using base::operator=;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_HPP
