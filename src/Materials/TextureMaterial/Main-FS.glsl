#version 460

uniform float kd;
uniform float ka;
uniform float ks;
uniform int s;
uniform vec3 C;

layout(binding = 0) uniform sampler2D textureDiff;
layout(binding = 2) uniform sampler2D textureNorm;

layout(location = 0) out vec4 Color;

in vec3 vertexL;
in vec3 vertexV;
in vec2 textureCoord;
in float distanceCam;

void main() {    
    vec4 tex = texture(textureDiff, textureCoord);

    vec3 L = normalize(vertexL);
    vec3 V = normalize(vertexV);

    vec3 N = 2 * (texture(textureNorm, textureCoord).xyz) - 1;
    vec3 R = reflect(-L, N);

    float NL = max(dot(N, L), 0.0);
    float RV = max(dot(R, V), 0.0);

    // Intensité diffuse
    float Id = kd * NL;

    // Intensité ambiante
    float Ia = ka;

    // Intensité spéculaire
    float Is = ks * pow(RV, s);

    vec3 color = Ia * tex.rgb + Id * tex.rgb + Is;
    Color = vec4(color, distanceCam);
}