/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:33:14 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/15 10:46:54 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector

#define NAMESPACE std

int main ()
{
	{
		std::stack<int> myvector (3,100);          // deque with 3 elements

		std::stack<int> first;                    // empty stack

		std::stack<int,std::vector<int> > second;  // empty stack using vector
		std::stack<int,std::vector<int> > third (myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
	}
	{
		std::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);

		while (!mystack.empty())
		{
		   sum += mystack.top();
		   mystack.pop();
		}

		std::cout << "total: " << sum << '\n';	
	}
  return 0;
}
