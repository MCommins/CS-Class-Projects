#version 400 compatibility

uniform float uCamZ;
uniform int uUpperCurve;
uniform float uOffset;

out vec2  	vST;		// texture coords

const float PI = 	3.14159265;
int vDivisor;

void
main( )
{ 
	vST = gl_MultiTexCoord0.st;
	float vDist = (uCamZ + uOffset) - gl_Vertex.z;
	vec4 vNewPosition = vec4(gl_Vertex.x, gl_Vertex.y - vDist*(vDist/uUpperCurve), gl_Vertex.z, 1.);
	gl_Position = gl_ModelViewProjectionMatrix * vNewPosition;
}