/**
 *	@file	insert_return_type.hpp
 *
 *	@brief	insert_return_type の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_INSERT_RETURN_TYPE_HPP
#define HAMON_CONTAINER_DETAIL_INSERT_RETURN_TYPE_HPP

namespace hamon
{

namespace detail
{

// 23.2.6 Insert return type[container.insert.return]

template <typename Iterator, typename NodeType>
struct insert_return_type
{
	Iterator position;
	bool     inserted;
	NodeType node;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_INSERT_RETURN_TYPE_HPP
