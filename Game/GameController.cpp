// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "GameController.hpp"
#include <JuEngine/Managers/MeshManager.hpp>
#include <JuEngine/Managers/ShaderManager.hpp>
#include <JuEngine/Managers/MaterialManager.hpp>
#include <JuEngine/Managers/PrefabManager.hpp>
#include <JuEngine/Managers/PoolManager.hpp>
#include <JuEngine/Managers/LevelManager.hpp>
#include <JuEngine/Managers/InputManager.hpp>
#include <string.h> // strcmp

#if ! defined(_WIN32) && defined(DEBUG_ON)
	#include <unistd.h> // execlp
#endif

#include "Prefabs/Camera.hpp"
#include "Prefabs/Duck.hpp"
#include "Prefabs/Grid.hpp"
#include "Prefabs/Hat.hpp"
#include "Prefabs/Light.hpp"
#include "Prefabs/Sun.hpp"
#include "Levels/Demo.hpp"

void GameController::Init(const int argc, const char* argv[])
{
	#if ! defined(_WIN32) && defined(DEBUG_ON)
		if(argc <= 1 || (argc > 1 && strcmp(argv[1], "--noconsole") != 0))
		{
			execlp("gnome-terminal", "gnome-terminal", "-x", argv[0], "--noconsole", NULL);
			exit(0);
		}
	#endif

	this->LoadAssets();
	this->ConfigureInput();

	// Start Level
	JuEngine::LevelManager::LoadLevel("lvl_demo");
}

