varying vec3 fPosition;
varying vec3 fNormal;


void main()
{
 
    // Basic Light Setup
    ////////////////////////////////////////////////////////////////////
    // sets the position of the light
    float lightDist = 100.0;
    vec3 lightPos =  vec3(-0.1,-1, -1) * lightDist;
    //vec4 movingLight = gl_ModelViewMatrix * vec4(lightPos, 1.0);
    //lightPos = movingLight.xyz;
    
    // normalized vector from the light source to the current vertex
    vec3 L = normalize(fPosition - lightPos);
    vec3 lightColor = vec3(1, 1, 1);
    ////////////////////////////////////////////////////////////////////
    
    
    // assumes and updates camera potition
    vec3 cameraPos = vec3(0,0, 0);
    vec4 movingCamera = gl_ModelViewMatrix * vec4(cameraPos, 1.0);
    
    
    vec3 objectColor = vec3(0.25,0.5,0.7);//vec3 objectColor = vec3(0.15,0.4,0.6);//vec3(0.08, 0.35, 0.08);
    
    // Specular Lighting Calculations
    ////////////////////////////////////////////////////////////////////
    // vector between vertex and camera
    // used to get the half vector
    vec3 E = normalize(-fPosition.xyz);
    // half vector that takes into account the lighting vector and the camera
    // position with respect to the vertex
    vec3 H = normalize(L+E);
    
    // power of the specular lighting
    float p = 400.0;
    float specIntensity = pow(max(dot(fNormal, H), 0.0), p);
    vec3 Specular = lightColor * specIntensity;
    ////////////////////////////////////////////////////////////////////
    
    
    
    vec3 ambient = objectColor * vec3(0.2, 0.2, 0.2);
    vec3 diffuse = objectColor * lightColor * max(dot(fNormal, L), 0.0);
    
    
    vec3 phong = ambient + diffuse + Specular;
    gl_FragColor = vec4(phong, 1.0);
  
    //gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    //gl_FragColor = vec4(abs(fNormal),1.0);
}

