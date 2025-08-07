/**
 *	@file	__parser.hpp
 *
 *	@brief	__parser の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PARSER_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PARSER_HPP

#include <hamon/format/__format_spec/__throw_invalid_option_format_error.hpp>
#include <hamon/format/__format_spec/__throw_invalid_type_format_error.hpp>
#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__create_type_mask.hpp>
#include <hamon/format/__format_spec/__parse_arg_id.hpp>
#include <hamon/format/__format_spec/__substitute_arg_id.hpp>
#include <hamon/format/other/__unicode.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/algorithm/copy_n.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/memory/addressof.hpp>

namespace hamon
{

namespace __format_spec
{

/// The parser for the std-format-spec.
///
/// Note this class is a member of std::formatter specializations. It's
/// expected developers will create their own formatter specializations that
/// inherit from the std::formatter specializations. This means this class
/// must be ABI stable. To aid the stability the unused bits in the class are
/// set to zero. That way they can be repurposed if a future revision of the
/// Standards adds new fields to std-format-spec.
template <class _CharT>
class __parser
{
public:
	// Parses the format specification.
	//
	// Depending on whether the parsing is done compile-time or run-time
	// the method slightly differs.
	// - Only parses a field when it is in the __fields. Accepting all
	//   fields and then validating the valid ones has a performance impact.
	//   This is faster but gives slighly worse error messages.
	// - At compile-time when a field is not accepted the parser will still
	//   parse it and give an error when it's present. This gives a more
	//   accurate error.
	// The idea is that most times the format instead of the vformat
	// functions are used. In that case the error will be detected during
	// compilation and there is no need to pay for the run-time overhead.
	template <class _ParseContext>
	constexpr typename _ParseContext::iterator
	__parse(_ParseContext& __ctx, __fields __fields)
	{
		auto __begin = __ctx.begin();
		auto __end   = __ctx.end();
		if (__begin == __end || *__begin == _CharT('}') || (__fields.__use_range_fill_ && *__begin == _CharT(':')))
		{
			return __begin;
		}

		if (__parse_fill_align(__begin, __end) && __begin == __end)
		{
			return __begin;
		}

		if (__fields.__sign_)
		{
			if (__parse_sign(__begin) && __begin == __end)
			{
				return __begin;
			}
		}
		else if (std::is_constant_evaluated() && __parse_sign(__begin))
		{
			hamon::detail::throw_format_error("The format specification does not allow the sign option");
		}

		if (__fields.__alternate_form_)
		{
			if (__parse_alternate_form(__begin) && __begin == __end)
			{
				return __begin;
			}
		}
		else if (std::is_constant_evaluated() && __parse_alternate_form(__begin))
		{
			hamon::detail::throw_format_error("The format specifier does not allow the alternate form option");
		}

		if (__fields.__zero_padding_)
		{
			if (__parse_zero_padding(__begin) && __begin == __end)
			{
				return __begin;
			}
		}
		else if (std::is_constant_evaluated() && __parse_zero_padding(__begin))
		{
			hamon::detail::throw_format_error("The format specifier does not allow the zero-padding option");
		}

		if (__parse_width(__begin, __end, __ctx) && __begin == __end)
		{
			return __begin;
		}

		if (__fields.__precision_)
		{
			if (__parse_precision(__begin, __end, __ctx) && __begin == __end)
			{
				return __begin;
			}
		}
		else if (std::is_constant_evaluated() && __parse_precision(__begin, __end, __ctx))
		{
			hamon::detail::throw_format_error("The format specifier does not allow the precision option");
		}

		if (__fields.__locale_specific_form_)
		{
			if (__parse_locale_specific_form(__begin) && __begin == __end)
			{
				return __begin;
			}
		}
		else if (std::is_constant_evaluated() && __parse_locale_specific_form(__begin))
		{
			hamon::detail::throw_format_error("The format specifier does not allow the locale-specific form option");
		}

		if (__fields.__clear_brackets_)
		{
			if (__parse_clear_brackets(__begin) && __begin == __end)
			{
				return __begin;
			}
		}
		else if (std::is_constant_evaluated() && __parse_clear_brackets(__begin))
		{
			hamon::detail::throw_format_error("The format specifier does not allow the n option");
		}

		if (__fields.__type_)
		{
			__parse_type(__begin);
		}

		if (!__fields.__consume_all_)
		{
			return __begin;
		}

		if (__begin != __end && *__begin != _CharT('}'))
		{
			hamon::detail::throw_format_error("The format specifier should consume the input or end with a '}'");
		}

		return __begin;
	}

	// Validates the selected the parsed data.
	//
	// The valid fields in the parser may depend on the display type
	// selected. But the type is the last optional field, so by the time
	// it's known an option can't be used, it already has been parsed.
	// This does the validation again.
	//
	// For example an integral may have a sign, zero-padding, or alternate
	// form when the type option is not 'c'. So the generic approach is:
	//
	// typename _ParseContext::iterator __result = __parser_.__parse(__ctx, __format_spec::__fields_integral);
	// if (__parser.__type_ == __format_spec::__type::__char) {
	//   __parser.__validate((__format_spec::__fields_bool, "an integer");
	//   ... // more char adjustments
	// } else {
	//   ... // validate an integral type.
	// }
	//
	// For some types all valid options need a second validation run, like
	// boolean types.
	//
	// Depending on whether the validation is done at compile-time or
	// run-time the error differs
	// - run-time the exception is thrown and contains the type of field
	//   being validated.
	// - at compile-time the line with `hamon::detail::throw_format_error` is shown
	//   in the output. In that case it's important for the error to be on one
	//   line.
	// Note future versions of C++ may allow better compile-time error
	// reporting.
	constexpr void
	__validate(__fields __fields, const char* __id, uint32_t __type_mask = uint32_t(-1)) const
	{
		if (!__fields.__sign_ && __sign_ != __sign::__default)
		{
			if (std::is_constant_evaluated())
			{
				hamon::detail::throw_format_error("The format specifier does not allow the sign option");
			}
			else
			{
				__format_spec::__throw_invalid_option_format_error(__id, "sign");
			}
		}

		if (!__fields.__alternate_form_ && __alternate_form_)
		{
			if (std::is_constant_evaluated())
			{
				hamon::detail::throw_format_error("The format specifier does not allow the alternate form option");
			}
			else
			{
				__format_spec::__throw_invalid_option_format_error(__id, "alternate form");
			}
		}

		if (!__fields.__zero_padding_ && __alignment_ == __alignment::__zero_padding)
		{
			if (std::is_constant_evaluated())
			{
				hamon::detail::throw_format_error("The format specifier does not allow the zero-padding option");
			}
			else
			{
				__format_spec::__throw_invalid_option_format_error(__id, "zero-padding");
			}
		}

		if (!__fields.__precision_ && __precision_ != -1)
		{
			// Works both when the precision has a value or an arg-id.
			if (std::is_constant_evaluated())
			{
				hamon::detail::throw_format_error("The format specifier does not allow the precision option");
			}
			else
			{
				__format_spec::__throw_invalid_option_format_error(__id, "precision");
			}
		}

		if (!__fields.__locale_specific_form_ && __locale_specific_form_)
		{
			if (std::is_constant_evaluated())
			{
				hamon::detail::throw_format_error("The format specifier does not allow the locale-specific form option");
			}
			else
			{
				__format_spec::__throw_invalid_option_format_error(__id, "locale-specific form");
			}
		}

		if ((__create_type_mask(__type_) & __type_mask) == 0)
		{
			if (std::is_constant_evaluated())
			{
				hamon::detail::throw_format_error("The format specifier uses an invalid value for the type option");
			}
			else
			{
				__format_spec::__throw_invalid_type_format_error(__id);
			}
		}
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4101)	// ローカル変数は 1 度も使われていません。

	/// \returns the `__parsed_specifications` with the resolved dynamic sizes..
	__parsed_specifications<_CharT> __get_parsed_std_specifications(auto& __ctx) const
	{
		return __parsed_specifications<_CharT>
		{
			.__std_ =
				__std
				{
					.__alignment_            = __alignment_,
					.__sign_                 = __sign_,
					.__alternate_form_       = __alternate_form_,
					.__locale_specific_form_ = __locale_specific_form_,
					.__type_                 = __type_
				},
				.__width_ {__get_width(__ctx)},
				.__precision_ {__get_precision(__ctx)},
				.__fill_ {__fill_}
		};
	}

HAMON_WARNING_POP()

	__parsed_specifications<_CharT> __get_parsed_chrono_specifications(auto& __ctx) const
	{
		return __parsed_specifications<_CharT>
		{
			.__chrono_ =
				__chrono
				{
					.__alignment_            = __alignment_,
					.__locale_specific_form_ = __locale_specific_form_,
					.__hour_                 = __hour_,
					.__weekday_name_         = __weekday_name_,
					.__weekday_              = __weekday_,
					.__day_of_year_          = __day_of_year_,
					.__week_of_year_         = __week_of_year_,
					.__month_name_           = __month_name_
				},
				.__width_ {__get_width(__ctx)},
				.__precision_ {__get_precision(__ctx)},
				.__fill_ {__fill_}
		};
	}

	__alignment __alignment_     : 3 {__alignment::__default};
	__sign __sign_               : 2 {__sign::__default};
	bool __alternate_form_       : 1 {false};
	bool __locale_specific_form_ : 1 {false};
	bool __clear_brackets_       : 1 {false};
	__type __type_ {__type::__default};

	// These flags are only used for formatting chrono. Since the struct has
	// padding space left it's added to this structure.
	bool __hour_ : 1 {false};

	bool __weekday_name_ : 1 {false};
	bool __weekday_      : 1 {false};

	bool __day_of_year_  : 1 {false};
	bool __week_of_year_ : 1 {false};

	bool __month_name_ : 1 {false};

	uint8_t __reserved_0_ : 2 {0};
	uint8_t __reserved_1_ : 6 {0};
	// These two flags are only used internally and not part of the
	// __parsed_specifications. Therefore put them at the end.
	bool __width_as_arg_     : 1 {false};
	bool __precision_as_arg_ : 1 {false};

	/// The requested width, either the value or the arg-id.
	int32_t __width_ {0};

	/// The requested precision, either the value or the arg-id.
	int32_t __precision_ {-1};

	__code_point<_CharT> __fill_ {};

private:
	constexpr bool __parse_alignment(_CharT __c)
	{
		switch (__c)
		{
		case _CharT('<'):
			__alignment_ = __alignment::__left;
			return true;

		case _CharT('^'):
			__alignment_ = __alignment::__center;
			return true;

		case _CharT('>'):
			__alignment_ = __alignment::__right;
			return true;
		}
		return false;
	}

	constexpr void __validate_fill_character(_CharT __fill)
	{
		// The forbidden fill characters all code points formed from a single code unit, thus the
		// check can be omitted when more code units are used.
		if (__fill == _CharT('{'))
		{
			hamon::detail::throw_format_error("The fill option contains an invalid value");
		}
	}

	// range-fill and tuple-fill are identical
	template <hamon::contiguous_iterator _Iterator>
	requires hamon::same_as<_CharT, char> || (hamon::same_as<_CharT, wchar_t> && sizeof(wchar_t) == 2)
	constexpr bool __parse_fill_align(_Iterator& __begin, _Iterator __end)
	{
		//_LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(
		//	__begin != __end,
		//	"when called with an empty input the function will cause "
		//	"undefined behavior by evaluating data not in the input");
		__unicode::__code_point_view<_CharT> __view {__begin, __end};
		__unicode::__consume_result __consumed = __view.__consume();
		if (__consumed.__status != __unicode::__consume_result::__ok)
		{
			hamon::detail::throw_format_error("The format specifier contains malformed Unicode characters");
		}

		if (__view.__position() < __end && __parse_alignment(*__view.__position()))
		{
			ptrdiff_t __code_units = __view.__position() - __begin;
			if (__code_units == 1)
			{
				// The forbidden fill characters all are code points encoded
				// in one code unit, thus the check can be omitted when more
				// code units are used.
				__validate_fill_character(*__begin);
			}

			hamon::copy_n(__begin, __code_units, hamon::addressof(__fill_.__data[0]));
			__begin += __code_units + 1;
			return true;
		}

		if (!__parse_alignment(*__begin))
		{
			return false;
		}

		++__begin;
		return true;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
	template <hamon::contiguous_iterator _Iterator>
	requires(hamon::same_as<_CharT, wchar_t> && sizeof(wchar_t) == 4)
	constexpr bool __parse_fill_align(_Iterator& __begin, _Iterator __end)
	{
		//_LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(
		//	__begin != __end,
		//	"when called with an empty input the function will cause "
		//	"undefined behavior by evaluating data not in the input");
		if (__begin + 1 != __end && __parse_alignment(*(__begin + 1)))
		{
			if (!__unicode::__is_scalar_value(*__begin))
			{
				hamon::detail::throw_format_error("The fill option contains an invalid value");
			}

			__validate_fill_character(*__begin);

			__fill_.__data[0] = *__begin;
			__begin += 2;
			return true;
		}

		if (!__parse_alignment(*__begin))
		{
			return false;
		}

		++__begin;
		return true;
	}
HAMON_WARNING_POP()

	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_sign(_Iterator& __begin)
	{
		switch (*__begin)
		{
		case _CharT('-'):
			__sign_ = __sign::__minus;
			break;
		case _CharT('+'):
			__sign_ = __sign::__plus;
			break;
		case _CharT(' '):
			__sign_ = __sign::__space;
			break;
		default:
			return false;
		}
		++__begin;
		return true;
	}

	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_alternate_form(_Iterator& __begin)
	{
		if (*__begin != _CharT('#'))
		{
			return false;
		}

		__alternate_form_ = true;
		++__begin;
		return true;
	}

	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_zero_padding(_Iterator& __begin)
	{
		if (*__begin != _CharT('0'))
		{
			return false;
		}

		if (__alignment_ == __alignment::__default)
		{
			__alignment_ = __alignment::__zero_padding;
		}

		++__begin;
		return true;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_width(_Iterator& __begin, _Iterator __end, auto& __ctx)
	{
		if (*__begin == _CharT('0'))
		{
			hamon::detail::throw_format_error("The width option should not have a leading zero");
		}

		if (*__begin == _CharT('{'))
		{
			__format::__parse_number_result __r = __format_spec::__parse_arg_id(++__begin, __end, __ctx);
			__width_as_arg_                     = true;
			__width_                            = __r.__value;
			__begin                             = __r.__last;
			return true;
		}

		if (*__begin < _CharT('0') || *__begin > _CharT('9'))
		{
			return false;
		}

		__format::__parse_number_result __r = __format::__parse_number(__begin, __end);
		__width_                            = __r.__value;
		//_LIBCPP_ASSERT_INTERNAL(__width_ != 0,
		//						"A zero value isn't allowed and should be impossible, "
		//						"due to validations in this function");
		__begin = __r.__last;
		return true;
	}
HAMON_WARNING_POP()

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_precision(_Iterator& __begin, _Iterator __end, auto& __ctx)
	{
		if (*__begin != _CharT('.'))
		{
			return false;
		}

		++__begin;
		if (__begin == __end)
		{
			hamon::detail::throw_format_error("End of input while parsing format specifier precision");
		}

		if (*__begin == _CharT('{'))
		{
			__format::__parse_number_result __arg_id = __format_spec::__parse_arg_id(++__begin, __end, __ctx);
			__precision_as_arg_                      = true;
			__precision_                             = __arg_id.__value;
			__begin                                  = __arg_id.__last;
			return true;
		}

		if (*__begin < _CharT('0') || *__begin > _CharT('9'))
		{
			hamon::detail::throw_format_error("The precision option does not contain a value or an argument index");
		}

		__format::__parse_number_result __r = __format::__parse_number(__begin, __end);
		__precision_                        = __r.__value;
		__precision_as_arg_                 = false;
		__begin                             = __r.__last;
		return true;
	}
HAMON_WARNING_POP()

	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_locale_specific_form(_Iterator& __begin)
	{
		if (*__begin != _CharT('L'))
		{
			return false;
		}

		__locale_specific_form_ = true;
		++__begin;
		return true;
	}

	template <hamon::contiguous_iterator _Iterator>
	constexpr bool __parse_clear_brackets(_Iterator& __begin)
	{
		if (*__begin != _CharT('n'))
		{
			return false;
		}

		__clear_brackets_ = true;
		++__begin;
		return true;
	}

	template <hamon::contiguous_iterator _Iterator>
	constexpr void __parse_type(_Iterator& __begin)
	{
		// Determines the type. It does not validate whether the selected type is
		// valid. Most formatters have optional fields that are only allowed for
		// certain types. These parsers need to do validation after the type has
		// been parsed. So its easier to implement the validation for all types in
		// the specific parse function.
		switch (*__begin)
		{
		case 'A':
			__type_ = __type::__hexfloat_upper_case;
			break;
		case 'B':
			__type_ = __type::__binary_upper_case;
			break;
		case 'E':
			__type_ = __type::__scientific_upper_case;
			break;
		case 'F':
			__type_ = __type::__fixed_upper_case;
			break;
		case 'G':
			__type_ = __type::__general_upper_case;
			break;
		case 'X':
			__type_ = __type::__hexadecimal_upper_case;
			break;
		case 'a':
			__type_ = __type::__hexfloat_lower_case;
			break;
		case 'b':
			__type_ = __type::__binary_lower_case;
			break;
		case 'c':
			__type_ = __type::__char;
			break;
		case 'd':
			__type_ = __type::__decimal;
			break;
		case 'e':
			__type_ = __type::__scientific_lower_case;
			break;
		case 'f':
			__type_ = __type::__fixed_lower_case;
			break;
		case 'g':
			__type_ = __type::__general_lower_case;
			break;
		case 'o':
			__type_ = __type::__octal;
			break;
		case 'p':
			__type_ = __type::__pointer_lower_case;
			break;
		case 'P':
			__type_ = __type::__pointer_upper_case;
			break;
		case 's':
			__type_ = __type::__string;
			break;
		case 'x':
			__type_ = __type::__hexadecimal_lower_case;
			break;
		case '?':
			__type_ = __type::__debug;
			break;
		default:
			return;
		}
		++__begin;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
	int32_t __get_width(auto& __ctx) const
	{
		if (!__width_as_arg_)
		{
			return __width_;
		}

		return __format_spec::__substitute_arg_id(__ctx.arg(__width_));
	}
HAMON_WARNING_POP()

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")
	int32_t __get_precision(auto& __ctx) const
	{
		if (!__precision_as_arg_)
		{
			return __precision_;
		}

		return __format_spec::__substitute_arg_id(__ctx.arg(__precision_));
	}
HAMON_WARNING_POP()
};

// Validates whether the reserved bitfields don't change the size.
static_assert(sizeof(__parser<char>) == 16);
static_assert(sizeof(__parser<wchar_t>) == 16);

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PARSER_HPP
