#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace sf;
using namespace std;

class TextManager  final {
private:
	static const int maxSize = 128;
	static TextManager* instance;
	Text* m_Texts[maxSize];
	int m_CurrFreeId;

	TextManager();
	~TextManager();
	TextManager(const TextManager& other) = delete;
	TextManager& operator=(const TextManager& rhs) = delete;

public:
	inline static TextManager* getInstance() {
		if (!instance) {
			instance = new TextManager();
		}

		return instance;
	}

	inline static void resetInstance() {
		if (instance) {
			delete(instance);
		}

		instance = NULL;
	}

	void add(Text& text);
	Text& get(int id) const;
	int size() const;
};

#endif

