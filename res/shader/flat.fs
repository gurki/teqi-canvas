#version 410 core

in vec2 fragPos;
out vec4 fragColor;

uniform vec2 relMousePos;


void main()
{
    float k = 0.5 - distance( relMousePos, vec2( 0.5 ) );
    fragColor = vec4( smoothstep( -0.1, 0.4, k ) * ( fragPos + 0.5 ), 0, 1 );
}