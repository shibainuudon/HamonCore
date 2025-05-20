/**
 *	@file	tags.hpp
 *
 *	@brief
 */

#ifndef HAMON_EXPECTED_DETAIL_TAGS_HPP
#define HAMON_EXPECTED_DETAIL_TAGS_HPP

namespace hamon
{

namespace detail
{

struct expected_ctor_tag{};
struct expected_in_place_invoke_tag {};
struct expected_unexpect_invoke_tag {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_EXPECTED_DETAIL_TAGS_HPP
