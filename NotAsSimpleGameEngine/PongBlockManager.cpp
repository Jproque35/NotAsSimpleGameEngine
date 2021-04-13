#include "PongBlockManager.h"
#include "PongBlock.h"

PongBlockManager* PongBlockManager::instance = NULL;

PongBlockManager::PongBlockManager() : 
	m_AmountFree(maxSize) {
	for (int i = 0; i < maxSize; ++i) {
		this->m_Blocks[i] = new PongBlock();
	}

	for (int i = 0; i < maxSize - 1; ++i) {
		this->m_Blocks[i]->setNext( this->m_Blocks[i + 1] );
		cout << "BlockManager: Next for block with id " << i << " set to " << i + 1 << endl;
	}

	this->m_FreeBlock = this->m_Blocks[0];
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