// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "CameraSystem.hpp"
#include "CameraComponent.hpp"
#include <JuEngine/Entity/Group.hpp>
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/Camera.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/App.hpp>
#include <JuEngine/Services/IInputService.hpp>
#include <JuEngine/Services/IWindowService.hpp>

namespace Systems
{
void Camera::SetPool(Pool* pool)
{
	mPool = pool;
}

void Camera::Execute()
{
	if(! App::Window()->HasFocus())
	{
		return;
	}

	auto entity = mPool->GetGroup(Matcher_AllOf(Transform, JuEngine::Camera, Components::Camera))->GetSingleEntity();
	auto camera = entity->Use<JuEngine::Camera>();
	auto cameraData = entity->Get<Components::Camera>();
	auto transform = entity->Use<Transform>();

	vec3 oldPos = transform->GetPosition();

	float cameraMovSpeed{10.f};
	if(App::Input()->IsHeld("shift"))       cameraMovSpeed = 2.f;
	if(App::Input()->IsHeld("ctrl"))        cameraMovSpeed = 100.f;

	if(App::Input()->IsHeld("right"))       transform->Translate(World::Right / cameraMovSpeed);
	if(App::Input()->IsHeld("left"))        transform->Translate(-World::Right / cameraMovSpeed);
	if(App::Input()->IsHeld("up"))          transform->Translate(World::Up / cameraMovSpeed);
	if(App::Input()->IsHeld("down"))        transform->Translate(-World::Up / cameraMovSpeed);
	if(App::Input()->IsHeld("forward"))     transform->Translate(World::Forward / cameraMovSpeed);
	if(App::Input()->IsHeld("backward"))    transform->Translate(-World::Forward / cameraMovSpeed);

	if(App::Input()->IsHeld("left_alt"))    camera->Rotate(0.f, -0.05f);
	if(App::Input()->IsHeld("right_alt"))   camera->Rotate(0.f, 0.05f);
	if(App::Input()->IsHeld("up_alt"))      camera->Rotate(0.05f, 0.f);
	if(App::Input()->IsHeld("down_alt"))    camera->Rotate(-0.05f, 0.f);

	if(App::Input()->MouseGetWheelDelta() != 0)
	{
		if(camera->IsOrthographic())
		{
			camera->SetZoom(camera->GetZoom() + (float)App::Input()->MouseGetWheelDelta() * 5.f);
			App::Log()->Debug("Zoom: %f", camera->GetZoom());
		}
		else
		{
			//camera->SetFov(camera->GetFov() + (float)App::Input()->MouseGetWheelDelta() * 5.f);
			//DebugLog::Write("Fov: %f", camera->GetFov());

			transform->Translate(World::Forward / cameraMovSpeed * (float)App::Input()->MouseGetWheelDelta() * 10.f);
		}
	}

	if(App::Input()->IsPressed("mouse_m") || App::Input()->IsPressed("mouse_r"))
	{
		cameraData->lastMousePoint = App::Input()->MouseGetPosition();
	}

	if(App::Input()->IsHeld("mouse_m") || App::Input()->IsHeld("mouse_r"))
	{
		auto mousePos = App::Input()->MouseGetPosition();
		auto mouseOldPos = mousePos;
		cameraData->mouseDiff = cameraData->lastMousePoint - mousePos;

		if(mousePos.x < 10.f)
		{
			mousePos.x = App::Window()->GetSize().x - 20.f;
		}
		else if(mousePos.x > App::Window()->GetSize().x - 10.f)
		{
			mousePos.x = 20.f;
		}

		if(mousePos.y < 10.f)
		{
			mousePos.y = App::Window()->GetSize().y - 20.f;
		}
		else if(mousePos.y > App::Window()->GetSize().y - 10.f)
		{
			mousePos.y = 20.f;
		}

		if(mousePos != mouseOldPos)
		{
			App::Input()->MouseSetPosition(mousePos);
		}
	}

	if(App::Input()->IsHeld("mouse_r"))
	{
		camera->Rotate(-cameraData->mouseDiff.y / 300.f, -cameraData->mouseDiff.x / 300.f);
	}
	else if(App::Input()->IsHeld("mouse_m"))
	{
		transform->Translate(World::Right / cameraMovSpeed * (cameraData->mouseDiff.x / 10.f));
		transform->Translate(World::Up / cameraMovSpeed * -(cameraData->mouseDiff.y / 10.f));
	}

	if(App::Input()->IsHeld("debug"))
	{
		//vec3 worldUp = vec3(0.5f, 0.5f, 0.f);
		//transform->LookAt(EntityManager_old::Get("duck")->GetComponent<Transform_old>()->GetPosition(), worldUp);
	}

	if(App::Input()->IsPressed("debug"))
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

	if(App::Input()->IsHeld("mouse_m") || App::Input()->IsHeld("mouse_r"))
	{
		cameraData->lastMousePoint = App::Input()->MouseGetPosition();
	}
}
}
