/**
 *	@file	scoped_lock.hpp
 *
 *	@brief	scoped_lock の定義
 */

#ifndef HAMON_MUTEX_SCOPED_LOCK_HPP
#define HAMON_MUTEX_SCOPED_LOCK_HPP

#include <mutex>

#if defined(__cpp_lib_scoped_lock) && (__cpp_lib_scoped_lock >= 201703L)

namespace hamon
{

using std::scoped_lock;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/tuple.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.6.5.3 Class template scoped_lock[thread.lock.scoped]

template <typename... MutexTypes>
class scoped_lock;

template <>
class scoped_lock<>
{
public:
	explicit scoped_lock() {}
	explicit scoped_lock(std::adopt_lock_t) {}
	~scoped_lock() {}

	scoped_lock(scoped_lock const&) = delete;
	scoped_lock& operator=(scoped_lock const&) = delete;
};

template <typename MutexType>
class scoped_lock<MutexType>
{
public:
	// [thread.lock.scoped]/1.1
	using mutex_type = MutexType;     // Only if sizeof...(MutexTypes) == 1 is true

	explicit scoped_lock(MutexType& m)
		: pm(m)
	{
		pm.lock();
	}

	explicit scoped_lock(std::adopt_lock_t, MutexType& m)
		: pm(m)
	{}

	~scoped_lock()
	{
		pm.unlock();
	}

	scoped_lock(scoped_lock const&) = delete;
	scoped_lock& operator=(scoped_lock const&) = delete;

private:
	MutexType& pm;
};


template <typename... MutexTypes>
class scoped_lock
{
public:
	explicit scoped_lock(MutexTypes&... m)
		: pm(m...)
	{
		std::lock(m...);
	}

	explicit scoped_lock(std::adopt_lock_t, MutexTypes&... m)
		: pm(m...)
	{
	}

	~scoped_lock()
	{
		unlock_all(hamon::make_index_sequence<sizeof...(MutexTypes)>{});
	}

	scoped_lock(scoped_lock const&) = delete;
	scoped_lock& operator=(scoped_lock const&) = delete;

private:
	template <typename... Types>
	HAMON_CXX14_CONSTEXPR void swallow(Types...) HAMON_NOEXCEPT {}

	template <hamon::size_t... Is>
	void unlock_all(hamon::index_sequence<Is...>)
	{
		swallow((hamon::get<Is>(pm).unlock(), 0)...);
	}

private:
	hamon::tuple<MutexTypes&...> pm;   // exposition only
};

}	// namespace hamon

#endif

#endif // HAMON_MUTEX_SCOPED_LOCK_HPP
