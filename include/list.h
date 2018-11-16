/**
 * @autor Iury Lamonie
 * 
 * @data 15/11/2018
 * 
 * @brief Implementação de uma lista Abstract Data Type (ADT) baseada em uma lista duplamente encadeada.
 * 
 * @status	
 */

#ifndef _LIST_H
#define _LIST_H

#include <iostream> //< std::cout
#include <initializer_list> //< std::initializer_list;

using size_type = unsigned long;
namespace sc
{
	template < typename T>
	class list
	{
	private:
		struct Node
		{
			T data;
			Node * prev;
			Node * next;

			Node( const T & d = T(), Node* p = nullptr, Node* n =nullptr ) : data( d ), prev( p ), next( n )
			{
				/* Empty */
			}
		};
	public:
		class const_iterator
		{
		public:
			const_iterator( void ) { /* Empty */ }

			const Node & operator*() const { return *this->current; }

			const_iterator & operator++( void )
			{
				this->current = this->current->next;
				return *this;
			}

			const_iterator operator++( int )
			{
				const_iterator temp( this->current );
				this->operator++();
				return temp;
			}

			const_iterator & operator--( void )
			{
				this->current = this->current->prev;
				return *this;
			}

			const_iterator operator--( int )
			{
				const_iterator temp( this->current );
				this->operator--();
				return temp;
			}

			bool operator==( const const_iterator & rhs ) const { return this->current == rhs.current; }
			bool operator!=( const const_iterator & rhs ) const { return this->current != rhs.current; }
			
			//==DEBUG
			void print_iterator( )
			{
				std::cout << this->current->data << std::endl;
			}
		protected:
			const_iterator( Node * p ) : current( p ) {}
			Node * current;
			friend class list<T>;
		};

		class iterator : public const_iterator
		{
		public:
			iterator( void ) : const_iterator() { /*Empty*/ } //< Preciso criar essas funções?
			/*
			const Node & operator*() const
			{
				return const_iterator::operator*();
			}
			Node & operator*()
			{
				return const_iterator::operator*();
			}
	
			iterator & operator++()
			{
				return const_iterator::operator++();
			}
			iterator operator++( int )
			{
				return const_iterator::operator++( int );
			}
			iterator & operator--()
			{
				return const_iterator::operator--();
			}
			iterator operator--( int )
			{
				return const_iterator::operator--( int );
			}*/
		
		protected:
			iterator( Node * p ) : const_iterator( p ) {}
			friend class list<T>;
			
		};
		//== SPECIAL MEMBERS
		list( void )
		{
			this->m_size = 0;
			this->m_head = new Node(); //< extra node
			this->m_tail = new Node(); //< extra node
			this->m_head->next = this->m_tail;
			this->m_tail->prev = this->m_head;
		}

		explicit list( size_type count ) : list()
		{
			for( size_type i = 0; i < count; ++i )
			{
				this->push_front( T() );
			}

		} 

		template< typename InputIt > 
		list( InputIt first, InputIt last ) : list() //< revisar codigo do construtor.
		{
			InputIt tmp = first;
			while( tmp != last )
			{
				this->push_back( *tmp );
				++tmp;
			}
		}
		
		list( const list& other ) : list()
		{
			Node * tmp = other.m_head->next; //< Aponta para o primeiro nó da outra lista.
			//Percorre a outra lista.
			for( size_type i = 0; i < other.m_size; ++i )
			{
				this->push_back( tmp->data );
				tmp = tmp->next; //< aponta para o proximo nó.
			}
		}

		list( std::initializer_list<T> ilist ) : list()
		{
			for( auto value : ilist ) //< Percorre toda ilist.s
			{
				this->push_back( value );
			}
		}

		~list( void ) { clear(); }

		list& operator=( const list& other )
		{
			list();
			Node * temp = other.m_head->next; //< Aponta para o primeiro nó da outra lista.
			//Percorre a outra lista.
			for( size_type i = 0; i <  other.m_size; ++i )
			{
				this->push_back( temp->data );
				temp = temp->next; //< Aponta para o proximo nó.
			}
			return *this;
		}

