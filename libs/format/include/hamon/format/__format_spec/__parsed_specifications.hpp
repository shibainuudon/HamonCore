/**
 *	@file	__parsed_specifications.hpp
 *
 *	@brief	__parsed_specifications の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___PARSED_SPECIFICATIONS_HPP
#define HAMON_FORMAT___FORMAT_SPEC___PARSED_SPECIFICATIONS_HPP

#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__format_spec/__std.hpp>
#include <hamon/format/__format_spec/__chrono.hpp>
#include <hamon/format/__format_spec/__code_point.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>

namespace hamon
{

namespace __format_spec
{

/// Contains the parsed formatting specifications.
///
/// This contains information for both the std-format-spec and the
/// chrono-format-spec. This results in some unused members for both
/// specifications. However these unused members don't increase the size
/// of the structure.
///
/// This struct doesn't cross ABI boundaries so its layout doesn't need to be
/// kept stable.
template <class _CharT>
struct __parsed_specifications
{
	union {
		// The field __alignment_ is the first element in __std_ and __chrono_.
		// This allows the code to always inspect this value regards which member
		// of the union is the active member [class.union.general]/2.
		//
		// This is needed since the generic output routines handle the alignment of
		// the output.
		__alignment __alignment_ : 3;
		__std __std_;
		__chrono __chrono_;
	};

	/// The requested width.
	///
	/// When the format-spec used an arg-id for this field it has already been
	/// replaced with the value of that arg-id.
	int32_t __width_;

	/// The requested precision.
	///
	/// When the format-spec used an arg-id for this field it has already been
	/// replaced with the value of that arg-id.
	int32_t __precision_;

	__code_point<_CharT> __fill_;

	constexpr bool __has_width() const { return __width_ > 0; }

	constexpr bool __has_precision() const { return __precision_ >= 0; }
};

// Validate the struct is small and cheap to copy since the struct is passed by
// value in formatting functions.
static_assert(sizeof(__parsed_specifications<char>) == 16);
static_assert(hamon::is_trivially_copyable_v<__parsed_specifications<char>>);

static_assert(sizeof(__parsed_specifications<wchar_t>) == 16);
static_assert(hamon::is_trivially_copyable_v<__parsed_specifications<wchar_t>>);

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___PARSED_SPECIFICATIONS_HPP
