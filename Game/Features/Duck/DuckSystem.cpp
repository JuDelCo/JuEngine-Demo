// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "DuckSystem.hpp"
#include "DuckComponent.hpp"
#include <JuEngine/Components/Camera.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include <JuEngine/Entity/Group.hpp>
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Resources/Timer.hpp>
#include <JuEngine/App.hpp>
#include <JuEngine/Services/IDataService.hpp>
#include <JuEngine/Services/IInputService.hpp>
#include <JuEngine/Services/IWindowService.hpp>

namespace Systems
{
void Duck::SetPool(Pool* pool)
{
	mPool = pool;
}

void Duck::Initialize()
{
	auto entities = mPool->GetGroup(Matcher_AllOf(Components::Duck))->GetEntities();

	for(auto &entity : entities)
	{
		auto axis = mPool->CreateEntity();

		axis->Add<Transform>();
		axis->Get<Transform>()->SetParent(entity);
		axis->Add<MeshRenderer>("obj_axis", "mat_vertexColor", true);
	}

	App::Data()->Add<Timer>("interpolation");
}

void Duck::Execute()
{
	if(! App::Window()->HasFocus())
	{
		return;
	}

	if(App::Input()->IsPressed("mouse_l"))
	{
		lastMousePoint = App::Input()->MouseGetPosition();
	}

	if(App::Input()->IsHeld("mouse_l"))
	{
		auto mousePos = App::Input()->MouseGetPosition();
		mouseDiff = lastMousePoint - mousePos;
	}

	auto duckTransform = mPool->GetGroup(Matcher_AllOf(Transform, Components::Duck))->GetEntities().front()->Get<Transform>();
	auto cameraTransform = mPool->GetGroup(Matcher_AllOf(Transform, Camera))->GetSingleEntity()->Get<Transform>();

	// ----------------------------------

	if(App::Input()->IsHeld("mouse_l"))
	{
		if(App::Input()->IsHeld("ctrl"))
		{
			duckTransform->Translate(vec3(-mouseDiff.x / 10000.f, mouseDiff.y / 10000.f, 0.f), cameraTransform);
		}
		else
		{
			duckTransform->Rotate(vec3(mouseDiff.y / 10000.f, mouseDiff.x / 10000.f, 0.f), cameraTransform);
		}
	}

	if(App::Input()->IsPressed("debug"))
	{
		interpolating = true;
		startInterpolating = App::Data()->Get<Timer>("interpolation")->GetTimeElapsed().AsSeconds();
		startOrientation = duckTransform->GetLocalRotation();
	}

	if(App::Input()->IsPressed("n_center"))
	{
		//desiredOrientation = duckTransform->GetLocalRotation();
		desiredOrientation = Math::LookAt(duckTransform->GetPosition(), cameraTransform->GetPosition()) * quat(vec3(0.f, -3.6f / 2.f, 0.f)) * quat(vec3(0.f, 0.f, -0.5f));

		// Si el producto vectorial es < 0, tomará el camino largo, así que invertimos
		if(Math::Dot(duckTransform->GetLocalRotation(), desiredOrientation) < 0)
		{
			desiredOrientation = -desiredOrientation;
		}
	}

	if(interpolating)
	{
		auto timeDiff = (App::Data()->Get<Timer>("interpolation")->GetTimeElapsed().AsSeconds() - startInterpolating) / 1.5f;
		auto orientation = Math::Slerp(startOrientation, desiredOrientation, timeDiff);
		duckTransform->SetLocalRotation(orientation);

		if(timeDiff >= 1.f)
		{
			interpolating = false;
		}
	}

	//float rvel = 0.1f;
	//vec3 rotatePoint = vec3(0.f, 1.f, 0.f);

	if(App::Input()->IsPressed("reset"))
	{
		duckTransform->SetLocalEulerAngles(vec3(0.f,0.f,0.f));
		duckTransform->SetLocalPosition(vec3(0.f,0.f,0.f));
	}
	if(App::Input()->IsHeld("n_up"))
	{
		//duckTransform->Translate(World_old::Up / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Forward, -rvel);
		//duckTransform->Rotate(vec3(0.f,0.f,-rvel), App::Input()->IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,0.f,-rvel), cameraTransform);
	}
	if(App::Input()->IsHeld("n_down"))
	{
		//duckTransform->Translate(-World_old::Up / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Forward, rvel);
		//duckTransform->Rotate(vec3(0.f,0.f,rvel), App::Input()->IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,0.f,rvel), cameraTransform);
	}
	if(App::Input()->IsHeld("n_left"))
	{
		//duckTransform->Translate(World_old::Right / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Up, -rvel);
		//duckTransform->Rotate(vec3(0.f,-rvel,0.f), App::Input()->IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,-rvel,0.f), cameraTransform);
	}
	if(App::Input()->IsHeld("n_right"))
	{
		//duckTransform->Translate(-World_old::Right / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Up, rvel);
		//duckTransform->Rotate(vec3(0.f,rvel,0.f), App::Input()->IsHeld("debug"));
		//duckTransform->Rotate(vec3(0.f,rvel,0.f), cameraTransform);
	}
	if(App::Input()->IsHeld("n_roll_left"))
	{
		//duckTransform->Translate(World_old::Forward / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Right, -rvel);
		//duckTransform->Rotate(vec3(-rvel,0.f,0.f), App::Input()->IsHeld("debug"));
		//duckTransform->Rotate(vec3(-rvel,0.f,0.f), cameraTransform);
	}
	if(App::Input()->IsHeld("n_roll_right"))
	{
		//duckTransform->Translate(-World_old::Forward / 10.f, cameraTransform);
		//duckTransform->RotateAround(rotatePoint, World_old::Right, rvel);
		//duckTransform->Rotate(vec3(rvel,0.f,0.f), App::Input()->IsHeld("debug"));
		//duckTransform->Rotate(vec3(rvel,0.f,0.f), cameraTransform);
	}

	if(App::Input()->IsHeld("mouse_m") || App::Input()->IsHeld("mouse_r"))
	{
		lastMousePoint = App::Input()->MouseGetPosition();
	}
}
}
