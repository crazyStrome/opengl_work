#pragma once

#include "events/Event.h"

#include <glm/glm.hpp>

struct LayerUpdateArgs {
	glm::mat4 view;
	glm::mat4 projection;
	int windowWidth;
	int windowHeight;
	float nearZpos;
	float farZpos;
};

class Layer {
public:
	virtual void OnEvent(Event&) {};
	virtual void OnUpdate(const LayerUpdateArgs&) {};
	virtual ~Layer() {}
};
