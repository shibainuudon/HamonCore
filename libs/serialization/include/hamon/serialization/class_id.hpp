/**
 *	@file	class_id.hpp
 *
 *	@brief	HAMON_SERIALIZATION_CLASS_ID の定義
 */

#ifndef HAMON_SERIALIZATION_CLASS_ID_HPP
#define HAMON_SERIALIZATION_CLASS_ID_HPP

#include <hamon/serialization/access.hpp>
#include <hamon/config.hpp>

#define HAMON_SERIALIZATION_CLASS_ID(S)                                    \
	friend class hamon::serialization::access;                             \
	HAMON_WARNING_PUSH();                                                  \
	HAMON_WARNING_DISABLE_CLANG("-Winconsistent-missing-override");        \
	static const char* static_class_id() { return S; }                     \
	virtual const char* get_class_id() const { return static_class_id(); } \
	HAMON_WARNING_POP()

#endif // HAMON_SERIALIZATION_CLASS_ID_HPP
