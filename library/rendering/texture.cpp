#include "texture.h"
#include <iostream>
#include <filesystem>


std::unordered_map <std::string, Texture> Texture::textureMap;

Texture::Texture()
{

}
Texture::Texture(std::string imageName) : imageName{imageName}
{
    std::cout << "image Name: " << imageName << '\n';
    imagePath = getPathFromName(imageName);
    loadTexture();
}


void Texture::initTexture()
{

    glGenTextures(1, &TEXid);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TEXid);
    // setup filtering and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //actually add data to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    std::cout << "Texture: " << imageName << " Successfully setup" << '\n';

    //unbind
    glBindTexture(GL_TEXTURE_2D,0);
}
void Texture::loadTexture()
{
    std::cout << "loading texture with path: " << imagePath << '\n';
    imageData = stbi_load(imagePath.c_str(), &width, &height, &numChannels, 0);
    if (imageData)
        initTexture();
    else
        std::cout << "Failed to load texture" << '\n';
    //free data
    stbi_image_free(imageData);
}


std::string Texture::getPathFromName(std::string& name)
{
    std::string path = name;
    std::cout << name << '\n';
    path.insert(0, "/assets/textures/");
    path.insert(0, std::filesystem::current_path().string());
    std::cout << path << '\n';
   return path;
}


unsigned int Texture::getTextureID()
{
    return TEXid;
}


//statics

void Texture::initTextures()
{
    std::string path = "/assets/textures/";
    path.insert(0, std::filesystem::current_path().string());

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        addTextureIfNotExists(entry.path().filename().string());
    }
 }
 void Texture::addTextureIfNotExists(std::string textureName)
 {
     if (checkIfTextureExistsInMap(textureName))
         return;

     Texture tex = Texture(textureName);
     textureMap[textureName] = tex;
 }


 Texture* Texture::getTexture(std::string name)
 {
     addTextureIfNotExists(name);
     Texture* ptr = &textureMap[name];
     return ptr;
 }

 bool Texture::checkIfTextureExistsInMap(const std::string& textureName)
 {
     if (!(textureMap.find(textureName) == textureMap.end())) {
         // found so dont add new shader
         return true;
     }
     return false;
 }