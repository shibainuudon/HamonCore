/**
 *	@file	save_pointer.hpp
 *
 *	@brief	save_pointerの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_POINTER_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_POINTER_HPP

#include <hamon/serialization/detail/get_class_id.hpp>
#include <hamon/serialization/detail/pointer_saver.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_pointer_detail
{

struct save_pointer_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<hamon::is_class<T>::value>>
	static void impl(Archive& ar, T* const& p, hamon::detail::overload_priority<1>)
	{
		hamon::string id = hamon::serialization::detail::get_class_id(*p);
		ar << make_nvp("class_id", id);
		hamon::serialization::detail::pointer_saver<Archive>::get_instance().save(ar, id, p);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T* const& p, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::pointer_saver<Archive>::get_instance().save(ar, "", p);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T* const& p) const
	{
		impl(ar, p, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace save_pointer_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_pointer_detail::save_pointer_fn save_pointer{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_POINTER_HPP
