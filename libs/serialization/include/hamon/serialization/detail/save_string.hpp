/**
 *	@file	save_string.hpp
 *
 *	@brief	save_stringの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_STRING_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_STRING_HPP

#include <hamon/serialization/detail/has_adl_save_string.hpp>
#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_string_detail
{

struct save_string_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_string<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		save_string(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::save_vector(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace save_string_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_string_detail::save_string_fn save_string{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_STRING_HPP
