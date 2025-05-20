/**
 *	@file	expected.hpp
 *
 *	@brief	expected の定義
 */

#ifndef HAMON_EXPECTED_EXPECTED_HPP
#define HAMON_EXPECTED_EXPECTED_HPP

#include <hamon/expected/config.hpp>

#if defined(HAMON_USE_STD_EXPECTED)

#include <expected>

namespace hamon
{

using std::expected;

}	// namespace hamon

#else

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <initializer_list>

namespace hamon
{

// in-place construction of unexpected values
struct unexpect_t
{
	explicit unexpect_t() = default;
};
inline constexpr unexpect_t unexpect {};

// 22.8.6 Class template expected[expected.expected]

template <typename T, typename E>
class expected
{
public:
	using value_type = T;
	using error_type = E;
	using unexpected_type = unexpected<E>;

	template <typename U>
	using rebind = expected<U, error_type>;

	// [expected.object.cons], constructors
	constexpr expected()
		requires(hamon::is_default_constructible_v<T>)	// [expected.object.cons]/2
		: has_val(true)	// [expected.object.cons]/4
		, val()	// [expected.object.cons]/3
	{}

	constexpr expected(expected const&);
	constexpr expected(expected&&) noexcept(see below);

	template <typename U, typename G,
		typename UF = U const&,
		typename GF = G const&
	>
	constexpr explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G> const&);

	template <typename U, typename G,
		typename UF = U,
		typename GF = G
	>
	constexpr explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G>&&);

	template <typename U = hamon::remove_cv_t<T>>
	constexpr explicit(!hamon::is_convertible_v<U, T>)
	expected(U&& v);

	template <typename G>
	constexpr explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const&);

	template <typename G>
	constexpr explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&&);

	template <typename... Args>
	constexpr explicit
	expected(hamon::in_place_t, Args&&...);

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::in_place_t, std::initializer_list<U>, Args&&...);

	template <typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, Args&&...);

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, std::initializer_list<U>, Args&&...);

	// [expected.object.dtor], destructor
	constexpr
	~expected();

	// [expected.object.assign], assignment
	constexpr expected&
	operator=(expected const&);

	constexpr expected&
	operator=(expected&&) noexcept(see below);

	template <typename U = hamon::remove_cv_t<T>>
	constexpr expected&
	operator=(U&&);

	template <typename G>
	constexpr expected&
	operator=(unexpected<G> const&);

	template <typename G>
	constexpr expected&
	operator=(unexpected<G>&&);

	template <typename... Args>
	constexpr T&
	emplace(Args&&...) noexcept;

	template <typename U, typename... Args>
	constexpr T&
	emplace(std::initializer_list<U>, Args&&...) noexcept;

	// [expected.object.swap], swap
	constexpr void
	swap(expected&)
		noexcept(see below);

	friend constexpr void
	swap(expected& x, expected& y)
		noexcept(noexcept(x.swap(y)));

	// [expected.object.obs], observers
	constexpr T const*
	operator->() const noexcept;

	constexpr T*
	operator->() noexcept;

	constexpr T const&
	operator*() const& noexcept;

	constexpr T&
	operator*() & noexcept;

	constexpr T const&&
	operator*() const&& noexcept;

	constexpr T&&
	operator*() && noexcept;

	constexpr explicit
	operator bool() const noexcept;

	constexpr bool
	has_value() const noexcept;

	constexpr T const&
	value() const&;

	constexpr T&
	value() &;

	constexpr T const&&
	value() const&&;

	constexpr T&&
	value() &&;

	constexpr E const&
	error() const& noexcept;

	constexpr E&
	error() & noexcept;

	constexpr E const&&
	error() const&& noexcept;

	constexpr E&&
	error() && noexcept;

	template <typename U = hamon::remove_cv_t<T>>
	constexpr T
	value_or(U&&) const&;

	template <typename U = hamon::remove_cv_t<T>>
	constexpr T
	value_or(U&&) &&;

	template <typename G = E>
	constexpr E
	error_or(G&&) const&;

	template <typename G = E>
	constexpr E
	error_or(G&&) &&;

	// [expected.object.monadic], monadic operations
	template <typename F>
	constexpr auto
	and_then(F&& f) &;

	template <typename F>
	constexpr auto
	and_then(F&& f) &&;

	template <typename F>
	constexpr auto
	and_then(F&& f) const&;

	template <typename F>
	constexpr auto
	and_then(F&& f) const&&;

	template <typename F>
	constexpr auto
	or_else(F&& f) &;

	template <typename F>
	constexpr auto
	or_else(F&& f) &&;

	template <typename F>
	constexpr auto
	or_else(F&& f) const&;

	template <typename F>
	constexpr auto
	or_else(F&& f) const&&;

	template <typename F>
	constexpr auto
	transform(F&& f) &;

	template <typename F>
	constexpr auto
	transform(F&& f) &&;

	template <typename F>
	constexpr auto
	transform(F&& f) const&;

	template <typename F>
	constexpr auto
	transform(F&& f) const&&;

	template <typename F>
	constexpr auto
	transform_error(F&& f) &;

	template <typename F>
	constexpr auto
	transform_error(F&& f) &&;

	template <typename F>
	constexpr auto
	transform_error(F&& f) const&;

	template <typename F>
	constexpr auto
	transform_error(F&& f) const&&;

	// [expected.object.eq], equality operators
	template <typename T2, typename E2>
		requires (!hamon::is_void_v<T2>)
	friend constexpr bool
	operator==(expected const& x, expected<T2, E2> const& y);

	template <typename T2>
	friend constexpr bool
	operator==(expected const&, T2 const&);

	template <typename E2>
	friend constexpr bool
	operator==(expected const&, unexpected<E2> const&);

