#ifndef COMPACTVECTOR_H
#define COMPACTVECTOR_H
#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

template <class T> 
class CompactVector {

private:
	vector<T*> m_Arr;
	queue<T*> m_DeletionList;
	stack<int> m_FreeIds;
	unordered_map<T*, int> m_IdMap;
	int m_Size;

	CompactVector() = delete;
	CompactVector(const CompactVector& other) = delete;
	CompactVector& operator=(const CompactVector& rhs) = delete;

public:
	CompactVector(int size);
	~CompactVector();

	int size() inline const;
	int add(T& obj);
	T& get(int id) inline const;
	void erase(int id);
	void cleanUp();

};

#endif

