uniform sampler2D texture;
uniform vec2 mouse_pos;

void main()
{
    vec4 pixel = texture2D(texture, mouse_pos);

    // multiply it by the color
    gl_FragColor = pixel;
}
