#include <Graphics/Noise.h>

Noise::Noise()
{
	m_Settings = {
		0.5,
		3.0,
		5.0,
		0.9,
		1.0,
		7.5,
		"Resources/Shaders/Noise/Noise_Vertex.glsl",
		"Resources/Shaders/Noise/Noise_Fragment.glsl"
	};

	Initialize();
}

Noise::Noise(const NoiseSettings& settings)
{
	m_Settings = settings;

	Initialize();
}

Noise::~Noise()
{

}

void Noise::Draw()
{
	m_Shader.Use();
	SetUniforms();

	m_VertexArray.Bind();
	GLWrapper::DrawArray(GL_TRIANGLE_STRIP, 0, 4);
	m_VertexArray.Unbind();

	m_Shader.Unbind();
}

void Noise::Initialize()
{
	m_Shader = GLShader(m_Settings.VertexShaderPath, m_Settings.FragmentShaderPath);

	// Set uniforms.
	m_Shader.Use();
	SetUniforms();

	// @Note: I tried to use only one VBO but didn't work for some reasons.
	// I still don't know why, so I will do some investigations later on.
	// Found a fix on the web, saying that I need to use 2 VBOs..?
	auto vbo1 = std::make_unique<GLVertexBuffer>(std::vector<float> {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	}, GLDrawMode::STATIC);
	GLWrapper::VertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0); // Position
	m_VertexArray.AddBuffer(vbo1);

	auto vbo2 = std::make_unique<GLVertexBuffer>( std::vector<float> {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	}, GLDrawMode::STATIC);
	// @Note: Replace with location = 1.
	GLWrapper::VertexAttributePointer(m_Shader.ProgramId, "mTexCoords", 2, GL_FLOAT, 2 * sizeof(float), 0); // TexCoords
	m_VertexArray.AddBuffer(vbo2);

#if _DEBUG
	assert(vbo1 == nullptr);
	assert(vbo2 == nullptr);
#endif
}

void Noise::SetUniforms()
{
	m_Shader
		.SetFloat("H", m_Settings.Height)
		.SetFloat("lacunarity", m_Settings.Lacunary)
		.SetFloat("octaves", m_Settings.Octaves)
		.SetFloat("offset", m_Settings.Offset)
		.SetFloat("gain", m_Settings.Gain)
		.SetFloat("density", m_Settings.Density);
}