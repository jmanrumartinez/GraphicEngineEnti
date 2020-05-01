#include "precompiledHeader.h"
#include "JoanModule.h"

extern Mesh cube;
extern Mesh Sphere;
void JoanModule::start()
{
	camera = new Camera();

	glm::vec2 viewport = Engine::get().getRender().getViewport();

	camera->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	window = Engine::get().getRender().getCtxWindow()->getWindowGL();
	Engine::get().SetCamera(camera);
	camera->getTransform().setPosition(0, 0, 8);
	camera->lookAt(glm::vec3(0, 0, 8), glm::vec3(0, 0, 0));

	pos = camera->getPosition();
	front = glm::vec3(0, 0, 1);
	initCameras();
}

void JoanModule::stop()
{

	for (int i = 0; i < cameras.size(); i++)
		delete cameras[i];
}

void JoanModule::update(float elapsed)
{
	glm::vec3 euler = cubeT.getEulerAngles();

	quad1.setPosition(glm::vec3(0, 0, 50.0f));
	quad1.setScale(5.0f);
	cubeT.setEulerAngles(glm::radians(euler.x + glfwGetTime() * 50.0f), euler.y, euler.z);
	cubeT.setPosition(glm::vec3(2, 0, 5));
	cubeT.setEulerAngles(glm::radians(euler.x + glfwGetTime() * 50.0f), euler.y, euler.z);
	cubeT3.setPosition(glm::vec3(6, 0, 10));
	cubeT3.setEulerAngles(glm::radians(euler.y + glfwGetTime() * 500.0f), euler.x, euler.z);
	cameraController();
	camera->lookAt(pos, target);
}

void JoanModule::initCameras()
{
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	cameras.push_back(camera);
	glm::vec2 viewport = Engine::get().getRender().getViewport();

	cameras[0]->setProjectionParams((float)glm::radians(15.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[0]->lookAt(glm::vec3(14.5f, 0, 1.42883f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	cameras[1]->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[1]->lookAt(glm::vec3(0, 3, 25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	Engine::get().SetCamera(cameras[0]);
}

void JoanModule::cameraController()
{
	front = glm::vec3(0, 0, 1);
	glm::vec3 euler = camera->getTransform().getEulerAngles();

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newAngle += glm::radians(5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newAngle -= glm::radians(5.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos -= 0.1f * camera->getFront();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos += 0.1f * camera->getFront();
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		newPitch += glm::radians(5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		newPitch += glm::radians(-5.0f);
	}
	if (canPress && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		actualCamera++;
		std::cout << "Camera changed to " << actualCamera << std::endl; 
		actualCamera %= cameras.size();
		Engine::get().SetCamera(cameras[actualCamera]);
		canPress = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		canPress = true;
	}

	target = pos + glm::vec3(sinf(newAngle) * cosf(newPitch),
		sinf(newPitch), cosf(newAngle) * cosf(newPitch));
	glm::vec3 front = camera->getFront();

	camera->getTransform().setPosition(pos);

	std::cout << cameras[0]->getTransform().getPosition().x << " " <<
		cameras[0]->getTransform().getPosition().y << " "
		<< cameras[0]->getTransform().getPosition().z << std::endl;
}

void JoanModule::renderDebug()
{
	Engine::get().setModelObjectConstants(quad1.asMatrix(), glm::vec4(0, 255, 0, 1));
	quad.render();

	Engine::get().setModelObjectConstants(cubeT.asMatrix(), glm::vec4(0.54f, 0.0f, 1.0f, 1.0f));
	cube.activateAndRender();

	Engine::get().setModelObjectConstants(cubeT2.asMatrix(), glm::vec4(1, 0.24f, 0, 1));
	cube.activateAndRender();

	Engine::get().setModelObjectConstants(cubeT3.asMatrix(), glm::vec4(0.78f, 0, 0.63f, 1));
	cube.activateAndRender();
}


JoanModule::JoanModule()
{
}


JoanModule::~JoanModule()
{
}
