// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Includes.hpp>

namespace Scripts
{
class TestMultipleScript : public ScriptBehaviour
{
public:
	TestMultipleScript();
	~TestMultipleScript() = default;

	void Init();
	void Update();
	void FixedUpdate();
};
}
