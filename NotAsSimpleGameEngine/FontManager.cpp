#include "FontManager.h"
#include <iostream>

FontManager* FontManager::instance = NULL;

FontManager::FontManager() :
	m_CurrFreeId(0) {}

FontManager::~FontManager() {
	cout << "***FontManager: Deleting FOntManager..." << endl;
}

void FontManager::loadFile(const string& filename) {
	int currId = m_CurrFreeId++;

	this->m_IdMap[filename] = currId;
	this->m_Fonts[currId].loadFromFile(filename);

	cout << "FontManager: Loaded from file " << filename << endl;
}

Font& FontManager::get(const string& filename) {
	return this->m_Fonts[this->m_IdMap[filename]];
}