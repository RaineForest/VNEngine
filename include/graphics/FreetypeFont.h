#pragma once 

#include "Exceptions.h"
#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/IModel.h"

#include <filesystem>
#include <map>
#include <memory>
#include <string>

namespace vngine {
namespace graphics {

class FreetypeFont {
public:
        FreetypeFont(const std::filesystem::path& file, int faceIndex);
        virtual ~FreetypeFont();

        virtual void setSize(int px);

        virtual std::unique_ptr<IModel> generate(char c, std::shared_ptr<glwrapping::ShaderProgram> program);

private:
        struct FreetypeImpl;
        static std::unique_ptr<FreetypeImpl> impl;

        struct FaceImpl;
        std::unique_ptr<FaceImpl> face;
};

class FreetypeException : public VNgineException {
public:
        FreetypeException(int errcode);
        virtual ~FreetypeException() = default;

        virtual const char* what() const noexcept { return VNgineException::what(); }
};

} // namespace graphics
} // namespace vngine
