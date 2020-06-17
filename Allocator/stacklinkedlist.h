#ifndef _STACK_LINKED_LIST_H_
#define _STACK_LINKED_LIST_H_

template<class T>
class StackLinkedList
{
public:

	struct Node
	{
		T data;
		Node* next;
	};

	Node* head{nullptr};

	StackLinkedList() = default;
	StackLinkedList(StackLinkedList& list) = delete;

	void Push(Node* nNode);
	Node* Pop();

};

template<class T>
void StackLinkedList<T>::Push(Node* nNode)
{
	nNode->next = head;
	head = nNode;
}

template<class T>
typename StackLinkedList<T>::Node* StackLinkedList<T>::Pop()
{
	assert(head != nullptr && "End of allocated memory!");
	Node* tempNode = head;
	head = head->next;
	return tempNode;
}


#endif // _STACK_LINKED_LIST_H_


