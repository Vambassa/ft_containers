#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "red_black_tree_utils.hpp"
#include "iterator.hpp"
#include "pair.hpp"

namespace ft
{
	enum OperType {Braces, Insert};

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RBTree {
	public:
		typedef T						value_type;
		typedef std::size_t				size_type;
		typedef Allocator				allocator_type;
		typedef Compare					comparator_type;
		typedef ft::RBTNode<T>			Node;

		typedef ft::RBTreeIterator<T>		iterator;
		typedef ft::RBTreeConstIterator<T>	const_iterator;

		typedef ft::RBTreeReverseIterator<T>		reverse_iterator;
		typedef ft::RBTreeConstReverseIterator<T>	const_reverse_iterator;

		typedef typename allocator_type::template rebind<Node>::other	node_allocator_type;

	private:
		Node			*_root;
		size_type		_size;
		allocator_type	_alloc;
		comparator_type	_comp;

	public:
		RBTree() : _root(NULL), _size(0), _alloc() {}

		explicit RBTree(const Compare &comp, const Allocator &alloc = Allocator()) :
				_root(NULL), _size(0), _alloc(alloc), _comp(comp) {}

		RBTree(const RBTree &other);

		~RBTree() {
			clear();
		};

		RBTree &operator=(const RBTree &other);

		allocator_type get_allocator() const { return _alloc; }

		bool empty() const { return _root == NULL; }

		size_type size() const { return _size; }

		size_type max_size() const { return (node_allocator_type().max_size()); }

		// Iterators

		iterator begin() {
			Node *min = _root;
			if (min) {
				while (min->left)
					min = min->left;
			}
			return iterator(min);
		}

		const_iterator begin() const {
			Node *min = _root;
			if (min) {
				while (min->left)
					min = min->left;
			}
			return const_iterator(min);
		}

		iterator end() { return iterator(NULL); }

		const_iterator end() const { return const_iterator(NULL); }

		reverse_iterator rbegin()
		{
			Node *max = _root;
			if (max) {
				while (max->right)
					max = max->right;
			}
			return reverse_iterator(max);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(NULL);
		}

		const_reverse_iterator rbegin() const
		{
			Node *max = _root;
			if (max) {
				while (max->right)
					max = max->right;
			}
			return const_reverse_iterator(max);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(NULL);
		}

		// Insert

		ft::pair<iterator,bool> insert(const value_type& value, OperType type);
		iterator insert(iterator, const value_type& value);

		template< class InputIt >
		void insert(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last);

		// Delete

		void 			erase(iterator pos);
		void 			erase(iterator first, iterator last);
		size_type 		erase(const value_type& key);

		// Search

		iterator		find(const value_type& key);
		const_iterator	find(const value_type& key) const;

		ft::pair<iterator,iterator> equal_range( const value_type& key );
		ft::pair<const_iterator,const_iterator> equal_range( const value_type& key ) const;

		iterator lower_bound( const value_type& key );
		const_iterator lower_bound( const value_type& key ) const;

		iterator upper_bound( const value_type& key );
		const_iterator upper_bound( const value_type& key ) const;

		void	swap(RBTree& other)
		{
			ft::swap(other._root, _root);
			ft::swap(other._size, _size);
		}

		void clear()
		{
			destroy_tree(_root);
			_root = NULL;
		}

	private:

		Node		*search(const T& key);
		Node		*search(Node *node, const T& key) const;

		void		insert_node(Node *&root, Node *node);
		void		fix_insert_tree(Node *&root, Node *node);

		void		rotate_left(Node* &root, Node* x);
		void		rotate_right(Node* &root, Node* x);

		size_type	remove_node(const T& key);
		void		remove_node(Node *&root, Node *node);
		void		fix_remove_tree(Node* &root, Node* node, Node *parent);
		void		swap_nodes(Node *n1, Node *n2);

		Node		*create_new_node(const T& value, RBTColor color = Red,
								 Node *parent = NULL, Node *left = NULL, Node *right = NULL);
		void		make_copy(Node *&cur, Node *parent, Node *child);
		void		destroy_tree(Node* &node);
		void		destroy_node(Node *node);
	};

