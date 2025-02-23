#pragma once

#include <vector>

#include "layers/Layer.h"

class LayerStack {
	using LayerIterator = std::vector<Layer*>::const_iterator;
private:
	std::vector<Layer*> mLayers;
public:
	void PushLayer(Layer*);
	void PopLayer();

	LayerIterator Begin() const;
	LayerIterator End() const;
};

