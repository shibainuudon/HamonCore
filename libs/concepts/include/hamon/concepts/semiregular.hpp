/**
 *	@file	semiregular.hpp
 *
 *	@brief	semiregular の定義
 */

#ifndef HAMON_CONCEPTS_SEMIREGULAR_HPP
#define HAMON_CONCEPTS_SEMIREGULAR_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.6 Object concepts	[concepts.object]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::semiregular;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL semiregular =
	hamon::copyable<T> &&
	hamon::default_initializable<T>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SEMIREGULAR_HPP