void GameController::LoadAssets()
{
	// Load Meshes
	JuEngine::MeshManager::Add("obj_axis",       "axis.dae");
	JuEngine::MeshManager::Add("obj_cube",       "cube.dae");
	JuEngine::MeshManager::Add("obj_sphere",     "sphere.dae");
	//JuEngine::MeshManager::Add("obj_cylinder", "cylinder.dae");
	//JuEngine::MeshManager::Add("obj_cone",     "cone.dae");
	//JuEngine::MeshManager::Add("obj_torus",    "torus.dae");
	//JuEngine::MeshManager::Add("obj_suzanne",  "suzanne.dae");
	JuEngine::MeshManager::Add("obj_duck",       "duck.dae");
	JuEngine::MeshManager::Add("obj_hat",        "hat.dae");
	//JuEngine::MeshManager::Add("obj_test",       "stress/sibenik-cathedral.obj");

	// ------------------------------------

	{
		unsigned int gridSize = 20; /* 20x20 */
		int gridOffset = -(gridSize / 2);
		unsigned int temp, indexH, indexV;
		float color;
		std::vector<float> gridMesh;
		std::vector<unsigned int> gridIndex;
		gridMesh.resize(gridSize * 2 /* H&V */ * 2 * JuEngine::Mesh::mNumVertexAttr, 0.f);
		gridIndex.resize(gridSize * 2 /* H&V */ * 2, 0);

		// Generate Grid
		for(unsigned int i = 0; i < gridSize; ++i)
		{
			temp = JuEngine::Mesh::mNumVertexAttr;
			indexH = (i * 2 * JuEngine::Mesh::mNumVertexAttr);
			indexV = indexH + (gridSize * 2 * JuEngine::Mesh::mNumVertexAttr);
			color = (i%-gridOffset == 0 ? 0.5f : (i%10 == 0 ? 0.45f : 0.41f));

			gridMesh[indexH+0] = gridOffset;
			gridMesh[indexH+2] = (float)i + gridOffset;
			gridMesh[indexH+4] = 1.f;
			gridMesh[indexH+8] = color;
			gridMesh[indexH+9] = color;
			gridMesh[indexH+10] = color;
			gridMesh[indexH+temp+0] = (float)gridSize + gridOffset;
			gridMesh[indexH+temp+2] = (float)i + gridOffset;
			gridMesh[indexH+temp+8] = color;
			gridMesh[indexH+temp+9] = color;
			gridMesh[indexH+temp+10] = color;

			gridMesh[indexV+0] =(float) i + gridOffset;
			gridMesh[indexV+2] = gridOffset;
			gridMesh[indexV+4] = 1.f;
			gridMesh[indexV+8] = color;
			gridMesh[indexV+9] = color;
			gridMesh[indexV+10] = color;
			gridMesh[indexV+temp+0] = (float)i + gridOffset;
			gridMesh[indexV+temp+2] = (float)gridSize + gridOffset;
			gridMesh[indexV+temp+8] = color;
			gridMesh[indexV+temp+9] = color;
			gridMesh[indexV+temp+10] = color;

			temp = i * 2;
			gridIndex[temp] = temp;
			gridIndex[temp+1] = temp+1;

			temp = i * 2 + gridSize * 2;
			gridIndex[temp] = temp;
			gridIndex[temp+1] = temp+1;
		}

		JuEngine::MeshManager::Add("obj_grid", gridMesh, gridIndex, GL_LINES);
	}

	// ------------------------------------

	// Load Textures
	// JuEngine::TextureManager::Add("tex_icon", "icon.png");

	// Load Shaders
	//	> Vertex Shaders en uso: BaseVertexColor, BaseUniformColor, Diffuse, VertexLit
	//	> Fragment Shaders en uso: Base, SpecularGaussian
	JuEngine::ShaderManager::Add("shader_baseVertexColor", "BaseVertexColor.vert", "Base.frag");
	JuEngine::ShaderManager::Add("shader_baseUniformColor", "BaseUniformColor.vert", "Base.frag");
	JuEngine::ShaderManager::Add("shader_vertexLit", "VertexLit.vert", "Base.frag");
	//JuEngine::ShaderManager::Add("shader_diffuse", "Diffuse.vert", "Diffuse.frag");
	//JuEngine::ShaderManager::Add("shader_specularPhong", "Diffuse.vert", "SpecularPhong.frag");
	//JuEngine::ShaderManager::Add("shader_specularBlinnPhong", "Diffuse.vert", "SpecularBlinnPhong.frag");
	JuEngine::ShaderManager::Add("shader_specularGaussian", "Diffuse.vert", "SpecularGaussian.frag");
	//JuEngine::ShaderManager::Add("shader_specularGaussianDir", "Diffuse.vert", "SpecularGaussianDir.frag");

	/*auto shaderTestDebug = JuEngine::ShaderManager::Get("shader_specularGaussian");
	JuEngine::DebugLog::Write("------------------------");
	JuEngine::DebugLog::Write("DEBUG: Diffuse.vert and SpecularGaussian.frag attributes:");
	shaderTestDebug->PrintAttributeNames();
	JuEngine::DebugLog::Write("------------------------");
	JuEngine::DebugLog::Write("DEBUG: Diffuse.vert and SpecularGaussian.frag uniforms:");
	shaderTestDebug->PrintUniformNames();
	JuEngine::DebugLog::Write("------------------------");
	JuEngine::DebugLog::Write("DEBUG: Diffuse.vert and SpecularGaussian.frag uniform blocks:");
	shaderTestDebug->PrintUniformBlockNames();
	JuEngine::DebugLog::Write("------------------------");*/

	// Load Materials
	JuEngine::MaterialManager::Add("mat_vertexColor", "tex_default", "shader_baseVertexColor");
	JuEngine::MaterialManager::Add("mat_vertexLit", "tex_default", "shader_vertexLit");
	JuEngine::MaterialManager::Add("mat_plane", "tex_default", "shader_specularGaussian");
	JuEngine::MaterialManager::Get("mat_plane")->SetDiffuseColor(vec3(0.5f, 0.5f, 0.5));
	JuEngine::MaterialManager::Get("mat_plane")->SetSpecularColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Get("mat_plane")->SetShininessFactor(0.1f);
	JuEngine::MaterialManager::Add("mat_light", "tex_default", "shader_baseUniformColor");
	JuEngine::MaterialManager::Get("mat_light")->SetDiffuseColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Add("mat_white", "tex_default", "shader_specularGaussian");
	JuEngine::MaterialManager::Get("mat_white")->SetDiffuseColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Get("mat_white")->SetSpecularColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Get("mat_white")->SetShininessFactor(0.2f);
	JuEngine::MaterialManager::Add("mat_red", "tex_default", "shader_specularGaussian");
	JuEngine::MaterialManager::Get("mat_red")->SetDiffuseColor(vec3(1.f, 0.02f, 0.02f));
	JuEngine::MaterialManager::Get("mat_red")->SetSpecularColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Get("mat_red")->SetShininessFactor(0.2f);
	JuEngine::MaterialManager::Add("mat_green", "tex_default", "shader_specularGaussian");
	JuEngine::MaterialManager::Get("mat_green")->SetDiffuseColor(vec3(0.02f, 1.f, 0.02f));
	JuEngine::MaterialManager::Get("mat_green")->SetSpecularColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Get("mat_green")->SetShininessFactor(0.2f);
	JuEngine::MaterialManager::Add("mat_blue", "tex_default", "shader_specularGaussian");
	JuEngine::MaterialManager::Get("mat_blue")->SetDiffuseColor(vec3(0.02f, 0.02f, 1.f));
	JuEngine::MaterialManager::Get("mat_blue")->SetSpecularColor(vec3(1.f, 1.f, 1.f));
	JuEngine::MaterialManager::Get("mat_blue")->SetShininessFactor(0.2f);

	// Load Prefabs
	JuEngine::PrefabManager::Add<Prefabs::Camera>();
	JuEngine::PrefabManager::Add<Prefabs::Duck>();
	JuEngine::PrefabManager::Add<Prefabs::Grid>();
	JuEngine::PrefabManager::Add<Prefabs::Hat>();
	JuEngine::PrefabManager::Add<Prefabs::Light>();
	JuEngine::PrefabManager::Add<Prefabs::Sun>();

	// Load Levels
	JuEngine::LevelManager::Add<Levels::Demo>();
}

void GameController::ConfigureInput()
{
	// Register Input Bindings
	JuEngine::InputManager::BindMouse("mouse_l",     MOUSE_BUTTON_LEFT);
	JuEngine::InputManager::BindMouse("mouse_r",     MOUSE_BUTTON_RIGHT);
	JuEngine::InputManager::BindMouse("mouse_m",     MOUSE_BUTTON_MIDDLE);
	JuEngine::InputManager::BindKey("ctrl",          KEY_LEFT_CONTROL);
	JuEngine::InputManager::BindKey("shift",         KEY_LEFT_SHIFT);
	JuEngine::InputManager::BindKey("forward",       KEY_W);
	JuEngine::InputManager::BindKey("backward",      KEY_S);
	JuEngine::InputManager::BindKey("left",          KEY_A);
	JuEngine::InputManager::BindKey("right",         KEY_D);
	JuEngine::InputManager::BindKey("up",            KEY_E);
	JuEngine::InputManager::BindKey("down",          KEY_Q);
	JuEngine::InputManager::BindKey("up_alt",        KEY_UP);
	JuEngine::InputManager::BindKey("down_alt",      KEY_DOWN);
	JuEngine::InputManager::BindKey("left_alt",      KEY_LEFT);
	JuEngine::InputManager::BindKey("right_alt",     KEY_RIGHT);
	JuEngine::InputManager::BindKey("n_center",      KEY_KP_5);
	JuEngine::InputManager::BindKey("n_up",          KEY_KP_8);
	JuEngine::InputManager::BindKey("n_down",        KEY_KP_2);
	JuEngine::InputManager::BindKey("n_left",        KEY_KP_4);
	JuEngine::InputManager::BindKey("n_right",       KEY_KP_6);
	JuEngine::InputManager::BindKey("n_roll_left",   KEY_KP_7);
	JuEngine::InputManager::BindKey("n_roll_right",  KEY_KP_9);
	JuEngine::InputManager::BindKey("reset",         KEY_R);
	JuEngine::InputManager::BindKey("reset_scene",   KEY_F1);
	JuEngine::InputManager::BindKey("reset_shaders", KEY_F5);
	JuEngine::InputManager::BindKey("exit",          KEY_ESCAPE);
	JuEngine::InputManager::BindKey("debug",         KEY_SPACE);
}
