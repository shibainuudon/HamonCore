/**
 *	@file	identity.hpp
 *
 *	@brief	identity クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_IDENTITY_HPP
#define HAMON_FUNCTIONAL_IDENTITY_HPP

#include <functional>

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

namespace hamon
{

using std::identity;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

struct identity
{
	template <typename T>
	HAMON_CONSTEXPR T&& operator()(T&& t) const HAMON_NOEXCEPT
	{
		return hamon::forward<T>(t);
	}

	using is_transparent = void;
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_IDENTITY_HPP
