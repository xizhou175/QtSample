#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D textureWall;
uniform sampler2D textureSmile;
uniform sampler2D textureSmall;
void main(){
    //FragColor = mix(texture(textureWall,TexCord), texture(textureSmile,TexCord), 0.5);
    FragColor = texture(textureWall, TexCord);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
