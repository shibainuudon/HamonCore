/**
 *	@file	expected_void_base.hpp
 *
 *	@brief	expected_void_base の定義
 */

#ifndef HAMON_EXPECTED_DETAIL_EXPECTED_VOID_BASE_HPP
#define HAMON_EXPECTED_DETAIL_EXPECTED_VOID_BASE_HPP

#include <hamon/expected/detail/tags.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

namespace detail
{

template <typename E,
	bool = hamon::is_trivially_destructible<E>::value>	// [expected.void.dtor]/2
struct expected_void_union
{
	struct empty_t{};

	union
	{
		empty_t empty;
		E unex;
	};
	bool has_val;

	HAMON_CXX11_CONSTEXPR explicit
	expected_void_union(hamon::in_place_t)
		: empty()
		, has_val(true)
	{}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_void_union(hamon::unexpect_t, Args&&... args)
		: unex(hamon::forward<Args>(args)...)
		, has_val(false)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_void_union(hamon::detail::expected_unexpect_invoke_tag, F&& f, Args&&... args)
		: unex(hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...))
		, has_val(false)
	{}

	// [expected.void.dtor]/1
	HAMON_CXX20_CONSTEXPR
	~expected_void_union()
	{
		if (!has_val)
		{
			this->unex.~E();
		}
	}
};

template <typename E>
struct expected_void_union<E, true>
{
	struct empty_t{};

	union
	{
		empty_t empty;
		E unex;
	};
	bool has_val;

	HAMON_CXX11_CONSTEXPR explicit
	expected_void_union(hamon::in_place_t)
		: empty()
		, has_val(true)
	{}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_void_union(hamon::unexpect_t, Args&&... args)
		: unex(hamon::forward<Args>(args)...)
		, has_val(false)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_void_union(hamon::detail::expected_unexpect_invoke_tag, F&& f, Args&&... args)
		: unex(hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...))
		, has_val(false)
	{}

	// [expected.void.dtor]/2
	// ~expected_void_union();
};

// expected<void, E>のコピー/ムーブコンストラクタにおいて、
// EがTriviallyMoveConstructibleであるとき、expected_void_union を構築してそれをムーブする。
// そうでないときは construct_at を使って構築する。
// 
// これにより、
//  * C++20以降では常にconstexpr
//  * それ以前ではTriviallyMoveConstructibleならconstexpr
// にできる。
template <typename E,
	bool = hamon::is_trivially_move_constructible<E>::value>
struct expected_void_ctor : public expected_void_union<E>
{
	using base_type = expected_void_union<E>;
	using base_type::base_type;

private:
	template <typename Expected>
	static HAMON_CXX14_CONSTEXPR expected_void_union<E>
	make_union(Expected&& rhs)
	{
		if (rhs.has_val)
		{
			return expected_void_union<E>{hamon::in_place};
		}
		else
		{
			return expected_void_union<E>{hamon::unexpect, hamon::forward<Expected>(rhs).unex};
		}
	}

public:
	template <typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_void_ctor(expected_ctor_tag, expected_void_ctor<G> const& rhs)
		: base_type(make_union(rhs))
	{}

	template <typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_void_ctor(expected_ctor_tag, expected_void_ctor<G>&& rhs)
		: base_type(make_union(hamon::move(rhs)))
	{}
};

template <typename E>
struct expected_void_ctor<E, false> : public expected_void_union<E>
{
	using base_type = expected_void_union<E>;
	using base_type::base_type;

private:
	template <typename Expected>
	HAMON_CXX14_CONSTEXPR void
	make_union(Expected&& rhs)
	{
		if (rhs.has_val)
		{
			hamon::construct_at(this, hamon::in_place);
		}
		else
		{
			hamon::construct_at(this, hamon::unexpect, hamon::forward<Expected>(rhs).unex);
		}
	}

public:
	template <typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_void_ctor(expected_ctor_tag, expected_void_ctor<G> const& rhs)
		: base_type(hamon::in_place)
	{
		make_union(rhs);
	}

