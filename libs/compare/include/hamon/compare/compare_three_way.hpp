/**
 *	@file	compare_three_way.hpp
 *
 *	@brief	compare_three_way の定義
 */

#ifndef HAMON_COMPARE_COMPARE_THREE_WAY_HPP
#define HAMON_COMPARE_COMPARE_THREE_WAY_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::compare_three_way;

}	// namespace hamon

#else	// defined(HAMON_USE_STD_COMPARE)

#include <hamon/compare/detail/builtin_ptr_three_way.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

struct compare_three_way
{
	template <typename T, typename U>
	requires hamon::three_way_comparable_with<T, U> || detail::builtin_ptr_three_way<T, U>
	constexpr auto operator()(T&& t, U&& u) const
		noexcept(noexcept(hamon::declval<T>() <=> hamon::declval<U>()))
	{
		if constexpr (detail::builtin_ptr_three_way<T, U>)
		{
			auto pt = static_cast<void const volatile*>(t);
			auto pu = static_cast<void const volatile*>(u);

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
			if (hamon::is_constant_evaluated())
			{
				return pt <=> pu;
			}
#endif
			auto it = reinterpret_cast<hamon::uintptr_t>(pt);
			auto iu = reinterpret_cast<hamon::uintptr_t>(pu);
			return it <=> iu;
		}
		else
		{
			return static_cast<T&&>(t) <=> static_cast<U&&>(u);
		}
	}

	using is_transparent = void;
};

}	// namespace hamon

#endif	// defined(HAMON_USE_STD_COMPARE)

#endif	// defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // HAMON_COMPARE_COMPARE_THREE_WAY_HPP
