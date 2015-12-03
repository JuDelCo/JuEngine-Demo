// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Camera.hpp"

namespace Scripts
{
CameraController::CameraController()
{
	SetName("script_camera");
}

void CameraController::Init()
{
	//
}

void CameraController::Update()
{
	if(! InputManager::IsWindowActive())
	{
		return;
	}

	Camera* camera = mEntity->GetComponent<Camera>();
	Transform* transform = mEntity->GetComponent<Transform>();
	vec3 oldPos = transform->GetPosition();

	float cameraMovSpeed{10.0f};
	if(InputManager::IsHeld("shift")) cameraMovSpeed = 2.0f;
	if(InputManager::IsHeld("ctrl")) cameraMovSpeed = 100.0f;

	if(InputManager::IsHeld("right"))		transform->Translate(World::Right / cameraMovSpeed);
	if(InputManager::IsHeld("left"))		transform->Translate(-World::Right / cameraMovSpeed);
	if(InputManager::IsHeld("up"))			transform->Translate(World::Up / cameraMovSpeed);
	if(InputManager::IsHeld("down"))		transform->Translate(-World::Up / cameraMovSpeed);
	if(InputManager::IsHeld("forward"))		transform->Translate(World::Forward / cameraMovSpeed);
	if(InputManager::IsHeld("backward"))	transform->Translate(-World::Forward / cameraMovSpeed);

	if(InputManager::IsHeld("left_alt"))    camera->Rotate(0.f, -0.05f);
	if(InputManager::IsHeld("right_alt"))   camera->Rotate(0.f, 0.05f);
	if(InputManager::IsHeld("up_alt"))      camera->Rotate(0.05f, 0.f);
	if(InputManager::IsHeld("down_alt"))    camera->Rotate(-0.05f, 0.f);

	if(InputManager::MouseGetWheelDelta() != 0)
	{
		if(camera->IsOrthographic())
		{
			camera->SetZoom(camera->GetZoom() + (float)InputManager::MouseGetWheelDelta() * 5.0f);
			DebugLog::Write("Zoom: %f", camera->GetZoom());
		}
		else
		{
			//camera->SetFov(camera->GetFov() + (float)InputManager::MouseGetWheelDelta() * 5.0f);
			//DebugLog::Write("Fov: %f", camera->GetFov());

			transform->Translate(World::Forward / cameraMovSpeed * (float)InputManager::MouseGetWheelDelta() * 10.0f);
		}
	}

	if(InputManager::IsPressed("mouse_m") || InputManager::IsPressed("mouse_r"))
	{
		lastMousePoint = InputManager::MouseGetPosition();
	}

	if(InputManager::IsHeld("mouse_m") || InputManager::IsHeld("mouse_r"))
	{
		auto mousePos = InputManager::MouseGetPosition();
		mouseDiff = lastMousePoint - mousePos;

		if(mousePos.x < 10.0f)
		{
			mousePos.x = WindowManager::GetSize().x - 20.0f;
		}
		else if(mousePos.x > WindowManager::GetSize().x - 10.0f)
		{
			mousePos.x = 20.0f;
		}

		if(mousePos.y < 10.0f)
		{
			mousePos.y = WindowManager::GetSize().y - 20.0f;
		}
		else if(mousePos.y > WindowManager::GetSize().y - 10.0f)
		{
			mousePos.y = 20.0f;
		}

		InputManager::MouseSetPosition(mousePos);
	}

	if(InputManager::IsHeld("mouse_r"))
	{
		camera->Rotate(-mouseDiff.y / 300.0f, -mouseDiff.x / 300.0f);
	}
	else if(InputManager::IsHeld("mouse_m"))
	{
		transform->Translate(World::Right / cameraMovSpeed * (mouseDiff.x / 10.0f));
		transform->Translate(World::Up / cameraMovSpeed * -(mouseDiff.y / 10.0f));
	}

	if(InputManager::IsHeld("debug"))
	{
		//vec3 worldUp = vec3(0.5f, 0.5f, 0.f);
		//transform->LookAt(EntityManager::Get("duck")->GetComponent<Transform>()->GetPosition(), worldUp);
	}

	if(InputManager::IsPressed("debug"))
	{
		//camera->SetOrthographic(! camera->IsOrthographic());
	}

	auto newPos = transform->GetPosition();

	if(oldPos != newPos)
	{
		//DebugLog::Write("Camera -> X: %f Y: %f Z: %f Pitch: %f Yaw: %f", newPos.x, newPos.y, newPos.z, camera->GetEulerAngles().x, camera->GetEulerAngles().y);
	}

	if(InputManager::IsHeld("mouse_m") || InputManager::IsHeld("mouse_r"))
	{
		lastMousePoint = InputManager::MouseGetPosition();
	}
}

void CameraController::FixedUpdate()
{
	//
}
}
