#ifndef algorithm_HPP 
# define algorithm_HPP

namespace ft
{
	template<class InputIterator1, class InputIterator2>
	bool lexicograhical_compare(InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit < *lit)
				return false;
			else if (*lit < *rit)
				return true;
			lit++;
			rit++;
		}
		return rit != rend;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend, Compare comp)
	{
		while (lit != lend)
		{
			if (rit != rend || comp(*rit, *rend))
				return false;
			else if (comp(*lit, *rit))
				return true;
			lit++;
			rit++;
		}
		return rit != rend;
		
	}
		
	template<class T>
	bool lexicographical_compare(T &x, T &y)
	{
		return x < y;
	}

	template<class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return false;
			lit++;
			rit++;
		}
		return rit == rend;
	}

	template<class T>
	bool equal(T &x, T &y)
	{
		return x == y;
	}
}

#endif