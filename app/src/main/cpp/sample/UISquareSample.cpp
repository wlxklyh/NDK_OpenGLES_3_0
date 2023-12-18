//
// Created by ByteFlow on 2019/7/9.
//

#include <vector>
#include "UISquareSample.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"

UISquareSample::UISquareSample()
{

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
    if(m_ProgramObj != 0)
        return;
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec3 vPosition;  \n"
            "uniform vec3 pos_offset;\n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vec4(vPosition.x + pos_offset.x, vPosition.y + pos_offset.y, vPosition.z, 1.0);              \n"
            "}                                        \n";

//    char fShaderStr[] =
//            "#version 300 es                              \n"
//            "#extension GL_EXT_shader_framebuffer_fetch : enable\n"
//            "precision mediump float;                     \n"
//            "inout vec4 fragColor;                          \n"
//            "void main()                                  \n"
//            "{                                            \n"
//            "   fragColor = vec4 ( fragColor.r, 0.0, 0.0, 1.0 );  \n"
//            "}                                            \n";

    char fShaderStr[] =
			"#version 300 es                              \n"
			"precision mediump float;                     \n"
			"out vec4 fragColor;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor = vec4 ( 0.9, 1.0, 0.0, 1.0 );  \n"
			"}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);


    const int numRectangles = 5; // 5x5共25个矩形



    // 生成顶点数据和索引数据
    for (int i = 0; i < numRectangles; ++i) {
        for (int j = 0; j < numRectangles; ++j) {
            float left = -1.0f + i * 0.4f;   // 计算左边界
            float right = -0.6f + i * 0.4f;  // 计算右边界
            float top = 1.0f - j * 0.4f;     // 计算上边界
            float bottom = 0.6f - j * 0.4f;  // 计算下边界

            // 顶点数据
            vVertices_vector.insert(vVertices_vector.end(), {
                    left, top, 0.0f,       // 左上角
                    left, bottom, 0.0f,    // 左下角
                    right, bottom, 0.0f,   // 右下角
                    right, top, 0.0f       // 右上角
            });

            // 索引数据
            GLushort baseIndex = static_cast<GLushort>(i * numRectangles * 4 + j * 4);
            indices_vector.insert(indices_vector.end(), baseIndex);
            indices_vector.insert(indices_vector.end(), baseIndex+1);
            indices_vector.insert(indices_vector.end(), baseIndex+3);

            indices_vector.insert(indices_vector.end(), baseIndex+1);
            indices_vector.insert(indices_vector.end(), baseIndex+2);
            indices_vector.insert(indices_vector.end(), baseIndex+3);

        }

        m_PosOffset = glGetUniformLocation(m_ProgramObj, "pos_offset");
    }

// 将容器中的数据转换为普通数组
//    GLfloat* vVertices = &vVertices[0];
//    GLushort* indices = &indices[0];

//    //顶点坐标
//    GLfloat vVertices[] = {
//            -1.0f, 	-1.0f, 	 0.0f,
//            1.0f, 	-1.0f, 	 0.0f,
//            -1.0f,	 1.0f, 	 0.0f,
//            1.0f, 	-1.0f, 	 0.0f,
//            1.0f,	 1.0f, 	 0.0f,
//            -1.0f,	 1.0f, 	 0.0f,
//    };
//
//    // Index buffer data
//    GLushort indices[6] = { 0, 1, 2, 3, 4, 5};


    // Generate VAO Id
    glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);

    // Generate VBO Ids and load the VBOs with data
    glGenBuffers(2, m_VboIds);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, vVertices_vector.size() * sizeof(GLfloat), &vVertices_vector[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_vector.size() * sizeof(GLushort) , &indices_vector[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[1]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) 0 );

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LOGERROR("OpenGL Error: %d\n", error);
    }
    glBindVertexArray(GL_NONE);
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

    //shader和VAO
    glUseProgram (m_ProgramObj);
    glBindVertexArray(m_VaoId);
    glUniform3f(m_PosOffset, (m_AngleY%360)*1.0/360.0, -(m_AngleX%360)*1.0/360.0, 2.0f);

    //绘制
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *)0);
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
}
