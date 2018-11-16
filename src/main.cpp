#include <iostream>
#include <cassert>   // assert()
#include <vector>
#include "list.h"

int main(int argc, char const *argv[])
{
	
	 auto n_unit{0};
    // Unit #1: default constructor
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": default constructor.\n";
        sc::list<int> seq;
        assert( seq.size() == 0 );
        assert( seq.empty() == true );
        std::cout << ">>> Passed!\n\n";
    }

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
	
	sc::list<int>::iterator it3 = l1.begin();
	it3.print_iterator();
	(++it3).print_iterator();
	(it3++).print_iterator();
	it3.print_iterator();
	(--it3).print_iterator();
	(it3--).print_iterator();
	it3.print_iterator();

	sc::list<int>::const_iterator it4 = l4.cbegin();
	++it4;
	l4.insert(it4, 25);
	l4.print_list();
	it4 = l4.cbegin();
	l4.insert(it4, 11);
	l4.print_list();
	it4 = l4.cend();
	l4.insert(it4, 666);
	l4.print_list();

	std::vector<int> v {1,2,3,4,5};
	l4.insert(l4.cend(), v.begin(), v.end());
	l4.print_list();
	l4.insert(l4.begin(), v.begin(), v.end());
	l4.print_list();
	l4.insert(l4.cend(), {777, 888, 999} );
	l4.print_list();
	l4.insert(l4.begin(), {-2, -33, -1} );
	l4.print_list();

	sc::list<int>::iterator it5 = l4.erase(++(l4.begin()));
	l4.print_list();
	it5.print_iterator();
	l4.erase( it5 );
	l4.print_list();
	it5.print_iterator();

	std::cout << ">> Lista 1" << std::endl;
	size_type sz = 8;
	//Se deixar (8, 1) o compilador chama assign( InItr first, InItr last )
	// o certo seria assign( size_type count, const T& value )
	l1.assign( sz , -1);
	l1.print_list();
	l1.assign( v.begin(), v.end() );
	l1.print_list();
	l1.assign( {99, 999, 991, 23232, 13123,1111,2222,333} );
	l1.print_list();
	l1.clear();
	l1.print_list();
	l1.assign( {99, 999, 991, 23232, 13123,1111,2222,333} );
	l1.print_list();
	return 0;

}