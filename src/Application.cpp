#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.hpp"
#include "Material.h"
#include "LightSource.h"
#include "Mesh.h"
#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//窗口大小
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

#pragma region Model Data

/* 顶点坐标 */
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
/* 位移向量 */
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
/*点光源坐标*/
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};
#pragma endregion

#pragma region Camera Declare
//Instantiate Camera class
Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare

LightDirectional lightDirectional(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.4f, 0.4f, 0.4f),
	glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.2f, -1.0f, -0.3f));

std::vector <LightPoint> lightPoint = {
	LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
	pointLightPositions[0], 1.0f, 0.09f, 0.032f, glm::vec3(0.0f,0.9f,0.8f)),

	LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
	pointLightPositions[1], 1.0f, 0.09f, 0.032f, glm::vec3(1.0f,0.9f,0.8f)),

	LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
	pointLightPositions[2], 1.0f, 0.09f, 0.032f, glm::vec3(1.0f,0.9f,0.8f)),

	LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
	pointLightPositions[3], 1.0f, 0.09f, 0.032f, glm::vec3(1.0f,0.9f,0.8f))
};

LightSpot lightSpot(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
	1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), glm::vec3(1.0f, 0.0f, 0.0f));

#pragma endregion

#pragma region FullScreen

bool isFullScreen = false;
void FullScreen(GLFWwindow* window)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (isFullScreen == false)
	{
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		isFullScreen = true;
	}
	else if (isFullScreen == true)
	{
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, SCR_WIDTH, SCR_HEIGHT, mode->refreshRate);

		isFullScreen = false;
	}
}

bool isMax = false;
void MaxScreen(GLFWwindow* window)
{

	if (isFullScreen == false)
	{
		glfwMaximizeWindow(window);
		isFullScreen = true;
	}
	else if (isFullScreen == true)
	{
		glfwRestoreWindow(window);
		isFullScreen = false;
	}
}
#pragma endregion

#pragma region Input Declare

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float mixValue = 0.2f;

// timing
float deltaTime = 0.0f;	// 当前帧和最后一帧之间的时间
float lastFrame = 0.0f;  //最后一帧

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01f * deltaTime * 50;
		if (mixValue >= 1.0f)
		{
			mixValue = 1.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01f * deltaTime * 50;
		if (mixValue <= 0.0f)
		{
			mixValue = 0.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_F11:
		MaxScreen(window);
		break;
	case GLFW_KEY_F10:
		FullScreen(window);
		break;
	default:
		break;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true)   //鼠标第一次进入
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;  //鼠标距上一帧的偏移量
	deltaX = xPos - lastX;
	deltaY = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(deltaX, deltaY);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
#pragma endregion


unsigned int loadTexture(char const* path, int textureSlot)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0 + textureSlot);  //激活纹理单元
	glBindTexture(GL_TEXTURE_2D, textureID);  //绑定纹理单元

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); //翻转y轴
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}
	stbi_image_free(data);
	return textureID;
}

int main(int argc, char* argv[])
{
	std::string exePath = argv[0];
	#pragma region Open a Window
	/* Initialize the Library (初始化GLFW库) */
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* 创建窗口 */
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", NULL, NULL);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		/* 结束，释放分配的内存 */
		glfwTerminate();
		return -1;
	}


	/* 设置当前窗口 绑定上下文 */
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //隐藏鼠标光标
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* 创建视口 */
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); //(x,y,长，宽）

	/*
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //框线模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //填充模式
	*/
	glEnable(GL_DEPTH_TEST);
#pragma endregion

	#pragma region Init Shader Program
	Shader* ourShader = new Shader("E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\vertexSource.vert", "E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\fragmentSource.frag");
	Shader* lightShader = new Shader("E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\lightCube.vert", "E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\lightCube.frag");
#pragma  endregion

	#pragma region Init Material
	Material *ourMaterial=new Material(
		ourShader,
		glm::vec3(0.0f, 0.0f, 0.0f),
		loadTexture("E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\container2.png", 0),
		loadTexture("E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\container2_specular.png", 1),
		32.0f);
#pragma endregion

	#pragma region Init Mesh
	//Mesh lightCube(vertices);
#pragma endregion

	#pragma region Init Model
	Model model(exePath.substr(0, exePath.find_last_of("\\")) + "\\model\\nanosuit.obj");
	