	template <class T, class Compare, class Allocator>
	RBTree<T, Compare, Allocator>::RBTree(const RBTree& other) :
		_alloc(other._alloc), _comp(other._comp), _root(NULL)
	{
		make_copy(_root, NULL, other._root);
		_size = other._size;
	}

	template <class T, class Compare, class Allocator>
	RBTree<T, Compare, Allocator>&	RBTree<T, Compare, Allocator>::operator=(const RBTree& other)
	{
		Node	*tmp = NULL;
		make_copy(tmp, NULL, other._root);
		destroy_tree(_root);
		_root = tmp;
		_size = other._size;
		return *this;
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::Node*
		RBTree<T, Compare, Allocator>::create_new_node(const T& value, RBTColor color,
		Node *parent, Node *left, Node *right)
	{
		Node	*node = node_allocator_type().allocate(1);
		node_allocator_type().construct(node, Node(value, color, left, right, parent));
		return node;
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::make_copy(Node *&cur, Node *parent, Node *child)
	{
		if (child == NULL)
			return ;
		cur = create_new_node(child->value, Red, parent);
		make_copy(cur->left, cur, child->left);
		make_copy(cur->right, cur, child->right);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::destroy_node(Node *node)
	{
		node_allocator_type().destroy(node);
		node_allocator_type().deallocate(node, 1);
		--_size;
	}

	template <class T, class Compare, class Allocator>
	void RBTree<T, Compare, Allocator>::destroy_tree(Node* &node)
	{
		if (node == NULL)
			return;
		destroy_tree(node->left);
		destroy_tree(node->right);
		destroy_node(node);
	}

	// Insert

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::swap_nodes(Node *n1, Node *n2)
	{
		ft::swap(n1->color, n2->color);
		if (n1->left)
			n1->left->parent = n2;
		if (n2->left)
			n2->left->parent = n1;
		ft::swap(n1->left, n2->left);

		if (n1->right)
			n1->right->parent = n2;
		if (n2->right)
			n2->right->parent = n1;
		ft::swap(n1->right, n2->right);

		if (n1->parent)
		{
			if (n1->parent->left == n1)
				n1->parent->left = n2;
			else
				n1->parent->right = n2;
		}
		else
			_root = n2;
		if (n2->parent)
		{
			if (n2->parent->left == n2)
				n2->parent->left = n1;
			else
				n2->parent->right = n1;
		}
		else
			_root = n1;
		ft::swap(n1->parent, n2->parent);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::rotate_left(Node* &root, Node* x)
	{
		Node	*y = x->right;
		x->right = y->left;
		if (y->left != NULL)
			y->left->parent = x;

		y->parent = x->parent;
		if (x->parent == NULL)
			root = y;
		else {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	};

	template <class T, class Compare, class Allocator>
	void RBTree<T, Compare, Allocator>::rotate_right(Node* &root, Node* y)
	{
		Node	*x = y->left;
		y->left = x->right;
		if (x->right != NULL)
			x->right->parent = y;

		x->parent = y->parent;
		if (y->parent == NULL)
			root = x;
		else {
			if  (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	};

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::insert_node(Node *&root, Node *node)
	{
		Node	*x = root;
		Node	*y = NULL;

		while (x)
		{
			y = x;
			if (_comp(node->value, x->value))
				x = x->left;
			else
				x = x->right;
		}
		node->parent = y;
		if (y)
		{
			if (_comp(node->value, y->value))
				y->left = node;
			else
				y->right = node;
		}
		else
			root = node;
		node->color = Red;
		fix_insert_tree(root, node);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::fix_insert_tree(Node *&root, Node *node)
	{
		Node	*parent = node->parent;
		while (node != RBTree::_root  && parent->color == Red)
		{
			Node	*gparent = parent->parent;
			if (gparent->left == parent)
			{
				Node	*uncle = gparent->right;
				if (uncle != NULL && uncle->color == Red)
				{
					parent->color = Black;
					uncle->color = Black;
					gparent->color = Red;
					node = gparent;
					parent = node->parent;
				}
				else
				{
					if (parent->right == node)
					{
						rotate_left(root, parent);
						swap_nodes(node, parent);
					}
					rotate_right(root, gparent);
					gparent->color = Red;
					parent->color = Black;
					break;
				}
			}
			else
			{
				Node	*uncle = gparent->left;
				if (uncle != NULL && uncle->color == Red)
				{
					gparent->color = Red;
					parent->color = Black;
					uncle->color = Black;
					node = gparent;
					parent = node->parent;
				}
				else
				{
					if (parent->left == node)
					{
						rotate_right(root, parent);
						swap_nodes(parent, node);
					}
					rotate_left(root, gparent);
					parent->color = Black;
					gparent->color = Red;
					break;
				}
			}
		}
		root->color = Black;
	}


	// Search

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::Node*
		RBTree<T, Compare, Allocator>::search(Node *node, const T& key) const
	{
		if (node != NULL)
		{
				if (_comp(key, node->value))
					return search(node->left, key);
				else if (_comp(node->value, key))
					return search(node->right, key);
				else
					return node;
		}
		return NULL;
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::Node*
		RBTree<T, Compare, Allocator>::search(const T& key)
	{
		return search(_root, key);
	}

	// Delete

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::size_type RBTree<T, Compare, Allocator>::remove_node(const T& key)
	{
		Node	*node = search(_root, key);
		if (node != NULL)
		{
			remove_node(_root, node);
			return 1;
		}
		return 0;
	}

	template <class T, class Compare, class Allocator>
	void RBTree<T, Compare, Allocator>::remove_node(Node *&root, Node *node)
	{
		Node	*child, *parent;
		RBTColor color;
		if (node->left != NULL && node->right != NULL)
		{
			Node *replace = node;
			replace = node->right;
			while (replace->left != NULL)
				replace = replace->left;
			if (node->parent != NULL)
			{
				if (node->parent->left == node)
					node->parent->left = replace;
				else
					node->parent->right = replace;
			}
			else
				root = replace;
			child = replace->right;
			parent = replace->parent;
			color = replace->color;
			if (parent == node)
				parent = replace;
			else
			{
				if (child != NULL)
					child->parent = parent;
				parent->left = child;
				replace->right = node->right;
				node->right->parent = replace;
			}
			replace->parent = node->parent;
			replace->color = node->color;
			replace->left = node->left;
			node->left->parent = replace;
			if (color == Black)
				fix_remove_tree(_root, child, parent);
			destroy_node(node);
			return;
		}
		if (node->left != NULL)
			child = node->left;
		else
			child = node->right;
		parent = node->parent;
		color = node->color;
		if (child)
			child->parent = parent;
		if (parent)
		{
			if (node == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			RBTree::_root = child;
		if (color == Black)
			fix_remove_tree(_root, child, parent);
		destroy_node(node);
	}

	template <class T, class Compare, class Allocator>
	void RBTree<T, Compare, Allocator>::fix_remove_tree(Node* &root, Node* node, Node *parent)
	{
		Node	*othernode;
		while ((!node) || (node->color == Black && node != RBTree::_root))
		{
			if (parent->left == node)
			{
				othernode = parent->right;
				if (othernode->color == Red)
				{
					othernode->color = Black;
					parent->color = Red;
					rotate_left(root, parent);
					othernode = parent->right;
				}
				else
				{
					if (!(othernode->right) || othernode->right->color == Black)
					{
						othernode->left->color = Black;
						othernode->color = Red;
						rotate_right(root, othernode);
						othernode = parent->right;
					}
					othernode->color = parent->color;
					parent->color = Black;
					othernode->right->color = Black;
					rotate_left(root, parent);
					node = root;
					break;
				}
			}
			else
			{
				othernode = parent->left;
				if (othernode->color == Red)
				{
					othernode->color = Black;
					parent->color = Red;
					rotate_right(root, parent);
					othernode = parent->left;
				}
				if ((!othernode->left || othernode->left->color == Black)
					&& (!othernode->right || othernode->right->color == Black))
				{
					othernode->color = Red;
					node = parent;
					parent = node->parent;
				}
				else
				{
					if (!(othernode->left) || othernode->left->color == Black)
					{
						othernode->right->color = Black;
						othernode->color = Red;
						rotate_left(root, othernode);
						othernode = parent->left;
					}
					othernode->color = parent->color;
					parent->color = Black;
					othernode->left->color = Black;
					rotate_right(root, parent);
					node = root;
					break;
				}
			}
		}
		if (node)
			node->color = Black;
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::iterator RBTree<T, Compare, Allocator>::find(const T& key)
	{
		return iterator(search(_root, key));
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::const_iterator RBTree<T, Compare, Allocator>::find(const T& key) const
	{
		return const_iterator(search(_root, key));
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::iterator RBTree<T, Compare, Allocator>::insert(
			typename RBTree<T, Compare, Allocator>::iterator, const T& value)
	{
		Node *node = create_new_node(value);
		if (search(value) != NULL)
		{
			destroy_node(node);
			return iterator(node);
		}
		insert_node(_root, node);
		++_size;
		return iterator(node);
	}

	template <class T, class Compare, class Allocator>
	ft::pair<typename RBTree<T, Compare, Allocator>::iterator, bool>
	RBTree<T, Compare, Allocator>::insert(const T& value, OperType type)
	{
		Node *node = create_new_node(value);
		if (search(value) != NULL)
		{
			if (type == Insert)
			{
				destroy_node(node);
				++_size;
				return (ft::make_pair(iterator(_root), false));
			}
			else if (type == Braces)
				erase(value);
		}
		insert_node(_root, node);
		++_size;
		return ft::make_pair(iterator(node), true);
	}

	template <class T, class Compare, class Allocator>
	template< class InputIt >
	void	RBTree<T, Compare, Allocator>::insert(typename ft::enable_if<!ft::is_integral<InputIt>::value,
												  InputIt>::type first, InputIt last)
	{
		for (; first != last; ++first)
			insert(*first, Insert);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::erase(typename RBTree<T, Compare, Allocator>::iterator pos)
	{
		remove_node(*pos);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::erase(iterator first, iterator last)
	{
		for (; first != last; first++)
			remove_node(*first);
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::size_type	RBTree<T, Compare, Allocator>::erase(const value_type& key)
	{
		return (remove_node(key));
	}

	template <class T, class Compare, class Allocator>
	ft::pair<typename RBTree<T, Compare, Allocator>::iterator,
		typename RBTree<T, Compare, Allocator>::iterator>
		RBTree<T, Compare, Allocator>::equal_range(const T& key)
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	template <class T, class Compare, class Allocator>
	ft::pair<typename RBTree<T, Compare, Allocator>::const_iterator,
		typename RBTree<T, Compare, Allocator>::const_iterator>
		RBTree<T, Compare, Allocator>::equal_range(const T& key) const
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::iterator
	        RBTree<T, Compare, Allocator>::lower_bound(const T& key)
	{
		Node *node = _root;
		Node *res = NULL;

		while (node)
		{
			if (_comp(key, node->value))
			{
				res = node;
				node = node->left;
			}
			else if (not _comp(node->value, key))
			{
				res = node;
				node = node->left;
			}
			else
				node = node->right;
		}
		return iterator(res);
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::const_iterator
	        RBTree<T, Compare, Allocator>::lower_bound(const T& key) const
	{
		Node *node = _root;
		Node *res = NULL;

		while (node)
		{
			if (_comp(key, node->value))
			{
				res = node;
				node = node->left;
			}
			else if (not _comp(node->value, key))
			{
				res = node;
				node = node->left;
			}
			else
				node = node->right;
		}
		return const_iterator(res);
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::iterator
	        RBTree<T, Compare, Allocator>::upper_bound(const T& key)
	{
		Node *node = _root;
		Node *res = NULL;

		while (node)
		{
			if (_comp(key, node->value))
			{
				res = node;
				node = node->left;
			}
			else
				node = node->right;
		}
		return iterator(res);
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::const_iterator
	        RBTree<T, Compare, Allocator>::upper_bound(const T& key)  const
	{
		Node *node = _root;
		Node *res = NULL;

		while (node)
		{
			if (_comp(key, node->value))
			{
				res = node;
				node = node->left;
			}
			else
				node = node->right;
		}
		return const_iterator(res);
	}
}

#endif
