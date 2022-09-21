/**
 *	@file	save_vector.hpp
 *
 *	@brief	save_vectorの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_VECTOR_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_VECTOR_HPP

#include <hamon/serialization/detail/has_adl_save_vector.hpp>
#include <hamon/serialization/detail/save_array.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_vector_detail
{

struct save_vector_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_vector<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		save_vector(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<0>)
	{
		ar << t.size();
		hamon::serialization::detail::save_array(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace save_vector_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_vector_detail::save_vector_fn save_vector{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_VECTOR_HPP
