/**
 *	@file	red_black_tree.hpp
 *
 *	@brief	red_black_tree の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_HPP
#define HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_HPP

#include <hamon/container/detail/red_black_tree_node.hpp>
#include <hamon/container/detail/red_black_tree_iterator.hpp>

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/prev.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <bool Multi,
	typename KeyType,
	typename ValueType = KeyType,
	typename Compare = hamon::less<>,
	typename SizeType = hamon::size_t,
	typename DifferenceType = hamon::ptrdiff_t>
struct red_black_tree
{
private:
	using Node = red_black_tree_node<ValueType>;
	using Algo = red_black_tree_algo<Node>;

public:
	using value_type      = ValueType;
	using key_type        = KeyType;
	using size_type       = SizeType;
	using difference_type = DifferenceType;
	using node_type       = Node;
	using iterator        = hamon::detail::red_black_tree_iterator<red_black_tree, false>;
	using const_iterator  = hamon::detail::red_black_tree_iterator<red_black_tree, true>;

private:
	HAMON_NO_UNIQUE_ADDRESS Compare m_comp;
	Node* m_root{};
	Node* m_leftmost{};
	Node* m_rightmost{};
	size_type m_size{};

public:
	red_black_tree() = default;

	explicit HAMON_CXX14_CONSTEXPR
	red_black_tree(Compare const& comp)
		: m_comp(comp)
	{}

	red_black_tree(red_black_tree const&) = delete;

	HAMON_CXX14_CONSTEXPR
	red_black_tree(red_black_tree&& x) HAMON_NOEXCEPT
		: m_comp(hamon::move(x.m_comp))
		, m_root(hamon::exchange(x.m_root, nullptr))
		, m_leftmost(hamon::exchange(x.m_leftmost, nullptr))
		, m_rightmost(hamon::exchange(x.m_rightmost, nullptr))
		, m_size(hamon::exchange(x.m_size, size_type{}))
	{}

	red_black_tree& operator=(red_black_tree const&) = delete;

	HAMON_CXX14_CONSTEXPR
	red_black_tree& operator=(red_black_tree&& x) HAMON_NOEXCEPT
	{
		red_black_tree(hamon::move(x)).swap(*this);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(red_black_tree& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_comp,      x.m_comp);
		hamon::swap(m_root,      x.m_root);
		hamon::swap(m_leftmost,  x.m_leftmost);
		hamon::swap(m_rightmost, x.m_rightmost);
		hamon::swap(m_size,      x.m_size);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Compare const&
	comp() const noexcept
	{
		return m_comp;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Node*
	root() const noexcept
	{
		return m_root;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Node*
	leftmost() const noexcept
	{
		return m_leftmost;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Node*
	rightmost() const noexcept
	{
		return m_rightmost;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size() const noexcept
	{
		return m_size;
	}

private:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator to_iterator(Node* p) const noexcept
	{
		return iterator{this, p};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator to_const_iterator(Node* p) const noexcept
	{
		return const_iterator{this, p};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator begin() const noexcept
	{
		return to_iterator(m_leftmost);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator cbegin() const noexcept
	{
		return to_const_iterator(m_leftmost);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	iterator end() const noexcept
	{
		return to_iterator(nullptr);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	const_iterator cend() const noexcept
	{
		return to_const_iterator(nullptr);
	}

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	find(K const& x) const
	{
		auto r = this->lower_bound(x);
		if (r != this->end() && !m_comp(x, *r))
		{
			return r;
		}
		return this->end();
	}

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR size_type
	count(K const& x) const
	{
		if (Multi)
		{
			auto r = this->equal_range(x);
			return static_cast<size_type>(
				hamon::ranges::distance(r.first, r.second));
		}
		else
		{
			return this->contains(x) ? 1 : 0;
		}
	}

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
	contains(K const& x) const
	{
		return this->find(x) != this->end();
	}

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	lower_bound(K const& x) const
	{
		if (m_root == nullptr)
		{
			return this->end();
		}

		auto r = Algo::lower_bound(m_root, x, m_comp);
		if (r.second == Algo::ChildDir::Right)
		{
			return to_iterator(Algo::next(r.first));
		}
		return to_iterator(r.first);
	}

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	upper_bound(K const& x) const
	{
		if (m_root == nullptr)
		{
			return this->end();
		}

		auto r = Algo::upper_bound(m_root, x, m_comp);
		if (r.second == Algo::ChildDir::Right)
		{
			return to_iterator(Algo::next(r.first));
		}
		return to_iterator(r.first);
	}

	template <typename K>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR
	pair<iterator, iterator>
	equal_range(K const& x) const
	{
		// TODO unique な場合はもっと効率的に実装できる
		return
		{
			this->lower_bound(x),
			this->upper_bound(x)
		};
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

private:
	template <typename Allocator, typename... Args>
	static HAMON_CXX14_CONSTEXPR Node*
	construct_node(Allocator& alloc, Args&&... args)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		auto node = AllocTraits::allocate(alloc, 1);	// may throw
		AllocTraits::construct(alloc, node, hamon::forward<Args>(args)...);	// may throw
		return node;
	}

	template <typename Allocator>
	static HAMON_CXX14_CONSTEXPR void
	destruct_node(Allocator& alloc, Node* p)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		AllocTraits::destroy(alloc, p);
		AllocTraits::deallocate(alloc, p, 1);
	}

public:
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert_node(Node* node)
	{
		if (node == nullptr)
		{
			return {this->end(), false};
		}

		if (m_root == nullptr)
		{
			m_root = node;
			m_leftmost = node;
			m_rightmost = node;
			m_size = 1;
			return {to_iterator(node), true};
		}

		auto r = Algo::find_to_insert(m_comp, node->value(), m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			Algo::insert_at(r.first, r.second, node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert_node_hint(const_iterator hint, Node* node)
	{
		if (node == nullptr)
		{
			return {this->end(), false};
		}

		if (m_root == nullptr)
		{
			m_root = node;
			m_leftmost = node;
			m_rightmost = node;
			m_size = 1;
			return {to_iterator(node), true};
		}

		auto r = Algo::find_to_insert_hint(m_comp, node->value(), m_root, Multi, hint, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			Algo::insert_at(r.first, r.second, node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Allocator, typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace(Allocator& alloc, K const& k, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return {to_iterator(new_node), true};
		}

		auto r = Algo::find_to_insert(m_comp, k, m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Allocator, typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace_hint(Allocator& alloc, const_iterator hint, K const& k, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return {to_iterator(new_node), true};
		}

		auto r = Algo::find_to_insert_hint(m_comp, k, m_root, Multi, hint, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

private:
	template <typename Allocator, typename Arg0, typename... Args,
		typename = hamon::enable_if_t<
			hamon::disjunction<
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<value_type>>,
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<key_type>>
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_impl(hamon::detail::overload_priority<1>,
		Allocator& alloc, Arg0&& arg0, Args&&... args)
	{
		auto r = Algo::find_to_insert(m_comp, hamon::forward<Arg0>(arg0), m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = construct_node(alloc, hamon::forward<Arg0>(arg0), hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_impl(hamon::detail::overload_priority<0>,
		Allocator& alloc, Args&&... args)
	{
		auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
		auto r = Algo::find_to_insert(m_comp, new_node->value(), m_root, Multi);
		if (r.second != Algo::ChildDir::None)
		{
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			destruct_node(alloc, new_node);
			return {to_iterator(r.first), false};
		}
	}

	template <typename Allocator, typename Arg0, typename... Args,
		typename = hamon::enable_if_t<
			hamon::disjunction<
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<value_type>>,
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<key_type>>
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_hint_impl(hamon::detail::overload_priority<1>,
		Allocator& alloc, const_iterator position, Arg0&& arg0, Args&&... args)
	{
		auto r = Algo::find_to_insert_hint(m_comp, hamon::forward<Arg0>(arg0), m_root, Multi, position, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			auto new_node = construct_node(alloc, hamon::forward<Arg0>(arg0), hamon::forward<Args>(args)...);	// may throw
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			return {to_iterator(r.first), false};
		}
	}

	template <typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_hint_impl(hamon::detail::overload_priority<0>,
		Allocator& alloc, const_iterator position, Args&&... args)
	{
		auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
		auto r = Algo::find_to_insert_hint(m_comp, new_node->value(), m_root, Multi, position, this->cbegin(), this->cend());
		if (r.second != Algo::ChildDir::None)
		{
			Algo::insert_at(r.first, r.second, new_node, m_root, m_leftmost, m_rightmost);
			++m_size;
			return {to_iterator(new_node), true};
		}
		else
		{
			destruct_node(alloc, new_node);
			return {to_iterator(r.first), false};
		}
	}

public:
	template <typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace(Allocator& alloc, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return {to_iterator(new_node), true};
		}

		return emplace_impl(hamon::detail::overload_priority<1>{},
			alloc, hamon::forward<Args>(args)...);
	}

	template <typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(Allocator& alloc, const_iterator position, Args&&... args)
	{
		if (m_root == nullptr)
		{
			auto new_node = construct_node(alloc, hamon::forward<Args>(args)...);	// may throw
			m_root = new_node;
			m_leftmost = new_node;
			m_rightmost = new_node;
			m_size = 1;
			return to_iterator(new_node);
		}

		return emplace_hint_impl(hamon::detail::overload_priority<1>{},
			alloc, position, hamon::forward<Args>(args)...).first;
	}

HAMON_WARNING_POP()

	template <typename Allocator, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	insert_range(Allocator& alloc, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->emplace(alloc, *first);
		}
	}

	HAMON_CXX14_CONSTEXPR Node*
	extract(const_iterator position)
	{
		auto z = const_cast<Node*>(position.node());

		Algo::erase(z, m_root);
		--m_size;
		if (m_size == 0)
		{
			m_root = nullptr;
			m_leftmost = nullptr;
			m_rightmost = nullptr;
		}
		else
		{
			m_leftmost = m_root->leftmost();
			m_rightmost = m_root->rightmost();
		}
		return z;
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR iterator
	erase(Allocator& alloc, const_iterator position)
	{
		auto z = const_cast<Node*>(position.node());
		auto ret = z->next();

		Algo::erase(z, m_root);
		destruct_node(alloc, z);

		--m_size;
		if (m_size == 0)
		{
			m_root = nullptr;
			m_leftmost = nullptr;
			m_rightmost = nullptr;
		}
		else
		{
			m_leftmost = m_root->leftmost();
			m_rightmost = m_root->rightmost();
		}

		return to_iterator(ret);
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR iterator
	erase(Allocator& alloc, const_iterator first, const_iterator last)
	{
		for (; first != last; )
		{
			first = this->erase(alloc, first);
		}
		return to_iterator(const_cast<Node*>(last.node()));
	}

private:
	template <typename Allocator>
	static HAMON_CXX14_CONSTEXPR void
	clear_impl(Allocator& alloc, Node* p) noexcept
	{
		if (p == nullptr)
		{
			return;
		}

		clear_impl(alloc, p->m_left);
		clear_impl(alloc, p->m_right);
		destruct_node(alloc, p);
	}

public:
	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void clear(Allocator& alloc)
	{
		clear_impl(alloc, m_root);
		m_root = nullptr;
		m_leftmost = nullptr;
		m_rightmost = nullptr;
		m_size = 0;
	}

	template <typename Tree>
	HAMON_CXX14_CONSTEXPR void
	merge(Tree& tree)
	{
		for (auto it = tree.begin(); it != tree.end(); )
		{
			auto next = hamon::next(it);
			auto node = tree.extract(it);
			auto r = this->insert_node(node);
			if (!r.second)
			{
				tree.insert_node_hint(next, node);
			}
			it = next;
		}
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void copy_from(Allocator& alloc, red_black_tree const& tree)
	{
		this->m_comp = tree.m_comp;
		this->insert_range(alloc, tree.begin(), tree.end());
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void move_from(Allocator& alloc, red_black_tree const& tree)
	{
		this->m_comp = hamon::move(tree.m_comp);
		this->insert_range(alloc, hamon::make_move_iterator(tree.begin()), hamon::make_move_iterator(tree.end()));
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RED_BLACK_TREE_HPP
