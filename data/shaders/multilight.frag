#version 410

in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec2 vTexCoord;

// dirLight ([0] = direction, [1] = diffuse, [2] = specular)
uniform mat3 dirLight1;
uniform mat3 dirLight2;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

//uniform vec3 cameraPosition;
uniform vec3 cameraFacing;

uniform vec3 Ia; // ambient light colour
uniform vec3 LightDirection;

uniform vec3 Ka; // ambient material colour
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour
uniform float specularPower;

out vec4 FragColour;

vec3 CalcDirLight(mat3 light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light[0]);
	
	//diffuse shading
	float diff = max(dot(normal, lightDir), 0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), specularPower);
	
	vec3 ambient = Ia * vec3(texture(diffuseTexture, vTexCoord));
	vec3 diffuse = light[1] * diff * vec3(texture(diffuseTexture, vTexCoord));
	vec3 specular = light[2] * spec * vec3(texture(specularTexture, vTexCoord));
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(LightDirection);
	
	mat3 TBN = mat3(T,B,N);
	
	vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	
	N = TBN * (texNormal * 2 - 1);
	
	float lambertTerm = max( 0, min( 1, dot( N, -L )));
	
	
	vec3 result = CalcDirLight(dirLight1, N, cameraFacing);
	result = result + CalcDirLight(dirLight2, N, cameraFacing);
	
	FragColour = vec4( result, 1);
}