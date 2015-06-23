attribute vec4 a_position;
attribute vec4 a_normal;

varying vec4 v_normal;

void main()
{
    v_normal = a_normal;
    gl_Position = CC_MVPMatrix * a_position;
}
