/**
 *	@file	expected.hpp
 *
 *	@brief	expected の定義
 */

#ifndef HAMON_EXPECTED_EXPECTED_HPP
#define HAMON_EXPECTED_EXPECTED_HPP

#include <hamon/expected/expected_fwd.hpp>
#include <hamon/expected/config.hpp>

#if !defined(HAMON_USE_STD_EXPECTED)

#include <hamon/expected/detail/expected_base.hpp>
#include <hamon/expected/detail/expected_void_base.hpp>
#include <hamon/expected/detail/is_specialization_of_expected.hpp>
#include <hamon/expected/detail/is_specialization_of_unexpected.hpp>
#include <hamon/expected/detail/tags.hpp>
#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/detail/converts_from_any_cvref.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

// 22.8.6 Class template expected[expected.expected]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename T, typename E>
#else
template <typename T, typename E, bool>
#endif
class expected : private hamon::detail::expected_base<T, E>
{
private:
	using base_type = hamon::detail::expected_base<T, E>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename, typename>
#else
	template <typename, typename, bool>
#endif
	friend class expected;

public:
	using value_type = T;
	using error_type = E;
	using unexpected_type = unexpected<E>;

	template <typename U>
	using rebind = expected<U, error_type>;

	// [expected.object.cons], constructors
	expected() = default;

	expected(expected const& rhs) = default;

	expected(expected&& rhs) = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <typename U, typename G,
		typename UF = U const&,		// [expected.object.cons]/17.1
		typename GF = G const&,		// [expected.object.cons]/17.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, UF>,	// [expected.object.cons]/18.1
			hamon::is_constructible<E, GF>,	// [expected.object.cons]/18.2
			hamon::disjunction<				// [expected.object.cons]/18.3
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>>
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G> const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, UF>::value &&
		hamon::is_nothrow_constructible<E, GF>::value)
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
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>>
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<UF, T> || !hamon::is_convertible_v<GF, E>)
	expected(expected<U, G>&& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, UF>::value &&
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename U = hamon::remove_cv_t<T>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<U>, hamon::in_place_t>>,				// [expected.object.cons]/23.1
			hamon::negation<hamon::is_same<hamon::expected<T, E>, hamon::remove_cvref_t<U>>>,			// [expected.object.cons]/23.2
			hamon::negation<hamon::detail::is_specialization_of_unexpected<hamon::remove_cvref_t<U>>>,	// [expected.object.cons]/23.3
			hamon::is_constructible<T, U>,																// [expected.object.cons]/23.4
			hamon::negation<hamon::conjunction<
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::detail::is_specialization_of_expected<hamon::remove_cvref_t<U>>>>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<U, T>)
	expected(U&& v) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, U>::value)
		: expected(hamon::in_place, hamon::forward<U>(v))	// [expected.object.cons]/24
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value>>	// [expected.object.cons]/28
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G const&>::value)
		: expected(hamon::unexpect, e.error())				// [expected.object.cons]/29
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value>>			// [expected.object.cons]/28
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G>::value)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.object.cons]/29
	{}

#else
	template <typename U, typename G,
		typename UF = U const&,		// [expected.object.cons]/17.1
		typename GF = G const&,		// [expected.object.cons]/17.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, UF>,	// [expected.object.cons]/18.1
			hamon::is_constructible<E, GF>,	// [expected.object.cons]/18.2
			hamon::disjunction<				// [expected.object.cons]/18.3
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>,
		hamon::enable_if_t<!hamon::conjunction<
			hamon::is_convertible<UF, T>,
			hamon::is_convertible<GF, E>
		>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(expected<U, G> const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, UF>::value &&
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}

	template <typename U, typename G,
		typename UF = U const&,		// [expected.object.cons]/17.1
		typename GF = G const&,		// [expected.object.cons]/17.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, UF>,	// [expected.object.cons]/18.1
			hamon::is_constructible<E, GF>,	// [expected.object.cons]/18.2
			hamon::disjunction<				// [expected.object.cons]/18.3
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::is_convertible<UF, T>,
			hamon::is_convertible<GF, E>
		>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(expected<U, G> const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, UF>::value &&
		hamon::is_nothrow_constructible<E, GF>::value)
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
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>,
		hamon::enable_if_t<!hamon::conjunction<
			hamon::is_convertible<UF, T>,
			hamon::is_convertible<GF, E>
		>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(expected<U, G>&& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, UF>::value &&
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename U, typename G,
		typename UF = U,		// [expected.object.cons]/17.1
		typename GF = G,		// [expected.object.cons]/17.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, UF>,	// [expected.object.cons]/18.1
			hamon::is_constructible<E, GF>,	// [expected.object.cons]/18.2
			hamon::disjunction<				// [expected.object.cons]/18.3
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::negation<hamon::detail::converts_from_any_cvref<T, expected<U, G>>>>,
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.object.cons]/18.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.object.cons]/18.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.object.cons]/18.6
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.object.cons]/18.7
		>::value>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::is_convertible<UF, T>,
			hamon::is_convertible<GF, E>
		>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(expected<U, G>&& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, UF>::value &&
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename U = hamon::remove_cv_t<T>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<U>, hamon::in_place_t>>,				// [expected.object.cons]/23.1
			hamon::negation<hamon::is_same<hamon::expected<T, E>, hamon::remove_cvref_t<U>>>,			// [expected.object.cons]/23.2
			hamon::negation<hamon::detail::is_specialization_of_unexpected<hamon::remove_cvref_t<U>>>,	// [expected.object.cons]/23.3
			hamon::is_constructible<T, U>,																// [expected.object.cons]/23.4
			hamon::negation<hamon::conjunction<
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::detail::is_specialization_of_expected<hamon::remove_cvref_t<U>>>>
		>::value>,
		hamon::enable_if_t<!hamon::is_convertible<U, T>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(U&& v) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, U>::value)
		: expected(hamon::in_place, hamon::forward<U>(v))	// [expected.object.cons]/24
	{}

	template <typename U = hamon::remove_cv_t<T>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<U>, hamon::in_place_t>>,				// [expected.object.cons]/23.1
			hamon::negation<hamon::is_same<hamon::expected<T, E>, hamon::remove_cvref_t<U>>>,			// [expected.object.cons]/23.2
			hamon::negation<hamon::detail::is_specialization_of_unexpected<hamon::remove_cvref_t<U>>>,	// [expected.object.cons]/23.3
			hamon::is_constructible<T, U>,																// [expected.object.cons]/23.4
			hamon::negation<hamon::conjunction<
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				hamon::detail::is_specialization_of_expected<hamon::remove_cvref_t<U>>>>
		>::value>,
		hamon::enable_if_t<hamon::is_convertible<U, T>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(U&& v) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, U>::value)
		: expected(hamon::in_place, hamon::forward<U>(v))	// [expected.object.cons]/24
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value>,	// [expected.object.cons]/28
		hamon::enable_if_t<!hamon::is_convertible<G const&, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G const&>::value)
		: expected(hamon::unexpect, e.error())				// [expected.object.cons]/29
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value>,	// [expected.object.cons]/28
		hamon::enable_if_t<hamon::is_convertible<G const&, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G const&>::value)
		: expected(hamon::unexpect, e.error())				// [expected.object.cons]/29
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value>,			// [expected.object.cons]/28
		hamon::enable_if_t<!hamon::is_convertible<G, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G>::value)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.object.cons]/29
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value>,			// [expected.object.cons]/28
		hamon::enable_if_t<hamon::is_convertible<G, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G>::value)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.object.cons]/29
	{}

