#include "../../../include/astrocore/systems/resources/resourcemanager.h"

using namespace Astrocore;


ResourceManager::ResourceManager()
{
    cachedTextures = std::map<std::string, std::shared_ptr<Texture2D>>();
    basePath = std::string(GetApplicationDirectory());
    //basePath = "";
}


std::shared_ptr<Texture2D> ResourceManager::GetTextureResource(std::string relativePath)
{
    // Already cached, return the texture
    if(cachedTextures.find(relativePath) != cachedTextures.end())
    {
        return cachedTextures.at(relativePath);
    }

    const char* fullPath = (relativePath).c_str();

    // Invalid file
    if(!(FileExists(fullPath) && IsPathFile(fullPath)) )
    {
        Debug::LogError("Unable to find the file at path " + relativePath);
        return nullptr;
    }

    // Load from disk and return
    Texture2D loadedTexture = LoadTexture(fullPath);
    std::shared_ptr<Texture2D> ptr = std::make_shared<Texture2D>(loadedTexture);
    cachedTextures.emplace(relativePath, ptr);

    return ptr;
}

ResourceManager* ResourceManager::instance()
{
    if(ResourceManager::inst == nullptr)
    {
        ResourceManager::inst = new ResourceManager();
    }

    return ResourceManager::inst;
}
