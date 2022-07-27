//
// Created by kiseki on 6/12/22.
//

#ifndef RENGINE_TEXTURE_H
#define RENGINE_TEXTURE_H

#include "stb_image.h"
#include <glad/glad.h>
#include<iostream>

class Texture {
public:
    void genTexture(const int &textureID, const int &texture_wrap_s_para, const int &texture_wrap_t_para,
                    const int &texture_min_filter_para, const int &texture_mag_filter_para, const char* texturePath);
    void binds(const int &activeTextures);
private:
    unsigned int textureUnits[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
};

#endif //RENGINE_TEXTURE_H