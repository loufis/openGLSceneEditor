uniform mat3 normalMatrix;
varying vec3 fNormal;
varying vec3 fPosition;

void main()
{
    fNormal = normalize(gl_NormalMatrix*gl_Normal);
    //vec4 norm = normalize(gl_ModelViewMatrix * vec4(fNormal,1.0));
    //fNormal = norm.xyz;
    vec4 pos = gl_ModelViewMatrix * gl_Vertex;
    fPosition = pos.xyz;
    gl_Position = ftransform();
}
