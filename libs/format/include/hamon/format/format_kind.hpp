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
#include <hamon/format/detail/__fmt_pair_like.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

// 28.5.7.1 Variable template format_kind[format.range.fmtkind]

template <class _Rp>
constexpr hamon::range_format format_kind = [] {
	// [format.range.fmtkind]/1
	// A program that instantiates the primary template of format_kind is ill-formed.
	static_assert(sizeof(_Rp) != sizeof(_Rp), "create a template specialization of format_kind for your type");
	return hamon::range_format::disabled;
}();

template <hamon::ranges::input_range _Rp>
	requires hamon::same_as<_Rp, hamon::remove_cvref_t<_Rp>>
inline constexpr hamon::range_format format_kind<_Rp> = [] {
	// [format.range.fmtkind]/2

	// 2.1 If same_as<remove_cvref_t<ranges::range_reference_t<R>>, R> is true,
	// Otherwise format_kind<R> is range_format::disabled.
	if constexpr (hamon::same_as<hamon::remove_cvref_t<hamon::ranges::range_reference_t<_Rp>>, _Rp>)
	{
		return hamon::range_format::disabled;
	}
	// 2.2 Otherwise, if the qualified-id R::key_type is valid and denotes a type:
	else if constexpr (requires { typename _Rp::key_type; })
	{
		// 2.2.1 If the qualified-id R::mapped_type is valid and denotes a type ...
		if constexpr (requires { typename _Rp::mapped_type; } &&
			// 2.2.1 ... If either U is a specialization of pair or U is a specialization
			// of tuple and tuple_size_v<U> == 2
			hamon::detail::__fmt_pair_like<hamon::remove_cvref_t<hamon::ranges::range_reference_t<_Rp>>>)
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
