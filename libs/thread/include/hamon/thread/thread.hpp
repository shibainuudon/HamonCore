/**
 *	@file	thread.hpp
 *
 *	@brief	thread の定義
 */

#ifndef HAMON_THREAD_THREAD_HPP
#define HAMON_THREAD_THREAD_HPP

#include <hamon/thread/detail/thread_impl.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/make_unique.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/detail/all.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_range.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <exception>	// std::terminate

namespace hamon
{

namespace detail
{

struct thread_id_access;

template <typename>
struct is_thread_attribute : public hamon::false_type{};

template <hamon::size_t, typename...>
struct count_thread_attribute_impl;

template <hamon::size_t N, typename T, typename... Rest>
struct count_thread_attribute_impl<N, T, Rest...>
	: public hamon::conditional_t<
		is_thread_attribute<T>::value,
		count_thread_attribute_impl<N + 1, Rest...>,
		hamon::integral_constant<hamon::size_t, N>
	>
{};

template <typename... Types>
struct count_thread_attribute
	: public count_thread_attribute_impl<0, Types...>
{};

}	// namespace detail

// 32.4.3 Class thread[thread.thread.class]

class thread
{
public:
	// 32.4.3.3 Class thread::id[thread.thread.id]
	class id
	{
	public:
		id() noexcept
			// [thread.thread.id]/5
			: m_id(0)
		{}

	private:
		id(hamon::detail::thread_id id_) : m_id(id_) {}

		hamon::detail::thread_id	m_id;

		friend hamon::detail::thread_id_access;
	};

	// 32.4.3.2.2 Class thread::name_hint[thread.attributes.hint]
	template <HAMON_CONSTRAINT(hamon::same_as, char, T)>
	class name_hint
	{
	public:
		constexpr explicit
		name_hint(hamon::basic_string_view<T> n) noexcept
			// [thread.attributes.hint]/2
			: name(n)
		{}

		name_hint(name_hint&&) = delete;
		name_hint(name_hint const&) = delete;

	private:
		hamon::basic_string_view<T> name;

		friend thread;
	};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	template <typename T>
	name_hint(T const*) -> name_hint<T>;

	template <typename T>
	name_hint(hamon::basic_string<T>) -> name_hint<T>;
#endif

	// 32.4.3.2.3 Class thread::stack_size_hint[thread.attributes.size]
	class stack_size_hint
	{
	public:
		constexpr explicit
		stack_size_hint(hamon::size_t s) noexcept
			// [thread.attributes.size]/4
			: size(s)
		{}

	private:
		hamon::size_t size;

		friend thread;
	};

	using native_handle_type = hamon::detail::thread_t;         // see [thread.req.native]

	// construct/copy/destroy
	thread() noexcept
		// [thread.thread.constr]/1
		: m_handle()
	{}

private:
	template <typename Tuple, hamon::size_t... Indices>
	static void thread_proxy_invoke(Tuple& t, hamon::index_sequence<Indices...>)
	{
		// [thread.thread.constr]/6
		hamon::invoke(hamon::move(hamon::get<Indices>(t))...);
	}

	template <typename Tuple>
	static hamon::detail::thread_proc_return_type
	HAMON_THREAD_PROC_CALLING_CONVENTION
	thread_proxy(void* vp)
	{
		hamon::unique_ptr<Tuple> up(static_cast<Tuple*>(vp));
		thread_proxy_invoke(*up.get(), hamon::make_index_sequence<hamon::tuple_size_v<Tuple>>());
		HAMON_THREAD_PROC_RETURN();
	}

	template <typename T>
	void apply_attr_pre(hamon::detail::thread_attr_t*, T const&)
	{
	}

	void apply_attr_pre(hamon::detail::thread_attr_t* pattr, stack_size_hint const& stacksize)
	{
		if (stacksize.size != 0)	// [thread.attributes.size]/3
		{
			hamon::detail::thread_attr_setstacksize(pattr, stacksize.size);
		}
	}

	template <typename T>
	void apply_attr_post(hamon::detail::thread_attr_t*, T const&)
	{
	}

	template <typename T>
	void apply_attr_post(hamon::detail::thread_attr_t*, name_hint<T> const& name)
	{
		hamon::detail::thread_setname(&m_handle, name.name.data());
	}

