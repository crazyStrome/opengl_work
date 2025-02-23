#pragma once
#include <vector>
struct VertexAttribData {
	int size; // ��������
	unsigned int type; // �������ͣ�GL ö��
	bool normalized; // �Ƿ��׼��
	int offset; // ��ǰ���������ڶ�����ֽ�ƫ����
};

class VertexLayout {
private:
	std::vector<VertexAttribData> mAttribs;
	int mStride;
public:
	VertexLayout();
	template<typename T> void AddAttrib(int, bool);
	int GetStride() const { return mStride; }
	std::vector<VertexAttribData>::const_iterator Begin() const { return mAttribs.cbegin(); }
	std::vector<VertexAttribData>::const_iterator End() const { return mAttribs.cend(); }
};

class VertexBuffer {
private:
	unsigned int mVBO;
	VertexLayout mLayout;
public:
	VertexBuffer(float*, int);

	std::vector<VertexAttribData>::const_iterator Begin() const { return mLayout.Begin(); }
	std::vector<VertexAttribData>::const_iterator End() const { return mLayout.End(); }

	void SetLayout(const VertexLayout& layout) { mLayout = layout; }
	int GetStride() const { return mLayout.GetStride(); }

	void Bind() const;
	void UnBind() const;
};

class IndexBuffer {
private:
	unsigned int mIBO;
public:
	IndexBuffer(unsigned int*, int);

	void Bind() const;
	void UnBind() const;
};

