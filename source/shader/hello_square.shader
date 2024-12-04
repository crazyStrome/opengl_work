#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 ourCoord;

void main()
{
	gl_Position = vec4(aPos.xyz, 1.0);
	ourCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec2 ourCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourMatrix;

uniform float yOffset;

void main()
{
	FragColor = mix(texture(ourTexture, ourCoord), 
		texture(ourMatrix, vec2(ourCoord.x, ourCoord.y+yOffset)), 0.8);
}