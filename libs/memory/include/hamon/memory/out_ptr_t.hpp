/**
 *	@file	out_ptr_t.hpp
 *
 *	@brief	out_ptr_t の定義
 */

#ifndef HAMON_MEMORY_OUT_PTR_T_HPP
#define HAMON_MEMORY_OUT_PTR_T_HPP

#include <memory>

//#if defined(__cpp_lib_out_ptr) && (__cpp_lib_out_ptr >= 202311L)	// P2833R2 は Free standing 指定だけ
#if defined(__cpp_lib_out_ptr) && (__cpp_lib_out_ptr >= 202106L)

namespace hamon
{

using std::out_ptr_t;

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

// 20.3.4.1 Class template out_ptr_t[out.ptr.t]
template <typename Smart, typename Pointer, typename... Args>
class out_ptr_t
{
private:
	// [out.ptr.t]/3
	static_assert(
		!hamon::detail::is_specialization_of_shared_ptr<Smart>::value ||
		sizeof...(Args) != 0, "");

	// [out.ptr.t]/6.1
	template <typename S = Smart,
		typename = decltype(hamon::declval<S&>().reset())>
	void Construct(hamon::detail::overload_priority<2>)
	{
		m_sp.reset();
	}

	// [out.ptr.t]/6.2
	template <typename S = Smart,
		typename = hamon::enable_if_t<hamon::is_constructible<S>::value>>
	void Construct(hamon::detail::overload_priority<1>)
	{
		m_sp = Smart();
	}

	// [out.ptr.t]/6.3
	void Construct(hamon::detail::overload_priority<0>);

	// [out.ptr.t]/9.1
	template <typename SP, typename S = Smart,
		typename = decltype(hamon::declval<S&>().reset(
			static_cast<SP>(hamon::declval<Pointer&>()), hamon::declval<Args>()...))>
	void Destruct(hamon::detail::overload_priority<2>)
	{
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

	// [out.ptr.t]/9.2
	template <typename SP,
		typename = hamon::enable_if_t<hamon::is_constructible<Smart, SP, Args...>::value>>
	void Destruct(hamon::detail::overload_priority<1>)
	{
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

	// [out.ptr.t]/9.3
	template <typename SP>
	void Destruct(hamon::detail::overload_priority<0>);

public:
	explicit out_ptr_t(Smart& smart, Args... args)
		// [out.ptr.t]/6
		: m_sp(smart)
		, m_args(hamon::forward<Args>(args)...)
		, m_ptr{}
	{
		Construct(hamon::detail::overload_priority<2>{});
	}

	out_ptr_t(out_ptr_t const&) = delete;

#if !defined(HAMON_HAS_CXX17_GUARANTEED_COPY_ELISION)
	out_ptr_t(out_ptr_t &&) = default;
#endif

	~out_ptr_t()
	{
		// [out.ptr.t]/8
		using SP = hamon::detail::POINTER_OF_OR<Smart, Pointer>;

		// [out.ptr.t]/9
		Destruct<SP>(hamon::detail::overload_priority<2>{});
	}

	operator Pointer*() const noexcept
	{
		// [out.ptr.t]/11
		return hamon::addressof(const_cast<Pointer&>(m_ptr));
	}

	template <typename P = Pointer,
		// [out.ptr.t]/12
		typename = hamon::enable_if_t<!hamon::is_same<P, void*>::value>>
	operator void**() const noexcept
	{
		// [out.ptr.t]/13
		static_assert(hamon::is_pointer<Pointer>::value, "");

		// [out.ptr.t]/15,17
		return reinterpret_cast<void**>(static_cast<Pointer*>(*this));
	}

private:
	Smart& m_sp;
	HAMON_NO_UNIQUE_ADDRESS hamon::tuple<Args...> m_args;
	HAMON_NO_UNIQUE_ADDRESS Pointer m_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_OUT_PTR_T_HPP
