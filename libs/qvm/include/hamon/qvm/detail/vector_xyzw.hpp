/**
 *	@file	vector_xyzw.hpp
 *
 *	@brief	vector_xyzw の定義
 */

#ifndef HAMON_QVM_DETAIL_VECTOR_XYZW_HPP
#define HAMON_QVM_DETAIL_VECTOR_XYZW_HPP

#include <hamon/qvm/detail/vector_base.hpp>
#include <hamon/qvm/detail/swizzle_operator.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T, std::size_t N>
class vector_xyzw : public vector_base<T, N>
{
private:
	using base_type = vector_base<T, N>;
public:
	using base_type::base_type;
};

template <typename T>
class vector_xyzw<T, 2> : public vector_base<T, 2>
{
private:
	using base_type = vector_base<T, 2>;
public:
	using base_type::base_type;

	HAMON_QVM_NAMED_ACCESS(x, 0);
	HAMON_QVM_NAMED_ACCESS(y, 1);
	HAMON_QVM_SWIZZLE_OPERATOR((x)(y));
};

template <typename T>
class vector_xyzw<T, 3> : public vector_base<T, 3>
{
private:
	using base_type = vector_base<T, 3>;
public:
	using base_type::base_type;

	HAMON_QVM_NAMED_ACCESS(x, 0);
	HAMON_QVM_NAMED_ACCESS(y, 1);
	HAMON_QVM_NAMED_ACCESS(z, 2);
	HAMON_QVM_SWIZZLE_OPERATOR((x)(y)(z));
};

template <typename T>
class vector_xyzw<T, 4> : public vector_base<T, 4>
{
private:
	using base_type = vector_base<T, 4>;
public:
	using base_type::base_type;

	HAMON_QVM_NAMED_ACCESS(x, 0);
	HAMON_QVM_NAMED_ACCESS(y, 1);
	HAMON_QVM_NAMED_ACCESS(z, 2);
	HAMON_QVM_NAMED_ACCESS(w, 3);
	HAMON_QVM_SWIZZLE_OPERATOR((x)(y)(z)(w));
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_VECTOR_XYZW_HPP
