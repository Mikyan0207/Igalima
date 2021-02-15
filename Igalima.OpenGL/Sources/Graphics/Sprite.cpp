//
// Created by Mikyan on 15/02/2021.
//

#include <Graphics/Sprite.h>

Sprite::Sprite(const std::string& path)
{
    m_Texture = Texture(path);
    m_Rectangle = Rectangle(0, 0, m_Texture.Width, m_Texture.Height);
    m_VertexArray = new GLVertexArray();
    
    auto vbo = std::make_unique<GLVertexBuffer>(std::vector<float> {
                                                    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                                    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                                                    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                                                    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
                                                }, GLDrawMode::STATIC);
    
    m_VertexArray->AddBuffer(vbo);
    
    auto ebo = std::make_unique<GLIndexBuffer>(std::vector<uint32_t> {
                                                   0, 1, 3,
                                                   1, 2, 3,
                                               }, GLDrawMode::STATIC);
    
    m_VertexArray->AddBuffer(ebo);
    
    GLWrapper::VertexAttributePointer(0, 3, GL_FLOAT, 5 * sizeof(float), 0); // Position.
    GLWrapper::VertexAttributePointer(1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float)); // Texture Coords.
    
    // TODO(mikyan): Pass shaders using SpriteSettings struct?
    m_Shader = GLShader("Demos/Shaders/Sprite/Sprite_Vertex.glsl", "Demos/Shaders/Sprite/Sprite_Fragment.glsl");
    
    m_Shader.Use();
    m_Shader.SetInt("Texture", 0);
    m_Shader.Unbind();
}

Sprite::~Sprite()
{
    delete m_VertexArray;
}

void Sprite::Draw(const glm::mat4& view)
{
    m_Shader.Use();
    
    auto model = glm::mat4(1.0f);
    
    //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
    
    m_Shader.SetMat4("Model", model);
    
    glActiveTexture(GL_TEXTURE0);
    m_Texture.Bind();
    m_VertexArray->Bind();
    
    GLWrapper::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    m_VertexArray->Unbind();
    m_Shader.Unbind();
}