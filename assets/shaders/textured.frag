#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
} fs_in;

out vec4 frag_color;

uniform vec4 tint;
uniform sampler2D tex;

uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform sampler2D tex6;
uniform sampler2D tex7;
uniform sampler2D tex8;
uniform sampler2D tex9;
uniform sampler2D tex10;
uniform sampler2D tex11;
uniform sampler2D tex12;
uniform sampler2D tex13;
uniform sampler2D tex14;




void main(){
    //TODO: (Req 7) Modify the following line to compute the fragment color
    // by multiplying the tint with the vertex color and with the texture color 
    vec4 texel1 = texture(tex, fs_in.tex_coord);
    vec4 texel2 = texture(tex2, fs_in.tex_coord);
    vec4 texel3 = texture(tex3, fs_in.tex_coord);
    vec4 texel4 = texture(tex4, fs_in.tex_coord);
    vec4 texel5 = texture(tex5, fs_in.tex_coord);
    vec4 texel6 = texture(tex6, fs_in.tex_coord);
    vec4 texel7 = texture(tex7, fs_in.tex_coord);
    vec4 texel8 = texture(tex8, fs_in.tex_coord);
    vec4 texel9 = texture(tex9, fs_in.tex_coord);
    vec4 texel10 = texture(tex10, fs_in.tex_coord);
    vec4 texel11 = texture(tex11, fs_in.tex_coord);
    vec4 texel12 = texture(tex12, fs_in.tex_coord);
    vec4 texel13 = texture(tex13, fs_in.tex_coord);
    vec4 texel14 = texture(tex14, fs_in.tex_coord);


    vec4 mix1 = mix(texel1, texel2, 1.0/13.0);
    vec4 mix2 = mix(mix1, texel3, 1.0/13.0);
    vec4 mix3 = mix(mix2, texel4, 1.0/13.0);
    vec4 mix4 = mix(mix3, texel5, 1.0/13.0);
    vec4 mix5 = mix(mix4, texel6, 1.0/13.0);
    vec4 mix6 = mix(mix5, texel7, 1.0/13.0);
    vec4 mix7 = mix(mix6, texel8, 1.0/13.0);
    vec4 mix8 = mix(mix7, texel9, 1.0/13.0);
    vec4 mix9 = mix(mix8, texel10, 1.0/13.0);
    vec4 mix10 = mix(mix9, texel11, 1.0/13.0);
    vec4 mix11 = mix(mix10, texel12, 1.0/13.0);
    vec4 mix12 = mix(mix11, texel13, 1.0/13.0);
    vec4 mix13 = mix(mix12, texel14, 1.0/13.0);


    frag_color = fs_in.color * tint  * mix13;
}