	template <typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_void_ctor(expected_ctor_tag, expected_void_ctor<G>&& rhs)
		: base_type(hamon::in_place)
	{
		make_union(hamon::move(rhs));
	}
};

template <typename E>
struct expected_void_impl : public expected_void_ctor<E>
{
	using base_type = expected_void_ctor<E>;
	using base_type::base_type;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void
	construct_at(hamon::unexpect_t, Args&&... args)
	{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
		hamon::construct_at(hamon::addressof(this->unex), hamon::forward<Args>(args)...);
#else
		hamon::construct_at(this, hamon::unexpect, hamon::forward<Args>(args)...);
#endif
	}
};

template <typename E,
	bool = hamon::is_copy_constructible<E>::value,				// [expected.void.cons]/5
	bool = hamon::is_trivially_copy_constructible<E>::value>	// [expected.void.cons]/6
struct expected_void_ctor_copy : public expected_void_impl<E>
{
	using base_type = expected_void_impl<E>;
	using base_type::base_type;

	expected_void_ctor_copy()                          = default;
	expected_void_ctor_copy(expected_void_ctor_copy&&) = default;

	// [expected.void.cons]/5
	expected_void_ctor_copy(expected_void_ctor_copy const& rhs) = delete;
};

template <typename E>
struct expected_void_ctor_copy<E, true, true> : public expected_void_impl<E>
{
	using base_type = expected_void_impl<E>;
	using base_type::base_type;

	expected_void_ctor_copy()                          = default;
	expected_void_ctor_copy(expected_void_ctor_copy&&) = default;

	// [expected.void.cons]/6
	expected_void_ctor_copy(expected_void_ctor_copy const& rhs) = default;
};

template <typename E>
struct expected_void_ctor_copy<E, true, false> : public expected_void_impl<E>
{
	using base_type = expected_void_impl<E>;
	using base_type::base_type;

	expected_void_ctor_copy()                          = default;
	expected_void_ctor_copy(expected_void_ctor_copy&&) = default;

	// [expected.void.cons]/2
	HAMON_CXX11_CONSTEXPR
	expected_void_ctor_copy(expected_void_ctor_copy const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<E>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, rhs)
	{}
};

template <typename E,
	bool = hamon::is_move_constructible<E>::value,				// [expected.void.cons]/7
	bool = hamon::is_trivially_move_constructible<E>::value>	// [expected.void.cons]/11
struct expected_void_ctor_move : public expected_void_ctor_copy<E>
{
	using base_type = expected_void_ctor_copy<E>;
	using base_type::base_type;

	expected_void_ctor_move()                                   = default;
	expected_void_ctor_move(expected_void_ctor_move const& rhs) = default;

	// [expected.void.cons]/7
	expected_void_ctor_move(expected_void_ctor_move&& rhs) = delete;
};

template <typename E>
struct expected_void_ctor_move<E, true, true> : public expected_void_ctor_copy<E>
{
	using base_type = expected_void_ctor_copy<E>;
	using base_type::base_type;

	expected_void_ctor_move()                                   = default;
	expected_void_ctor_move(expected_void_ctor_move const& rhs) = default;

	// [expected.void.cons]/11
	expected_void_ctor_move(expected_void_ctor_move&& rhs) = default;
};

template <typename E>
struct expected_void_ctor_move<E, true, false> : public expected_void_ctor_copy<E>
{
	using base_type = expected_void_ctor_copy<E>;
	using base_type::base_type;

	expected_void_ctor_move()                                   = default;
	expected_void_ctor_move(expected_void_ctor_move const& rhs) = default;

	// [expected.void.cons]/8
	HAMON_CXX11_CONSTEXPR
	expected_void_ctor_move(expected_void_ctor_move&& rhs) HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_move_constructible<E>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}
};

template <typename E, bool =
	hamon::is_copy_assignable<E>::value &&			// [expected.void.assign]/3
	hamon::is_copy_constructible<E>::value>
struct expected_void_assign_copy : public expected_void_ctor_move<E>
{
	using base_type = expected_void_ctor_move<E>;
	using base_type::base_type;

