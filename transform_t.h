#ifndef TRANSFORM_T_H
#define TRANSFORM_T_H

#include "matrix_t.h"

class transform_t
{
public:
    matrix_t world;         // ��������任
    matrix_t view;          // ��Ӱ������任
    matrix_t projection;    // ͶӰ�任
    matrix_t transform;     // transform = world * view * projection
    float w, h;             // ��Ļ��С

    transform_t() :w(0.0f), h(0.0f) {}
    // ���캯������ʼ����������Ļ����
    transform_t(int width, int height)
    {
        float aspect = (float)width / ((float)height);
        world.setIdentity();
        view.setIdentity();
        projection = perspective(3.1415926f*0.5f, aspect, 1.0f, 500.0f);
        transform = world * view * projection;
        w = (float)width;
        h = (float)height;
    }

    // �������
    void update() 
    {
        transform = world * view * projection;
    }

    // ��ʸ�� x ���� project 
    vector_t apply( const vector_t &x) const
    {
        return x * transform;
    }

    // ��һ�����õ���Ļ����
    vector_t homogenize(const vector_t &x) const
    {
        vector_t y;
        float rhw = 1.0f / x.w;
        y.x = (x.x * rhw + 1.0f) * w * 0.5f;
        y.y = (1.0f - x.y * rhw) * h * 0.5f;
        y.z = x.z * rhw;
        y.w = 1.0f;
        return y;
    }
};

// ����������ͬ cvv �ı߽�������׶�ü�
inline int transform_check_cvv(const vector_t &v)
{
    float w = v.w;
    int check = 0;
    if (v.z < 0.0f) check |= 1;
    if (v.z > w) check |= 2;
    if (v.x < -w) check |= 4;
    if (v.x > w) check |= 8;
    if (v.y < -w) check |= 16;
    if (v.y > w) check |= 32;
    return check;
}


#endif // !TRANSFORM_T_H
