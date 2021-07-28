#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
#pragma endregion

#pragma region Camera Declare
//Instantiate Camera class
Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

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

unsigned int LoadImageToGpu(const char* filename, int internalformat, GLenum format, int textureSlot)
{
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);  //激活纹理单元
	glBindTexture(GL_TEXTURE_2D, TexBuffer);  //绑定纹理单元

	// set the texture wrapping parameters   环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters    过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); //翻转y轴
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "load image failed." << std::endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}

int main(void)
{
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //隐藏鼠标光标
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

#pragma region Init and Load Models to VAO,VBO
	/* 创建VAO(顶点数组对象) */
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	/* 创建VBO顶点缓冲对象 */
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//绑定缓冲类型 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)
	//将用户数据复制到当前绑定缓冲(GL_ARRAY_BUFFER)    将数据从CPU复制到GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//参数4：显卡处理数据的方式
	/* 设置顶点属性指针 */
	glBindVertexArray(VAO);
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 光照属性
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
	// 纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(lightCubeVAO);
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion

#pragma region Init and Load Textures
	/* 纹理贴图 */
	unsigned int TexBufferA;
	TexBufferA = LoadImageToGpu("E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\container2.png", GL_RGBA, GL_RGBA, 0);
	unsigned int TexBufferB;
	TexBufferB = LoadImageToGpu("E:\\Code\\CPP\\OpenGL\\OpenGL\\src\\container2_specular.png", GL_RGBA, GL_RGBA, 1);
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。
		/* 清除缓冲区 */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//当前可写的颜色缓冲

		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		//lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		//lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
		for (int i = 0; i < 10; i++)
		{
#pragma region Prepare MVP matrices
			//set Model matrix
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(-45.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			//set View Matrices
			glm::mat4 viewMat;
			viewMat = camera.GetViewMatrix();
			//set Projection Matrices
			glm::mat4 projMat;
			projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
#pragma endregion

			//set Material -> Shader Program
			ourShader->use();
			//set Material -> Uniforms

			ourShader->setUniform("mixValue", mixValue);
			ourShader->setMat4("modelMat", modelMat);
			ourShader->setMat4("viewMat", viewMat);
			ourShader->setMat4("projMat", projMat);
			ourShader->setVec3("objColor", 1.0f, 0.5f, 0.31f);
			ourShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			ourShader->setVec3("viewPos", camera.Position);
			ourShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
			ourShader->setUniform("material.diffuse", 0);
			ourShader->setUniform("material.specular", 1);
			ourShader->setUniform("material.shininess", 32.0f);
			ourShader->setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
			ourShader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f); 
			ourShader->setVec3("light.specular", 5.0f, 5.0f, 5.0f);
			ourShader->setVec3("light.position", camera.Position);
			ourShader->setUniform("light.constant", 1.0f);
			ourShader->setUniform("light.linear", 0.22f);
			ourShader->setUniform("light.quadratic", 0.20f);
			ourShader->setVec3("light.direction", camera.Front);
			ourShader->setUniform("light.cutOff", glm::cos(glm::radians(12.5f)));

			glBindVertexArray(VAO);
			//DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);//VAO画图
		}

#pragma region Prepare lightCube MVP matrices
		//set Model matrix
		glm::mat4 modelMat;
		modelMat = glm::translate(modelMat, lightPos);
		modelMat = glm::scale(modelMat, glm::vec3(0.2f)); // a smaller cube
		//set View Matrices
		glm::mat4 viewMat;
		viewMat = camera.GetViewMatrix();
		//set Projection Matrices
		glm::mat4 projMat;
		projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
#pragma endregion

		lightShader->use();
		lightShader->setMat4("modelMat", modelMat);
		lightShader->setMat4("viewMat", viewMat);
		lightShader->setMat4("projMat", projMat);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//清空缓存，准备下一次渲染循环
		/* Swap front and back buffers (交换颜色缓冲) */
		glfwSwapBuffers(window);
		/* Poll for and process events (检测是否有事件出发（鼠标、键盘）) */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}