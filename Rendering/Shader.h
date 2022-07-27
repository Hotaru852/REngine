//
// Created by kiseki on 6/10/22.
//

#ifndef RENGINE_SHADER_H
#define RENGINE_SHADER_H

#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Shader {
public:
    void initShader(const char* vShaderPath, const char* fShaderPath, const std::vector<float> *vertexAttribs,
                    const std::vector<unsigned int> *vertexIndices, const std::vector<int> *vertexLocs);
    // Considering to remove later
    void use() const;
    void bind() const;
    void deAllocate() const;
    void setInt(const std::string &name, const int &value) const;
    void setFloat(const std::string &name, const float &value) const;
    void setBool(const std::string &name, const bool &value) const;
    void setVec2(const std::string &name, const glm::vec2 &vec) const;
    void setVec2(const std::string &name, const float &x, float &y) const;
    void setVec3(const std::string &name, const glm::vec3 &vec) const;
    void setVec3(const std::string &name, const float &x, const float &y, const float &z) const;
    void setVec4(const std::string &name, const glm::vec4 &vec) const;
    void setVec4(const std::string &name, const float &x, const float &y, const float &z, const float &w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

#endif //RENGINE_SHADER_H