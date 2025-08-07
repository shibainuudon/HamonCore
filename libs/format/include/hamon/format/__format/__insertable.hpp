/**
 *	@file	__insertable.hpp
 *
 *	@brief	__insertable の定義
 */

#ifndef HAMON_FORMAT___FORMAT___INSERTABLE_HPP
#define HAMON_FORMAT___FORMAT___INSERTABLE_HPP

#include <hamon/format/__format/__enable_insertable.hpp>
#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/type_traits/add_pointer.hpp>

namespace hamon
{

namespace __format
{

/// Concept to see whether a \a _Container is insertable.
///
/// The concept is used to validate whether multiple calls to a
/// \ref back_insert_iterator can be replace by a call to \c _Container::insert.
///
/// \note a \a _Container needs to opt-in to the concept by specializing
/// \ref __enable_insertable.
template <class _Container>
concept __insertable =
	__format::__enable_insertable<_Container> &&
	__format::__fmt_char_type<typename _Container::value_type> &&
	requires(_Container& __t,
		hamon::add_pointer_t<typename _Container::value_type> __first,
		hamon::add_pointer_t<typename _Container::value_type> __last)
	{
		__t.insert(__t.end(), __first, __last);
	};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___INSERTABLE_HPP
