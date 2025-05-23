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

template <typename T, typename W>
using converts_from_any_cvref = hamon::disjunction<
	hamon::is_constructible<T, W&>,       hamon::is_convertible<W&,       T>,
	hamon::is_constructible<T, W>,        hamon::is_convertible<W,        T>,
	hamon::is_constructible<T, W const&>, hamon::is_convertible<W const&, T>,
	hamon::is_constructible<T, W const>,  hamon::is_convertible<W const,  T>
>;

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

	constexpr explicit
	expected_union() {}

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

	// [expected.object.dtor]/1
	HAMON_CXX20_CONSTEXPR
	~expected_union()
	{
		this->destroy();
	}

	HAMON_CXX14_CONSTEXPR
	void destroy()
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

	constexpr explicit
	expected_union() {}

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

	// [expected.object.dtor]/2
	// ~expected_union();

	HAMON_CXX14_CONSTEXPR
	void destroy()
	{
	}
};

struct expected_access
{
	// (1) expected_union を構築して返す
	// "値のコピー省略を保証[P0135R1]"が実装されていない場合はコピー/ムーブが発生する
	template <typename T, typename E, typename Expected>
	static HAMON_CXX14_CONSTEXPR expected_union<T, E>
	make_union(Expected&& rhs)
	{
		if (rhs.has_val)
		{
			return expected_union<T, E>{hamon::in_place, hamon::forward<Expected>(rhs).val};
		}
		else
		{
			return expected_union<T, E>{hamon::unexpect, hamon::forward<Expected>(rhs).unex};
		}
	}

	// (2) 受け取った expected_union& に構築する
	// construct_atを使っているため、C++20以降でないとconstexprにできない
	template <typename T, typename E, typename Expected>
	static HAMON_CXX14_CONSTEXPR void
	make_union(expected_union<T, E>& dst, Expected&& rhs)
	{
		if (rhs.has_val)
		{
			hamon::construct_at(hamon::addressof(dst), hamon::in_place, hamon::forward<Expected>(rhs).val);
		}
		else
		{
			hamon::construct_at(hamon::addressof(dst), hamon::unexpect, hamon::forward<Expected>(rhs).unex);
		}
	}

	// expected<T, E>のコピー/ムーブコンストラクタにおいて、
	//  * "値のコピー省略を保証[P0135R1]"が実装されている、もしくは
	//  * TとEが両方ともTriviallyMoveConstructibleであるとき、
	// (1)を使う。
	// そうでないときは(2)を使う。
	// 
	// これにより、
	//  * C++14ではTriviallyMoveConstructibleならconstexpr
	//  * C++17以降では常にconstexpr
	// にできる。
};

template <typename T, typename E, bool =
#if defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	true
#else
	hamon::is_trivially_move_constructible<T>::value &&
	hamon::is_trivially_move_constructible<E>::value
#endif
>
struct expected_impl : expected_union<T, E>
{
	using base_type = expected_union<T, E>;
	using base_type::base_type;

	template <typename Expected>
	HAMON_CXX14_CONSTEXPR explicit
	expected_impl(expected_ctor_tag, Expected&& rhs)
		: base_type(expected_access::make_union<T, E>(hamon::forward<Expected>(rhs)))
	{}
};

template <typename T, typename E>
struct expected_impl<T, E, false> : expected_union<T, E>
{
	using base_type = expected_union<T, E>;
	using base_type::base_type;

