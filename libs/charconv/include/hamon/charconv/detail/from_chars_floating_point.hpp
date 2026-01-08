/**
 *	@file	from_chars_floating_point.hpp
 *
 *	@brief	from_chars_floating_point の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP

#include <hamon/charconv/detail/from_chars_floating_point_inf.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_nan.hpp>
#include <hamon/charconv/detail/make_floating_point_infinity.hpp>
#include <hamon/charconv/detail/make_floating_point_zero.hpp>

#include <hamon/algorithm.hpp>
#include <hamon/bit.hpp>
#include <hamon/cctype.hpp>
#include <hamon/cstring.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>

#include <cfloat>

namespace hamon
{

namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

// vvvvvvvvvv DERIVED FROM corecrt_internal_fltintrn.h vvvvvvvvvv

template <typename F>
struct _Floating_type_traits;

template <>
struct _Floating_type_traits<float> {
    static constexpr int32_t _Mantissa_bits           = 24; // FLT_MANT_DIG
    static constexpr int32_t _Exponent_bits           = 8; // sizeof(float) * CHAR_BIT - FLT_MANT_DIG
    static constexpr int32_t _Maximum_binary_exponent = 127; // FLT_MAX_EXP - 1
    static constexpr int32_t _Minimum_binary_exponent = -126; // FLT_MIN_EXP - 1
    static constexpr int32_t _Exponent_bias           = 127;
    static constexpr int32_t _Sign_shift              = 31; // _Exponent_bits + _Mantissa_bits - 1
    static constexpr int32_t _Exponent_shift          = 23; // _Mantissa_bits - 1

    using _Uint_type = uint32_t;

    static constexpr uint32_t _Exponent_mask             = 0x000000FFu; // (1u << _Exponent_bits) - 1
    static constexpr uint32_t _Normal_mantissa_mask      = 0x00FFFFFFu; // (1u << _Mantissa_bits) - 1
    static constexpr uint32_t _Denormal_mantissa_mask    = 0x007FFFFFu; // (1u << (_Mantissa_bits - 1)) - 1
    static constexpr uint32_t _Special_nan_mantissa_mask = 0x00400000u; // 1u << (_Mantissa_bits - 2)
    static constexpr uint32_t _Shifted_sign_mask         = 0x80000000u; // 1u << _Sign_shift
    static constexpr uint32_t _Shifted_exponent_mask     = 0x7F800000u; // _Exponent_mask << _Exponent_shift

    static constexpr float _Minimum_value = FLT_MIN;//0x1.000000p-126f; // FLT_MIN
    static constexpr float _Maximum_value = FLT_MAX;//0x1.FFFFFEp+127f; // FLT_MAX
};

template <>
struct _Floating_type_traits<double> {
    static constexpr int32_t _Mantissa_bits           = 53; // DBL_MANT_DIG
    static constexpr int32_t _Exponent_bits           = 11; // sizeof(double) * CHAR_BIT - DBL_MANT_DIG
    static constexpr int32_t _Maximum_binary_exponent = 1023; // DBL_MAX_EXP - 1
    static constexpr int32_t _Minimum_binary_exponent = -1022; // DBL_MIN_EXP - 1
    static constexpr int32_t _Exponent_bias           = 1023;
    static constexpr int32_t _Sign_shift              = 63; // _Exponent_bits + _Mantissa_bits - 1
    static constexpr int32_t _Exponent_shift          = 52; // _Mantissa_bits - 1

    using _Uint_type = uint64_t;

    static constexpr uint64_t _Exponent_mask             = 0x00000000000007FFu; // (1ULL << _Exponent_bits) - 1
    static constexpr uint64_t _Normal_mantissa_mask      = 0x001FFFFFFFFFFFFFu; // (1ULL << _Mantissa_bits) - 1
    static constexpr uint64_t _Denormal_mantissa_mask    = 0x000FFFFFFFFFFFFFu; // (1ULL << (_Mantissa_bits - 1)) - 1
    static constexpr uint64_t _Special_nan_mantissa_mask = 0x0008000000000000u; // 1ULL << (_Mantissa_bits - 2)
    static constexpr uint64_t _Shifted_sign_mask         = 0x8000000000000000u; // 1ULL << _Sign_shift
    static constexpr uint64_t _Shifted_exponent_mask     = 0x7FF0000000000000u; // _Exponent_mask << _Exponent_shift

    static constexpr double _Minimum_value = DBL_MIN;//0x1.0000000000000p-1022; // DBL_MIN
    static constexpr double _Maximum_value = DBL_MAX;//0x1.FFFFFFFFFFFFFp+1023; // DBL_MAX
};

template <>
struct _Floating_type_traits<long double> : _Floating_type_traits<double> {};



// convert ['0', '9'] ['A', 'Z'] ['a', 'z'] to [0, 35], everything else to 255
static constexpr unsigned char _Digit_from_byte[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 255, 255, 255, 255, 255,
    255, 255, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    255, 255, 255, 255, 255, 255, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
//_STL_INTERNAL_STATIC_ASSERT(std::size(_Digit_from_byte) == 256);

HAMON_NODISCARD constexpr unsigned char _Digit_from_char(const char _Ch) noexcept {
    // convert ['0', '9'] ['A', 'Z'] ['a', 'z'] to [0, 35], everything else to 255

    // CodeQL [SM01954] This index is valid: we cast to unsigned char and the array has 256 elements.
    return _Digit_from_byte[static_cast<unsigned char>(_Ch)];
}

// vvvvvvvvvv DERIVED FROM corecrt_internal_big_integer.h vvvvvvvvvv

// A lightweight, sufficiently functional high-precision integer type for use in the binary floating-point <=> decimal
// string conversions. We define only the operations (and in some cases, parts of operations) that are actually used.

// We require sufficient precision to represent the reciprocal of the smallest representable value (the smallest
// denormal, 2^-1074). During parsing, we may also consider up to 768 decimal digits. For this, we require an
// additional log2(10^768) bits of precision. Finally, we require 54 bits of space for pre-division numerator shifting,
// because double explicitly stores 52 bits, implicitly stores 1 bit, and we need 1 more bit for rounding.

// PERFORMANCE NOTE: We intentionally do not initialize the _Mydata array when a _Big_integer_flt object is constructed.
// Profiling showed that zero-initialization caused a substantial performance hit. Initialization of the _Mydata
// array is not necessary: all operations on the _Big_integer_flt type are carefully written to only access elements at
// indices [0, _Myused), and all operations correctly update _Myused as the utilized size increases.

// _Big_integer_flt _Xval{}; is direct-list-initialization (N4950 [dcl.init.list]/1).
// N4950 [dcl.init.list]/3.5:
// "Otherwise, if the initializer list has no elements and T is a class type with a default constructor,
// the object is value-initialized."
// N4950 [dcl.init.general]/9, /9.1, /9.1.1:
// "To value-initialize an object of type T means:
// - if T is a (possibly cv-qualified) class type ([class]), then
//   - if T has either no default constructor ([class.default.ctor]) or a default constructor
//   that is user-provided or deleted, then the object is default-initialized;"
// N4950 [dcl.init.general]/7, /7.1:
// "To default-initialize an object of type T means:
// - If T is a (possibly cv-qualified) class type ([class]), constructors are considered. The applicable constructors
// are enumerated ([over.match.ctor]), and the best one for the initializer () is chosen through overload resolution
// ([over.match]).
// The constructor thus selected is called, with an empty argument list, to initialize the object."
// N4950 [class.base.init]/9, /9.3:
// "In a non-delegating constructor other than an implicitly-defined copy/move constructor ([class.copy.ctor]),
// if a given potentially constructed subobject is not designated by a mem-initializer-id (including the case
// where there is no mem-initializer-list because the constructor has no ctor-initializer), then [...]
// - otherwise, the entity is default-initialized ([dcl.init])."
// N4950 [dcl.init.general]/7, /7.2, /7.3:
// "To default-initialize an object of type T means: [...]
// - If T is an array type, each element is default-initialized.
// - Otherwise, no initialization is performed."
// Therefore, _Mydata's elements are not initialized.
struct _Big_integer_flt {
//#pragma warning(push)
//#pragma warning(disable : 26495) // Variable 'std::_Big_integer_flt::_Mydata' is uninitialized.
//                                 // Always initialize a member variable (type.6).
    _Big_integer_flt() noexcept : _Myused(0) {}
//#pragma warning(pop)

    _Big_integer_flt(const _Big_integer_flt& _Other) noexcept : _Myused(_Other._Myused) {
        hamon::memcpy(_Mydata, _Other._Mydata, _Other._Myused * sizeof(uint32_t));
    }

    _Big_integer_flt& operator=(const _Big_integer_flt& _Other) noexcept {
        _Myused = _Other._Myused;
        hamon::memmove(_Mydata, _Other._Mydata, _Other._Myused * sizeof(uint32_t));
        return *this;
    }

    HAMON_NODISCARD bool operator<(const _Big_integer_flt& _Rhs) const noexcept {
        if (_Myused != _Rhs._Myused) {
            return _Myused < _Rhs._Myused;
        }

        for (uint32_t i = _Myused - 1; i != static_cast<uint32_t>(-1); --i) {
            if (_Mydata[i] != _Rhs._Mydata[i]) {
                return _Mydata[i] < _Rhs._Mydata[i];
            }
        }

        return false;
    }

    static constexpr uint32_t _Maximum_bits = 1074 // 1074 bits required to represent 2^1074
                                            + 2552 // ceil(log2(10^768))
                                            + 54; // shift space

    static constexpr uint32_t _Element_bits = 32;

    static constexpr uint32_t _Element_count = (_Maximum_bits + _Element_bits - 1) / _Element_bits;

    uint32_t _Myused; // The number of elements currently in use
    uint32_t _Mydata[_Element_count]; // The number, stored in little-endian form
};

HAMON_NODISCARD inline _Big_integer_flt _Make_big_integer_flt_one() noexcept
{
	_Big_integer_flt _Xval{};
	_Xval._Mydata[0] = 1;
	_Xval._Myused    = 1;
	return _Xval;
}

HAMON_NODISCARD inline uint32_t _Bit_scan_reverse(const uint32_t value) noexcept
{
	return 32 - hamon::countl_zero(value);
}

HAMON_NODISCARD inline uint32_t _Bit_scan_reverse(const uint64_t value) noexcept
{
	return 64 - hamon::countl_zero(value);
}

HAMON_NODISCARD inline uint32_t _Bit_scan_reverse(const _Big_integer_flt& _Xval) noexcept
{
	if (_Xval._Myused == 0)
	{
		return 0;
	}

	const uint32_t _Bx = _Xval._Myused - 1;
	return _Bit_scan_reverse(_Xval._Mydata[_Bx]) + _Bx * _Big_integer_flt::_Element_bits;
}

// Shifts the high-precision integer _Xval by _Nx bits to the left. Returns true if the left shift was successful;
// false if it overflowed. When overflow occurs, the high-precision integer is reset to zero.
HAMON_NODISCARD inline bool
_Shift_left(_Big_integer_flt& _Xval, const uint32_t _Nx) noexcept
{
	if (_Xval._Myused == 0)
	{
		return true;
	}

	const uint32_t _Unit_shift = _Nx / _Big_integer_flt::_Element_bits;
	const uint32_t _Bit_shift  = _Nx % _Big_integer_flt::_Element_bits;

	if (_Xval._Myused + _Unit_shift > _Big_integer_flt::_Element_count)
	{
		// Unit shift will overflow.
		_Xval._Myused = 0;
		return false;
	}

	if (_Bit_shift == 0)
	{
		hamon::memmove(_Xval._Mydata + _Unit_shift, _Xval._Mydata, _Xval._Myused * sizeof(uint32_t));
		_Xval._Myused += _Unit_shift;
	}
	else
	{
		const bool _Bit_shifts_into_next_unit =
			_Bit_shift > (_Big_integer_flt::_Element_bits - _Bit_scan_reverse(_Xval._Mydata[_Xval._Myused - 1]));

		const uint32_t _New_used = _Xval._Myused + _Unit_shift + static_cast<uint32_t>(_Bit_shifts_into_next_unit);

		if (_New_used > _Big_integer_flt::_Element_count)
		{
			// Bit shift will overflow.
			_Xval._Myused = 0;
			return false;
		}

		const uint32_t _Msb_bits = _Bit_shift;
		const uint32_t _Lsb_bits = _Big_integer_flt::_Element_bits - _Msb_bits;

		const uint32_t _Lsb_mask = uint32_t((1UL << _Lsb_bits) - 1UL);
		const uint32_t _Msb_mask = ~_Lsb_mask;

		// If _Unit_shift == 0, this will wraparound, which is okay.
		for (uint32_t _Dest_index = _New_used - 1; _Dest_index != _Unit_shift - 1; --_Dest_index)
		{
			// performance note: PSLLDQ and PALIGNR instructions could be more efficient here

			// If _Bit_shifts_into_next_unit, the first iteration will trigger the bounds check below, which is okay.
			const uint32_t _Upper_source_index = _Dest_index - _Unit_shift;

			// When _Dest_index == _Unit_shift, this will wraparound, which is okay (see bounds check below).
			const uint32_t _Lower_source_index = _Dest_index - _Unit_shift - 1;

			const uint32_t _Upper_source = _Upper_source_index < _Xval._Myused ? _Xval._Mydata[_Upper_source_index] : 0;
			const uint32_t _Lower_source = _Lower_source_index < _Xval._Myused ? _Xval._Mydata[_Lower_source_index] : 0;

			const uint32_t _Shifted_upper_source = (_Upper_source & _Lsb_mask) << _Msb_bits;
			const uint32_t _Shifted_lower_source = (_Lower_source & _Msb_mask) >> _Lsb_bits;

			const uint32_t _Combined_shifted_source = _Shifted_upper_source | _Shifted_lower_source;

			_Xval._Mydata[_Dest_index] = _Combined_shifted_source;
		}

		_Xval._Myused = _New_used;
	}

	hamon::memset(_Xval._Mydata, 0, _Unit_shift * sizeof(uint32_t));

	return true;
}

// Adds a 32-bit value to the high-precision integer _Xval. Returns true if the addition was successful;
// false if it overflowed. When overflow occurs, the high-precision integer is reset to zero.
HAMON_NODISCARD inline bool
_Add(_Big_integer_flt& _Xval, const uint32_t value) noexcept
{
	if (value == 0)
	{
		return true;
	}

	uint32_t _Carry = value;
	for (uint32_t i = 0; i != _Xval._Myused; ++i)
	{
		const uint64_t result = static_cast<uint64_t>(_Xval._Mydata[i]) + _Carry;
		_Xval._Mydata[i]     = static_cast<uint32_t>(result);
		_Carry                 = static_cast<uint32_t>(result >> 32);
	}

	if (_Carry != 0)
	{
		if (_Xval._Myused < _Big_integer_flt::_Element_count)
		{
			_Xval._Mydata[_Xval._Myused] = _Carry;
			++_Xval._Myused;
		}
		else
		{
			_Xval._Myused = 0;
			return false;
		}
	}

	return true;
}

HAMON_NODISCARD inline uint32_t
_Add_carry(uint32_t& _Ux1, const uint32_t _Ux2, const uint32_t _U_carry) noexcept
{
	const uint64_t _Uu = static_cast<uint64_t>(_Ux1) + _Ux2 + _U_carry;
	_Ux1               = static_cast<uint32_t>(_Uu);
	return static_cast<uint32_t>(_Uu >> 32);
}

HAMON_NODISCARD inline uint32_t
_Add_multiply_carry(uint32_t& _U_add, const uint32_t _U_mul_1, const uint32_t _U_mul_2, const uint32_t _U_carry) noexcept
{
	const uint64_t _Uu_res = static_cast<uint64_t>(_U_mul_1) * _U_mul_2 + _U_add + _U_carry;
	_U_add                 = static_cast<uint32_t>(_Uu_res);
	return static_cast<uint32_t>(_Uu_res >> 32);
}

HAMON_NODISCARD inline uint32_t
_Multiply_core(uint32_t* const _Multiplicand, const uint32_t _Multiplicand_count, const uint32_t _Multiplier) noexcept
{
	uint32_t _Carry = 0;
	for (uint32_t i = 0; i != _Multiplicand_count; ++i)
	{
		const uint64_t result = static_cast<uint64_t>(_Multiplicand[i]) * _Multiplier + _Carry;
		_Multiplicand[i]     = static_cast<uint32_t>(result);
		_Carry                 = static_cast<uint32_t>(result >> 32);
	}

	return _Carry;
}

// Multiplies the high-precision _Multiplicand by a 32-bit _Multiplier. Returns true if the multiplication
// was successful; false if it overflowed. When overflow occurs, the _Multiplicand is reset to zero.
HAMON_NODISCARD inline bool
_Multiply(_Big_integer_flt& _Multiplicand, const uint32_t _Multiplier) noexcept
{
	if (_Multiplier == 0)
	{
		_Multiplicand._Myused = 0;
		return true;
	}

	if (_Multiplier == 1)
	{
		return true;
	}

	if (_Multiplicand._Myused == 0)
	{
		return true;
	}

	const uint32_t _Carry = _Multiply_core(_Multiplicand._Mydata, _Multiplicand._Myused, _Multiplier);
	if (_Carry != 0)
	{
		if (_Multiplicand._Myused < _Big_integer_flt::_Element_count)
		{
			_Multiplicand._Mydata[_Multiplicand._Myused] = _Carry;
			++_Multiplicand._Myused;
		}
		else
		{
			_Multiplicand._Myused = 0;
			return false;
		}
	}

	return true;
}

// This high-precision integer multiplication implementation was translated from the implementation of
// System.Numerics.BigIntegerBuilder.Mul in the .NET Framework sources. It multiplies the _Multiplicand
// by the _Multiplier and returns true if the multiplication was successful; false if it overflowed.
// When overflow occurs, the _Multiplicand is reset to zero.
HAMON_NODISCARD inline bool
_Multiply(_Big_integer_flt& _Multiplicand, const _Big_integer_flt& _Multiplier) noexcept
{
	if (_Multiplicand._Myused == 0)
	{
		return true;
	}

	if (_Multiplier._Myused == 0)
	{
		_Multiplicand._Myused = 0;
		return true;
	}

	if (_Multiplier._Myused == 1)
	{
		return _Multiply(_Multiplicand, _Multiplier._Mydata[0]); // when overflow occurs, resets to zero
	}

	if (_Multiplicand._Myused == 1)
	{
		const uint32_t _Small_multiplier = _Multiplicand._Mydata[0];
		_Multiplicand                    = _Multiplier;
		return _Multiply(_Multiplicand, _Small_multiplier); // when overflow occurs, resets to zero
	}

	// We prefer more iterations on the inner loop and fewer on the outer:
	const bool _Multiplier_is_shorter = _Multiplier._Myused < _Multiplicand._Myused;
	const uint32_t* const _Rgu1       = _Multiplier_is_shorter ? _Multiplier._Mydata : _Multiplicand._Mydata;
	const uint32_t* const _Rgu2       = _Multiplier_is_shorter ? _Multiplicand._Mydata : _Multiplier._Mydata;

	const uint32_t _Cu1 = _Multiplier_is_shorter ? _Multiplier._Myused : _Multiplicand._Myused;
	const uint32_t _Cu2 = _Multiplier_is_shorter ? _Multiplicand._Myused : _Multiplier._Myused;

	_Big_integer_flt result{};
	for (uint32_t _Iu1 = 0; _Iu1 != _Cu1; ++_Iu1)
	{
		const uint32_t _U_cur = _Rgu1[_Iu1];
		if (_U_cur == 0)
		{
			if (_Iu1 == result._Myused)
			{
				result._Mydata[_Iu1] = 0;
				result._Myused       = _Iu1 + 1;
			}

			continue;
		}

		uint32_t _U_carry = 0;
		uint32_t _Iu_res  = _Iu1;
		for (uint32_t _Iu2 = 0; _Iu2 != _Cu2 && _Iu_res != _Big_integer_flt::_Element_count; ++_Iu2, ++_Iu_res)
		{
			if (_Iu_res == result._Myused)
			{
				result._Mydata[_Iu_res] = 0;
				result._Myused          = _Iu_res + 1;
			}

			_U_carry = _Add_multiply_carry(result._Mydata[_Iu_res], _U_cur, _Rgu2[_Iu2], _U_carry);
		}

		while (_U_carry != 0 && _Iu_res != _Big_integer_flt::_Element_count)
		{
			if (_Iu_res == result._Myused)
			{
				result._Mydata[_Iu_res] = 0;
				result._Myused          = _Iu_res + 1;
			}

			_U_carry = _Add_carry(result._Mydata[_Iu_res++], 0, _U_carry);
		}

		if (_Iu_res == _Big_integer_flt::_Element_count)
		{
			_Multiplicand._Myused = 0;
			return false;
		}
	}

	// Store the result in the _Multiplicand and compute the actual number of elements used:
	_Multiplicand = result;
	return true;
}

static const uint32_t _Large_power_data[578] = {0x540be400, 0x00000002, 0x63100000, 0x6bc75e2d, 0x00000005,
    0x40000000, 0x4674edea, 0x9f2c9cd0, 0x0000000c, 0xb9f56100, 0x5ca4bfab, 0x6329f1c3, 0x0000001d, 0xb5640000,
    0xc40534fd, 0x926687d2, 0x6c3b15f9, 0x00000044, 0x10000000, 0x946590d9, 0xd762422c, 0x9a224501, 0x4f272617,
    0x0000009f, 0x07950240, 0x245689c1, 0xc5faa71c, 0x73c86d67, 0xebad6ddc, 0x00000172, 0xcec10000, 0x63a22764,
    0xefa418ca, 0xcdd17b25, 0x6bdfef70, 0x9dea3e1f, 0x0000035f, 0xe4000000, 0xcdc3fe6e, 0x66bc0c6a, 0x2e391f32,
    0x5a450203, 0x71d2f825, 0xc3c24a56, 0x000007da, 0xa82e8f10, 0xaab24308, 0x8e211a7c, 0xf38ace40, 0x84c4ce0b,
    0x7ceb0b27, 0xad2594c3, 0x00001249, 0xdd1a4000, 0xcc9f54da, 0xdc5961bf, 0xc75cabab, 0xf505440c, 0xd1bc1667,
    0xfbb7af52, 0x608f8d29, 0x00002a94, 0x21000000, 0x17bb8a0c, 0x56af8ea4, 0x06479fa9, 0x5d4bb236, 0x80dc5fe0,
    0xf0feaa0a, 0xa88ed940, 0x6b1a80d0, 0x00006323, 0x324c3864, 0x8357c796, 0xe44a42d5, 0xd9a92261, 0xbd3c103d,
    0x91e5f372, 0xc0591574, 0xec1da60d, 0x102ad96c, 0x0000e6d3, 0x1e851000, 0x6e4f615b, 0x187b2a69, 0x0450e21c,
    0x2fdd342b, 0x635027ee, 0xa6c97199, 0x8e4ae916, 0x17082e28, 0x1a496e6f, 0x0002196e, 0x32400000, 0x04ad4026,
    0xf91e7250, 0x2994d1d5, 0x665bcdbb, 0xa23b2e96, 0x65fa7ddb, 0x77de53ac, 0xb020a29b, 0xc6bff953, 0x4b9425ab,
    0x0004e34d, 0xfbc32d81, 0x5222d0f4, 0xb70f2850, 0x5713f2f3, 0xdc421413, 0xd6395d7d, 0xf8591999, 0x0092381c,
    0x86b314d6, 0x7aa577b9, 0x12b7fe61, 0x000b616a, 0x1d11e400, 0x56c3678d, 0x3a941f20, 0x9b09368b, 0xbd706908,
    0x207665be, 0x9b26c4eb, 0x1567e89d, 0x9d15096e, 0x7132f22b, 0xbe485113, 0x45e5a2ce, 0x001a7f52, 0xbb100000,
    0x02f79478, 0x8c1b74c0, 0xb0f05d00, 0xa9dbc675, 0xe2d9b914, 0x650f72df, 0x77284b4c, 0x6df6e016, 0x514391c2,
    0x2795c9cf, 0xd6e2ab55, 0x9ca8e627, 0x003db1a6, 0x40000000, 0xf4ecd04a, 0x7f2388f0, 0x580a6dc5, 0x43bf046f,
    0xf82d5dc3, 0xee110848, 0xfaa0591c, 0xcdf4f028, 0x192ea53f, 0xbcd671a0, 0x7d694487, 0x10f96e01, 0x791a569d,
    0x008fa475, 0xb9b2e100, 0x8288753c, 0xcd3f1693, 0x89b43a6b, 0x089e87de, 0x684d4546, 0xfddba60c, 0xdf249391,
    0x3068ec13, 0x99b44427, 0xb68141ee, 0x5802cac3, 0xd96851f1, 0x7d7625a2, 0x014e718d, 0xfb640000, 0xf25a83e6,
    0x9457ad0f, 0x0080b511, 0x2029b566, 0xd7c5d2cf, 0xa53f6d7d, 0xcdb74d1c, 0xda9d70de, 0xb716413d, 0x71d0ca4e,
    0xd7e41398, 0x4f403a90, 0xf9ab3fe2, 0x264d776f, 0x030aafe6, 0x10000000, 0x09ab5531, 0xa60c58d2, 0x566126cb,
    0x6a1c8387, 0x7587f4c1, 0x2c44e876, 0x41a047cf, 0xc908059e, 0xa0ba063e, 0xe7cfc8e8, 0xe1fac055, 0xef0144b2,
    0x24207eb0, 0xd1722573, 0xe4b8f981, 0x071505ae, 0x7a3b6240, 0xcea45d4f, 0x4fe24133, 0x210f6d6d, 0xe55633f2,
    0x25c11356, 0x28ebd797, 0xd396eb84, 0x1e493b77, 0x471f2dae, 0x96ad3820, 0x8afaced1, 0x4edecddb, 0x5568c086,
    0xb2695da1, 0x24123c89, 0x107d4571, 0x1c410000, 0x6e174a27, 0xec62ae57, 0xef2289aa, 0xb6a2fbdd, 0x17e1efe4,
    0x3366bdf2, 0x37b48880, 0xbfb82c3e, 0x19acde91, 0xd4f46408, 0x35ff6a4e, 0x67566a0e, 0x40dbb914, 0x782a3bca,
    0x6b329b68, 0xf5afc5d9, 0x266469bc, 0xe4000000, 0xfb805ff4, 0xed55d1af, 0x9b4a20a8, 0xab9757f8, 0x01aefe0a,
    0x4a2ca67b, 0x1ebf9569, 0xc7c41c29, 0xd8d5d2aa, 0xd136c776, 0x93da550c, 0x9ac79d90, 0x254bcba8, 0x0df07618,
    0xf7a88809, 0x3a1f1074, 0xe54811fc, 0x59638ead, 0x97cbe710, 0x26d769e8, 0xb4e4723e, 0x5b90aa86, 0x9c333922,
    0x4b7a0775, 0x2d47e991, 0x9a6ef977, 0x160b40e7, 0x0c92f8c4, 0xf25ff010, 0x25c36c11, 0xc9f98b42, 0x730b919d,
    0x05ff7caf, 0xb0432d85, 0x2d2b7569, 0xa657842c, 0xd01fef10, 0xc77a4000, 0xe8b862e5, 0x10d8886a, 0xc8cd98e5,
    0x108955c5, 0xd059b655, 0x58fbbed4, 0x03b88231, 0x034c4519, 0x194dc939, 0x1fc500ac, 0x794cc0e2, 0x3bc980a1,
    0xe9b12dd1, 0x5e6d22f8, 0x7b38899a, 0xce7919d8, 0x78c67672, 0x79e5b99f, 0xe494034e, 0x00000001, 0xa1000000,
    0x6c5cd4e9, 0x9be47d6f, 0xf93bd9e7, 0x77626fa1, 0xc68b3451, 0xde2b59e8, 0xcf3cde58, 0x2246ff58, 0xa8577c15,
    0x26e77559, 0x17776753, 0xebe6b763, 0xe3fd0a5f, 0x33e83969, 0xa805a035, 0xf631b987, 0x211f0f43, 0xd85a43db,
    0xab1bf596, 0x683f19a2, 0x00000004, 0xbe7dfe64, 0x4bc9042f, 0xe1f5edb0, 0x8fa14eda, 0xe409db73, 0x674fee9c,
    0xa9159f0d, 0xf6b5b5d6, 0x7338960e, 0xeb49c291, 0x5f2b97cc, 0x0f383f95, 0x2091b3f6, 0xd1783714, 0xc1d142df,
    0x153e22de, 0x8aafdf57, 0x77f5e55f, 0xa3e7ca8b, 0x032f525b, 0x42e74f3d, 0x0000000a, 0xf4dd1000, 0x5d450952,
    0xaeb442e1, 0xa3b3342e, 0x3fcda36f, 0xb4287a6e, 0x4bc177f7, 0x67d2c8d0, 0xaea8f8e0, 0xadc93b67, 0x6cc856b3,
    0x959d9d0b, 0x5b48c100, 0x4abe8a3d, 0x52d936f4, 0x71dbe84d, 0xf91c21c5, 0x4a458109, 0xd7aad86a, 0x08e14c7c,
    0x759ba59c, 0xe43c8800, 0x00000017, 0x92400000, 0x04f110d4, 0x186472be, 0x8736c10c, 0x1478abfb, 0xfc51af29,
    0x25eb9739, 0x4c2b3015, 0xa1030e0b, 0x28fe3c3b, 0x7788fcba, 0xb89e4358, 0x733de4a4, 0x7c46f2c2, 0x8f746298,
    0xdb19210f, 0x2ea3b6ae, 0xaa5014b2, 0xea39ab8d, 0x97963442, 0x01dfdfa9, 0xd2f3d3fe, 0xa0790280, 0x00000037,
    0x509c9b01, 0xc7dcadf1, 0x383dad2c, 0x73c64d37, 0xea6d67d0, 0x519ba806, 0xc403f2f8, 0xa052e1a2, 0xd710233a,
    0x448573a9, 0xcf12d9ba, 0x70871803, 0x52dc3a9b, 0xe5b252e8, 0x0717fb4e, 0xbe4da62f, 0x0aabd7e1, 0x8c62ed4f,
    0xceb9ec7b, 0xd4664021, 0xa1158300, 0xcce375e6, 0x842f29f2, 0x00000081, 0x7717e400, 0xd3f5fb64, 0xa0763d71,
    0x7d142fe9, 0x33f44c66, 0xf3b8f12e, 0x130f0d8e, 0x734c9469, 0x60260fa8, 0x3c011340, 0xcc71880a, 0x37a52d21,
    0x8adac9ef, 0x42bb31b4, 0xd6f94c41, 0xc88b056c, 0xe20501b8, 0x5297ed7c, 0x62c361c4, 0x87dad8aa, 0xb833eade,
    0x94f06861, 0x13cc9abd, 0x8dc1d56a, 0x0000012d, 0x13100000, 0xc67a36e8, 0xf416299e, 0xf3493f0a, 0x77a5a6cf,
    0xa4be23a3, 0xcca25b82, 0x3510722f, 0xbe9d447f, 0xa8c213b8, 0xc94c324e, 0xbc9e33ad, 0x76acfeba, 0x2e4c2132,
    0x3e13cd32, 0x70fe91b4, 0xbb5cd936, 0x42149785, 0x46cc1afd, 0xe638ddf8, 0x690787d2, 0x1a02d117, 0x3eb5f1fe,
    0xc3b9abae, 0x1c08ee6f, 0x000002be, 0x40000000, 0x8140c2aa, 0x2cf877d9, 0x71e1d73d, 0xd5e72f98, 0x72516309,
    0xafa819dd, 0xd62a5a46, 0x2a02dcce, 0xce46ddfe, 0x2713248d, 0xb723d2ad, 0xc404bb19, 0xb706cc2b, 0x47b1ebca,
    0x9d094bdc, 0xc5dc02ca, 0x31e6518e, 0x8ec35680, 0x342f58a8, 0x8b041e42, 0xfebfe514, 0x05fffc13, 0x6763790f,
    0x66d536fd, 0xb9e15076, 0x00000662, 0x67b06100, 0xd2010a1a, 0xd005e1c0, 0xdb12733b, 0xa39f2e3f, 0x61b29de2,
    0x2a63dce2, 0x942604bc, 0x6170d59b, 0xc2e32596, 0x140b75b9, 0x1f1d2c21, 0xb8136a60, 0x89d23ba2, 0x60f17d73,
    0xc6cad7df, 0x0669df2b, 0x24b88737, 0x669306ed, 0x19496eeb, 0x938ddb6f, 0x5e748275, 0xc56e9a36, 0x3690b731,
    0xc82842c5, 0x24ae798e, 0x00000ede, 0x41640000, 0xd5889ac1, 0xd9432c99, 0xa280e71a, 0x6bf63d2e, 0x8249793d,
    0x79e7a943, 0x22fde64a, 0xe0d6709a, 0x05cacfef, 0xbd8da4d7, 0xe364006c, 0xa54edcb3, 0xa1a8086e, 0x748f459e,
    0xfc8e54c8, 0xcc74c657, 0x42b8c3d4, 0x57d9636e, 0x35b55bcc, 0x6c13fee9, 0x1ac45161, 0xb595badb, 0xa1f14e9d,
    0xdcf9e750, 0x07637f71, 0xde2f9f2b, 0x0000229d, 0x10000000, 0x3c5ebd89, 0xe3773756, 0x3dcba338, 0x81d29e4f,
    0xa4f79e2c, 0xc3f9c774, 0x6a1ce797, 0xac5fe438, 0x07f38b9c, 0xd588ecfa, 0x3e5ac1ac, 0x85afccce, 0x9d1f3f70,
    0xe82d6dd3, 0x177d180c, 0x5e69946f, 0x648e2ce1, 0x95a13948, 0x340fe011, 0xb4173c58, 0x2748f694, 0x7c2657bd,
    0x758bda2e, 0x3b8090a0, 0x2ddbb613, 0x6dcf4890, 0x24e4047e, 0x00005099};

// Multiplies the high-precision integer _Xval by 10^_Power. Returns true if the multiplication was successful;
// false if it overflowed. When overflow occurs, the high-precision integer is reset to zero.
HAMON_NODISCARD inline bool
_Multiply_by_power_of_ten(_Big_integer_flt& _Xval, const uint32_t _Power) noexcept
{
	// To improve performance, we use a table of precomputed powers of ten, from 10^10 through 10^380, in increments
	// of ten. In its unpacked form, as an array of _Big_integer_flt objects, this table consists mostly of zero
	// elements. Thus, we store the table in a packed form, trimming leading and trailing zero elements. We provide an
	// index that is used to unpack powers from the table, using the function that appears after this function in this
	// file.

	// The minimum value representable with double-precision is 5E-324.
	// With the _Large_power_data table we can thus compute most multiplications with a single multiply.

	struct _Unpack_index
	{
		uint16_t _Offset; // The offset of this power's initial element in the array
		uint8_t _Zeroes; // The number of omitted leading zero elements
		uint8_t _Size; // The number of elements present for this power
	};

	static constexpr _Unpack_index _Large_power_indices[] ={{0, 0, 2}, {2, 0, 3}, {5, 0, 4}, {9, 1, 4}, {13, 1, 5},
		{18, 1, 6}, {24, 2, 6}, {30, 2, 7}, {37, 2, 8}, {45, 3, 8}, {53, 3, 9}, {62, 3, 10}, {72, 4, 10}, {82, 4, 11},
		{93, 4, 12}, {105, 5, 12}, {117, 5, 13}, {130, 5, 14}, {144, 5, 15}, {159, 6, 15}, {174, 6, 16}, {190, 6, 17},
		{207, 7, 17}, {224, 7, 18}, {242, 7, 19}, {261, 8, 19}, {280, 8, 21}, {301, 8, 22}, {323, 9, 22}, {345, 9, 23},
		{368, 9, 24}, {392, 10, 24}, {416, 10, 25}, {441, 10, 26}, {467, 10, 27}, {494, 11, 27}, {521, 11, 28},
		{549, 11, 29}};

	for (uint32_t _Large_power = _Power / 10; _Large_power != 0;)
	{
		const uint32_t _Current_power =
			(hamon::min)(_Large_power, static_cast<uint32_t>(hamon::size(_Large_power_indices)));

		const _Unpack_index& _Index = _Large_power_indices[_Current_power - 1];
		_Big_integer_flt _Multiplier{};
		_Multiplier._Myused = static_cast<uint32_t>(_Index._Size + _Index._Zeroes);

		const uint32_t* const _Source = _Large_power_data + _Index._Offset;

		hamon::memset(_Multiplier._Mydata, 0, _Index._Zeroes * sizeof(uint32_t));
		hamon::memcpy(_Multiplier._Mydata + _Index._Zeroes, _Source, _Index._Size * sizeof(uint32_t));

		if (!_Multiply(_Xval, _Multiplier))
		{ // when overflow occurs, resets to zero
			return false;
		}

		_Large_power -= _Current_power;
	}

	static constexpr uint32_t _Small_powers_of_ten[9] ={
		10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

	const uint32_t _Small_power = _Power % 10;

	if (_Small_power == 0)
	{
		return true;
	}

	return _Multiply(_Xval, _Small_powers_of_ten[_Small_power - 1]); // when overflow occurs, resets to zero
}

// Computes the number of zeroes higher than the most significant set bit in _Ux
HAMON_NODISCARD inline uint32_t _Count_sequential_high_zeroes(const uint32_t _Ux) noexcept
{
	//unsigned long _Index; // Intentionally uninitialized for better codegen
	//return _BitScanReverse(&_Index, _Ux) ? 31 - _Index : 32;
	return hamon::countl_zero(_Ux);
}

// This high-precision integer division implementation was translated from the implementation of
// System.Numerics.BigIntegerBuilder.ModDivCore in the .NET Framework sources.
// It computes both quotient and remainder: the remainder is stored in the _Numerator argument,
// and the least significant 64 bits of the quotient are returned from the function.
HAMON_NODISCARD inline uint64_t _Divide(_Big_integer_flt& _Numerator, const _Big_integer_flt& _Denominator) noexcept
{
	// If the _Numerator is zero, then both the quotient and remainder are zero:
	if (_Numerator._Myused == 0)
	{
		return 0;
	}

	// If the _Denominator is zero, then uh oh. We can't divide by zero:
	//_STL_INTERNAL_CHECK(_Denominator._Myused != 0); // Division by zero

	uint32_t _Max_numerator_element_index         = _Numerator._Myused - 1;
	const uint32_t _Max_denominator_element_index = _Denominator._Myused - 1;

	// The _Numerator and _Denominator are both nonzero.
	// If the _Denominator is only one element wide, we can take the fast route:
	if (_Max_denominator_element_index == 0)
	{
		const uint32_t _Small_denominator = _Denominator._Mydata[0];

		if (_Max_numerator_element_index == 0)
		{
			const uint32_t _Small_numerator = _Numerator._Mydata[0];

			if (_Small_denominator == 1)
			{
				_Numerator._Myused = 0;
				return _Small_numerator;
			}

			_Numerator._Mydata[0] = _Small_numerator % _Small_denominator;
			_Numerator._Myused    = _Numerator._Mydata[0] > 0 ? 1u : 0u;
			return _Small_numerator / _Small_denominator;
		}

		if (_Small_denominator == 1)
		{
			uint64_t _Quotient = _Numerator._Mydata[1];
			_Quotient <<= 32;
			_Quotient |= _Numerator._Mydata[0];
			_Numerator._Myused = 0;
			return _Quotient;
		}

		// We count down in the next loop, so the last assignment to _Quotient will be the correct one.
		uint64_t _Quotient = 0;

		uint64_t _Uu = 0;
		for (uint32_t _Iv = _Max_numerator_element_index; _Iv != static_cast<uint32_t>(-1); --_Iv)
		{
			_Uu       = (_Uu << 32) | _Numerator._Mydata[_Iv];
			_Quotient = (_Quotient << 32) + static_cast<uint32_t>(_Uu / _Small_denominator);
			_Uu %= _Small_denominator;
		}

		_Numerator._Mydata[1] = static_cast<uint32_t>(_Uu >> 32);
		_Numerator._Mydata[0] = static_cast<uint32_t>(_Uu);

		if (_Numerator._Mydata[1] > 0)
		{
			_Numerator._Myused = 2u;
		}
		else if (_Numerator._Mydata[0] > 0)
		{
			_Numerator._Myused = 1u;
		}
		else
		{
			_Numerator._Myused = 0u;
		}

		return _Quotient;
	}

	if (_Max_denominator_element_index > _Max_numerator_element_index)
	{
		return 0;
	}

	const uint32_t _Cu_den = _Max_denominator_element_index + 1;
	const int32_t _Cu_diff = static_cast<int32_t>(_Max_numerator_element_index - _Max_denominator_element_index);

	// Determine whether the result will have _Cu_diff or _Cu_diff + 1 digits:
	int32_t _Cu_quo = _Cu_diff;
	for (int32_t _Iu = static_cast<int32_t>(_Max_numerator_element_index);; --_Iu)
	{
		if (_Iu < _Cu_diff)
		{
			++_Cu_quo;
			break;
		}

		if (_Denominator._Mydata[_Iu - _Cu_diff] != _Numerator._Mydata[_Iu])
		{
			if (_Denominator._Mydata[_Iu - _Cu_diff] < _Numerator._Mydata[_Iu])
			{
				++_Cu_quo;
			}

			break;
		}
	}

	if (_Cu_quo == 0)
	{
		return 0;
	}

	// Get the uint to use for the trial divisions. We normalize so the high bit is set:
	uint32_t _U_den      = _Denominator._Mydata[_Cu_den - 1];
	uint32_t _U_den_next = _Denominator._Mydata[_Cu_den - 2];

	const uint32_t _Cbit_shift_left  = _Count_sequential_high_zeroes(_U_den);
	const uint32_t _Cbit_shift_right = 32 - _Cbit_shift_left;
	if (_Cbit_shift_left > 0)
	{
		_U_den = (_U_den << _Cbit_shift_left) | (_U_den_next >> _Cbit_shift_right);
		_U_den_next <<= _Cbit_shift_left;

		if (_Cu_den > 2)
		{
			_U_den_next |= _Denominator._Mydata[_Cu_den - 3] >> _Cbit_shift_right;
		}
	}

	uint64_t _Quotient = 0;
	for (int32_t _Iu = _Cu_quo; --_Iu >= 0;)
	{
		// Get the high (normalized) bits of the _Numerator:
		const uint32_t _U_num_hi = (_Iu + _Cu_den <= _Max_numerator_element_index) ? _Numerator._Mydata[_Iu + _Cu_den] : 0;

		uint64_t _Uu_num = (static_cast<uint64_t>(_U_num_hi) << 32) | static_cast<uint64_t>(_Numerator._Mydata[_Iu + _Cu_den - 1]);

		uint32_t _U_num_next = _Numerator._Mydata[_Iu + _Cu_den - 2];
		if (_Cbit_shift_left > 0)
		{
			_Uu_num = (_Uu_num << _Cbit_shift_left) | (_U_num_next >> _Cbit_shift_right);
			_U_num_next <<= _Cbit_shift_left;

			if (_Iu + _Cu_den >= 3)
			{
				_U_num_next |= _Numerator._Mydata[_Iu + _Cu_den - 3] >> _Cbit_shift_right;
			}
		}

		// Divide to get the quotient digit:
		uint64_t _Uu_quo = _Uu_num / _U_den;
		uint64_t _Uu_rem = static_cast<uint32_t>(_Uu_num % _U_den);

		if (_Uu_quo > UINT32_MAX)
		{
			_Uu_rem += _U_den * (_Uu_quo - UINT32_MAX);
			_Uu_quo = UINT32_MAX;
		}

		while (_Uu_rem <= UINT32_MAX && _Uu_quo * _U_den_next > ((_Uu_rem << 32) | _U_num_next))
		{
			--_Uu_quo;
			_Uu_rem += _U_den;
		}

		// Multiply and subtract. Note that _Uu_quo may be one too large.
		// If we have a borrow at the end, we'll add the _Denominator back on and decrement _Uu_quo.
		if (_Uu_quo > 0)
		{
			uint64_t _Uu_borrow = 0;

			for (uint32_t _Iu2 = 0; _Iu2 < _Cu_den; ++_Iu2)
			{
				_Uu_borrow += _Uu_quo * _Denominator._Mydata[_Iu2];

				const uint32_t _U_sub = static_cast<uint32_t>(_Uu_borrow);
				_Uu_borrow >>= 32;
				if (_Numerator._Mydata[_Iu + _Iu2] < _U_sub)
				{
					++_Uu_borrow;
				}

				_Numerator._Mydata[_Iu + _Iu2] -= _U_sub;
			}

			if (_U_num_hi < _Uu_borrow)
			{
				// Add, tracking carry:
				uint32_t _U_carry = 0;
				for (uint32_t _Iu2 = 0; _Iu2 < _Cu_den; ++_Iu2)
				{
					const uint64_t _Sum = static_cast<uint64_t>(_Numerator._Mydata[_Iu + _Iu2]) + static_cast<uint64_t>(_Denominator._Mydata[_Iu2]) + _U_carry;

					_Numerator._Mydata[_Iu + _Iu2] = static_cast<uint32_t>(_Sum);
					_U_carry                       = static_cast<uint32_t>(_Sum >> 32);
				}

				--_Uu_quo;
			}

			_Max_numerator_element_index = _Iu + _Cu_den - 1;
		}

		_Quotient = (_Quotient << 32) + static_cast<uint32_t>(_Uu_quo);
	}

	// Trim the remainder:
	uint32_t _Used = _Max_numerator_element_index + 1;

	while (_Used != 0 && _Numerator._Mydata[_Used - 1] == 0)
	{
		--_Used;
	}

	_Numerator._Myused = _Used;

	return _Quotient;
}

// ^^^^^^^^^^ DERIVED FROM corecrt_internal_big_integer.h ^^^^^^^^^^

// vvvvvvvvvv DERIVED FROM corecrt_internal_strtox.h vvvvvvvvvv

// This type is used to hold a partially-parsed string representation of a floating-point number.
// The number is stored in the following form:
//
// [sign] 0._Mymantissa * B^_Myexponent
//
// The _Mymantissa buffer stores the mantissa digits in big-endian, binary-coded decimal form. The _Mymantissa_count
// stores the number of digits present in the _Mymantissa buffer. The base B is not stored; it must be tracked
// separately. Note that the base of the mantissa digits may not be the same as B (e.g., for hexadecimal
// floating-point, the mantissa digits are in base 16 but the exponent is a base 2 exponent).
//
// We consider up to 768 decimal digits during conversion. In most cases, we require nowhere near this many digits
// of precision to compute the correctly rounded binary floating-point value for the input string. The worst case is
// (2 - 3 * 2^-53) * 2^-1022, which has an exact decimal representation of 768 decimal digits after trimming zeroes.
// This value is exactly between 0x1.ffffffffffffep-1022 and 0x1.fffffffffffffp-1022. For round-to-nearest,
// ties-to-even behavior, we also need to consider whether there are any nonzero trailing decimal digits.

// NOTE: The mantissa buffer count here must be kept in sync with the precision of the _Big_integer_flt type.
struct _Floating_point_string
{
	bool _Myis_negative;
	int32_t _Myexponent;
	uint32_t _Mymantissa_count;
	uint8_t _Mymantissa[768];
};

// Computes value / 2^shift, then rounds the result according to round_to_nearest.
// By the time we call this function, we will already have discarded most digits.
// The caller must pass true for has_zero_tail if all discarded bits were zeroes.
HAMON_NODISCARD inline uint64_t
_Right_shift_with_rounding(const uint64_t value, const uint32_t shift, const bool has_zero_tail) noexcept
{
	constexpr uint32_t _Total_number_of_bits = 64;
	if (shift >= _Total_number_of_bits)
	{
		if (shift == _Total_number_of_bits)
		{
			constexpr uint64_t _Extra_bits_mask = (1ULL << (_Total_number_of_bits - 1)) - 1;
			constexpr uint64_t _Round_bit_mask  = (1ULL << (_Total_number_of_bits - 1));

			const bool _Round_bit = (value & _Round_bit_mask) != 0;
			const bool _Tail_bits = !has_zero_tail || (value & _Extra_bits_mask) != 0;

			// We round up the answer to 1 if the answer is greater than 0.5. Otherwise, we round down the answer to 0
			// if either [1] the answer is less than 0.5 or [2] the answer is exactly 0.5.
			return static_cast<uint64_t>(_Round_bit && _Tail_bits);
		}
		else
		{
			// If we'd need to shift 65 or more bits, the answer is less than 0.5 and is always rounded to zero:
			return 0;
		}
	}

	// Reference implementation with suboptimal codegen:
	// const uint64_t _Extra_bits_mask = (1ULL << (shift - 1)) - 1;
	// const uint64_t _Round_bit_mask  = (1ULL << (shift - 1));
	// const uint64_t _Lsb_bit_mask    = 1ULL << shift;

	// const bool _Lsb_bit   = (value & _Lsb_bit_mask) != 0;
	// const bool _Round_bit = (value & _Round_bit_mask) != 0;
	// const bool _Tail_bits = !has_zero_tail || (value & _Extra_bits_mask) != 0;

	// return (value >> shift) + _Should_round_up(_Lsb_bit, _Round_bit, _Tail_bits);

	// Example for optimized implementation: Let shift be 8.
	// Bit index: ...[8]76543210
	//    value: ...[L]RTTTTTTT
	// By focusing on the bit at index shift, we can avoid unnecessary branching and shifting.

	// Bit index: ...[8]76543210
	//  _Lsb_bit: ...[L]RTTTTTTT
	const uint64_t _Lsb_bit = value;

	//  Bit index: ...9[8]76543210
	// _Round_bit: ...L[R]TTTTTTT0
	const uint64_t _Round_bit = value << 1;

	// We can detect (without branching) whether any of the trailing bits are set.
	// Due to _Should_round below, this computation will be used if and only if R is 1, so we can assume that here.
	//      Bit index: ...9[8]76543210
	//     _Round_bit: ...L[1]TTTTTTT0
	// _Has_tail_bits: ....[H]........

	// If all of the trailing bits T are 0, and has_zero_tail is true,
	// then `_Round_bit - static_cast<uint64_t>(has_zero_tail)` will produce 0 for H (due to R being 1).
	// If any of the trailing bits T are 1, or has_zero_tail is false,
	// then `_Round_bit - static_cast<uint64_t>(has_zero_tail)` will produce 1 for H (due to R being 1).
	const uint64_t _Has_tail_bits = _Round_bit - static_cast<uint64_t>(has_zero_tail);

	// Finally, we can use _Should_round_up() logic with bitwise-AND and bitwise-OR,
	// selecting just the bit at index shift.
	const uint64_t _Should_round = ((_Round_bit & (_Has_tail_bits | _Lsb_bit)) >> shift) & uint64_t{1};

	// This rounding technique is dedicated to the memory of Peppermint. =^..^=
	return (value >> shift) + _Should_round;
}

// Converts the floating-point value [sign] (mantissa / 2^(precision-1)) * 2^exponent into the correct form for
// F and stores the result into the result object.
// The caller must ensure that the mantissa and exponent are correctly computed such that either:
// [1] min_exponent <= exponent <= max_exponent && 2^(precision-1) <= mantissa <= 2^precision, or
// [2] exponent == min_exponent && 0 < mantissa <= 2^(precision-1).
// (The caller should round the mantissa before calling this function. The caller doesn't need to renormalize the
// mantissa when the mantissa carries over to a higher bit after rounding up.)

// This function correctly handles overflow and stores an infinity in the result object.
// (The result overflows if and only if exponent == max_exponent && mantissa == 2^precision)
template <typename F>
void _Assemble_floating_point_value_no_shift(const bool is_negative, const int32_t exponent, const typename _Floating_type_traits<F>::_Uint_type mantissa, F& result) noexcept
{
	// The following code assembles floating-point values based on an alternative interpretation of the IEEE 754 binary
	// floating-point format. It is valid for all of the following cases:
	// [1] normal value,
	// [2] normal value, needs renormalization and exponent increment after rounding up the mantissa,
	// [3] normal value, overflows after rounding up the mantissa,
	// [4] subnormal value,
	// [5] subnormal value, becomes a normal value after rounding up the mantissa.

	// Examples for float:
	// | Case |     Input     | Exponent |  Exponent  |  Exponent  |  Rounded  | Result Bits |     Result      |
	// |      |               |          | + Bias - 1 |  Component |  Mantissa |             |                 |
	// | ---- | ------------- | -------- | ---------- | ---------- | --------- | ----------- | --------------- |
	// | [1]  | 1.000000p+0   |     +0   |    126     | 0x3f000000 |  0x800000 | 0x3f800000  | 0x1.000000p+0   |
	// | [2]  | 1.ffffffp+0   |     +0   |    126     | 0x3f000000 | 0x1000000 | 0x40000000  | 0x1.000000p+1   |
	// | [3]  | 1.ffffffp+127 |   +127   |    253     | 0x7e800000 | 0x1000000 | 0x7f800000  |     inf         |
	// | [4]  | 0.fffffep-126 |   -126   |      0     | 0x00000000 |  0x7fffff | 0x007fffff  | 0x0.fffffep-126 |
	// | [5]  | 0.ffffffp-126 |   -126   |      0     | 0x00000000 |  0x800000 | 0x00800000  | 0x1.000000p-126 |
	using _Floating_traits = _Floating_type_traits<F>;
	using _Uint_type       = typename _Floating_traits::_Uint_type;

	_Uint_type _Sign_component = is_negative;
	_Sign_component <<= _Floating_traits::_Sign_shift;

	_Uint_type _Exponent_component = static_cast<uint32_t>(exponent + (_Floating_traits::_Exponent_bias - 1));
	_Exponent_component <<= _Floating_traits::_Exponent_shift;

	result = hamon::bit_cast<F>(_Sign_component | (_Exponent_component + mantissa));
}

// Converts the floating-point value [sign] (mantissa / 2^(precision-1)) * 2^exponent into the correct form for
// F and stores the result into the result object. The caller must ensure that the mantissa and exponent
// are correctly computed such that either [1] the most significant bit of the mantissa is in the correct position for
// the F, or [2] the exponent has been correctly adjusted to account for the shift of the mantissa that will
// be required.
//
// This function correctly handles range errors and stores a zero or infinity in the result object
// on underflow and overflow errors, respectively. This function correctly forms denormal numbers when required.
//
// If the provided mantissa has more bits of precision than can be stored in the result object, the mantissa is
// rounded to the available precision. Thus, if possible, the caller should provide a mantissa with at least one
// more bit of precision than is required, to ensure that the mantissa is correctly rounded.
// (The caller should not round the mantissa before calling this function.)
template <typename F>
HAMON_NODISCARD errc
_Assemble_floating_point_value(const uint64_t initial_mantissa, const int32_t initial_exponent, const bool is_negative, const bool has_zero_tail, F& result) noexcept
{
	using _Traits = _Floating_type_traits<F>;

	// Assume that the number is representable as a normal value.
	// Compute the number of bits by which we must adjust the mantissa to shift it into the correct position,
	// and compute the resulting base two exponent for the normalized mantissa:
	const uint32_t initial_mantissa_bits = _Bit_scan_reverse(initial_mantissa);
	const int32_t normal_mantissa_shift  = static_cast<int32_t>(_Traits::_Mantissa_bits - initial_mantissa_bits);
	const int32_t normal_exponent        = initial_exponent - normal_mantissa_shift;

	if (normal_exponent > _Traits::_Maximum_binary_exponent)
	{
		// The exponent is too large to be represented by the floating-point type; report the overflow condition:
		result = make_floating_point_infinity<F>(is_negative);
		return errc::result_out_of_range; // Overflow example: "1e+1000"
	}

	uint64_t mantissa = initial_mantissa;
	int32_t exponent  = normal_exponent;
	errc error_code{};

	if (normal_exponent < _Traits::_Minimum_binary_exponent)
	{
		// The exponent is too small to be represented by the floating-point type as a normal value, but it may be
		// representable as a denormal value.

		// The exponent of subnormal values (as defined by the mathematical model of floating-point numbers, not the
		// exponent field in the bit representation) is equal to the minimum exponent of normal values.
		exponent = _Traits::_Minimum_binary_exponent;

		// Compute the number of bits by which we need to shift the mantissa in order to form a denormal number.
		const int32_t denormal_mantissa_shift = initial_exponent - exponent;

		if (denormal_mantissa_shift < 0)
		{
			mantissa = _Right_shift_with_rounding(mantissa, static_cast<uint32_t>(-denormal_mantissa_shift), has_zero_tail);

			// from_chars in MSVC STL and strto[f|d|ld] in UCRT reports underflow only when the result is zero after
			// rounding to the floating-point format. This behavior is different from IEEE 754 underflow exception.
			if (mantissa == 0)
			{
				error_code = errc::result_out_of_range; // Underflow example: "1e-1000"
			}

			// When we round the mantissa, the result may be so large that the number becomes a normal value.
			// For example, consider the single-precision case where the mantissa is 0x01ffffff and a right shift
			// of 2 is required to shift the value into position. We perform the shift in two steps: we shift by
			// one bit, then we shift again and round using the dropped bit. The initial shift yields 0x00ffffff.
			// The rounding shift then yields 0x007fffff and because the least significant bit was 1, we add 1
			// to this number to round it. The final result is 0x00800000.

			// 0x00800000 is 24 bits, which is more than the 23 bits available in the mantissa.
			// Thus, we have rounded our denormal number into a normal number.

			// We detect this case here and re-adjust the mantissa and exponent appropriately, to form a normal number.
			// This is handled by _Assemble_floating_point_value_no_shift.
		}
		else
		{
			mantissa <<= denormal_mantissa_shift;
		}
	}
	else
	{
		if (normal_mantissa_shift < 0)
		{
			mantissa = _Right_shift_with_rounding(mantissa, static_cast<uint32_t>(-normal_mantissa_shift), has_zero_tail);

			// When we round the mantissa, it may produce a result that is too large. In this case,
			// we divide the mantissa by two and increment the exponent (this does not change the value).
			// This is handled by _Assemble_floating_point_value_no_shift.

			// The increment of the exponent may have generated a value too large to be represented.
			// In this case, report the overflow:
			if (mantissa > _Traits::_Normal_mantissa_mask && exponent == _Traits::_Maximum_binary_exponent)
			{
				error_code = errc::result_out_of_range; // Overflow example: "1.ffffffp+127" for float
														 // Overflow example: "1.fffffffffffff8p+1023" for double
			}
		}
		else
		{
			mantissa <<= normal_mantissa_shift;
		}
	}

	// Assemble the floating-point value from the computed components:
	using _Uint_type = typename _Traits::_Uint_type;

	_Assemble_floating_point_value_no_shift(is_negative, exponent, static_cast<_Uint_type>(mantissa), result);

	return error_code;
}

// This function is part of the fast track for integer floating-point strings. It takes an integer and a sign and
// converts the value into its F representation, storing the result in the result object. If the value
// is not representable, +/-infinity is stored and overflow is reported (since this function deals with only integers,
// underflow is impossible).
template <typename F>
HAMON_NODISCARD errc
_Assemble_floating_point_value_from_big_integer_flt(
	const _Big_integer_flt& integer_value, const uint32_t integer_bits_of_precision, const bool is_negative, const bool has_nonzero_fractional_part, F& result) noexcept
{
	using _Traits = _Floating_type_traits<F>;

	constexpr int32_t base_exponent = _Traits::_Mantissa_bits - 1;

	// Very fast case: If we have 64 bits of precision or fewer,
	// we can just take the two low order elements from the _Big_integer_flt:
	if (integer_bits_of_precision <= 64)
	{
		constexpr int32_t exponent = base_exponent;

		const uint32_t mantissa_low  = integer_value._Myused > 0 ? integer_value._Mydata[0] : 0;
		const uint32_t mantissa_high = integer_value._Myused > 1 ? integer_value._Mydata[1] : 0;
		const uint64_t mantissa      = mantissa_low + (static_cast<uint64_t>(mantissa_high) << 32);

		return _Assemble_floating_point_value(mantissa, exponent, is_negative, !has_nonzero_fractional_part, result);
	}

	const uint32_t top_element_bits  = integer_bits_of_precision % 32;
	const uint32_t top_element_index = integer_bits_of_precision / 32;

	const uint32_t middle_element_index = top_element_index - 1;
	const uint32_t bottom_element_index = top_element_index - 2;

	// Pretty fast case: If the top 64 bits occupy only two elements, we can just combine those two elements:
	if (top_element_bits == 0)
	{
		const int32_t exponent = static_cast<int32_t>(base_exponent + bottom_element_index * 32);

		const uint64_t mantissa = integer_value._Mydata[bottom_element_index] + (static_cast<uint64_t>(integer_value._Mydata[middle_element_index]) << 32);

		bool has_zero_tail = !has_nonzero_fractional_part;
		for (uint32_t i = 0; has_zero_tail && i != bottom_element_index; ++i)
		{
			has_zero_tail = integer_value._Mydata[i] == 0;
		}

		return _Assemble_floating_point_value(mantissa, exponent, is_negative, has_zero_tail, result);
	}

	// Not quite so fast case: The top 64 bits span three elements in the _Big_integer_flt. Assemble the three pieces:
	const uint32_t top_element_mask  = (1u << top_element_bits) - 1;
	const uint32_t top_element_shift = 64 - top_element_bits; // Left

	const uint32_t middle_element_shift = top_element_shift - 32; // Left

	const uint32_t bottom_element_bits  = 32 - top_element_bits;
	const uint32_t bottom_element_mask  = ~top_element_mask;
	const uint32_t bottom_element_shift = 32 - bottom_element_bits; // Right

	const int32_t exponent = static_cast<int32_t>(base_exponent + bottom_element_index * 32 + top_element_bits);

	const uint64_t mantissa =
		(static_cast<uint64_t>(integer_value._Mydata[top_element_index] & top_element_mask) << top_element_shift) +
		(static_cast<uint64_t>(integer_value._Mydata[middle_element_index]) << middle_element_shift) +
		(static_cast<uint64_t>(integer_value._Mydata[bottom_element_index] & bottom_element_mask) >> bottom_element_shift);

	bool has_zero_tail = !has_nonzero_fractional_part && (integer_value._Mydata[bottom_element_index] & top_element_mask) == 0;

	for (uint32_t i = 0; has_zero_tail && i != bottom_element_index; ++i)
	{
		has_zero_tail = integer_value._Mydata[i] == 0;
	}

	return _Assemble_floating_point_value(mantissa, exponent, is_negative, has_zero_tail, result);
}

// Accumulates the decimal digits in [first_digit, last_digit) into the result high-precision integer.
// This function assumes that no overflow will occur.
inline void
_Accumulate_decimal_digits_into_big_integer_flt(const uint8_t* const first_digit, const uint8_t* const last_digit, _Big_integer_flt& result) noexcept
{
	// We accumulate nine digit chunks, transforming the base ten string into base one billion on the fly,
	// allowing us to reduce the number of high-precision multiplication and addition operations by 8/9.
	uint32_t accumulator       = 0;
	uint32_t accumulator_count = 0;
	for (const uint8_t* it = first_digit; it != last_digit; ++it)
	{
		if (accumulator_count == 9)
		{
			/*[[maybe_unused]]*/ const bool success1 = _Multiply(result, 1000000000); // assumes no overflow
			(void)success1;
			//_STL_INTERNAL_CHECK(success1);
			/*[[maybe_unused]]*/ const bool success2 = _Add(result, accumulator); // assumes no overflow
			(void)success2;
			//_STL_INTERNAL_CHECK(success2);

			accumulator       = 0;
			accumulator_count = 0;
		}

		accumulator *= 10;
		accumulator += *it;
		++accumulator_count;
	}

	if (accumulator_count != 0)
	{
		/*[[maybe_unused]]*/ const bool success3 = _Multiply_by_power_of_ten(result, accumulator_count); // assumes no overflow
		(void)success3;
		//_STL_INTERNAL_CHECK(success3);
		/*[[maybe_unused]]*/ const bool success4 = _Add(result, accumulator); // assumes no overflow
		(void)success4;
		//_STL_INTERNAL_CHECK(success4);
	}
}

