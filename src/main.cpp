// Computergrafik Spotlight Demo
// Author: Tobias Zoll

// Imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Function to Close the Window, when ESC is pressed
void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main()
{
  // Initiate GLFW and set Up Window Hints
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  // Create a new GLFW Window with 1280x720
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Spotlight Demo for Computergrafik", NULL, NULL);
  if (window == NULL)
  {
      std::cout << "[Fatal] Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(window);

  // Initiate GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      std::cout << "[Fatal] Failed to initialize GLAD" << std::endl;
      return -1;
  }  

  // Set GL Viewport to Window Size
  glViewport(0, 0, 1280, 720);

  while(!glfwWindowShouldClose(window))
  {
    // Input Keys Here
    processInput(window);  // ESC closes the Window

    // Rendering Commands Here


    //Check and Call Events also swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  // End of Program
  glfwTerminate();
  return 0;
}
