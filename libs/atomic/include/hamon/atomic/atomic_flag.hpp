/**
 *	@file	atomic_flag.hpp
 *
 *	@brief	atomic_flag の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_FLAG_HPP
#define HAMON_ATOMIC_ATOMIC_FLAG_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_test_and_set.hpp>
#include <hamon/atomic/detail/atomic_clear.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

// 32.5.10 Flag type and operations[atomics.flag]

struct atomic_flag
{
	constexpr atomic_flag() noexcept
		// [atomics.flag]/4
		: m_value()
	{}

	atomic_flag(atomic_flag const&) = delete;
	atomic_flag& operator=(atomic_flag const&) = delete;
	atomic_flag& operator=(atomic_flag const&) volatile = delete;

	bool test(memory_order order = memory_order::seq_cst) const volatile noexcept
	{
		// [atomics.flag]/6
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.flag]/7,8
		return hamon::detail::atomic_load(data(), order);
	}

	constexpr bool test(memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.flag]/6
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.flag]/7,8
		return hamon::detail::atomic_load(data(), order);
	}

	bool test_and_set(memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.flag]/9,10
		return hamon::detail::atomic_test_and_set(data(), order);
	}

	constexpr bool test_and_set(memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.flag]/9,10
		return hamon::detail::atomic_test_and_set(data(), order);
	}

	void clear(memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.flag]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.flag]/12
		return hamon::detail::atomic_clear(data(), order);
	}

	constexpr void clear(memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.flag]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.flag]/12
		return hamon::detail::atomic_clear(data(), order);
	}

	void wait(bool old, memory_order order = memory_order::seq_cst) const volatile noexcept;
	constexpr void wait(bool old, memory_order order = memory_order::seq_cst) const noexcept;
	void notify_one() volatile noexcept;
	constexpr void notify_one() noexcept;
	void notify_all() volatile noexcept;
	constexpr void notify_all() noexcept;

private:
	using value_type = bool;

	constexpr value_type* data() noexcept
	{
		return const_cast<value_type*>(hamon::addressof(m_value));
	}

	constexpr value_type* data() const noexcept
	{
		return const_cast<value_type*>(hamon::addressof(m_value));
	}

	constexpr value_type* data() volatile noexcept
	{
		return const_cast<value_type*>(hamon::addressof(m_value));
	}

	constexpr value_type* data() const volatile noexcept
	{
		return const_cast<value_type*>(hamon::addressof(m_value));
	}

	value_type m_value;
};

inline bool atomic_flag_test(atomic_flag const volatile* object) noexcept
{
	return object->test();
}

inline constexpr bool atomic_flag_test(atomic_flag const* object) noexcept
{
	return object->test();
}

inline bool atomic_flag_test_explicit(atomic_flag const volatile* object, memory_order order) noexcept
{
	return object->test(order);
}

inline constexpr bool atomic_flag_test_explicit(atomic_flag const* object, memory_order order) noexcept
{
	return object->test(order);
}

inline bool atomic_flag_test_and_set(atomic_flag volatile* object) noexcept
{
	return object->test_and_set();
}

inline constexpr bool atomic_flag_test_and_set(atomic_flag* object) noexcept
{
	return object->test_and_set();
}

inline bool atomic_flag_test_and_set_explicit(atomic_flag volatile* object, memory_order order) noexcept
{
	return object->test_and_set(order);
}

inline constexpr bool atomic_flag_test_and_set_explicit(atomic_flag* object, memory_order order) noexcept
{
	return object->test_and_set(order);
}

inline void atomic_flag_clear(atomic_flag volatile* object) noexcept
{
	object->clear();
}

inline constexpr void atomic_flag_clear(atomic_flag* object) noexcept
{
	object->clear();
}

inline void atomic_flag_clear_explicit(atomic_flag volatile* object, memory_order order) noexcept
{
	object->clear(order);
}

inline constexpr void atomic_flag_clear_explicit(atomic_flag* object, memory_order order) noexcept
{
	object->clear(order);
}

void atomic_flag_wait(atomic_flag const volatile* object, bool old) noexcept;
constexpr void atomic_flag_wait(atomic_flag const* object, bool old) noexcept;
void atomic_flag_wait_explicit(atomic_flag const volatile* object, bool old, memory_order order) noexcept;
constexpr void atomic_flag_wait_explicit(atomic_flag const* object, bool old, memory_order order) noexcept;
void atomic_flag_notify_one(atomic_flag volatile* object) noexcept;
constexpr void atomic_flag_notify_one(atomic_flag* object) noexcept;
void atomic_flag_notify_all(atomic_flag volatile* object) noexcept;
constexpr void atomic_flag_notify_all(atomic_flag* object) noexcept;

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_FLAG_HPP
