//
// Created by kiseki on 6/12/22.
//

#include "Texture.h"

using namespace std;

void Texture::genTexture(const int &textureID, const int &texture_wrap_s_para, const int &texture_wrap_t_para,
                         const int &texture_min_filter_para, const int &texture_mag_filter_para, const char *texturePath) {
    // Generate textures
    glGenTextures(1, &textureUnits[textureID]);
    // Bind textures
    glBindTexture(GL_TEXTURE_2D, textureUnits[textureID]);
    // Set parameters for textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s_para);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t_para);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_min_filter_para);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filter_para);
    // Generate textures images
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture" << endl;
    }
    // Free images after use
    stbi_image_free(data);
}

void Texture::binds(const int &activeTextures) {
    for (int i = 0; i < activeTextures; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureUnits[i]);
    }
}