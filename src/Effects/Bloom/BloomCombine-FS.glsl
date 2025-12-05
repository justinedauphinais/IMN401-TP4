#version 460

uniform sampler2D originalScene;
uniform sampler2D blurredBright;

in vec2 uv;
layout(location = 0) out vec4 Color;

void main() {
    vec3 scene = texture(originalScene, uv).rgb;
    vec3 bloom = texture(blurredBright, uv).rgb;

    Color = vec4(scene + bloom, 1.0);   // additive blend
}
