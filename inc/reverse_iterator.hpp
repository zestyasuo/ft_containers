#ifndef reverse_iterator_HPP
#define reverse_iterator_HPP
#include "utils.hpp"

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
	public:
	 	typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
	 	typedef typename ft::iterator_traits<Iter>::value_type	value_type;
	 	typedef typename ft::iterator_traits<Iter>::difference_type	difference_type;
	 	typedef typename ft::iterator_traits<Iter>::pointer	pointer;
	 	typedef typename ft::iterator_traits<Iter>::reference	reference;
		typedef Iter iterator_type;
		reverse_iterator() : current() {}
		explicit reverse_iterator(iterator_type it) : current(it) {}
		template <class Iterator>
		explicit reverse_iterator(const reverse_iterator<Iter> &other) :current(other.base()) {}


		iterator_type	base() const {
			return current;
		}

		reference	operator++() {
			--current;
			return *this;
		}
		reverse_iterator	operator++(int) {
			reverse_iterator	tmp(*this);
			current--;
			return tmp;
		}
		reverse_iterator	&operator--() {
			++current;
			return *this;
		}
		reverse_iterator	operator--(int) {
			reverse_iterator	tmp(*this);
			current++;
			return tmp;
		}

		reverse_iterator operator+(difference_type const &other) const {
			return reverse_iterator(current - other);
		}

		reverse_iterator operator-(difference_type const &other) const {
			return reverse_iterator(current + other);
		}

		reverse_iterator	&operator+=(difference_type const &other) {
			current -= other; 
			return *this;
		}

		reverse_iterator	&operator-=(difference_type const &other) {
			current += other; 
			return *this;
		}

		reference	operator*() const {
			iterator_type	tmp(current);
			return (*(--tmp));
		}
		
		pointer	operator->() const {
			return &(operator*());
		}

		reference	operator[](difference_type n) const {
			return (current[-n-1]);
		}

		~reverse_iterator() {}

	protected:
		iterator_type	current;
	};

	template <class Iterator>
	bool operator==(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator==(reverse_iterator<Iterator_L> const &lhs, reverse_iterator<Iterator_R> const &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<class Iterator>
	bool operator!=(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator!=(reverse_iterator<Iterator_L> const &lhs, reverse_iterator<Iterator_R> const &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<class Iterator>
	bool operator<(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<(reverse_iterator<Iterator_L> const &lhs, reverse_iterator<Iterator_R> const &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<class Iterator>
	bool operator<=(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<=(reverse_iterator<Iterator_L> const &lhs, reverse_iterator<Iterator_R> const &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<class Iterator>
	bool operator>(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>(reverse_iterator<Iterator_L> const &lhs, reverse_iterator<Iterator_R> const &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<class Iterator>
	bool operator>=(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>=(reverse_iterator<Iterator_L> const &lhs, reverse_iterator<Iterator_R> const &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template<class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
										reverse_iterator<Iterator> const revit)
	{
		return revit + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(
		reverse_iterator<Iterator> const &lhs,
		reverse_iterator<Iterator> const &rhs
	)
	{
		return lhs.base() - rhs.base();
	}

	template <class Iterator_L, class Iterator_R>
	bool	operator-(
		reverse_iterator<Iterator_L> const &lhs,
		reverse_iterator<Iterator_R> const &rhs
	)
	{
		return lhs.base() - rhs.base();
	}
}

#endif