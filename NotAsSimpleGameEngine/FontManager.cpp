#include "FontManager.h"
#include <iostream>
#include <sstream>

FontManager* FontManager::instance = NULL;

FontManager::FontManager() :
	m_CurrFreeId(0) {}

FontManager::~FontManager() {
	cout << "***FontManager: Deleting FOntManager..." << endl;
}

void FontManager::loadFile(const string& filename) {
	int currId = m_CurrFreeId++;
	this->m_IdMap[filename] = currId;

	ostringstream ss;
	ss << "assets/fonts/" << filename << ".ttf";
	this->m_Fonts[currId].loadFromFile(ss.str());

	cout << "FontManager: Loaded from file " << filename << endl;
}

Font& FontManager::get(const string& filename) {
	return this->m_Fonts[this->m_IdMap[filename]];
}