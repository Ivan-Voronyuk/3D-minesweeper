#ifndef PHYZ
#define PHYZ
#include "types.h"
#include <vector>
#include <string>
using namespace VMath;

struct RGB {
    uint8_t r, g, b;
};

struct DigitTexture
{
    std::vector<std::vector <bool>> data;
    int width, height;
};
class Sphere
{
    public:
        Point3 center;
        float radius;
    
        Sphere(const Point3& center, float radius) : center(center), radius(radius) {}
};
class Cube {
public:
    Sphere sphere;       // Сфера вокруг куба
    Cube(Point3 center = Point3(), float size = 1.0f)
        : center(center), size(size), rotation(), sphere(center, size * std::sqrt(3) / 2) {}
    Quaternion rotation; // Текущий поворот куба
    std::vector<double> position;
    SO3 orientation;
    bool isMine;
    bool isRevealed;
    Point3 center;
    double radius; //сферы, описанной вокруг куба
    double size;
    //Проверка касания ячейски
    bool checkCubeTouch(const Vector3& fingerPosition, const SO3& cubeTransform);
    //Пересечение с номером ячейки
    std::pair<bool, std::vector<double>> intersectRayAndPlane(const Vector3& rayOrigin, const Vector3& rayDirection, const Vector3& planeNormal, double planeDistance);
    //Номер ячейки
    std::tuple<int, int, int> getSelectedCell(const Vector3& rayOrigin, const Vector3& rayDirection,const SO3& rotation,const Vector3& cubeSize,int cellsPerSide);
    //SO3 rotate(const Vector3& ray_origin, const Vector3& ray_direction);
    };

//Отрисовка цифр
void drawDigit(int digit, const SO3& rotation, const Vector3& position, const std::vector<std::vector<RGB>>& texture, std::vector<std::vector<bool>>& output, double size);
SO3 handleMouseDrag(const Point3& rayOrigin, const Vector3& rayDirection, SO3& cubeRotation, const Vector3& cubePosition, float sphereRadius);
//Проверка пересечения со сферой
bool checkRaySphereIntersection(const Vector3& rayOrigin, const Vector3& rayDirection, const Vector3& sphereCenter, double sphereRadius);
//Ближайшая точка пот луча до сферы
Point3 getNearestPointOnSphere(const Vector3& rayOrigin, const Vector3& rayDirection, const Vector3& sphereCenter, double sphereRadius);

#endif