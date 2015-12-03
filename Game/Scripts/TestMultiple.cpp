// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "TestMultiple.hpp"

namespace Scripts
{
TestMultipleScript::TestMultipleScript()
{
	SetName("script_multiple_test");
}

void TestMultipleScript::Init()
{
	//TimerManager::Create("test");
}

void TestMultipleScript::Update()
{
	//
}

void TestMultipleScript::FixedUpdate()
{
	//auto time = TimerManager::Get("test")->GetTimeElapsed().asSeconds();
	//mEntity->GetComponent<Transform>()->SetLocalPosition(vec3(sin(time)/1.5f, cos(time)/2.0f, sin(time)/1.5f));
	//mEntity->GetComponent<Transform>()->Rotate(vec3(0.0f, 0.0f, time));
	//mEntity->GetComponent<Transform>()->SetLocalScale(vec3(1.0f, 1.0f, sin(time/1.5f)+1.2f));
	//TimerManager::Get("test")->Reset();
}
}
