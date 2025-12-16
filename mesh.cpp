#include "mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

Mesh Mesh::LoadFromObj(const std::string& filename) {
    Mesh mesh;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return mesh;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            // Считываем позицию вершины: v x y z
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            mesh.vertices.push_back(v);
        }
        else if (prefix == "f") {
            // Вектор для хранения индексов вершин текущего полигона
            std::vector<int> faceIndices;
            std::string segment;

            // Читаем части строки после f по одной.
            while (ss >> segment) {
                // Нам нужно извлечь только ПЕРВОЕ число до слэша.
                // Форматы могут быть: "1", "1/2", "1//3", "1/2/3"
                
                std::string indexStr;
                size_t slashPos = segment.find('/');

                if (slashPos != std::string::npos) {
                    indexStr = segment.substr(0, slashPos);
                } else {
                    indexStr = segment;
                }

                // Преобразуем в число
                try {
                    int idx = std::stoi(indexStr);
                    faceIndices.push_back(idx - 1);
                } catch (...) {
                    continue; 
                }
            }
                
            // Тут реализуем триангуляцию Превращение многоугольника в треугольники
            // Первая вершина (0) соединяется со всеми последующими парами (i, i+1).
            // Для квадрата (0,1,2,3) это даст два треугольника: (0,1,2) и (0,2,3).
            if (faceIndices.size() >= 3) {
                for (size_t i = 1; i < faceIndices.size() - 1; i++) {
                    Mesh::Face face;
                    face.v[0] = faceIndices[0];
                    face.v[1] = faceIndices[i];
                    face.v[2] = faceIndices[i + 1];
                    mesh.faces.push_back(face);
                }
            }
        }
    }

    std::cout << "Loaded " << filename << ": " 
              << mesh.vertices.size() << " vertices, " 
              << mesh.faces.size() << " triangles." << std::endl;

    return mesh;
}
