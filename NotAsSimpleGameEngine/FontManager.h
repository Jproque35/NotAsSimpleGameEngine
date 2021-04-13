#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;

class FontManager final {
private:
	static const int maxSize = 128;
	static FontManager* instance;
	unordered_map<string, int> m_IdMap;
	Font m_Fonts[maxSize];
	int m_CurrFreeId;

	FontManager();
	FontManager(const FontManager& other) = delete;
	FontManager& operator=(const FontManager& rhs) = delete;
	~FontManager();

public:
	static FontManager* getInstance() {
		if (!instance) {
			instance = new FontManager();
		}

		return instance;
	}

	static void resetInstance() {
		if (instance) {
			delete(instance);
		}

		instance = NULL;
	}

	void loadFile(const string& filename);
	Font& get(const string& fillename);

};

#endif

