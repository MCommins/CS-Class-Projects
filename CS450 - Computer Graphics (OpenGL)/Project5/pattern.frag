#version 330 compatibility

uniform float	uCoverage;	// found in Animate( )
in vec2  	vST;		// texture coords
in vec3		vColor;		// base color
in vec3		vVert;		// xyz

const float PI = 	3.14159265;

void
main( )
{
	vec3 myColor = vec3(1 - vColor.x, 1 - vColor.y, 1 - vColor.z);
	float wave1 = 0.1 * sin(PI * vST.t) * (1 + cos(24 * PI * vST.s)) / 2;
	float wave2 = - 0.1 * sin(PI * vST.t) * (1 + cos(24 * PI * vST.s + PI)) / 2;
	if (vVert.z < 0 ) {
		if(vST.t < uCoverage + 0.1 * sin(PI * vST.t) && vST.t > uCoverage) {
			myColor = vColor;
		}
	}
	else if (vST.t < uCoverage + wave1 && vST.t > uCoverage + wave2)
	{
		myColor = vColor;
	}
	gl_FragColor = vec4( myColor,  1. );
}