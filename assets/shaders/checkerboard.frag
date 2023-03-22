#version 330 core

out vec4 frag_color;

// In this shader, we want to draw a checkboard where the size of each tile is (size x size).
// The color of the bottom-left most tile should be "colors[0]" and the 2 tiles adjacent to it
// should have the color "colors[1]".

//TODO: (Req 1) Finish this shader.
    /*
             0 1 2 3
          0  x O x O
          1  O x o x
          2  x o x o

          0,0 => color_0
          0,1 => color_1
          0,2 => color_0
          0,3 => color_1
          1,0 => color_1
          1,1 => color_0
          1,2 => color_1
    */


uniform int size = 32;
uniform vec3 colors[2];

void main(){

   // Calculate the pixel's position in the checkerboard pattern
   vec2 pos = floor(gl_FragCoord.xy / size);

   // Alternate between two colors based on the position
   if (mod(pos.x + pos.y, 2.0) == 0.0)
       frag_color = vec4(colors[0], 1.0);
    else
       frag_color = vec4(colors[1], 1.0);
}