		list & operator=( std::initializer_list<T> ilist )
		{
			list();
			for( auto value : ilist ) //< Percorre toda a lista de inicialização.
			{
				this->push_back( value );
			}
			return *this;
		}

		//== Capacity
		size_type size( void ) { return this->m_size; }
		bool empty( void ) { return (this->m_size == 0); }

		//== MODIFIERS
		void clear( void ) 
		{
			Node * current = this->m_head->next; //< Aponta para ao primeiro nó da lista
			for( size_type i = 1; i <= this->m_size; ++i )
			{
				this->m_head->next = current->next; //< Aponta para o proximo nó da sequencia
				current->next->prev = this->m_head; //< O prev do proximo nó aponta para m_head
				delete current; //< Deleta o nó
				current	= this->m_head->next; //< aponta para o novo primeiro nó da lista.	 
			}
			this->m_size = 0;
		}

		void push_front( const T & value )
		{
			Node * new_node = new Node( value, /*prev*/ this->m_head, /*next*/ this->m_head->next );
			this->m_head->next->prev =  new_node; //< Aponta o prev do antigo primeiro nó para o new_node.
			this->m_head->next = new_node;
			++this->m_size;
		}

		void push_back( const T & value )
		{
			Node * new_node = new Node( value, /*prev*/ this->m_tail->prev, /*next*/ this->m_tail );
			this->m_tail->prev->next = new_node; //< Aponta o next do antigo ultimo nó para o new_node.
			this->m_tail->prev = new_node;
			++this->m_size;
		}

		void pop_back( void )
		{
			if( !empty() )
			{
				Node * current = this->m_tail->prev; //< Aponta para o ultimo nó.
				this->m_tail->prev = current->prev; //< Aponta para o "penultimo" nó.
				current->prev->next = this->m_tail; //< Faz o "penultimo" nó apontar para tail.
				delete current; //< Deleta o ultimo nó.
				--this->m_size;
			}
		}

		void pop_front( void )
		{
			if( !empty() )
			{
				Node * current = this->m_head->next; //< Aponta para o primeiro nó.
				this->m_head->next = current->next; //< Aponta para o "segundo" nó.
				current->next->prev = this->m_head; //< Faz o "segundo" nó apontar head..
				delete current; //< Deleta o primeiro nó.
				--this->m_size;
			}
		}

		const T & back() const { return this->m_tail->prev->data ; }

		const T & front() const { return this->m_head->next->data ; }

		void assign( const T & value )
		{
			if( !empty() )
			{
				Node * temp = this->m_head->next;
				for( size_type i = 1; i <= this->m_size; ++i )
				{
					temp->data = value;
					temp = temp->next;
				}
			}
		}
		
		//== Operator overloading
		bool operator==( const list & rhs )
		{
			if( this->m_size == rhs.m_size )
			{
				//Aponta para o primeiro elemento da list lhs
				Node * currLHS = this->m_head->next;
				//Aponta para o primeiro elemento da list rhs
				Node * currRHS = rhs.m_head->next;
				for ( size_type i = 1; i <= this->m_size; ++i)
				{
					if( currLHS->data != currRHS->data ) return false;
					currRHS = currRHS->next;
					currLHS = currLHS->next;
				}
				return true;
			}

			return false;
		}

		bool operator!=( const list & rhs )
		{
			if( this->m_size == rhs.m_size )
			{
				//Aponta para o primeiro elemento da list lhs
				Node * currLHS = this->m_head->next;
				//Aponta para o primeiro elemento da list rhs
				Node * currRHS = rhs.m_head->next;
				for ( size_type i = 1; i <= this->m_size; ++i)
				{
					if( currLHS->data != currRHS->data ) return true;
					currRHS = currRHS->next;
					currLHS = currLHS->next;
				}
				return false;
			}

			return true;
		}

		//== ITERATORS

