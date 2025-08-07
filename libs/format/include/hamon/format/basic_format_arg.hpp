/**
 *	@file	basic_format_arg.hpp
 *
 *	@brief	basic_format_arg の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_ARG_HPP
#define HAMON_FORMAT_BASIC_FORMAT_ARG_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_arg;

}	// namespace hamon

#else

//#include <hamon/format/basic_format_parse_context.hpp>
//#include <hamon/format/detail/formattable_with.hpp>
//#include <hamon/format/detail/is_signed_integer.hpp>
//#include <hamon/format/detail/is_unsigned_integer.hpp>
//#include <hamon/format/detail/is_standard_floating_point.hpp>
//#include <hamon/memory/addressof.hpp>
//#include <hamon/string_view.hpp>
//#include <hamon/string_view/detail/is_specialization_of_basic_string_view.hpp>
//#include <hamon/string/detail/is_specialization_of_basic_string.hpp>
//#include <hamon/type_traits/conditional.hpp>
//#include <hamon/type_traits/decay.hpp>
//#include <hamon/type_traits/is_null_pointer.hpp>
//#include <hamon/type_traits/is_same.hpp>
//#include <hamon/type_traits/is_void.hpp>
//#include <hamon/type_traits/remove_const.hpp>
//#include <hamon/type_traits/remove_pointer.hpp>
//#include <hamon/utility/forward.hpp>
//#include <hamon/variant.hpp>

#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/detail/__basic_format_arg_value.hpp>
#include <hamon/format/other/__visit_format_arg.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

#if 0

// 28.5.8.1 Class template basic_format_arg[format.arg]

template <typename Context>
class basic_format_arg
{
private:
	using char_type = typename Context::char_type;

public:
	class handle
	{
		const void* ptr_;

		void (*format_)(hamon::basic_format_parse_context<char_type>&, Context&, const void*);

		template <typename T>
		explicit handle(T& val) noexcept
			// [format.arg]/13
			: ptr_(hamon::addressof(val))
			, format_([](hamon::basic_format_parse_context<char_type>& parse_ctx, Context& format_ctx, const void* ptr)
				{
					// [format.arg]/11.1
					using TD = hamon::remove_const_t<T>;
					// [format.arg]/11.2
					using TQ = hamon::conditional_t<hamon::detail::formattable_with<const TD, Context>, const TD, TD>;
					// [format.arg]/12
					static_assert(hamon::detail::formattable_with<TQ, Context>, "");

					typename Context::template formatter_type<TD> f;
					parse_ctx.advance_to(f.parse(parse_ctx));
					format_ctx.advance_to(f.format(*const_cast<TQ*>(static_cast<const TD*>(ptr)), format_ctx));
				})
		{}

	public:
		void format(hamon::basic_format_parse_context<char_type>& parse_ctx, Context& format_ctx) const
		{
			// [format.arg]/14
			format_(parse_ctx, format_ctx, ptr_);
		}
	};

private:
	hamon::variant<
		hamon::monostate, bool, char_type,
		int, unsigned int, long long int, unsigned long long int,
		float, double, long double,
		const char_type*, hamon::basic_string_view<char_type>,
		const void*, handle> value;

public:	// TODO
	template <typename T>
	requires hamon::detail::formattable_with<T, Context>	// [format.arg]/4
	explicit basic_format_arg(T& v) noexcept
	{
		// [format.arg]/6
		using TD = hamon::remove_const_t<T>;

		// [format.arg]/6.1
		if constexpr (hamon::is_same<TD, bool>::value || hamon::is_same<TD, char_type>::value)
		{
			value = v;
		}
		// [format.arg]/6.2
		else if constexpr (hamon::is_same<TD, char>::value && hamon::is_same<char_type, wchar_t>::value)
		{
			value = static_cast<wchar_t>(static_cast<unsigned char>(v));
		}
		// [format.arg]/6.3
		else if constexpr (hamon::detail::is_signed_integer<TD>::value && (sizeof(TD) <= sizeof(int)))
		{
			value = static_cast<int>(v);
		}
		// [format.arg]/6.4
		else if constexpr (hamon::detail::is_unsigned_integer<TD>::value && (sizeof(TD) <= sizeof(unsigned int)))
		{
			value = static_cast<unsigned int>(v);
		}
		// [format.arg]/6.5
		else if constexpr (hamon::detail::is_signed_integer<TD>::value && (sizeof(TD) <= sizeof(long long int)))
		{
			value = static_cast<long long int>(v);
		}
		// [format.arg]/6.6
		else if constexpr (hamon::detail::is_unsigned_integer<TD>::value && (sizeof(TD) <= sizeof(unsigned long long int)))
		{
			value = static_cast<unsigned long long int>(v);
		}
		// [format.arg]/6.7
		else if constexpr (hamon::detail::is_standard_floating_point<TD>::value)
		{
			value = v;
		}
		// [format.arg]/6.8
		else if constexpr (
			(hamon::detail::is_specialization_of_basic_string_view<TD>::value ||
			 hamon::detail::is_specialization_of_basic_string<TD>::value) &&
			hamon::is_same<TD::value_type, char_type>::value)
		{
			value = hamon::basic_string_view<char_type>(v.data(), v.size());
		}
		// [format.arg]/6.9
		else if constexpr (
			hamon::is_same<hamon::decay_t<TD>, char_type*>::value ||
			hamon::is_same<hamon::decay_t<TD>, const char_type*>::value)
		{
			value = static_cast<const char_type*>(v);
		}
		// [format.arg]/6.10
		else if constexpr (
			hamon::is_void<hamon::remove_pointer_t<TD>>::value ||
			hamon::is_null_pointer<TD>::value)
		{
			value = static_cast<const void*>(v);
		}
		// [format.arg]/6.11
		else
		{
			value = handle(v);
		}
	}

public:
	basic_format_arg() noexcept
		// [format.arg]/3
		: value()//hamon::monostate)
	{}

	explicit operator bool() const noexcept
	{
		// [format.arg]/7
		return !hamon::holds_alternative<hamon::monostate>(value);
	}

#if 0	// TODO
	template <typename Visitor>
	decltype(auto) visit(this basic_format_arg arg, Visitor&& vis)
	{
		// [format.arg]/8
		return arg.value.visit(hamon::forward<Visitor>(vis));
	}

	template <typename R, typename Visitor>
	R visit(this basic_format_arg arg, Visitor&& vis)
	{
		// [format.arg]/9
		return arg.value.visit<R>(hamon::forward<Visitor>(vis));
	}
#endif
};

#endif

template <class _Context>
class basic_format_arg
{
public:
	class handle;

	basic_format_arg() noexcept : __type_ {__format::__arg_t::__none} {}

	explicit operator bool() const noexcept { return __type_ != __format::__arg_t::__none; }

#  if defined(HAMON_HAS_CXX23_EXPLICIT_THIS_PARAMETER)//_LIBCPP_STD_VER >= 26 && _LIBCPP_HAS_EXPLICIT_THIS_PARAMETER

	// This function is user facing, so it must wrap the non-standard types of
	// the "variant" in a handle to stay conforming. See __arg_t for more details.
	template <class _Visitor>
	decltype(auto) visit(this basic_format_arg __arg, _Visitor&& __vis)
	{
//		switch (__arg.__type_)
		{
//#    if _LIBCPP_HAS_INT128
//		case __format::__arg_t::__i128: {
//				typename hamon::detail::__basic_format_arg_value<_Context>::__handle __h {__arg.__value_.__i128_};
//				return std::invoke(std::forward<_Visitor>(__vis), typename basic_format_arg<_Context>::handle {__h});
//			}
//
//		case __format::__arg_t::__u128: {
//				typename hamon::detail::__basic_format_arg_value<_Context>::__handle __h {__arg.__value_.__u128_};
//				return std::invoke(std::forward<_Visitor>(__vis), typename basic_format_arg<_Context>::handle {__h});
//			}
//#    endif
//		default:
			return hamon::__visit_format_arg(hamon::forward<_Visitor>(__vis), __arg);
		}
	}

	// This function is user facing, so it must wrap the non-standard types of
	// the "variant" in a handle to stay conforming. See __arg_t for more details.
	template <class _Rp, class _Visitor>
	_Rp visit(this basic_format_arg __arg, _Visitor&& __vis)
	{
//		switch (__arg.__type_)
		{
//#    if _LIBCPP_HAS_INT128
//		case __format::__arg_t::__i128: {
//				typename hamon::detail::__basic_format_arg_value<_Context>::__handle __h {__arg.__value_.__i128_};
//				return std::invoke_r<_Rp>(std::forward<_Visitor>(__vis), typename basic_format_arg<_Context>::handle {__h});
//			}
//
//		case __format::__arg_t::__u128: {
//				typename hamon::detail::__basic_format_arg_value<_Context>::__handle __h {__arg.__value_.__u128_};
//				return std::invoke_r<_Rp>(std::forward<_Visitor>(__vis), typename basic_format_arg<_Context>::handle {__h});
//			}
//#    endif
//		default:
			return hamon::__visit_format_arg<_Rp>(hamon::forward<_Visitor>(__vis), __arg);
		}
	}

#else

	template <class _Visitor>
	decltype(auto) visit(_Visitor&& __vis)
	{
		return hamon::__visit_format_arg(hamon::forward<_Visitor>(__vis), *this);
	}

	// This function is user facing, so it must wrap the non-standard types of
	// the "variant" in a handle to stay conforming. See __arg_t for more details.
	template <class _Rp, class _Visitor>
	_Rp visit(_Visitor&& __vis)
	{
		return hamon::__visit_format_arg<_Rp>(hamon::forward<_Visitor>(__vis), *this);
	}

#  endif // _LIBCPP_STD_VER >= 26 && _LIBCPP_HAS_EXPLICIT_THIS_PARAMETER

private:
	using char_type = typename _Context::char_type;

	// TODO FMT Implement constrain [format.arg]/4
	// Constraints: The template specialization
	//   typename Context::template formatter_type<T>
	// meets the Formatter requirements ([formatter.requirements]).  The extent
	// to which an implementation determines that the specialization meets the
	// Formatter requirements is unspecified, except that as a minimum the
	// expression
	//   typename Context::template formatter_type<T>()
	//    .format(declval<const T&>(), declval<Context&>())
	// shall be well-formed when treated as an unevaluated operand.

public:
	hamon::detail::__basic_format_arg_value<_Context> __value_;
	__format::__arg_t __type_;

	explicit basic_format_arg(__format::__arg_t __type, hamon::detail::__basic_format_arg_value<_Context> __value) noexcept
		: __value_(__value), __type_(__type) {}
};

template <class _Context>
class basic_format_arg<_Context>::handle
{
public:
	void format(hamon::basic_format_parse_context<char_type>& __parse_ctx, _Context& __ctx) const
	{
		__handle_.__format_(__parse_ctx, __ctx, __handle_.__ptr_);
	}

	explicit handle(typename hamon::detail::__basic_format_arg_value<_Context>::__handle& __handle) noexcept
		: __handle_(__handle) {}

private:
	typename hamon::detail::__basic_format_arg_value<_Context>::__handle& __handle_;
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_ARG_HPP
