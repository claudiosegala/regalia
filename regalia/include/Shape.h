#pragma once

#include <pch.h>

class Shape {
public:

	virtual void Start();

	virtual bool Is(std::string) = 0;

};