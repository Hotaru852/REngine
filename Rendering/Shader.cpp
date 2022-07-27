//
// Created by kiseki on 6/10/22.
//

#include "Shader.h"

using namespace std;

void Shader::initShader(const char *vShaderPath, const char *fShaderPath, const vector<float> *vertexAttribs,
                        const vector<unsigned int> *vertexIndices, const vector<int> *vertexLocs) {
    int success;
    char infoLog[1024];
    string vertexCode, fragmentCode;
    ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(ifstream::badbit | ifstream::failbit);
    fShaderFile.exceptions(ifstream::badbit | ifstream::failbit);

    // Read vertex shader source code and fragment sahder soure code
    try {
        vShaderFile.open(vShaderPath);
        fShaderFile.open(fShaderPath);
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
        // Check for source code reading errors
    catch (const ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const char* vertexSource = vertexCode.c_str(), * fragmentSource = fragmentCode.c_str();

    // Generate and compile vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // Check for vertex shader compilation errors
    if (!success) {
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << endl;
    }

    // Generate and compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // Check for fragment shader compilation errors
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << endl;
    }

    // Generate shader program and link normalObject
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //Check for shader program linking errors
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 1024, nullptr, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << endl;
    }
    // Delete normalObject after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Generate vertex array objects, vertex buffer objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind vertex array objects, vertex buffer objects
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexAttribs->size() * sizeof(float), &vertexAttribs->front(), GL_STATIC_DRAW);
    // Generate and bind element buffer objects if needed
    if (vertexIndices) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices->size() * sizeof(unsigned int), &vertexIndices->front(), GL_STATIC_DRAW);
    }
    // Set vertex attributes pointers
    unsigned int *offset = new unsigned int;
    *offset = 0;
    for (int i = 0; i < vertexLocs->size() - 1; i++) {
        glVertexAttribPointer(i, (*vertexLocs)[i], GL_FLOAT, GL_FALSE, (*vertexLocs)[vertexLocs->size() - 1] * sizeof(float), (void*)(*offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        *offset += (*vertexLocs)[i];
    }
    delete offset;
}

void Shader::use() const {
    glUseProgram(shaderProgram);
}

void Shader::bind() const {
    glBindVertexArray(VAO);
}

void Shader::deAllocate() const {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Shader::setInt(const string &name, const int &value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const string &name, const float &value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &vec) const {
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &vec[0]);
}

void Shader::setVec2(const std::string &name, const float &x, float &y) const {
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &vec[0]);
}

void Shader::setVec3(const std::string &name, const float &x, const float &y, const float &z) const {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &vec) const {
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &vec[0]);
}

void Shader::setVec4(const std::string &name, const float &x, const float &y, const float &z, const float &w) const {
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}

void Shader::setBool(const string &name, const bool &value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}