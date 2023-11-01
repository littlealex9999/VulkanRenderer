#version 450

layout(binding = 1) uniform sampler2D baseColorTex;
layout(binding = 2) uniform sampler2D emissiveTex;
layout(binding = 3) uniform sampler2D heightTex;
layout(binding = 4) uniform sampler2D metallicTex;
layout(binding = 5) uniform sampler2D normalTex;
layout(binding = 6) uniform sampler2D roughnessTex;

layout(binding = 7) uniform LightSource {
	vec3 direction;
} light;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragTangent;
layout(location = 3) in mat3 TBN;
layout(location = 6) in vec2 fragTexCoord;
layout(location = 7) in vec2 frameSize;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 diffuse = texture(baseColorTex, fragTexCoord).xyz;
	vec3 emissive = texture(emissiveTex, fragTexCoord).xyz;
	vec3 normalCalc = TBN * (texture(normalTex, fragTexCoord).xyz * 2 - 1);

	float roughness = texture(roughnessTex, fragTexCoord).x;
	vec3 viewerDir = normalize(vec3(-(gl_FragCoord.xy - frameSize / 2) / (frameSize.x / 2), cos(45)));

	float reflectionCoefficient = 0.0f;

	// Oren-Nayar diffuse reflectance
	float R2 = roughness * roughness;
	float A = 1.0f - 0.5f * R2 / (R2 + 0.33f);
	float B = 0.45f * R2 / (R2 + 0.09f);

	float NdE = max(0.0f, dot(normalCalc, viewerDir));

	vec3 viewProjected = normalize(viewerDir - normalCalc * NdE);

	float OrenNayarOut = 0;

	// Cook-Torrance Specular Reflectance
	float e = 2.71828182845904523536028747135f;
	float pi = 3.1415926535897932384626433832f;

	// Fresnel, Schlick's Approximation
	float F = reflectionCoefficient + (1 - reflectionCoefficient) * pow(1 - NdE, 5);

	float CookTorranceOut = 0;

	// Lighting
	// Oren-Nayar diffuse reflectance
	vec3 lightDir = light.direction;
	float NdL = max(0.0f, dot(normalCalc, lightDir));

	vec3 lightProjected = normalize(lightDir - normalCalc * NdL);

	float CX = max(0.0f, dot(lightProjected, viewProjected));

	float alpha = sin(max(acos(clamp(NdE, -1, 1)), acos(clamp(NdL, -1, 1))));
	float beta = tan(min(acos(clamp(NdE, -1, 1)), acos(clamp(NdL, -1, 1))));
	float DX = alpha * beta;

	OrenNayarOut += NdL * (A + B * CX * DX);

	// Beckmann Distribution
	vec3 H = normalize(lightDir + viewerDir); // light and view half vector
	float NdH = max(dot(normalCalc, H), 0.0f);
	float NdH2 = NdH * NdH;

	float exponent = -(1 - NdH2) / (NdH2 * R2);
	float D = pow(e, exponent) / (R2 * NdH2 * NdH2);

	// Geometric Attenuation Factor
	float X = 2.0f * NdH / dot(viewerDir, H);
	float G = min(1, min(X * NdL, X * NdE));

	CookTorranceOut += max((D*G*F) / (NdE * pi), 0.0f);

	outColor = vec4(diffuse * (OrenNayarOut + CookTorranceOut) + emissive, 1);
	//outColor = vec4(normalCalc, 1);
	//outColor = texture(normalTex, fragTexCoord);
}