// The core floating-point string parser for decimal strings. After a subject string is parsed and converted
// into a _Floating_point_string object, if the subject string was determined to be a decimal string,
// the object is passed to this function. This function converts the decimal real value to floating-point.
template <typename F>
HAMON_NODISCARD errc
_Convert_decimal_string_to_floating_type(const _Floating_point_string& data, F& result, bool has_zero_tail) noexcept
{
	using _Traits = _Floating_type_traits<F>;

	// To generate an N bit mantissa we require N + 1 bits of precision. The extra bit is used to correctly round
	// the mantissa (if there are fewer bits than this available, then that's totally okay;
	// in that case we use what we have and we don't need to round).
	constexpr uint32_t required_bits_of_precision = static_cast<uint32_t>(_Traits::_Mantissa_bits + 1);

	// The input is of the form 0.mantissa * 10^exponent, where 'mantissa' are the decimal digits of the mantissa
	// and 'exponent' is the decimal exponent. We decompose the mantissa into two parts: an integer part and a
	// fractional part. If the exponent is positive, then the integer part consists of the first 'exponent' digits,
	// or all present digits if there are fewer digits. If the exponent is zero or negative, then the integer part
	// is empty. In either case, the remaining digits form the fractional part of the mantissa.
	const uint32_t positive_exponent      = static_cast<uint32_t>((hamon::max)(0, data._Myexponent));
	const uint32_t integer_digits_present = (hamon::min)(positive_exponent, data._Mymantissa_count);
	const uint32_t integer_digits_missing = positive_exponent - integer_digits_present;
	const uint8_t* const integer_first    = data._Mymantissa;
	const uint8_t* const integer_last     = data._Mymantissa + integer_digits_present;

	const uint8_t* const fractional_first    = integer_last;
	const uint8_t* const fractional_last     = data._Mymantissa + data._Mymantissa_count;
	const uint32_t fractional_digits_present = static_cast<uint32_t>(fractional_last - fractional_first);

	// First, we accumulate the integer part of the mantissa into a _Big_integer_flt:
	_Big_integer_flt integer_value{};
	_Accumulate_decimal_digits_into_big_integer_flt(integer_first, integer_last, integer_value);

	if (integer_digits_missing > 0)
	{
		if (!_Multiply_by_power_of_ten(integer_value, integer_digits_missing))
		{
			result = make_floating_point_infinity<F>(data._Myis_negative);
			return errc::result_out_of_range; // Overflow example: "1e+2000"
		}
	}

	// At this point, the integer_value contains the value of the integer part of the mantissa. If either
	// [1] this number has more than the required number of bits of precision or
	// [2] the mantissa has no fractional part, then we can assemble the result immediately:
	const uint32_t integer_bits_of_precision = _Bit_scan_reverse(integer_value);
	{
		const bool has_zero_fractional_part = fractional_digits_present == 0 && has_zero_tail;

		if (integer_bits_of_precision >= required_bits_of_precision || has_zero_fractional_part)
		{
			return _Assemble_floating_point_value_from_big_integer_flt(integer_value, integer_bits_of_precision, data._Myis_negative, !has_zero_fractional_part, result);
		}
	}

	// Otherwise, we did not get enough bits of precision from the integer part, and the mantissa has a fractional
	// part. We parse the fractional part of the mantissa to obtain more bits of precision. To do this, we convert
	// the fractional part into an actual fraction N/M, where the numerator N is computed from the digits of the
	// fractional part, and the denominator M is computed as the power of 10 such that N/M is equal to the value
	// of the fractional part of the mantissa.
	_Big_integer_flt fractional_numerator{};
	_Accumulate_decimal_digits_into_big_integer_flt(fractional_first, fractional_last, fractional_numerator);

	const uint32_t fractional_denominator_exponent = data._Myexponent < 0 ? fractional_digits_present + static_cast<uint32_t>(-data._Myexponent) : fractional_digits_present;

	_Big_integer_flt fractional_denominator = _Make_big_integer_flt_one();
	if (!_Multiply_by_power_of_ten(fractional_denominator, fractional_denominator_exponent))
	{
		// If there were any digits in the integer part, it is impossible to underflow (because the exponent
		// cannot possibly be small enough), so if we underflow here it is a true underflow and we return zero.
		result = make_floating_point_zero<F>(data._Myis_negative);
		return errc::result_out_of_range; // Underflow example: "1e-2000"
	}

	// Because we are using only the fractional part of the mantissa here, the numerator is guaranteed to be smaller
	// than the denominator. We normalize the fraction such that the most significant bit of the numerator is in the
	// same position as the most significant bit in the denominator. This ensures that when we later shift the
	// numerator N bits to the left, we will produce N bits of precision.
	const uint32_t fractional_numerator_bits   = _Bit_scan_reverse(fractional_numerator);
	const uint32_t fractional_denominator_bits = _Bit_scan_reverse(fractional_denominator);

	const uint32_t fractional_shift = fractional_denominator_bits > fractional_numerator_bits
		? fractional_denominator_bits - fractional_numerator_bits
		: 0;

	if (fractional_shift > 0)
	{
		/*[[maybe_unused]]*/ const bool shift_success1 = _Shift_left(fractional_numerator, fractional_shift); // assumes no overflow
		(void)shift_success1;
		//_STL_INTERNAL_CHECK(shift_success1);
	}

	const uint32_t required_fractional_bits_of_precision = required_bits_of_precision - integer_bits_of_precision;

	uint32_t remaining_bits_of_precision_required = required_fractional_bits_of_precision;
	if (integer_bits_of_precision > 0)
	{
		// If the fractional part of the mantissa provides no bits of precision and cannot affect rounding,
		// we can just take whatever bits we got from the integer part of the mantissa. This is the case for numbers
		// like 5.0000000000000000000001, where the significant digits of the fractional part start so far to the
		// right that they do not affect the floating-point representation.

		// If the fractional shift is exactly equal to the number of bits of precision that we require,
		// then no fractional bits will be part of the result, but the result may affect rounding.
		// This is e.g. the case for large, odd integers with a fractional part greater than or equal to .5.
		// Thus, we need to do the division to correctly round the result.
		if (fractional_shift > remaining_bits_of_precision_required)
		{
			return _Assemble_floating_point_value_from_big_integer_flt(integer_value, integer_bits_of_precision, data._Myis_negative, fractional_digits_present != 0 || !has_zero_tail, result);
		}

		remaining_bits_of_precision_required -= fractional_shift;
	}

	// If there was no integer part of the mantissa, we will need to compute the exponent from the fractional part.
	// The fractional exponent is the power of two by which we must multiply the fractional part to move it into the
	// range [1.0, 2.0). This will either be the same as the shift we computed earlier, or one greater than that shift:
	const uint32_t fractional_exponent = fractional_numerator < fractional_denominator ? fractional_shift + 1 : fractional_shift;

	/*[[maybe_unused]]*/ const bool shift_success2 = _Shift_left(fractional_numerator, remaining_bits_of_precision_required); // assumes no overflow
	(void)shift_success2;
	//_STL_INTERNAL_CHECK(shift_success2);

	uint64_t fractional_mantissa = _Divide(fractional_numerator, fractional_denominator);

	has_zero_tail = has_zero_tail && fractional_numerator._Myused == 0;

	// We may have produced more bits of precision than were required. Check, and remove any "extra" bits:
	const uint32_t fractional_mantissa_bits = _Bit_scan_reverse(fractional_mantissa);
	if (fractional_mantissa_bits > required_fractional_bits_of_precision)
	{
		const uint32_t shift = fractional_mantissa_bits - required_fractional_bits_of_precision;
		has_zero_tail        = has_zero_tail && (fractional_mantissa & ((1ULL << shift) - 1)) == 0;
		fractional_mantissa >>= shift;
	}

	// Compose the mantissa from the integer and fractional parts:
	const uint32_t integer_mantissa_low  = integer_value._Myused > 0 ? integer_value._Mydata[0] : 0;
	const uint32_t integer_mantissa_high = integer_value._Myused > 1 ? integer_value._Mydata[1] : 0;
	const uint64_t integer_mantissa = integer_mantissa_low + (static_cast<uint64_t>(integer_mantissa_high) << 32);

	const uint64_t complete_mantissa = (integer_mantissa << required_fractional_bits_of_precision) + fractional_mantissa;

	// Compute the final exponent:
	// * If the mantissa had an integer part, then the exponent is one less than the number of bits we obtained
	// from the integer part. (It's one less because we are converting to the form 1.11111,
	// with one 1 to the left of the decimal point.)
	// * If the mantissa had no integer part, then the exponent is the fractional exponent that we computed.
	// Then, in both cases, we subtract an additional one from the exponent,
	// to account for the fact that we've generated an extra bit of precision, for use in rounding.
	const int32_t final_exponent = integer_bits_of_precision > 0
		? static_cast<int32_t>(integer_bits_of_precision - 2)
		: -static_cast<int32_t>(fractional_exponent) - 1;

	return _Assemble_floating_point_value(complete_mantissa, final_exponent, data._Myis_negative, has_zero_tail, result);
}

