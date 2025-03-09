//shader vertex
#version 430 core
layout(location = 0) in vec4 aPos;

uniform mat4 modelMatrix;

void main()
{
	gl_Position = modelMatrix * aPos;
}


//shader fragment
#version 430 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(0.5, 0.3, 0.8, 1.0);
}
