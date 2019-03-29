#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec2 vTexCoord;

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
	
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;
	
	FragColour = vec4( ambient + diffuse + specular, 1);
}