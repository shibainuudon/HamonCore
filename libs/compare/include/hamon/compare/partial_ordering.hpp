/**
 *	@file	partial_ordering.hpp
 *
 *	@brief	partial_ordering の定義
 */

#ifndef HAMON_COMPARE_PARTIAL_ORDERING_HPP
#define HAMON_COMPARE_PARTIAL_ORDERING_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::partial_ordering;

}	// namespace hamon

#else

#include <hamon/compare/detail/cmp_cat.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if !defined(HAMON_COMPARE_USE_INLINE_VARIABLES)
template <typename>
#endif
class partial_ordering_t
{
private:
	cmp_cat::type m_value;

	HAMON_CONSTEXPR explicit
	partial_ordering_t(cmp_cat::Ord v) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(v))
	{}

	HAMON_CONSTEXPR explicit
	partial_ordering_t(cmp_cat::Ncmp v) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(v))
	{}

public:
	static const partial_ordering_t less;
	static const partial_ordering_t equivalent;
	static const partial_ordering_t greater;
	static const partial_ordering_t unordered;

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	// * extension *
	// std::partial_ordering からの変換
	HAMON_CONSTEXPR
	partial_ordering_t(std::partial_ordering ord) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::partial_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::partial_ordering::greater ? cmp_cat::Ord::greater :
			                                        cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::weak_ordering からの変換
	HAMON_CONSTEXPR
	partial_ordering_t(std::weak_ordering ord) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::weak_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::weak_ordering::greater ? cmp_cat::Ord::greater :
			                                     cmp_cat::Ord::equivalent))
	{}

	// * extension *
	// std::strong_ordering からの変換
	HAMON_CONSTEXPR
	partial_ordering_t(std::strong_ordering ord) HAMON_NOEXCEPT
		: m_value(cmp_cat::type(
			ord == std::strong_ordering::less    ? cmp_cat::Ord::less    :
			ord == std::strong_ordering::greater ? cmp_cat::Ord::greater :
			                                       cmp_cat::Ord::equivalent))
	{}
#endif

	// comparisons
	friend HAMON_CONSTEXPR bool
	operator==(partial_ordering_t lhs, partial_ordering_t rhs) HAMON_NOEXCEPT
	{
		return lhs.m_value == rhs.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator==(partial_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value == 0;
	}

	friend HAMON_CONSTEXPR bool
	operator< (partial_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value == -1;
	}

	friend HAMON_CONSTEXPR bool
	operator> (partial_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value == 1;
	}

	friend HAMON_CONSTEXPR bool
	operator<=(partial_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v.m_value <= 0;
	}

	friend HAMON_CONSTEXPR bool
	operator>=(partial_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return cmp_cat::type(v.m_value & 1) == v.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator< (cmp_cat::unspec, partial_ordering_t v) HAMON_NOEXCEPT
	{
		return v.m_value == 1;
	}

	friend HAMON_CONSTEXPR bool
	operator> (cmp_cat::unspec, partial_ordering_t v) HAMON_NOEXCEPT
	{
		return v.m_value == -1;
	}

	friend HAMON_CONSTEXPR bool
	operator<=(cmp_cat::unspec, partial_ordering_t v) HAMON_NOEXCEPT
	{
		return cmp_cat::type(v.m_value & 1) == v.m_value;
	}

	friend HAMON_CONSTEXPR bool
	operator>=(cmp_cat::unspec, partial_ordering_t v) HAMON_NOEXCEPT
	{
		return 0 >= v.m_value;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CONSTEXPR partial_ordering_t
	operator<=>(partial_ordering_t v, cmp_cat::unspec) HAMON_NOEXCEPT
	{
		return v;
	}

	friend HAMON_CONSTEXPR partial_ordering_t
	operator<=>(cmp_cat::unspec, partial_ordering_t v) HAMON_NOEXCEPT
	{
		if (v.m_value & 1)
		{
			return partial_ordering_t(cmp_cat::Ord(-v.m_value));
		}
		else
		{
			return v;
		}
	}
#else
	friend HAMON_CONSTEXPR bool
	operator!=(partial_ordering_t lhs, partial_ordering_t rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend HAMON_CONSTEXPR bool
	operator!=(partial_ordering_t lhs, cmp_cat::unspec rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	friend HAMON_CONSTEXPR bool
	operator==(cmp_cat::unspec lhs, partial_ordering_t rhs) HAMON_NOEXCEPT
	{
		return rhs == lhs;
	}

	friend HAMON_CONSTEXPR bool
	operator!=(cmp_cat::unspec lhs, partial_ordering_t rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif
};

#if defined(HAMON_COMPARE_USE_INLINE_VARIABLES)

using partial_ordering = partial_ordering_t;

inline HAMON_CONSTEXPR partial_ordering partial_ordering::less(cmp_cat::Ord::less);
inline HAMON_CONSTEXPR partial_ordering partial_ordering::equivalent(cmp_cat::Ord::equivalent);
inline HAMON_CONSTEXPR partial_ordering partial_ordering::greater(cmp_cat::Ord::greater);
inline HAMON_CONSTEXPR partial_ordering partial_ordering::unordered(cmp_cat::Ncmp::unordered);

#else

using partial_ordering = partial_ordering_t<void>;

template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::less(cmp_cat::Ord::less);
template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::equivalent(cmp_cat::Ord::equivalent);
template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::greater(cmp_cat::Ord::greater);
template <typename T> partial_ordering_t<T> const partial_ordering_t<T>::unordered(cmp_cat::Ncmp::unordered);

#endif

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_PARTIAL_ORDERING_HPP
