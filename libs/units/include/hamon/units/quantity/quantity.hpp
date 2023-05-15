/**
 *	@file	quantity.hpp
 *
 *	@brief	quantity の定義
 */

#ifndef HAMON_UNITS_QUANTITY_QUANTITY_HPP
#define HAMON_UNITS_QUANTITY_QUANTITY_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>
#include <hamon/units/quantity/dimensionless.hpp>
#include <hamon/units/quantity/detail/quantity_cast.hpp>
#include <hamon/units/quantity/detail/quantity_common_type.hpp>
#include <hamon/units/quantity/detail/quantity_multiply_result.hpp>
#include <hamon/units/quantity/detail/quantity_divide_result.hpp>
#include <hamon/units/quantity/detail/quantity_without_offset.hpp>
#include <hamon/units/quantity/detail/quantity_without_scale_offset.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/utility/adl_swap.hpp>
#include <hamon/compare/config.hpp>
#include <hamon/config.hpp>
#include <ratio>
#include <ostream>

namespace hamon
{

namespace units
{

/**
 *	@brief	quantity
 */
template <typename T, typename Dimension, typename Scale, typename Offset>
class quantity
{
public:
	using this_type       = quantity<T, Dimension, Scale, Offset>;
	using value_type      = T;
	using dimension_type  = Dimension;
	using scale_type      = Scale;
	using offset_type     = Offset;
	using reference       = value_type&;
	using const_reference = value_type const&;

	HAMON_CONSTEXPR
	quantity() HAMON_NOEXCEPT
		: m_value{}
	{}

	explicit HAMON_CONSTEXPR
	quantity(const_reference value) HAMON_NOEXCEPT
		: m_value{value}
	{}

	template <typename T2, typename S2, typename O2>
	HAMON_CONSTEXPR
	quantity(quantity<T2, Dimension, S2, O2> const& rhs) HAMON_NOEXCEPT
		: m_value{detail::quantity_cast<this_type>(rhs).value()}
	{}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	value() const HAMON_NOEXCEPT
	{
		return m_value;
	}