template <typename F>
HAMON_NODISCARD errc
_Convert_hexadecimal_string_to_floating_type(const _Floating_point_string& data, F& result, bool has_zero_tail) noexcept
{
	using _Traits = _Floating_type_traits<F>;

	uint64_t mantissa = 0;
	int32_t exponent  = data._Myexponent + _Traits::_Mantissa_bits - 1;

	// Accumulate bits into the mantissa buffer
	const uint8_t* const mantissa_last = data._Mymantissa + data._Mymantissa_count;
	const uint8_t* mantissa_it         = data._Mymantissa;
	while (mantissa_it != mantissa_last && mantissa <= _Traits::_Normal_mantissa_mask)
	{
		mantissa *= 16;
		mantissa += *mantissa_it++;
		exponent -= 4; // The exponent is in binary; log2(16) == 4
	}

	while (has_zero_tail && mantissa_it != mantissa_last)
	{
		has_zero_tail = *mantissa_it++ == 0;
	}

	return _Assemble_floating_point_value(mantissa, exponent, data._Myis_negative, has_zero_tail, result);
}

// ^^^^^^^^^^ DERIVED FROM corecrt_internal_strtox.h ^^^^^^^^^^

// C11 6.4.2.1 "General"
// digit: one of
//     0 1 2 3 4 5 6 7 8 9

