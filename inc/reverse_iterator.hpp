#ifndef reverse_iterator_HPP
#define reverse_iterator_HPP
#include "utils.hpp"

namespace ft
{

	template <class Iter>
	class reverse_iterator : public ft::iterator<
								typename ft::iterator_traits<Iter>::iterator_category,
								typename ft::iterator_traits<Iter>::value_type,
								typename ft::iterator_traits<Iter>::difference_type,
								typename ft::iterator_traits<Iter>::pointer,
								typename ft::iterator_traits<Iter>::reference>
	{
	public:
	 	typedef typename ft::iterator_traits<Iter>::iterator_categoty	iterator_category;
	 	typedef typename ft::iterator_traits<Iter>::value_type	value_type;
	 	typedef typename ft::iterator_traits<Iter>::difference_type	difference_type;
	 	typedef typename ft::iterator_traits<Iter>::pointer	pointer;
	 	typedef typename ft::iterator_traits<Iter>::reference	reference;
		typedef Iter iterator_type;
		reverse_iterator() : current() {}
		explicit reverse_iterator(iterator_type it) : current(it) {}
		template <class U>
		explicit reverse_iterator(const U &other) :current(other.base()) {}

		iterator_type	base() const {
			return current;
		}

		reverse_iterator	&operator++() {
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

		reference	operator*() {
			iterator_type	tmp(current);
			return (*--tmp);
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
}

#endif