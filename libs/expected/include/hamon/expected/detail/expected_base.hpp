/**
 *	@file	expected_base.hpp
 *
 *	@brief	expected_base の定義
 */

#ifndef HAMON_EXPECTED_DETAIL_EXPECTED_BASE_HPP
#define HAMON_EXPECTED_DETAIL_EXPECTED_BASE_HPP

#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/detail/tags.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
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

template <typename T, typename E,
	bool = hamon::is_trivially_destructible<T>::value &&	// [expected.object.dtor]/2
	       hamon::is_trivially_destructible<E>::value>
struct expected_union
{
	union
	{
		T val;
		E unex;
	};
	bool has_val;

	HAMON_CXX11_CONSTEXPR explicit
	expected_union() {}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::in_place_t, Args&&... args)
		: val(hamon::forward<Args>(args)...)
		, has_val(true)
	{}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::unexpect_t, Args&&... args)
		: unex(hamon::forward<Args>(args)...)
		, has_val(false)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::detail::expected_in_place_invoke_tag, F&& f, Args&&... args)
		: val(hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...))
		, has_val(true)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::detail::expected_unexpect_invoke_tag, F&& f, Args&&... args)
		: unex(hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...))
		, has_val(false)
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
	union
	{
		T val;
		E unex;
	};
	bool has_val;

	HAMON_CXX11_CONSTEXPR explicit
	expected_union() {}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::in_place_t, Args&&... args)
		: val(hamon::forward<Args>(args)...)
		, has_val(true)
	{}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::unexpect_t, Args&&... args)
		: unex(hamon::forward<Args>(args)...)
		, has_val(false)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::detail::expected_in_place_invoke_tag, F&& f, Args&&... args)
		: val(hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...))
		, has_val(true)
	{}

	template <typename F, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	expected_union(hamon::detail::expected_unexpect_invoke_tag, F&& f, Args&&... args)
		: unex(hamon::invoke(hamon::forward<F>(f), hamon::forward<Args>(args)...))
		, has_val(false)
	{}

	// [expected.object.dtor]/2
	// ~expected_union();
};

// expected<T, E>のコピー/ムーブコンストラクタにおいて、
// TとEが両方ともTriviallyMoveConstructibleであるとき、expected_union を構築してそれをムーブする。
// そうでないときは construct_at を使って構築する。
// 
// これにより、
//  * C++20以降では常にconstexpr
//  * それ以前ではTriviallyMoveConstructibleならconstexpr
// にできる。
template <typename T, typename E, bool =
	hamon::is_trivially_move_constructible<T>::value &&
	hamon::is_trivially_move_constructible<E>::value>
struct expected_ctor : public expected_union<T, E>
{
	using base_type = expected_union<T, E>;
	using base_type::base_type;

private:
	template <typename Expected>
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

public:
	template <typename U, typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_ctor(expected_ctor_tag, expected_ctor<U, G> const& rhs)
		: base_type(make_union(rhs))
	{}

	template <typename U, typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_ctor(expected_ctor_tag, expected_ctor<U, G>&& rhs)
		: base_type(make_union(hamon::move(rhs)))
	{}
};

template <typename T, typename E>
struct expected_ctor<T, E, false> : public expected_union<T, E>
{
	using base_type = expected_union<T, E>;
	using base_type::base_type;

private:
	template <typename Expected>
	HAMON_CXX14_CONSTEXPR void
	make_union(Expected&& rhs)
	{
		if (rhs.has_val)
		{
			hamon::construct_at(this, hamon::in_place, hamon::forward<Expected>(rhs).val);
		}
		else
		{
			hamon::construct_at(this, hamon::unexpect, hamon::forward<Expected>(rhs).unex);
		}
	}

public:
	template <typename U, typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_ctor(expected_ctor_tag, expected_ctor<U, G> const& rhs)
		: base_type()
	{
		make_union(rhs);
	}

	template <typename U, typename G>
	HAMON_CXX14_CONSTEXPR explicit
	expected_ctor(expected_ctor_tag, expected_ctor<U, G>&& rhs)
		: base_type()
	{
		make_union(hamon::move(rhs));
	}
};

template <typename T, typename E>
struct expected_impl : public expected_ctor<T, E>
{
	using base_type = expected_ctor<T, E>;
	using base_type::base_type;

private:
	HAMON_CXX14_CONSTEXPR T&
	get(hamon::in_place_t)
	{
		return this->val;
	}

