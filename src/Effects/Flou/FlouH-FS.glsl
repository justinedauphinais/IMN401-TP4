#version 460

uniform sampler2D myFBO;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() {
    ivec2 tSize = textureSize(myFBO, 0);
    int k = 8;  // try 4–8 for visible blur

    vec3 sum = vec3(0.0);
    int count = 0;

    for (int i = -k; i <= k; i++) {
        vec2 offset = vec2(float(i) / float(tSize.x), 0.0);
        sum += texture(myFBO, uv + offset).rgb;
        count++;
    }

    Color = vec4(sum / float(count), 1.0);
}
