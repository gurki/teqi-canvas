#version 410 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 vertCoords;

out vec2 fragCoords;


void main() {
    fragCoords = vertCoords;
    gl_Position = vec4( vertPos, 1.f );
}