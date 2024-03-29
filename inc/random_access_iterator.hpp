#ifndef random_access_iterator_HPP
# define random_access_iterator_HPP
# include "utils.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef T*			pointer;
		typedef	T&			reference;


		random_access_iterator(void) : _ptr(u_nullptr)
		{
		}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		random_access_iterator(random_access_iterator const &other) : _ptr(other._ptr)
		{
		}

		random_access_iterator &operator=(random_access_iterator const &other)
		{
			if (this == &other)
				return *this;
			this->_ptr = other._ptr;
			return *this;
		}

		virtual ~random_access_iterator()
		{
		}

		pointer base() const
		{
			return _ptr;
		}

		reference operator*(void) const
		{
			return *_ptr;
		}

		pointer operator->() const
		{
			return &(*_ptr);
		}

		random_access_iterator &operator++()
		{
			_ptr++;
			return *this;
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp(*this);
			++this->_ptr;
			return tmp;
		}

		random_access_iterator &operator--()
		{
			_ptr--;
			return *this;
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator tmp(*this);
			_ptr--;
			return tmp;
		}

		random_access_iterator operator+(difference_type other) const
		{
			return random_access_iterator(_ptr + other);
		}

		random_access_iterator operator-(difference_type other) const
		{
			return random_access_iterator(_ptr - other);
		}

		random_access_iterator &operator+=(difference_type n)
		{
			_ptr += n;
			return *this;
		}

		random_access_iterator &operator-=(difference_type n)
		{
			_ptr -= n;
			return *this;
		}


		reference operator[](difference_type n)
		{
			return *(_ptr + n);
		}

		operator	random_access_iterator<const T>() const
		{
			return random_access_iterator<const T>(_ptr);
		}

	protected:
		pointer _ptr;
	};

	template <typename T>
	bool operator==(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Tl, typename Tr>
	bool operator==(random_access_iterator<Tl> const &lhs, random_access_iterator<Tr> const &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename T>
	bool operator>=(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Tl, typename Tr>
	bool operator>=(random_access_iterator<Tl> const &lhs, random_access_iterator<Tr> const &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename T>
	bool operator<=(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Tl, typename Tr>
	bool operator<=(random_access_iterator<Tl> const &lhs, random_access_iterator<Tr> const &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename T>
	bool operator!=(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Tl, typename Tr>
	bool operator!=(random_access_iterator<Tl> const &lhs, random_access_iterator<Tr> const &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename T>
	bool operator>(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Tl, typename Tr>
	bool operator>(random_access_iterator<Tl> const &lhs, random_access_iterator<Tr> const &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename T>
	bool operator<(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Tl, typename Tr>
	bool operator<(random_access_iterator<Tl> const &lhs, random_access_iterator<Tr> const &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<typename T>
	random_access_iterator<T>	operator+(typename random_access_iterator<T>::diffefence_type n, random_access_iterator<T> const &rai) {
		return &(*rai) + n;
	}

	template<typename T>
	typename random_access_iterator<T>::difference_type	operator-(ft::random_access_iterator<T> const lhs, ft::random_access_iterator<T> const rhs) {
		return lhs.base() - rhs.base();
	}

	template<typename Tl, typename Tr>
	typename random_access_iterator<Tl>::difference_type	operator-(random_access_iterator<Tl> const lhs, random_access_iterator<Tr> const rhs) {
		return lhs.base() - rhs.base();
	}
}
#endif