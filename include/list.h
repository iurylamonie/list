#ifndef _LIST_H
#define _LIST_H

#include <initializer_list> //< std::initializer_list
#include <iostream>

using size_type = unsigned long;

namespace sc
{
	template < typename T >
	class list
	{
	
	private:
		struct  Node
		{
			T data;
			Node *prev;
			Node *next;

			Node( const T & d = T(), Node * p = nullptr, Node * n = nullptr) : data( d ), prev( p ), next( n )
			{
				/* Empty */
			}
		};

	public:
		class const_iterator
		{
		public:
			const_iterator( Node * p ) : current( p ) {}
			
			const Node & operator*() const { return *this->current; }

			const_iterator & operator++()
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
			const_iterator & operator--()
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
			bool operator==( const const_iterator & rhs ) const { return this->current == rhs->current; }
			bool operator!=( const const_iterator & rhs ) const { return this->current == rhs->current; }

		protected:
			Node *current;
			friend class list< T >;
		};

		class iterator
		{
		public:
			iterator( Node *p ) : const_iterator( p ) { /* Empty */ };
			const Node & operator*() const
			{
				return *this->current;
			}
			Node & operator*()
			{
				return *this->current;
			}
	
			iterator & operator++()
			{
				this->current = this->current->next;
				return *this;
			}
			iterator operator++( int )
			{
				iterator temp = this->current;
				this->operator++();
				return *temp;
			}
			iterator & operator--()
			{
				this->current = this->current->prev;
				return *this;
			}
			iterator operator--( int )
			{
				iterator temp = this->current;
				this->operator--();
				return *temp;
			}
			bool operator==( const iterator & rhs ) const { return this->current == rhs->current; }
			bool operator!=( const iterator & rhs ) const { return this->current == rhs->current; }

		protected:			
			friend class list<T>;
		};

		//== SPECIAL MEMBERs

		/**
		 * @brief      Default constructor that creates an empty list.
		 */
		list(){ this->iniciar_list(); }
		
		/**
		 * @brief      Constructs the list with count default-inserted instances of T .
		 *
		 * @param[in]  the size of the list.
		 */
		explicit list( size_type count )
		{		
			this->iniciar_list();
			for( size_type i = 0; i < count; ++i)
			{
				this->push_back( T() ); //< Duvida
			}
		}

		/**
		 * @brief      Constructs the list with the contents of the range [first, last) .
		 *
		 * @param[in]  first    The first element on the rage
		 * @param[in]  last     The last element on the rage
		 *
		 * @tparam     InputIt  Inmput Iterator
		 */
		template < typename InputIt >
		list( InputIt first, InputIt last )
		{
			this->iniciar_list();
			InputIt temp = first; //< Aponta para o valor atual
			while( temp != last )
			{
				this->push_back( *temp ); //< Insere na ordem certa
				++temp;
			}
		}

		/**
		 * @brief      Copy constructor. Constructs the list with the deep copy of the contents of other .
		 *
		 * @param[in]  another list to be used as source to initialize the elements of the list with.
		 */
		list( const list & other )
		{
			this->iniciar_list();
			Node * temp = other.m_head; //< Aponta para o head da outra lista
			for( size_type i = 0; i <  other.m_size; ++i ) //< Percorre a outra lista 
			{
				this->push_back( temp->data );
				temp = temp->next; //< Aponta o temp para o proximo nó.
			}
		}

		/**
		 * @brief      Replaces the contents with those identified by initializer list ilist .
		 *
		 * @param[in]  initializer list to initialize the elements of the list with.
		 */
		list( std::initializer_list<T> ilist )
		{
			this->iniciar_list();
			for( auto value : ilist ) //< Percorre toda a lista de inicialização.
			{
				this->push_back( value );
			}
		}
		
		/**
		 * @brief      Destructs the list. The destructors of the elements are called and the 
		 * used storage is deallocated. Note, that if the elements are pointers, 
		 * the pointed-to objects are not destroyed.
		 */
		~list(){ this->clear(); }
		
		/**
		 * @brief      Copy assignment operator. Replaces the contents with a copy of the contents of other.
		 *
		 * @param[in]  another list to be used as source to initialize the elements of the list with.
		 *
		 * @return     The list
		 */
		list & operator=( const list & other )
		{
			this->iniciar_list();
			Node * temp = other.m_head; //< Aponta para o head da outra lista
			for( size_type i = 0; i <  other.m_size; ++i ) //< Percorre a outra lista 
			{
				this->push_back( temp->data );
				temp = temp->next; //< Aponta o temp para o proximo nó.
			}
			return *this;
		}

		/**
		 * @brief      Replaces the contents with those identified by initializer list ilist .
		 *
		 * @param[in]  initializer list to initialize the elements of the list with.
		 *
		 * @return     The list
		 */
		list & operator=( std::initializer_list<T> ilist )
		{
			this->iniciar_list();
			for( auto value : ilist ) //< Percorre toda a lista de inicialização.
			{
				this->push_back( value );
			}
			return *this;
		}

		//== DEBUG

