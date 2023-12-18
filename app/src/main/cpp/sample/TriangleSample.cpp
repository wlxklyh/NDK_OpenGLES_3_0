//
// Created by ByteFlow on 2019/7/9.
//

#include "TriangleSample.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"

TriangleSample::TriangleSample()
{

}

TriangleSample::~TriangleSample()
{
}


void TriangleSample::LoadImage(NativeImage *pImage)
{
	//null implement

}

void TriangleSample::Init()
{
	if(m_ProgramObj != 0)
		return;
	char vShaderStr[] =
			"#version 300 es                          \n"
			"layout(location = 0) in vec3 vPosition;  \n"
			"void main()                              \n"
			"{                                        \n"
			"   gl_Position = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);              \n"
			"}                                        \n";

	char fShaderStr[] =
			"#version 300 es                              \n"
            "#extension GL_EXT_shader_framebuffer_fetch : enable\n"
			"precision mediump float;                     \n"
			"inout vec4 fragColor;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor = vec4 ( fragColor.r, 0.0, 0.0, 1.0 );  \n"
			"}                                            \n";

//	char fShaderStr[] =
//			"#version 300 es                              \n"
//			"precision mediump float;                     \n"
//			"out vec4 fragColor;                          \n"
//			"void main()                                  \n"
//			"{                                            \n"
//			"   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
//			"}                                            \n";

	m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

    LOGERROR("hawk");

	//顶点坐标
	GLfloat vVertices[] = {
			-1.0f, 	-1.0f, 	 0.99f,
			1.0f, 	-1.0f, 	 0.99f,
			-1.0f,	 1.0f, 	 0.99f,
			1.0f, 	-1.0f, 	 0.99f,
			1.0f,	 1.0f, 	 0.99f,
			-1.0f,	 1.0f, 	 0.99f,
	};

	// Index buffer data
	GLushort indices[6] = { 0, 1, 2, 3, 4, 5};


    // Generate VAO Id
    glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);

	// Generate VBO Ids and load the VBOs with data
	glGenBuffers(2, m_VboIds);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

void TriangleSample::Draw(int screenW, int screenH)
{
	LOGCATE("TriangleSample::Draw");
	if(m_ProgramObj == 0)
		return;
    glDisable(GL_BLEND);
//    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    glDepthMask(GL_TRUE);

	//shader和VAO
	glUseProgram (m_ProgramObj);
	glBindVertexArray(m_VaoId);

	//绘制
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *)0);
}

void TriangleSample::Destroy()
{
	if (m_ProgramObj)
	{
		glDeleteProgram(m_ProgramObj);
		m_ProgramObj = GL_NONE;
	}

}