// C11 6.4.4.1 "Integer constants"
// hexadecimal-digit: one of
//     0 1 2 3 4 5 6 7 8 9 a b c d e f A B C D E F

// C11 6.4.4.2 "Floating constants" (without floating-suffix, hexadecimal-prefix)
// amended by C11 7.22.1.3 "The strtod, strtof, and strtold functions" making exponents optional
// LWG-3080: "the sign '+' may only appear in the exponent part"

// digit-sequence:
//     digit
//     digit-sequence digit

// hexadecimal-digit-sequence:
//     hexadecimal-digit
//     hexadecimal-digit-sequence hexadecimal-digit

// sign: one of
//     + -

// decimal-floating-constant:
//     fractional-constant exponent-part[opt]
//     digit-sequence exponent-part[opt]

// fractional-constant:
//     digit-sequence[opt] . digit-sequence
//     digit-sequence .

// exponent-part:
//     e sign[opt] digit-sequence
//     E sign[opt] digit-sequence

// hexadecimal-floating-constant:
//     hexadecimal-fractional-constant binary-exponent-part[opt]
//     hexadecimal-digit-sequence binary-exponent-part[opt]

// hexadecimal-fractional-constant:
//     hexadecimal-digit-sequence[opt] . hexadecimal-digit-sequence
//     hexadecimal-digit-sequence .

