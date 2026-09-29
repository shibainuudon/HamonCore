/**
 *	@file	atomic_ref_base_common.hpp
 *
 *	@brief	atomic_ref_base_common の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_COMMON_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_COMMON_HPP

#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
struct atomic_ref_base_common
{
protected:
	using value_type = hamon::remove_cv_t<T>;

	constexpr atomic_ref_base_common(T* p)
		: m_ptr(const_cast<value_type*>(p))
	{}

	template <typename U>
	constexpr atomic_ref_base_common(atomic_ref_base_common<U> const& ref)
		: m_ptr(ref.m_ptr)
	{}

	constexpr value_type* data() const noexcept
	{
		return m_ptr;
	}

private:
	value_type* m_ptr;

	template <typename>
	friend struct atomic_ref_base_common;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_COMMON_HPP
