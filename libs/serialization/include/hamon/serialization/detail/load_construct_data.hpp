/**
 *	@file	load_construct_data.hpp
 *
 *	@brief	load_construct_dataの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_CONSTRUCT_DATA_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_CONSTRUCT_DATA_HPP

#include <hamon/serialization/detail/has_adl_load_construct_data.hpp>
#include <hamon/serialization/detail/load_class_version.hpp>
#include <hamon/serialization/detail/always_false.hpp>
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

namespace load_construct_data_detail
{

struct load_construct_data_fn
{
private:
	// load_construct_data(ar, t, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_construct_data<Archive&, T*, version_t>::value>>
	static void impl(Archive& ar, T* p, version_t version, hamon::detail::overload_priority<2>)
	{
		load_construct_data(ar, p, version);
	}

	// load_construct_data(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_construct_data<Archive&, T*>::value>>
	static void impl(Archive& ar, T* p, version_t, hamon::detail::overload_priority<1>)
	{
		load_construct_data(ar, p);
	}

	// fallback
	template <typename Archive, typename T>
	static void impl(Archive&, T*, version_t, hamon::detail::overload_priority<0>)
	{
		static_assert(always_false<T>::value, "This type has to overload load_construct_data function.");
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T* p) const
	{
		start_load_class(ar);
		auto const version = hamon::serialization::detail::load_class_version(ar, *p);
		impl(ar, p, version, hamon::detail::overload_priority<2>{});
		end_load_class(ar);
	}
};

}	// namespace load_construct_data_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_construct_data_detail::load_construct_data_fn load_construct_data{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_CONSTRUCT_DATA_HPP
