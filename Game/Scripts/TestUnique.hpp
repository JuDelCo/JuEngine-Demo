// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Includes.hpp>

namespace Scripts
{
class TestUniqueScript : public ScriptBehaviour
{
public:
	TestUniqueScript();
	~TestUniqueScript() = default;

	void Init();
	void Update();
	void FixedUpdate();

	vec2 lastMousePoint{0.f,0.f};
	vec2 mouseDiff{0.f,0.f};
	float lightCounter{0.f};
	bool interpolating{false};
	quat startOrientation;
	quat desiredOrientation;
	float startInterpolating;
};
}
