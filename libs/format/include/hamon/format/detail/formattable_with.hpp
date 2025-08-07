/**
 *	@file	formattable_with.hpp
 *
 *	@brief	formattable_with の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FORMATTABLE_WITH_HPP
#define HAMON_FORMAT_DETAIL_FORMATTABLE_WITH_HPP

#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/type_traits/remove_const.hpp>

namespace hamon
{

namespace detail
{

// 28.5.6.3 Concept formattable[format.formattable]

template <
	typename T,
	typename Context,
	typename Formatter = typename Context::template formatter_type<hamon::remove_const_t<T>>>
concept formattable_with =
	hamon::semiregular<Formatter> &&
	requires(Formatter& f, const Formatter& cf, T&& t, Context fc,
		hamon::basic_format_parse_context<typename Context::char_type> pc)
	{
		{ f.parse(pc) } -> hamon::same_as<typename decltype(pc)::iterator>;
		{ cf.format(t, fc) } -> hamon::same_as<typename Context::iterator>;
	};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FORMATTABLE_WITH_HPP
