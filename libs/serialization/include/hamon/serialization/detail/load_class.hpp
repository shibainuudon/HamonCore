/**
 *	@file	load_class.hpp
 *
 *	@brief	load_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP

#include <hamon/serialization/detail/has_adl_load_class.hpp>
#include <hamon/serialization/detail/load.hpp>
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

template <typename Archive>
void start_load_class(Archive&)
{
}

template <typename Archive>
void end_load_class(Archive&)
{
}

struct load_class_fn
{
private:
	// load_class(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_class<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		load_class(ar, t);
	}

	// default
	template <typename Archive, typename T>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<0>)
	{
		start_load_class(ar);

		version_t version{};

		// version_t を load
		ar >> make_nvp("version", version);

		hamon::serialization::load(ar, t, version);

		end_load_class(ar);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::load_class_fn load_class{};

}	// inline namespace cpo

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_CLASS_HPP
