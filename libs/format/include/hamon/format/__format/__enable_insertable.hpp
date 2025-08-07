/**
 *	@file	__enable_insertable.hpp
 *
 *	@brief	__enable_insertable の定義
 */

#ifndef HAMON_FORMAT___FORMAT___ENABLE_INSERTABLE_HPP
#define HAMON_FORMAT___FORMAT___ENABLE_INSERTABLE_HPP


namespace hamon
{

namespace __format
{

/// Opt-in to enable \ref __insertable for a \a _Container.
template <class _Container>
inline constexpr bool __enable_insertable = false;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___ENABLE_INSERTABLE_HPP
