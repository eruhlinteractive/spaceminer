#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <string>
#include <raylib.h>
#include <memory>
#include <map>
#include "../debug.h"

namespace Astrocore
{
    class ResourceManager
    {
    private:
        ResourceManager();
        static inline ResourceManager* inst = nullptr;
        std::string basePath;
        std::map<std::string, std::shared_ptr<Texture2D>> cachedTextures;

    public:
       /// @brief Singleton instance return
       /// @return The singleton instance of the resource manager
       static ResourceManager* instance();

        /// @brief  Gets a cached resource. Will load from disk (synchronously) if the texture hasn't been cached.
        /// @return The loaded texture, or a nullptr if none was found    
        std::shared_ptr<Texture2D> GetTextureResource(std::string relativePath);
    }; 
}

#endif // __RESOURCEMANAGER_H__