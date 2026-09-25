/**
 *	@file	atomic_ref_base_general.hpp
 *
 *	@brief	atomic_ref_base_general の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_GENERAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_GENERAL_HPP

#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.1 General[atomics.ref.generic.general]

template <typename T>
struct atomic_ref_base_general
{
public:
	using value_type = hamon::remove_cv_t<T>;

protected:
	constexpr atomic_ref_base_general(T* p)
		: ptr(const_cast<value_type*>(p))
	{}

	template <typename U>
	constexpr atomic_ref_base_general(atomic_ref_base_general<U> const& ref)
		: ptr(ref.ptr)
	{}

protected:
	value_type* ptr;

	template <typename>
	friend struct atomic_ref_base_general;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_GENERAL_HPP