#endif
	template <typename... Args, typename = hamon::enable_if_t<
		hamon::is_constructible<T, Args...>::value>>							// [expected.object.cons]/32
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::in_place_t, Args&&... args) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, Args...>::value)
		: base_type(hamon::in_place, hamon::forward<Args>(args)...)				// [expected.object.cons]/33
	{}

	template <typename U, typename... Args, typename = hamon::enable_if_t<
		hamon::is_constructible<T, std::initializer_list<U>&, Args...>::value>>	// [expected.object.cons]/36
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::in_place_t, std::initializer_list<U> il, Args&&... args) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value)
		: base_type(hamon::in_place, il, hamon::forward<Args>(args)...)			// [expected.object.cons]/37
	{}

	template <typename... Args, typename = hamon::enable_if_t<
		hamon::is_constructible<E, Args...>::value>>							// [expected.object.cons]/40
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::unexpect_t, Args&&... args) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, Args...>::value)
		: base_type(hamon::unexpect, hamon::forward<Args>(args)...)				// [expected.object.cons]/41
	{}

	template <typename U, typename... Args, typename = hamon::enable_if_t<
		hamon::is_constructible<E, std::initializer_list<U>&, Args...>::value>>	// [expected.object.cons]/44
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::unexpect_t, std::initializer_list<U> il, Args&&... args) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, std::initializer_list<U>&, Args...>::value)
		: base_type(hamon::unexpect, il, hamon::forward<Args>(args)...)			// [expected.object.cons]/45
	{}

private:
	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::detail::expected_in_place_invoke_tag tag, F&& f, Args&&... args)
		: base_type(tag, hamon::forward<F>(f), hamon::forward<Args>(args)...)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::detail::expected_unexpect_invoke_tag tag, F&& f, Args&&... args)
		: base_type(tag, hamon::forward<F>(f), hamon::forward<Args>(args)...)
	{}

public:
	// [expected.object.dtor], destructor
	~expected() = default;

	// [expected.object.assign], assignment
	expected& operator=(expected const&) = default;

	expected& operator=(expected&&) = default;

	template <typename U = hamon::remove_cv_t<T>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_same<hamon::expected<T, E>, hamon::remove_cvref_t<U>>>,			// [expected.object.assign]/9.1
			hamon::negation<hamon::detail::is_specialization_of_unexpected<hamon::remove_cvref_t<U>>>,	// [expected.object.assign]/9.2
			hamon::is_constructible<T, U>,																// [expected.object.assign]/9.3
			hamon::is_assignable<T&, U>,																// [expected.object.assign]/9.4
			hamon::disjunction<																			// [expected.object.assign]/9.5
				hamon::is_nothrow_constructible<T, U>,
				hamon::is_nothrow_move_constructible<T>,
				hamon::is_nothrow_move_constructible<E>>
		>::value>>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(U&& v) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<T, U>::value &&
		hamon::is_nothrow_assignable<T&, U>::value)
	{
		if (this->has_value())
		{
			// [expected.object.assign]/10.1
			this->val = hamon::forward<U>(v);
		}
		else
		{
			// [expected.object.assign]/10.2
			//hamon::detail::reinit_expected(this->val, this->unex, hamon::forward<U>(v));
			this->reinit(hamon::in_place, hamon::unexpect, hamon::forward<U>(v));
			this->has_val = true;
		}

		// [expected.object.assign]/11
		return *this;
	}

	template <typename G, typename GF = G const&,	// [expected.object.assign]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<E, GF>,			// [expected.object.assign]/13.1
			hamon::is_assignable<E&, GF>,			// [expected.object.assign]/13.2
			hamon::disjunction<						// [expected.object.assign]/13.3
				hamon::is_nothrow_constructible<E, GF>,
				hamon::is_nothrow_move_constructible<T>,
				hamon::is_nothrow_move_constructible<E>>
		>::value>>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value &&
		hamon::is_nothrow_assignable<E&, GF>::value)
	{
		if (this->has_value())
		{
			// [expected.object.assign]/14.1
			//hamon::detail::reinit_expected(this->unex, this->val, hamon::forward<GF>(e.error()));
			this->reinit(hamon::unexpect, hamon::in_place, hamon::forward<GF>(e.error()));
			this->has_val = false;
		}
		else
		{
			// [expected.object.assign]/14.2
			this->unex = hamon::forward<GF>(e.error());
		}

		// [expected.object.assign]/15
		return *this;
	}

	template <typename G, typename GF = G,		// [expected.object.assign]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<E, GF>,		// [expected.object.assign]/13.1
			hamon::is_assignable<E&, GF>,		// [expected.object.assign]/13.2
			hamon::disjunction<					// [expected.object.assign]/13.3
				hamon::is_nothrow_constructible<E, GF>,
				hamon::is_nothrow_move_constructible<T>,
				hamon::is_nothrow_move_constructible<E>>
		>::value>>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value &&
		hamon::is_nothrow_assignable<E&, GF>::value)
	{
		if (this->has_value())
		{
			// [expected.object.assign]/14.1
			//hamon::detail::reinit_expected(this->unex, this->val, hamon::forward<GF>(e.error()));
			this->reinit(hamon::unexpect, hamon::in_place, hamon::forward<GF>(e.error()));
			this->has_val = false;
		}
		else
		{
			// [expected.object.assign]/14.2
			this->unex = hamon::forward<GF>(e.error());
		}

		// [expected.object.assign]/15
		return *this;
	}

	template <typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_nothrow_constructible<T, Args...>::value>>	// [expected.object.assign]/16
	HAMON_CXX14_CONSTEXPR T&
	emplace(Args&&... args) HAMON_NOEXCEPT
	{
		// [expected.object.assign]/17
		if (this->has_value())
		{
			hamon::destroy_at(hamon::addressof(this->val));
		}
		else
		{
			hamon::destroy_at(hamon::addressof(this->unex));
			this->has_val = true;
		}

		//return *hamon::construct_at(hamon::addressof(this->val), hamon::forward<Args>(args)...);
		return *this->construct_at(hamon::in_place, hamon::forward<Args>(args)...);
	}

	template <typename U, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value>>	// [expected.object.assign]/18
	HAMON_CXX14_CONSTEXPR T&
	emplace(std::initializer_list<U> il, Args&&... args) HAMON_NOEXCEPT
	{
		// [expected.object.assign]/19
		if (this->has_value())
		{
			hamon::destroy_at(hamon::addressof(this->val));
		}
		else
		{
			hamon::destroy_at(hamon::addressof(this->unex));
			this->has_val = true;
		}

		//return *hamon::construct_at(hamon::addressof(this->val), il, hamon::forward<Args>(args)...);
		return *this->construct_at(hamon::in_place, il, hamon::forward<Args>(args)...);
	}

	// [expected.object.swap], swap
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename U = T, typename G = E,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_swappable<U>,				// [expected.object.swap]/1.1
			hamon::is_swappable<G>,				// [expected.object.swap]/1.2
			hamon::is_move_constructible<U>,	// [expected.object.swap]/1.3
			hamon::is_move_constructible<G>,
			hamon::disjunction<
				hamon::is_nothrow_move_constructible<U>,	// [expected.object.swap]/1.4
				hamon::is_nothrow_move_constructible<G>>
		>::value>>