	template <typename Expected>
	HAMON_CXX14_CONSTEXPR explicit
	expected_impl(expected_ctor_tag, Expected&& rhs)
		: base_type()
	{
		expected_access::make_union(*this, hamon::forward<Expected>(rhs));
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

	friend struct hamon::detail::expected_access;

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

	template <typename U, typename G,
		typename UF = U const&,		// [expected.object.cons]/17.1
		typename GF = G const&,		// [expected.object.cons]/17.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, UF>,	// [expected.object.cons]/18.1
			hamon::is_constructible<E, GF>,	// [expected.object.cons]/18.2
			hamon::disjunction<				// [expected.object.cons]/18.3
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>
			>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>
	>
	constexpr //explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G> const& rhs)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}

	template <typename U, typename G,
		typename UF = U,		// [expected.object.cons]/17.1
		typename GF = G,		// [expected.object.cons]/17.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, UF>,	// [expected.object.cons]/18.1
			hamon::is_constructible<E, GF>,	// [expected.object.cons]/18.2
			hamon::disjunction<				// [expected.object.cons]/18.3
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>
			>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>
	>
	constexpr //explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G>&& rhs)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename U = hamon::remove_cv_t<T>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<U>, hamon::in_place_t>>,	// [expected.object.cons]/23.1
			hamon::negation<hamon::is_same<hamon::expected<T, E>, hamon::remove_cvref_t<U>>>,	// [expected.object.cons]/23.2
			hamon::negation<hamon::detail::is_specialization_of_unexpected<hamon::remove_cvref_t<U>>>,	// [expected.object.cons]/23.3
			hamon::is_constructible<T, U>,		// [expected.object.cons]/23.4
			hamon::negation<hamon::conjunction<
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::detail::is_specialization_of_expected<hamon::remove_cvref_t<U>>
			>>
		>::value>
	>
	constexpr //explicit(!hamon::is_convertible_v<U, T>)
	expected(U&& v)
		: expected(hamon::in_place, hamon::forward<U>(v))	// [expected.object.cons]/24
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value		// [expected.object.cons]/28
		>
	>
	constexpr //explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const& e)
		: expected(hamon::unexpect, e.error())				// [expected.object.cons]/29
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value			// [expected.object.cons]/28
		>
	>
	constexpr //explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&& e)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.object.cons]/29
	{}

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, Args...>::value		// [expected.object.cons]/32
		>
	>
	constexpr explicit
	expected(hamon::in_place_t, Args&&... args)
		: base_type(hamon::in_place, hamon::forward<Args>(args)...)	// [expected.object.cons]/33
	{}

	template <typename U, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, std::initializer_list<U>&, Args...>::value		// [expected.object.cons]/36
		>
	>
	constexpr explicit
	expected(hamon::in_place_t, std::initializer_list<U> il, Args&&... args)
		: base_type(hamon::in_place, il, hamon::forward<Args>(args)...)		// [expected.object.cons]/37
	{}

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, Args...>::value		// [expected.object.cons]/40
		>
	>
	constexpr explicit
	expected(hamon::unexpect_t, Args&&... args)
		: base_type(hamon::unexpect, hamon::forward<Args>(args)...)	// [expected.object.cons]/41
	{}

	template <typename U, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, std::initializer_list<U>&, Args...>::value		// [expected.object.cons]/44
		>
	>
	constexpr explicit
	expected(hamon::unexpect_t, std::initializer_list<U> il, Args&&... args)
		: base_type(hamon::unexpect, il, hamon::forward<Args>(args)...)		// [expected.object.cons]/45
	{}

	// [expected.object.dtor], destructor
	~expected() = default;

	// [expected.object.assign], assignment
	HAMON_CXX14_CONSTEXPR expected&
	operator=(expected const&);

	HAMON_CXX14_CONSTEXPR expected&
	operator=(expected&&) noexcept;//(see below);

	template <typename U = hamon::remove_cv_t<T>>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(U&&);

	template <typename G>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(unexpected<G> const&);

	template <typename G>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(unexpected<G>&&);

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_nothrow_constructible<T, Args...>::value	// [expected.object.assign]/16
		>
	>
	HAMON_CXX14_CONSTEXPR T&
	emplace(Args&&... args) noexcept
	{
		// [expected.object.assign]/17
		this->destroy();
		this->has_val = true;
		return *hamon::construct_at(hamon::addressof(this->val), hamon::forward<Args>(args)...);
	}

	template <typename U, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value	// [expected.object.assign]/18
		>
	>
	HAMON_CXX14_CONSTEXPR T&
	emplace(std::initializer_list<U> il, Args&&... args) noexcept
	{
		// [expected.object.assign]/19
		this->destroy();
		this->has_val = true;
		return *hamon::construct_at(hamon::addressof(this->val), il, hamon::forward<Args>(args)...);
	}

	// [expected.object.swap], swap
	HAMON_CXX14_CONSTEXPR void
	swap(expected&)
		noexcept;//(see below);

	//friend constexpr void
	//swap(expected& x, expected& y)
	//	noexcept(noexcept(x.swap(y)));

	// [expected.object.obs], observers
	HAMON_CXX14_CONSTEXPR T const*
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

	HAMON_CXX14_CONSTEXPR T const&
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

	HAMON_CXX14_CONSTEXPR T const&&
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

	HAMON_CXX14_CONSTEXPR T const&
	value() const&
	{
		// [expected.object.obs]/8
		static_assert(hamon::is_copy_constructible<E>::value, "");

		if (!this->has_value())
		{
			// [expected.object.obs]/10
			hamon::detail::throw_bad_expected_access<E>(hamon::as_const(this->error()));
		}

		// [expected.object.obs]/9
		return this->val;
	}

	HAMON_CXX14_CONSTEXPR T&
	value() &
	{
		// [expected.object.obs]/8
		static_assert(hamon::is_copy_constructible<E>::value, "");

		if (!this->has_value())
		{
			// [expected.object.obs]/10
			hamon::detail::throw_bad_expected_access<E>(hamon::as_const(this->error()));
		}

		// [expected.object.obs]/9
		return this->val;
	}

	HAMON_CXX14_CONSTEXPR T const&&
	value() const&&
	{
		// [expected.object.obs]/11
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_constructible<E, decltype(hamon::move(this->error()))>::value, "");

		if (!this->has_value())
		{
			// [expected.object.obs]/13
			hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error()));
		}

		// [expected.object.obs]/12
		return hamon::move(this->val);
	}

	HAMON_CXX14_CONSTEXPR T&&
	value() &&
	{
		// [expected.object.obs]/11
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_constructible<E, decltype(hamon::move(this->error()))>::value, "");

		if (!this->has_value())
		{
			// [expected.object.obs]/13
			hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error()));
		}

		// [expected.object.obs]/12
		return hamon::move(this->val);
	}

