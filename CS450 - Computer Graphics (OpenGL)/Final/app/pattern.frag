#version 400 compatibility

uniform sampler2D uTexUnit;
uniform int uIsTextured; // Use Texturing
in vec2  	vST;		// texture coords

void
main( )
{
	if (uIsTextured == 1) {
		vec3 newColor = texture(uTexUnit, vST).rgb;
		gl_FragColor = vec4( newColor,  1. );
	} else {
		gl_FragColor = vec4( 0.5, 0, 0, 1);
	}
}