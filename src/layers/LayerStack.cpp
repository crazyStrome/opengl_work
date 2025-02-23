#include "layers/LayerStack.h"

void LayerStack::PushLayer(Layer* layer) {
	mLayers.push_back(layer);
}

void LayerStack::PopLayer() {
	mLayers.pop_back();
}

LayerStack::LayerIterator LayerStack::Begin() const {
	return mLayers.begin();
}

LayerStack::LayerIterator LayerStack::End() const {
	return mLayers.end();
}
