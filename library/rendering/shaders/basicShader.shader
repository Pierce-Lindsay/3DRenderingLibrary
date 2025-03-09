//shader vertex
#version 430 core
layout(location = 0) in vec4 aPos;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform mat4 cameraMatrix;

void main()
{
	gl_Position = projMatrix * cameraMatrix * modelMatrix * aPos;
}


//shader fragment
#version 430 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(0.5, 0.3, 0.8, 1.0);
}
