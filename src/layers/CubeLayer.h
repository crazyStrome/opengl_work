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
	Shader mBorderShader;
	Texture2D mTexture;
	Texture2D mMatrix;

	double mLast;
	float mCursorXpos;
	float mCursorYpos;

	void OnEventCursorPosition(EventCursorPosition&);
public:
	void OnEvent(Event&) override;
	void OnUpdate(const LayerUpdateArgs&) override;

	CubeLayer();
	~CubeLayer();
};
