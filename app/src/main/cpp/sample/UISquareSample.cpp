//
// Created by ByteFlow on 2019/7/9.
//

#include <vector>
#include "UISquareSample.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"

UISquareSample::UISquareSample()
{
    m_vertices_dirty = false;
    m_VaoId = 0;
    m_VboIds[0] = 0;
    m_VboIds[1] = 0;
}

UISquareSample::~UISquareSample()
{
}


void UISquareSample::LoadImage(NativeImage *pImage)
{
    //null implement

}

void UISquareSample::Init()
{
    InitShader();

    InitVAOData();

    UploadVAO();
}

void UISquareSample::UploadVAO() {// Generate VAO Id
    glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(2, m_VboIds);

    glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[1]);


    glBufferData(GL_ARRAY_BUFFER, m_vertices_vector.size() * sizeof(GLfloat), &m_vertices_vector[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices_vector.size() * sizeof(GLushort) , &m_indices_vector[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) 0 );

    glBindVertexArray(GL_NONE);

    LOGERROR("value : %d %d %d ", m_VaoId, m_VboIds[0], m_VboIds[1]);
}

void UISquareSample::UpdateVBO() const {
    glUseProgram (m_ProgramObj);
    glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_vector.size() * sizeof(GLfloat), &m_vertices_vector[0]);
    LOGERROR("UpdateTransformMatrix : %f %f",m_vertices_vector[6],m_vertices_vector[1]);
    glBindVertexArray(GL_NONE);
}

void UISquareSample::DeleteVAO() {
    if(m_VboIds[0] != 0)
    {
        glDeleteBuffers(2, m_VboIds);
        m_VboIds[0]=0;
        m_VboIds[1]=0;
    }


    if(m_VaoId != 0)
    {
        glDeleteVertexArrays(1, &m_VaoId);
        m_VaoId = 0;
    }
}

void UISquareSample::InitVAOData() {
    //
    // 1 2
    // 0 3
    std::__ndk1::vector<GLfloat> tmp_vertices = {
            -1.00f, 	-1.00f, 	 0.99f,
            -1.00f, 	+1.00f, 	 0.99f,
            +1.00f,	    +1.00f, 	 0.99f,
            +1.00f, 	-1.00f, 	 0.99f,
    };

    // Index buffer data
    std::__ndk1::vector<GLushort> tmp_indices = {2, 1, 0, 0, 3, 2};
    m_vertices_vector.clear();
    m_vertices_vector.clear();
    m_vertices_vector.insert(m_vertices_vector.end(), tmp_vertices.begin(), tmp_vertices.end());
    m_indices_vector.insert(m_indices_vector.end(), tmp_indices.begin(), tmp_indices.end());
}

void UISquareSample::InitShader() {
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec3 vPosition;  \n"
            "uniform vec3 pos_offset;\n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vec4(vPosition.x + pos_offset.x, vPosition.y + pos_offset.y, vPosition.z, 1.0);              \n"
            "}                                        \n";

    char fShaderStr[] =
			"#version 300 es                              \n"
			"precision mediump float;                     \n"
			"out vec4 fragColor;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor = vec4 ( 1.0, 1.0, 0.0, 1.0 );  \n"
			"}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
    m_PosOffset = glGetUniformLocation(m_ProgramObj, "pos_offset");
}

void UISquareSample::Draw(int screenW, int screenH)
{
    LOGCATE("UISquareSample::Draw");
    if(m_ProgramObj == 0)
        return;
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    if(m_vertices_dirty)UpdateVBO();
    //shader和VAO
    glUseProgram (m_ProgramObj);
    glBindVertexArray(m_VaoId);

    //更新参数
//    glUniform3f(m_PosOffset, (m_AngleY)*1.0/360.0, -(m_AngleX)*1.0/360.0, 2.0f);

    //绘制
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *)0);
    glLineWidth(100.0);
    glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_SHORT, (const void *)0);
}

void UISquareSample::Destroy()
{
    if (m_ProgramObj)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }

}

void UISquareSample::UpdateTransformMatrix(float rotateX, float rotateY, float scaleX,
                                                float scaleY) {
    m_AngleX = static_cast<int>(rotateX);
    m_AngleY = static_cast<int>(rotateY);

//    m_vertices_vector[1] = 0.8 - m_AngleX*1.0/360.0/4.0;
//    m_vertices_vector[10] = m_vertices_vector[1];
//    m_vertices_vector[6] = -0.8 + m_AngleY*1.0/360.0/4.0;
//    m_vertices_vector[9] = m_vertices_vector[6];
//    m_vertices_dirty = true;
//    LOGERROR("UpdateTransformMatrix : %f %f",m_vertices_vector[6],m_vertices_vector[1]);
}
