#include "SoundFileManager.h"
#include <iostream>
#include <sstream>

SoundFileManager* SoundFileManager::instance = NULL;

SoundFileManager::SoundFileManager() :
	m_CurrFreeId(0) {}

SoundFileManager::~SoundFileManager() {
	cout << "***SoundFileManager: Deleting SoundFileManager..." << endl;
}

void SoundFileManager::loadFile(const string filename) {
	int currId = this->m_CurrFreeId++;
	ostringstream ss;
	ss << "assets/sounds/" << filename;

	this->m_IdMap[filename] = currId;

	this->m_Bufs[currId].loadFromFile(ss.str());

	cout << "SoundFileManager: Loaded file " << ss.str() << endl;
}

SoundBuffer& SoundFileManager::get(const string filename) {
	return this->m_Bufs[this->m_IdMap[filename]];
}