#ifndef tree_iterator_HPP 
# define tree_iterator_HPP
# include "utils.hpp"

namespace ft
{
	template <typename T, class Compare>
	class	tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:
		typedef typename	T::value_type	value_type;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer			pointer;
		typedef typename	ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;

		tree_iterator(Compare const &comp = Compare()) : _node(), _last_node(), _comp(comp)
		{}

		tree_iterator(T *node, T *last_node, Compare const &comp = Compare()) : _node(node), _last_node(last_node), _comp(comp)
		{}

		tree_iterator(tree_iterator const &other) : _node(other._node), _last_node(other._last_node), _comp(other._comp)
		{}

		virtual ~tree_iterator() {}

		tree_iterator	&operator=(tree_iterator const &ti)
		{
			if (*this == ti)
				return (*this);
			_node = ti._node;
			_last_node = ti._last_node;
			_comp = ti._comp;
			return *this;
		}

		bool	operator==(tree_iterator const &ti)
		{
			return _node == ti._node;
		}

		bool	operator!=(tree_iterator const &ti)
		{
			return _node != ti._node;
		}

		reference	operator*() const
		{
			return _node->value;
		}

		pointer	operator->() const
		{
			return &(_node->value);
		}

		tree_iterator	&operator++(void)
		{
			T	*current = _node;

			if (_node->right == _last_node)
			{
				current = _node->parent;
				while (current != _last_node && _comp(current->value.first, _node->value.first))
					current = current->parent;
				_node = current;
			}
			else if (current == _last_node)
				_node = _last_node->right;
			else
			{
				current = _node->right;
				if (current == _last_node->parent && current->right == _last_node)
					_node = current;
				else
				{
					while (current->left != _last_node)
						current = current->left;
				}
				_node = current;
			}
			return *this;
		}

		tree_iterator	operator++(int)
		{
			tree_iterator	tmp(*this);
			operator++();
			return (tmp);
		}

		tree_iterator	&operator--(void)
		{
			T* current = _node;

			if (_node->left == _last_node)
			{
				current = _node->parent;
				while (current != _last_node
					&& !_comp(current->value.first, _node->value.first))
					current = current->parent;
				_node = current;
			}
			else if (current == _last_node)
				_node = _last_node->right;
			else
			{
				current = _node->left;
				if (current == _last_node->parent
					&& current->left == _last_node)
					_node = current;
				else
				{
					while (current->right != _last_node)
						current = current->right;
				}
				_node = current;
			}
			return (*this);
		}

		tree_iterator	operator--(int)
		{
			tree_iterator tmp(*this);
			operator--();
			return tmp;
		}

		operator tree_iterator<const T, Compare>() const
		{
			return tree_iterator<const T, Compare>(_node, _last_node, _comp);
		}

