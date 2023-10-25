#version 450

layout(binding = 1) uniform sampler2D baseColorTex;
layout(binding = 2) uniform sampler2D emissiveTex;
layout(binding = 3) uniform sampler2D heightTex;
layout(binding = 4) uniform sampler2D metallicTex;
layout(binding = 5) uniform sampler2D normalTex;
layout(binding = 6) uniform sampler2D roughnessTex;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragTangent;
layout(location = 3) in mat3 TBN;
layout(location = 6) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 normalCalc = TBN * (texture(normalTex, fragTexCoord).xyz * 2 - 1);

	outColor = vec4(normalCalc, 1);
	//outColor = texture(normalTex, fragTexCoord);
}