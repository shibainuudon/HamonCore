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

//#include <hamon/format/basic_format_arg.hpp>
//#include <hamon/format/detail/format_arg_store.hpp>
//#include <hamon/cstddef/size_t.hpp>

#include <hamon/format/detail/format_arg_store.hpp>
#include <hamon/format/detail/__basic_format_arg_value.hpp>
#include <hamon/format/__format/__use_packed_format_arg_store.hpp>
#include <hamon/format/__format/__get_packed_type.hpp>
#include <hamon/format/basic_format_arg.hpp>

namespace hamon
{

#if 0

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
};

template <typename Context, typename... Args>
basic_format_args(hamon::detail::format_arg_store<Context, Args...>)
	-> basic_format_args<Context>;

#endif

template <class _Context>
class basic_format_args
{
public:
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4100)	// 引数は関数の本体部で 1 度も参照されません。
	template <class... _Args>
	basic_format_args(const hamon::detail::format_arg_store<_Context, _Args...>& __store) noexcept
		: __size_(sizeof...(_Args))
	{
		if constexpr (sizeof...(_Args) != 0)
		{
			if constexpr (__format::__use_packed_format_arg_store(sizeof...(_Args)))
			{
				__values_ = __store.__storage.__values_;
				__types_  = __store.__storage.__types_;
			}
			else
			{
				__args_ = __store.__storage.__args_;
			}
		}
	}
HAMON_WARNING_POP()

	hamon::basic_format_arg<_Context> get(size_t __id) const noexcept
	{
		if (__id >= __size_)
		{
			return hamon::basic_format_arg<_Context>{};
		}

		if (__format::__use_packed_format_arg_store(__size_))
		{
			return hamon::basic_format_arg<_Context>{__format::__get_packed_type(__types_, __id), __values_[__id]};
		}

		return __args_[__id];
	}

	size_t __size() const noexcept { return __size_; }

private:
	size_t __size_ {0};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4201)	// 非標準の拡張機能が使用されています: 無名の構造体または共用体です。
HAMON_WARNING_DISABLE_GCC("-Wpedantic")
HAMON_WARNING_DISABLE_CLANG("-Wgnu-anonymous-struct")
HAMON_WARNING_DISABLE_CLANG("-Wnested-anon-types")

	// [format.args]/5
	// [Note 1: Implementations are encouraged to optimize the representation of
	// basic_format_args for small number of formatting arguments by storing
	// indices of type alternatives separately from values and packing the
	// former. - end note]
	union {
		struct {
			const hamon::detail::__basic_format_arg_value<_Context>* __values_;
			uint64_t __types_;
		};
		const hamon::basic_format_arg<_Context>* __args_;
	};

HAMON_WARNING_POP()
};

template <class _Context, class... _Args>
basic_format_args(hamon::detail::format_arg_store<_Context, _Args...>) -> basic_format_args<_Context>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP
