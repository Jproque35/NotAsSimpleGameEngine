#include "CollisionList.h"
#include "CollisionListNode.h"
#include "Collider.h"

int CollisionList::size() const {
	return this->m_Size;
}

void CollisionList::push_front(CollisionListNode& node) {
	if (this->m_Size <= 0) {
		this->m_Head = &node;
		this->m_Tail = &node;
	}
	else {
		CollisionListNode* prevHead = this->m_Head;
		node.setNext(prevHead);
		prevHead->setPrev(&node);
		this->m_Head = &node;
	}

	++this->m_Size;
}

void CollisionList::push_back(CollisionListNode& node) {
	if (this->m_Size <= 0) {
		this->m_Head = &node;
		this->m_Tail = &node;
	}
	else {
		CollisionListNode* prevTail = this->m_Tail;
		node.setPrev(prevTail);
		prevTail->setNext(&node);
		this->m_Tail = &node;
	}

	++this->m_Size;
}

void CollisionList::sort() {

	CollisionListNode* currNode = this->m_Head;

	if (this->m_Head->getNext()) {
		currNode = currNode->getNext();

		while (currNode) {
			CollisionListNode* prevNode = currNode->getPrev();

			while (currNode->getValue() < prevNode->getValue()
				&& prevNode->getPrev()) {
				prevNode = prevNode->getPrev();
			}

			if (prevNode->getPrev()) {
				currNode->setPrev(prevNode);
				currNode->setNext(prevNode->getNext());
				currNode->getPrev()->setNext(currNode);
				currNode->getNext()->setPrev(currNode);
			}
			else {
				this->m_Head = currNode;
				prevNode->setPrev(currNode);
				currNode->setNext(prevNode);
				currNode->setPrev(NULL);
			}
		}
	}
}