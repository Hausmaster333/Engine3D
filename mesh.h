#pragma once
#include <vector>
#include <string>
#include "math_3d.h"

struct Mesh {
    std::vector<Vec3> vertices;
    struct Face {
        int v[3]; // Индексы вершин
    };
    std::vector<Face> faces;

    // Функция загрузки
    static Mesh LoadFromObj(const std::string& filename);
};