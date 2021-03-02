//--------------------------------------------------------------------
//
//  Laboratory 6                                        queueLnk.cpp
//
//  SOLUTION: Linked list implementation of the Queue ADT
//
//--------------------------------------------------------------------

#include <assert.h>
#include <iostream>
#include "queueLnk.h"

//--------------------------------------------------------------------

template < class QE >
QueueNode<QE>::QueueNode(const QE &elem, QueueNode<QE> *nextPtr)

// Creates a queue node containing element elem and next pointer
// nextPtr.
{
	element = elem;
	next = nextPtr;
}

template < class QE >
QueueNode<QE>::QueueNode()
{}

template<class QE>
QueueNode<QE>::QueueNode(QueueNode & qn) {
	element = qn.element;
	next = qn.next;
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>::Queue(int ignored)

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.

	: front(0),
	rear(0)
{
	front = NULL;
	rear = NULL;
}

//--------------------------------------------------------------------

template < class QE >
Queue<QE>:: ~Queue()

// Frees the memory used by a queue.

{
	delete[] front;
	delete[] rear;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::enqueue(const QE &newElement)

// Inserts newElement at the rear of a queue.

{
	// 생성자를 통해 노드 생성
	QueueNode<QE>* location
		= new QueueNode<QE>(newElement, nullptr);

	// 메모리 할당 가능
	if (location != NULL) {
		// 항상 rear의 next에 enqueue된다.

		// 노드가 비어있을 때,
		if (Queue<QE>::empty()) {
			front = location;
			rear = location;
		}

		// 노드가 1개 이상 있을 때,
		else {
			rear->next = location;
			rear = rear->next;
		}

	}
	// 메모리 할당 불가능
	else std::cout << "full Memory, can't enqueue!" << std::endl;
}

//--------------------------------------------------------------------

template < class QE >
QE Queue<QE>::dequeue()

// Removes the least recently (front) element from a queue and
// returns it.

{
	// 큐가 비어있는 경우
	if (Queue<QE>::empty()) std::cout << "Queue is empty, can't dequeue!" << std::endl;
	else {
		QE temp = front->element;
		// front랑 rear와 같은 경우 : 자료가 하나일 경우
		if (front == rear) Queue<QE>::clear();
		else front = front->next;

		return temp;
	}
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::clear()

// Removes all the elements from a queue.

{
	front = nullptr;
	rear = nullptr;
}


//--------------------------------------------------------------------

template < class QE >
int Queue<QE>::empty() const

// Returns 1 if a queue is empty. Otherwise, returns 0.

{
	if (front == nullptr && rear == nullptr) return 1;
	else return 0;
}

template < class QE >
int Queue<QE>::full() const

// Returns 1 if a queue is full. Otherwise, returns 0.

{
	QueueNode* temp = new QueueNode();
	if (!temp) return 1;
	else return 0;
}

template < class QE >
QE Queue<QE>::getFront() const
{
	return front->element;
}

//--------------------------------------------------------------------

template < class QE >
void Queue<QE>::showStructure() const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
	// 노드가 비어있는 경우
	if (Queue<QE>::empty()) std::cout << "Empty queue" << std::endl;
	// 노드가 1개 이상인 경우
	else {
		QueueNode<QE>* temp = front;

		for (; temp != rear->next; temp = temp->next) {
			std::cout << temp->element << '\t';
		}
	}
}