#endif
	HAMON_CXX14_CONSTEXPR void
	swap(expected& rhs) HAMON_NOEXCEPT_IF(	// [expected.object.swap]/4
		hamon::is_nothrow_move_constructible<T>::value && hamon::is_nothrow_swappable<T>::value &&
		hamon::is_nothrow_move_constructible<E>::value && hamon::is_nothrow_swappable<E>::value)
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires(
			hamon::is_swappable_v<T> &&				// [expected.object.swap]/1.1
			hamon::is_swappable_v<E> &&				// [expected.object.swap]/1.2
			hamon::is_move_constructible_v<T> &&	// [expected.object.swap]/1.3
			hamon::is_move_constructible_v<E> &&
			(hamon::is_nothrow_move_constructible_v<T> ||	// [expected.object.swap]/1.4
			 hamon::is_nothrow_move_constructible_v<E>))
#endif
	{
		// [expected.object.swap]/2
		if (this->has_value())
		{
			if (rhs.has_value())
			{
				using hamon::swap;
				swap(this->val, rhs.val);
			}
			else
			{
				this->swap_val_unex(rhs);
			}
		}
		else
		{
			if (rhs.has_value())
			{
				rhs.swap(*this);
			}
			else
			{
				using hamon::swap;
				swap(this->unex, rhs.unex);
			}
		}
	}

	template <
		typename Expected = hamon::expected<T, E>,
		typename = decltype(hamon::declval<Expected&>().swap(hamon::declval<Expected&>()))>
	friend HAMON_CXX14_CONSTEXPR void
	swap(expected& x, expected& y)
		HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
