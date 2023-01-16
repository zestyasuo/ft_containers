#ifndef vector_HPP
#define vector_HPP
#include <memory.h>
#include <algorithm>
#include <cstddef>
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include "algorithm.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type>					iterator;
		typedef ft::random_access_iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _array(0), _size(0), _capacity(0){};

		explicit vector(size_type n, value_type const &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _array(u_nullptr), _size(n), _capacity(n)
		{
			_array = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_array[i], val);
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last,
				allocator_type const &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = u_nullptr) : _alloc(alloc)
		{
			bool is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value;
			if (!is_valid)
				throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
			if (first > last)
				throw std::length_error("vector");
			_size = last - first;
			_capacity = _size;
			_array = _alloc.allocate(_capacity);
			for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
				_alloc.construct(_array + i, *(first + i));
		}

		vector(const vector &other):
			_size(0), _capacity(0)
		{
			*this = other;
		}

		vector &operator=(const vector &x)
		{
			if (this == &x)
				return *this;
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			this->_size = x._size;
			if(_capacity < _size){
				if (_capacity != 0)
					_alloc.deallocate(_array, _capacity);
				_capacity = _size;
				_array = _alloc.allocate(_capacity);
			}
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_array + i, x[i]);
			return *this;
		}

		size_type size(void) const
		{
			return (_size);
		}
		size_type max_size(void) const
		{
			return _alloc.max_size();
		}
		size_type capacity(void) const
		{
			return (_capacity);
		}
		bool empty(void) const
		{
			return _size == 0;
		}

		void reserve(size_type n)
		{
			if (n < _capacity)
				return;
			pointer new_array = _alloc.allocate(n);
			try
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&new_array[i], _array[i]);
			}
			catch (std::exception &e)
			{
				for (size_type i = 0; new_array[i] && i < _size; i++)
					_alloc.destroy(&new_array[i]);
				_alloc.deallocate(new_array, n);
				throw;
			}
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			if (_capacity)
				_alloc.deallocate(_array, _capacity);
			_capacity = n;
			_array = new_array;
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (_size == n)
				return;
			if (n > _capacity)
				reserve(n);
			if (n > _size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}
			else if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_size = n;
			}
		}

		void push_back(value_type const &el)
		{
			if (_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			_alloc.construct(&_array[_size], el);
			_size++;
		}

		void pop_back(void)
		{
			_alloc.destroy(_array + _size - 1);
			_size--;
		}

		reference operator[](size_type n)
		{
			return _array[n];
		}

		const_reference operator[](size_type n) const
		{
			return _array[n];
		}

		reference at(size_type n)
		{
			if (n > _capacity)
				throw std::out_of_range("out of range");
			return _array[n];
		}

		const_reference at(size_type n) const
		{
			if (n > _capacity)
				throw std::out_of_range("out of range");
			return _array[n];
		}

		reference front()
		{
			return _array[0];
		}

		const_reference front() const
		{
			return _array[0];
		}

		reference back()
		{
			return _array[_size - 1];
		}

		const_reference back() const
		{
			return _array[_size - 1];
		}

		allocator_type get_allocator() const
		{
			return (allocator_type(_alloc));
		}

		void clear()
		{
			size_type size = _size;
			for (size_type i = 0; i < size; i++)
			{
				_alloc.destroy(&_array[_size]);
				_size--;
			}
			// for (size_type i = 0; i < _size; i++)
			// 	_alloc.destroy(&_array[i]);
			// _size = 0;
		}

		// void assign(size_type n, const value_type &val)
		// {
		// 	resize(n);
		// 	clear();
		// 	for (size_type i = 0; i < _size; i++)
		// 	{
		// 		_alloc.construct(&_array[i], val);
		// 	}
		// }

		void swap(vector &other)
		{
			ft::swap(_alloc, other._alloc);
			ft::swap(_array, other._array);
			ft::swap(_size, other._size);
			ft::swap(_capacity, other._capacity);
		}

		~vector(void)
		{
			clear();
			if (_array)
				_alloc.deallocate(_array, _capacity);
			// for (size_type i = 0; i < _size; i++)
				// _alloc.destroy(&_array[i]);
			// if (_capacity)
				// _alloc.deallocate(_array, _capacity);
		};

		iterator begin()
		{
			return (_array);
		}
		const_iterator begin() const
		{
			return (_array);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}
		iterator end()
		{
			return _array + _size;
		}
		const_iterator end() const
		{
			return ((_array + (_size)));
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = u_nullptr)
		{
			bool is_valid;
			if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
				throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>());
			this->clear();
			size_type	dist = ft::distance(first, last);
			if (_capacity >= dist)
			{
				for (;&(*first) != &(*last); first++, _size++)
					_alloc.construct(&_array[_size], *first);
			}
			else
			{
				pointer	new_array = pointer();
				size_t	new_size = 0;
				size_t	new_capacity = 0;

				new_array = _alloc.allocate(dist);
				new_capacity = dist;
				for (; &(*first) != &(*last); first++, new_size++)
					_alloc.construct(&new_array[new_size], *first);
				_alloc.deallocate(_array, capacity());

				_array = new_array;
				_size = new_size;
				_capacity = new_capacity;
			}
		}

		void	assign (size_type n, value_type const &val)
		{
			clear();
			if (n == 0)
				return;
			if (_capacity >= n)
			{
				while (n)
				{
					_alloc.construct(&_array[_size++], val);
					n--;
				}
			}
			else
			{
				_alloc.deallocate(_array, _capacity);
				_array = _alloc.allocate(n);
				_size = 0;
				_capacity = n;
				while (n)
				{
					_alloc.construct(&_array[_size++], val);
					n--;
				}
			}
		}

		iterator	insert(iterator position, value_type const &val)
		{
			size_type	pos_len = &(*position) - _array;
			if (_capacity - _size >= _size + 1)
			{
				for (size_type i = 0; i < pos_len; i++)
					_alloc.construct(&_array[_size - i], _array[_size - i - 1]);
				_size++;
				_alloc.construct(&(*position), val);
			}
			else
			{
				pointer	new_array = pointer();
				size_type new_size = 0;
				size_type	new_cap = 0;
			
				int	next_capacity = _size * 2 > 0 ? _size * 2 : 1;
				new_array = _alloc.allocate(next_capacity);
				new_size = _size + 1;
				new_cap = next_capacity;

				for (size_type i = 0; i < pos_len; i++)
					_alloc.construct(new_array + i, _array[i]);
				_alloc.construct(new_array + pos_len, val);
				for (size_type j = 0; j < _size - pos_len; j++)
					_alloc.construct(&_array[_size - j - 1], _array[_size - j - 1]);
				
				for (size_type l = 0; l < _size; l++)
					_alloc.destroy(&_array[l]);
				if (_array)
					_alloc.deallocate(_array, _capacity);
				
				_array = new_array;
				_size = new_size;
				_capacity = new_cap;
			}
			return (iterator(&_array[pos_len]));
		}

		void	insert(iterator position, size_type n, value_type const &val)
		{
			if (n == 0)
				return ;
			if (n > this->max_size())
				throw std::length_error("vector::insert (fill)");
			size_type	pos_len = &(*position) - _array;
			if (_capacity - _size >= n)
			{
				for (size_type i = 0; i < _size - pos_len; i++)
					_alloc.construct(&_array[_size - i + (n -1)], _array[_size - i - 1]);
				_size += n;
				while (n)
				{
					_alloc.construct(&(*position) + (n - 1), val);
					n--;
				}
			}
			else
			{
				pointer	new_array = pointer();
				size_type	new_size = 0;
				size_type	new_cap = 0;

				int	next_cap = _capacity > 0 ? _size * 2 : 1;
				new_array = _alloc.allocate(next_cap);
				new_cap = next_cap;
				new_size = _size + n;

				if (new_cap < _size + n)
				{
					if (new_array)
						_alloc.deallocate(new_array, new_cap);
					next_cap = _size + n;
					new_array = _alloc.allocate(next_cap);
					new_size = _size + n;
					new_cap = next_cap;
				}

				for (size_type i = 0; i < size_type(&(*position) - _array); i++)
					_alloc.construct(new_array + i, _array[i]);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(new_array + pos_len + i, val);
				for (size_type i = 0; i < _size - pos_len; i++)
					_alloc.construct(&new_array[new_size - i - 1], _array[_size - i - 1]);

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				_alloc.deallocate(_array, _capacity);

				_array = new_array;
				_size = new_size;
				_capacity = new_cap;
			}
		}

		template<class InputIterator>
		void	insert (
			iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = u_nullptr)
		{
			bool is_valid;
			if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
				throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>());
			
			size_type dist = ft::distance(first, last);
			if (_capacity - _size >= dist)
			{
				for (size_type i = 0; i < _size - (&(*position) - _array); i++)
					_alloc.construct(&_array[_size - i + (dist - 1)], _array[_size - i - 1]);
				_size += dist;
				for (; &(*first) != &(*last); first++, position++)
					_alloc.construct(&(*position), *first);
			}
			else
			{
				pointer	new_array = pointer();
				size_type	new_size = 0;
				size_type	new_cap = 0;

				new_array = _alloc.allocate(_size * 2);
				new_size = _size + dist;
				new_cap = _size * 2;

				if (new_cap < _size + dist)
				{
					if (new_array)
						_alloc.deallocate(new_array, new_cap);
					new_array = _alloc.allocate(_size + dist);
					new_size = _size + dist;
					new_cap = new_size;
				}

				for (size_type i = 0; i < size_type(&(*position) - _array); i++)
					_alloc.construct(new_array + i, _array[i]);
				for (size_type i = 0; &(*first) != &(*last); first++, i++)
					_alloc.construct(_array + (&(*position) - _array) + i, *first);
				for (size_type i = 0; i < _size - (&(*position) - _array); i++)
					_alloc.construct(new_array + (&(*position) - _array) + dist + i, _array[(&(*position) - _array) + i]);
				
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_alloc.deallocate(_array, _capacity);

				_array = new_array;
				_size = new_size;
				_capacity = new_cap;
			}
		}

		iterator	erase(iterator position)
		{
			size_type	d = static_cast<size_type>(ft::distance(begin(), position));
			for (size_type i = d; i < _size - 1; i++)
			{
				_alloc.destroy(_array + i);
				_alloc.construct(_array + i, _array[i + 1]);
			}
			_size--;
			_alloc.destroy(&_array[_size - 1]);
			return iterator(_array + d);
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type start = ft::distance(begin(), first);
			difference_type to_copy = ft::distance(begin(), first);

			bool last_is_end = (last == (end()));
			while (first != last)
			{
				_alloc.destroy(&(*first));
				first++;
			}
			size_type i = start;
			while (last < end())
			{
				if (_array + start)
					_alloc.destroy(_array + i);
				_alloc.construct(_array + i, *last);
				i++;
				last++;
			}
			for (size_type i = start + to_copy; i < _size; i++)
				_alloc.destroy(_array + i);
			_size = start + to_copy;
			return last_is_end ? end() : iterator(_array + start);
		}

	private:
		allocator_type _alloc;
		pointer _array;
		size_type _size;
		size_type _capacity;
	};

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < rhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs > rhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif