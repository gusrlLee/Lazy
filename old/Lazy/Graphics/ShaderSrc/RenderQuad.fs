// FRAGMENT SHADER 
#version 330 core 
out vec4 outColor;

in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    // outColor = vec4(0.5f);
    outColor = texture(tex, texCoord);
}