//		requires requires {x.swap(y);}
	{
		// [expected.object.swap]/5
		x.swap(y);
	}

	// [expected.object.obs], observers
	HAMON_CXX14_CONSTEXPR T const*
	operator->() const HAMON_NOEXCEPT
	{
		// [expected.object.obs]/1
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/2
		return hamon::addressof(this->val);
	}

	HAMON_CXX14_CONSTEXPR T*
	operator->() HAMON_NOEXCEPT
	{
		// [expected.object.obs]/1
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/2
		return hamon::addressof(this->val);
	}

	HAMON_CXX14_CONSTEXPR T const&
	operator*() const& HAMON_NOEXCEPT
	{
		// [expected.object.obs]/3
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/4
		return this->val;
	}

	HAMON_CXX14_CONSTEXPR T&
	operator*() & HAMON_NOEXCEPT
	{
		// [expected.object.obs]/3
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/4
		return this->val;
	}

	HAMON_CXX14_CONSTEXPR T const&&
	operator*() const&& HAMON_NOEXCEPT
	{
		// [expected.object.obs]/5
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/6
		return hamon::move(this->val);
	}

	HAMON_CXX14_CONSTEXPR T&&
	operator*() && HAMON_NOEXCEPT
	{
		// [expected.object.obs]/5
		HAMON_ASSERT(this->has_value());

		// [expected.object.obs]/6
		return hamon::move(this->val);
	}

	HAMON_CXX11_CONSTEXPR explicit
	operator bool() const HAMON_NOEXCEPT
	{
		// [expected.object.obs]/7
		return this->has_val;
	}

	HAMON_CXX11_CONSTEXPR bool
	has_value() const HAMON_NOEXCEPT
	{
		// [expected.object.obs]/7
		return this->has_val;
	}

	HAMON_CXX14_CONSTEXPR T const&
	value() const&
	{
		// [expected.object.obs]/8
		static_assert(hamon::is_copy_constructible<E>::value, "");

		// [expected.object.obs]/10
		if (!this->has_value())
		{
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

		// [expected.object.obs]/10
		if (!this->has_value())
		{
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

		// [expected.object.obs]/13
		if (!this->has_value())
		{
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

	HAMON_CXX14_CONSTEXPR E const&
	error() const& HAMON_NOEXCEPT
	{
		// [expected.object.obs]/14
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/15
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E&
	error() & HAMON_NOEXCEPT
	{
		// [expected.object.obs]/14
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/15
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E const&&
	error() const&& HAMON_NOEXCEPT
	{
		// [expected.object.obs]/16
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/17
		return hamon::move(this->unex);
	}

	HAMON_CXX14_CONSTEXPR E&&
	error() && HAMON_NOEXCEPT
	{
		// [expected.object.obs]/16
		HAMON_ASSERT(!this->has_value());

		// [expected.object.obs]/17
		return hamon::move(this->unex);
	}

	template <typename U = hamon::remove_cv_t<T>>
	HAMON_CXX11_CONSTEXPR T
	value_or(U&& v) const& HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<T>::value &&
		hamon::is_nothrow_convertible<U, T>::value)
	{
		static_assert(hamon::is_copy_constructible<T>::value, "[expected.object.obs]/18");
		static_assert(hamon::is_convertible<U, T>::value, "[expected.object.obs]/18");

		// [expected.object.obs]/19
		return this->has_value() ? **this : static_cast<T>(hamon::forward<U>(v));
	}

	template <typename U = hamon::remove_cv_t<T>>
	HAMON_CXX14_CONSTEXPR T
	value_or(U&& v) && HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<T>::value &&
		hamon::is_nothrow_convertible<U, T>::value)
	{
		static_assert(hamon::is_move_constructible<T>::value, "[expected.object.obs]/20");
		static_assert(hamon::is_convertible<U, T>::value, "[expected.object.obs]/20");

		// [expected.object.obs]/21
		return this->has_value() ? hamon::move(**this) : static_cast<T>(hamon::forward<U>(v));
	}

	template <typename G = E>
	HAMON_CXX11_CONSTEXPR E
	error_or(G&& e) const& HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<E>::value &&
		hamon::is_nothrow_convertible<G, E>::value)
	{
		static_assert(hamon::is_copy_constructible<E>::value, "[expected.object.obs]/22");
		static_assert(hamon::is_convertible<G, E>::value, "[expected.object.obs]/22");

		// [expected.object.obs]/23
		return this->has_value() ? hamon::forward<G>(e) : this->error();
	}

	template <typename G = E>
	HAMON_CXX14_CONSTEXPR E
	error_or(G&& e) && HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<E>::value &&
		hamon::is_nothrow_convertible<G, E>::value)
	{
		static_assert(hamon::is_move_constructible<E>::value, "[expected.object.obs]/24");
		static_assert(hamon::is_convertible<G, E>::value, "[expected.object.obs]/24");

		// [expected.object.obs]/25
		return this->has_value() ? hamon::forward<G>(e) : hamon::move(this->error());
	}

	// [expected.object.monadic], monadic operations
	template <typename F, typename G = E&,
		// [expected.object.monadic]/2
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/1
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F, T&>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) & -> U
	{
		// [expected.object.monadic]/3
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.object.monadic]/4
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f), this->val);
		}
		else
		{
			return U(hamon::unexpect, this->error());
		}
	}

	template <typename F, typename G = E const&,
		// [expected.object.monadic]/2
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/1
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F, T const&>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) const& -> U
	{
		// [expected.object.monadic]/3
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.object.monadic]/4
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f), this->val);
		}
		else
		{
			return U(hamon::unexpect, this->error());
		}
	}

	template <typename F, typename G = E&&,
		// [expected.object.monadic]/6
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/5
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F, T&&>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) && -> U
	{
		// [expected.object.monadic]/7
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.object.monadic]/8
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f), hamon::move(this->val));
		}
		else
		{
			return U(hamon::unexpect, hamon::move(this->error()));
		}
	}

	template <typename F, typename G = E const&&,
		// [expected.object.monadic]/6
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/5
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F, T const&&>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) const&& -> U
	{
		// [expected.object.monadic]/7
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.object.monadic]/8
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f), hamon::move(this->val));
		}
		else
		{
			return U(hamon::unexpect, hamon::move(this->error()));
		}
	}

	template <typename F, typename U = T&,
		// [expected.object.monadic]/10
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/9
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) & -> G
	{
		// [expected.object.monadic]/11
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.object.monadic]/12
		if (this->has_value())
		{
			return G(hamon::in_place, this->val);
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), this->error());
		}
	}

	template <typename F, typename U = T const&,
		// [expected.object.monadic]/10
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/9
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E const&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) const& -> G
	{
		// [expected.object.monadic]/11
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.object.monadic]/12
		if (this->has_value())
		{
			return G(hamon::in_place, this->val);
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), this->error());
		}
	}

	template <typename F, typename U = T&&,
		// [expected.object.monadic]/14
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/13
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E&&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) && -> G
	{
		// [expected.object.monadic]/15
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.object.monadic]/16
		if (this->has_value())
		{
			return G(hamon::in_place, hamon::move(this->val));
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	template <typename F, typename U = T const&&,
		// [expected.object.monadic]/14
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/13
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E const&&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) const&& -> G
	{
		// [expected.object.monadic]/15
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.object.monadic]/16
		if (this->has_value())
		{
			return G(hamon::in_place, hamon::move(this->val));
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	template <typename F, typename G = E&,
		// [expected.object.monadic]/18
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/17
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F, T&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) & -> hamon::expected<U, E>
	{
		// [expected.object.monadic]/19
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(hamon::forward<F>(f), val));
		// is well-formed.

		// [expected.object.monadic]/20

		if (!this->has_value())
		{
			// [expected.object.monadic]/20.1
			return hamon::expected<U, E>(hamon::unexpect, this->error());
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f), this->val);
	}

	template <typename F, typename G = E const&,
		// [expected.object.monadic]/18
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/17
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F, T const&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) const& -> hamon::expected<U, E>
	{
		// [expected.object.monadic]/19
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(hamon::forward<F>(f), val));
		// is well-formed.

		// [expected.object.monadic]/20

		if (!this->has_value())
		{
			// [expected.object.monadic]/20.1
			return hamon::expected<U, E>(hamon::unexpect, this->error());
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f), this->val);
	}

	template <typename F, typename G = E&&,
		// [expected.object.monadic]/22
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/21
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F, T&&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) && -> hamon::expected<U, E>
	{
		// [expected.object.monadic]/23
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(hamon::forward<F>(f), std::move(val)));
		// is well-formed.

		// [expected.object.monadic]/24

		if (!this->has_value())
		{
			// [expected.object.monadic]/24.1
			return hamon::expected<U, E>(hamon::unexpect, hamon::move(this->error()));
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f), hamon::move(this->val));
	}

	template <typename F, typename G = E const&&,
		// [expected.object.monadic]/22
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.object.monadic]/21
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F, T const&&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) const&& -> hamon::expected<U, E>
	{
		// [expected.object.monadic]/23
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(hamon::forward<F>(f), std::move(val)));
		// is well-formed.

		// [expected.object.monadic]/24

		if (!this->has_value())
		{
			// [expected.object.monadic]/24.1
			return hamon::expected<U, E>(hamon::unexpect, hamon::move(this->error()));
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f), hamon::move(this->val));
	}

	template <typename F, typename U = T&,
		// [expected.object.monadic]/26
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/25
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) & -> hamon::expected<T, G>
	{
		// [expected.object.monadic]/27
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), error()));
		// is well-formed.

		// [expected.object.monadic]/28
		if (this->has_value())
		{
			return hamon::expected<T, G>(hamon::in_place, this->val);
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), this->error());
		}
	}

	template <typename F, typename U = T const&,
		// [expected.object.monadic]/26
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/25
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E const&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) const& -> hamon::expected<T, G>
	{
		// [expected.object.monadic]/27
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), error()));
		// is well-formed.

		// [expected.object.monadic]/28
		if (this->has_value())
		{
			return hamon::expected<T, G>(hamon::in_place, this->val);
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), this->error());
		}
	}

	template <typename F, typename U = T&&,
		// [expected.object.monadic]/30
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/29
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E&&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) && -> hamon::expected<T, G>
	{
		// [expected.object.monadic]/31
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), std::move(error())));
		// is well-formed.

		// [expected.object.monadic]/32
		if (this->has_value())
		{
			return hamon::expected<T, G>(hamon::in_place, hamon::move(this->val));
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	template <typename F, typename U = T const&&,
		// [expected.object.monadic]/30
		typename = hamon::enable_if_t<hamon::is_constructible<T, U>::value>,
		// [expected.object.monadic]/29
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E const&&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) const&& -> hamon::expected<T, G>
	{
		// [expected.object.monadic]/31
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), std::move(error())));
		// is well-formed.

		// [expected.object.monadic]/32
		if (this->has_value())
		{
			return hamon::expected<T, G>(hamon::in_place, hamon::move(this->val));
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	// [expected.object.eq], equality operators
	template <typename T2, typename E2,
		// [expected.object.eq]/1
		typename = hamon::enable_if_t<!hamon::is_void<T2>::value>,
		typename R1 = decltype(hamon::declval<T const&>() == hamon::declval<T2 const&>()),
		typename R2 = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<
			hamon::convertible_to_t<R1, bool>::value &&
			hamon::convertible_to_t<R2, bool>::value>>
	friend HAMON_CXX14_CONSTEXPR bool
	operator==(expected const& x, expected<T2, E2> const& y) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(static_cast<bool>(hamon::declval<T const&>() == hamon::declval<T2 const&>())) &&
		HAMON_NOEXCEPT_EXPR(static_cast<bool>(hamon::declval<E const&>() == hamon::declval<E2 const&>())))
	{
		// [expected.object.eq]/2
		if (x.has_value() != y.has_value())
		{
			return false;
		}

		if (x.has_value())
		{
			return *x == *y;
		}
		else
		{
			return x.error() == y.error();
		}
	}

	template <typename T2,
		// [expected.object.eq]/3
		typename = hamon::enable_if_t<!hamon::detail::is_specialization_of_expected<T2>::value>,
		typename R = decltype(hamon::declval<T const&>() == hamon::declval<T2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(expected const& x, T2 const& v) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		static_cast<bool>(hamon::declval<T const&>() == hamon::declval<T2 const&>()))
	{
		// [expected.object.eq]/4
		return x.has_value() && static_cast<bool>(*x == v);
	}

	template <typename E2,
		// [expected.object.eq]/5
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(expected const& x, unexpected<E2> const& e) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		static_cast<bool>(hamon::declval<E const&>() == hamon::declval<E2 const&>()))
	{
		// [expected.object.eq]/6
		return !x.has_value() && static_cast<bool>(x.error() == e.error());
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <typename T2, typename E2,
		typename = hamon::enable_if_t<!hamon::is_void<T2>::value>,
		typename R1 = decltype(hamon::declval<T const&>() == hamon::declval<T2 const&>()),
		typename R2 = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<
			hamon::convertible_to_t<R1, bool>::value &&
			hamon::convertible_to_t<R2, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(expected const& x, expected<T2, E2> const& y)
		HAMON_NOEXCEPT_IF_EXPR(x == y)	// noexcept as an extension
	{
		return !(x == y);
	}

	template <typename T2,
		typename = hamon::enable_if_t<!hamon::detail::is_specialization_of_expected<T2>::value>,
		typename R = decltype(hamon::declval<T const&>() == hamon::declval<T2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(expected const& x, T2 const& v)
		HAMON_NOEXCEPT_IF_EXPR(x == v)	// noexcept as an extension
	{
		return !(x == v);
	}

	template <typename T2,
		typename = hamon::enable_if_t<!hamon::detail::is_specialization_of_expected<T2>::value>,
		typename R = decltype(hamon::declval<T const&>() == hamon::declval<T2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(T2 const& v, expected const& x)
		HAMON_NOEXCEPT_IF_EXPR(x == v)	// noexcept as an extension
	{
		return x == v;
	}

	template <typename T2,
		typename = hamon::enable_if_t<!hamon::detail::is_specialization_of_expected<T2>::value>,
		typename R = decltype(hamon::declval<T const&>() == hamon::declval<T2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(T2 const& v, expected const& x)
		HAMON_NOEXCEPT_IF_EXPR(x == v)	// noexcept as an extension
	{
		return !(x == v);
	}

	template <typename E2,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(expected const& x, unexpected<E2> const& e)
		HAMON_NOEXCEPT_IF_EXPR(x == e)	// noexcept as an extension
	{
		return !(x == e);
	}

	template <typename E2,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(unexpected<E2> const& e, expected const& x)
		HAMON_NOEXCEPT_IF_EXPR(x == e)	// noexcept as an extension
	{
		return x == e;
	}

	template <typename E2,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(unexpected<E2> const& e, expected const& x)
		HAMON_NOEXCEPT_IF_EXPR(x == e)	// noexcept as an extension
	{
		return !(x == e);
	}
#endif
};

// 22.8.7 Partial specialization of expected for void types[expected.void]

template <typename T, typename E>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::is_void_v<T>
class expected<T, E>
#else
class expected<T, E, true>
#endif
	: private hamon::detail::expected_void_base<E>
{
private:
	using base_type = hamon::detail::expected_void_base<E>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename, typename>
#else
	template <typename, typename, bool>
#endif
	friend class expected;

public:
	using value_type = T;
	using error_type = E;
	using unexpected_type = unexpected<E>;

	template <typename U>
	using rebind = expected<U, error_type>;

	// [expected.void.cons], constructors
	HAMON_CXX11_CONSTEXPR expected() HAMON_NOEXCEPT
		: base_type(hamon::in_place)
	{}

	expected(expected const&) = default;

	expected(expected&&) = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <typename U, typename G,
		typename GF = G const&,		// [expected.void.cons]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_void<U>,																// [expected.void.cons]/13.1
			hamon::is_constructible<E, GF>,													// [expected.void.cons]/13.2
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.void.cons]/13.3
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.void.cons]/13.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.void.cons]/13.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.void.cons]/13.6
		>::value>>
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<G const&, E>)
	expected(expected<U, G> const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}

	template <typename U, typename G,
		typename GF = G,		// [expected.void.cons]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_void<U>,																// [expected.void.cons]/13.1
			hamon::is_constructible<E, GF>,													// [expected.void.cons]/13.2
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.void.cons]/13.3
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.void.cons]/13.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.void.cons]/13.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.void.cons]/13.6
		>::value>>
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<G, E>)
	expected(expected<U, G>&& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value>>	// [expected.void.cons]/18
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<G const&, E>)
	expected(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G const&>::value)
		: expected(hamon::unexpect, e.error())				// [expected.void.cons]/19
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value>>			// [expected.void.cons]/18
	HAMON_CXX11_CONSTEXPR
	explicit(!hamon::is_convertible_v<G, E>)
	expected(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G>::value)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.void.cons]/19
	{}

