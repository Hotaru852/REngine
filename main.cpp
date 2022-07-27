//
// Created by kiseki on 6/10/22.
//

#include "Rendering/Shader.h"
#include "Rendering/Camera.h"
#include <GLFW/glfw3.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLFWwindow* window;
Shader normalObject;
Shader lightSource;
Camera camera = Camera();

glm::mat4 model;
glm::vec3 lightPos = glm::vec3(1.0f, 2.0f, 0.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

float deltaTime;
float lastFrameTime = 0.0f;

float lastCursorX = SCR_WIDTH / 2;
float lastCursorY = SCR_HEIGHT / 2;

bool firstMouseCursorInput;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCursorInputCallback(GLFWwindow *_window, double currentCursorX, double currentCursorY);
void mouseScrollInputCallback(GLFWwindow *_window, double xOffset, double yOffSet);
void keyboardInputCallback(GLFWwindow *_window, int key, int scancode, int action, int mods);
void cameraInput(GLFWwindow *_window);

void init();
void loop();

int main()
{
    init();
    loop();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* _window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouseCursorInputCallback(GLFWwindow *_window, double currentCursorX, double currentCursorY) {
    if (firstMouseCursorInput) {
        lastCursorY = currentCursorX;
        lastCursorY = currentCursorY;
        firstMouseCursorInput = false;
    }

    float xOffset = currentCursorX - lastCursorX;
    float yOffset = lastCursorY - currentCursorY;

    lastCursorX = currentCursorX;
    lastCursorY = currentCursorY;

    camera.rotate(&xOffset, &yOffset);
}

void mouseScrollInputCallback(GLFWwindow *_window, double xOffset, double yOffset) {
    camera.zoom(yOffset);
}

void keyboardInputCallback(GLFWwindow *_window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void cameraInput(GLFWwindow *_window) {
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.move(FORWARD, &deltaTime);
    }
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.move(LEFT, &deltaTime);
    }
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.move(BACKWARD, &deltaTime);
    }
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.move(RIGHT, &deltaTime);
    }
    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.move(UP, &deltaTime);
    }
    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.move(DOWN, &deltaTime);
    }
}



void init() {
    // Initialize and configure glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "REngine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCursorInputCallback);
    glfwSetScrollCallback(window, mouseScrollInputCallback);
    glfwSetKeyCallback(window, keyboardInputCallback);

    // Load glad to load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    std::vector<int> locations = {3, 3, 6};

    normalObject.initShader("/home/kiseki/CLionProjects/REngine/Rendering/vertexShader.vs", "/home/kiseki/CLionProjects/REngine/Rendering/fragmentShader.fs", &vertices,
                            nullptr, &locations);
    lightSource.initShader("/home/kiseki/CLionProjects/REngine/Rendering/vertexShader.vs", "/home/kiseki/CLionProjects/REngine/Rendering/fragmentShader_lightSource.fs", &vertices,
                           nullptr, &locations);
    glEnable(GL_DEPTH_TEST);
}


void loop() {
    while (!glfwWindowShouldClose(window))
    {
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        lightPos.x = 1.0f * sin(glfwGetTime());
        lightPos.y = 2.0f * cos(glfwGetTime());
        lightColor.x = 1.0f * sin(glfwGetTime());
        lightColor.y = 1.0f * sin(glfwGetTime());
        lightColor.z = 1.0f * sin(glfwGetTime());

        // Input
        cameraInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw normal object
        normalObject.use();
        model = glm::mat4(1.0f);
        normalObject.setMat4("model", model);
        normalObject.setMat4("projection", camera.getProjectionMatrix(SCR_WIDTH, SCR_HEIGHT));
        normalObject.setMat4("view", camera.getViewMatrix());
        normalObject.setVec3("lightColor", lightColor);
        normalObject.setVec3("lightPos", lightPos);
        normalObject.setVec3("material.ambient", 0.1745, 0.01175, 0.01175);
        normalObject.setVec3("material.diffuse", 0.61424, 0.04136, 0.04136);
        normalObject.setVec3("material.specular", 0.727811, 0.626959, 0.626959);
        normalObject.setFloat("material.shininess", 0.6 * 128);
        normalObject.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw light source
        lightSource.use();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightSource.setMat4("model", model);
        lightSource.setMat4("projection", camera.getProjectionMatrix(SCR_WIDTH, SCR_HEIGHT));
        lightSource.setMat4("view", camera.getViewMatrix());
        lightSource.setVec3("lightColor", lightColor);
        lightSource.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    normalObject.deAllocate();
    lightSource.deAllocate();

    // Terminate and clear all previously allocated GLFW resources.
    glfwTerminate();
}