private:
	bool has_val;       // exposition only
	union
	{
		T val;            // exposition only
		E unex;           // exposition only
	};
};

// 22.8.7 Partial specialization of expected for void types[expected.void]

template <typename T, typename E>
	requires hamon::is_void_v<T>
class expected<T, E>
{
public:
	using value_type = T;
	using error_type = E;
	using unexpected_type = unexpected<E>;

	template <typename U>
	using rebind = expected<U, error_type>;

	// [expected.void.cons], constructors
	constexpr expected() noexcept;
	constexpr expected(expected const&);
	constexpr expected(expected&&) noexcept(see below);

	template <typename U, typename G>
	constexpr explicit(!hamon::is_convertible_v<G const&, E>)
	expected(expected<U, G> const&);

	template <typename U, typename G>
	constexpr explicit(!hamon::is_convertible_v<G, E>)
	expected(expected<U, G>&&);

	template <typename G>
	constexpr explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const&);

	template <typename G>
	constexpr explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&&);

	constexpr explicit
	expected(hamon::in_place_t) noexcept;

	template <typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, Args&&...);

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, std::initializer_list<U>, Args&&...);


	// [expected.void.dtor], destructor
	constexpr
	~expected();

	// [expected.void.assign], assignment
	constexpr expected&
	operator=(expected const&);

	constexpr expected&
	operator=(expected&&) noexcept(see below);

	template <typename G>
	constexpr expected&
	operator=(unexpected<G> const&);

	template <typename G>
	constexpr expected&
	operator=(unexpected<G>&&);

	constexpr void
	emplace() noexcept;

	// [expected.void.swap], swap
	constexpr void
	swap(expected&) noexcept(see below);

	friend constexpr void
	swap(expected& x, expected& y)
		noexcept(noexcept(x.swap(y)));

	// [expected.void.obs], observers
	constexpr explicit
	operator bool() const noexcept;

	constexpr bool
	has_value() const noexcept;

	constexpr void
	operator*() const noexcept;

	constexpr void
	value() const&;

	constexpr void
	value() &&;

	constexpr E const&
	error() const& noexcept;

	constexpr E&
	error() & noexcept;

	constexpr E const&&
	error() const&& noexcept;

	constexpr E&&
	error() && noexcept;

	template <typename G = E>
	constexpr E
	error_or(G&&) const&;

	template <typename G = E>
	constexpr E
	error_or(G&&) &&;

	// [expected.void.monadic], monadic operations
	template <typename F>
	constexpr auto
	and_then(F&& f) &;

	template <typename F>
	constexpr auto
	and_then(F&& f) &&;

	template <typename F>
	constexpr auto
	and_then(F&& f) const&;

	template <typename F>
	constexpr auto
	and_then(F&& f) const&&;

	template <typename F>
	constexpr auto
	or_else(F&& f) &;

	template <typename F>
	constexpr auto
	or_else(F&& f) &&;

	template <typename F>
	constexpr auto
	or_else(F&& f) const&;

	template <typename F>
	constexpr auto
	or_else(F&& f) const&&;

	template <typename F>
	constexpr auto
	transform(F&& f) &;

	template <typename F>
	constexpr auto
	transform(F&& f) &&;

	template <typename F>
	constexpr auto
	transform(F&& f) const&;

	template <typename F>
	constexpr auto
	transform(F&& f) const&&;

	template <typename F>
	constexpr auto
	transform_error(F&& f) &;

	template <typename F>
	constexpr auto
	transform_error(F&& f) &&;

	template <typename F>
	constexpr auto
	transform_error(F&& f) const&;

	template <typename F>
	constexpr auto
	transform_error(F&& f) const&&;

	// [expected.void.eq], equality operators
	template <typename T2, typename E2>
		requires hamon::is_void_v<T2>
	friend constexpr bool
	operator==(expected const& x, expected<T2, E2> const& y);

	template <typename E2>
	friend constexpr bool
	operator==(expected const&, unexpected<E2> const&);

private:
	bool has_val;         // exposition only
	union
	{
		E unex;             // exposition only
	};
};

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_EXPECTED_HPP
