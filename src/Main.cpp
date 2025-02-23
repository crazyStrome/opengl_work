#include "Application.h"

#include "layers/CubeLayer.h"

int main() {
	// Window 控制窗口
	// Application 持有 Window，并控制 Window 刷新
	// Application 渲染 Layer
	// Application 持有 Camera，控制视角、透视矩阵
	Application application;

	CubeLayer cubeLayer;
	application.AddLayer(&cubeLayer);
	application.Run();
	return 0;
}