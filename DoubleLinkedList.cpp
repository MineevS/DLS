#include "DoubleLinkedList.h"
#include <iostream>
#include <cassert>

DoubleLinkedList::Node::Node(const ValueType& value, Node* next, Node* prev)
{//+
	this->value = value;
	this->next = next;
	this->prev = prev;
}

DoubleLinkedList::Node::~Node()
{//+
	// ничего не удаляем, т.к. агрегация
}

void DoubleLinkedList::Node::insertNext(const ValueType& value)
{//+
	Node* newNode = new Node(value, this->next, this->prev);
	this->next = newNode;
	newNode->prev = this;
}

void DoubleLinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

DoubleLinkedList::DoubleLinkedList()
	: _head(nullptr), _size(0)
{//+
	//Создаем лист по умолчанию.
}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentNode->next = new Node(currentCopyNode->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	DoubleLinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;

	return *this;
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

DoubleLinkedList::~DoubleLinkedList()
{//+
	//forceNodeDelete(_head);
}

ValueType& DoubleLinkedList::operator[](const size_t pos) const
{//+
	return getNode(pos)->value;
}

DoubleLinkedList::Node* DoubleLinkedList::getNode(const size_t pos) const
{//+
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void DoubleLinkedList::insert(const size_t pos, const ValueType& value)
{//+
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos-1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void DoubleLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
}

void DoubleLinkedList::pushBack(const ValueType& value)
{//+
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void DoubleLinkedList::pushFront(const ValueType& value)
{//+
	_head = new Node(value, this->_head, this->_head);
	++_size;
}

void DoubleLinkedList::remove(const size_t pos)
{//+
    if (pos == 0)
    {
        removeFront();
    }
    else
    {
		Node* bufNode = this->_head;

			for (size_t i = 0; i < pos-1; ++i)
			{
				bufNode = bufNode->next;
			}

		Node* removeNode = bufNode->next;
		bufNode->next = removeNode->next;
		delete removeNode;
		_size--;
    }
}

void DoubleLinkedList::removeFront()
{
    Node* removeNode = this->_head;
    this->_head =  _head->next;

    delete removeNode;
    _size--;

}

void DoubleLinkedList::removeBack()
{
    remove(_size - 1);
}

void DoubleLinkedList::removeNextNode(Node* node)
{
    node->removeNext();
}

long long int DoubleLinkedList::findIndex(const ValueType& Ivalue) const
{
    Node* bufNode = this->_head;

    for(int i = 0; i < _size; ++i)
    {
        if(Ivalue == bufNode->value)
		{
            return i;
		}
        else
		{
			bufNode = bufNode->next;
		}
    }
    
	std::cout << "ERROR ";
    
	return 0;
}

DoubleLinkedList::Node* DoubleLinkedList::findNode(const ValueType& Ivalue) const
{
    Node* bufNode = this->_head;

    for(int i = 0; i < _size; ++i)
    {
        if(Ivalue == bufNode->value)
            return bufNode;
        else
        bufNode = bufNode->next;
    }
    std::cout << "ERROR ";

	return nullptr;
}

void DoubleLinkedList::reverse()
{//+
	
	Node *reversedNode = nullptr;

    while(this->_head != nullptr)
    {
        Node *temp = _head->next;
        _head->next = reversedNode;
        reversedNode = _head;
        _head = temp;
    }
    
	_head = reversedNode;

/*
	Node *temp = this->_head;
	
	this->_head = _head->next;
	
	_head->next = temp;
	*/
	
	/*
	while(this->_head->value < this->_head->next->value)
	{
		
		int Ivalue = this->_head->value;
	
		this->_head->value = this->_head->next->value;

		this->_head->next->value = Ivalue;
	}
	*/
	
	/*
    Node *reversedNode = nullptr;
	
	Node *temp = _head;

	while(temp != nullptr)
	{
		reversedNode = temp->prev;
		temp->prev = temp->next;
		temp->next = temp;
		temp = temp->prev;
	}
	
	if(temp != nullptr)
	{
		_head = reversedNode->prev;
	}
	*/

/*
	Node *reversedNode = nullptr;
	
    while(this->_head != nullptr)
    {
        Node *temp = _head->next;
        _head->next = reversedNode;
        reversedNode = _head;
        _head = temp;
		_head->next = reversedNode;
		_head->prev = temp;
    }
   
   _head = reversedNode;
	*/
	
}

DoubleLinkedList DoubleLinkedList::reverse() const
{//+
	DoubleLinkedList reversed = (*this);
	reversed.reverse();

	return reversed;
}

DoubleLinkedList DoubleLinkedList::getReverseList() const
{
	DoubleLinkedList reversed (*this);
	reversed.reverse();

	return reversed;
}

size_t DoubleLinkedList::size() const
{
	return _size;
}

void DoubleLinkedList::forceNodeDelete(Node* node)
{
	if (node == node->next)
    {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}