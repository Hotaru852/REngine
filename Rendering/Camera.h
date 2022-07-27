//
// Created by kiseki on 7/6/22.
//

#ifndef RENGINE_CAMERA_H
#define RENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CAMERA_MOVEMENT {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera settings
const glm::vec3 defaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 defaultOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 defaultWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
const float defaultYaw = -90.0f;
const float defaultPitch = 0.0f;
const float defaultSpeed = 2.5f;
const float defaultSensitvity = 0.1f;
const float defaultFov = 45.0f;

class Camera {
public:
    Camera(glm::vec3 _position = defaultPosition, glm::vec3 _orientation = defaultOrientation,
           glm::vec3 _worldUp = defaultWorldUp, float _yaw = defaultYaw, float _pitch = defaultPitch, float _speed = defaultSpeed,
           float _sensitivity = defaultSensitvity, float _fov = defaultFov);
    void move(CAMERA_MOVEMENT direction, const float *deltaTime);
    void rotate(float *xOffset, float *yOffset, bool pitchConstraint = true);
    void zoom(float yOffset);
    void update();
    glm::vec3 getPos() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(const unsigned int &SCR_WIDTH, const unsigned int &SCR_HEIGHT) const;
private:
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 up;
    glm::vec3 worldUp;
    glm::vec3 right;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float fov;
};

#endif //RENGINE_CAMERA_H