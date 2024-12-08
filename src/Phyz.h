//Простите, написала и забыла закоммитить
#ifndef PHYZ
#define PHYZ
#include <vector>
#include <string>
using namespace VMath;
struct DigitTexture
{
    std::vector<std::vector <bool>> data;
    int width, height;
};
class Sphere
{
    public:
        Vector3 center;
        float radius;
        //Проверка пересечения со сферой
        bool checkRaySphereIntersection(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection, const std::vector<double>& sphereCenter, double sphereRadius);
        //Ближайшая точка пот луча до сферы
        std::vector<double> getNearestPointOnSphere(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection, const std::vector<double>& sphereCenter, double sphereRadius);
        Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
};
class Cube {
public:
    Sphere sphere;       // Сфера вокруг куба
    Cube(Vector3 center = Vector3(0.0f), float size = 1.0f)
        : center(center), size(size), rotation(), sphere(center, size * std::sqrt(3) / 2) {}
    Quaternion rotation; // Текущий поворот куба
    std::vector<double> position;
    Quaternion orientation;
    bool isMine;
    bool isRevealed;
    Vector3 center;
    double radius; //сферы, описанной вокруг куба
    double size;
    //Проверка касания ячейски
    bool checkCubeTouch(const std::vector<double>& fingerPosition, const Cube& cube);
    //Пересечение с номером ячейки
    std::pair<bool, std::vector<double>> intersectRayAndPlane(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection,const std::vector<double>& planeNormal, double planeDistance);
    //Номер ячейки
    std::tuple<int, int, int> getSelectedCell(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection,const Quaternion& rotation, int cubeSide);
    };
void rotate(const Vector3& ray_origin, const Vector3& ray_direction);

//Отрисовка цифр
void drawDigit(int digit, const Quaternion& rotation, const DigitTexture& texture, std::vector<std::vector<bool>>& output);
void handleMouseDrag(float deltaX, float deltaY, SO3& cubeRotation, const Vector3& cubePosition, float sphereRadius);
#endif