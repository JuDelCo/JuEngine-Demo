// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "DemoSystem.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/Managers/AppTimeManager.hpp>
#include <JuEngine/Managers/InputManager.hpp>
#include <JuEngine/Managers/LevelManager.hpp>
#include <JuEngine/Managers/ShaderManager.hpp>
#include <JuEngine/Managers/TimerManager.hpp>
#include <JuEngine/Managers/WindowManager.hpp>
#include <JuEngine/Resources/DebugLog.hpp>
#include <JuEngine/Application.hpp>
#include <JuEngine/ImGui/imgui.hpp>
#include <sstream>
#include <iomanip>

namespace Systems
{
void Demo::SetPool(JuEngine::Pool* pool)
{
	mPool = pool;
}

void Demo::Initialize()
{
	JuEngine::TimerManager::Create("fps");
}

void Demo::Execute()
{
	if(JuEngine::WindowManager::GetCloseState())
	{
		JuEngine::Application::Stop();
	}

	static bool show_debug_window = true;

	ImGui::Begin("Debug", &show_debug_window);
	ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::SliderFloat("lightCounter", &lightCounter, 0.f, 64.f, "%.2f"); // READONLY
	ImGui::ColorEdit3("skycolor", (float*)&mPool->GetGroup(Matcher_AllOf(JuEngine::World))->GetSingleEntity()->Get<JuEngine::World>()->GetSkyColor()); // ReadOnly

	if(ImGui::Button("Test button"))
	{
		JuEngine::DebugLog::Write("Test button pressed!");
	}
	ImGui::End();

	/*
		testBar->AddVarCallback("sunPos", VarType::DIR3,
		[](const void* value, void*) {},
		[](void* value, void*)
		{
			testSunPosition = glm::normalize(EntityManager_old::Get("camera")->GetComponent<Transform_old>()->GetPosition() - EntityManager_old::Get("sun")->GetComponent<Transform_old>()->GetPosition());
			testSunPosition = -EntityManager_old::Get("camera")->GetComponent<Transform_old>()->InverseTransformDirection(testSunPosition);
			testSunPosition = vec3(testSunPosition.x, testSunPosition.y, -testSunPosition.z);
			*(vec3*)value = testSunPosition;
		});
		testBar->SetVarReadOnly("sunPos", true);
	*/

	if(! JuEngine::InputManager::IsWindowActive())
	{
		return;
	}

	if(JuEngine::TimerManager::Get("fps")->GetTimeElapsed().AsSeconds() >= 0.5f)
	{
		std::stringstream mBufferTest;
		mBufferTest << std::setprecision(1) << std::fixed << JuEngine::AppTimeManager::GetFPS(); // std::to_string doesnt work with GCC/win32 :C
		JuEngine::WindowManager::SetTitle("JuEngine Test, FPS: " + mBufferTest.str());
		JuEngine::TimerManager::Get("fps")->Reset();
	}

	if(JuEngine::InputManager::IsPressed("exit"))
	{
		JuEngine::DebugLog::Write("Application stop requested");
		JuEngine::Application::Stop();
	}

	if(JuEngine::InputManager::IsPressed("reset_shaders"))
	{
		JuEngine::DebugLog::Write("Reloading all shaders ...");
		JuEngine::ShaderManager::ReloadAll();
	}

	if(JuEngine::InputManager::IsPressed("reset_scene"))
	{
		JuEngine::DebugLog::Write("Mainscreen level requested to load");
		JuEngine::LevelManager::LoadLevel("lvl_demo");
	}

	if(JuEngine::InputManager::IsPressed("debug"))
	{
		//DebugLog::Write("Hora actual: %s", DebugLog::GetCurrentTime().c_str());
		//DebugLog::Write("Fecha actual: %s", DebugLog::GetCurrentDate().c_str());
	}
}
}
