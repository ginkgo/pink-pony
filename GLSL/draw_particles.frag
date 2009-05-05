
uniform sampler2D texture;

varying vec2 uv;

void main()
{
    vec4 t = texture2D(texture, uv);

/*     if (t.r < 0.5) { */
/*         discard; */
/*     } */

    gl_FragColor = gl_Color * t;

}
