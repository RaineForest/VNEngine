
#pragma once

#define CAT_HELP(x,y) x##y
#define CAT(x,y) CAT_HELP(x,y)

#define GL_HELPER(retType, name, N, T, Ts)      \
template<unsigned int N, typename T>            \
retType name<N, T>(float* vals) {               \
        return CAT(CAT(CAT(name,1),Ts),v)(vals);\
}

#define GL_HELPER_EXPAND(retType, name)         \
GL_HELPER(retType, name, 1, float, f)           \
GL_HELPER(retType, name, 2, float, f)           \
GL_HELPER(retType, name, 3, float, f)           \
GL_HELPER(retType, name, 4, float, f)           \
GL_HELPER(retType, name, 1, int, i)             \
GL_HELPER(retType, name, 2, int, i)             \
GL_HELPER(retType, name, 3, int, i)             \
GL_HELPER(retType, name, 4, int, i)             \
GL_HELPER(retType, name, 1, unsigned int, ui)   \
GL_HELPER(retType, name, 2, unsigned int, ui)   \
GL_HELPER(retType, name, 3, unsigned int, ui)   \
GL_HELPER(retType, name, 4, unsigned int, ui)   

#define GL_TEMP_DEF(retType, name)              \
template<unsigned int N, typename T>            \
retType name(T* vals);                          \
GL_HELPER_EXPAND(retType, name)

#define GL_HELPER_VOID(name, N, T, Ts)          \
template<unsigned int N, typename T>            \
void name<N, T>(float* vals) {                  \
        CAT(CAT(CAT(name,1),Ts),v)(vals);       \
}

#define GL_HELPER_EXPAND_VOID(name)             \
GL_HELPER_VOID(name, 1, float, f)               \
GL_HELPER_VOID(name, 2, float, f)               \
GL_HELPER_VOID(name, 3, float, f)               \
GL_HELPER_VOID(name, 4, float, f)               \
GL_HELPER_VOID(name, 1, int, i)                 \
GL_HELPER_VOID(name, 2, int, i)                 \
GL_HELPER_VOID(name, 3, int, i)                 \
GL_HELPER_VOID(name, 4, int, i)                 \
GL_HELPER_VOID(name, 1, unsigned int, ui)       \
GL_HELPER_VOID(name, 2, unsigned int, ui)       \
GL_HELPER_VOID(name, 3, unsigned int, ui)       \
GL_HELPER_VOID(name, 4, unsigned int, ui)   

#define GL_TEMP_DEF_VOID(name)                  \
template<unsigned int N, typename T>            \
void name(T* vals);                             \
GL_HELPER_EXPAND_VOID(name)

GL_TEMP_DEF_VOID(glVertex)
