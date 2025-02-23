#pragma once

#include "Layer.h"

#include "renderer/Renderer.h"

class CubeLayer : public Layer {
private:
	VertexBuffer mVertexBuffer;
	VertexBuffer mTextureBuffer;
	IndexBuffer mIndexBuffer;
	VertexArray mVertexArray;

	Shader mShader;
	Texture2D mTexture;
	Texture2D mMatrix;

	double mLast;
public:
	//void OnEvent(Event&) override;
	void OnUpdate(const LayerUpdateArgs&) override;

	CubeLayer();
	~CubeLayer();
};
