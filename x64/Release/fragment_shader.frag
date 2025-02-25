#version 120

varying vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;

void main()
{
    // Ambient light
    vec4 ambient = vec4(0.14, 0.14, 0.14, 1.0);
    
    // Convert light to view coordinates and store it in a local variable
    vec2 lightPosView = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0.0, 1.0)).xy;
    
    // Calculate the vector from light to pixel (make circular)
    vec2 lightToFrag = lightPosView - vert_pos.xy;
    lightToFrag.y = lightToFrag.y / 1.7;
    
    // Length of the vector (distance)
    float vecLength = clamp(length(lightToFrag) * 2.4, 0.0, 1.0);
    
    // Lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    // Multiply it by the color and lighting
    if(hasTexture)
    {
        gl_FragColor = gl_Color * pixel * clamp(ambient + vec4(1.0 - vecLength,
                                                                  1.0 - vecLength,
                                                                  1.0 - vecLength,
                                                                  1.0), 0.0, 1.0);
    }
    else
    {
        gl_FragColor = gl_Color;
    }
}
