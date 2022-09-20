/**
 *	@file	save_construct_data.hpp
 *
 *	@brief	save_construct_dataの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_CONSTRUCT_DATA_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_CONSTRUCT_DATA_HPP

#include <hamon/serialization/detail/has_adl_save_construct_data.hpp>
#include <hamon/serialization/detail/get_version.hpp>
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

namespace save_construct_data_detail
{

struct save_construct_data_fn
{
private:
	// save_construct_data(ar, t, version);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_construct_data<Archive&, T const*, version_t>::value>>
	static void impl(Archive& ar, T const* p, version_t version, hamon::detail::overload_priority<2>)
	{
		save_construct_data(ar, p, version);
	}

	// save_construct_data(ar, t);
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_construct_data<Archive&, T const*>::value>>
	static void impl(Archive& ar, T const* p, version_t, hamon::detail::overload_priority<1>)
	{
		save_construct_data(ar, p);
	}

	// fallback
	template <typename Archive, typename T>
	static void impl(Archive&, T const*, version_t, hamon::detail::overload_priority<0>)
	{
		static_assert(always_false<T>::value, "This type has to overload save_construct_data function.");
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const* p) const
	{
		start_save_class(ar);

		version_t const version = hamon::serialization::detail::get_version(*p);

		// version_t を save
		ar << make_nvp("version", version);

		impl(ar, p, version, hamon::detail::overload_priority<2>{});

		end_save_class(ar);
	}
};

}	// namespace save_construct_data_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_construct_data_detail::save_construct_data_fn save_construct_data{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_CONSTRUCT_DATA_HPP