// binary-exponent-part:
//     p sign[opt] digit-sequence
//     P sign[opt] digit-sequence

template <typename F>
HAMON_NODISCARD hamon::from_chars_result
_Ordinary_floating_from_chars(const char* const first, const char* const last, F& value, const hamon::chars_format fmt, const bool negative, const char* next) noexcept
{
	// vvvvvvvvvv DERIVED FROM corecrt_internal_strtox.h WITH SIGNIFICANT MODIFICATIONS vvvvvvvvvv

	const bool is_hexadecimal = fmt == hamon::chars_format::hex;
	const int base{is_hexadecimal ? 16 : 10};

	// PERFORMANCE NOTE: _Fp_string is intentionally left uninitialized. Zero-initialization is quite expensive
	// and is unnecessary. The benefit of not zero-initializing is greatest for short inputs.
	_Floating_point_string _Fp_string;

	// Record the optional minus sign:
	_Fp_string._Myis_negative = negative;

	uint8_t* const mantissa_first = _Fp_string._Mymantissa;
	uint8_t* const mantissa_last  = hamon::end(_Fp_string._Mymantissa);
	uint8_t* mantissa_it          = mantissa_first;

	// [whole_begin, whole_end) will contain 0 or more digits/hexits
	const char* const whole_begin = next;

	// Skip past any leading zeroes in the mantissa:
	for (; next != last && *next == '0'; ++next)
	{
	}
	const char* const leading_zero_end = next;

	bool has_zero_tail = true;

	// Scan the integer part of the mantissa:
	for (; next != last; ++next)
	{
		const unsigned char digit_value = _Digit_from_char(*next);

		if (digit_value >= base)
		{
			break;
		}

		if (mantissa_it != mantissa_last)
		{
			*mantissa_it++ = digit_value;
		}
		else
		{
			has_zero_tail = has_zero_tail && digit_value == 0;
		}
	}
	const char* const whole_end = next;

	// The exponent adjustment holds the number of digits in the mantissa buffer that appeared before the radix point.
	// It can be negative, and leading zeroes in the integer part are ignored. Examples:
	// For "03333.111", it is 4.
	// For "00000.111", it is 0.
	// For "00000.001", it is -2.
	ptrdiff_t exponent_adjustment = whole_end - leading_zero_end;

	// [whole_end, dot_end) will contain 0 or 1 '.' characters
	if (next != last && *next == '.')
	{
		++next;
	}
	const char* const dot_end = next;

	// [dot_end, frac_end) will contain 0 or more digits/hexits

	// If we haven't yet scanned any nonzero digits, continue skipping over zeroes,
	// updating the exponent adjustment to account for the zeroes we are skipping:
	if (exponent_adjustment == 0)
	{
		for (; next != last && *next == '0'; ++next)
		{
		}

		exponent_adjustment = dot_end - next;
	}

	// Scan the fractional part of the mantissa:
	for (; next != last; ++next)
	{
		const unsigned char digit_value = _Digit_from_char(*next);

		if (digit_value >= base)
		{
			break;
		}

		if (mantissa_it != mantissa_last)
		{
			*mantissa_it++ = digit_value;
		}
		else
		{
			has_zero_tail = has_zero_tail && digit_value == 0;
		}
	}
	const char* const frac_end = next;

	// We must have at least 1 digit/hexit
	if (whole_begin == whole_end && dot_end == frac_end)
	{
		return {first, errc::invalid_argument};
	}

	const char exponent_prefix{is_hexadecimal ? 'p' : 'e'};

	bool exponent_is_negative = false;
	bool exp_abs_too_large    = false;
	ptrdiff_t exponent        = 0;

	constexpr int maximum_temporary_decimal_exponent = 5200;
	constexpr int minimum_temporary_decimal_exponent = -5200;

	if (fmt != hamon::chars_format::fixed // N4950 [charconv.from.chars]/6.3
									// "if fmt has chars_format::fixed set but not chars_format::scientific,
									// the optional exponent part shall not appear"
		&& next != last && (static_cast<unsigned char>(*next) | 0x20) == exponent_prefix)
	{
		// found exponent prefix
		const char* unread = next + 1;

		if (unread != last && (*unread == '+' || *unread == '-'))

		{ // found optional sign
			exponent_is_negative = *unread == '-';
			++unread;
		}

		while (unread != last)
		{
			const unsigned char digit_value = _Digit_from_char(*unread);

			if (digit_value >= 10)
			{
				break;
			}

			// found decimal digit

			if (exponent < PTRDIFF_MAX / 10 || (exponent == PTRDIFF_MAX / 10 && digit_value <= PTRDIFF_MAX % 10))
			{
				exponent = exponent * 10 + digit_value;
			}
			else
			{
				exp_abs_too_large = true;
			}

			++unread;
			next = unread; // consume exponent-part/binary-exponent-part
		}

		if (exponent_is_negative)
		{
			exponent = -exponent;
		}
	}

	// [frac_end, exponent_end) will either be empty or contain "[EPep] sign[opt] digit-sequence"
	const char* const exponent_end = next;

	if (fmt == hamon::chars_format::scientific && frac_end == exponent_end)
	{
		// N4950 [charconv.from.chars]/6.2
		// "if fmt has chars_format::scientific set but not chars_format::fixed,
		// the otherwise optional exponent part shall appear"
		return {first, errc::invalid_argument};
	}

	// Remove trailing zeroes from mantissa:
	while (mantissa_it != mantissa_first && *(mantissa_it - 1) == 0)
	{
		--mantissa_it;
	}

	// If the mantissa buffer is empty, the mantissa was composed of all zeroes (so the mantissa is 0).
	// All such strings have the value zero, regardless of what the exponent is (because 0 * b^n == 0 for all b and n).
	// We can return now. Note that we defer this check until after we scan the exponent, so that we can correctly
	// update next to point past the end of the exponent.
	if (mantissa_it == mantissa_first)
	{
		//_STL_INTERNAL_CHECK(has_zero_tail);
		value = make_floating_point_zero<F>(negative);
		return {next, errc{}};
	}

	// Handle exponent of an overly large absolute value.
	if (exp_abs_too_large)
	{
		if (exponent > 0)
		{
			value = make_floating_point_infinity<F>(negative);
			return {next, errc::result_out_of_range};
		}
		else
		{
			value = make_floating_point_zero<F>(negative);
			return {next, errc::result_out_of_range};
		}
	}

	// Adjust exponent and exponent_adjustment when they have different signedness to avoid overflow.
	if (exponent > 0 && exponent_adjustment < 0)
	{
		if (is_hexadecimal)
		{
			const ptrdiff_t further_adjustment = (hamon::max)(-((exponent - 1) / 4 + 1), exponent_adjustment);
			exponent += further_adjustment * 4;
			exponent_adjustment -= further_adjustment;
		}
		else
		{
			const ptrdiff_t further_adjustment = (hamon::max)(-exponent, exponent_adjustment);
			exponent += further_adjustment;
			exponent_adjustment -= further_adjustment;
		}
	}
	else if (exponent < 0 && exponent_adjustment > 0)
	{
		if (is_hexadecimal)
		{
			const ptrdiff_t further_adjustment = (hamon::min)((-exponent - 1) / 4 + 1, exponent_adjustment);
			exponent += further_adjustment * 4;
			exponent_adjustment -= further_adjustment;
		}
		else
		{
			const ptrdiff_t further_adjustment = (hamon::min)(-exponent, exponent_adjustment);
			exponent += further_adjustment;
			exponent_adjustment -= further_adjustment;
		}
	}

	// In hexadecimal floating constants, the exponent is a base 2 exponent. The exponent adjustment computed during
	// parsing has the same base as the mantissa (so, 16 for hexadecimal floating constants).
	// We therefore need to scale the base 16 multiplier to base 2 by multiplying by log2(16):
	const int exponent_adjustment_multiplier{is_hexadecimal ? 4 : 1};

	// And then exponent and exponent_adjustment are either both non-negative or both non-positive.
	// So we can detect out-of-range cases directly.
	if (exponent > maximum_temporary_decimal_exponent || exponent_adjustment > maximum_temporary_decimal_exponent / exponent_adjustment_multiplier)
	{
		value = make_floating_point_infinity<F>(negative);
		return {next, errc::result_out_of_range}; // Overflow example: "1e+9999"
	}

	if (exponent < minimum_temporary_decimal_exponent || exponent_adjustment < minimum_temporary_decimal_exponent / exponent_adjustment_multiplier)
	{
		value = make_floating_point_zero<F>(negative);
		return {next, errc::result_out_of_range}; // Underflow example: "1e-9999"
	}

	exponent += exponent_adjustment * exponent_adjustment_multiplier;

	// Verify that after adjustment the exponent isn't wildly out of range (if it is, it isn't representable
	// in any supported floating-point format).
	if (exponent > maximum_temporary_decimal_exponent)
	{
		value = make_floating_point_infinity<F>(negative);
		return {next, errc::result_out_of_range}; // Overflow example: "10e+5199"
	}

	if (exponent < minimum_temporary_decimal_exponent)
	{
		value = make_floating_point_zero<F>(negative);
		return {next, errc::result_out_of_range}; // Underflow example: "0.001e-5199"
	}

	_Fp_string._Myexponent = static_cast<int32_t>(exponent);
	_Fp_string._Mymantissa_count = static_cast<uint32_t>(mantissa_it - mantissa_first);

	if (is_hexadecimal)
	{
		const errc ec = _Convert_hexadecimal_string_to_floating_type(_Fp_string, value, has_zero_tail);
		return {next, ec};
	}
	else
	{
		const errc ec = _Convert_decimal_string_to_floating_type(_Fp_string, value, has_zero_tail);
		return {next, ec};
	}

	// ^^^^^^^^^^ DERIVED FROM corecrt_internal_strtox.h WITH SIGNIFICANT MODIFICATIONS ^^^^^^^^^^
}

