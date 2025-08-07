/**
 *	@file	__back_insert_iterator_container.hpp
 *
 *	@brief	__back_insert_iterator_container の定義
 */

#ifndef HAMON_FORMAT___FORMAT___BACK_INSERT_ITERATOR_CONTAINER_HPP
#define HAMON_FORMAT___FORMAT___BACK_INSERT_ITERATOR_CONTAINER_HPP

#include <hamon/format/__format/__insertable.hpp>
#include <hamon/iterator/back_insert_iterator.hpp>

namespace hamon
{

namespace __format
{

/// Extract the container type of a \ref back_insert_iterator.
template <class _It>
struct __back_insert_iterator_container
{
	using type = void;
};

template <__format::__insertable _Container>
struct __back_insert_iterator_container<hamon::back_insert_iterator<_Container>>
{
	using type = _Container;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___BACK_INSERT_ITERATOR_CONTAINER_HPP
