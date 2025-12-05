#version 460

uniform sampler2D myFBO;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() {
    ivec2 tSize = textureSize(myFBO, 0);

    int k = 2;

    vec3 sum = vec3(0.0);
    int count = 0;

    for (int i = -k; i <= k; i++) {
        for (int j = -k; j <= k; j++) {

            vec2 offset = vec2(float(i) / float(tSize.x),
                               float(j) / float(tSize.y));

            sum += texture(myFBO, uv + offset).rgb;
            count++;
        }
    }

    vec3 blur = sum / float(count);

    Color = vec4(blur, 1.0);
}
