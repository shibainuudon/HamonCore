/**
 *	@file	load_class_version.hpp
 *
 *	@brief	load_class_versionの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_VERSION_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_VERSION_HPP

#include <hamon/serialization/detail/has_class_version.hpp>
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

namespace load_class_version_detail
{

struct load_class_version_fn
{
private:
	//
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_class_version<T>::value>>
	static version_t impl(Archive& ar, T&, hamon::detail::overload_priority<1>)
	{
		version_t version{};
		ar >> make_nvp("version", version);
		return version;
	}

	//
	template <typename Archive, typename T>
	static version_t impl(Archive&, T&, hamon::detail::overload_priority<0>)
	{
		return 0;
	}

public:
	template <typename Archive, typename T>
	version_t operator()(Archive& ar, T& t) const
	{
		return impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace load_class_version_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_class_version_detail::load_class_version_fn load_class_version{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_VERSION_HPP
