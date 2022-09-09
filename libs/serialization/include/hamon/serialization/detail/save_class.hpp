/**
 *	@file	save_class.hpp
 *
 *	@brief	save_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP

#include <hamon/serialization/detail/has_adl_save_class.hpp>
#include <hamon/serialization/detail/has_adl_save.hpp>
#include <hamon/serialization/detail/serialize_value.hpp>
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

struct save_class_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_class<Archive, T>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<2>)
	{
		save_class(ar, t);
	}

	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		save(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::serialize_value(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<2>{});
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::save_class_fn save_class{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP
