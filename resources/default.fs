#version 300 es
precision mediump float;

// input attributes
in vec2 fragTexcoord;
in vec3 fragMaterialColor;

// input uniforms
uniform sampler2D tex;

// output variable
out vec4 FragColor;


void main()
{
    FragColor = texture(tex, fragTexcoord) * vec4(fragMaterialColor, 1.0);
}
