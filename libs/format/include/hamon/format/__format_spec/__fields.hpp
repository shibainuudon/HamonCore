/**
 *	@file	__fields.hpp
 *
 *	@brief	__fields の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___FIELDS_HPP
#define HAMON_FORMAT___FORMAT_SPEC___FIELDS_HPP


namespace hamon
{

namespace __format_spec
{

/// These fields are a filter for which elements to parse.
///
/// They default to false so when a new field is added it needs to be opted in
/// explicitly.
struct __fields
{
	uint16_t __sign_                 : 1 {false};
	uint16_t __alternate_form_       : 1 {false};
	uint16_t __zero_padding_         : 1 {false};
	uint16_t __precision_            : 1 {false};
	uint16_t __locale_specific_form_ : 1 {false};
	uint16_t __type_                 : 1 {false};
	// Determines the valid values for fill.
	//
	// Originally the fill could be any character except { and }. Range-based
	// formatters use the colon to mark the beginning of the
	// underlying-format-spec. To avoid parsing ambiguities these formatter
	// specializations prohibit the use of the colon as a fill character.
	uint16_t __use_range_fill_ : 1 {false};
	uint16_t __clear_brackets_ : 1 {false};
	uint16_t __consume_all_    : 1 {false};
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___FIELDS_HPP
