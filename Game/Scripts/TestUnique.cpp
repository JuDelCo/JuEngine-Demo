// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "TestUnique.hpp"
#include <sstream>
#include <iomanip>

namespace Scripts
{
bool testBool;
int testInt;
string testString = "prueba :D";
JuEngine::quat testQuat;
vec3 testSunPosition;

TestUniqueScript::TestUniqueScript()
{
	SetName("script_unique_test");
}

void TestUniqueScript::Init()
{
	TimerManager::Create("fps");

	vector<Entity*> entities;

	EntityManager::ForEach([&entities](Entity* e)
	{
		entities.push_back(e);
	});

	for(Entity* entity : entities)
	{
		if(entity->GetName() != "duck") continue;

		auto axis = EntityManager::Create("axis");
		axis->CreateComponent<MeshRenderer>("obj_axis", "mat_vertexColor")->SetForceDraw(true);
		axis->GetComponent<Transform>()->SetParent(entity);
	}

	TimerManager::Create("interpolation");
}

void TestUniqueScript::Update()
{
	if(WindowManager::GetCloseState())
	{
		Application::Stop();
	}

// ----------------------------------------------------------------------

	static bool show_debug_window = true;

	ImGui::Begin("Debug", &show_debug_window);
	ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat("lightCounter", &lightCounter, 0.0f, 64.0f, "%.2f"); // READONLY
	ImGui::ColorEdit3("skyColor", (float*)&EntityManager::GetWorld()->GetSkyColor()); // READONLY

	if(ImGui::Button("Test button"))
	{
		DebugLog::Write("Test button pressed!");
	}
	ImGui::End();

/*
	testBar->AddVarCallback("sunPos", VarType::DIR3,
	[](const void* value, void*) {},
	[](void* value, void*)
	{
		testSunPosition = glm::normalize(EntityManager::Get("camera")->GetComponent<Transform>()->GetPosition() - EntityManager::Get("sun")->GetComponent<Transform>()->GetPosition());
		testSunPosition = -EntityManager::Get("camera")->GetComponent<Transform>()->InverseTransformDirection(testSunPosition);
		testSunPosition = vec3(testSunPosition.x, testSunPosition.y, -testSunPosition.z);
		*(vec3*)value = testSunPosition;
	});
	testBar->SetVarReadOnly("sunPos", true);
*/
// ----------------------------------------------------------------------

	if(TimerManager::Get("fps")->GetTimeElapsed().AsSeconds() >= 0.5f)
	{
		std::stringstream mBufferTest;
		mBufferTest << std::setprecision(1) << std::fixed << AppTimeManager::GetFPS(); // std::to_string doesnt work with GCC/win32 :C
		WindowManager::SetTitle("JuEngine Test, FPS: " + mBufferTest.str());
		TimerManager::Get("fps")->Reset();
	}

	float sunVel = 0.1f;
	float sunForce = Math::Clamp(Math::Clamp((float)cos(lightCounter * sunVel)) * 3.0f, 0.f, 1.0f);
	EntityManager::Get("sun")->GetComponent<Transform>()->SetLocalPosition(vec3(-sin(lightCounter * sunVel) * 4500.0f, cos(lightCounter * sunVel) * 4500.0f, 0.f));
	EntityManager::Get("sun")->GetComponent<Light>()->SetIntensity(sunForce * 1.0f);
	EntityManager::GetWorld()->SetAmbientIntensity(sunForce * 0.1f);
	EntityManager::GetWorld()->SetSkyColor(vec3(0.529f, 0.807f, 1.0f) * sunForce);
	EntityManager::GetWorld()->SetLightAttenuation(0.1f + 0.9f * sunForce);

	EntityManager::Get("light1")->GetComponent<Transform>()->SetLocalPosition(vec3(sin(lightCounter + Math::PI * 0.0f) * 5.0f, 1.0f, cos(lightCounter + Math::PI * 0.0f) * 5.0f));
	EntityManager::Get("light2")->GetComponent<Transform>()->SetLocalPosition(vec3(sin(lightCounter + Math::PI * 0.5f) * 5.0f, 1.0f, cos(lightCounter + Math::PI * 0.5f) * 5.0f));
	EntityManager::Get("light3")->GetComponent<Transform>()->SetLocalPosition(vec3(sin(lightCounter + Math::PI * 1.0f) * 5.0f, 1.0f, cos(lightCounter + Math::PI * 1.0f) * 5.0f));
	EntityManager::Get("light4")->GetComponent<Transform>()->SetLocalPosition(vec3(sin(lightCounter + Math::PI * 1.5f) * 5.0f, 1.0f, cos(lightCounter + Math::PI * 1.5f) * 5.0f));
	lightCounter += 0.01;

	if(InputManager::IsHeld("n_up"))
	{
		//EntityManager::Get("light")->GetComponent<Transform>()->Translate(vec3(0.f, 0.02f, 0.f));
	}
	if(InputManager::IsHeld("n_down"))
	{
		//EntityManager::Get("light")->GetComponent<Transform>()->Translate(vec3(0.f, -0.02f, 0.f));
	}

	if(! InputManager::IsWindowActive())
	{
		return;
	}

	if(InputManager::IsPressed("mouse_l"))
	{
		lastMousePoint = InputManager::MouseGetPosition();
	}

	if(InputManager::IsHeld("mouse_l"))
	{
		auto mousePos = InputManager::MouseGetPosition();
		mouseDiff = lastMousePoint - mousePos;
	}

	if(InputManager::IsPressed("reset_shaders"))
	{
		DebugLog::Write("Reloading all shaders ...");
		ShaderManager::ReloadAll();
	}

	if(InputManager::IsPressed("reset_scene"))
	{
		DebugLog::Write("Mainscreen level requested to load");
		LevelManager::LoadLevel("lvl_mainScreen");
	}

	if(InputManager::IsPressed("debug"))
	{
		//DebugLog::Write("Hora actual: %s", DebugLog::GetCurrentTime().c_str());
		//DebugLog::Write("Fecha actual: %s", DebugLog::GetCurrentDate().c_str());
	}

	if(InputManager::IsPressed("exit"))
	{
		DebugLog::Write("Application stop requested");
		Application::Stop();
	}

	Transform* duck_transform = EntityManager::Get("duck")->GetComponent<Transform>();
	//float rvel = 0.1f;
	//vec3 rotatePoint = vec3(0.f, 1.0f, 0.f);
	Transform* cameraTransform = EntityManager::Get("camera")->GetComponent<Transform>();

	// ----------------------------------

	//vec3 res;
	// Local to World
	//res = cameraTransform->TransformPoint(vec3(0.f,5.0f,5.0f));
	//res = cameraTransform->TransformVector(vec3(0.f,0.f,1.0f));
	//res = cameraTransform->TransformDirection(vec3(0.f,0.f,1.0f));
	// World to Local
	//res = cameraTransform->InverseTransformPoint(vec3(0.f,5.0f,5.0f));
	//res = cameraTransform->InverseTransformVector(vec3(0.f,0.f,1.0f));
	//res = cameraTransform->InverseTransformDirection(vec3(0.f,0.f,1.0f));
	//DebugLog::Write("%f %f %f", res.x, res.y, res.z);

	// ----------------------------------

	if(InputManager::IsHeld("mouse_l"))
	{
		if(InputManager::IsHeld("ctrl"))
		{
			duck_transform->Translate(vec3(-mouseDiff.x / 10000.0f, mouseDiff.y / 10000.0f, 0.f), cameraTransform);
		}
		else
		{
			duck_transform->Rotate(vec3(mouseDiff.y / 10000.0f, mouseDiff.x / 10000.0f, 0.f), cameraTransform);
		}
	}

	if(InputManager::IsPressed("debug"))
	{
		interpolating = true;
		startInterpolating = TimerManager::Get("interpolation")->GetTimeElapsed().AsSeconds();
		startOrientation = duck_transform->GetLocalRotation();
	}

	if(InputManager::IsPressed("n_center"))
	{
		//desiredOrientation = duck_transform->GetLocalRotation();
		desiredOrientation = Math::LookAt(duck_transform->GetPosition(), cameraTransform->GetPosition()) * quat(vec3(0.f, -3.6f / 2.0f, 0.f)) * quat(vec3(0.f, 0.f, -0.5f));

		// Si el producto vectorial es < 0, tomará el camino largo, así que invertimos
		if(Math::Dot(duck_transform->GetLocalRotation(), desiredOrientation) < 0)
		{
			desiredOrientation = -desiredOrientation;
		}
	}

	if(interpolating)
	{
		auto timeDiff = (TimerManager::Get("interpolation")->GetTimeElapsed().AsSeconds() - startInterpolating) / 1.5f;
		auto orientation = Math::Slerp(startOrientation, desiredOrientation, timeDiff);
		duck_transform->SetLocalRotation(orientation);

		if(timeDiff >= 1.0f)
		{
			interpolating = false;
		}
	}

	if(InputManager::IsPressed("reset"))
	{
		duck_transform->SetLocalEulerAngles(vec3(0.f,0.f,0.f));
		duck_transform->SetLocalPosition(vec3(0.f,0.f,0.f));
	}
	if(InputManager::IsHeld("n_up"))
	{
		//duck_transform->Translate(World::Up / 10.0f, cameraTransform);
		//duck_transform->RotateAround(rotatePoint, World::Forward, -rvel);
		//duck_transform->Rotate(vec3(0.f,0.f,-rvel), InputManager::IsHeld("debug"));
		//duck_transform->Rotate(vec3(0.f,0.f,-rvel), cameraTransform);
	}
	if(InputManager::IsHeld("n_down"))
	{
		//duck_transform->Translate(-World::Up / 10.0f, cameraTransform);
		//duck_transform->RotateAround(rotatePoint, World::Forward, rvel);
		//duck_transform->Rotate(vec3(0.f,0.f,rvel), InputManager::IsHeld("debug"));
		//duck_transform->Rotate(vec3(0.f,0.f,rvel), cameraTransform);
	}
	if(InputManager::IsHeld("n_left"))
	{
		//duck_transform->Translate(World::Right / 10.0f, cameraTransform);
		//duck_transform->RotateAround(rotatePoint, World::Up, -rvel);
		//duck_transform->Rotate(vec3(0.f,-rvel,0.f), InputManager::IsHeld("debug"));
		//duck_transform->Rotate(vec3(0.f,-rvel,0.f), cameraTransform);
	}
	if(InputManager::IsHeld("n_right"))
	{
		//duck_transform->Translate(-World::Right / 10.0f, cameraTransform);
		//duck_transform->RotateAround(rotatePoint, World::Up, rvel);
		//duck_transform->Rotate(vec3(0.f,rvel,0.f), InputManager::IsHeld("debug"));
		//duck_transform->Rotate(vec3(0.f,rvel,0.f), cameraTransform);
	}
	if(InputManager::IsHeld("n_roll_left"))
	{
		//duck_transform->Translate(World::Forward / 10.0f, cameraTransform);
		//duck_transform->RotateAround(rotatePoint, World::Right, -rvel);
		//duck_transform->Rotate(vec3(-rvel,0.f,0.f), InputManager::IsHeld("debug"));
		//duck_transform->Rotate(vec3(-rvel,0.f,0.f), cameraTransform);
	}
	if(InputManager::IsHeld("n_roll_right"))
	{
		//duck_transform->Translate(-World::Forward / 10.f, cameraTransform);
		//duck_transform->RotateAround(rotatePoint, World::Right, rvel);
		//duck_transform->Rotate(vec3(rvel,0.f,0.f), InputManager::IsHeld("debug"));
		//duck_transform->Rotate(vec3(rvel,0.f,0.f), cameraTransform);
	}

	if(InputManager::IsHeld("mouse_m") || InputManager::IsHeld("mouse_r"))
	{
		lastMousePoint = InputManager::MouseGetPosition();
	}
}

void TestUniqueScript::FixedUpdate()
{
	//
}
}
