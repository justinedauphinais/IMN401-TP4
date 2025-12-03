#version 460

uniform vec3 posCam;
uniform vec3 posLum;
uniform vec3 color;

uniform float temps;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normale;
layout(location = 3) in vec3 Texture;
layout(location = 4) in vec4 Tangente;

out vec3 L;
out vec3 V;
out vec3 N;
out vec3 colorObj;
out vec2 texturePos;

void main() {
    // Normalize inputs
    vec3 T = normalize(Tangente.xyz);
    vec3 Nrm = normalize(Normale);
    vec3 B = normalize(cross(Nrm, T) * Tangente.w);

    // Build correct TBN matrix
    mat3 TBN = mat3(T, B, Nrm);

    // Transform lighting vectors into tangent space
    L = TBN * (posLum - Position);
    V = TBN * (posCam - Position);
    N = TBN * Nrm;

    texturePos = Texture.xy;

    colorObj = color;

    gl_Position = Proj * View * Model * vec4(Position, 1.0);
}