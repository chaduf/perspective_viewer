#version 300 es
precision mediump float;

// input attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

// input uniforms
uniform vec3 materialColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// output variables
out vec2 fragTexcoord;
out vec3 fragMaterialColor;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragTexcoord = texcoord;
    fragMaterialColor = materialColor;
}