varying vec4 baseColor;
void main(void)
{
    gl_Position = ftransform();
    baseColor = vec4(vec3(0.5) + gl_Normal * 0.5, 1.0);
}