#include <iostream>

#include "list.h"

int main(int argc, char const *argv[])
{
	ls::list<int> l1;
	l1.printList();
	l1.push_back(9);
	l1.push_back(10);
	l1.push_front(8);
	l1.push_front(7);
	l1.printList();
	std::cout << "front() :" << l1.front() << " back(): " << l1.back() << std::endl;
	l1.pop_front();
	std::cout << "front() :" << l1.front() << " back(): " << l1.back() << std::endl;
	l1.printList();
	l1.pop_back();
	std::cout << "front() :" << l1.front() << " back(): " << l1.back() << std::endl;
	l1.printList();
	l1.clear();
	l1.printList();
	l1.push_back(90);
	l1.push_back(100);
	l1.push_front(80);
	l1.push_front(70);
	l1.printList();

	l1 = {1,2,3,4,5,6}; //< operator=( std::initializer_list<T> ilist )
	l1.printList();

	ls::list<int> l2 = l1;
	l2.printList();
	l2.pop_back();
	l2.printList();
	l1.printList();
	return 0;
}