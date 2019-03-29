#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec2 vTexCoord;

struct DirLight
{
	vec3 direction;
	
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight[2];


uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 cameraPosition;

uniform vec3 Ia; // ambient light colour
uniform vec3 Id; // diffuse light colour
uniform vec3 Is; // specular light colour
uniform vec3 LightDirection;

uniform vec3 Ka; // ambient material colour
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour
uniform float specularPower;

out vec4 FragColour;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	float diff = max(dot(normal, lightDir), 0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), specularPower);
	
	vec3 ambient = Ia * vec3(texture(Kd, vTexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(Kd, vTexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.diffuse, vTexCoord));
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(LightDirection);
	
	mat3 TBN = mat3(T,B,N);
	
	
	vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
	vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;
	vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	
	N = TBN * (texNormal * 2 - 1);
	
	float lambertTerm = max( 0, min( 1, dot( N, -L )));
	
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( L, N );
	
	float specularTerm = pow( max( 0, dot(R, V) ), specularPower );
	
	//vec3 ambient = Ia * Ka;
	//vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	//vec3 specular = Is * Ks * texSpecular * specularTerm;
	
	vec3 result = CalcDirLight(dirLight[0], vNormal, lambertTerm);
	
	
	FragColour = vec4( result, 1);
}