#ifndef PONGBLOCKMANAGER_H
#define PONGBLOCKMAANGER_H
#pragma once
#include <cstdlib>

class PongBlock;

class PongBlockManager final {
private:
	static PongBlockManager* instance;
	static const int maxSize = 40;
	PongBlock* m_Blocks[maxSize];
	PongBlock* m_FreeBlock;
	int m_AmountFree;

	PongBlockManager();
	~PongBlockManager();
	PongBlockManager(const PongBlockManager& rhs) = delete;
	PongBlockManager& operator=(const PongBlockManager& rhs) = delete;

public:
	inline static PongBlockManager* getInstance() {
		if (!instance) {
			instance = new PongBlockManager();
		}

		return instance;
	}

	inline static void resetInstance() {
		if (instance) {
			delete(instance);
		}

		instance = NULL;
	}

	inline int getAmountFree() const {
		return this->m_AmountFree;
	}

	inline int getMaxSize() const {
		return maxSize;
	}

	PongBlock& getFreeBlock();
	void addFreeBlock(PongBlock& block);
	void deactivateAll();
};

#endif

