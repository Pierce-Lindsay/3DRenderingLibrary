//shader vertex
#version 430 core
layout(location = 0) in vec4 aPos;
layout (location = 1) in mat4 instanceModel;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform mat4 cameraMatrix;
uniform bool isInstanced;

void main()
{
	if(!isInstanced)
		gl_Position = projMatrix * cameraMatrix * modelMatrix * aPos;
	else
		gl_Position = projMatrix * cameraMatrix * modelMatrix * instanceModel * aPos;
}


//shader fragment
#version 430 core
out vec4 FragColor;
uniform vec4 uColor;

void main()
{
	FragColor = uColor;
}
