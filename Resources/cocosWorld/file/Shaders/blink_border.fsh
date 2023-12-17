#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;
uniform vec2 u_resolution;

void main()
{
    vec2 uv = v_texCoord.xy;
    vec2 pixelSize = 1.0 / u_resolution;

    vec4 col = texture2D(CC_Texture0, uv);

    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    if (col.a > 0.0) {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }

    gl_FragColor = v_fragmentColor * mix(col, color, step(0.5, fract(uv.x * 10.0)));
}
