/**
 *	@file	disabled_hash.hpp
 *
 *	@brief	disabled_hash クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_DISABLED_HASH_HPP
#define HAMON_FUNCTIONAL_DETAIL_DISABLED_HASH_HPP

namespace hamon
{
namespace detail
{

struct disabled_hash
{
	disabled_hash()                                = delete;
	disabled_hash(disabled_hash const&)            = delete;
	disabled_hash(disabled_hash&&)                 = delete;
	disabled_hash& operator=(disabled_hash const&) = delete;
	disabled_hash& operator=(disabled_hash&&)      = delete;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_DISABLED_HASH_HPP
