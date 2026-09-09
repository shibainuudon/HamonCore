/**
 *	@file	cv_status.hpp
 *
 *	@brief	cv_status の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_CV_STATUS_HPP
#define HAMON_CONDITION_VARIABLE_CV_STATUS_HPP

namespace hamon
{

// 32.7.2 Header <condition_variable> synopsis[condition.variable.syn]

enum class cv_status { no_timeout, timeout };

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_CV_STATUS_HPP
