/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:53:07 by rchallie          #+#    #+#             */
/*   Updated: 2023/01/16 19:20:56 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#include <stack>

int main()
{
    test_vector();
    std::cout << "\n";
    // test_list();
    // std::cout << "\n";
    // test_map();
    // std::cout << "\n";
    // test_deque();
    // std::cout << "\n";
    test_stack();
    std::cout << "\n";
    // test_queue();
}