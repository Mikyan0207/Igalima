#version 420

layout(location = 0) in vec2 m_Position;
layout(location = 1) in vec4 m_Colour;

out vec4 v_Colour;

void main(void)
{
    gl_Position = vec4(m_Position.xy, 1.0, 1.0);
    v_Colour = m_Colour;
}
