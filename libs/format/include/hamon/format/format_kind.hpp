/**
 *	@file	format_kind.hpp
 *
 *	@brief	format_kind の定義
 */

#ifndef HAMON_FORMAT_FORMAT_KIND_HPP
#define HAMON_FORMAT_FORMAT_KIND_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_kind;

}	// namespace hamon

#else

#include <hamon/format/range_format.hpp>
#include <hamon/format/detail/fmt_pair_like.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

// 28.5.7.1 Variable template format_kind[format.range.fmtkind]

template <typename R>
constexpr hamon::range_format format_kind = hamon::range_format::disabled;// = unspecified;

template <hamon::ranges::input_range R>
	requires hamon::same_as<R, hamon::remove_cvref_t<R>>
constexpr hamon::range_format format_kind<R> = [] {
	// [format.range.fmtkind]/2

	// 2.1 If same_as<remove_cvref_t<ranges::range_reference_t<R>>, R> is true,
	// Otherwise format_kind<R> is range_format::disabled.
	if constexpr (hamon::same_as<hamon::remove_cvref_t<hamon::ranges::range_reference_t<R>>, R>)
	{
		return hamon::range_format::disabled;
	}
	// 2.2 Otherwise, if the qualified-id R::key_type is valid and denotes a type:
	else if constexpr (requires { typename R::key_type; })
	{
		// 2.2.1 If the qualified-id R::mapped_type is valid and denotes a type ...
		if constexpr (requires { typename R::mapped_type; } &&
			// 2.2.1 ... If either U is a specialization of pair or U is a specialization
			// of tuple and tuple_size_v<U> == 2
			hamon::detail::fmt_pair_like<hamon::remove_cvref_t<hamon::ranges::range_reference_t<R>>>)
		{
			return hamon::range_format::map;
		}
		else
		{
			// 2.2.2 Otherwise format_kind<R> is range_format::set.
			return hamon::range_format::set;
		}
	}
	else
	{
		// 2.3 Otherwise, format_kind<R> is range_format::sequence.
		return hamon::range_format::sequence;
	}
}();

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_KIND_HPP
