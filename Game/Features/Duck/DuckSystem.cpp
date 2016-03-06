// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "DuckSystem.hpp"
#include <JuEngine/Components/Camera.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Managers/InputManager.hpp>
#include <JuEngine/Managers/TimerManager.hpp>
#include "DuckComponent.hpp"

namespace Systems
{
void Duck::SetPool(JuEngine::Pool* pool)
{
	mPool = pool;
}

void Duck::Initialize()
{
	auto entities = mPool->GetGroup(Matcher_AllOf(Components::Duck))->GetEntities();

	for(auto &entity : entities)
	{
		auto axis = mPool->CreateEntity();

		axis->Add<JuEngine::Transform>();
		axis->GetTransform()->SetParent(entity);
		axis->Add<JuEngine::MeshRenderer>("obj_axis", "mat_vertexColor", true);
	}

	JuEngine::TimerManager::Create("interpolation");
}

void Duck::Execute()
{
	if(! JuEngine::InputManager::IsWindowActive())
	{
		return;
	}

	if(JuEngine::InputManager::IsPressed("mouse_l"))
	{
		lastMousePoint = JuEngine::InputManager::MouseGetPosition();
	}

	if(JuEngine::InputManager::IsHeld("mouse_l"))
	{
		auto mousePos = JuEngine::InputManager::MouseGetPosition();
		mouseDiff = lastMousePoint - mousePos;
	}

	auto duckTransform = mPool->GetGroup(Matcher_AllOf(JuEngine::Transform, Components::Duck))->GetEntities().front()->GetTransform();
	auto cameraTransform = mPool->GetGroup(Matcher_AllOf(JuEngine::Transform, JuEngine::Camera))->GetSingleEntity()->GetTransform();

	// ----------------------------------

	if(JuEngine::InputManager::IsHeld("mouse_l"))
	{
		if(JuEngine::InputManager::IsHeld("ctrl"))
		{
			duckTransform->Translate(vec3(-mouseDiff.x / 10000.f, mouseDiff.y / 10000.f, 0.f), cameraTransform);
		}
		else
		{
			duckTransform->Rotate(vec3(mouseDiff.y / 10000.f, mouseDiff.x / 10000.f, 0.f), cameraTransform);
		}
	}

	if(JuEngine::InputManager::IsPressed("debug"))
	{
		interpolating = true;
		startInterpolating = JuEngine::TimerManager::Get("interpolation")->GetTimeElapsed().AsSeconds();
		startOrientation = duckTransform->GetLocalRotation();
	}

	if(JuEngine::InputManager::IsPressed("n_center"))
	{
		//desiredOrientation = duckTransform->GetLocalRotation();
		desiredOrientation = JuEngine::Math::LookAt(duckTransform->GetPosition(), cameraTransform->GetPosition()) * quat(vec3(0.f, -3.6f / 2.f, 0.f)) * quat(vec3(0.f, 0.f, -0.5f));

		// Si el producto vectorial es < 0, tomará el camino largo, así que invertimos
		if(JuEngine::Math::Dot(duckTransform->GetLocalRotation(), desiredOrientation) < 0)
		{
			desiredOrientation = -desiredOrientation;
		}
	}

	if(interpolating)
	{
		auto timeDiff = (JuEngine::TimerManager::Get("interpolation")->GetTimeElapsed().AsSeconds() - startInterpolating) / 1.5f;
		auto orientation = JuEngine::Math::Slerp(startOrientation, desiredOrientation, timeDiff);
		duckTransform->SetLocalRotation(orientation);

		if(timeDiff >= 1.f)
		{
			interpolating = false;
		}
	}

	//float rvel = 0.1f;
	//vec3 rotatePoint = vec3(0.f, 1.f, 0.f);

	if(JuEngine::InputManager::IsPressed("reset"))
	{
		duckTransform->SetLocalEulerAngles(vec3(0.f,0.f,0.f));
		duckTransform->SetLocalPosition(vec3(0.f,0.f,0.f));
	}
	if(JuEngine::InputManager::IsHeld("n_up"))
	{
		//duckTransform->Translate(World_old::Up / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Forward, -rvel);
		//duckTransform->Rotate(vec3(0.f,0.f,-rvel), InputManager::IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,0.f,-rvel), cameraTransform);
	}
	if(JuEngine::InputManager::IsHeld("n_down"))
	{
		//duckTransform->Translate(-World_old::Up / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Forward, rvel);
		//duckTransform->Rotate(vec3(0.f,0.f,rvel), InputManager::IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,0.f,rvel), cameraTransform);
	}
	if(JuEngine::InputManager::IsHeld("n_left"))
	{
		//duckTransform->Translate(World_old::Right / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Up, -rvel);
		//duckTransform->Rotate(vec3(0.f,-rvel,0.f), InputManager::IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,-rvel,0.f), cameraTransform);
	}
	if(JuEngine::InputManager::IsHeld("n_right"))
	{
		//duckTransform->Translate(-World_old::Right / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Up, rvel);
		//duckTransform->Rotate(vec3(0.f,rvel,0.f), InputManager::IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,rvel,0.f), cameraTransform);
	}
	if(JuEngine::InputManager::IsHeld("n_roll_left"))
	{
		//duckTransform->Translate(World_old::Forward / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Right, -rvel);
		//duckTransform->Rotate(vec3(-rvel,0.f,0.f), InputManager::IsHeld("debug"));
		//duckTransform->Rotate(vec3(-rvel,0.f,0.f), cameraTransform);
	}
	if(JuEngine::InputManager::IsHeld("n_roll_right"))
	{
		//duckTransform->Translate(-World_old::Forward / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Right, rvel);
		//duckTransform->Rotate(vec3(rvel,0.f,0.f), InputManager::IsHeld("debug"));
		//duckTransform->Rotate(vec3(rvel,0.f,0.f), cameraTransform);
	}

	if(JuEngine::InputManager::IsHeld("mouse_m") || JuEngine::InputManager::IsHeld("mouse_r"))
	{
		lastMousePoint = JuEngine::InputManager::MouseGetPosition();
	}
}
}
