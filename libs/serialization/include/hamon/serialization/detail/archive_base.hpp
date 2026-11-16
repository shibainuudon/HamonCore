/**
 *	@file	archive_base.hpp
 *
 *	@brief	archive_baseの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_ARCHIVE_BASE_HPP
#define HAMON_SERIALIZATION_DETAIL_ARCHIVE_BASE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <memory>
#endif

namespace hamon
{

namespace serialization
{

namespace detail
{

template <template <typename...> class SharedPtr>
struct shared_ptr_list
{
public:
	template <typename T>
	int get_shared_ptr_index(SharedPtr<T> const& sp) const
	{
		for (hamon::size_t i = 0; i < m_list.size(); ++i)
		{
			if (m_list[i] == sp)
			{
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	template <typename T>
	void register_shared_ptr(SharedPtr<T> const& sp)
	{
		m_list.push_back(sp);
	}

	template <typename T>
	void get_shared_ptr(SharedPtr<T>& sp, int index)
	{
		auto vp = m_list[static_cast<hamon::size_t>(index)];
		sp = SharedPtr<T>(vp, static_cast<T*>(vp.get()));
	}

private:
	hamon::vector<SharedPtr<void>>	m_list;
};

class archive_base
{
public:
	template <typename T>
	int get_shared_ptr_index(hamon::shared_ptr<T> const& sp) const
	{
		return m_shared_ptr_list.get_shared_ptr_index(sp);
	}

	template <typename T>
	void register_shared_ptr(hamon::shared_ptr<T> const& sp)
	{
		m_shared_ptr_list.register_shared_ptr(sp);
	}

	template <typename T>
	void get_shared_ptr(hamon::shared_ptr<T>& sp, int index)
	{
		m_shared_ptr_list.get_shared_ptr(sp, index);
	}

private:
	shared_ptr_list<hamon::shared_ptr> m_shared_ptr_list;

#if !defined(HAMON_NO_STD)
public:
	template <typename T>
	int get_shared_ptr_index(std::shared_ptr<T> const& sp) const
	{
		return m_std_shared_ptr_list.get_shared_ptr_index(sp);
	}

	template <typename T>
	void register_shared_ptr(std::shared_ptr<T> const& sp)
	{
		m_std_shared_ptr_list.register_shared_ptr(sp);
	}

	template <typename T>
	void get_shared_ptr(std::shared_ptr<T>& sp, int index)
	{
		m_std_shared_ptr_list.get_shared_ptr(sp, index);
	}

private:
	shared_ptr_list<std::shared_ptr> m_std_shared_ptr_list;
#endif
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_ARCHIVE_BASE_HPP
