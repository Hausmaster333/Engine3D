#include "math_3d.h"
#include <cmath>

Mat4 Mat4::RotateX(float theta) {
    Mat4 mat = Mat4::Identity();
    mat.m[1][1] = cosf(theta); mat.m[1][2] = -sinf(theta);
    mat.m[2][1] = sinf(theta); mat.m[2][2] = cosf(theta);
    return mat;
}

Mat4 Mat4::RotateY(float theta) {
    Mat4 mat = Mat4::Identity();
    mat.m[0][0] = cosf(theta); mat.m[0][2] = sinf(theta);
    mat.m[2][0] = -sinf(theta); mat.m[2][2] = cosf(theta);
    return mat;
}

Mat4 Mat4::RotateZ(float theta) {
    Mat4 mat = Mat4::Identity();
    mat.m[0][0] = cosf(theta); mat.m[0][1] = -sinf(theta);
    mat.m[1][0] = sinf(theta); mat.m[1][1] = cosf(theta);
    return mat;
}

Mat4 Mat4::Translate(float x, float y, float z) { // Матрица смещения на вектор 
    Mat4 mat = Mat4::Identity();
    mat.m[0][3] = x;
    mat.m[1][3] = y;
    mat.m[2][3] = z;
    return mat;
}

Mat4 Mat4::Projection(float fov, float aspectRatio, float zNear, float zFar) { 
    Mat4 mat;
    float f = 1.0f / tanf(fov * 0.5f); 
    float q = zFar / (zFar - zNear);

    mat.m[0][0] = aspectRatio * f;
    mat.m[1][1] = f;
    mat.m[2][2] = q;
    mat.m[2][3] = -zNear * q;
    mat.m[3][2] = 1.0f;     
    return mat; // Перспективная проекция. Объекты дальше выглядят меньше. В общем сжимаем 3д координаты до [-1, 1]
}

Mat4 Mat4::operator*(const Mat4& other) const {
    Mat4 res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.m[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                res.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return res;
}

Vec3 MultiplyMatrixVector(const Vec3& i, const Mat4& m) { // Трансформация вершин
    Vec3 v;
    float x = i.x * m.m[0][0] + i.y * m.m[0][1] + i.z * m.m[0][2] + m.m[0][3];
    float y = i.x * m.m[1][0] + i.y * m.m[1][1] + i.z * m.m[1][2] + m.m[1][3];
    float z = i.x * m.m[2][0] + i.y * m.m[2][1] + i.z * m.m[2][2] + m.m[2][3];
    float w = i.x * m.m[3][0] + i.y * m.m[3][1] + i.z * m.m[3][2] + m.m[3][3];

    if (w != 0.0f) { // Перспективное деление, чтобы дальние объекты выглядели меньше
        v.x = x / w;
        v.y = y / w;
        v.z = z / w;
    }
    return v;
}

float DotProduct(const Vec3& a, const Vec3& b) { // Скалярное произведение. 
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 CrossProduct(const Vec3& a, const Vec3& b) { // Векторное произведение для двух ребер дает нормаль к треугольнику. Используется для освещения и отсечения граней
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}