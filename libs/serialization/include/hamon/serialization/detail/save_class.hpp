/**
 *	@file	save_class.hpp
 *
 *	@brief	save_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_CLASS_HPP

#include <hamon/serialization/detail/has_adl_save_class.hpp>
#include <hamon/serialization/detail/save.hpp>
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
	// save_class(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_class<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		save_class(ar, t);
	}

	// default
	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		start_save_class(ar);

		version_t const version = hamon::serialization::detail::get_version(t);

		// version_t を save
		ar << make_nvp("version", version);

		hamon::serialization::detail::save(ar, t, version);

		end_save_class(ar);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<2>{});
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
