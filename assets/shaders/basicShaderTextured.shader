//shader vertex
#version 430 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 texCoord;
layout (location = 2) in mat4 instanceModel;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform mat4 cameraMatrix;
uniform bool isInstanced;

out vec2 f_texCoord;

void main()
{
	if(!isInstanced)
		gl_Position = projMatrix * cameraMatrix * modelMatrix * aPos;
	else
		gl_Position = projMatrix * cameraMatrix * modelMatrix * instanceModel * aPos;

	f_texCoord = texCoord;
}


//shader fragment
#version 430 core
out vec4 FragColor;
in vec2 f_texCoord;
uniform vec4 uColor;
uniform sampler2D tex0;

void main()
{
	FragColor = uColor * 0.25 + 0.75 * texture(tex0, f_texCoord);
	//FragColor = uColor;
}
