#include <iostream>

#include "list.h"

int main()
{
	ls::list<int> l1;
	std::cout << l1.size() << std::endl;
	l1.printList();
	ls::list<int> l2(10);
	std::cout << l2.size() << std::endl;
	l2.printList();
	ls::list<int> l3 {1,2,3};
	std::cout << l3.size() << std::endl;
	l3.printList();
	l3.push_front(5);
	l3.push_back(-1);
	l3.printList();
	std::cout << l3.front() << std::endl;
	std::cout << l1.front() << std::endl;
	return 0;

}