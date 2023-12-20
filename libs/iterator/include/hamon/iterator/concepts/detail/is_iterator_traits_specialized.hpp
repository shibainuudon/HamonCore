/**
 *	@file	is_iterator_traits_specialized.hpp
 *
 *	@brief	is_iterator_traits_specialized の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP

namespace hamon
{

namespace detail
{

/**
 *	@brief	iterator_traitsを特殊化したかどうかのフラグ
 * 
 *	iterator concept の取得の際、iterator_traitsを特殊化しているかどうかで結果が変わる。
 *	つまり、iterator_traits<T> が primary template かどうかが重要なのだが、
 *	コンパイラマジックを使わない限り、primary template かどうかを取得することはできない。
 *	そこで、iterator_traitsを特殊化したかどうかを表すクラステンプレートを作成した。
 *	独自のイテレータを作成してiterator_traitsを特殊化する際は、
 *	is_iterator_traits_specializedクラステンプレートも特殊化して、value = true; に設定する。
 */
template <typename Iter>
struct is_iterator_traits_specialized
{
	static const bool value = false;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_IS_ITERATOR_TRAITS_SPECIALIZED_HPP
