#version 460

uniform sampler2D myFBO;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() {
    ivec2 tSize = textureSize(myFBO, 0);
    int k = 8;  // must use same k as horizontal

    vec3 sum = vec3(0.0);
    int count = 0;

    for (int j = -k; j <= k; j++) {
        vec2 offset = vec2(0.0, float(j) / float(tSize.y));
        sum += texture(myFBO, uv + offset).rgb;
        count++;
    }

    Color = vec4(sum / float(count), 1.0);
}
