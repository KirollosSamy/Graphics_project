#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;

out vec4 frag_color;

// Vignette is a postprocessing effect that darkens the corners of the screen
// to grab the attention of the viewer towards the center of the screen

// --> vignette means that approaching the center of the screen lead to more lightness

void main(){
    //TODO: Modify this shader to apply vignette
    // To apply vignette, divide the scene color
    // by 1 + the squared length of the 2D pixel location the NDC space
    // Hint: remember that the NDC space ranges from -1 to 1
    // while the texture coordinate space ranges from 0 to 1
    // We have the pixel's texture coordinate, how can we compute its location in the NDC space?

    // ? what is NDC space 🤔
    /*
    * Normalized Device Coordinates (NDC) Space is a common coordinate system used to represent
    * the final stage of a graphics pipeline. After a 3D model is transformed and projected onto a 2D screen,
    * the resulting coordinates are typically in device coordinates, which are specific to the display hardware.
    * it differs from screen to screen based on the Resolution(WindowSize.x, WindowSize.y).
    */

    // translate the pixel to NDC space.
    vec2 NDC = vec2(2.0f * tex_coord - 1.0f);  
    // calculate the vignette simply by dividing scene color by : 1 + the squared length of the 2D pixel location in the NDC space.
    frag_color = texture(tex, tex_coord) / (1 + length(NDC)*length(NDC));
    // Note that : length() is used to calculate the magnitude of the vector.
}