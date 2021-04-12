#ifndef SOUNDFILEMANAGER_H
#define SOUNDFILEMANAGER_H
#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class SoundFileManager {
private:
	static SoundFileManager* instance;
	unordered_map<string, int> m_IdMap;
	SoundBuffer m_Bufs[128];
	int m_CurrFreeId;

	SoundFileManager();
	SoundFileManager(const SoundFileManager& other) = delete;
	SoundFileManager& operator=(const SoundFileManager& rhs) = delete;
	~SoundFileManager();

public:
	inline static SoundFileManager* getInstance() {
		if (instance == NULL) {
			instance = new SoundFileManager();
		}

		return instance;
	}

	inline static void resetInstance() {
		if (instance) {
			delete(instance);
		}

		instance = NULL;
	}

	void loadFile(const string filename);
	SoundBuffer& get(const string filename);
};

#endif

