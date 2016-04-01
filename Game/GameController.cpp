// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "GameController.hpp"
#include "Prefabs/Camera.hpp"
#include "Prefabs/Grid.hpp"
#include "Prefabs/Light.hpp"
#include "Prefabs/ModelTest.hpp"
#include "Levels/Demo.hpp"
#include <JuEngine/Resources/Material.hpp>
#include <JuEngine/Resources/MeshLoader.hpp>
#include <JuEngine/Resources/Shader.hpp>
#include <JuEngine/Resources/Texture.hpp>
#include <JuEngine/App.hpp>
#include <JuEngine/Services/IDataService.hpp>
#include <JuEngine/Services/IInputService.hpp>
#include <JuEngine/Managers/InputDefines.hpp>
#include <JuEngine/Services/ILevelService.hpp>

#include <string.h> // strcmp

#if ! defined(_WIN32) && defined(DEBUG_ON)
	#include <unistd.h> // execlp
#endif

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
	App::Level()->LoadLevel<Levels::Demo>();
}

void GameController::LoadAssets()
{
	// Load Shaders
	App::Data()->Add<Shader>("shader_vertexColor",		"Assets/Shaders/vertexColor.vert",		"Assets/Shaders/vertexColor.frag");
	//App::Data()->Add<Shader>("shader_diffuseColor",	"Assets/Shaders/diffuseColor.vert",		"Assets/Shaders/diffuseColor.frag");
	//App::Data()->Add<Shader>("shader_gouraudShading",	"Assets/Shaders/gouraudShading.vert",	"Assets/Shaders/gouraudShading.frag");
	App::Data()->Add<Shader>("shader_phongShading",		"Assets/Shaders/phongShading.vert",		"Assets/Shaders/phongShading.frag");

	/*auto shaderTestDebug = App::Data()->Get<Shader>("shader_vertexColor");
	App::Log()->Debug("------------------------");
	App::Log()->Debug("DEBUG: vertexColor.vert and vertexColor.frag attributes:\n\n%s", shaderTestDebug->PrintAttributeNames().c_str());
	App::Log()->Debug("------------------------");
	App::Log()->Debug("DEBUG: vertexColor.vert and vertexColor.frag uniforms:\n\n%s", shaderTestDebug->PrintUniformNames().c_str());
	App::Log()->Debug("------------------------");
	App::Log()->Debug("DEBUG: vertexColor.vert and vertexColor.frag uniform blocks:\n\n%s", shaderTestDebug->PrintUniformBlockNames().c_str());
	App::Log()->Debug("------------------------");*/

	// Load Textures
	//App::Data()->Add<Texture>("tex_sanic", "sanic.png");

	// Load Materials
	App::Data()->Add<Material>("mat_vertexColor") // Grid & Lights
		->SetDiffuseColor(vec3(1.f, 1.f, 1.f))
		->SetSpecularColor(vec3(1.f, 1.f, 1.f))
		->SetShininessFactor(32.f);

	// Load Meshes
	App::Data()->Set<MeshNode>("obj_cube", MeshLoader::Load("Assets/Models/cube.dae", MeshVertexFormat::PositionColor)); // TODO: Asignar materíal "mat_vertexColor"
	App::Data()->Set<MeshNode>("obj_sphere", MeshLoader::Load("Assets/Models/sphere.dae", MeshVertexFormat::PositionNormalColor));
	//App::Data()->Set<MeshNode>("obj_quad", MeshLoader::GenerateQuad((new Material())->SetTexture("diffuse0", App::Data()->Get<Texture>("tex_sanic"))));
	// Test Meshes
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/axis.dae", MeshVertexFormat::PositionNormalColor));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/bunny/bunny2.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/bunny/bunny.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/crytek-sponza/banner.obj", MeshVertexFormat::PositionNormalTexture));
	App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/crytek-sponza/sponza.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/dabrovic-sponza/sponza.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/flowey/curso1.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/head/head.OBJ", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/lost-empire/lost_empire.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/lucy/lucy_20_lakh.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/lucy/lucy_low_2.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/mitsuba/mitsuba.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/mitsuba/mitsuba-sphere.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/nanosuit/nanosuit.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/rungholt/house.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/rungholt/rungholt.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/san-miguel/san-miguel.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/sibenik-cathedral/sibenik.obj", MeshVertexFormat::PositionNormalTexture));
	//App::Data()->Set<MeshNode>("obj_test", MeshLoader::Load("Assets/Models/stress/teapot/teapot.obj", MeshVertexFormat::PositionNormalTexture));

	// ------------------------------------

	{
		unsigned int gridSize = 20; /* 20x20 */
		int gridOffset = -(gridSize / 2);
		unsigned int temp, indexH, indexV;
		float color;
		float* floatPackedValue;
		std::vector<float> gridMesh;
		std::vector<unsigned int> gridIndex;
		unsigned int NumVertexAttr = Mesh::GetNumVertexAttr(MeshVertexFormat::PositionColor);
		gridMesh.resize(gridSize * 2 /* H&V */ * 2 * NumVertexAttr, 0.f);
		gridIndex.resize(gridSize * 2 /* H&V */ * 2, 0);

		// Generate Grid
		for(unsigned int i = 0; i < gridSize; ++i)
		{
			temp = NumVertexAttr;
			indexH = (i * 2 * NumVertexAttr);
			indexV = indexH + (gridSize * 2 * NumVertexAttr);
			color = (i%-gridOffset == 0 ? 0.5f : (i%10 == 0 ? 0.45f : 0.41f));

			uint32_t packedValue = 0;
			packedValue = packedValue | (((unsigned int)(color * 1023)) << 20); // B
			packedValue = packedValue | (((unsigned int)(color * 1023)) << 10); // G
			packedValue = packedValue | (((unsigned int)(color * 1023)) << 0);  // R
			floatPackedValue = (float*)&packedValue;

			gridMesh[indexH+0] = gridOffset;
			gridMesh[indexH+2] = (float)i + gridOffset;
			gridMesh[indexH+3] = *floatPackedValue;

			gridMesh[indexH+temp+0] = (float)gridSize + gridOffset;
			gridMesh[indexH+temp+2] = (float)i + gridOffset;
			gridMesh[indexH+temp+3] = *floatPackedValue;

			gridMesh[indexV+0] =(float) i + gridOffset;
			gridMesh[indexV+2] = gridOffset;
			gridMesh[indexV+3] = *floatPackedValue;

			gridMesh[indexV+temp+0] = (float)i + gridOffset;
			gridMesh[indexV+temp+2] = (float)gridSize + gridOffset;
			gridMesh[indexV+temp+3] = *floatPackedValue;

			temp = i * 2;
			gridIndex[temp] = temp;
			gridIndex[temp+1] = temp+1;

			temp = i * 2 + gridSize * 2;
			gridIndex[temp] = temp;
			gridIndex[temp+1] = temp+1;
		}

		auto material = App::Data()->Get<Material>("mat_vertexColor");
		auto mesh = new Mesh(gridMesh, gridIndex, MeshDrawMode::Lines, MeshVertexFormat::PositionColor, material);
		App::Data()->Set<MeshNode>("obj_grid", (new MeshNode())->AddMesh(mesh));
	}

	// ------------------------------------

	// Load Prefabs
	App::Data()->Add<Prefab, Prefabs::Camera>("p_camera");
	App::Data()->Add<Prefab, Prefabs::ModelTest>("p_modelTest");
	App::Data()->Add<Prefab, Prefabs::Grid>("p_grid");
	App::Data()->Add<Prefab, Prefabs::Light>("p_light");

	// Load Levels
	App::Level()->Add<Levels::Demo>();
}

void GameController::ConfigureInput()
{
	// Register Input Bindings
	App::Input()->BindMouse("mouse_l",     MOUSE_BUTTON_LEFT);
	App::Input()->BindMouse("mouse_r",     MOUSE_BUTTON_RIGHT);
	App::Input()->BindMouse("mouse_m",     MOUSE_BUTTON_MIDDLE);
	App::Input()->BindKey("ctrl",          KEY_LEFT_CONTROL);
	App::Input()->BindKey("shift",         KEY_LEFT_SHIFT);
	App::Input()->BindKey("forward",       KEY_W);
	App::Input()->BindKey("backward",      KEY_S);
	App::Input()->BindKey("left",          KEY_A);
	App::Input()->BindKey("right",         KEY_D);
	App::Input()->BindKey("up",            KEY_E);
	App::Input()->BindKey("down",          KEY_Q);
	App::Input()->BindKey("up_alt",        KEY_UP);
	App::Input()->BindKey("down_alt",      KEY_DOWN);
	App::Input()->BindKey("left_alt",      KEY_LEFT);
	App::Input()->BindKey("right_alt",     KEY_RIGHT);
	App::Input()->BindKey("n_center",      KEY_KP_5);
	App::Input()->BindKey("n_up",          KEY_KP_8);
	App::Input()->BindKey("n_down",        KEY_KP_2);
	App::Input()->BindKey("n_left",        KEY_KP_4);
	App::Input()->BindKey("n_right",       KEY_KP_6);
	App::Input()->BindKey("n_roll_left",   KEY_KP_7);
	App::Input()->BindKey("n_roll_right",  KEY_KP_9);
	App::Input()->BindKey("reset",         KEY_R);
	App::Input()->BindKey("reset_scene",   KEY_F1);
	App::Input()->BindKey("reset_shaders", KEY_F5);
	App::Input()->BindKey("exit",          KEY_ESCAPE);
	App::Input()->BindKey("debug",         KEY_SPACE);
}
