/**
 *	@file	__substitute_arg_id.hpp
 *
 *	@brief	__substitute_arg_id の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___SUBSTITUTE_ARG_ID_HPP
#define HAMON_FORMAT___FORMAT_SPEC___SUBSTITUTE_ARG_ID_HPP

#include <hamon/format/__format/__number_max.hpp>
#include <hamon/format/other/__visit_format_arg.hpp>
#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/variant.hpp>

namespace hamon
{

namespace __format_spec
{

template <class _Context>
constexpr uint32_t __substitute_arg_id(hamon::basic_format_arg<_Context> __format_arg)
{
	// [format.string.std]/8
	//   If the corresponding formatting argument is not of integral type...
	// This wording allows char and bool too. LWG-3720 changes the wording to
	//    If the corresponding formatting argument is not of standard signed or
	//    unsigned integer type,
	// This means the 128-bit will not be valid anymore.
	// TODO FMT Verify this resolution is accepted and add a test to verify
	//          128-bit integrals fail and switch to visit_format_arg.
	return hamon::__visit_format_arg(
		[](auto __arg) -> uint32_t {
			  using _Type = decltype(__arg);
			  if constexpr (hamon::same_as<_Type, hamon::monostate>)
			  {
				  hamon::detail::throw_format_error("The argument index value is too large for the number of arguments supplied");
			  }

			  // [format.string.std]/8
			  // If { arg-idopt } is used in a width or precision, the value of the
			  // corresponding formatting argument is used in its place. If the
			  // corresponding formatting argument is not of standard signed or unsigned
			  // integer type, or its value is negative for precision or non-positive for
			  // width, an exception of type format_error is thrown.
			  //
			  // When an integral is used in a format function, it is stored as one of
			  // the types checked below. Other integral types are promoted. For example,
			  // a signed char is stored as an int.
			  if constexpr (hamon::same_as<_Type, int> || hamon::same_as<_Type, unsigned int> || //
							hamon::same_as<_Type, long long> || hamon::same_as<_Type, unsigned long long>)
			  {
				  if constexpr (hamon::signed_integral<_Type>)
				  {
					  if (__arg < 0)
					  {
						  hamon::detail::throw_format_error("An argument index may not have a negative value");
					  }
				  }

				  using _CT = hamon::common_type_t<_Type, decltype(__format::__number_max)>;
				  if (static_cast<_CT>(__arg) > static_cast<_CT>(__format::__number_max))
				  {
					  hamon::detail::throw_format_error("The value of the argument index exceeds its maximum value");
				  }

				  return __arg;
			  }
			  else
			  {
				  hamon::detail::throw_format_error("Replacement argument isn't a standard signed or unsigned integer type");
			  }
		},
		__format_arg);
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___SUBSTITUTE_ARG_ID_HPP