HAMON_WARNING_POP()

	HAMON_CXX14_CONSTEXPR E const&
	error() const& noexcept
	{
		// [expected.object.obs]/14
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/15
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E&
	error() & noexcept
	{
		// [expected.object.obs]/14
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/15
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E const&&
	error() const&& noexcept
	{
		// [expected.object.obs]/16
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/17
		return hamon::move(this->unex);
	}

	HAMON_CXX14_CONSTEXPR E&&
	error() && noexcept
	{
		// [expected.object.obs]/16
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/17
		return hamon::move(this->unex);
	}

	template <typename U = hamon::remove_cv_t<T>>
	constexpr T
	value_or(U&& v) const&
	{
		static_assert(hamon::is_copy_constructible<T>::value && hamon::is_convertible<U, T>::value, "[expected.object.obs]/18");
		return this->has_value() ? **this : static_cast<T>(hamon::forward<U>(v));	// [expected.object.obs]/19
	}

	template <typename U = hamon::remove_cv_t<T>>
	HAMON_CXX14_CONSTEXPR T
	value_or(U&& v) &&
	{
		static_assert(hamon::is_move_constructible<T>::value && hamon::is_convertible<U, T>::value, "[expected.object.obs]/20");
		return this->has_value() ? hamon::move(**this) : static_cast<T>(hamon::forward<U>(v));	// [expected.object.obs]/21
	}

	template <typename G = E>
	constexpr E
	error_or(G&& e) const&
	{
		static_assert(hamon::is_copy_constructible<E>::value && hamon::is_convertible<G, E>::value, "[expected.object.obs]/22");
		return this->has_value() ? hamon::forward<G>(e) : this->error();	// [expected.object.obs]/23
	}

	template <typename G = E>
	HAMON_CXX14_CONSTEXPR E
	error_or(G&& e) &&
	{
		static_assert(hamon::is_move_constructible<E>::value && hamon::is_convertible<G, E>::value, "[expected.object.obs]/24");
		return this->has_value() ? hamon::forward<G>(e) : hamon::move(this->error());	// [expected.object.obs]/25
	}

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