#pragma endregion

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//获取渲染每帧的时间
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		/* 渲染指令 */
		/* 设置屏幕颜色。*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。
		/* 清除缓冲区 */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//当前可写的颜色缓冲

		#pragma region set Uniform

		//set Shader Program
		ourShader->use();

		ourShader->setVec3("viewPos", camera.Position);

		// directional light
		ourShader->setVec3("dirLight.direction", lightDirectional.direction);
		ourShader->setVec3("dirLight.color", lightDirectional.color);
		ourShader->setVec3("dirLight.ambient", lightDirectional.ambient);
		ourShader->setVec3("dirLight.diffuse", lightDirectional.diffuse);
		ourShader->setVec3("dirLight.specular", lightDirectional.specular);

		// point light
		ourShader->setVec3("pointLights[0].position", lightPoint[0].position);
		ourShader->setVec3("pointLights[0].color", lightPoint[0].color);
		ourShader->setVec3("pointLights[0].ambient", lightPoint[0].ambient);
		ourShader->setVec3("pointLights[0].diffuse", lightPoint[0].diffuse);
		ourShader->setVec3("pointLights[0].specular", lightPoint[0].specular);
		ourShader->setUniform("pointLights[0].constant", lightPoint[0].constant);
		ourShader->setUniform("pointLights[0].linear", lightPoint[0].linear);
		ourShader->setUniform("pointLights[0].quadratic", lightPoint[0].quadratic);

		ourShader->setVec3("pointLights[1].position", lightPoint[1].position);
		ourShader->setVec3("pointLights[1].color", lightPoint[1].color);
		ourShader->setVec3("pointLights[1].ambient", lightPoint[1].ambient);
		ourShader->setVec3("pointLights[1].diffuse", lightPoint[1].diffuse);
		ourShader->setVec3("pointLights[1].specular", lightPoint[1].specular);
		ourShader->setUniform("pointLights[1].constant", lightPoint[1].constant);
		ourShader->setUniform("pointLights[1].linear", lightPoint[1].linear);
		ourShader->setUniform("pointLights[1].quadratic", lightPoint[1].quadratic);

		ourShader->setVec3("pointLights[2].position", lightPoint[2].position);
		ourShader->setVec3("pointLights[2].color", lightPoint[2].color);
		ourShader->setVec3("pointLights[2].ambient", lightPoint[2].ambient);
		ourShader->setVec3("pointLights[2].diffuse", lightPoint[2].diffuse);
		ourShader->setVec3("pointLights[2].specular", lightPoint[2].specular);
		ourShader->setUniform("pointLights[2].constant", lightPoint[2].constant);
		ourShader->setUniform("pointLights[2].linear", lightPoint[2].linear);
		ourShader->setUniform("pointLights[2].quadratic", lightPoint[2].quadratic);

		ourShader->setVec3("pointLights[3].position", lightPoint[3].position);
		ourShader->setVec3("pointLights[3].color", lightPoint[3].color);
		ourShader->setVec3("pointLights[3].ambient", lightPoint[3].ambient);
		ourShader->setVec3("pointLights[3].diffuse", lightPoint[3].diffuse);
		ourShader->setVec3("pointLights[3].specular", lightPoint[3].specular);
		ourShader->setUniform("pointLights[3].constant", lightPoint[3].constant);
		ourShader->setUniform("pointLights[3].linear", lightPoint[3].linear);
		ourShader->setUniform("pointLights[3].quadratic", lightPoint[3].quadratic);

		// spotLight
		ourShader->setVec3("spotLight.position", camera.Position);
		ourShader->setVec3("spotLight.direction", camera.Front);
		ourShader->setVec3("spotLight.color", lightSpot.color);
		ourShader->setVec3("spotLight.ambient", lightSpot.ambient);
		ourShader->setVec3("spotLight.diffuse", lightSpot.diffuse);
		ourShader->setVec3("spotLight.specular", lightSpot.specular);
		ourShader->setUniform("spotLight.constant", lightSpot.constant);
		ourShader->setUniform("spotLight.linear", lightSpot.linear);
		ourShader->setUniform("spotLight.quadratic", lightSpot.quadratic);
		ourShader->setUniform("spotLight.cutOff", lightSpot.cutOff);
		ourShader->setUniform("spotLight.outerCutOff", lightSpot.outerCutOff);

#pragma endregion
		
		for (int i = 0; i < 1; i++)
		{
			#pragma region Prepare MVP matrices
			//set Model matrix
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			//set View Matrices
			glm::mat4 viewMat;
			viewMat = camera.GetViewMatrix();
			//set Projection Matrices
			glm::mat4 projMat;
			projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
#pragma endregion

			//set Shader Program
			ourShader->use();

			//set MVP matrices -> Uniforms
			ourShader->setMat4("modelMat", modelMat);
			ourShader->setMat4("viewMat", viewMat);
			ourShader->setMat4("projMat", projMat);

			//set Material -> Uniforms
			ourMaterial->shader->setVec3("material.ambient", ourMaterial->ambient);
			ourMaterial->shader->setUniform("material.diffuse", 0);
			ourMaterial->shader->setUniform("material.specular", 1);
			ourMaterial->shader->setUniform("material.shininess", ourMaterial->shiness);

			//DrawCall
			//cube.Draw(*(ourMaterial->shader));
			model.Draw(*(ourMaterial->shader));
		}

#pragma region Prepare lightCube MVP matrices
		for (unsigned int i = 0; i < lightPoint.size(); i++)
		{
			//set Model matrix
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, pointLightPositions[i]);
			modelMat = glm::scale(modelMat, glm::vec3(0.2f)); // a smaller cube
			//set View Matrices
			glm::mat4 viewMat;
			viewMat = camera.GetViewMatrix();
			//set Projection Matrices
			glm::mat4 projMat;
			projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

			lightShader->use();
			lightShader->setMat4("modelMat", modelMat);
			lightShader->setMat4("viewMat", viewMat);
			lightShader->setMat4("projMat", projMat);

			//lightCube.Draw(*lightShader);
		}
#pragma endregion
		

		//清空缓存，准备下一次渲染循环
		/* Swap front and back buffers (交换颜色缓冲) */
		glfwSwapBuffers(window);
		/* Poll for and process events (检测是否有事件出发（鼠标、键盘）) */
		glfwPollEvents();
	}

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}