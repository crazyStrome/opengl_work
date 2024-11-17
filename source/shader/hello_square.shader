#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

void main()
{
	gl_Position = vec4(aPos.xyz, 1.0);
	ourColor = aColor;
}

#shader fragment
#version 330 core
in vec4 ourColor;
out vec4 FragColor;

void main()
{
	FragColor = ourColor;
}