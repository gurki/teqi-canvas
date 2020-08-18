#version 410 core

in vec2 fragCoords;

uniform vec2 mouseRel;
uniform bool mouseDown;
uniform sampler2D albedo;

out vec4 fragColor;


void main()
{
    vec2 mouse = clamp( vec2( mouseRel.x, 1.0 - mouseRel.y ), 0.0, 1.0 );
    vec2 coords = mouseDown ? 0.5 * ( mouse + fragCoords ) : fragCoords;
    vec4 color = texture( albedo, coords );
    float vignette = smoothstep( mouseDown ? 1.0 : 0.5, 0.0, length( mouse - fragCoords ) );

    fragColor = vignette * color;
}