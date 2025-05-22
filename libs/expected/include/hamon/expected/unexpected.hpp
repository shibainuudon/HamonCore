/**
 *	@file	unexpected.hpp
 *
 *	@brief	unexpected の定義
 */

#ifndef HAMON_EXPECTED_UNEXPECTED_HPP
#define HAMON_EXPECTED_UNEXPECTED_HPP

#include <hamon/expected/config.hpp>

#if defined(HAMON_USE_STD_EXPECTED)

#include <expected>

namespace hamon
{

using std::unexpected;

}	// namespace hamon

#else

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <initializer_list>

namespace hamon
{

// 22.8.3 Class template unexpected[expected.unexpected]

template <typename E>
class unexpected
{
public:
	// [expected.un.cons], constructors
	constexpr unexpected(unexpected const&) = default;

	constexpr unexpected(unexpected&&) = default;

	template <typename Err = E,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<Err>, unexpected>>,		// [expected.un.cons]/1.1
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<Err>, hamon::in_place_t>>,	// [expected.un.cons]/1.2
			hamon::is_constructible<E, Err>													// [expected.un.cons]/1.3
		>::value>
	>
	constexpr explicit
	unexpected(Err&& e)
		: unex(hamon::forward<Err>(e))	// [expected.un.cons]/2
	{}

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, Args...>::value	// [expected.un.cons]/4
		>
	>
	constexpr explicit
	unexpected(hamon::in_place_t, Args&&... args)
		: unex(hamon::forward<Args>(args)...)	// [expected.un.cons]/5
	{}

	template <typename U, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, std::initializer_list<U>&, Args...>::value	// [expected.un.cons]/7
		>
	>
	constexpr explicit
	unexpected(hamon::in_place_t, std::initializer_list<U> il, Args&&... args)
		: unex(il, hamon::forward<Args>(args)...)	// [expected.un.cons]/8
	{}

	HAMON_CXX14_CONSTEXPR unexpected&
	operator=(unexpected const&) = default;

	HAMON_CXX14_CONSTEXPR unexpected&
	operator=(unexpected&&) = default;

	constexpr E const&
	error() const& noexcept
	{
		return unex;	// [expected.un.obs]/1
	}

	HAMON_CXX14_CONSTEXPR E&
	error() & noexcept
	{
		return unex;	// [expected.un.obs]/1
	}

	constexpr E const&&
	error() const&& noexcept
	{
		return hamon::move(unex);	// [expected.un.obs]/2
	}

	HAMON_CXX14_CONSTEXPR E&&
	error() && noexcept
	{
		return hamon::move(unex);	// [expected.un.obs]/2
	}

	HAMON_CXX14_CONSTEXPR void
	swap(unexpected& other)
		noexcept(hamon::is_nothrow_swappable<E>::value)
	{
		static_assert(hamon::is_swappable<E>::value, "[expected.un.swap]/1");

		// [expected.un.swap]/2
		using std::swap;
		swap(unex, other.unex);
	}

	template <typename E2>
	friend constexpr bool
	operator==(unexpected const& x, unexpected<E2> const& y)
	{
		// [expected.un.eq]/2
		return x.error() == y.error();
	}

	friend HAMON_CXX14_CONSTEXPR void
	swap(unexpected& x, unexpected& y)
		noexcept(noexcept(x.swap(y)))
//		requires(hamon::is_swappable_v<E>)	// [expected.un.swap]/3
	{
		// [expected.un.swap]/4
		x.swap(y);
	}

private:
	E unex;             // exposition only
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename E>
unexpected(E) -> unexpected<E>;

#endif

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_UNEXPECTED_HPP