#else
	template <typename U, typename G,
		typename GF = G const&,		// [expected.void.cons]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_void<U>,																// [expected.void.cons]/13.1
			hamon::is_constructible<E, GF>,													// [expected.void.cons]/13.2
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.void.cons]/13.3
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.void.cons]/13.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.void.cons]/13.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.void.cons]/13.6
		>::value>,
		hamon::enable_if_t<!hamon::is_convertible<G const&, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(expected<U, G> const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}

	template <typename U, typename G,
		typename GF = G const&,		// [expected.void.cons]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_void<U>,																// [expected.void.cons]/13.1
			hamon::is_constructible<E, GF>,													// [expected.void.cons]/13.2
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.void.cons]/13.3
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.void.cons]/13.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.void.cons]/13.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.void.cons]/13.6
		>::value>,
		hamon::enable_if_t<hamon::is_convertible<G const&, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(expected<U, G> const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}

	template <typename U, typename G,
		typename GF = G,		// [expected.void.cons]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_void<U>,																// [expected.void.cons]/13.1
			hamon::is_constructible<E, GF>,													// [expected.void.cons]/13.2
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.void.cons]/13.3
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.void.cons]/13.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.void.cons]/13.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.void.cons]/13.6
		>::value>,
		hamon::enable_if_t<!hamon::is_convertible<G, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(expected<U, G>&& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename U, typename G,
		typename GF = G,		// [expected.void.cons]/12
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_void<U>,																// [expected.void.cons]/13.1
			hamon::is_constructible<E, GF>,													// [expected.void.cons]/13.2
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>&>>,		// [expected.void.cons]/13.3
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G>>>,		// [expected.void.cons]/13.4
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const&>>,	// [expected.void.cons]/13.5
			hamon::negation<hamon::is_constructible<unexpected<E>, expected<U, G> const>>	// [expected.void.cons]/13.6
		>::value>,
		hamon::enable_if_t<hamon::is_convertible<G, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(expected<U, G>&& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value>,	// [expected.void.cons]/18
		hamon::enable_if_t<!hamon::is_convertible<G const&, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G const&>::value)
		: expected(hamon::unexpect, e.error())				// [expected.void.cons]/19
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G const&>::value>,	// [expected.void.cons]/18
		hamon::enable_if_t<hamon::is_convertible<G const&, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G const&>::value)
		: expected(hamon::unexpect, e.error())				// [expected.void.cons]/19
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value>,			// [expected.void.cons]/18
		hamon::enable_if_t<!hamon::is_convertible<G, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit
	expected(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G>::value)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.void.cons]/19
	{}

	template <typename G,
		typename = hamon::enable_if_t<
			hamon::is_constructible<E, G>::value>,			// [expected.void.cons]/18
		hamon::enable_if_t<hamon::is_convertible<G, E>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	expected(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, G>::value)
		: expected(hamon::unexpect, hamon::move(e.error()))	// [expected.void.cons]/19
	{}