		const_iterator cbegin() const { return const_iterator( this->m_head->next ); }
		const_iterator cend() const { return const_iterator( this->m_tail ); }
		iterator begin() { return iterator( this->m_head->next ); }
		iterator end() { return iterator( this->m_tail ); }
		
		//== MODIFIERS WITH ITERATORS

		iterator insert( const_iterator pos, const T & value )
		{
			if( !empty() )
			{
				Node * tmp = pos.current;
				Node * new_node = new Node( value, /*prev*/ tmp->prev, /*next*/ tmp );
				tmp->prev->next = new_node; //Aponta o next do nó anterior pra new_node
				tmp->prev =  new_node; //Aponta o prev do pos para o new_node
				++this->m_size;
				return iterator( new_node );
			}

			//Se estiver vazio
			this->push_back( value );
			return iterator( this->m_head->next );
		}

		template < typename InItr >
		iterator insert( const_iterator pos, InItr first, InItr last )
		{
			InItr currIt = first; //< Iterador atual
			iterator it; //< Iterador para o primeiro item inserido do rage na list
			while( currIt != last )
			{
				//Armazena o iterador para o primeiro item inserido.
				if( currIt == first ) it = insert( pos, *currIt );
				else insert( pos, *currIt );
				++currIt;
			}

			return it; //< Retornar o iterador para o primeiro elemento inserido do rage.
		}

		iterator insert( const_iterator pos, std::initializer_list<T> ilist )
		{
			iterator it; //< Aponta para o primeiro item inserido do ilist na list
			size_type aux = 0;
			for( auto i : ilist )
			{
				if( aux == 0 ) //< Verifica se é o primeiro elemento
				{
					it = insert( pos, i );
					++aux;	
				}
				else insert( pos, i );
			}

			return it;
		}

		iterator erase( const_iterator pos )
		{
			Node * pc = pos.current; //< Aponta para o nó que vai ser deletado.
			iterator it( pc->next ); //< Iterador para o proximo nó.
			/* 
			 * Verifica se a lista esta fazia e se o node que deseja 
			 * delatar não é o head ou tail.
			 */
			if( !empty() and pc != this->m_tail and pc != this->m_head )
			{
				// O next do nó anterior aponta para o proximo nó da pos.
				pc->prev->next = pc->next;
				// O prev do proximo nó aponta para nó anterior da pos.
				pc->next->prev = pc->prev;
				delete pc; //< Deleta o nó
				//pos.current = nullptr; //< 
				--this->m_size;
			}
			// Retorna um iterador ao nó seguinte de pos.
			return it;
		}
		
		iterator erase( const_iterator first, const_iterator last )
		{
			const_iterator it = first;
			while( it != last )
			{
				this->erase(it);
				++it;
			}
			// Verifica se o last armazena a tail da list.
			if( it.current != this->m_tail )
			{
				this->erase( it ); //< Deleta se nao for a tail da list.
				++it;
			}
			// Retorna um iterador para o elemento seguinte a last. 
			return iterator(it.current);
		}

		void assign( size_type count, const T& value )
		{
			this->erase( this->begin(), this->end() ); //< Limpa a lista
			for( size_type i = 0; i < count; ++i)
			{
				this->push_back( value );
			}
		}

		template < typename InItr >
		void assign( InItr first, InItr last )
		{
			this->erase( this->begin(), this->end() ); //< Limpa a lista
			InItr temp = first;
			while( temp != last )
			{
				push_back( *temp );
				++temp;
			}
		}

		void assign( std::initializer_list<T> ilist )
		{
			this->erase( this->begin(), this->end() ); //< Limpa a lista
			for( auto i: ilist )
			{
				this->push_back( i );
			}
		}
		

		//== DEBUG
		void print_list()
		{
			std::cout << "[ ";
			Node * temp = this->m_head->next;
			for( size_type i = 1; i <= this->m_size; ++i )
			{
				std::cout << temp->data << " ";
				temp = temp->next;
			}
			std::cout << "] - Size: " << this->m_size << std::endl;
		}


	private:
		size_type m_size;
		Node * m_head;
		Node * m_tail;	
	};	
};

#endif