	expected_void_assign_copy()                                 = default;
	expected_void_assign_copy(expected_void_assign_copy const&) = default;
	expected_void_assign_copy(expected_void_assign_copy&&)      = default;

	// [expected.void.assign]/3
	expected_void_assign_copy& operator=(expected_void_assign_copy const&) = delete;
};

template <typename E>
struct expected_void_assign_copy<E, true> : public expected_void_ctor_move<E>
{
	using base_type = expected_void_ctor_move<E>;
	using base_type::base_type;

	expected_void_assign_copy()                                 = default;
	expected_void_assign_copy(expected_void_assign_copy const&) = default;
	expected_void_assign_copy(expected_void_assign_copy&&)      = default;

	HAMON_CXX14_CONSTEXPR expected_void_assign_copy&
	operator=(expected_void_assign_copy const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<E>::value &&
		hamon::is_nothrow_copy_assignable<E>::value)
	{
		// [expected.void.assign]/1
		if (this->has_val)
		{
			if (rhs.has_val)
			{
				// [expected.void.assign]/1.1
			}
			else
			{
				// [expected.void.assign]/1.2
				//hamon::construct_at(hamon::addressof(this->unex), rhs.unex);
				this->construct_at(hamon::unexpect, rhs.unex);
				this->has_val = false;
			}
		}
		else
		{
			if (rhs.has_val)
			{
				// [expected.void.assign]/1.3
				hamon::destroy_at(hamon::addressof(this->unex));
				this->has_val = true;
			}
			else
			{
				// [expected.void.assign]/1.4
				this->unex = rhs.unex;
			}
		}

		// [expected.void.assign]/2
		return *this;
	}
};

template <typename E, bool =
	hamon::is_move_constructible<E>::value &&	// [expected.void.assign]/4
	hamon::is_move_assignable<E>::value>
struct expected_void_assign_move : public expected_void_assign_copy<E>
{
	using base_type = expected_void_assign_copy<E>;
	using base_type::base_type;

	expected_void_assign_move()                                            = default;
	expected_void_assign_move(expected_void_assign_move const&)            = default;
	expected_void_assign_move(expected_void_assign_move&&)                 = default;
	expected_void_assign_move& operator=(expected_void_assign_move const&) = default;

	// [expected.void.assign]/4
	expected_void_assign_move& operator=(expected_void_assign_move&&) = delete;
};

template <typename E>
struct expected_void_assign_move<E, true> : public expected_void_assign_copy<E>
{
	using base_type = expected_void_assign_copy<E>;
	using base_type::base_type;

	expected_void_assign_move()                                            = default;
	expected_void_assign_move(expected_void_assign_move const&)            = default;
	expected_void_assign_move(expected_void_assign_move&&)                 = default;
	expected_void_assign_move& operator=(expected_void_assign_move const&) = default;

	HAMON_CXX14_CONSTEXPR expected_void_assign_move&
	operator=(expected_void_assign_move&& rhs) HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_move_constructible<E>::value &&	// [expected.void.assign]/7
		hamon::is_nothrow_move_assignable<E>::value)
	{
		// [expected.void.assign]/5
		if (this->has_val)
		{
			if (rhs.has_val)
			{
				// [expected.void.assign]/5.1
			}
			else
			{
				// [expected.void.assign]/5.2
				//hamon::construct_at(hamon::addressof(this->unex), hamon::move(rhs.unex));
				this->construct_at(hamon::unexpect, hamon::move(rhs.unex));
				this->has_val = false;
			}
		}
		else
		{
			if (rhs.has_val)
			{
				// [expected.void.assign]/5.3
				hamon::destroy_at(hamon::addressof(this->unex));
				this->has_val = true;
			}
			else
			{
				// [expected.void.assign]/5.4
				this->unex = hamon::move(rhs.unex);
			}
		}

		// [expected.void.assign]/6
		return *this;
	}
};

template <typename E>
using expected_void_base = expected_void_assign_move<E>;

}	// namespace detail

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_EXPECTED_DETAIL_EXPECTED_VOID_BASE_HPP
