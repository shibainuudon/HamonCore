/**
 *	@file	move_sentinel.hpp
 *
 *	@brief	move_sentinel の定義
 */

#ifndef HAMON_ITERATOR_MOVE_SENTINEL_HPP
#define HAMON_ITERATOR_MOVE_SENTINEL_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#include <iterator>

namespace hamon
{

using std::move_sentinel;

}	// namespace hamon

#else

#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept move_sentinel_constructible_from =
	hamon::convertible_to<From const&, To>;

template <typename From, typename To>
concept move_sentinel_assignable_from =
	hamon::assignable_from<To&, From const&>;

#else

template <typename From, typename To>
using move_sentinel_constructible_from =
	hamon::convertible_to<From const&, To>;

template <typename From, typename To>
using move_sentinel_assignable_from =
	hamon::assignable_from<To&, From const&>;

#endif

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::semiregular, Sent)>
class move_sentinel
{
public:
	move_sentinel() = default;

	HAMON_CXX14_CONSTEXPR
	explicit move_sentinel(Sent s)
	HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<Sent>::value)	// extension
		: m_last(hamon::move(s)) {}

	template <HAMON_CONSTRAINED_PARAM(detail::move_sentinel_constructible_from, Sent, S2)>
	HAMON_CXX14_CONSTEXPR move_sentinel(move_sentinel<S2> const& s)
	HAMON_NOEXCEPT_IF((hamon::is_nothrow_constructible<Sent, S2 const&>::value))	// extension
		: m_last(s.base()) {}

	template <HAMON_CONSTRAINED_PARAM(detail::move_sentinel_assignable_from, Sent, S2)>
	HAMON_CXX14_CONSTEXPR move_sentinel&
	operator=(move_sentinel<S2> const& s)
	HAMON_NOEXCEPT_IF((hamon::is_nothrow_assignable<Sent&, S2 const&>::value))	// extension
	{
		m_last = s.base();
		return *this;
	}

	constexpr Sent base() const
	HAMON_NOEXCEPT_IF(hamon::is_nothrow_copy_constructible<Sent>::value)	// extension
	{
		return m_last;
	}

private:
	Sent m_last = Sent();
};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MOVE_SENTINEL_HPP
