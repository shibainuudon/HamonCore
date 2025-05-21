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

#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <initializer_list>

#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_expected
	: public hamon::false_type {};

template <typename T>
struct is_specialization_of_unexpected
	: public hamon::false_type {};


template <typename T, typename E>
struct expected_impl
{
	bool has_val;
	union
	{
		T val;
		E unex;
	};

	template <typename... Args>
	constexpr explicit
	expected_impl(hamon::in_place_t, Args&&... args)
		: has_val(true)
		, val(hamon::forward<Args>(args)...)
	{}

	template <typename... Args>
	constexpr explicit
	expected_impl(hamon::unexpect_t, Args&&... args)
		: has_val(false)
		, unex(hamon::forward<Args>(args)...)
	{}

	constexpr ~expected_impl()
		requires(hamon::is_trivially_destructible<T>::value && hamon::is_trivially_destructible<E>::value)
	= default;

	constexpr ~expected_impl()
		requires(!hamon::is_trivially_destructible<T>::value || !hamon::is_trivially_destructible<E>::value)
	{
		this->destroy();
	}

	static constexpr expected_impl
	make(expected_impl const& x)
	{
		if (x.has_val)
		{
			return expected_impl{hamon::in_place, x.val};
		}
		else
		{
			return expected_impl{hamon::unexpect, x.unex};
		}
	}

	static constexpr expected_impl
	make(expected_impl&& x)
	{
		if (x.has_val)
		{
			return expected_impl{hamon::in_place, hamon::move(x.val)};
		}
		else
		{
			return expected_impl{hamon::unexpect, hamon::move(x.unex)};
		}
	}

private:
	constexpr void destroy()
	{
		if (has_val)
		{
			hamon::destroy_at(hamon::addressof(val));
		}
		else
		{
			hamon::destroy_at(hamon::addressof(unex));
		}
	}
};

}	// namespace detail

// 22.8.6 Class template expected[expected.expected]

template <typename T, typename E>
class expected
{
private:
	using Impl = hamon::detail::expected_impl<T, E>;

public:
	using value_type = T;
	using error_type = E;
	using unexpected_type = unexpected<E>;

	template <typename U>
	using rebind = expected<U, error_type>;

	// [expected.object.cons], constructors
	constexpr expected()
		requires(hamon::is_default_constructible_v<T>)	// [expected.object.cons]/2
		: m_impl(hamon::in_place)	// [expected.object.cons]/3
	{}

	constexpr expected(expected const& rhs) = delete;

	constexpr expected(expected const& rhs)
		requires(
			hamon::is_copy_constructible<T>::value &&	// [expected.object.cons]/9.1
			hamon::is_copy_constructible<E>::value &&	// [expected.object.cons]/9.2
			hamon::is_trivially_copy_constructible<T>::value &&	// [expected.object.cons]/10.1
			hamon::is_trivially_copy_constructible<E>::value)  	// [expected.object.cons]/10.2
	= default;

	constexpr expected(expected const& rhs)
		requires(
			hamon::is_copy_constructible<T>::value &&	// [expected.object.cons]/9.1
			hamon::is_copy_constructible<E>::value &&	// [expected.object.cons]/9.2
			!(hamon::is_trivially_copy_constructible<T>::value &&	// [expected.object.cons]/10.1
			  hamon::is_trivially_copy_constructible<E>::value)) 	// [expected.object.cons]/10.2
		: m_impl(Impl::make(rhs.m_impl))	// [expected.object.cons]/6
	{}

	constexpr expected(expected&& rhs) = delete;

	constexpr expected(expected&& rhs)
		requires(
			hamon::is_move_constructible<T>::value &&	// [expected.object.cons]/11.1
			hamon::is_move_constructible<E>::value &&	// [expected.object.cons]/11.2
			hamon::is_trivially_move_constructible<T>::value &&	// [expected.object.cons]/16.1
			hamon::is_trivially_move_constructible<E>::value)  	// [expected.object.cons]/16.2
	= default;

	constexpr expected(expected&& rhs) noexcept(	// [expected.object.cons]/15
		hamon::is_nothrow_move_constructible<T>::value &&
		hamon::is_nothrow_move_constructible<E>::value)
		requires(
			hamon::is_move_constructible<T>::value &&	// [expected.object.cons]/11.1
			hamon::is_move_constructible<E>::value &&	// [expected.object.cons]/11.2
			!(hamon::is_trivially_move_constructible<T>::value &&	// [expected.object.cons]/16.1
			  hamon::is_trivially_move_constructible<E>::value)) 	// [expected.object.cons]/16.2
		: m_impl(Impl::make(hamon::move(rhs.m_impl)))	// [expected.object.cons]/12
	{}

