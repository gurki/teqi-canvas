#version 410 core

in vec2 fragPos;
out vec4 fragColor;

uniform vec2 mouseRel;
uniform bool mouseDown = false;

float remap( float value, float start1, float stop1, float start2, float stop2 ) {
	return ( value - start1 ) / ( stop1 - start1 ) * ( stop2 - start2 ) + start2;
}

void main()
{
    float vignette = smoothstep( 1.0, 0.0, length( fragPos ) );
    float lightness = remap( float( mouseDown ), 1, 0, 0.5, 1 );
    vec4 color = vec4( mouseRel.x, mouseRel.y, 0.0, 1.0 );

    fragColor = vignette * lightness * color;
}