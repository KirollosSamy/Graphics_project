#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;
out vec4 frag_color;

// How far (in the texture space) is the distance (on the x-axis) between
// the pixels from which the red/green (or green/blue) channels are sampled
#define STRENGTH 0.005

// Chromatic aberration mimics some old cameras where the lens disperses light
// differently based on its wavelength. In this shader, we will implement a
// cheap version of that effect 

void main(){
//TODO: Modify this shader to apply chromatic aberration
    // To apply this effect, we only read the green channel from the correct pixel (as defined by tex_coord)
    // To get the red channel, we move by amount STRENGTH to the left then sample another pixel from which we take the red channel
    // To get the blue channel, we move by amount STRENGTH to the right then sample another pixel from which we take the blue channel

    frag_color = texture(tex, tex_coord);
    // to move to right direction of X we just need to subtract STRENGTH from X
    // while keeping y same and we pick only the red channel
    frag_color.r = texture(tex, vec2(tex_coord.x - STRENGTH, tex_coord.y)).r; 

    // to move to right we only need to add this STRENGTH value to X while 
    // keeping y same and pick only blue channel
    frag_color.b = texture(tex, vec2(tex_coord.x+STRENGTH, tex_coord.y)).b;

    // keep the green channel as it is and set the alpha channel to 1 (nothing new here)
    frag_color.a = 1.0;
}