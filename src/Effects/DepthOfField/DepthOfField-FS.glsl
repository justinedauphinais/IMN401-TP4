#version 460

layout(binding = 0) uniform sampler2D myFBO;

in vec2 uv;

layout(location = 0) out vec4 Color;

void main() 
{
    vec2 invSize = 1.0 / vec2(textureSize(myFBO, 0));

    vec4 tex = texture(myFBO, uv);

    float distance = tex.a;

    float focusDistance = 0.2;
    float focusRange = 0.5;

    if (abs(distance - focusDistance) <= focusRange) {
        Color = vec4(tex.rgb, 1.0);
        return;
    }

    float blurAmount = clamp(abs(distance - focusDistance) - focusRange, 0.0, 1.0);

    int k = int(mix(1.0, 4.0, blurAmount));

    vec3 c = vec3(0.0);
    int count = 0;

    for (int i = -k; i <= k; i++) {
        for (int j = -k; j <= k; j++) {
            vec2 sampleUv = uv + vec2(i, j) * invSize;

            sampleUv = clamp(sampleUv, vec2(0.0), vec2(1.0));

            c += texture(myFBO, sampleUv).rgb;
            count++;
        }
    }

    Color = vec4(c / float(count), 1.0);
}