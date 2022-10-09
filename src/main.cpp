#include <iostream>
#include "../inc/vector.hpp"
#include "../inc/stack.hpp"

template <typename T>
void	display_vector(ft::vector<T> &vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}


int main()
{
	using namespace std;
	ft::vector<int> vec;
	ft::stack<int> s1;
	ft::stack<int> s2;
	ft::stack<int> s3;

	// s1.push(2);
	// s1.push(4);
	// s1.push(6);
	// s1.push(8);
	// s2.push(5);
	// s2.push(10);
	// s3.push(2);
	// s3.push(4);
	// s3.push(6);
	// s3.push(8);
	// if (s1 >= s2)
	// 	cout << "The stack s1 is greater than or equal to "
	// 		 << "the stack s2." << endl;
	// else
	// 	cout << "The stack s1 is less than "
	// 		 << "the stack s2." << endl;

	// if (s1 >= s3)
	// 	cout << "The stack s1 is greater than or equal to "
	// 		 << "the stack s3." << endl;
	// else
	// 	cout << "The stack s1 is less than "
	// 		 << "the stack s3." << endl;

	// // to print out the stack s1 ( by unstacking the elements):
	// ft::stack<int>::size_type i_size_s1 = s1.size();
	// cout << "The stack s1 from the top down is: ( ";
	// unsigned int i;
	// for (i = 1; i <= i_size_s1; i++)
	// {
	// 	cout << s1.top() << " ";
	// 	s1.pop();
	// }
	// cout << ")." << endl;
	

	//VECTOR TESTS
	std::cout << vec.max_size() << " ";
	std::cout << vec.size() << "\n";
	std::cout << "Push back: \n";
	std::cout << "Capacity before push back: " << vec.capacity() << "\n";
	vec.push_back(10);
	std::cout << "Capacity after push back: " << vec.capacity() << "\n";
	std::cout << "Size: " << vec.size() << "\n";
	std::cout << vec.back() << "\n";
	// std::cout << vec.at(111) << "\n";
	std::cout << vec.front() << "\n";
	std::cout << "Reserve: \n";
	std::cout << "Capacity before reserve 10: " << vec.capacity() << "\n";
	vec.reserve(10);
	std::cout << "Capacity after reserve 10: " << vec.capacity() << "\n";
	vec.push_back(11);
	vec.push_back(12);
	display_vector(vec);
	vec.pop_back();
	vec.pop_back();
	display_vector(vec);

}