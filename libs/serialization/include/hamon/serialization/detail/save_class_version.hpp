/**
 *	@file	save_class_version.hpp
 *
 *	@brief	save_class_versionの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_VERSION_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_VERSION_HPP

#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/serialization/detail/get_class_version.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_class_version_detail
{

struct save_class_version_fn
{
private:
	// 
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_class_version<T>::value>>
	static version_t impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		version_t const version = hamon::serialization::detail::get_class_version(t);
		ar << make_nvp("version", version);
		return version;
	}

	// 
	template <typename Archive, typename T>
	static version_t impl(Archive&, T const&, hamon::detail::overload_priority<0>)
	{
		return 0;
	}

public:
	template <typename Archive, typename T>
	version_t operator()(Archive& ar, T const& t) const
	{
		return impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace save_class_version_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_class_version_detail::save_class_version_fn save_class_version{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_VERSION_HPP
