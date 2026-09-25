/**
 *	@file	atomic_required_alignment.hpp
 *
 *	@brief	atomic_required_alignment の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REQUIRED_ALIGNMENT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REQUIRED_ALIGNMENT_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
struct atomic_required_alignment
	: public hamon::integral_constant<hamon::size_t,
		alignof(T)
	>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REQUIRED_ALIGNMENT_HPP
