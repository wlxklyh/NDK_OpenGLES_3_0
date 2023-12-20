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
	bool m_vertices_dirty;
    std::__ndk1::vector<GLfloat> m_vertices_vector;
    // 存储索引数据的容器
    std::__ndk1::vector<GLushort> m_indices_vector;
    GLuint m_VaoId;
    GLuint m_VboIds[2];
	UISquareSample();
	virtual ~UISquareSample();

	virtual void LoadImage(NativeImage *pImage);

	virtual void Init();

	virtual void Draw(int screenW, int screenH);
    virtual void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX,
                                               float scaleY);
    virtual void Destroy();

    void InitShader();

    void InitVAOData();

    void UploadVAO();

    void DeleteVAO();

	void UpdateVBO() const;
};


#endif //NDK_OPENGLES_3_0_UISQURESAMPLE_H
