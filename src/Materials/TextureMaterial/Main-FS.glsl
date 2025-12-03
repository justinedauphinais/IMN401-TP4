#version 460

uniform sampler2D textureDiffuse;
uniform sampler2D textureN;

uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float shiny;

in vec3 L;
in vec3 V;
in vec3 N;

in vec3 colorObj;

in vec2 texturePos;

layout(location = 0) out vec4 Color;

void main() {
    vec3 tex = texture(textureDiffuse,  texturePos).rgb;

    vec3 nL = normalize(L);
    vec3 nV = normalize(V);
    vec3 nN = 2 * (texture(textureN, texturePos).xyz) - 1;

    vec3 R = reflect(-nL, nN);

    float NL = max(dot(nN, nL), 0.0f);
    float RV = max(dot(R, nV), 0.0f);

    vec3 ambient = ka * tex;
    vec3 diffuse = kd * NL * tex;
    vec3 speculaire = ks * pow(RV, shiny) * vec3(1.0f, 1.0f, 1.0f);

    vec3 couleur = ambient + diffuse + speculaire;
    
    Color = vec4(couleur, 1.0);
}