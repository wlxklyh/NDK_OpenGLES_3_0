//
// Created by ByteFlow on 2019/7/9.
//

#ifndef NDK_OPENGLES_3_0_UISQURESAMPLE_H
#define NDK_OPENGLES_3_0_UISQURESAMPLE_H

#include "../util/ImageDef.h"
#include "GLSampleBase.h"
#include <vector>

class UISquareSample : public GLSampleBase
{
public:
    int m_AngleX;
    int m_AngleY;
    // 存储顶点数据的容器
    std::vector<GLfloat> vVertices_vector;
    // 存储索引数据的容器
    std::vector<GLushort> indices_vector;
    GLuint m_VaoId;
    GLuint m_VboIds[1];
	UISquareSample();
	virtual ~UISquareSample();

	virtual void LoadImage(NativeImage *pImage);

	virtual void Init();

	virtual void Draw(int screenW, int screenH);
    virtual void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX,
                                               float scaleY);
    virtual void Destroy();
};


#endif //NDK_OPENGLES_3_0_UISQURESAMPLE_H