	template <typename F, typename... FArgs>
	void do_create_thread(hamon::detail::thread_attr_t* pattr, F&& f, FArgs&&... fargs)
	{
		// [thread.thread.constr]/5.1
		static_assert(hamon::is_constructible_v<hamon::decay_t<F>, F>, "");
		// [thread.thread.constr]/5.2
		static_assert(hamon::detail::all_v<hamon::is_constructible_v<hamon::decay_t<FArgs>, FArgs>...>, "");
		// [thread.thread.constr]/5.3
		static_assert(hamon::is_invocable_v<hamon::decay_t<F>, hamon::decay_t<FArgs>...>, "");

		using Tuple = hamon::tuple<hamon::decay_t<F>, hamon::decay_t<FArgs>...>;
		auto decay_copied = hamon::make_unique<Tuple>(hamon::forward<F>(f), hamon::forward<FArgs>(fargs)...);
		int ec = hamon::detail::thread_create(&m_handle, pattr, hamon::addressof(thread_proxy<Tuple>), decay_copied.get());

		// [thread.thread.constr]/9
		if (ec != 0)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}

		decay_copied.release();
	}

	template <hamon::size_t... Js, hamon::size_t... Ks, typename... Args>
	void create_thread(hamon::detail::thread_attr_t* pattr, hamon::tuple<Args...> args, hamon::index_sequence<Js...>, hamon::index_sequence<Ks...>)
	{
		// [thread.thread.constr]/5.4
		// TODO: no type is present more than once in the pack remove_cvref_t<Attrs>.

		using swallow = hamon::initializer_list<int>;
		(void)swallow{(apply_attr_pre(pattr, hamon::get<Js>(args)), 0)...};
		do_create_thread(pattr, hamon::get<Ks>(args)...);
		(void)swallow{(apply_attr_post(pattr, hamon::get<Js>(args)), 0)...};
	}

public:
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4180)	// 関数型へ適用された修飾子は無効なため、無視されます。
	template <typename... Args,
		typename = hamon::enable_if_t<sizeof...(Args) != 0>,	// [thread.thread.constr]/3.1
		typename = hamon::enable_if_t<!hamon::is_same_v<hamon::remove_cvref_t<hamon::nth_t<0, Args...>>, thread>>// [thread.thread.constr]/3.2
	>
	explicit thread(Args&&... args)
	{
		hamon::detail::thread_attr_t attr;
		hamon::detail::thread_attr_init(&attr);

		// [thread.thread.constr]/4
		constexpr hamon::size_t i = hamon::detail::count_thread_attribute<hamon::decay_t<Args>...>::value;

		// [thread.thread.constr]/5
		static_assert(i < sizeof...(Args), "");

		create_thread(&attr,
			hamon::forward_as_tuple(hamon::forward<Args>(args)...),
			hamon::make_index_range<0, i>{},
			hamon::make_index_range<i, sizeof...(Args)>{});
	}
HAMON_WARNING_POP()

	~thread()
	{
		// [thread.thread.destr]/1
		if (joinable())
		{
			std::terminate();
		}
	}

	thread(thread const&) = delete;

	thread(thread&& x) noexcept
		: m_handle(hamon::exchange(x.m_handle, native_handle_type{}))
	{}

	thread& operator=(thread const&) = delete;

	thread& operator=(thread&& x) noexcept
	{
		// [thread.thread.assign]/1
		if (joinable())
		{
			std::terminate();
		}

		m_handle = hamon::exchange(x.m_handle, native_handle_type{});

		// [thread.thread.assign]/3
		return *this;
	}

	// [thread.thread.member], members
	void swap(thread& x) noexcept
	{
		// [thread.thread.member]/1
		hamon::swap(m_handle, x.m_handle);
	}

	bool joinable() const noexcept
	{
		// [thread.thread.member]/2
		//return get_id() != id();
		return !hamon::detail::thread_isnull(&m_handle);
	}

	void join()
	{
		// [thread.thread.member]/7.1
		// TODO: resource_deadlock_would_occur — if deadlock is detected or get_id() == this_thread​::​​get_id().

		// [thread.thread.member]/7.2
		// TODO: no_such_process — if the thread is not valid.

		// [thread.thread.member]/7.3
		if (!joinable())
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::invalid_argument));
		}

		auto ec = hamon::detail::thread_join(&m_handle);

		// [thread.thread.member]/6
		if (ec != 0)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}

		// [thread.thread.member]/5
		m_handle = {};
	}

	void detach()
	{
		// [thread.thread.member]/11.1
		// TODO: no_such_process — if the thread is not valid.

		// [thread.thread.member]/11.2
		if (!joinable())
		{
			hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::invalid_argument));
		}

		auto ec = hamon::detail::thread_detach(&m_handle);

		// [thread.thread.member]/10
		if (ec != 0)
		{
			hamon::detail::throw_system_error(ec, hamon::generic_category());
		}

		// [thread.thread.member]/9
		m_handle = {};
	}

	id get_id() const noexcept;

	native_handle_type native_handle()                         // see [thread.req.native]
	{
		return m_handle;
	}

	// static members
	static unsigned int hardware_concurrency() noexcept
	{
		// [thread.thread.static]/1
		return hamon::detail::thread_hardware_concurrency();
	}

