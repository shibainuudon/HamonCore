/**
 *	@file	archive_base.hpp
 *
 *	@brief	archive_baseの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_ARCHIVE_BASE_HPP
#define HAMON_SERIALIZATION_DETAIL_ARCHIVE_BASE_HPP

#include <memory>
#include <vector>
#include <cstddef>

namespace hamon
{

namespace serialization
{

namespace detail
{

class archive_base
{
public:
	template <typename T>
	int get_shared_ptr_index(std::shared_ptr<T> const& ptr) const
	{
		for (std::size_t i = 0; i < m_list.size(); ++i)
		{
			if (m_list[i] == ptr)
			{
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	template <typename T>
	void register_shared_ptr(std::shared_ptr<T> const& ptr)
	{
		m_list.push_back(ptr);
	}

	template <typename T>
	std::shared_ptr<T> get_shared_ptr(int index)
	{
		return std::static_pointer_cast<T>(m_list[static_cast<std::size_t>(index)]);
	}

private:
	std::vector<std::shared_ptr<void>>	m_list;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_ARCHIVE_BASE_HPP
