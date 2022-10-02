/**
 *	@file	strong_ordering.hpp
 *
 *	@brief	strong_ordering の定義
 */

#ifndef HAMON_COMPARE_STRONG_ORDERING_HPP
#define HAMON_COMPARE_STRONG_ORDERING_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::strong_ordering;

}	// namespace hamon

#else

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/detail/cmp_cat.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if !defined(HAMON_COMPARE_USE_INLINE_VARIABLES)
template <typename>
#endif
class strong_ordering_t
{
private:
	cmp_cat::type m_value;

	HAMON_CONSTEXPR explicit
	strong_ordering_t(cmp_cat::Ord v) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(v))
	{}

public:
	static const strong_ordering_t less;
	static const strong_ordering_t equal;
	static const strong_ordering_t equivalent;
	static const strong_ordering_t greater;

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	// * extension *
	// std::strong_ordering からの変換
	HAMON_CONSTEXPR
	strong_ordering_t(std::strong_ordering ord) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::strong_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::strong_ordering::greater ? cmp_cat::Ord::greater :
			                                       cmp_cat::Ord::equivalent))
	{}
#endif

	HAMON_CONSTEXPR operator partial_ordering() const HAMON_NOEXCEPT
	{
		return
			m_value == cmp_cat::type(cmp_cat::Ord::less) ?
				partial_ordering::less :
			m_value == cmp_cat::type(cmp_cat::Ord::greater) ?
				partial_ordering::greater :
			    partial_ordering::equivalent;
	}

	HAMON_CONSTEXPR operator weak_ordering() const HAMON_NOEXCEPT
	{
		return
			m_value == cmp_cat::type(cmp_cat::Ord::less) ?
				weak_ordering::less :
			m_value == cmp_cat::type(cmp_cat::Ord::greater) ?
				weak_ordering::greater :
			    weak_ordering::equivalent;
	}

	// comparisons
	friend HAMON_CONSTEXPR bool
	operator==(strong_ordering_t lhs, strong_ordering_t rhs) HAMON_NOEXCEPT
	{
		return lhs.m_value == rhs.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator==(strong_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value == 0;
	}

	friend HAMON_CONSTEXPR bool
	operator< (strong_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value < 0;
	}

	friend HAMON_CONSTEXPR bool
	operator> (strong_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value > 0;
	}

	friend HAMON_CONSTEXPR bool
	operator<=(strong_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value <= 0;
	}

	friend HAMON_CONSTEXPR bool
	operator>=(strong_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value >= 0;
	}

	friend HAMON_CONSTEXPR bool
	operator< (cmp_cat::unspec, strong_ordering_t v) HAMON_NOEXCEPT
	{
		return 0 < v.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator> (cmp_cat::unspec, strong_ordering_t v) HAMON_NOEXCEPT
	{
		return 0 > v.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator<=(cmp_cat::unspec, strong_ordering_t v) HAMON_NOEXCEPT
	{
		return 0 <= v.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator>=(cmp_cat::unspec, strong_ordering_t v) HAMON_NOEXCEPT
	{
		return 0 >= v.m_value;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CONSTEXPR strong_ordering_t
	operator<=>(strong_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v;
	}

	friend HAMON_CONSTEXPR strong_ordering_t
	operator<=>(cmp_cat::unspec, strong_ordering_t v) HAMON_NOEXCEPT
	{
		return strong_ordering_t(cmp_cat::Ord(-v.m_value));
	}
#else
	friend HAMON_CONSTEXPR bool
	operator!=(strong_ordering_t lhs, strong_ordering_t rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend HAMON_CONSTEXPR bool
	operator!=(strong_ordering_t lhs, cmp_cat::unspec rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend HAMON_CONSTEXPR bool
	operator==(cmp_cat::unspec lhs, strong_ordering_t rhs) HAMON_NOEXCEPT
	{
		return rhs == lhs;
	}

	friend HAMON_CONSTEXPR bool
	operator!=(cmp_cat::unspec lhs, strong_ordering_t rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif
};

#if defined(HAMON_COMPARE_USE_INLINE_VARIABLES)

using strong_ordering = strong_ordering_t;

inline HAMON_CONSTEXPR strong_ordering strong_ordering::less(cmp_cat::Ord::less);
inline HAMON_CONSTEXPR strong_ordering strong_ordering::equal(cmp_cat::Ord::equivalent);
inline HAMON_CONSTEXPR strong_ordering strong_ordering::equivalent(cmp_cat::Ord::equivalent);
inline HAMON_CONSTEXPR strong_ordering strong_ordering::greater(cmp_cat::Ord::greater);

#else

using strong_ordering = strong_ordering_t<void>;

template <typename T> strong_ordering_t<T> const strong_ordering_t<T>::less(cmp_cat::Ord::less);
template <typename T> strong_ordering_t<T> const strong_ordering_t<T>::equal(cmp_cat::Ord::equivalent);
template <typename T> strong_ordering_t<T> const strong_ordering_t<T>::equivalent(cmp_cat::Ord::equivalent);
template <typename T> strong_ordering_t<T> const strong_ordering_t<T>::greater(cmp_cat::Ord::greater);

#endif

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_STRONG_ORDERING_HPP
