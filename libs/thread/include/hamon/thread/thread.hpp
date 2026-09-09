/**
 *	@file	thread.hpp
 *
 *	@brief	thread の定義
 */

#ifndef HAMON_THREAD_THREAD_HPP
#define HAMON_THREAD_THREAD_HPP

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.4.3 Class thread[thread.thread.class]

class thread
{
public:
	// [thread.thread.id], class thread​::​id
	class id;

	// 32.4.3.2.2 Class thread​::​name_hint[thread.attributes.hint]
	template <HAMON_CONSTRAINT(hamon::same_as, char, T)>
	class name_hint
	{
	public:
		constexpr explicit
		name_hint(hamon::basic_string_view<T> n) noexcept;

		name_hint(name_hint&&) = delete;
		name_hint(name_hint const&) = delete;

	private:
		hamon::basic_string_view<T> name;
	};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	template <typename T>
	name_hint(T const*) -> name_hint<T>;

	template <typename T>
	name_hint(hamon::basic_string<T>) -> name_hint<T>;
#endif

	// 32.4.3.2.3 Class thread​::​stack_size_hint[thread.attributes.size]
	class stack_size_hint
	{
	public:
		constexpr explicit stack_size_hint(hamon::size_t s) noexcept;

	private:
		hamon::size_t size;
	};

//	using native_handle_type = implementation-defined;         // see [thread.req.native]

	// construct/copy/destroy
	thread() noexcept;

	template <typename... Args>
	explicit thread(Args&&... args);

	~thread();

	thread(thread const&) = delete;
	thread(thread&&) noexcept;
	thread& operator=(thread const&) = delete;
	thread& operator=(thread&&) noexcept;

	// [thread.thread.member], members
	void swap(thread&) noexcept;
	bool joinable() const noexcept;
	void join();
	void detach();
	id get_id() const noexcept;

//	native_handle_type native_handle();                         // see [thread.req.native]

	// static members
	static unsigned int hardware_concurrency() noexcept;
};

void swap(thread& x, thread& y) noexcept;

// 32.4.3.3 Class thread​::​id[thread.thread.id]

class thread::id
{
public:
	id() noexcept;
};

bool operator==(thread::id x, thread::id y) noexcept;

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
hamon::strong_ordering operator<=>(thread::id x, thread::id y) noexcept;
#endif

template <typename charT, typename traits>
hamon::basic_ostream<charT, traits>&
operator<<(hamon::basic_ostream<charT, traits>& out, thread::id id);

#if 0	// TODO
template <typename charT>
struct formatter<thread::id, charT>;
#endif

#if 0	// TODO
// hash support
template <typename T>
struct hash;

template <>
struct hash<thread::id>;
#endif

}	// namespace hamon

#endif // HAMON_THREAD_THREAD_HPP
