#version 330

in vec2 fragTexCoord;
out vec4 fragColor;

uniform float uTime;
uniform vec2 uResolution;

// Hash function
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

// Interpolation
float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);

    // 4 corners
    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    // Smooth interpolation
    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
           (c - a) * u.y * (1.0 - u.x) +
           (d - b) * u.x * u.y;
}

void main() {
    vec2 uv = fragTexCoord * uResolution / 200.0; // scale
    float n = noise(uv + uTime * 0.1);
    fragColor = vec4(vec3(n), 1.0);
}
