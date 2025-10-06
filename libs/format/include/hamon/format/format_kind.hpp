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
#include <hamon/detail/overload_priority.hpp>

namespace hamon
{

namespace detail
{

// [format.range.fmtkind]/2.1
template <typename R>
	requires hamon::same_as<hamon::remove_cvref_t<hamon::ranges::range_reference_t<R>>, R>
constexpr hamon::range_format get_format_kind_2(hamon::detail::overload_priority<3>)
{
	return hamon::range_format::disabled;
}

// [format.range.fmtkind]/2.2.1
template <typename R,
	typename = typename R::key_type,
	typename = typename R::mapped_type,
	typename = hamon::enable_if<hamon::detail::__fmt_pair_like<hamon::remove_cvref_t<hamon::ranges::range_reference_t<R>>>>
>
constexpr hamon::range_format get_format_kind_2(hamon::detail::overload_priority<2>)
{
	return hamon::range_format::map;
}

// [format.range.fmtkind]/2.2.2
template <typename R,
	typename = typename R::key_type
>
constexpr hamon::range_format get_format_kind_2(hamon::detail::overload_priority<1>)
{
	return hamon::range_format::set;
}

// [format.range.fmtkind]/2.3
template <typename R>
constexpr hamon::range_format get_format_kind_2(hamon::detail::overload_priority<0>)
{
	return hamon::range_format::sequence;
}

// [format.range.fmtkind]/1
// A program that instantiates the primary template of format_kind is ill-formed.
template <typename R>
constexpr hamon::range_format get_format_kind();

// [format.range.fmtkind]/2
template <hamon::ranges::input_range R>
	requires hamon::same_as<R, hamon::remove_cvref_t<R>>
constexpr hamon::range_format get_format_kind()
{
	return get_format_kind_2<R>(hamon::detail::overload_priority<3>{});
}

}	// namespace detail

// 28.5.7.1 Variable template format_kind[format.range.fmtkind]

template <typename R>
constexpr hamon::range_format format_kind = hamon::detail::get_format_kind<R>();

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_KIND_HPP
