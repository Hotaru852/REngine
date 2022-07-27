//
// Created by kiseki on 7/6/22.
//

#include "Camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 _orientation, glm::vec3 _worldUp, float _yaw, float _pitch, float _speed,
               float _sensitivity, float _fov) {
    position = _position;
    orientation = _orientation;
    worldUp = _worldUp;
    yaw = _yaw;
    pitch = _pitch;
    speed = _speed;
    sensitivity = _sensitivity;
    fov = _fov;
    update();
}

void Camera::move(CAMERA_MOVEMENT direction, const float *deltaTime) {
    float velocity = speed * (*deltaTime);
    if (direction == FORWARD) {
        position += orientation * velocity;
    }
    if (direction == BACKWARD) {
        position -= orientation * velocity;
    }
    if (direction == LEFT) {
        position -= right * velocity;
    }
    if (direction == RIGHT) {
        position += right * velocity;
    }
    if (direction == UP) {
        position += worldUp * velocity;
    }
    if (direction == DOWN) {
        position -= worldUp * velocity;
    }
}

void Camera::rotate(float *xOffset, float *yOffset, bool pitchConstraint) {
    *xOffset *= sensitivity;
    *yOffset *= sensitivity;
    yaw += *xOffset;
    pitch += *yOffset;

    if (pitchConstraint) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    update();
}

void Camera::zoom(float yOffset) {
    fov -= yOffset;
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    if (fov > 45.0f) {
        fov = 45.0f;
    }
}

void Camera::update() {
    // Calculate new orientation vector
    glm::vec3 newOrientation;
    newOrientation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newOrientation.y = sin(glm::radians(pitch));
    newOrientation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    orientation = glm::normalize(newOrientation);
    // Update right and up vector to new orientation
    right = glm::normalize(glm::cross(newOrientation, worldUp));
    up = glm::normalize(glm::cross(right, newOrientation));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + orientation, up);
}

glm::mat4 Camera::getProjectionMatrix(const unsigned int &SCR_WIDTH, const unsigned int &SCR_HEIGHT) const {
    return glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
}