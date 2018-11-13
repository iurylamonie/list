#ifndef _LIST_H
#define _LIST_H

#include <initializer_list> //< std::initializer_list
#include <iostream>

using size_type = unsigned long;

namespace ls
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
			const_iterator(){ this->current = nullptr; }
			const Node & operator*() const
			{
				return *this->current;
			}
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
			const_iterator( Node * p ) : current( p ) {}
			friend class list< T >;
		};

		class iterator
		{
		public:
			iterator() : const_iterator() { /* Empty */ };
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

		protected:
			iterator( Node *p ) : const_iterator( p ) { /* Empty */ };
			friend class list<T>;
		};

		//== SPECIAL MEMBERs

		list(){ this->iniciar_list(); }
		
		explicit list( size_type count )
		{		
			this->iniciar_list();
			for( size_type i = 0; i < count; ++i)
			{
				this->push_back( T() ); //< Duvida
			}
		}

		template < typename InputIt >
		list( InputIt first, InputIt last )
		{
			this->iniciar_list();
			InputIt current = first; //< Aponta para o valor atual
			while( current != last )
			{
				this->push_back( *current ); //< Insere na ordem certa
			}
		}

		list( const list & other )
		{
			this->iniciar_list();
			Node * current = other.m_head; //< Aponta para o head da outra lista
			for( size_type i = 0; i <  other.m_size; ++i ) //< Percorre a outra lista 
			{
				this->push_back( current->data );
				current = current->next; //< Aponta o current para o proximo nó.
			}
		}

		list( std::initializer_list<T> ilist )
		{
			this->iniciar_list();
			for( auto value : ilist ) //< Percorre toda a lista de inicialização.
			{
				this->push_back( value );
			}
		}
		
		~list(){ this->clear(); }
		
		list & operator=( const list & other )
		{
			this->iniciar_list();
			Node * current = other.m_head; //< Aponta para o head da outra lista
			for( size_type i = 0; i <  other.m_size; ++i ) //< Percorre a outra lista 
			{
				this->push_back( current->data );
				current = current->next; //< Aponta o current para o proximo nó.
			}
			return *this;
		}

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
		void printList() //< Função para printar a list.
		{
			std::cout << "[ ";
			Node * current = this->m_head;
			for( size_type i = 1; i <= this->m_size; ++i )
			{
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << "] - Size: " << this->m_size << std::endl;
		}

		//== ITERATORS
		iterator begin();
		const_iterator cbegin() const;
		iterator end();
		const_iterator cend() const;

		//== Capacity

		size_type size() const { return this->m_size; }

		bool empty() const { return (this->m_size == 0); }

		//== MODIFIERS
		void clear(){ this->iniciar_list(); } 
		
		T & front() //< Alterar para trabalhar com begin 
		{ 
			/*if( !empty() )*/ return this->m_head->data; 
			//return T(); //< O que retonar
		}
		
		const T & front() const //< Alterar para trabalhar com cbegin
		{
			/*if( !empty() )*/ return this->m_head->data; 
			//return T(); //< O que retonar
		}
		
		T & back() //< Alterar para trabalhar com end
		{
			/*if( !empty() )*/ return this->m_tail->data; 
			//return T(); //< O que retonar
		}

		const T & back() const //< Alterar para trabalhar com cend
		{
			/*if( !empty() )*/ return this->m_tail->data; 
			//return T(); //< O que retonar
		}
		
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
		
		void assign( const T & value )
		{
			if( !empty() )
			{
				for( size_type i = 1; i < this->m_size; ++i )
				{
					/* empty */ //< Vai utilizar o insert;
				}
			}
		}

		//== MODIFIERS WITH ITERATORS
		template < class InItr >
		void assign( InItr first, InItr last );
		void assign( std::initializer_list<T> ilist );
		iterator insert( const_iterator itr, const T & value );
		iterator insert( const_iterator pos, std::initializer_list<T> ilist );
		iterator erase( const_iterator itr );
		iterator erase( const_iterator first, const_iterator last );
		const_iterator find( const T & value ) const;

	private:
		size_type m_size;
		Node * m_head;
		Node * m_tail;

		//== Function
		void iniciar_list() //< iniciar os atributos para usar os construtores
		{
			this->m_head = nullptr;
			this->m_tail = nullptr;
			this->m_size = 0;
		}
	};
};

#endif