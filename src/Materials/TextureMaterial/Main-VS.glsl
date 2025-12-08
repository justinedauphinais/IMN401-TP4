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
out vec3 colorObj;
out vec2 texturePos;
out float dist;

void main() {
    vec3 T = normalize(Tangente.xyz);
    vec3 Nrm = normalize(Normale);
    vec3 B = cross(Normale, Tangente.xyz);

    mat3 TBN = transpose(mat3(Tangente.xyz, B, Normale));

    L = TBN * (posLum - Position);
    V = TBN * (posCam - Position);

    texturePos = Texture.xy;

    colorObj = color;

    dist = length(posCam - Position) * 0.1;

    gl_Position = Proj * View * Model * vec4(Position, 1.0);
}