// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "GamePong.hpp"
#include "Assets.hpp"

#if ! defined(_WIN32) && defined(DEBUG_ON)
	#include <unistd.h>
#endif

void GamePong::Init(const int argc, const char* argv[])
{
	#if ! defined(_WIN32) && defined(DEBUG_ON)
		if(argc <= 1 || (argc > 1 && strcmp(argv[1], "--noconsole") != 0))
		{
			execlp("gnome-terminal", "gnome-terminal", "-x", argv[0], "--noconsole", NULL);
			exit(0);
		}
	#endif

	// ===============================================

	// Load Meshes
	MeshManager::Add("obj_axis",       "axis.dae");
	MeshManager::Add("obj_cube",       "cube.dae");
	MeshManager::Add("obj_sphere",     "sphere.dae");
	//MeshManager::Add("obj_cylinder", "cylinder.dae");
	//MeshManager::Add("obj_cone",     "cone.dae");
	//MeshManager::Add("obj_torus",    "torus.dae");
	//MeshManager::Add("obj_suzanne",  "suzanne.dae");
	MeshManager::Add("obj_duck",       "duck.dae");
	MeshManager::Add("obj_hat",        "hat.dae");
	//MeshManager::Add("obj_test",       "stress/sibenik-cathedral.obj");

	// ------------------------------------
	unsigned int gridSize = 20; /* 20x20 */
	int gridOffset = -(gridSize / 2);
	unsigned int temp, indexH, indexV;
	float color;
	std::vector<float> gridMesh;
	std::vector<unsigned int> gridIndex;
	gridMesh.resize(gridSize * 2 /* H&V */ * 2 * Mesh::mNumVertexAttr, 0.0f);
	gridIndex.resize(gridSize * 2 /* H&V */ * 2, 0);

	for(unsigned int i = 0; i < gridSize; ++i)
	{
		temp = Mesh::mNumVertexAttr;
		indexH = (i * 2 * Mesh::mNumVertexAttr);
		indexV = indexH + (gridSize * 2 * Mesh::mNumVertexAttr);
		color = (i%-gridOffset == 0 ? 0.5f : (i%10 == 0 ? 0.45f : 0.41f));

		gridMesh[indexH+0] = gridOffset;
		gridMesh[indexH+2] = (float)i + gridOffset;
		gridMesh[indexH+4] = 1.0f;
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
		gridMesh[indexV+4] = 1.0f;
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

	MeshManager::Add("obj_grid", gridMesh, gridIndex, GL_LINES);
	// ------------------------------------

	// Load Textures
	// TextureManager::Add("tex_icon", "icon.png");

	// Load Shaders
	//	> Vertex Shaders en uso: BaseVertexColor, BaseUniformColor, Diffuse, VertexLit
	//	> Fragment Shaders en uso: Base, SpecularGaussian
	ShaderManager::Add("shader_baseVertexColor", "BaseVertexColor.vert", "Base.frag");
	ShaderManager::Add("shader_baseUniformColor", "BaseUniformColor.vert", "Base.frag");
	ShaderManager::Add("shader_vertexLit", "VertexLit.vert", "Base.frag");
	//ShaderManager::Add("shader_diffuse", "Diffuse.vert", "Diffuse.frag");
	//ShaderManager::Add("shader_specularPhong", "Diffuse.vert", "SpecularPhong.frag");
	//ShaderManager::Add("shader_specularBlinnPhong", "Diffuse.vert", "SpecularBlinnPhong.frag");
	ShaderManager::Add("shader_specularGaussian", "Diffuse.vert", "SpecularGaussian.frag");
	//ShaderManager::Add("shader_specularGaussianDir", "Diffuse.vert", "SpecularGaussianDir.frag");

	/*auto shaderTestDebug = ShaderManager::Get("shader_specularGaussian");
	DebugLog::Write("------------------------");
	DebugLog::Write("DEBUG: Diffuse.vert and SpecularGaussian.frag attributes:");
	shaderTestDebug->PrintAttributeNames();
	DebugLog::Write("------------------------");
	DebugLog::Write("DEBUG: Diffuse.vert and SpecularGaussian.frag uniforms:");
	shaderTestDebug->PrintUniformNames();
	DebugLog::Write("------------------------");
	DebugLog::Write("DEBUG: Diffuse.vert and SpecularGaussian.frag uniform blocks:");
	shaderTestDebug->PrintUniformBlockNames();
	DebugLog::Write("------------------------");*/

	// Load Materials
	MaterialManager::Add("mat_vertexColor", "tex_default", "shader_baseVertexColor");
	MaterialManager::Add("mat_vertexLit", "tex_default", "shader_vertexLit");
	MaterialManager::Add("mat_plane", "tex_default", "shader_specularGaussian");
	MaterialManager::Get("mat_plane")->SetDiffuseColor(vec3(0.5f, 0.5f, 0.5));
	MaterialManager::Get("mat_plane")->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Get("mat_plane")->SetShininessFactor(0.1f);
	MaterialManager::Add("mat_light", "tex_default", "shader_baseUniformColor");
	MaterialManager::Get("mat_light")->SetDiffuseColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Add("mat_white", "tex_default", "shader_specularGaussian");
	MaterialManager::Get("mat_white")->SetDiffuseColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Get("mat_white")->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Get("mat_white")->SetShininessFactor(0.2f);
	MaterialManager::Add("mat_red", "tex_default", "shader_specularGaussian");
	MaterialManager::Get("mat_red")->SetDiffuseColor(vec3(1.0f, 0.02f, 0.02f));
	MaterialManager::Get("mat_red")->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Get("mat_red")->SetShininessFactor(0.2f);
	MaterialManager::Add("mat_green", "tex_default", "shader_specularGaussian");
	MaterialManager::Get("mat_green")->SetDiffuseColor(vec3(0.02f, 1.0f, 0.02f));
	MaterialManager::Get("mat_green")->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Get("mat_green")->SetShininessFactor(0.2f);
	MaterialManager::Add("mat_blue", "tex_default", "shader_specularGaussian");
	MaterialManager::Get("mat_blue")->SetDiffuseColor(vec3(0.02f, 0.02f, 1.0f));
	MaterialManager::Get("mat_blue")->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	MaterialManager::Get("mat_blue")->SetShininessFactor(0.2f);

	// Load Prefabs
	PrefabManager::Add<Prefabs::CameraEditor>();
	PrefabManager::Add<Prefabs::Duck>();
	PrefabManager::Add<Prefabs::Grid>();
	PrefabManager::Add<Prefabs::Hat>();

	// Load Levels
	LevelManager::Add<Levels::MainScreen>();

	// ===============================================

	// Register Input Bindings
	InputManager::BindMouse("mouse_l",     MOUSE_BUTTON_LEFT);
	InputManager::BindMouse("mouse_r",     MOUSE_BUTTON_RIGHT);
	InputManager::BindMouse("mouse_m",     MOUSE_BUTTON_MIDDLE);
	InputManager::BindKey("ctrl",          KEY_LEFT_CONTROL);
	InputManager::BindKey("shift",         KEY_LEFT_SHIFT);
	InputManager::BindKey("forward",       KEY_W);
	InputManager::BindKey("backward",      KEY_S);
	InputManager::BindKey("left",          KEY_A);
	InputManager::BindKey("right",         KEY_D);
	InputManager::BindKey("up",            KEY_E);
	InputManager::BindKey("down",          KEY_Q);
	InputManager::BindKey("up_alt",        KEY_UP);
	InputManager::BindKey("down_alt",      KEY_DOWN);
	InputManager::BindKey("left_alt",      KEY_LEFT);
	InputManager::BindKey("right_alt",     KEY_RIGHT);
	InputManager::BindKey("n_center",      KEY_KP_5);
	InputManager::BindKey("n_up",          KEY_KP_8);
	InputManager::BindKey("n_down",        KEY_KP_2);
	InputManager::BindKey("n_left",        KEY_KP_4);
	InputManager::BindKey("n_right",       KEY_KP_6);
	InputManager::BindKey("n_roll_left",   KEY_KP_7);
	InputManager::BindKey("n_roll_right",  KEY_KP_9);
	InputManager::BindKey("reset",         KEY_R);
	InputManager::BindKey("reset_scene",   KEY_F1);
	InputManager::BindKey("reset_shaders", KEY_F5);
	InputManager::BindKey("exit",          KEY_ESCAPE);
	InputManager::BindKey("debug",         KEY_SPACE);

	// Start Level
	LevelManager::LoadLevel("lvl_mainScreen");

	// ===============================================
}
