#ifndef COMMAND_H
#define COMMAND_H
#pragma once
#include <SFML/Graphics.hpp>

class Command {
public:
	virtual void execute(float dtAsSeconds) = 0;
};

#endif
