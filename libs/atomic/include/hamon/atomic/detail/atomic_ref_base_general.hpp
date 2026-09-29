/**
 *	@file	atomic_ref_base_general.hpp
 *
 *	@brief	atomic_ref_base_general の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_GENERAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_GENERAL_HPP

#include <hamon/atomic/detail/atomic_ref_base_common.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.1 General[atomics.ref.generic.general]

template <typename T>
struct atomic_ref_base_general : public hamon::detail::atomic_ref_base_common<T>
{
private:
	using base = hamon::detail::atomic_ref_base_common<T>;
	using base::base;

public:
	using value_type = typename base::value_type;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_GENERAL_HPP
