# Autores

Iury Lamonie - Turma 2
& 
Leonardo Igor - Turma 1

# 1. Introdução:

Este projeto contém a implementação de uma lista Abstract Data Type (ADT) baseada em uma lista duplamente encadeada.

# 2. Makefile/Compiling:

Verifica se o setup está configurado, caso contrario, fará um novo setup chamando "make dir" e compila. Ele chama "make all" internamente.

```
make
```

Você também pode passar argumentos para o compilador. Como o exemplo abaixo:
```
make args="-D something=212"
```
Para ativar o modo debug, faça:

```
make args="-D DEBUG"
```

Fará tods os diretórios de trabalho. Você pode fazer isso manualmente ou automaticamente se você usar "make".
```
make dir
```

Limpa todo o diretorio de trabalho, irá apagar todos os arquivos contidos em bin e docs
```
make clean
```

Fará a documentação para o projeto atual.
```
make doxy
```

Irá chamar "make clear" e "make dir"
```
make fresh
```

# 2.1 Constructors, Destructors, and Assignment
1(x) list( ); 
2(x) explicit list( size_type count ); 	
3() template< typename InputIt > list( InputIt first, InputIt last ); 
4(x)list( const list& other );
5(x) list( std::initializer_list<T> ilist );
6(x) ∼list( ); 
7(x) list& operator=( const list& other );
8(x) list& operator=( std::initializer_list<T> ilist );
# 2.2 Common operations to all list implementations
1(x) size_type size() const : return the number of elements in the container.
1(x) void clear() : remove (either logically or physically) all elements from the container.
1(x) bool empty() : returns true if the container contains no elements, and false otherwise.
1(x) void push_front( const T & value ) : adds value to the front of the list.
1(x) void push_back( const T & value ) : adds value to the end of the list.
1(x) void pop_back() : removes the object at the end of the list.
1(x) void pop_front() : removes the object at the front of the list.
1(x) const T & back() const : returns the object at the end of the list.
1(x) const T & front() const : returns the object at the beginning of the list.
1(x) void assign( const T & value ) : replaces the content of the list with copies of value value .
# 2.3 Operator overloading — non-member functions
(x) bool operator==( const Vector& lhs, const Vector& rhs );
(x) bool operator!=( const Vector& lhs, const Vector& rhs ;

# 3.1 Getting an iterator
iterator begin()
const_iterator begin() const
iterator end()
const_iterator end() const
# 3.2 Iterator operations
(x) const_iterator
operator++()
operator++( int )
operator==()
operator!=()
# 3.3 methods that require iterator (Section 3.3)
(a) insert() ×3 (9 credits);
(b) find() ×2 (6 credits);
(c) erase() ×2 (6 credits);