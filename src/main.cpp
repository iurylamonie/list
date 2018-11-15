#include <iostream>

#include "list.h"

int main(int argc, char const *argv[])
{
	//== Contrutor Padrão, Clear, Push_front	
	std::cout << ">> Lista 1" << std::endl;
	sc::list<int> l1;
	l1.print_list();
	for( size_type i = 20; i > 0; --i )
	{
		l1.push_front(i);
	}
	l1.print_list();
	l1.clear();
	l1.print_list();
	for( size_type i = 20; i > 0; --i )
	{
		l1.push_front(i);
	}
	l1.print_list();
	for ( size_type i = 21; i < 31; ++i)
	{
		l1.push_back(i);
	}
	l1.print_list();
	std::cout << "First: " << l1.front() << " - Last: " << l1.back() << std::endl;
	
	std::cout << ">> Lista 2" << std::endl;
	//== Construtores
	sc::list<int> l2(10);
	l2.print_list();
	l2.push_front( 2 );
	l2.print_list();
	l2.push_back( 4 );
	l2.print_list();
	l2.pop_back();
	l2.print_list();
	l2.pop_front();
	l2.print_list();
	l2.assign(666);
	l2.print_list();
	l2.clear();
	l2.pop_front();
	l2.pop_back();
	l2.print_list();
	l2.assign(666);
	l2.print_list();

	std::cout << ">> Lista 3" << std::endl;
	sc::list<int> l3(l1);
	l3.print_list();

	std::cout << ">> Lista 4" << std::endl;
	sc::list<int> l4 {1,2,3,4,5,10};
	l4.print_list();
	
	std::cout << ">> Lista 5" << std::endl;
	sc::list<int> l5 = {112,23,31,4,5,10};
	l5.print_list();

	std::cout << ">> Lista 6" << std::endl;
	sc::list<int> l6 = l1;
	l6.print_list();

	std::cout << ((l5 == l6)? "Sim":"Não") << std::endl;
	std::cout << ((l4 == l5)? "Sim":"Não") << std::endl;
	std::cout << ((l6 == l1)? "Sim":"Não") << std::endl;

	std::cout << ((l5 != l6)? "Sim":"Não") << std::endl;
	std::cout << ((l4 != l5)? "Sim":"Não") << std::endl;
	std::cout << ((l6 != l1)? "Sim":"Não") << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << ">>> ITERATORS" <<std::endl;
	sc::list<int>::const_iterator it = l1.cbegin();
	it.print_iterator();
	(++it).print_iterator();
	(it++).print_iterator();
	it.print_iterator();
	(--it).print_iterator();
	(it--).print_iterator();
	it.print_iterator();

	sc::list<int>::const_iterator it2 = l1.cbegin();
	++it2;
	std::cout << ((it == it2)? "Sim":"Não") << std::endl;
	std::cout << ((it != it2)? "Sim":"Não") << std::endl;
	--it2;
	std::cout << ((it == it2)? "Sim":"Não") << std::endl;
	std::cout << ((it != it2)? "Sim":"Não") << std::endl;
	
	sc::list<int> l7( l1.cbegin(), l1.cend() ); //< list( InputIt first, InputIt last )
	l7.print_list();

	sc::list<int>::iterator it3 = l1.begin();
	it3.print_iterator();
	(++it3).print_iterator();
	(it3++).print_iterator();
	it3.print_iterator();
	(--it3).print_iterator();
	(it3--).print_iterator();
	it3.print_iterator();

	return 0;

}