#version 330 compatibility

uniform float	uSinTime; // found in Animate( )
out vec2  	vST;		// texture coords
out vec3	vColor;		// base color
out vec3	vVert;		// xyz

const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency

void
main( )
{ 
	vST = gl_MultiTexCoord0.st;
	vVert = gl_Vertex.xyz;
	vColor = vVert.xyz;
	if (vVert.y > 0) {
		vVert.x = vVert.x + (uSinTime * (1 + vVert.y)/2);
	}
	gl_Position = gl_ModelViewProjectionMatrix * vec4( vVert, 1. );
}