private:
	native_handle_type	m_handle;
};

inline void swap(thread& x, thread& y) noexcept
{
	// [thread.thread.algorithm]/1
	x.swap(y);
}

// 32.4.3.3 Class thread::id[thread.thread.id]

namespace detail
{

struct thread_id_access
{
	static thread::id
	create(hamon::detail::thread_id const& id_)
	{
		return thread::id{id_};
	}

	static constexpr hamon::detail::thread_id const&
	get_id(thread::id const& x)
	{
		return x.m_id;
	}
};

template <typename T>
struct is_thread_attribute<hamon::thread::name_hint<T>> : public hamon::true_type{};

template <>
struct is_thread_attribute<hamon::thread::stack_size_hint> : public hamon::true_type{};

}	// namespace detail

inline thread::id thread::get_id() const noexcept
{
	// [thread.thread.member]/12
	return hamon::detail::thread_id_access::create(
		hamon::detail::thread_get_id(&m_handle));
}

inline bool operator==(thread::id x, thread::id y) noexcept
{
	// [thread.thread.id]/6
	auto const& lhs = hamon::detail::thread_id_access::get_id(x);
	auto const& rhs = hamon::detail::thread_id_access::get_id(y);
	return hamon::detail::thread_id_equal(lhs, rhs);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

inline hamon::strong_ordering operator<=>(thread::id x, thread::id y) noexcept
{
	// [thread.thread.id]/7,8
	auto const& lhs = hamon::detail::thread_id_access::get_id(x);
	auto const& rhs = hamon::detail::thread_id_access::get_id(y);

	if (hamon::detail::thread_id_less(lhs, rhs))
	{
		return hamon::strong_ordering::less;
	}

	if (hamon::detail::thread_id_less(rhs, lhs))
	{
		return hamon::strong_ordering::greater;
	}

	return hamon::strong_ordering::equal;
}

#else

inline bool operator!=(thread::id x, thread::id y) noexcept
{
	return !(x == y);
}

inline bool operator<(thread::id x, thread::id y) noexcept
{
	auto const& lhs = hamon::detail::thread_id_access::get_id(x);
	auto const& rhs = hamon::detail::thread_id_access::get_id(y);
	return hamon::detail::thread_id_less(lhs, rhs);
}

inline bool operator<=(thread::id x, thread::id y) noexcept
{
	return !(y < x);
}

inline bool operator>(thread::id x, thread::id y) noexcept
{
	return y < x;
}

inline bool operator>=(thread::id x, thread::id y) noexcept
{
	return !(x < y);
}

#endif

#if 0	// TODO
template <typename charT, typename traits>
hamon::basic_ostream<charT, traits>&
operator<<(hamon::basic_ostream<charT, traits>& out, thread::id id);
// [thread.thread.id]/9
// [thread.thread.id]/10
#endif

#if 0	// TODO
template <typename charT>
struct formatter<thread::id, charT>;
// [thread.thread.id]/11
// [thread.thread.id]/12
// [thread.thread.id]/13
#endif

#if 0	// TODO
// hash support
template <typename T>
struct hash;

template <>
struct hash<thread::id>;
// [thread.thread.id]/14
#endif

}	// namespace hamon

#endif // HAMON_THREAD_THREAD_HPP