		/**
		 * @brief      Função para printar a list.
		 */
		void printList()
		{
			std::cout << "[ ";
			Node * temp = this->m_head;
			for( size_type i = 1; i <= this->m_size; ++i )
			{
				std::cout << temp->data << " ";
				temp = temp->next;
			}
			std::cout << "] - Size: " << this->m_size << std::endl;
		}

		//== ITERATORS

		/**
		 * @brief      returns an iterator pointing to the first item in the list
		 *
		 * @return     returns an iterator
		 */
		iterator begin() { return iterator( this->m_head ); }
		
		/**
		 * @brief      returns an iterator pointing to the first item in the list
		 *
		 * @return     returns an iterator
		 */
		const_iterator cbegin() const { return const_iterator( this->m_head ); }
		
		/**
		 * @brief      returns an iterator pointing to the end mark in the list
		 *
		 * @return     returns an iterator
		 */
		iterator end() { return ++(iterator( this->m_tail )); }
		
		/**
		 * @brief      returns an iterator pointing to the end mark in the list
		 *
		 * @return     returns an iterator
		 */
		const_iterator cend() const { return ++(const_iterator( this->m_tail )); }

		//== Capacity

		/**
		 * @brief      return the number of elements in the container.
		 *
		 * @return     m_size
		 */
		size_type size() const { return this->m_size; }

		/**
		 * @brief      returns true if the container contains no elements, and false otherwise.
		 *
		 * @return     true or false
		 */
		bool empty() const { return (this->m_size == 0); }

		//== MODIFIERS

		/**
		 * @brief      remove all elements from the container.
		 */
		void clear(){ this->iniciar_list(); } 
		
		/**
		 * @brief      returns the object at the beginning of the list.
		 *
		 * @return     The element
		 */
		T & front() { return this->m_head->data; }
		
		/**
		 * @brief      returns the object at the beginning of the list.
		 *
		 * @return    The element
		 */
		const T & front() const { return this->m_head->data; }
		
		/**
		 * @brief      returns the object at the end of the list.
		 *
		 * @return     The element
		 */
		T & back() { return this->m_tail->data; }

		/**
		 * @brief      returns the object at the end of the list.
		 *
		 * @return     The element
		 */
		const T & back() const { return this->m_tail->data; }
		
		/**
		 * @brief      adds value to the front of the list.
		 *
		 * @param[in]  value  The value
		 */
		void push_front( const T & value )
		{
			Node * new_node = new Node( value, /*prev*/ nullptr, /*next*/ nullptr );
			if( this->m_head == nullptr ) //< Verifica se a lista está vazia
			{
				this->m_head = new_node;
				this->m_tail = new_node;
				++this->m_size;
				return;
			}
			this->m_head->prev = new_node;
			new_node->next = this->m_head;
			this->m_head = new_node;
			++this->m_size;
		}

		/**
		 * @brief      adds value to the end of the list.
		 *
		 * @param[in]  value  The value
		 */
		void push_back( const T & value )
		{
			Node * new_node = new Node( value, /*prev*/ nullptr, /*next*/ nullptr );
			if( this->m_head == nullptr ) //< Verifica se a lista está vazia
			{
				this->m_head = new_node;
				this->m_tail = new_node;
				++this->m_size;
				return;
			}
			this->m_tail->next = new_node;
			new_node->prev = this->m_tail;
			this->m_tail = new_node;
			++this->m_size;
		}
		
		/**
		 * @brief      removes the object at the front of the list.
		 */
		void pop_front()
		{
			if( !empty() )
			{
				Node * next_node = this->m_head->next; //< Aponta para o provavel segundo nó.
				if(next_node != nullptr) next_node->prev = nullptr;
				else this->m_tail = next_node; //< Se next_node for nullptr, só tem um nó.
				this->m_head = next_node;
				--this->m_size;
			}
		}
		
		/**
		 * @brief      removes the object at the end of the list.
		 */
		void pop_back()
		{
			if( !empty() )
			{
				Node * prev_node = this->m_tail->prev; //< Aponta para o nó anterior ao ultimo.
				if( prev_node != nullptr ) prev_node->next = nullptr;  //< Se prev_node for nullptr, só tem um nó.
				else this->m_head = prev_node; //< Caso tenha só um nó;
				this->m_tail = prev_node;
				--this->m_size;
			}
		}
		
		
		/**
		 * @brief      replaces the content of the list with copies of value value.
		 *
		 * @param[in]  value  The value
		 */
		void assign( const T & value )
		{
			if( !empty() )
			{
				Node * temp = this->m_head;
				for( size_type i = 1; i <= this->m_size; ++i )
				{
					temp->data = value;
					temp = temp->next;
				}
			}
		}

		//== MODIFIERS WITH ITERATORS

		/**
		 * @brief      dds value into the list before the position given by the iterator pos .
		 *
		 * @param[in]  pos    The position
		 * @param[in]  value  The value
		 *
		 * @return     returns an iterator to the position of the inserted item.
		 */
		iterator insert( const_iterator pos, const T & value )
		{
			if( !empty() )
			{
				Node * pc = pos->current; 
				Node * new_node = new Node( value, /*prev*/ pc->prev , /*next*/ pc );
				if( pc->prev != nullptr) pc->prev->next = new_node; //< Faz o next do nó anterior apontar para novo nó
				pc->prev = new_node;
				++this->m_size;
				return iterator( new_node );
			}
			
			//Se a list estiver vazia
			this->push_front( value ); 
			return iterator( this->m_head );
		}

