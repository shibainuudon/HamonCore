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
#include <type_traits>

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
		typename = hamon::enable_if_t<has_adl_save_array<Archive&, T const&, std::size_t>::value>>
	static void impl(Archive& ar, T const& t, std::size_t size, hamon::detail::overload_priority<1>)
	{
		save_array(ar, t, size);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, std::size_t size, hamon::detail::overload_priority<0>)
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			ar << t[i];
		}
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t, std::size_t size) const
	{
		impl(ar, t, size, hamon::detail::overload_priority<1>{});
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
