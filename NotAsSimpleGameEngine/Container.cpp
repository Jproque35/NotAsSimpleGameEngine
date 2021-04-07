#include "Container.h"

template<class T>
Container<T>::Container(int size)
	: m_Size(0) {}

template<class T>
Container<T>::~Container() {
	cout << "CompactVector: Deleting Container..." << endl;

	
	for (int i = 0; i < this->m_Arr.size(); ++i) {
		if (this->m_Arr[i]) {
			delete(this->m_Arr[i]);
		}

		this->m_Arr[i] = NULL;
	}
	
	this->cleanUp();
}

template<class T>
int Container<T>::size() inline const {
	return this->m_Size;
}

template<class T>
void Container<T>::add(T& obj, int id) {
	this->m_Arr.push_back(&obj);
	this->m_IdMap[id] = this->m_Arr.size() - 1;
	++this->m_Size;
}

template<class T>
T& Container<T>::get(int id) inline const {
	try {
		return *this->m_Arr[this->m_IdMap.at(id)];
	}
	catch (exception& e) {
		cout << "CompactVector: Object does not exist!" << endl;
	}
}

template<class T>
void Container<T>::erase(int id) {
	int idx = this->m_IdMap[id];
	T* obj = this->m_Arr[idx];
	this->m_Arr.erase(this->m_Arr.begin() + idx);
	this->m_DeletionList.push(obj);
	this->m_IdMap.erase(id);
	--this->m_Size;

	for (int i = 0; i < this->m_Arr.size(); ++i) {
		this->m_IdMap[ this->m_Arr[i] ] = i;
	}
}

template<class T>
void Container<T>::cleanUp() {
	while (this->m_DeletionList.size() > 0) {
		T* currObj = this->m_DeletionList.front();
		this->m_DeletionList.pop();
		delete(currObj);
		currObj = NULL;
	}
}