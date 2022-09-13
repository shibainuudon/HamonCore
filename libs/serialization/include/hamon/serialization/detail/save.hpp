/**
 *	@file	save.hpp
 *
 *	@brief	saveの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_HPP

#include <hamon/serialization/detail/has_adl_save.hpp>
#include <hamon/serialization/detail/serialize_value.hpp>
#include <hamon/serialization/detail/get_version.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/serialization/nvp.hpp>
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

struct save_fn
{
private:
	// t.save(ar, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_save<Archive&, T const&, version_t>::value>>
	static void impl(Archive& ar, T const& t, version_t version, hamon::detail::overload_priority<4>)
	{
		access::save(ar, t, version);
	}

	// t.save(ar);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<access::has_member_save<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, version_t, hamon::detail::overload_priority<3>)
	{
		access::save(ar, t);
	}

	// save(ar, t, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save<Archive&, T const&, version_t>::value>>
	static void impl(Archive& ar, T const& t, version_t version, hamon::detail::overload_priority<2>)
	{
		save(ar, t, version);
	}

	// save(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, version_t, hamon::detail::overload_priority<1>)
	{
		save(ar, t);
	}

	// serialize_value
	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, version_t version, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::serialize_value(ar, t, version);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t, version_t version) const
	{
		impl(ar, t, version, hamon::detail::overload_priority<4>{});
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::save_fn save{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_HPP
