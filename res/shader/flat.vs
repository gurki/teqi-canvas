#version 410 core

in vec3 vertPos;
out vec2 fragPos;


void main() {
    fragPos = vertPos.xy;
    gl_Position = vec4( vertPos, 1.f );
}