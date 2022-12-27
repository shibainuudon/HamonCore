/**
 *	@file	reference_wrapper_fwd.hpp
 *
 *	@brief	reference_wrapper クラステンプレートの前方宣言
 */

#ifndef HAMON_FUNCTIONAL_FWD_REFERENCE_WRAPPER_FWD_HPP
#define HAMON_FUNCTIONAL_FWD_REFERENCE_WRAPPER_FWD_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_REFERENCE_WRAPPER)

namespace hamon
{

using std::reference_wrapper;

}	// namespace hamon

#else

namespace hamon
{

template <typename T>
class reference_wrapper;

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_FWD_REFERENCE_WRAPPER_FWD_HPP