	template <typename U, typename G,
		typename UF = U const&,
		typename GF = G const&
	>
	constexpr explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G> const& rhs);

	template <typename U, typename G,
		typename UF = U,
		typename GF = G
	>
	constexpr explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G>&& rhs);

	template <typename U = hamon::remove_cv_t<T>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<U>, hamon::in_place_t>>,
			hamon::negation<hamon::is_same<hamon::expected<T, E>, hamon::remove_cvref_t<U>>>,
			hamon::negation<hamon::detail::is_specialization_of_unexpected<hamon::remove_cvref_t<U>>>,
			hamon::is_constructible<T, U>,
			hamon::negation<hamon::conjunction<
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::detail::is_specialization_of_expected<hamon::remove_cvref_t<U>>
			>>
		>::value>
	>
	constexpr explicit(!hamon::is_convertible_v<U, T>)
	expected(U&& v)
		: m_impl(hamon::in_place, hamon::forward<U>(v))
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value
		>
	>
	constexpr explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const& e)
		: m_impl(hamon::unexpect, e.error())
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value
		>
	>
	constexpr explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&& e)
		: m_impl(hamon::unexpect, hamon::move(e.error()))
	{}

	template <typename... Args>
	constexpr explicit
	expected(hamon::in_place_t, Args&&... args)
		: m_impl(hamon::in_place, hamon::forward<Args>(args)...)
	{}

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::in_place_t, std::initializer_list<U>, Args&&...);

	template <typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, Args&&... args)
		: m_impl(hamon::unexpect, hamon::forward<Args>(args)...)
	{}

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, std::initializer_list<U>, Args&&...);

	// [expected.object.dtor], destructor
	constexpr ~expected() = default;

	// [expected.object.assign], assignment
	constexpr expected&
	operator=(expected const&);

	constexpr expected&
	operator=(expected&&) noexcept;//(see below);

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
		noexcept;//(see below);

	friend constexpr void
	swap(expected& x, expected& y)
		noexcept(noexcept(x.swap(y)));

	// [expected.object.obs], observers
	constexpr T const*
	operator->() const noexcept
	{
		// [expected.object.obs]/1
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/2
		return hamon::addressof(m_impl.val);
	}

	constexpr T*
	operator->() noexcept
	{
		// [expected.object.obs]/1
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/2
		return hamon::addressof(m_impl.val);
	}

	constexpr T const&
	operator*() const& noexcept
	{
		// [expected.object.obs]/3
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/4
		return m_impl.val;
	}

	constexpr T&
	operator*() & noexcept
	{
		// [expected.object.obs]/3
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/4
		return m_impl.val;
	}

	constexpr T const&&
	operator*() const&& noexcept
	{
		// [expected.object.obs]/5
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/6
		return hamon::move(m_impl.val);
	}

	constexpr T&&
	operator*() && noexcept
	{
		// [expected.object.obs]/5
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/6
		return hamon::move(m_impl.val);
	}

	constexpr explicit
	operator bool() const noexcept
	{
		// [expected.object.obs]/7
		return m_impl.has_val;
	}

	constexpr bool
	has_value() const noexcept
	{
		// [expected.object.obs]/7
		return m_impl.has_val;
	}

	constexpr T const&
	value() const&
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		if (!this->has_value())
		{
			hamon::detail::throw_bad_expected_access<E>(hamon::as_const(this->error()));
		}
		return m_impl.val;
	}

	constexpr T&
	value() &
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		if (!this->has_value())
		{
			hamon::detail::throw_bad_expected_access<E>(hamon::as_const(this->error()));
		}
		return m_impl.val;
	}

	constexpr T const&&
	value() const&&
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_constructible<E, decltype(hamon::move(this->error()))>::value, "");
		if (!this->has_value())
		{
			hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error()));
		}
		return hamon::move(m_impl.val);
	}

	constexpr T&&
	value() &&
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_constructible<E, decltype(hamon::move(this->error()))>::value, "");
		if (!this->has_value())
		{
			hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error()));
		}
		return hamon::move(m_impl.val);
	}

	constexpr E const&
	error() const& noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return m_impl.unex;
	}

	constexpr E&
	error() & noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return m_impl.unex;
	}

	constexpr E const&&
	error() const&& noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return hamon::move(m_impl.unex);
	}

	constexpr E&&
	error() && noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return hamon::move(m_impl.unex);
	}

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
	Impl	m_impl;
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
	constexpr expected(expected&&) noexcept;//(see below);

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
	operator=(expected&&) noexcept;//(see below);

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
	swap(expected&) noexcept;//(see below);

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
