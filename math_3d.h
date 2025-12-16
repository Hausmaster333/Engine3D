#pragma once
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float f) const { return Vec3(x * f, y * f, z * f); }

    Vec3 Normalize() const { // Нормализуем вектор
        float length = std::sqrt(x*x + y*y + z*z);
        return Vec3(x / length, y / length, z / length);
    }
};

struct Mat4 {
    float m[4][4];

    Mat4() {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                m[i][j] = 0.0f;
    }

    static Mat4 Identity() {
        Mat4 res;
        res.m[0][0] = 1.0f; res.m[1][1] = 1.0f; res.m[2][2] = 1.0f; res.m[3][3] = 1.0f;
        return res;
    }

    // Матрицы вращения
    static Mat4 RotateX(float angleRadians);
    static Mat4 RotateY(float angleRadians);
    static Mat4 RotateZ(float angleRadians);
    static Mat4 Translate(float x, float y, float z);
    static Mat4 Projection(float fov, float aspectRatio, float zNear, float zFar); // Матрица проекции - преобразует 3д в 2д

    Mat4 operator*(const Mat4& other) const;
};

Vec3 MultiplyMatrixVector(const Vec3& i, const Mat4& m);

float DotProduct(const Vec3& a, const Vec3& b);
Vec3 CrossProduct(const Vec3& a, const Vec3& b);
