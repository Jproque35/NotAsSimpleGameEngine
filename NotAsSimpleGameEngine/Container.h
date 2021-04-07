#ifndef CONTAINER_H
#define CONTAINER_H
#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

template <class T> 
class Container {

private:
	vector<T*> m_Arr;
	queue<T*> m_DeletionList;
	unordered_map<int, int> m_IdMap;
	int m_Size;

	Container() = delete;
	Container(const Container& other) = delete;
	Container& operator=(const Container& rhs) = delete;

public:
	Container(int size);
	~Container();

	int size() inline const;
	void add(T& obj, int id);
	T& get(int id) inline const;
	void erase(int id);
	void cleanUp();

};

#endif

