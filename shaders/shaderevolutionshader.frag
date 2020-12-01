#version 400 core

in vec3 color;
in vec3 pos; //(object space)
in float timevar;

out vec4 fragColor;

void main(){
    fragColor = vec4(pos.r - timevar, pos.g + timevar, -timevar + pos.b, 1) / 0.5f;
    fragColor += vec4(color, 1) / 0.5f;
}
