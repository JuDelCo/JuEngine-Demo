// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "GameController.hpp"
#include "Prefabs/Camera.hpp"
#include "Prefabs/Duck.hpp"
#include "Prefabs/Grid.hpp"
#include "Prefabs/Hat.hpp"
#include "Prefabs/Light.hpp"
#include "Prefabs/Sun.hpp"
#include "Levels/Demo.hpp"
#include <JuEngine/Resources/Material.hpp>
#include <JuEngine/Resources/Mesh.hpp>
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
	// Load Meshes
	App::Data()->Add<Mesh>("obj_axis",       "axis.dae");
	App::Data()->Add<Mesh>("obj_cube",       "cube.dae");
	App::Data()->Add<Mesh>("obj_sphere",     "sphere.dae");
	//App::Data()->Add<Mesh>("obj_cylinder", "cylinder.dae");
	//App::Data()->Add<Mesh>("obj_cone",     "cone.dae");
	//App::Data()->Add<Mesh>("obj_torus",    "torus.dae");
	//App::Data()->Add<Mesh>("obj_suzanne",  "suzanne.dae");
	App::Data()->Add<Mesh>("obj_duck",       "duck.dae");
	App::Data()->Add<Mesh>("obj_hat",        "hat.dae");
	//App::Data()->Add<Mesh>("obj_test",       "stress/sibenik-cathedral.obj");

	// ------------------------------------

	{
		unsigned int gridSize = 20; /* 20x20 */
		int gridOffset = -(gridSize / 2);
		unsigned int temp, indexH, indexV;
		float color;
		std::vector<float> gridMesh;
		std::vector<unsigned int> gridIndex;
		gridMesh.resize(gridSize * 2 /* H&V */ * 2 * Mesh::mNumVertexAttr, 0.f);
		gridIndex.resize(gridSize * 2 /* H&V */ * 2, 0);

		// Generate Grid
		for(unsigned int i = 0; i < gridSize; ++i)
		{
			temp = Mesh::mNumVertexAttr;
			indexH = (i * 2 * Mesh::mNumVertexAttr);
			indexV = indexH + (gridSize * 2 * Mesh::mNumVertexAttr);
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

		App::Data()->Add<Mesh>("obj_grid", gridMesh, gridIndex, MeshDrawMode::Lines);
	}

	{
		std::vector<float> quadMesh = {
		//    X      Y      Z      NX    NY    NZ    U     V     R     G     B
			-0.5f, -0.5f,  0.5f,  1.f,  1.f,  1.f,  0.f,  0.f,  1.f,  1.f,  1.f, // BL
			 0.5f, -0.5f,  0.5f,  1.f,  1.f,  1.f,  1.f,  0.f,  1.f,  1.f,  1.f, // BR
			 0.5f,  0.5f,  0.5f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f, // TR
			 0.5f,  0.5f,  0.5f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f,  1.f, // TR
			-0.5f,  0.5f,  0.5f,  1.f,  1.f,  1.f,  0.f,  1.f,  1.f,  1.f,  1.f, // TL
			-0.5f, -0.5f,  0.5f,  1.f,  1.f,  1.f,  0.f,  0.f,  1.f,  1.f,  1.f  // BL
		};

		std::vector<unsigned int> gridIndex = {
			0, 1, 2,
			3, 4, 5
		};

		App::Data()->Add<Mesh>("obj_quad", quadMesh, gridIndex, MeshDrawMode::Triangles);
	}

	// ------------------------------------

	// Load Textures
	App::Data()->Add<Texture>("tex_awesome", "awesome_face.png");
	App::Data()->Add<Texture>("tex_box", "container_box.png");
	App::Data()->Add<Texture>("tex_floor", "floor_wall.png");
	App::Data()->Add<Texture>("tex_sanic", "sanic.png");

	// Load Shaders
	//	> Vertex Shaders en uso: BaseVertexColor, BaseUniformColor, Diffuse, VertexLit
	//	> Fragment Shaders en uso: Base, SpecularGaussian
	App::Data()->Add<Shader>("shader_baseVertexColor", "baseVertexColor.vert", "base.frag");
	App::Data()->Add<Shader>("shader_baseUniformColor", "baseUniformColor.vert", "base.frag");
	App::Data()->Add<Shader>("shader_baseTextureColor", "baseTextureColor.vert", "baseTexture.frag");
	App::Data()->Add<Shader>("shader_vertexLit", "vertexLit.vert", "base.frag");
	//App::Data()->Add<Shader>("shader_diffuse", "diffuse.vert", "diffuse.frag");
	//App::Data()->Add<Shader>("shader_specularPhong", "diffuse.vert", "specularPhong.frag");
	//App::Data()->Add<Shader>("shader_specularBlinnPhong", "diffuse.vert", "specularBlinnPhong.frag");
	App::Data()->Add<Shader>("shader_specularGaussian", "diffuse.vert", "specularGaussian.frag");
	//App::Data()->Add<Shader>("shader_specularGaussianDir", "diffuse.vert", "specularGaussianDir.frag");

	/*auto shaderTestDebug = App::Data()->Get<Shader>("shader_specularGaussian");
	App::Log()->Debug("------------------------");
	App::Log()->Debug("DEBUG: diffuse.vert and specularGaussian.frag attributes:");
	shaderTestDebug->PrintAttributeNames();
	App::Log()->Debug("------------------------");
	App::Log()->Debug("DEBUG: diffuse.vert and specularGaussian.frag uniforms:");
	shaderTestDebug->PrintUniformNames();
	App::Log()->Debug("------------------------");
	App::Log()->Debug("DEBUG: diffuse.vert and specularGaussian.frag uniform blocks:");
	shaderTestDebug->PrintUniformBlockNames();
	App::Log()->Debug("------------------------");*/

	// Load Materials
	App::Data()->Add<Material>("mat_vertexColor", "shader_baseVertexColor");
	App::Data()->Add<Material>("mat_vertexLit", "shader_vertexLit");
	App::Data()->Add<Material>("mat_plane", "shader_specularGaussian");
	App::Data()->Get<Material>("mat_plane")
		->SetDiffuseColor(vec3(0.5f, 0.5f, 0.5))
		->SetSpecularColor(vec3(1.f, 1.f, 1.f))
		->SetShininessFactor(0.1f);
	App::Data()->Add<Material>("mat_light", "shader_baseUniformColor");
	App::Data()->Get<Material>("mat_light")
		->SetDiffuseColor(vec3(1.f, 1.f, 1.f));
	App::Data()->Add<Material>("mat_white", "shader_specularGaussian");
	App::Data()->Get<Material>("mat_white")
		->SetDiffuseColor(vec3(1.f, 1.f, 1.f))
		->SetSpecularColor(vec3(1.f, 1.f, 1.f))
		->SetShininessFactor(0.2f);
	App::Data()->Add<Material>("mat_red", "shader_specularGaussian");
	App::Data()->Get<Material>("mat_red")
		->SetDiffuseColor(vec3(1.f, 0.02f, 0.02f))
		->SetSpecularColor(vec3(1.f, 1.f, 1.f))
		->SetShininessFactor(0.2f);
	App::Data()->Add<Material>("mat_green", "shader_specularGaussian");
	App::Data()->Get<Material>("mat_green")
		->SetDiffuseColor(vec3(0.02f, 1.f, 0.02f))
		->SetSpecularColor(vec3(1.f, 1.f, 1.f))
		->SetShininessFactor(0.2f);
	App::Data()->Add<Material>("mat_blue", "shader_specularGaussian");
	App::Data()->Get<Material>("mat_blue")
		->SetDiffuseColor(vec3(0.02f, 0.02f, 1.f))
		->SetSpecularColor(vec3(1.f, 1.f, 1.f))
		->SetShininessFactor(0.2f);
	App::Data()->Add<Material>("mat_texture_test", "shader_baseTextureColor", "tex_sanic");

	// Load Prefabs
	App::Data()->Add<Prefab, Prefabs::Camera>("camera");
	App::Data()->Add<Prefab, Prefabs::Duck>("duck");
	App::Data()->Add<Prefab, Prefabs::Grid>("grid");
	App::Data()->Add<Prefab, Prefabs::Hat>("hat");
	App::Data()->Add<Prefab, Prefabs::Light>("light");
	App::Data()->Add<Prefab, Prefabs::Sun>("sun");

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
