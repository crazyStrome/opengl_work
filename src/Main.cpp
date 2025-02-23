#include "Application.h"

#include "layers/CubeLayer.h"

int main() {
	// Window ���ƴ���
	// Application ���� Window�������� Window ˢ��
	// Application ��Ⱦ Layer
	// Application ���� Camera�������ӽǡ�͸�Ӿ���
	Application application;

	CubeLayer cubeLayer;
	application.AddLayer(&cubeLayer);
	application.Run();
	return 0;
}