#version 460

uniform float kd;
uniform float ka;
uniform float ks;
uniform int s;
uniform vec3 C;

layout(binding = 0) uniform sampler2D T;
layout(binding = 2) uniform sampler2D TN;

layout(location = 0) out vec4 Color;

in vec3 fragL;
in vec3 fragV;
in vec2 fragTexCoord;
in float dist;

void main() {

    vec3 Nd = 2*(texture(TN, fragTexCoord).xyz) - 1;
    
    vec3 L = normalize(fragL);
    vec3 V = normalize(fragV);

    vec3 N = Nd; // on utilise la normale perturbée
    vec3 R = reflect(-L, N);

    vec4 tex = texture(T, fragTexCoord);

    vec3 objColor = tex.rgb;

    // éclairage diffus
    float Id = kd * max(dot(N, L), 0.0);

    // éclairage ambiant
    float Ia = ka;

    // éclairage spéculaire
    float Is = ks * pow(max(dot(R, V), 0.0), s);

    vec3 color = Ia * C * objColor + Id * C * objColor + Is * C;
    Color = vec4(color, dist);

    
}