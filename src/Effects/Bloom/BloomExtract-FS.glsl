#version 460

uniform sampler2D myFBO;     // original scene
uniform float threshold;     // try 1.0 for testing

in vec2 uv;
layout(location = 0) out vec4 Color;

void main() {
    vec3 col = texture(myFBO, uv).rgb;
    float brightness = length(col);   // or max(col.r, max(col.g, col.b))

    if (brightness > threshold)
        Color = vec4(col, 1.0);
    else
        Color = vec4(0.0);
}
