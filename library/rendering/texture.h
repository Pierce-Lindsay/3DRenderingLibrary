#pragma once
#include "../rendererEssentials.h"
#include <string>
#include <unordered_map>


//for right now, only 1 texture object can be created per texture path

class Texture
{
private:


	std::string imageName;
	std::string imagePath;

 //image data
	unsigned char * imageData;
	int width;
	int height;
	int numChannels;

	unsigned int TEXid;

	//statics

	static std::unordered_map <std::string, Texture> textureMap;


	std::string getPathFromName(std::string& name);

	static bool checkIfTextureExistsInMap(const std::string& textureName);

public:

	Texture(std::string imageName);
	Texture();
	void initTexture();
	void loadTexture();
	unsigned int getTextureID();

	static void initTextures();
	static void addTextureIfNotExists(std::string textureName);
	static Texture* getTexture(std::string name);


};
