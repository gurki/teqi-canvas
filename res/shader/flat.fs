#version 410 core

in vec2 fragPos;
out vec4 fragColor;

uniform vec2 relMousePos;


void main()
{
    fragColor = vec4( relMousePos * ( fragPos + 0.5 ), 0, 1 );
}