#endif
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::in_place_t) HAMON_NOEXCEPT
		: base_type(hamon::in_place)
	{}

	template <typename... Args, typename = hamon::enable_if_t<
		hamon::is_constructible<E, Args...>::value>>							// [expected.void.cons]/23
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::unexpect_t, Args&&... args) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, Args...>::value)
		: base_type(hamon::unexpect, hamon::forward<Args>(args)...)				// [expected.void.cons]/24
	{}

	template <typename U, typename... Args, typename = hamon::enable_if_t<
		hamon::is_constructible<E, std::initializer_list<U>&, Args...>::value>>	// [expected.void.cons]/27
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::unexpect_t, std::initializer_list<U> il, Args&&... args) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, std::initializer_list<U>&, Args...>::value)
		: base_type(hamon::unexpect, il, hamon::forward<Args>(args)...)			// [expected.void.cons]/28
	{}

private:
	template <typename F, typename... Args>
	HAMON_CXX14_CONSTEXPR explicit
	expected(hamon::detail::expected_in_place_invoke_tag, F&& f, Args&&... args)
		: base_type(hamon::in_place)
	{
		hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...);
	}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected(hamon::detail::expected_unexpect_invoke_tag tag, F&& f, Args&&... args)
		: base_type(tag, hamon::forward<F>(f), hamon::forward<Args>(args)...)
	{}