	HAMON_CXX14_CONSTEXPR void swap(quantity& other)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_swappable<T>::value)
	{
		hamon::adl_swap(m_value, other.m_value);
	}

private:
	value_type		m_value;
};

/**
 *	@brief	swap
 */
template <typename T, typename D, typename S, typename O>
inline HAMON_CXX14_CONSTEXPR void
swap(quantity<T, D, S, O>& lhs, quantity<T, D, S, O>& rhs)
HAMON_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

/**
 *	@brief	単項+演算子
 */
template <typename T, typename D, typename S, typename O>
HAMON_NODISCARD inline HAMON_CONSTEXPR quantity<T, D, S, O>
operator+(quantity<T, D, S, O> const& q) HAMON_NOEXCEPT
{
	return q;
}

/**
 *	@brief	単項-演算子
 */
template <typename T, typename D, typename S, typename O>
HAMON_NODISCARD inline HAMON_CONSTEXPR quantity<T, D, S, O>
operator-(quantity<T, D, S, O> const& q) HAMON_NOEXCEPT
{
	return quantity<T, D, S, O> { -q.value() };
}

/**
 *	@brief	quantity + quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator+(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
-> detail::quantity_common_type_t<
	quantity<T1, D1, S1, O1>,
	quantity<T2, D2, S2, O2>>
{
	using type = detail::quantity_common_type_t<
		quantity<T1, D1, S1, O1>,
		quantity<T2, D2, S2, O2>>;
	return type{ type{ lhs }.value() + type{ rhs }.value() };
}

/**
 *	@brief	quantity += quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
inline HAMON_CXX14_CONSTEXPR quantity<T1, D1, S1, O1>&
operator+=(
	quantity<T1, D1, S1, O1>& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs + rhs;
}

/**
 *	@brief	quantity - quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
-> detail::quantity_common_type_t<
	quantity<T1, D1, S1, O1>,
	quantity<T2, D2, S2, O2>>
{
	using type = detail::quantity_common_type_t<
		quantity<T1, D1, S1, O1>,
		quantity<T2, D2, S2, O2>>;
	return type{ type{ lhs }.value() - type{ rhs }.value() };
}

/**
 *	@brief	quantity -= quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
inline HAMON_CXX14_CONSTEXPR quantity<T1, D1, S1, O1>&
operator-=(
	quantity<T1, D1, S1, O1>& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	return lhs = lhs - rhs;
}

/**
 *	@brief	quantity * Scalar
 */
template <
	typename T, typename D, typename S, typename O,
	typename ArithmeticType,
	typename = hamon::enable_if_t<
		hamon::is_arithmetic<ArithmeticType>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR quantity<T, D, S, O>
operator*(
	quantity<T, D, S, O> const& lhs,
	ArithmeticType rhs) HAMON_NOEXCEPT
{
	using Q = quantity<T, D, S, O>;
	using Q2 = detail::quantity_without_offset_t<Q>;
	using CT = hamon::common_type_t<T, ArithmeticType>;
	return Q { Q2 { static_cast<T>(static_cast<CT>(Q2 { lhs }.value()) * static_cast<CT>(rhs)) } };
}

/**
 *	@brief	Scalar * quantity
 */
template <
	typename T, typename D, typename S, typename O,
	typename ArithmeticType,
	typename = hamon::enable_if_t<
		hamon::is_arithmetic<ArithmeticType>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR quantity<T, D, S, O>
operator*(
	ArithmeticType lhs,
	quantity<T, D, S, O> const& rhs) HAMON_NOEXCEPT
{
	return rhs * lhs;
}

/**
 *	@brief	quantity * ratio
 */
template <
	typename T, typename D, typename S, typename O,
	hamon::intmax_t Num, hamon::intmax_t Den
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(
	quantity<T, D, S, O> const& lhs,
	std::ratio<Num, Den> const& /*rhs*/) HAMON_NOEXCEPT
-> detail::quantity_multiply_result_t<
	quantity<T, D, S, O>,
	dimensionless<int, std::ratio<Num, Den>>>
{
	using type = detail::quantity_multiply_result_t<
		quantity<T, D, S, O>,
		dimensionless<int, std::ratio<Num, Den>>>;
	return type(lhs.value());
}

/**
 *	@brief	quantity *= Scalar
 */
template <
	typename T, typename D, typename S, typename O,
	typename ArithmeticType,
	typename = hamon::enable_if_t<
		hamon::is_arithmetic<ArithmeticType>::value
	>
>
inline HAMON_CXX14_CONSTEXPR quantity<T, D, S, O>&
operator*=(
	quantity<T, D, S, O>& lhs,
	ArithmeticType rhs) HAMON_NOEXCEPT
{
	return lhs = lhs * rhs;
}

/**
 *	@brief	quantity * quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator*(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
-> detail::quantity_multiply_result_t<
	quantity<T1, D1, S1, O1>,
	quantity<T2, D2, S2, O2>>
{
	using Q1 = quantity<T1, D1, S1, O1>;
	using Q2 = quantity<T2, D2, S2, O2>;
	using result_type = detail::quantity_multiply_result_t<Q1, Q2>;
	return result_type
	{
		detail::quantity_without_scale_offset_t<result_type>
		{
			detail::quantity_without_scale_offset_t<Q1>{lhs}.value() *
			detail::quantity_without_scale_offset_t<Q2>{rhs}.value()
		}
	};
}

/**
 *	@brief	quantity / Scalar
 */
template <
	typename T, typename D, typename S, typename O,
	typename ArithmeticType,
	typename = hamon::enable_if_t<
		hamon::is_arithmetic<ArithmeticType>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR quantity<T, D, S, O>
operator/(
	quantity<T, D, S, O> const& lhs,
	ArithmeticType rhs) HAMON_NOEXCEPT
{
	using Q = quantity<T, D, S, O>;
	using Q2 = detail::quantity_without_offset_t<Q>;
	using CT = hamon::common_type_t<T, ArithmeticType>;
	return Q { Q2 { static_cast<T>(static_cast<CT>(Q2 { lhs }.value()) / static_cast<CT>(rhs)) } };
}

/**
 *	@brief	Scalar / quantity
 */
template <
	typename T, typename D, typename S, typename O,
	typename ArithmeticType,
	typename = hamon::enable_if_t<
		hamon::is_arithmetic<ArithmeticType>::value
	>
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator/(
	ArithmeticType lhs,
	quantity<T, D, S, O> const& rhs) HAMON_NOEXCEPT
-> detail::quantity_divide_result_t<
	dimensionless<ArithmeticType>,
	quantity<T, D, S, O>>
{
#if defined(HAMON_MSVC) && (HAMON_MSVC == 1900)
	using Q1 = dimensionless<ArithmeticType>;
	using Q2 = quantity<T, D, S, O>;
	using result_type = detail::quantity_divide_result_t<Q1, Q2>;
	return result_type
	{
		detail::quantity_without_scale_offset_t<result_type>
		{
			detail::quantity_without_scale_offset_t<Q1>{lhs}.value() /
			detail::quantity_without_scale_offset_t<Q2>{rhs}.value()
		}
	};
	// MSVC14 だと何故か↓のコードがconstexprにならない
#else
	return dimensionless<ArithmeticType>(lhs) / rhs;
#endif
}

/**
 *	@brief	quantity /= Scalar
 */
template <
	typename T, typename D, typename S, typename O,
	typename ArithmeticType,
	typename = hamon::enable_if_t<
		hamon::is_arithmetic<ArithmeticType>::value
	>
>
inline HAMON_CXX14_CONSTEXPR quantity<T, D, S, O>&
operator/=(
	quantity<T, D, S, O>& lhs,
	ArithmeticType rhs) HAMON_NOEXCEPT
{
	return lhs = lhs / rhs;
}

/**
 *	@brief	quantity / quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator/(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
-> detail::quantity_divide_result_t<
	quantity<T1, D1, S1, O1>,
	quantity<T2, D2, S2, O2>>
{
	using Q1 = quantity<T1, D1, S1, O1>;
	using Q2 = quantity<T2, D2, S2, O2>;
	using Q3 = detail::quantity_divide_result_t<Q1, Q2>;
	using Q1_2 = detail::quantity_without_scale_offset_t<Q1>;
	using Q2_2 = detail::quantity_without_scale_offset_t<Q2>;
	using Q3_2 = detail::quantity_without_scale_offset_t<Q3>;
	using T3 = typename Q3_2::value_type;
	return Q3
	{
		Q3_2
		{
			static_cast<T3>(Q1_2{lhs}.value()) /
			static_cast<T3>(Q2_2{rhs}.value())
		}
	};
}

/**
 *	@brief	quantity == quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	using type = detail::quantity_common_type_t<
		quantity<T1, D1, S1, O1>,
		quantity<T2, D2, S2, O2>>;
	return type{lhs}.value() == type{rhs}.value();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON) && defined(HAMON_HAS_STD_COMPARE)

/**
 *	@brief	quantity <=> quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator<=>(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs)
{
	using type = detail::quantity_common_type_t<
		quantity<T1, D1, S1, O1>,
		quantity<T2, D2, S2, O2>>;
	return type{lhs}.value() <=> type{rhs}.value();
}

#else

/**
 *	@brief	quantity < quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	using type = detail::quantity_common_type_t<
		quantity<T1, D1, S1, O1>,
		quantity<T2, D2, S2, O2>>;
	return type{lhs}.value() < type{rhs}.value();
}

/**
 *	@brief	quantity != quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

/**
 *	@brief	quantity > quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	return rhs < lhs;
}


/**
 *	@brief	quantity <= quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<=(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	return !(rhs < lhs);
}

/**
 *	@brief	quantity >= quantity
 */
template <
	typename T1, typename D1, typename S1, typename O1,
	typename T2, typename D2, typename S2, typename O2
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>=(
	quantity<T1, D1, S1, O1> const& lhs,
	quantity<T2, D2, S2, O2> const& rhs) HAMON_NOEXCEPT
{
	return !(lhs < rhs);
}

#endif

/**
 *	@brief	ストリームへの出力
 */
template <
	typename E, typename T,
	typename U, typename D, typename S, typename O
>
inline std::basic_ostream<E, T>&
operator<<(std::basic_ostream<E, T>& os, quantity<U, D, S, O> const& rhs)
{
	return os << rhs.value();
}

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_QUANTITY_HPP
