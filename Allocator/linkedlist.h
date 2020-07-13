#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

template<class T> class LinkedList
{
public:
	struct Node
	{
		T data;
		Node* next;
	};

	Node* head{ nullptr };

	LinkedList() = default;
	LinkedList(LinkedList& list) = delete;

	void Insert(Node* nNode, Node* pNode = nullptr);
	void Remove(Node* dNode, Node* pNode = nullptr);
};

template <class T>
void LinkedList<T>::Insert(Node* nNode, Node* pNode)
{
	if (pNode == nullptr) 
	{
		if (head != nullptr)
		{
			nNode->next = head;
		}
		else
		{
			nNode->next = nullptr;
		}
		head = nNode;
	}
	else
	{
		if (pNode->next == nullptr) 
		{
			pNode->next = nNode;
			nNode->next = nullptr;
		}
		else 
		{
			nNode->next = pNode->next;
			pNode->next = nNode;
		}
	}
}

template <class T>
void LinkedList<T>::Remove(Node* dNode, Node* pNode)
{
	if (pNode == nullptr) 
	{
		if (dNode->next == nullptr)
		{
			head = nullptr;
		}
		else 
		{
			head = dNode->next;
		}
	}
	else 
	{
		pNode->next = dNode->next;
	}
}
#endif //_LINKEDLIST_H_
