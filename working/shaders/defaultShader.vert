#version 450

layout(binding = 0) uniform UniformBufferObject {
	mat4 model;
	mat4 view;
	mat4 proj;
} mvp;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inTangent;
layout(location = 4) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec3 fragTangent;
layout(location = 3) out mat3 TBN;
layout(location = 6) out vec2 fragTexCoord;

void main()
{
	gl_Position = mvp.proj * mvp.view * mvp.model * vec4(inPosition, 1.0);
	fragColor = inColor;
	fragNormal = (mvp.model * vec4(inNormal, 0)).xyz;
	fragTangent = inTangent;
	fragTexCoord = inTexCoord;

	TBN[0] = vec3(-inTangent);
	TBN[1] = vec3(cross(fragNormal, inTangent));
	TBN[2] = vec3(fragNormal);
}