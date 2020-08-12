#pragma once 

#include "graphics/glwrapping/ShaderProgram.h"
#include "graphics/text/Codepoint.h"
#include "graphics/text/Glyph.h"
#include "graphics/text/TypeFace.h"
#include "Exceptions.h"

#include <filesystem>
#include <map>
#include <memory>
#include <string>

namespace vngine {
namespace graphics {
namespace text {

class FreeTypeFont : public TypeFace {
public:
        FreeTypeFont(const std::filesystem::path& file, int faceIndex);
        virtual ~FreeTypeFont();

        virtual void setSize(int px);

        virtual std::unique_ptr<Glyph> generate(Codepoint c, std::shared_ptr<glwrapping::ShaderProgram> program) const;

private:
        struct FreeTypeImpl;
        static std::unique_ptr<FreeTypeImpl> impl;

        struct FaceImpl;
        std::unique_ptr<FaceImpl> face;
};

class FreeTypeException : public VNgineException {
public:
        FreeTypeException(int errcode);
        virtual ~FreeTypeException() = default;

        virtual const char* what() const noexcept { return VNgineException::what(); }
};

} // namespace text
} // namespace graphics
} // namespace vngine
