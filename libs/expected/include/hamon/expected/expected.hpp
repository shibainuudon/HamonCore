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

#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>

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

struct expected_ctor_tag{};

template <typename T, typename E,
	bool = hamon::is_trivially_destructible<T>::value &&	// [expected.object.dtor]/2
	       hamon::is_trivially_destructible<E>::value>
struct expected_union
{
	bool has_val;
	union
	{
		T val;
		E unex;
	};

	template <typename... Args>
	constexpr explicit
	expected_union(hamon::in_place_t, Args&&... args)
		: has_val(true)
		, val(hamon::forward<Args>(args)...)
	{}

	template <typename... Args>
	constexpr explicit
	expected_union(hamon::unexpect_t, Args&&... args)
		: has_val(false)
		, unex(hamon::forward<Args>(args)...)
	{}

	constexpr explicit
	expected_union(bool has_val_)
		: has_val(has_val_)
	{}

	// [expected.object.dtor]/1
	HAMON_CXX20_CONSTEXPR
	~expected_union()
	{
		if (has_val)
		{
			this->val.~T();
		}
		else
		{
			this->unex.~E();
		}
	}
};

template <typename T, typename E>
struct expected_union<T, E, true>
{
	bool has_val;
	union
	{
		T val;
		E unex;
	};

	template <typename... Args>
	constexpr explicit
	expected_union(hamon::in_place_t, Args&&... args)
		: has_val(true)
		, val(hamon::forward<Args>(args)...)
	{}

	template <typename... Args>
	constexpr explicit
	expected_union(hamon::unexpect_t, Args&&... args)
		: has_val(false)
		, unex(hamon::forward<Args>(args)...)
	{}

	constexpr explicit
	expected_union(bool has_val_)
		: has_val(has_val_)
	{}

	// [expected.object.dtor]/2
	// ~expected_union();
};

template <typename T, typename E>
struct expected_impl : expected_union<T, E>
{
	using base_type = expected_union<T, E>;
	using base_type::base_type;

	HAMON_CXX14_CONSTEXPR explicit
	expected_impl(expected_ctor_tag, expected_impl<T, E> const& rhs)
		: base_type(rhs.has_val)
	{
		if (this->has_val)
		{
			hamon::construct_at(hamon::addressof(this->val), rhs.val);
		}
		else
		{
			hamon::construct_at(hamon::addressof(this->unex), rhs.unex);
		}
	}

	HAMON_CXX14_CONSTEXPR explicit
	expected_impl(expected_ctor_tag, expected_impl<T, E>&& rhs)
		: base_type(rhs.has_val)
	{
		if (this->has_val)
		{
			hamon::construct_at(hamon::addressof(this->val), hamon::move(rhs.val));
		}
		else
		{
			hamon::construct_at(hamon::addressof(this->unex), hamon::move(rhs.unex));
		}
	}
};

template <typename T, typename E,
	bool = hamon::is_default_constructible<T>::value	// [expected.object.cons]/2
>
struct expected_ctor_default : expected_impl<T, E>
{
	using base_type = expected_impl<T, E>;
	using base_type::base_type;

	expected_ctor_default() = delete;
};

template <typename T, typename E>
struct expected_ctor_default<T, E, true> : expected_impl<T, E>
{
	using base_type = expected_impl<T, E>;
	using base_type::base_type;

	constexpr
	expected_ctor_default() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<T>::value)
		: base_type(hamon::in_place)	// [expected.object.cons]/3
	{}
};

template <typename T, typename E,
	bool = hamon::is_copy_constructible<T>::value &&			// [expected.object.cons]/9.1
	       hamon::is_copy_constructible<E>::value,				// [expected.object.cons]/9.2
	bool = hamon::is_trivially_copy_constructible<T>::value &&	// [expected.object.cons]/10.1
	       hamon::is_trivially_copy_constructible<E>::value		// [expected.object.cons]/10.2
>
struct expected_ctor_copy : expected_ctor_default<T, E>
{
	using base_type = expected_ctor_default<T, E>;
	using base_type::base_type;

	constexpr expected_ctor_copy() = default;
	constexpr expected_ctor_copy(expected_ctor_copy&&) = default;

	// [expected.object.cons]/9
	constexpr expected_ctor_copy(expected_ctor_copy const& rhs) = delete;
};

