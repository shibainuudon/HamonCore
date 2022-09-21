/**
 *	@file	save_class.hpp
 *
 *	@brief	save_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP

#include <hamon/serialization/detail/has_adl_save.hpp>
#include <hamon/serialization/detail/serialize_value.hpp>
#include <hamon/serialization/detail/save_class_version.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive>
void start_save_class(Archive&)
{
}

template <typename Archive>
void end_save_class(Archive&)
{
}

namespace save_class_detail
{

struct save_class_fn
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
		hamon::serialization::detail::serialize_value(ar, t, version);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		start_save_class(ar);
		auto const version = hamon::serialization::detail::save_class_version(ar, t);
		impl(ar, t, version, hamon::detail::overload_priority<4>{});
		end_save_class(ar);
	}
};

}	// namespace save_class_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR save_class_detail::save_class_fn save_class{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP
