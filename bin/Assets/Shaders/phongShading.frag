#version 330 core

smooth in vec3 v_Position;
smooth in vec3 v_Normal;
smooth in vec2 v_TexCoords;
smooth in vec3 v_Color;

out vec4 frag_color;

layout (std140) uniform GlobalMatrices
{
	mat4 cameraToClipMatrix;
	mat4 worldToCameraMatrix;
};

//layout (std140) uniform Material
//{
//	vec3 diffuse;
//	vec3 specular;
//	float shininess; // 2~256
//};

struct Material
{
	vec3 diffuseColor;
	vec3 specularColor;
	sampler2D diffuse0;
	sampler2D specular0;
	float shininess;
};
uniform Material material;

struct World
{
	vec3 ambient;
};
uniform World world;

// --------------------------

struct DirLight
{
	vec3 direction;

	vec3 color;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 color;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 color;
};

#define NUM_DIR_LIGHTS 2
#define NUM_POINT_LIGHTS 5
#define NUM_SPOT_LIGHTS 1

uniform DirLight dirLights[NUM_DIR_LIGHTS];
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform SpotLight spotLights[NUM_SPOT_LIGHTS];

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// --------------------------

void main()
{
	vec3 viewPos = vec3(0.0f); // All operations are in camera space
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(viewPos - v_Position);
	vec4 result = vec4(0.0f);

	for(int i = 0; i < NUM_DIR_LIGHTS; i++)
	{
		result += CalcDirLight(dirLights[i], norm, viewDir);
	}

	//for(int i = 0; i < NUM_POINT_LIGHTS; i++)
	//{
	//	result += CalcPointLight(pointLights[i], norm, v_Position, viewDir);
	//}

	for(int i = 0; i < NUM_SPOT_LIGHTS; i++)
	{
		result += CalcSpotLight(spotLights[i], norm, v_Position, viewDir);
	}

	result += vec4(world.ambient, 0.0f);

	if(result.a < 0.01)
	{
		discard;
	}

	frag_color = result;
}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Colors
	vec4 diffuseTex = /*v_Color +*/ texture(material.diffuse0, v_TexCoords);
	vec3 diffuse = light.color * diff * vec3(diffuseTex);
	vec3 specular = light.color * spec * vec3(texture(material.specular0, v_TexCoords));

	return vec4(diffuse + specular, diffuseTex.a);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Colors
	vec4 diffuseTex = /*v_Color +*/ texture(material.diffuse0, v_TexCoords);
	vec3 diffuse = light.color * diff * vec3(diffuseTex);
	vec3 specular = light.color * spec * (/*v_Color +*/ vec3(texture(material.specular0, v_TexCoords)));

	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	diffuse *= attenuation;
	specular *= attenuation;

	return vec4(diffuse + specular, diffuseTex.a);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Colors
	vec4 diffuseTex = /*v_Color +*/ texture(material.diffuse0, v_TexCoords);
	vec3 diffuse = light.color * diff * vec3(diffuseTex);
	vec3 specular = light.color * spec * (/*v_Color +*/ vec3(texture(material.specular0, v_TexCoords)));

	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return vec4(diffuse + specular, diffuseTex.a);
}