template <typename T, typename E>
struct expected_ctor_copy<T, E, true, true> : expected_ctor_default<T, E>
{
	using base_type = expected_ctor_default<T, E>;
	using base_type::base_type;

	constexpr expected_ctor_copy() = default;
	constexpr expected_ctor_copy(expected_ctor_copy&&) = default;

	// [expected.object.cons]/10
	constexpr expected_ctor_copy(expected_ctor_copy const& rhs) = default;
};

template <typename T, typename E>
struct expected_ctor_copy<T, E, true, false> : expected_ctor_default<T, E>
{
	using base_type = expected_ctor_default<T, E>;
	using base_type::base_type;

	constexpr expected_ctor_copy() = default;
	constexpr expected_ctor_copy(expected_ctor_copy&&) = default;

	// [expected.object.cons]/6
	constexpr
	expected_ctor_copy(expected_ctor_copy const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<T>::value &&
		hamon::is_nothrow_copy_constructible<E>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}
};

template <typename T, typename E,
	bool = hamon::is_move_constructible<T>::value &&			// [expected.object.cons]/11.1
	       hamon::is_move_constructible<E>::value,				// [expected.object.cons]/11.2
	bool = hamon::is_trivially_move_constructible<T>::value &&	// [expected.object.cons]/16.1
	       hamon::is_trivially_move_constructible<E>::value		// [expected.object.cons]/16.2
>
struct expected_ctor_move : expected_ctor_copy<T, E>
{
	using base_type = expected_ctor_copy<T, E>;
	using base_type::base_type;

	constexpr expected_ctor_move() = default;
	constexpr expected_ctor_move(expected_ctor_move const& rhs) = default;

	// [expected.object.cons]/11
	constexpr expected_ctor_move(expected_ctor_move&& rhs) = delete;
};

template <typename T, typename E>
struct expected_ctor_move<T, E, true, true> : expected_ctor_copy<T, E>
{
	using base_type = expected_ctor_copy<T, E>;
	using base_type::base_type;

	constexpr expected_ctor_move() = default;
	constexpr expected_ctor_move(expected_ctor_move const& rhs) = default;

	// [expected.object.cons]/16
	constexpr expected_ctor_move(expected_ctor_move&& rhs) = default;
};

template <typename T, typename E>
struct expected_ctor_move<T, E, true, false> : expected_ctor_copy<T, E>
{
	using base_type = expected_ctor_copy<T, E>;
	using base_type::base_type;

	constexpr expected_ctor_move() = default;
	constexpr expected_ctor_move(expected_ctor_move const& rhs) = default;

	// [expected.object.cons]/12
	constexpr
	expected_ctor_move(expected_ctor_move&& rhs) HAMON_NOEXCEPT_IF(	// [expected.object.cons]/15
		hamon::is_nothrow_move_constructible<T>::value &&
		hamon::is_nothrow_move_constructible<E>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}
};

template <typename T, typename E>
using expected_base = expected_ctor_move<T, E>;

}	// namespace detail

// 22.8.6 Class template expected[expected.expected]

template <typename T, typename E>
class expected : private hamon::detail::expected_base<T, E>
{
private:
	using base_type = hamon::detail::expected_base<T, E>;

public:
	using value_type = T;
	using error_type = E;
	using unexpected_type = unexpected<E>;

	template <typename U>
	using rebind = expected<U, error_type>;

	// [expected.object.cons], constructors
	constexpr expected() = default;

	constexpr expected(expected const& rhs) = default;

	constexpr expected(expected&& rhs) = default;

	//template <typename U, typename G,
	//	typename UF = U const&,
	//	typename GF = G const&
	//>
	//constexpr explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	//expected(expected<U, G> const& rhs);

	//template <typename U, typename G,
	//	typename UF = U,
	//	typename GF = G
	//>
	//constexpr explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	//expected(expected<U, G>&& rhs);

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
	constexpr //explicit(!hamon::is_convertible_v<U, T>)
	expected(U&& v)
		: expected(hamon::in_place, hamon::forward<U>(v))
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value
		>
	>
	constexpr //explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const& e)
		: expected(hamon::unexpect, e.error())
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value
		>
	>
	constexpr //explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&& e)
		: expected(hamon::unexpect, hamon::move(e.error()))
	{}

