/**
 *	@file	basic_format_args.hpp
 *
 *	@brief	basic_format_args の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP
#define HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_args;

}	// namespace hamon

#else

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/detail/format_arg_store.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// 28.5.8.3 Class template basic_format_args[format.args]

template <typename Context>
class basic_format_args
{
	hamon::size_t size_;
	hamon::basic_format_arg<Context> const* data_;

	// TODO
	// [format.args]/1
	// An instance of basic_format_args provides access to formatting arguments.
	// Implementations should optimize the representation of basic_format_args for a small number of formatting arguments.
	// [Note 1: For example, by storing indices of type alternatives separately from values and packing the former. — end note]

public:
	template <typename... Args>
	basic_format_args(hamon::detail::format_arg_store<Context, Args...> const& store) noexcept
		// [format.args]/2
		: size_(sizeof...(Args))
		, data_(store.args.data())
	{}

	hamon::basic_format_arg<Context> get(hamon::size_t i) const noexcept
	{
		// [format.args]/3
		return i < size_ ? data_[i] : hamon::basic_format_arg<Context>();
	}

	// TODO:
	size_t __size() const noexcept { return size_; }
};

template <typename Context, typename... Args>
basic_format_args(hamon::detail::format_arg_store<Context, Args...>)
	-> basic_format_args<Context>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP
