#include "CompactVector.h"

template<class T>
CompactVector<T>::CompactVector(int size)
	: m_Size(0) {

	cout << "Creating CompactVector of size " << size << endl;

	this->m_Arr.resize(size);

	for (int i = 0; i < this->m_Arr.size(); ++i) {
		this->m_Arr[i] = NULL;
	}

	for (int i = this->m_Arr.size() - 1; i >= 0; --i) {
		this->m_FreeIds.push(i);
	}

	cout << "Successfully created CompactVector of size " << this->m_Arr.size() << endl;

}

template<class T>
CompactVector<T>::~CompactVector() {
	cout << "CompactVector: Deleting CompactVector..." << endl;

	/*
	for (int i = 0; i < this->m_Arr.size(); ++i) {
		cout << this->m_Arr[i] << endl;
	}*/

	for (int i = 0; i < this->m_Arr.size(); ++i) {
		if (this->m_Arr[i]) {
			//cout << "CompactVector: Deleted item " << this->m_Arr[i] << endl;
			delete(this->m_Arr[i]);
		}

		this->m_Arr[i] = NULL;
	}

	this->cleanUp();
}

template<class T>
int CompactVector<T>::size() inline const {
	return this->m_Size;
}

template<class T>
int CompactVector<T>::add(T& obj) {
	cout << "CompactVector: Adding item to CompactVector..." << endl;

	int id = -1;

	//cout << this->m_IdMap.find(&obj) << endl;

	if (this->m_IdMap.find(&obj) == this->m_IdMap.end()) {
		id = this->m_FreeIds.top();
		this->m_FreeIds.pop();
		this->m_Arr[id] = &obj;
		this->m_IdMap[&obj] = id;
		++this->m_Size;

		cout << "CompactVector: Item successfully added to Compact Vector." << endl;
	}
	else {
		id = this->m_IdMap[&obj];
		cout << "CompactVector: Already contains object. Returning existing id." << endl;
	}

	cout << "CompactVector: Size is " << this->m_Size << endl;

	return id;
}

template<class T>
T& CompactVector<T>::get(int id) inline const {
	try {
		return *this->m_Arr[id];
	}
	catch (exception& e) {
		cout << "CompactVector: Object does not exist!" << endl;
	}
}

template<class T>
void CompactVector<T>::erase(int id) {
	T* desire = this->m_Arr[id];

	if (desire) {
		//cout << "CompactVector: Marking item for deletion..." << endl;
		this->m_Arr[id] = NULL;
		this->m_FreeIds.push(id);
		this->m_DeletionList.push(desire);
		this->m_IdMap.erase(desire);
		--this->m_Size;
		//cout << "CompactVector: Previous spot is now " << this->m_Arr[id] << endl;
	}
}

template<class T>
void CompactVector<T>::cleanUp() {
	while (this->m_DeletionList.size() > 0) {
		//cout << "CompactVector: Deleted item from CompactVector" << endl;
		T* currObj = this->m_DeletionList.front();
		//cout << "CompactVector: Deleting item " << currObj << endl;
		this->m_DeletionList.pop();
		delete(currObj);
		currObj = NULL;
	}
}