	template <typename... Args>
	constexpr explicit
	expected(hamon::in_place_t, Args&&... args)
		: base_type(hamon::in_place, hamon::forward<Args>(args)...)
	{}

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::in_place_t, std::initializer_list<U>, Args&&...);

	template <typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, Args&&... args)
		: base_type(hamon::unexpect, hamon::forward<Args>(args)...)
	{}

	template <typename U, typename... Args>
	constexpr explicit
	expected(hamon::unexpect_t, std::initializer_list<U>, Args&&...);

	// [expected.object.dtor], destructor
	~expected() = default;

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

	//friend constexpr void
	//swap(expected& x, expected& y)
	//	noexcept(noexcept(x.swap(y)));

	// [expected.object.obs], observers
	constexpr T const*
	operator->() const noexcept
	{
		// [expected.object.obs]/1
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/2
		return hamon::addressof(this->val);
	}

	HAMON_CXX14_CONSTEXPR T*
	operator->() noexcept
	{
		// [expected.object.obs]/1
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/2
		return hamon::addressof(this->val);
	}

	constexpr T const&
	operator*() const& noexcept
	{
		// [expected.object.obs]/3
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/4
		return this->val;
	}

	HAMON_CXX14_CONSTEXPR T&
	operator*() & noexcept
	{
		// [expected.object.obs]/3
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/4
		return this->val;
	}

	constexpr T const&&
	operator*() const&& noexcept
	{
		// [expected.object.obs]/5
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/6
		return hamon::move(this->val);
	}

	HAMON_CXX14_CONSTEXPR T&&
	operator*() && noexcept
	{
		// [expected.object.obs]/5
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/6
		return hamon::move(this->val);
	}

	constexpr explicit
	operator bool() const noexcept
	{
		// [expected.object.obs]/7
		return this->has_val;
	}

	constexpr bool
	has_value() const noexcept
	{
		// [expected.object.obs]/7
		return this->has_val;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	constexpr T const&
	value() const&
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		return this->has_value() ? this->val :
			(hamon::detail::throw_bad_expected_access<E>(hamon::as_const(this->error())), this->val);
	}

	HAMON_CXX14_CONSTEXPR T&
	value() &
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		return this->has_value() ? this->val :
			(hamon::detail::throw_bad_expected_access<E>(hamon::as_const(this->error())), this->val);
	}

	constexpr T const&&
	value() const&&
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_constructible<E, decltype(hamon::move(this->error()))>::value, "");
		return this->has_value() ? hamon::move(this->val) :
			(hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error())), hamon::move(this->val));
	}

	HAMON_CXX14_CONSTEXPR T&&
	value() &&
	{
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_constructible<E, decltype(hamon::move(this->error()))>::value, "");
		return this->has_value() ? hamon::move(this->val) :
			(hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error())), hamon::move(this->val));
	}

HAMON_WARNING_POP()

	constexpr E const&
	error() const& noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E&
	error() & noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return this->unex;
	}

	constexpr E const&&
	error() const&& noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return hamon::move(this->unex);
	}

	HAMON_CXX14_CONSTEXPR E&&
	error() && noexcept
	{
		HAMON_ASSERT(!this->has_value());
		return hamon::move(this->unex);
	}

	template <typename U = hamon::remove_cv_t<T>>
	constexpr T
	value_or(U&&) const&;

	template <typename U = hamon::remove_cv_t<T>>
	HAMON_CXX14_CONSTEXPR T
	value_or(U&&) &&;

	template <typename G = E>
	constexpr E
	error_or(G&&) const&;

	template <typename G = E>
	HAMON_CXX14_CONSTEXPR E
	error_or(G&&) &&;

#if 0	// TODO
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
#endif

	// [expected.object.eq], equality operators
	template <typename T2, typename E2>
		//requires (!hamon::is_void_v<T2>)	// TODO
	friend constexpr bool
	operator==(expected const& x, expected<T2, E2> const& y);

	template <typename T2>
	friend constexpr bool
	operator==(expected const&, T2 const&);

	template <typename E2>
	friend constexpr bool
	operator==(expected const&, unexpected<E2> const&);
};

#if 0	// TODO

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

	//friend constexpr void
	//swap(expected& x, expected& y)
	//	noexcept(noexcept(x.swap(y)));

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

#endif

}	// namespace hamon

#endif

#endif // HAMON_EXPECTED_EXPECTED_HPP
