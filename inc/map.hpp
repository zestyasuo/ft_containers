#ifndef map_HPP 
# define map_HPP
# include "utils.hpp"
# include "tree_iterator.hpp"
# include "binary_search_tree.hpp"
# include "reverse_iterator.hpp"
# include <functional>

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>,
				class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<key_type, mapped_type> value_type;
		typedef Compare key_compare;
		
		class value_compare : std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, Allocator>;
		protected:
			Compare comp;
			value_compare(Compare comp) : comp(comp){}
		public:
			bool operator() (value_type const &a, value_type const &b) const
			{
				return comp(a.first, b.first);
			}
		};

		typedef Allocator allocator_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_reference const_pointer;
		typedef typename ft::binary_search_tree<value_type, key_compare>::iterator	iterator;
		typedef typename ft::binary_search_tree<value_type, key_compare>::const_iterator	const_iterator;
		typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t	size_type;

		explicit map (key_compare const &comp = key_compare(), allocator_type const &alloc = allocator_type())
		:
			_alloc(alloc),
			_comp(comp),
			_bst()
		{}

		template<class InputIterator>
		map(InputIterator first, InputIterator last, key_compare const &comp = key_compare(),
			allocator_type const &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:
			_alloc(alloc),
			_comp(comp),
			_bst()
		{
			bool is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value;
			if (!is_valid)
				throw ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
			insert(first, last);
		}

		map (map const &other):
			_alloc (other._alloc),
			_comp(other._comp),
			_bst()
		{
			insert(other.begin(), other.end());
		}

		virtual ~map()
		{
			clear();
		}

		map	&operator=(map const &other)
		{
			if (&other == this)
				return *this;
			clear();
			insert(other.begin, other.end());
			return *this;
		}

		iterator	begin()
		{
			return iterator(_bst._last_node->left, _bst._last_node);
		}

		const_iterator begin() const
		{
			return const_iterator(_bst._last_node->left, _bst._last_node);
		}

		iterator end()
		{
			return iterator(_bst._last_node, _bst._last_node);
		}
		
		const_iterator	end() const
		{
			return iterator(_bst._last_node, _bst._last_node);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		
		const_reverse_iterator rbegin() const
		{
			return reverse_iterator(end());
		}

		reverse_iterator	rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const
		{
			return _bst._last_node->parent == _bst._last_node;
		}

		size_type	size() const
		{
			return _bst._last_node->value.first;
		}

		size_type	max_size() const
		{
			return _bst.max_size();
		}

		mapped_type	&operator[](key_type const &key)
		{
			iterator it = find(key);

			if (it == end())
				insert(ft::make_pair(key, mapped_type()));
			it = find(key);
			return (*it).second;
		}

		pair<iterator, bool> insert (value_type const &val)
		{
			return _bst.insertPair(val);
		}

		iterator insert(iterator position, value_type const &val)
		{
			(void)position;
			return _bst.insertPair(val).first;
		}

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = u_nullptr)
		{
			bool is_valid;
			if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
				throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

			difference_type n = ft::distance(first, last);
			while (n--)
				insert(*(first++));
		}

		void	erase(iterator position)
		{
			erase((*position).first);
		}

		size_type	erase (key_type const &k)
		{
			if (find(k) == end())
				return 0;
			_bst.removeByKey(ft::make_pair(k, mapped_type()));
			return 1;
		}

		void	erase(iterator first, iterator last)
		{
			while (first != last)
			{
				erase((*(first++)).first);
			}
		}

		void	swap(map &other)
		{
			_bst.swap(other._bst);
		}

		void clear()
		{
			erase(begin(), end());
		}

		key_compare key_comp() const
		{
			return key_compare();
		}
		
		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

		iterator find (key_type const &key)
		{
			return iterator(_bst.searchByKey(ft::make_pair(key, mapped_type())), _bst._last_node);
		}
		
		const_iterator find(key_type const &key) const
		{
			return const_iterator(_bst.searchByKey(ft::make_pair(key, mapped_type())), _bst._last_node);
		}
		
		size_type count(key_type const &key) const
		{
			const_iterator start = begin();
			const_iterator finish = end();
			
			while (start != finish)
				if ((*(start++)).first == key)
					return 1;
			return 0;
		}

		iterator lower_bound (const key_type& k)
		{
			iterator start = begin();
			iterator finish = end();

			while (start != finish)
			{
				if (_comp((*start).first, k) == false)
					break;
				start++;
			}
			return (start);
		}

		const_iterator	lower_bound (key_type const &key) const
		{
			return const_iterator(lower_bound(key));
		}

		iterator	upper_bound(key_type const &key)
		{
			iterator start = begin();
			iterator finish = end();
			
			while (start != finish)
			{
				if (_comp(key , (*start).first))
					break ;
				start++;
			}
			return start;
		}
			
		const_iterator	upper_bound(key_type const &key) const
		{
			return const_iterator(upper_bound(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range (key_type const &key) const
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		ft::pair<iterator, iterator> equal_range (key_type const &key)
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

	private:
		allocator_type	_alloc;
		Compare			_comp;
		binary_search_tree<value_type, Compare> _bst;
		
	};
}
#endif