	HAMON_CXX14_CONSTEXPR E&
	get(hamon::unexpect_t)
	{
		return this->unex;
	}

	template <typename Tag>
	using get_type = hamon::conditional_t<
		hamon::is_same<Tag, hamon::in_place_t>::value, T, E>;

public:
	template <typename Tag, typename... Args>
	HAMON_CXX14_CONSTEXPR get_type<Tag>*
	construct_at(Tag, Args&&... args)
	{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
		return hamon::construct_at(hamon::addressof(this->get(Tag{})), hamon::forward<Args>(args)...);
#else
		hamon::construct_at(this, Tag{}, hamon::forward<Args>(args)...);
		return hamon::addressof(this->get(Tag{}));
#endif
	}

	template <typename Tag>
	HAMON_CXX14_CONSTEXPR void
	destroy_at(Tag)
	{
		hamon::destroy_at(hamon::addressof(this->get(Tag{})));
	}

private:
	// [expected.object.assign]/1
	// 
	// template<class T, class U, class... Args>
	// constexpr void reinit-expected(T& newval, U& oldval, Args&&... args) {  // exposition only
	//   if constexpr (is_nothrow_constructible_v<T, Args...>) {
	//     destroy_at(addressof(oldval));
	//     construct_at(addressof(newval), std::forward<Args>(args)...);
	//   } else if constexpr (is_nothrow_move_constructible_v<T>) {
	//     T tmp(std::forward<Args>(args)...);
	//     destroy_at(addressof(oldval));
	//     construct_at(addressof(newval), std::move(tmp));
	//   } else {
	//     U tmp(std::move(oldval));
	//     destroy_at(addressof(oldval));
	//     try {
	//       construct_at(addressof(newval), std::forward<Args>(args)...);
	//     } catch (...) {
	//       construct_at(addressof(oldval), std::move(tmp));
	//       throw;
	//     }
	//   }
	// }

	template <typename NewValTag, typename OldValTag, typename Arg,
		typename U = get_type<NewValTag>,
		typename = hamon::enable_if_t<hamon::is_nothrow_constructible<U, Arg>::value>>
	HAMON_CXX14_CONSTEXPR void
	reinit_expected_impl(NewValTag, OldValTag, Arg&& arg, hamon::detail::overload_priority<2>)
	{
		this->destroy_at(OldValTag{});
		this->construct_at(NewValTag{}, hamon::forward<Arg>(arg));
	}

	template <typename NewValTag, typename OldValTag, typename Arg,
		typename U = get_type<NewValTag>,
		typename = hamon::enable_if_t<hamon::is_nothrow_move_constructible<U>::value>>
	HAMON_CXX14_CONSTEXPR void
	reinit_expected_impl(NewValTag, OldValTag, Arg&& arg, hamon::detail::overload_priority<1>)
	{
		U tmp(hamon::forward<Arg>(arg));
		this->destroy_at(OldValTag{});
		this->construct_at(NewValTag{}, hamon::move(tmp));
	}

	template <typename NewValTag, typename OldValTag, typename Arg,
		typename G = get_type<OldValTag>>
	HAMON_CXX20_CONSTEXPR void
	reinit_expected_impl(NewValTag, OldValTag, Arg&& arg, hamon::detail::overload_priority<0>)
	{
#if defined(HAMON_NO_EXCEPTIONS)
		this->destroy_at(OldValTag{});
		this->construct_at(NewValTag{}, hamon::forward<Arg>(arg));
#else
		G tmp(hamon::move(this->get(OldValTag{})));
		this->destroy_at(OldValTag{});
		try
		{
			this->construct_at(NewValTag{}, hamon::forward<Arg>(arg));
		}
		catch (...)
		{
			this->construct_at(OldValTag{}, hamon::move(tmp));
			throw;
		}
#endif
	}

public:
	template <typename NewValTag, typename OldValTag, typename Arg>
	HAMON_CXX14_CONSTEXPR void
	reinit(NewValTag, OldValTag, Arg&& arg)
	{
		this->reinit_expected_impl(NewValTag{}, OldValTag{}, hamon::forward<Arg>(arg),
			hamon::detail::overload_priority<2>{});
	}

private:
	// [expected.object.swap]/2
	// 
	//if constexpr (is_nothrow_move_constructible_v<E>) {
	//  E tmp(std::move(rhs.unex));
	//  destroy_at(addressof(rhs.unex));
	//  try {
	//    construct_at(addressof(rhs.val), std::move(val));
	//    destroy_at(addressof(val));
	//    construct_at(addressof(unex), std::move(tmp));
	//  } catch(...) {
	//    construct_at(addressof(rhs.unex), std::move(tmp));
	//    throw;
	//  }
	//} else {
	//  T tmp(std::move(val));
	//  destroy_at(addressof(val));
	//  try {
	//    construct_at(addressof(unex), std::move(rhs.unex));
	//    destroy_at(addressof(rhs.unex));
	//    construct_at(addressof(rhs.val), std::move(tmp));
	//  } catch (...) {
	//    construct_at(addressof(val), std::move(tmp));
	//    throw;
	//  }
	//}
	//has_val = false;
	//rhs.has_val = true;

	template <typename U, typename G,
		typename = hamon::enable_if_t<
			hamon::is_nothrow_move_constructible<U>::value &&
			hamon::is_nothrow_move_constructible<G>::value>>
	HAMON_CXX14_CONSTEXPR void
	swap_val_unex_impl(expected_impl<U, G>& rhs, hamon::detail::overload_priority<2>)
	{
		G tmp(hamon::move(rhs.unex));
		rhs.destroy_at(hamon::unexpect);
		rhs.construct_at(hamon::in_place, hamon::move(this->val));
		this->destroy_at(hamon::in_place);
		this->construct_at(hamon::unexpect, hamon::move(tmp));
	}

	template <typename U, typename G,
		typename = hamon::enable_if_t<hamon::is_nothrow_move_constructible<G>::value>>
	HAMON_CXX20_CONSTEXPR void
	swap_val_unex_impl(expected_impl<U, G>& rhs, hamon::detail::overload_priority<1>)
	{
		G tmp(hamon::move(rhs.unex));
		hamon::destroy_at(hamon::addressof(rhs.unex));
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			hamon::construct_at(hamon::addressof(rhs.val), hamon::move(this->val));
			hamon::destroy_at(hamon::addressof(this->val));
			hamon::construct_at(hamon::addressof(this->unex), hamon::move(tmp));
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			hamon::construct_at(hamon::addressof(rhs.unex), hamon::move(tmp));
			throw;
		}
#endif
	}

	template <typename U, typename G>
	HAMON_CXX20_CONSTEXPR void
	swap_val_unex_impl(expected_impl<U, G>& rhs, hamon::detail::overload_priority<0>)
	{
		U tmp(hamon::move(this->val));
		hamon::destroy_at(hamon::addressof(this->val));
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			hamon::construct_at(hamon::addressof(this->unex), hamon::move(rhs.unex));
			hamon::destroy_at(hamon::addressof(rhs.unex));
			hamon::construct_at(hamon::addressof(rhs.val), hamon::move(tmp));
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			hamon::construct_at(hamon::addressof(this->val), hamon::move(tmp));
			throw;
		}
#endif
	}

public:
	HAMON_CXX14_CONSTEXPR void
	swap_val_unex(expected_impl& rhs)
	{
		this->swap_val_unex_impl(rhs, hamon::detail::overload_priority<2>{});
		this->has_val = false;
		rhs.has_val = true;
	}
};

template <typename T, typename E,
	bool = hamon::is_default_constructible<T>::value>	// [expected.object.cons]/2
struct expected_ctor_default : public expected_impl<T, E>
{
	using base_type = expected_impl<T, E>;
	using base_type::base_type;

	expected_ctor_default() = delete;
};

template <typename T, typename E>
struct expected_ctor_default<T, E, true> : public expected_impl<T, E>
{
	using base_type = expected_impl<T, E>;
	using base_type::base_type;

	HAMON_CXX11_CONSTEXPR
	expected_ctor_default() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<T>::value)
		: base_type(hamon::in_place)	// [expected.object.cons]/3
	{}
};

template <typename T, typename E,
	bool = hamon::is_copy_constructible<T>::value &&			// [expected.object.cons]/9.1
	       hamon::is_copy_constructible<E>::value,				// [expected.object.cons]/9.2
	bool = hamon::is_trivially_copy_constructible<T>::value &&	// [expected.object.cons]/10.1
	       hamon::is_trivially_copy_constructible<E>::value>	// [expected.object.cons]/10.2
struct expected_ctor_copy : public expected_ctor_default<T, E>
{
	using base_type = expected_ctor_default<T, E>;
	using base_type::base_type;

	expected_ctor_copy()                     = default;
	expected_ctor_copy(expected_ctor_copy&&) = default;

	// [expected.object.cons]/9
	expected_ctor_copy(expected_ctor_copy const& rhs) = delete;
};

template <typename T, typename E>
struct expected_ctor_copy<T, E, true, true> : public expected_ctor_default<T, E>
{
	using base_type = expected_ctor_default<T, E>;
	using base_type::base_type;

	expected_ctor_copy()                     = default;
	expected_ctor_copy(expected_ctor_copy&&) = default;

	// [expected.object.cons]/10
	expected_ctor_copy(expected_ctor_copy const& rhs) = default;
};

template <typename T, typename E>
struct expected_ctor_copy<T, E, true, false> : public expected_ctor_default<T, E>
{
	using base_type = expected_ctor_default<T, E>;
	using base_type::base_type;

	expected_ctor_copy()                     = default;
	expected_ctor_copy(expected_ctor_copy&&) = default;

	// [expected.object.cons]/6
	HAMON_CXX11_CONSTEXPR
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
	       hamon::is_trivially_move_constructible<E>::value>	// [expected.object.cons]/16.2
struct expected_ctor_move : public expected_ctor_copy<T, E>
{
	using base_type = expected_ctor_copy<T, E>;
	using base_type::base_type;

	expected_ctor_move()                              = default;
	expected_ctor_move(expected_ctor_move const& rhs) = default;

	// [expected.object.cons]/11
	expected_ctor_move(expected_ctor_move&& rhs) = delete;
};

template <typename T, typename E>
struct expected_ctor_move<T, E, true, true> : public expected_ctor_copy<T, E>
{
	using base_type = expected_ctor_copy<T, E>;
	using base_type::base_type;

	expected_ctor_move()                              = default;
	expected_ctor_move(expected_ctor_move const& rhs) = default;

	// [expected.object.cons]/16
	expected_ctor_move(expected_ctor_move&& rhs) = default;
};

template <typename T, typename E>
struct expected_ctor_move<T, E, true, false> : public expected_ctor_copy<T, E>
{
	using base_type = expected_ctor_copy<T, E>;
	using base_type::base_type;

	expected_ctor_move()                              = default;
	expected_ctor_move(expected_ctor_move const& rhs) = default;

	// [expected.object.cons]/12
	HAMON_CXX11_CONSTEXPR
	expected_ctor_move(expected_ctor_move&& rhs) HAMON_NOEXCEPT_IF(	// [expected.object.cons]/15
		hamon::is_nothrow_move_constructible<T>::value &&
		hamon::is_nothrow_move_constructible<E>::value)
		: base_type(hamon::detail::expected_ctor_tag{}, hamon::move(rhs))
	{}
};

template <typename T, typename E, bool =
	hamon::is_copy_assignable<T>::value    &&			// [expected.object.assign]/4.1
	hamon::is_copy_constructible<T>::value &&			// [expected.object.assign]/4.2
	hamon::is_copy_assignable<E>::value    &&			// [expected.object.assign]/4.3
	hamon::is_copy_constructible<E>::value &&			// [expected.object.assign]/4.4
	(hamon::is_nothrow_move_constructible<T>::value ||	// [expected.object.assign]/4.5
	 hamon::is_nothrow_move_constructible<E>::value)>
struct expected_assign_copy : public expected_ctor_move<T, E>
{
	using base_type = expected_ctor_move<T, E>;
	using base_type::base_type;

	expected_assign_copy()                            = default;
	expected_assign_copy(expected_assign_copy const&) = default;
	expected_assign_copy(expected_assign_copy&&)      = default;

	// [expected.object.assign]/4
	expected_assign_copy& operator=(expected_assign_copy const&) = delete;
};

template <typename T, typename E>
struct expected_assign_copy<T, E, true> : public expected_ctor_move<T, E>
{
	using base_type = expected_ctor_move<T, E>;
	using base_type::base_type;

	expected_assign_copy()                            = default;
	expected_assign_copy(expected_assign_copy const&) = default;
	expected_assign_copy(expected_assign_copy&&)      = default;

	// [expected.object.assign]/2
	HAMON_CXX14_CONSTEXPR expected_assign_copy&
	operator=(expected_assign_copy const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_assignable<T>::value    &&
		hamon::is_nothrow_copy_assignable<E>::value    &&
		hamon::is_nothrow_copy_constructible<T>::value &&
		hamon::is_nothrow_copy_constructible<E>::value)
	{
		if (this->has_val)
		{
			if (rhs.has_val)
			{
				// [expected.object.assign]/2.1
				this->val = rhs.val;
			}
			else
			{
				// [expected.object.assign]/2.2
				//hamon::detail::reinit_expected(this->unex, this->val, rhs.unex);
				this->reinit(hamon::unexpect, hamon::in_place, rhs.unex);
			}
		}
		else
		{
			if (rhs.has_val)
			{
				// [expected.object.assign]/2.3
				//hamon::detail::reinit_expected(this->val, this->unex, rhs.val);
				this->reinit(hamon::in_place, hamon::unexpect, rhs.val);
			}
			else
			{
				// [expected.object.assign]/2.4
				this->unex = rhs.unex;
			}
		}

		// [expected.object.assign]/2
		this->has_val = rhs.has_val;

		// [expected.object.assign]/3
		return *this;
	}
};

template <typename T, typename E, bool =
	hamon::is_move_constructible<T>::value &&			// [expected.object.assign]/5.1
	hamon::is_move_assignable<T>::value    &&			// [expected.object.assign]/5.2
	hamon::is_move_constructible<E>::value &&			// [expected.object.assign]/5.3
	hamon::is_move_assignable<E>::value    &&			// [expected.object.assign]/5.4
	(hamon::is_nothrow_move_constructible<T>::value ||	// [expected.object.assign]/5.5
	 hamon::is_nothrow_move_constructible<E>::value)>
struct expected_assign_move : public expected_assign_copy<T, E>
{
	using base_type = expected_assign_copy<T, E>;
	using base_type::base_type;

	expected_assign_move()                                       = default;
	expected_assign_move(expected_assign_move const&)            = default;
	expected_assign_move(expected_assign_move&&)                 = default;
	expected_assign_move& operator=(expected_assign_move const&) = default;

	// [expected.object.assign]/5
	expected_assign_move& operator=(expected_assign_move&&) = delete;
};

template <typename T, typename E>
struct expected_assign_move<T, E, true> : public expected_assign_copy<T, E>
{
	using base_type = expected_assign_copy<T, E>;
	using base_type::base_type;

	expected_assign_move()                                       = default;
	expected_assign_move(expected_assign_move const&)            = default;
	expected_assign_move(expected_assign_move&&)                 = default;
	expected_assign_move& operator=(expected_assign_move const&) = default;

	// [expected.object.assign]/6
	HAMON_CXX14_CONSTEXPR expected_assign_move&
	operator=(expected_assign_move&& rhs) HAMON_NOEXCEPT_IF(	// [expected.object.assign]/8
		hamon::is_nothrow_move_assignable<T>::value    &&
		hamon::is_nothrow_move_assignable<E>::value    &&
		hamon::is_nothrow_move_constructible<T>::value &&
		hamon::is_nothrow_move_constructible<E>::value)
	{
		if (this->has_val)
		{
			if (rhs.has_val)
			{
				// [expected.object.assign]/6.1
				this->val = hamon::move(rhs.val);
			}
			else
			{
				// [expected.object.assign]/6.2
				//hamon::detail::reinit_expected(this->unex, this->val, hamon::move(rhs.unex));
				this->reinit(hamon::unexpect, hamon::in_place, hamon::move(rhs.unex));
			}
		}
		else
		{
			if (rhs.has_val)
			{
				// [expected.object.assign]/6.3
				//hamon::detail::reinit_expected(this->val, this->unex, hamon::move(rhs.val));
				this->reinit(hamon::in_place, hamon::unexpect, hamon::move(rhs.val));
			}
			else
			{
				// [expected.object.assign]/6.4
				this->unex = hamon::move(rhs.unex);
			}
		}

		// [expected.object.assign]/6
		this->has_val = rhs.has_val;

		// [expected.object.assign]/7
		return *this;
	}
};

template <typename T, typename E>
using expected_base = expected_assign_move<T, E>;

}	// namespace detail

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_EXPECTED_DETAIL_EXPECTED_BASE_HPP