		/**
		 * @brief      inserts elements from the range [first; last) before pos .
		 *
		 * @param[in]  pos    The position
		 * @param[in]  first  The first
		 * @param[in]  last   The last
		 *
		 * @tparam     InItr  Inmput Iterator
		 *
		 * @return     returns an iterator to the position of the inserted item first.
		 */
		template < typename InItr >
		iterator insert( const_iterator pos, InItr first, InItr last )
		{
			size_type sz = last - first;
			iterator * currIt = first; //< Iterador atual
			iterator it; //< Aponta para o primeiro item inserido do rage na list
			while( currIt != last )
			{
				if( currIt == first ) it = insert( pos, currIt->current->data );
				else it( pos, currIt->current->data );
				++currIt;
			}

			return it; //< Retornar o iterador para o primeiro elemento inserido do rage.
		}

		/**
		 * @brief      nserts elements from the range [first; last) before pos .
		 *
		 * @param[in]  pos    The position
		 * @param[in]  ilist  The ilist
		 *
		 * @return     returns an iterator to the position of the inserted item first.
		 */
		iterator insert( const_iterator pos, std::initializer_list<T> ilist )
		{
			iterator it; //< Aponta para o primeiro item inserido do ilist na list
			size_type aux = 0;
			for( auto i : ilist )
			{
				if( aux == 0 )
				{
					it = insert( pos, ilist );
					++aux;	
				}
				else insert( pos, ilist );
			}

			return it;
		}

		iterator erase( const_iterator pos )
		{
			Node * pc = pos->current;
			iterator it;
			if( pc != nullptr )
			{
				if(pc->next != nullptr ) pc->next->prev = pc->prev; //< Verifica se é o ultimo nó
				if(pc->prev != nullptr ) pc->prev->next = pc->next; //< verifica se é o primeiro nó
				it = iterator( pc->next );
			}
			else it = iterator( pc );
			pos->current = nullptr;
			if(this->m_size > 0) --this->m_size;
			return it;
		}

		iterator erase( const_iterator first, const_iterator last )
		{
			const_iterator it = first;
			while( it != last )
			{
				erase(it);
				++it;
			}
			if( it->current != nullptr )
			{
				erase( it );
				++it;
			} 
			return it;
		}

		void assign( size_type count, const T& value )
		{
			erase( iterator(this->m_head), iterator(this->m_tail) ); //< Limpa a lista
			for( size_type i = 0; i < count; ++i)
			{
				insert( iterator(m_tail), value );
			}
		}

		template < typename InItr >
		void assign( InItr first, InItr last )
		{
			erase( iterator(this->m_head), iterator(this->m_tail) ); //< Limpa a lista
			InItr temp = first;
			while( temp != last )
			{
				insert( iterator( this->m_tail, temp->current->data ) );
				++temp;
			}
		}

		void assign( std::initializer_list<T> ilist )
		{
			erase( iterator(this->m_head), iterator(this->m_tail) ); //< Limpa a lista
			for( auto i: ilist )
			{
				insert( this->m_tail, i );
			}
		}
		
		const_iterator find( const T & value ) const
		{
			const_iterator it( this->m_head );
			for( size_type i = 1; i <= this->m_size; ++i)
			{
				if( it->current->data == value ) return it;
			}
			return it;
		}
	
		iterator find( const T & value )
		{
			iterator it( this->m_head );
			for( size_type i = 1; i <= this->m_size; ++i)
			{
				if( it->current->data == value ) return it;
				++it;
			}
			return it;
		}

		bool operator==( const list & rhs )
		{
			if(this->empty() && rhs.empty()) return true;
			if( this->m_size == rhs->m_size )
			{
				iterator itLHS(this->m_head);
				iterator itRHS(rhs->m_head);
				for ( size_type  i = 1; i <= this->m_size; ++i)
				{
					if( itLHS->current->data != itRHS->current->data ) return false;
					++itLHS;
					++itRHS;
				}
			}

			return true;
		}

		bool operator!=( const list & rhs )
		{
			if(this->empty() && rhs.empty()) return true;
			if( this->m_size == rhs->m_size )
			{
				iterator itLHS(this->m_head);
				iterator itRHS(rhs->m_head);
				for ( size_type  i = 1; i <= this->m_size; ++i)
				{
					if( itLHS->current->data != itRHS->current->data ) return true;
					++itLHS;
					++itRHS;
				}
				return false;
			}

			return true;
		}

	private:
		size_type m_size;
		Node * m_head;
		Node * m_tail;

		//== Function

		/**
		 * @brief      iniciar os atributos para usar os construtores
		 */
		void iniciar_list()
		{
			this->m_head = nullptr;
			this->m_tail = nullptr;
			this->m_size = 0;
		}
	};
};

#endif