/**
 *	@file	inout_ptr_t.hpp
 *
 *	@brief	inout_ptr_t の定義
 */

#ifndef HAMON_MEMORY_INOUT_PTR_T_HPP
#define HAMON_MEMORY_INOUT_PTR_T_HPP

#include <memory>

//#if defined(__cpp_lib_out_ptr) && (__cpp_lib_out_ptr >= 202311L)	// P2833R2 は Free standing 指定だけ
#if defined(__cpp_lib_out_ptr) && (__cpp_lib_out_ptr >= 202106L)

namespace hamon
{

using std::inout_ptr_t;

}	// namespace hamon

#else

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/detail/pointer_of_or.hpp>
#include <hamon/memory/detail/is_specialization_of_shared_ptr.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/tuple.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.4.3 Class template inout_ptr_t[inout.ptr.t]
template <typename Smart, typename Pointer, typename... Args>
class inout_ptr_t
{
private:
	// [inout.ptr.t]/3
	static_assert(!hamon::detail::is_specialization_of_shared_ptr<Smart>::value, "");

	// [inout.ptr.t]/6.1
	template <typename SP, hamon::enable_if_t<hamon::is_pointer<SP>::value>* = nullptr>
	static Pointer get_ptr(SP& sp)
	{
		return sp;
	}

	// [inout.ptr.t]/6.2
	template <typename SP, hamon::enable_if_t<!hamon::is_pointer<SP>::value>* = nullptr>
	static Pointer get_ptr(SP& sp)
	{
		return sp.get();
	}

	// [inout.ptr.t]/11.1
	template <typename SP, typename S = Smart,
		typename = hamon::enable_if_t<hamon::is_pointer<S>::value>>
	void Destruct(hamon::detail::overload_priority<3>)
	{
		hamon::apply(
			[&](Args... args)
			{
				m_sp = Smart(static_cast<SP>(m_ptr), hamon::forward<Args>(args)...);
			},
			hamon::move(m_args));
	}

	// [inout.ptr.t]/11.2
	template <typename SP, typename S = Smart,
		typename = decltype(hamon::declval<S&>().reset(
			static_cast<SP>(hamon::declval<Pointer&>()), hamon::declval<Args>()...))>
	void Destruct(hamon::detail::overload_priority<2>)
	{
		m_sp.release();
		if (m_ptr)
		{
			hamon::apply(
				[&](Args... args)
				{
					m_sp.reset(static_cast<SP>(m_ptr), hamon::forward<Args>(args)...);
				},
				hamon::move(m_args));
		}
	}

	// [inout.ptr.t]/11.3
	template <typename SP, typename S = Smart,
		typename = hamon::enable_if_t<hamon::is_constructible<S, SP, Args...>::value>>
	void Destruct(hamon::detail::overload_priority<1>)
	{
		m_sp.release();
		if (m_ptr)
		{
			hamon::apply(
				[&](Args... args)
				{
					m_sp = Smart(static_cast<SP>(m_ptr), hamon::forward<Args>(args)...);
				},
				hamon::move(m_args));
		}
	}

	// [inout.ptr.t]/11.4
	template <typename SP>
	void Destruct(hamon::detail::overload_priority<0>);

public:
	explicit inout_ptr_t(Smart& smart, Args... args)
		// [inout.ptr.t]/6
		: m_sp(smart)
		, m_args(hamon::forward<Args>(args)...)
		, m_ptr(get_ptr(smart))
	{}

	inout_ptr_t(inout_ptr_t const&) = delete;

#if !defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	inout_ptr_t(inout_ptr_t &&) = default;
#endif

	~inout_ptr_t()
	{
		// [inout.ptr.t]/9
		using SP = hamon::detail::POINTER_OF_OR<Smart, Pointer>;

		// [inout.ptr.t]/11
		Destruct<SP>(hamon::detail::overload_priority<3>{});
	}

	operator Pointer*() const noexcept
	{
		// [inout.ptr.t]/13
		return hamon::addressof(const_cast<Pointer&>(m_ptr));
	}

	template <typename P = Pointer,
		// [inout.ptr.t]/14
		typename = hamon::enable_if_t<!hamon::is_same<P, void*>::value>>
	operator void**() const noexcept
	{
		// [inout.ptr.t]/17,19
		return reinterpret_cast<void**>(static_cast<Pointer*>(*this));
	}

private:
	Smart& m_sp;
	HAMON_NO_UNIQUE_ADDRESS hamon::tuple<Args...> m_args;
	HAMON_NO_UNIQUE_ADDRESS Pointer m_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_INOUT_PTR_T_HPP