HAMON_WARNING_POP()

template <typename F>
HAMON_NODISCARD hamon::from_chars_result
from_chars_floating_point_impl(const char* const first, const char* const last, F& value, const hamon::chars_format fmt) noexcept
{
	if (first == last) /*[[unlikely]]*/
	{
		return {first, errc::invalid_argument};
	}

	const char* ptr = first;
	bool const negative = (*ptr == '-');
	if (negative)
	{
		++ptr;

		if (ptr == last) /*[[unlikely]]*/
		{
			return {first, errc::invalid_argument};
		}
	}

	switch (hamon::tolower(*ptr))
	{
	case 'i':
		return hamon::detail::from_chars_floating_point_inf<F>(first, last, value, negative, ptr);
	case 'n':
		return hamon::detail::from_chars_floating_point_nan<F>(first, last, value, negative, ptr);
	}

	// Distinguish ordinary numbers versus inf/nan with a single test.
	// ordinary numbers start with ['.'] ['0', '9'] ['A', 'F'] ['a', 'f']
	// inf/nan start with ['I'] ['N'] ['i'] ['n']
	// All other starting characters are invalid.
	// Setting the 0x20 bit folds these ranges in a useful manner.
	// ordinary (and some invalid) starting characters are folded to ['.'] ['0', '9'] ['a', 'f']
	// inf/nan starting characters are folded to ['i'] ['n']
	// These are ordered: ['.'] ['0', '9'] ['a', 'f'] < ['i'] ['n']
	// Note that invalid starting characters end up on both sides of this test.
	const unsigned char _Folded_start = static_cast<unsigned char>(static_cast<unsigned char>(*ptr) | 0x20);

	if (_Folded_start <= 'f')
	{
		// possibly an ordinary number
		return _Ordinary_floating_from_chars(first, last, value, fmt, negative, ptr);
	}
	//else if (_Folded_start == 'i')
	//{
	//	// possibly inf
	//	return _Infinity_from_chars(first, last, value, negative, ptr);
	//}
	//else if (_Folded_start == 'n')
	//{
	//	// possibly nan
	//	return _Nan_from_chars(first, last, value, negative, ptr);
	//}
	else
	{
		// definitely invalid
		return {first, errc::invalid_argument};
	}
}

inline hamon::from_chars_result
from_chars_floating_point(const char* first, const char* last, float& value, hamon::chars_format fmt) noexcept
{
	return from_chars_floating_point_impl(first, last, value, fmt);
}

inline hamon::from_chars_result
from_chars_floating_point(const char* first, const char* last, double& value, hamon::chars_format fmt) noexcept
{
	return from_chars_floating_point_impl(first, last, value, fmt);
}

inline hamon::from_chars_result
from_chars_floating_point(const char* first, const char* last, long double& value, hamon::chars_format fmt) noexcept
{
	double dbl; // intentionally default-init
	auto const ret = from_chars_floating_point_impl(first, last, dbl, fmt);

	if (ret.ec == errc{})
	{
		value = dbl;
	}

	return ret;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP
