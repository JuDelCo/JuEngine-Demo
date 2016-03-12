// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "DemoSystem.hpp"
#include <JuEngine/Entity/Group.hpp>
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/ImGui/imgui.hpp>
#include <JuEngine/Resources/Shader.hpp>
#include <JuEngine/Resources/Timer.hpp>
#include <JuEngine/App.hpp>
#include <JuEngine/Services/IAppController.hpp>
#include <JuEngine/Services/IDataService.hpp>
#include <JuEngine/Services/IInputService.hpp>
#include <JuEngine/Services/ILevelService.hpp>
#include <JuEngine/Services/ITimeService.hpp>
#include <JuEngine/Services/IWindowService.hpp>
#include <sstream>
#include <iomanip>

namespace Systems
{
void Demo::SetPool(Pool* pool)
{
	mPool = pool;
}

void Demo::Initialize()
{
	App::Data()->Add<Timer>("fps");
}

void Demo::Execute()
{
	if(App::Window()->GetCloseState())
	{
		App::Controller()->Stop();
	}

	static bool show_debug_window = true;

	ImGui::Begin("Debug", &show_debug_window);
	ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::SliderFloat("lightCounter", &lightCounter, 0.f, 64.f, "%.2f"); // READONLY
	ImGui::ColorEdit3("skycolor", (float*)&mPool->GetGroup(Matcher_AllOf(World))->GetSingleEntity()->Get<World>()->GetSkyColor()); // ReadOnly

	if(ImGui::Button("Test button"))
	{
		App::Log()->Debug("Test button pressed!");
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

	if(! App::Window()->HasFocus())
	{
		return;
	}

	if(App::Data()->Get<Timer>("fps")->GetTimeElapsed().AsSeconds() >= 0.5f)
	{
		std::stringstream mBufferTest;
		mBufferTest << std::setprecision(1) << std::fixed << App::Time()->GetFPS(); // std::to_string doesnt work with GCC/win32 :C
		App::Window()->SetTitle("JuEngine Test, FPS: " + mBufferTest.str());
		App::Data()->Get<Timer>("fps")->Reset();
	}

	if(App::Input()->IsPressed("exit"))
	{
		App::Log()->Info("Application stop requested");
		App::Controller()->Stop();
	}

	if(App::Input()->IsPressed("reset_shaders"))
	{
		App::Log()->Info("Reloading all shaders ...");
		Shader::ReloadAll();
	}

	if(App::Input()->IsPressed("reset_scene"))
	{
		App::Log()->Info("Mainscreen level requested to load");
		App::Level()->LoadLevel("lvl_demo");
	}

	if(App::Input()->IsPressed("debug"))
	{
		//DebugLog::Write("Hora actual: %s", DebugLog::GetCurrentTime().c_str());
		//DebugLog::Write("Fecha actual: %s", DebugLog::GetCurrentDate().c_str());
	}
}
}