	// private:
		T	*_node;
		T	*_last_node;
		Compare	_comp;
	};


	// template <typename T, class Compare >
	// class BST_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	// {
	// 	public :

	// 		typedef typename T::value_type    value_type;

	// 		/* The iterator category */
	// 		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;

	// 		/* The value_type pointed by the iterator (BST)*/

	// 		/* The difference type */
	// 		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;

	// 		/* The pointer to the value */
	// 		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;

	// 		/* The reference to the value */
	// 		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			
	// 		/*
	// 		** @brief Default.
	// 		** Create an iterator that pointing to inisialized 
	// 		** binary search tree.
	// 		*/
	// 		BST_const_iterator(const Compare& comp = Compare())
	// 		:
	// 			_node(),
	// 			_last_node(),
	// 			_comp(comp)
	// 		{}

	// 		/*
	// 		** @brief Create an iterator on "node_p".
	// 		*/
	// 		BST_const_iterator(T * node_p, T * last_node,
	// 					const Compare& comp = Compare())
	// 		:
	// 			_node(node_p),
	// 			_last_node(last_node),
	// 			_comp(comp)
	// 		{}

	// 		/*
	// 		** @brief Copy constructor.
	// 		** Create a new Binary search tree iterator to be 
	// 		** a copy of another.
	// 		**
	// 		** @param bst_it the binary search tree to be inpired by.
	// 		*/
	// 		BST_const_iterator(const BST_const_iterator& bst_it)
	// 		:
	// 			_node(bst_it._node),
	// 			_last_node(bst_it._last_node),
	// 			_comp()
	// 		{}

	// 		BST_const_iterator(const tree_iterator<T, Compare>& bst_it)
	// 		:
	// 			_node(bst_it._node),
	// 			_last_node(bst_it._last_node),
	// 			_comp()
	// 		{}

	// 		// Added for subject
	// 		virtual ~BST_const_iterator() { }

	// 		/*
	// 		** @brief Assignement operator.
	// 		** Create an iterator that will iterate the same than
	// 		** "bst_it".
	// 		**
	// 		** @param bst_it the binary search tree to be inpired by.
	// 		** @return a reference to this.
	// 		*/
	// 		BST_const_iterator &operator=(const BST_const_iterator& bst_it)
	// 		{
	// 			if (*this == bst_it)
	// 				return (*this);
	// 			this->_node = bst_it._node;
	// 			this->_last_node = bst_it._last_node;
	// 			this->_comp = bst_it._comp;
	// 			return (*this);
	// 		}
			
	// 		/*
	// 		** @brief Strictment equal operator.
	// 		** Return a boolean that contains : if this iterator
	// 		** and another one contains two equal binary search tree.
	// 		**
	// 		** @param bst_it the other binaray search tree iterator.
	// 		** @return true if the two iterator iterate on two equal
	// 		** tree, otherwise false.
	// 		*/
	// 		bool operator==(const BST_const_iterator& bst_it)
	// 		{ return (this->_node == bst_it._node); }

	// 		/*
	// 		** @brief Different operator.
	// 		** Return a boolean that contains : if this iterator
	// 		** and another one contains two different binary search tree.
	// 		**
	// 		** @param bst_it the other binaray search tree iterator.
	// 		** @return true if the two iterator iterate on two different
	// 		** tree, otherwise false.
	// 		*/
	// 		bool operator!=(const BST_const_iterator& bst_it)
	// 		{ return (this->_node != bst_it._node); }

	// 		/*
	// 		** @brief Give a reference to the value that contains
	// 		** the binary search tree (value on a node) at the iterator
	// 		** position.
	// 		**
	// 		** @return the const reference.
	// 		*/
	// 		reference operator*() const
	// 		{ return (this->_node->value); }

	// 		/*
	// 		** @brief Give a pointer to the value that contain
	// 		** the binary search tree (value on a node) at the iterator
	// 		** position.
	// 		**
	// 		** @return the const pointer.
	// 		*/
	// 		pointer operator->() const
	// 		{ return (&this->_node->value); }

	// 		/*
	// 		** @brief Increment the iterator to the next value
	// 		** after the value in the tree at iterator position.
	// 		**
	// 		** @return a reference to this.
	// 		*/
	// 		BST_const_iterator& operator++(void)
	// 		{
	// 			T * cursor = _node;

	// 			if (_node->right == _last_node)
	// 			{
	// 				cursor = _node->parent;
	// 				while (cursor != _last_node
	// 					&& _comp(cursor->value.first, _node->value.first))
	// 					cursor = cursor->parent;
	// 				_node = cursor;
	// 			}
	// 			else if (cursor == _last_node)
	// 				_node = _last_node->right;
	// 			else
	// 			{
	// 				cursor = _node->right;
	// 				if (cursor == _last_node->parent
	// 					&& cursor->right == _last_node)
	// 					_node = cursor;
	// 				else
	// 				{
	// 					while (cursor->left != _last_node)
	// 						cursor = cursor->left;
	// 				}
	// 				_node = cursor;
	// 			}
	// 			return (*this);
	// 		}

	// 		/*
	// 		** @brief Post increment the iterator to the next value
	// 		** after the value in the tree at iterator position.
	// 		**
	// 		** @return this before the incrementation.
	// 		*/
	// 		BST_const_iterator operator++(int)
	// 		{
	// 			BST_const_iterator tmp(*this);
	// 			operator++();
	// 			return (tmp);
	// 		}

	// 		/*
	// 		** @brief decrement the iterator to the previous value
	// 		** before the value in the tree at iterator position.
	// 		**
	// 		** @return a reference to this.
	// 		*/
	// 		BST_const_iterator& operator--(void)
	// 		{
	// 			T * cursor = _node;

	// 			if (_node->left == _last_node)
	// 			{
	// 				cursor = _node->parent;
	// 				while (cursor != _last_node
	// 					&& !_comp(cursor->value.first, _node->value.first))
	// 					cursor = cursor->parent;
	// 				_node = cursor;
	// 			}
	// 			else if (cursor == _last_node)
	// 				_node = _last_node->right;
	// 			else
	// 			{
	// 				cursor = _node->left;
	// 				if (cursor == _last_node->parent
	// 					&& cursor->left == _last_node)
	// 					_node = cursor;
	// 				else
	// 				{
	// 					while (cursor->right != _last_node)
	// 						cursor = cursor->right;
	// 				}
	// 				_node = cursor;
	// 			}
	// 			return (*this);
	// 		}

	// 		/*
	// 		** @brief Post decrement the iterator to the previous value
	// 		** before the value in the tree at iterator position.
	// 		**
	// 		** @return this before the decrementation.
	// 		*/
	// 		BST_const_iterator operator--(int)
	// 		{
	// 			BST_const_iterator tmp(*this);
	// 			operator--();
	// 			return (tmp);
	// 		}            

	// 		T *         _node;
	// 		T *         _last_node;
	// 		Compare     _comp;
	// };
}


#endif