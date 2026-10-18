#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"


unsigned int width = 800;
unsigned int height = 800;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Vertices Coords
GLfloat vertices[] =
{ // 	COORDINATES     /        COLORS
	-0.5f, -0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
	 0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
	 0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
	 0.0f,  0.8f,  0.0f,    0.92f, 0.86f, 0.76f,    2.5f, 5.0f,

};

GLuint indices[] =
{
	0,1,2,
	0,2,3,
	0,1,4,
	1,2,4,
	2,3,4,
	3,0,4
};

int main() 
{
	//init GLFW
	glfwInit();

	//Tell GLFW what version of openGl is used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW to use the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the GLFWwindow object of 800 x 800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGl", NULL, NULL);
	//Error handling if the window fails to open
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Tells GLFW to make the window current context
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	//auto resizes window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Loads GLAD
	gladLoadGL();

	////Makes a OpenGl viewport of 800x800 pixels
	//glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// texture
	//
	//int widthImg, heightImg, mumColCh;
	//stbi_set_flip_vertically_on_load(true);
	//unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &mumColCh, 0);

	//GLuint texture;
	//glGenTextures(1, &texture);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//stbi_image_free(bytes);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	//shaderProgram.Activate();
	//glUniform1i(tex0Uni, 0);


	Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Enable wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//sets bg colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//cleans the back buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//tells opengl what shader program to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		popCat.Bind();
		//bind the vao so that opengl knows to use it
		VAO1.Bind();
		//draw the triangles using the primative GL_TRIANGLES
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		//swaps the front and back buffers
		glfwSwapBuffers(window);

		//Takes care of GLFW events
		glfwPollEvents();
	}

	//deletes all objects we made
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	//Deletes the window before ending program
	glfwDestroyWindow(window);
	//Closes GLFW
	glfwTerminate();
	//Sends Closing without error message
	std::cout << "window closed on command." << std::endl;
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}