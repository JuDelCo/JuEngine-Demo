// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "CameraSystem.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/Camera.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/Managers/InputManager.hpp>
#include <JuEngine/Managers/WindowManager.hpp>
#include <JuEngine/Resources/DebugLog.hpp>
#include "CameraComponent.hpp"

namespace Systems
{
void Camera::SetPool(JuEngine::Pool* pool)
{
	mPool = pool;
}

void Camera::Execute()
{
	if(! JuEngine::InputManager::IsWindowActive())
	{
		return;
	}

	auto entity = mPool->GetGroup(Matcher_AllOf(JuEngine::Transform, JuEngine::Camera, Components::Camera))->GetSingleEntity();
	auto camera = entity->Use<JuEngine::Camera>();
	auto cameraData = entity->Get<Components::Camera>();
	auto transform = entity->UseTransform();

	vec3 oldPos = transform->GetPosition();

	float cameraMovSpeed{10.f};
	if(JuEngine::InputManager::IsHeld("shift")) cameraMovSpeed = 2.f;
	if(JuEngine::InputManager::IsHeld("ctrl")) cameraMovSpeed = 100.f;

	if(JuEngine::InputManager::IsHeld("right"))		transform->Translate(JuEngine::World::Right / cameraMovSpeed);
	if(JuEngine::InputManager::IsHeld("left"))		transform->Translate(-JuEngine::World::Right / cameraMovSpeed);
	if(JuEngine::InputManager::IsHeld("up"))		transform->Translate(JuEngine::World::Up / cameraMovSpeed);
	if(JuEngine::InputManager::IsHeld("down"))		transform->Translate(-JuEngine::World::Up / cameraMovSpeed);
	if(JuEngine::InputManager::IsHeld("forward"))	transform->Translate(JuEngine::World::Forward / cameraMovSpeed);
	if(JuEngine::InputManager::IsHeld("backward"))	transform->Translate(-JuEngine::World::Forward / cameraMovSpeed);

	if(JuEngine::InputManager::IsHeld("left_alt"))    camera->Rotate(0.f, -0.05f);
	if(JuEngine::InputManager::IsHeld("right_alt"))   camera->Rotate(0.f, 0.05f);
	if(JuEngine::InputManager::IsHeld("up_alt"))      camera->Rotate(0.05f, 0.f);
	if(JuEngine::InputManager::IsHeld("down_alt"))    camera->Rotate(-0.05f, 0.f);

	if(JuEngine::InputManager::MouseGetWheelDelta() != 0)
	{
		if(camera->IsOrthographic())
		{
			camera->SetZoom(camera->GetZoom() + (float)JuEngine::InputManager::MouseGetWheelDelta() * 5.f);
			JuEngine::DebugLog::Write("Zoom: %f", camera->GetZoom());
		}
		else
		{
			//camera->SetFov(camera->GetFov() + (float)InputManager::MouseGetWheelDelta() * 5.f);
			//DebugLog::Write("Fov: %f", camera->GetFov());

			transform->Translate(JuEngine::World::Forward / cameraMovSpeed * (float)JuEngine::InputManager::MouseGetWheelDelta() * 10.f);
		}
	}

	if(JuEngine::InputManager::IsPressed("mouse_m") || JuEngine::InputManager::IsPressed("mouse_r"))
	{
		cameraData->lastMousePoint = JuEngine::InputManager::MouseGetPosition();
	}

	if(JuEngine::InputManager::IsHeld("mouse_m") || JuEngine::InputManager::IsHeld("mouse_r"))
	{
		auto mousePos = JuEngine::InputManager::MouseGetPosition();
		auto mouseOldPos = mousePos;
		cameraData->mouseDiff = cameraData->lastMousePoint - mousePos;

		if(mousePos.x < 10.f)
		{
			mousePos.x = JuEngine::WindowManager::GetSize().x - 20.f;
		}
		else if(mousePos.x > JuEngine::WindowManager::GetSize().x - 10.f)
		{
			mousePos.x = 20.f;
		}

		if(mousePos.y < 10.f)
		{
			mousePos.y = JuEngine::WindowManager::GetSize().y - 20.f;
		}
		else if(mousePos.y > JuEngine::WindowManager::GetSize().y - 10.f)
		{
			mousePos.y = 20.f;
		}

		if(mousePos != mouseOldPos)
		{
			JuEngine::InputManager::MouseSetPosition(mousePos);
		}
	}

	if(JuEngine::InputManager::IsHeld("mouse_r"))
	{
		camera->Rotate(-cameraData->mouseDiff.y / 300.f, -cameraData->mouseDiff.x / 300.f);
	}
	else if(JuEngine::InputManager::IsHeld("mouse_m"))
	{
		transform->Translate(JuEngine::World::Right / cameraMovSpeed * (cameraData->mouseDiff.x / 10.f));
		transform->Translate(JuEngine::World::Up / cameraMovSpeed * -(cameraData->mouseDiff.y / 10.f));
	}

	if(JuEngine::InputManager::IsHeld("debug"))
	{
		//vec3 worldUp = vec3(0.5f, 0.5f, 0.f);
		//transform->LookAt(EntityManager_old::Get("duck")->GetComponent<Transform_old>()->GetPosition(), worldUp);
	}

	if(JuEngine::InputManager::IsPressed("debug"))
	{
		//camera->SetOrthographic(! camera->IsOrthographic());
	}

	auto newPos = transform->GetPosition();

	if(oldPos != newPos)
	{
		//DebugLog::Write("Camera -> X: %f Y: %f Z: %f Pitch: %f Yaw: %f", newPos.x, newPos.y, newPos.z, camera->GetEulerAngles().x, camera->GetEulerAngles().y);

		//vec3 res;
		// Local to World
		//res = transform->TransformPoint(vec3(0.f,5.f,5.f));
		//res = transform->TransformVector(vec3(0.f,0.f,1.f));
		//res = transform->TransformDirection(vec3(0.f,0.f,1.f));
		// World to Local
		//res = transform->InverseTransformPoint(vec3(0.f,5.f,5.f));
		//res = transform->InverseTransformVector(vec3(0.f,0.f,1.f));
		//res = transform->InverseTransformDirection(vec3(0.f,0.f,1.f));
		//DebugLog::Write("%f %f %f", res.x, res.y, res.z);
	}

	if(JuEngine::InputManager::IsHeld("mouse_m") || JuEngine::InputManager::IsHeld("mouse_r"))
	{
		cameraData->lastMousePoint = JuEngine::InputManager::MouseGetPosition();
	}
}
}
