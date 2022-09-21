/**
 *	@file	load_vector.hpp
 *
 *	@brief	load_vectorの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_VECTOR_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_VECTOR_HPP

#include <hamon/serialization/detail/has_adl_load_vector.hpp>
#include <hamon/serialization/detail/load_array.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_vector_detail
{

struct load_vector_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_vector<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		load_vector(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<0>)
	{
		std::size_t size;
		ar >> size;

		t.resize(size);
		hamon::serialization::detail::load_array(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace load_vector_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_vector_detail::load_vector_fn load_vector{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_VECTOR_HPP