public:
	// [expected.void.dtor], destructor
	~expected() = default;

	// [expected.void.assign], assignment
	expected& operator=(expected const&) = default;

	expected& operator=(expected&&) = default;

	template <typename G, typename GF = G const&,			// [expected.void.assign]/8
		typename = hamon::enable_if_t<hamon::conjunction<	// [expected.void.assign]/9
			hamon::is_constructible<E, GF>,
			hamon::is_assignable<E&, GF>
		>::value>>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(unexpected<G> const& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value &&
		hamon::is_nothrow_assignable<E&, GF>::value)
	{
		if (this->has_value())
		{
			// [expected.void.assign]/10.1
			//hamon::construct_at(hamon::addressof(this->unex), hamon::forward<GF>(e.error()));
			this->construct_at(hamon::unexpect, hamon::forward<GF>(e.error()));
			this->has_val = false;
		}
		else
		{
			// [expected.void.assign]/10.2
			this->unex = hamon::forward<GF>(e.error());
		}

		// [expected.void.assign]/11
		return *this;
	}

	template <typename G, typename GF = G,					// [expected.void.assign]/8
		typename = hamon::enable_if_t<hamon::conjunction<	// [expected.void.assign]/9
			hamon::is_constructible<E, GF>,
			hamon::is_assignable<E&, GF>
		>::value>>
	HAMON_CXX14_CONSTEXPR expected&
	operator=(unexpected<G>&& e) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<E, GF>::value &&
		hamon::is_nothrow_assignable<E&, GF>::value)
	{
		if (this->has_value())
		{
			// [expected.void.assign]/10.1
			//hamon::construct_at(hamon::addressof(this->unex), hamon::forward<GF>(e.error()));
			this->construct_at(hamon::unexpect, hamon::forward<GF>(e.error()));
			this->has_val = false;
		}
		else
		{
			// [expected.void.assign]/10.2
			this->unex = hamon::forward<GF>(e.error());
		}

		// [expected.void.assign]/11
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	emplace() HAMON_NOEXCEPT
	{
		// [expected.void.assign]/12
		if (!this->has_value())
		{
			hamon::destroy_at(hamon::addressof(this->unex));
			this->has_val = true;
		}
	}

	// [expected.void.swap], swap
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename G = E,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_swappable<G>,
			hamon::is_move_constructible<G>
		>::value>>
#endif
	HAMON_CXX14_CONSTEXPR void
	swap(expected& rhs) HAMON_NOEXCEPT_IF(	// [expected.void.swap]/4
		hamon::is_nothrow_move_constructible<E>::value &&
		hamon::is_nothrow_swappable<E>::value)
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires(				// [expected.void.swap]/1
			hamon::is_swappable<E>::value &&
			hamon::is_move_constructible<E>::value)
#endif
	{
		// [expected.void.swap]/2
		if (this->has_value())
		{
			if (rhs.has_value())
			{
				// no effects
			}
			else
			{
				//hamon::construct_at(hamon::addressof(this->unex), hamon::move(rhs.unex));
				this->construct_at(hamon::unexpect, hamon::move(rhs.unex));
				hamon::destroy_at(hamon::addressof(rhs.unex));
				this->has_val = false;
				rhs.has_val = true;
			}
		}
		else
		{
			if (rhs.has_value())
			{
				rhs.swap(*this);
			}
			else
			{
				using hamon::swap;
				swap(this->unex, rhs.unex);
			}
		}
	}

	template <
		typename Expected = hamon::expected<T, E>,
		typename = decltype(hamon::declval<Expected&>().swap(hamon::declval<Expected&>()))>
	friend HAMON_CXX14_CONSTEXPR void
	swap(expected& x, expected& y)
		HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
//		requires requires {x.swap(y);}
	{
		// [expected.void.swap]/5
		x.swap(y);
	}

	// [expected.void.obs], observers
	HAMON_CXX11_CONSTEXPR explicit
	operator bool() const HAMON_NOEXCEPT
	{
		// [expected.void.obs]/1
		return this->has_val;
	}

	HAMON_CXX11_CONSTEXPR bool
	has_value() const HAMON_NOEXCEPT
	{
		// [expected.void.obs]/1
		return this->has_val;
	}

	HAMON_CXX14_CONSTEXPR void
	operator*() const HAMON_NOEXCEPT
	{
		// [expected.void.obs]/2
		HAMON_ASSERT(this->has_value());
	}

	HAMON_CXX14_CONSTEXPR void
	value() const&
	{
		// [expected.void.obs]/3
		static_assert(hamon::is_copy_constructible<E>::value, "");

		// [expected.void.obs]/4
		if (!this->has_value())
		{
			hamon::detail::throw_bad_expected_access<E>(this->error());
		}
	}

	HAMON_CXX14_CONSTEXPR void
	value() &&
	{
		// [expected.void.obs]/5
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_move_constructible<E>::value, "");

		// [expected.void.obs]/6
		if (!this->has_value())
		{
			hamon::detail::throw_bad_expected_access<E>(hamon::move(this->error()));
		}
	}

	HAMON_CXX14_CONSTEXPR E const&
	error() const& HAMON_NOEXCEPT
	{
		// [expected.void.obs]/7
		HAMON_ASSERT(!this->has_value());

		// [expected.void.obs]/8
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E&
	error() & HAMON_NOEXCEPT
	{
		// [expected.void.obs]/7
		HAMON_ASSERT(!this->has_value());

		// [expected.void.obs]/8
		return this->unex;
	}

	HAMON_CXX14_CONSTEXPR E const&&
	error() const&& HAMON_NOEXCEPT
	{
		// [expected.void.obs]/9
		HAMON_ASSERT(!this->has_value());

		// [expected.void.obs]/10
		return hamon::move(this->unex);
	}

	HAMON_CXX14_CONSTEXPR E&&
	error() && HAMON_NOEXCEPT
	{
		// [expected.void.obs]/9
		HAMON_ASSERT(!this->has_value());

		// [expected.void.obs]/10
		return hamon::move(this->unex);
	}

	template <typename G = E>
	HAMON_CXX11_CONSTEXPR E
	error_or(G&& e) const& HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<E>::value &&
		hamon::is_nothrow_convertible<G, E>::value)
	{
		// [expected.void.obs]/11
		static_assert(hamon::is_copy_constructible<E>::value, "");
		static_assert(hamon::is_convertible<G, E>::value, "");

		// [expected.void.obs]/12
		return this->has_value() ? hamon::forward<G>(e) : this->error();
	}

	template <typename G = E>
	HAMON_CXX14_CONSTEXPR E
	error_or(G&& e) && HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<E>::value &&
		hamon::is_nothrow_convertible<G, E>::value)
	{
		// [expected.void.obs]/13
		static_assert(hamon::is_move_constructible<E>::value, "");
		static_assert(hamon::is_convertible<G, E>::value, "");

		// [expected.void.obs]/14
		return this->has_value() ? hamon::forward<G>(e) : hamon::move(this->error());
	}

	// [expected.void.monadic], monadic operations
	template <typename F, typename G = E&,
		// [expected.void.monadic]/2
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/1
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) & -> U
	{
		// [expected.void.monadic]/3
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.void.monadic]/4
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f));
		}
		else
		{
			return U(hamon::unexpect, this->error());
		}
	}

	template <typename F, typename G = E const&,
		// [expected.void.monadic]/2
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/1
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) const& -> U
	{
		// [expected.void.monadic]/3
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.void.monadic]/4
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f));
		}
		else
		{
			return U(hamon::unexpect, this->error());
		}
	}

	template <typename F, typename G = E&&,
		// [expected.void.monadic]/6
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/5
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) && -> U
	{
		// [expected.void.monadic]/7
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.void.monadic]/8
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f));
		}
		else
		{
			return U(hamon::unexpect, hamon::move(this->error()));
		}
	}

	template <typename F, typename G = E const&&,
		// [expected.void.monadic]/6
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/5
		typename U = hamon::remove_cvref_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	and_then(F&& f) const&& -> U
	{
		// [expected.void.monadic]/7
		static_assert(hamon::detail::is_specialization_of_expected<U>::value, "");
		static_assert(hamon::is_same<typename U::error_type, E>::value, "");

		// [expected.void.monadic]/8
		if (this->has_value())
		{
			return hamon::invoke(hamon::forward<F>(f));
		}
		else
		{
			return U(hamon::unexpect, hamon::move(this->error()));
		}
	}

	template <typename F,
		// [expected.void.monadic]/9
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) & -> G
	{
		// [expected.void.monadic]/10
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.void.monadic]/11
		if (this->has_value())
		{
			return G();
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), this->error());
		}
	}

	template <typename F,
		// [expected.void.monadic]/9
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E const&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) const& -> G
	{
		// [expected.void.monadic]/10
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.void.monadic]/11
		if (this->has_value())
		{
			return G();
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), this->error());
		}
	}

	template <typename F,
		// [expected.void.monadic]/12
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E&&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) && -> G
	{
		// [expected.void.monadic]/13
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.void.monadic]/14
		if (this->has_value())
		{
			return G();
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	template <typename F,
		// [expected.void.monadic]/12
		typename G = hamon::remove_cvref_t<hamon::invoke_result_t<F, E const&&>>>
	HAMON_CXX14_CONSTEXPR auto
	or_else(F&& f) const&& -> G
	{
		// [expected.void.monadic]/13
		static_assert(hamon::detail::is_specialization_of_expected<G>::value, "");
		static_assert(hamon::is_same<typename G::value_type, T>::value, "");

		// [expected.void.monadic]/14
		if (this->has_value())
		{
			return G();
		}
		else
		{
			return hamon::invoke(hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	template <typename F, typename G = E&,
		// [expected.void.monadic]/16
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/15
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) & -> hamon::expected<U, E>
	{
		// [expected.void.monadic]/17
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(std::forward<F>(f)));
		// is well-formed.

		// [expected.void.monadic]/18

		if (!this->has_value())
		{
			// [expected.void.monadic]/18.1
			return hamon::expected<U, E>(hamon::unexpect, this->error());
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f));
	}

	template <typename F, typename G = E const&,
		// [expected.void.monadic]/16
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/15
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) const& -> hamon::expected<U, E>
	{
		// [expected.void.monadic]/17
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(std::forward<F>(f)));
		// is well-formed.

		// [expected.void.monadic]/18

		if (!this->has_value())
		{
			// [expected.void.monadic]/18.1
			return hamon::expected<U, E>(hamon::unexpect, this->error());
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f));
	}

	template <typename F, typename G = E&&,
		// [expected.void.monadic]/20
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/19
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) && -> hamon::expected<U, E>
	{
		// [expected.void.monadic]/21
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(std::forward<F>(f)));
		// is well-formed.

		// [expected.void.monadic]/22

		if (!this->has_value())
		{
			// [expected.void.monadic]/22.1
			return hamon::expected<U, E>(hamon::unexpect, hamon::move(this->error()));
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f));
	}

	template <typename F, typename G = E const&&,
		// [expected.void.monadic]/20
		typename = hamon::enable_if_t<hamon::is_constructible<E, G>::value>,
		// [expected.void.monadic]/19
		typename U = hamon::remove_cv_t<hamon::invoke_result_t<F>>>
	HAMON_CXX14_CONSTEXPR auto
	transform(F&& f) const&& -> hamon::expected<U, E>
	{
		// [expected.void.monadic]/21
		// TODO
		// U is a valid value type for expected.
		// If is_void_v<U> is false, the declaration
		// U u(invoke(std::forward<F>(f)));
		// is well-formed.

		// [expected.void.monadic]/22

		if (!this->has_value())
		{
			// [expected.void.monadic]/22.1
			return hamon::expected<U, E>(hamon::unexpect, hamon::move(this->error()));
		}

		return hamon::expected<U, E>(hamon::detail::expected_in_place_invoke_tag{},
			hamon::forward<F>(f));
	}

	template <typename F,
		// [expected.void.monadic]/23
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) & -> hamon::expected<T, G>
	{
		// [expected.void.monadic]/24
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), error()));
		// is well-formed.

		// [expected.void.monadic]/25
		if (this->has_value())
		{
			return hamon::expected<T, G>();
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), this->error());
		}
	}

	template <typename F,
		// [expected.void.monadic]/23
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E const&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) const& -> hamon::expected<T, G>
	{
		// [expected.void.monadic]/24
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), error()));
		// is well-formed.

		// [expected.void.monadic]/25
		if (this->has_value())
		{
			return hamon::expected<T, G>();
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), this->error());
		}
	}

	template <typename F,
		// [expected.void.monadic]/26
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E&&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) && -> hamon::expected<T, G>
	{
		// [expected.void.monadic]/27
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), std::move(error())));
		// is well-formed.

		// [expected.void.monadic]/28
		if (this->has_value())
		{
			return hamon::expected<T, G>();
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	template <typename F,
		// [expected.void.monadic]/26
		typename G = hamon::remove_cv_t<hamon::invoke_result_t<F, E const&&>>>
	HAMON_CXX14_CONSTEXPR auto
	transform_error(F&& f) const&& -> hamon::expected<T, G>
	{
		// [expected.void.monadic]/27
		// TODO
		// G is a valid template argument for unexpected.
		// The declaration
		// G g(invoke(hamon::forward<F>(f), std::move(error())));
		// is well-formed.

		// [expected.void.monadic]/28
		if (this->has_value())
		{
			return hamon::expected<T, G>();
		}
		else
		{
			return hamon::expected<T, G>(hamon::detail::expected_unexpect_invoke_tag{},
				hamon::forward<F>(f), hamon::move(this->error()));
		}
	}

	// [expected.void.eq], equality operators
	template <typename T2, typename E2,
		// [expected.void.eq]/1
		typename = hamon::enable_if_t<hamon::is_void<T2>::value>,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX14_CONSTEXPR bool
	operator==(expected const& x, expected<T2, E2> const& y) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		static_cast<bool>(hamon::declval<E const&>() == hamon::declval<E2 const&>()))
	{
		// [expected.void.eq]/2
		if (x.has_value() != y.has_value())
		{
			return false;
		}

		return x.has_value() || static_cast<bool>(x.error() == y.error());
	}

	template <typename E2,
		// [expected.void.eq]/3
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(expected const& x, unexpected<E2> const& e) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		static_cast<bool>(hamon::declval<E const&>() == hamon::declval<E2 const&>()))
	{
		// [expected.void.eq]/4
		return !x.has_value() && static_cast<bool>(x.error() == e.error());
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <typename T2, typename E2,
		typename = hamon::enable_if_t<hamon::is_void<T2>::value>,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(expected const& x, expected<T2, E2> const& y)
		HAMON_NOEXCEPT_IF_EXPR(x == y)	// noexcept as an extension
	{
		return !(x == y);
	}

	template <typename E2,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(expected const& x, unexpected<E2> const& e)
		HAMON_NOEXCEPT_IF_EXPR(x == e)	// noexcept as an extension
	{
		return !(x == e);
	}

	template <typename E2,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(unexpected<E2> const& e, expected const& x)
		HAMON_NOEXCEPT_IF_EXPR(x == e)	// noexcept as an extension
	{
		return x == e;
	}

	template <typename E2,
		typename R = decltype(hamon::declval<E const&>() == hamon::declval<E2 const&>()),
		typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(unexpected<E2> const& e, expected const& x)
		HAMON_NOEXCEPT_IF_EXPR(x == e)	// noexcept as an extension
	{
		return !(x == e);
	}
#endif
};

}	// namespace hamon

HAMON_WARNING_POP()

#endif

#endif // HAMON_EXPECTED_EXPECTED_HPP
