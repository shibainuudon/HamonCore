/**
 *	@file	expected_fwd.hpp
 *
 *	@brief	expected の前方宣言
 */

#ifndef HAMON_EXPECTED_EXPECTED_FWD_HPP
#define HAMON_EXPECTED_EXPECTED_FWD_HPP

#include <hamon/expected/config.hpp>

#if defined(HAMON_USE_STD_EXPECTED)

#include <expected>

namespace hamon
{

using std::expected;

}	// namespace hamon

#else

#if !defined(HAMON_HAS_CXX20_CONCEPTS)
#include <hamon/type_traits/is_void.hpp>
#endif

namespace hamon
{

// [expected.expected], class template expected
template <typename T, typename E
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, bool = hamon::is_void<T>::value
#endif
>
class expected;

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_EXPECTED_FWD_HPP
