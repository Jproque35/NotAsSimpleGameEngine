#include "PongBlockManager.h"
#include "PongBlock.h"

PongBlockManager* PongBlockManager::instance = NULL;

PongBlockManager::PongBlockManager() : 
	m_AmountFree(maxSize) {
	for (int i = 0; i < maxSize; ++i) {
		this->m_Blocks[i] = new PongBlock();
	}

	this->deactivateAll();
}

PongBlockManager::~PongBlockManager() {
	cout << "BlockManager: Deleting BlockManager..." << endl;
}

PongBlock& PongBlockManager::getFreeBlock() {
	try {
		PongBlock* desire = this->m_FreeBlock;
		this->m_FreeBlock = &desire->getNext();
		--this->m_AmountFree;
		return *desire;
	}
	catch (exception& e) {
		cout << "PongBlockManager: No free block exists" << endl;
	}
}

void PongBlockManager::addFreeBlock(PongBlock& block) {
	block.setActive(false);
	block.setNext(this->m_FreeBlock);
	this->m_FreeBlock = &block;
	++this->m_AmountFree;
}

void PongBlockManager::deactivateAll() {
	for (int i = 0; i < maxSize - 1; ++i) {
		this->m_Blocks[i]->setActive(false);
		this->m_Blocks[i]->setNext(this->m_Blocks[i + 1]);
		//cout << "BlockManager: Block with id " << i << " is " << this->m_Blocks[i]->isActive() << endl;
		//cout << "BlockManager: Next for block with id " << i << " set to " << i + 1 << endl;
	}

	this->m_AmountFree = maxSize;
	this->m_Blocks[maxSize - 1]->setNext(NULL);
	this->m_FreeBlock = this->m_Blocks[0];
}