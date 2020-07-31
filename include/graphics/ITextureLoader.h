#pragma once

#include <filesystem>

namespace vngine {
namespace graphics {

class ITextureLoader {
public:
        virtual ~ITextureLoader() = default;

        virtual void load(const std::filesystem::path& file) const = 0;
};

} // namespace graphics
} // namespace vngine
