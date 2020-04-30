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

void JoanModule::update(float elapsed)
{
	cameraController();
}

void JoanModule::initCameras()
{
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	glm::vec2 viewport = Engine::get().getRender().getViewport();

	cameras[0]->setProjectionParams((float)glm::radians(45.f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[0]->lookAt(glm::vec3(10.f, 0, 1.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	cameras[1]->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[1]->lookAt(glm::vec3(500.f, 500.f, 1.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	cameras[2]->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[2]->lookAt(glm::vec3(600.f, 1000.f, 1.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Engine::get().SetCamera(cameras[0]);
}

void JoanModule::cameraController()
{
	front = glm::vec3(1, 0, 1);
	glm::vec3 euler = camera->getTransform().getEulerAngles();

	if (canPress && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		
		actualCamera++;
		std::cout << "NumCamera: " << actualCamera << std::endl;
		actualCamera %= cameras.size();
		Engine::get().SetCamera(cameras[actualCamera]);
		canPress = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		canPress = true;
	}
}

void JoanModule::renderDebug()
{
	Engine::get().setModelObjectConstants(cubeT.asMatrix(), glm::vec4(1, 0, 1, 1.0f));
	cube.render();

	Engine::get().setModelObjectConstants(cubeT2.asMatrix(), glm::vec4(500, 0, 1, 1.0f));
	cube.render();

	Engine::get().setModelObjectConstants(cubeT3.asMatrix(), glm::vec4(1, 0, 1, 1.0f));
	cube.render();
}

JoanModule::JoanModule()
{
}


JoanModule::~JoanModule()
{
}
