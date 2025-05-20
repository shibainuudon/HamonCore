/**
 *	@file	bad_expected_access.hpp
 *
 *	@brief	bad_expected_access の定義
 */

#ifndef HAMON_EXPECTED_BAD_EXPECTED_ACCESS_HPP
#define HAMON_EXPECTED_BAD_EXPECTED_ACCESS_HPP

#include <hamon/expected/config.hpp>

#if defined(HAMON_USE_STD_EXPECTED)

#include <expected>

namespace hamon
{

using std::bad_expected_access;

}	// namespace hamon

#else

#include <hamon/cstdlib/abort.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <exception>

namespace hamon
{

// [expected.bad], class template bad_expected_access
template <typename E>
class bad_expected_access;

// [expected.bad.void], specialization for void
template <>
class bad_expected_access<void>;

// 22.8.4 Class template bad_expected_access[expected.bad]

template <>
class bad_expected_access<void> : public std::exception
{
protected:
	/*constexpr*/ bad_expected_access()                                      noexcept = default;
	/*constexpr*/ bad_expected_access(bad_expected_access const&)            noexcept = default;
	/*constexpr*/ bad_expected_access(bad_expected_access&&)                 noexcept = default;
	/*constexpr*/ bad_expected_access& operator=(bad_expected_access const&) noexcept = default;
	/*constexpr*/ bad_expected_access& operator=(bad_expected_access&&)      noexcept = default;
	/*constexpr*/ ~bad_expected_access() override                                     = default;

public:
	HAMON_CXX20_CONSTEXPR const char*
	what() const HAMON_NOEXCEPT override
	{
		return "bad access to hamon::expected";
	}
};

template <typename E>
class bad_expected_access : public bad_expected_access<void>
{
public:
	HAMON_CXX11_CONSTEXPR explicit
	bad_expected_access(E e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<E>::value)
		: unex(hamon::move(e))	// [expected.bad]/2
	{}

	//constexpr const char*
	//what() const noexcept override;

	HAMON_CXX14_CONSTEXPR E&
	error() & HAMON_NOEXCEPT
	{
		return unex;	// [expected.bad]/3
	}

	HAMON_CXX11_CONSTEXPR E const&
	error() const & HAMON_NOEXCEPT
	{
		return unex;	// [expected.bad]/3
	}

	HAMON_CXX14_CONSTEXPR E&&
	error() && HAMON_NOEXCEPT
	{
		return hamon::move(unex);	// [expected.bad]/4
	}

	HAMON_CXX11_CONSTEXPR E const&&
	error() const && HAMON_NOEXCEPT
	{
		return hamon::move(unex);	// [expected.bad]/4
	}

private:
	E unex;             // exposition only
};

namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

template <typename E, typename Arg>
HAMON_NORETURN inline void
throw_bad_expected_access(Arg&& arg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::bad_expected_access<E>(hamon::forward<Arg>(arg));
#else
	(void)arg;
	hamon::abort();
#endif
}

HAMON_WARNING_POP()

}	// namespace detail

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_BAD_EXPECTED_ACCESS_HPP
