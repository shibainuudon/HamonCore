/**
 *	@file	regular.hpp
 *
 *	@brief	regular の定義
 */

#ifndef HAMON_CONCEPTS_REGULAR_HPP
#define HAMON_CONCEPTS_REGULAR_HPP

#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.6 Object concepts	[concepts.object]

template <typename T>
HAMON_CONCEPT_OR_BOOL regular =
	hamon::semiregular<T> &&
	hamon::equality_comparable<T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_REGULAR_HPP
