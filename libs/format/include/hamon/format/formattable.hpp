/**
 *	@file	formattable.hpp
 *
 *	@brief	formattable の定義
 */

#ifndef HAMON_FORMAT_FORMATTABLE_HPP
#define HAMON_FORMAT_FORMATTABLE_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::formattable;

}	// namespace hamon

#else

#include <hamon/format/detail/formattable_with.hpp>
#include <hamon/format/detail/fmt_iter_for.hpp>
#include <hamon/format/basic_format_context_fwd.hpp>
#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

// 28.5.6.3 Concept formattable[format.formattable]

template <typename T, typename charT>
concept formattable =
	hamon::detail::formattable_with<
		hamon::remove_reference_t<T>,
		hamon::basic_format_context<hamon::detail::fmt_iter_for<charT>, charT>>;

}	// namespace hamon

#include <hamon/format/basic_format_context.hpp>

#endif

#endif // HAMON_FORMAT_FORMATTABLE_HPP
