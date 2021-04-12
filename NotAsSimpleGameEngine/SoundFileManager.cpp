#include "SoundFileManager.h"
#include <iostream>

SoundFileManager* SoundFileManager::instance = NULL;

SoundFileManager::SoundFileManager() :
	m_CurrFreeId(0) {}

SoundFileManager::~SoundFileManager() {
	cout << "***SoundFileManager: Deleting SoundFileManager..." << endl;
}

void SoundFileManager::loadFile(const string filename) {
	int currId = this->m_CurrFreeId++;

	this->m_IdMap[filename] = currId;
	this->m_Bufs[currId].loadFromFile(filename);

	cout << "SoundFileManager: Loaded file " << filename << endl;
}

SoundBuffer& SoundFileManager::get(const string filename) {
	return this->m_Bufs[this->m_IdMap[filename]];
}