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

#include <hamon/utility/move.hpp>
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

template <typename E>
class bad_expected_access : public bad_expected_access<void>
{
public:
	constexpr explicit
	bad_expected_access(E e)
		: unex(hamon::move(e))	// [expected.bad]/2
	{}

	constexpr const char*
	what() const noexcept override;

	constexpr E&
	error() & noexcept
	{
		return unex;	// [expected.bad]/3
	}

	constexpr E const&
	error() const & noexcept
	{
		return unex;	// [expected.bad]/3
	}

	constexpr E&&
	error() && noexcept
	{
		return hamon::move(unex);	// [expected.bad]/4
	}

	constexpr E const&&
	error() const && noexcept
	{
		return hamon::move(unex);	// [expected.bad]/4
	}

private:
	E unex;             // exposition only
};

template <>
class bad_expected_access<void> : public std::exception
{
protected:
	constexpr bad_expected_access() noexcept;
	constexpr bad_expected_access(bad_expected_access const&) noexcept;
	constexpr bad_expected_access(bad_expected_access&&) noexcept;
	constexpr bad_expected_access& operator=(bad_expected_access const&) noexcept;
	constexpr bad_expected_access& operator=(bad_expected_access&&) noexcept;
	constexpr ~bad_expected_access();

public:
	constexpr const char* what() const noexcept override;
};

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_BAD_EXPECTED_ACCESS_HPP
