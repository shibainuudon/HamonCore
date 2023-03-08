/**
 *	@file	save_array.hpp
 *
 *	@brief	save_arrayの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_ARRAY_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_ARRAY_HPP

#include <hamon/serialization/detail/has_adl_save_array.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_array_detail
{

struct save_array_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_array<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		save_array(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		for (auto const& x : t)
		{
			ar << x;
		}
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace save_array_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_array_detail::save_array_fn save_array{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_ARRAY_HPP
