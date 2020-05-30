#pragma once
#include <iostream>
// потом поменяем на шаблоны
using ValueType = double;

class DoubleLinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList
	// (доступ по ключу, поиск по ключу и т.д.)
	
	struct Node
	{
		Node(const ValueType& value, Node* next = nullptr, Node* prev = nullptr); //сделано
		~Node(); //сделано

		void insertNext(const ValueType& value); //сделано
		void removeNext(); //сделано

		ValueType value;
		Node* next;
		Node* prev;
	};

	public:
		////
		DoubleLinkedList();  //сделано
		DoubleLinkedList(const DoubleLinkedList& copyList);  //сделано
		DoubleLinkedList& operator=(const DoubleLinkedList& copyList); //сделано

		DoubleLinkedList(DoubleLinkedList&& moveList) noexcept; //сделано
		DoubleLinkedList& operator=(DoubleLinkedList&& moveList) noexcept; //сделано

		~DoubleLinkedList();  //сделано
		////

		// доступ к значению элемента по индексу
		ValueType& operator[](const size_t pos) const; //сделано
		// доступ к узлу по индексу
		DoubleLinkedList::Node* getNode(const size_t pos) const; //сделано

		// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
		void insert(const size_t pos, const ValueType& value); //сделано
		// вставка элемента после узла, (O(1))
		static void insertAfterNode(Node* node, const ValueType& value); //сделано
		// вставка в конец (О(n))
		void pushBack(const ValueType& value); //сделано
		// вставка в начало (О(1))
		void pushFront(const ValueType& value); //сделано

		// удалениеNode
		void remove(const size_t pos);
		void removeNextNode(Node* node);
		void removeFront();//+
		void removeBack();//+

		// поиск, О(n)
		long long int findIndex(const ValueType& value) const;
		Node* findNode(const ValueType& Ivalue) const;

		// разворот списка
		void reverse();						// изменение текущего списка
		DoubleLinkedList reverse() const;			// полчение нового списка (для константных объектов)
		DoubleLinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

		size_t size() const;
		
		private:
			
			Node*	_head;
			size_t	_size;

			void forceNodeDelete(Node* node); //сделано
};

