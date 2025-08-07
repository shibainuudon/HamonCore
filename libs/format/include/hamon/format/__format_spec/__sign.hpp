/**
 *	@file	__sign.hpp
 *
 *	@brief	__sign の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___SIGN_HPP
#define HAMON_FORMAT___FORMAT_SPEC___SIGN_HPP

namespace hamon
{

namespace __format_spec
{

enum class __sign : uint8_t
{
	/// No sign is set in the format string.
	///
	/// The sign isn't allowed for certain format-types. By using this value
	/// it's possible to detect whether or not the user explicitly set the sign
	/// flag. For formatting purposes it behaves the same as \ref __minus.
	__default,
	__minus,
	__plus,
	__space
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___SIGN_HPP
