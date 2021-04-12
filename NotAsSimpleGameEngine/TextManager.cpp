#include "TextManager.h"
#include <iostream>

TextManager* TextManager::instance = NULL;

TextManager::TextManager() :
	m_CurrFreeId(0) {
	for (int i = 0; i < 128; ++i) {
		this->m_Texts[i] = NULL;
	}
}

TextManager::~TextManager() {
	cout << "TextManager: Deleting TextManager..." << endl;
	for (int i = 0; i < 128; ++i) {
		if (this->m_Texts[i]) {
			delete(this->m_Texts[i]);
			cout << "TextManager: Deleted text with id " << i << endl;
		}

		this->m_Texts[i] = NULL;
	}
}

void TextManager::add(Text& text) {
	this->m_Texts[m_CurrFreeId++] = &text;
	cout << "TextManager: Successfully added text object. New size is now " << this->m_CurrFreeId << endl;
}

Text& TextManager::get(int id) const {
	try {
		return *this->m_Texts[id];
	}
	catch (exception& e) {
		cout << "TextManager: Text with id " << id << " does not exist!" << endl;
	}
}

int TextManager::size() const {
	return this->m_CurrFreeId;
}