#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

uniform vec3 posLum;
uniform vec3 posCam;

uniform float distCoef;
uniform float time;
uniform int catDeform;

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

vec3 deformSurface(vec3 pos, vec3 normal) {
    float dist = distance(pos, posLum);

    float delta = dist - 0.7 ;
    delta = 0.5*clamp(delta, -0.01, 0);

    return pos + normal * delta;
}

void main() {
    vec3 pos;
    if(catDeform == 1){
        pos = deformSurface(Position,Normale);
    }else{
        pos = Position;
    }

    vec3 B = cross(Normale, Tangente.xyz);

    mat3 TBN = transpose(mat3(Tangente.xyz, B, Normale));

    vertexL = TBN*(posLum - pos);
    vertexV = TBN*(posCam - pos);
    
    gl_Position = Proj * View * Model * (vec4(pos, 1.0));




    

    textureCoord = TextureCoordinates.xy;
}