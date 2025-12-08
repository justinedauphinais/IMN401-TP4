#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform vec3 posLum;
uniform vec3 posCam;

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

out vec3 vertexL;
out vec3 vertexV;
out vec2 textureCoord;
out float distance;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normale;
layout(location = 3) in vec3 TextureCoordinates;
layout(location = 4) in vec4 Tangente;

void main() {
    vec3 B = cross(Normale, Tangente.xyz);

    mat3 TBN = transpose(mat3(Tangente.xyz, B, Normale));

    vertexL = TBN * (posLum - Position);
    vertexV = TBN * (posCam - Position);
    
    gl_Position = Proj * View * Model * (vec4(Position, 1.0));

    distance = length(posCam - Position) * 0.1;

    textureCoord = TextureCoordinates.xy;
}