/**
 *	@file	__basic_format_arg_value.hpp
 *
 *	@brief	__basic_format_arg_value の定義
 */

#ifndef HAMON_FORMAT_DETAIL___BASIC_FORMAT_ARG_VALUE_HPP
#define HAMON_FORMAT_DETAIL___BASIC_FORMAT_ARG_VALUE_HPP

#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/detail/formattable_with.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/string_view.hpp>
#include <hamon/variant.hpp>

namespace hamon
{

namespace detail
{

/// Contains the values used in basic_format_arg.
///
/// This is a separate type so it's possible to store the values and types in
/// separate arrays.
template <class _Context>
class __basic_format_arg_value
{
	using _CharT = typename _Context::char_type;

public:
	/// Contains the implementation for basic_format_arg::handle.
	struct __handle
	{
		template <class _Tp>
		explicit __handle(_Tp& __v) noexcept
			: __ptr_(hamon::addressof(__v)),
			__format_([](hamon::basic_format_parse_context<_CharT>& __parse_ctx, _Context& __ctx, const void* __ptr) {
			using _Dp = hamon::remove_const_t<_Tp>;
			using _Qp = hamon::conditional_t<hamon::detail::formattable_with<const _Dp, _Context>, const _Dp, _Dp>;
			static_assert(hamon::detail::formattable_with<_Qp, _Context>, "Mandated by [format.arg]/10");

			typename _Context::template formatter_type<_Dp> __f;
			__parse_ctx.advance_to(__f.parse(__parse_ctx));
			__ctx.advance_to(__f.format(*const_cast<_Qp*>(static_cast<const _Dp*>(__ptr)), __ctx));
			})
		{}

		const void* __ptr_;
		void (*__format_)(hamon::basic_format_parse_context<_CharT>&, _Context&, const void*);
	};

	union
	{
		hamon::monostate __monostate_;
		bool __boolean_;
		_CharT __char_type_;
		int __int_;
		unsigned __unsigned_;
		long long __long_long_;
		unsigned long long __unsigned_long_long_;
#  if _LIBCPP_HAS_INT128
		__int128_t __i128_;
		__uint128_t __u128_;
#  endif
		float __float_;
		double __double_;
		long double __long_double_;
		const _CharT* __const_char_type_ptr_;
		hamon::basic_string_view<_CharT> __string_view_;
		const void* __ptr_;
		__handle __handle_;
	};

	// These constructors contain the exact storage type used. If adjustments are
	// required, these will be done in __create_format_arg.

	__basic_format_arg_value() noexcept : __monostate_() {}
	__basic_format_arg_value(bool __value) noexcept : __boolean_(__value) {}
	__basic_format_arg_value(_CharT __value) noexcept : __char_type_(__value) {}
	__basic_format_arg_value(int __value) noexcept : __int_(__value) {}
	__basic_format_arg_value(unsigned __value) noexcept : __unsigned_(__value) {}
	__basic_format_arg_value(long long __value) noexcept : __long_long_(__value) {}
	__basic_format_arg_value(unsigned long long __value) noexcept
		: __unsigned_long_long_(__value) {}
#  if _LIBCPP_HAS_INT128
	__basic_format_arg_value(__int128_t __value) noexcept : __i128_(__value) {}
	__basic_format_arg_value(__uint128_t __value) noexcept : __u128_(__value) {}
#  endif
	__basic_format_arg_value(float __value) noexcept : __float_(__value) {}
	__basic_format_arg_value(double __value) noexcept : __double_(__value) {}
	__basic_format_arg_value(long double __value) noexcept : __long_double_(__value) {}
	__basic_format_arg_value(const _CharT* __value) noexcept : __const_char_type_ptr_(__value) {}
	__basic_format_arg_value(hamon::basic_string_view<_CharT> __value) noexcept
		: __string_view_(__value) {}
	__basic_format_arg_value(const void* __value) noexcept : __ptr_(__value) {}
	__basic_format_arg_value(__handle&& __value) noexcept : __handle_(std::move(__value)) {}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL___BASIC_FORMAT_ARG_VALUE_HPP
