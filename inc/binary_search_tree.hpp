#ifndef binary_search_tree_HPP 
# define binary_search_tree_HPP
# include "utils.hpp"
# include "tree_iterator.hpp"
# include <memory>
# define RIGHT true
# define LEFT false

namespace ft
{
	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T>,
				class Node = ft::TreeNode<T>, class Node_Allocator = std::allocator<Node> >
	class binary_search_tree
	{
	public:
		typedef binary_search_tree self;
		typedef self	&self_reference;
		typedef	T		value_type;
		typedef Node	node_type;
		typedef Node	*node_pointer;
		typedef	Node_Allocator	node_allocator;
		typedef	ft::tree_iterator<Node, Compare>	iterator;
		typedef	ft::tree_const_iterator<Node, Compare>	const_iterator;
		typedef	size_t	size_type;

		binary_search_tree(node_allocator const &al = node_allocator()) : _node_alloc(al)
		{
			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
		}

		~binary_search_tree(void) {
			_node_alloc.destroy(_last_node);
			_node_alloc.deallocate(_last_node, 1);
		}

		ft::pair<iterator, bool>	insertPair(value_type ins)
		{
			node_pointer	new_node = _node_alloc.allocate(1);
			node_pointer	prev = _last_node;
			node_pointer	start = _last_node->parent;

			bool side = RIGHT;
			while (start != _last_node)
			{
				int	cur_key = start->value.first;
				if (cur_key == ins.first)
					return ft::make_pair(iterator(start, _last_node), false);
				prev = start;
				if (ins.first > cur_key)
				{
					side = RIGHT;
					start = start->right;
				}
				else
				{
					side = LEFT;
					start = start->left;
				}
			}
			_node_alloc.construct(new_node, Node(ins, prev, _last_node, _last_node));

			if (prev == _last_node)
				_last_node->parent = new_node;
			else if (side == RIGHT)
				prev->right = new_node;
			else
				prev->left = new_node;
			
			_last_node->left = get_lower_node(_last_node->parent);
			_last_node->right = get_higher_node(_last_node->parent);
			_last_node->value.first += 1;
			return ft::make_pair(iterator(new_node, _last_node), true);
		}

		void removeByKey(value_type to_remove)
		{
			_removeByKey(_last_node->parent, to_remove);
		}

		node_pointer	searchByKey(value_type find)
		{
			node_pointer node = _last_node->parent;

			while (node != _last_node)
			{
				if (node->value.first == find.first)
					return node;
				if (node->value.first > find.first)
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}

		void	swap(self &other)
		{
			if (&other == this)
				return;
			ft::swap(_last_node, other._last_node);
		}

		size_type	max_size() const
		{
			return node_allocator().max_size();
		}
		node_allocator	_node_alloc;
		node_pointer	_last_node;

	private:

		node_pointer	get_lower_node(node_pointer root)
		{
			while (root != _last_node && root->left != _last_node)
			{
				root = root->left;
			}
			return root;
		}

		node_pointer	get_higher_node(node_pointer root)
		{
			while (root != _last_node && root->right != _last_node)
				root = root->right;
			return root;
		}

			void _replaceNodeInParent(node_pointer node, node_pointer new_node)
			{
				if (node->parent != _last_node)
				{
					if (_last_node->parent == node)
						_last_node->parent = new_node;

					if (node == node->parent->left)
						node->parent->left = new_node;
					else
						node->parent->right = new_node;
				}
				else
					_last_node->parent = new_node;

				_last_node->left = get_lower_node(_last_node->parent);
				_last_node->right = get_higher_node(_last_node->parent);
				_last_node->value.first -= 1;
				
				new_node->parent = node->parent;
				
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)
			{
				if (new_node->parent != _last_node)
				{
					if (new_node->parent != to_remove)
						new_node->parent->left = new_node->right;
				}
				
				new_node->parent = to_remove->parent;
				if (to_remove->left != new_node)
					new_node->left = to_remove->left;
				if (to_remove->right != new_node)
					new_node->right = to_remove->right;

				if (to_remove->parent != _last_node)
				{
					if (to_remove->parent->left == to_remove)
						to_remove->parent->left = new_node;
					else if (to_remove->parent->right == to_remove)
						to_remove->parent->right = new_node;
				}
				else
					_last_node->parent = new_node;
					
				if (to_remove->left != _last_node && to_remove->left != new_node)
					to_remove->left->parent = new_node;
				if (to_remove->right != _last_node && to_remove->right != new_node)
					to_remove->right->parent = new_node;

				if (to_remove->parent != _last_node)
				{
					to_remove->left = _last_node;
					to_remove->right = _last_node;
					to_remove->parent = new_node;
				}

				_last_node->left = get_lower_node(_last_node->parent);
				_last_node->right = get_higher_node(_last_node->parent);
				_last_node->value.first -= 1;

				_node_alloc.destroy(to_remove);
				_node_alloc.deallocate(to_remove, 1);
			}

			/*
			** @brief need a pair create like : make_pair(key, mapped_type())
			*/
			void _removeByKey(node_pointer node, value_type to_remove)
			{
				if (to_remove.first < node->value.first)
				{
					_removeByKey(node->left, to_remove);
					return ;
				}

				if (to_remove.first > node->value.first)
				{
					_removeByKey(node->right, to_remove);
					return ;
				}

				if (node->left != _last_node && node->right != _last_node)
				{
					node_pointer successor = get_lower_node(node->right);
					_replaceDoubleChildren(node, successor);
					return ;
				}
				else if (node->left != _last_node)
					_replaceNodeInParent(node, node->left);
				else if (node->right != _last_node)
					_replaceNodeInParent(node, node->right);
				else
					_replaceNodeInParent(node, _last_node);
			}
	};
}


#endif