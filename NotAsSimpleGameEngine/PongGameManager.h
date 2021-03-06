#ifndef PONGGAMEMANAGER_H
#define PONGGAMEMANAGER_H
#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class PongBlockManager;
class PongBall;
class PongBlock;
class PongPaddle;

class PongGameManager final {
private:
	static PongGameManager* instance;
	PongBall* m_Ball;
	PongPaddle* m_Paddle;
	PongBlockManager* m_Blocks;
	Text* m_ScoreText;
	Text* m_CountdownText;
	Text* m_WinText;
	Text* m_LoseText;
	float m_StartCount;
	float m_SceneWidth;
	float m_SceneHeight;
	int m_Lives;

	PongGameManager();
	~PongGameManager();
	PongGameManager(const PongGameManager& other) = delete;
	PongGameManager& operator=(const PongGameManager& rhs) = delete;

public:
	inline static PongGameManager* getInstance() {
		if (!instance) {
			instance = new PongGameManager();
		}

		return instance;
	}

	inline static void resetInstance() {
		if (instance) {
			delete(instance);
		}

		instance = NULL;
	}

	inline void restStartCount() {
		this->m_StartCount = 3.0f;
	}

	inline float getStartCount() const {
		return this->m_StartCount;
	}

	inline PongBall& getBall() const {
		return *this->m_Ball;
	}

	inline PongPaddle& getPaddle() const {
		return *this->m_Paddle;
	}

	inline PongBlockManager& getBlocks() const {
		return *this->m_Blocks;
	}

	inline int getLives() const {
		return this->m_Lives;
	}

	inline void restLives() {
		this->m_Lives = 3;
	}

	inline void decrementLives() {
		--this->m_Lives;
	}

	void reset();
	void resetPaddleAndBall();
	void update(float dtAsSeconds);
};

#endif

