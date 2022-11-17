﻿/**
 *	@file	flags_saver.hpp
 *
 *	@brief	flags_saver クラスの定義
 */

#ifndef HAMON_IOS_FLAGS_SAVER_HPP
#define HAMON_IOS_FLAGS_SAVER_HPP

#include <ios>

namespace hamon
{

namespace ios
{

class flags_saver
{
public:
	typedef ::std::ios_base            state_type;
	typedef ::std::ios_base::fmtflags  aspect_type;

	explicit flags_saver(state_type& s)
		: m_state(s), m_aspect(s.flags())
	{}

	flags_saver(state_type& s, aspect_type const& a)
		: m_state(s), m_aspect(s.flags(a))
	{}

	~flags_saver()
	{
		this->restore();
	}

	void restore()
	{
		m_state.flags(m_aspect);
	}

private:
	state_type&			m_state;
	aspect_type const	m_aspect;

	flags_saver& operator=(flags_saver const&) = delete;
};

}	// namespace ios

}	// namespace hamon

#endif // HAMON_IOS_FLAGS_SAVER_HPP
