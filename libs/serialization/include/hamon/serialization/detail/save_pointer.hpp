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
#include <hamon/config.hpp>
#include <type_traits>

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
		typename = hamon::enable_if_t<std::is_class<T>::value>>
	static void impl(Archive& ar, T* const& t, hamon::detail::overload_priority<1>)
	{
		std::string s = hamon::serialization::detail::get_class_id(*t);
		ar << make_nvp("class_id", s);
		hamon::serialization::detail::pointer_saver<Archive>::get_instance().save(ar, s, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T* const& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::pointer_saver<Archive>::get_instance().save(ar, "", t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T* const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
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
