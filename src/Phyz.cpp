#include "Phyz.h"
//---------------------------Проверка касания куба---------------------------------------------------------------------------------------------------------------------

bool Cube::checkCubeTouch(const Vector3& fingerPosition, const SO3& cubeTransform)
{

    Vector3 translatedPosition = cubeTransform * Vector3(0, 0, 0);

    double distance = (fingerPosition - translatedPosition).len(); 

    return distance <= 0.5;
}
//-------------------------Пересечение с плоскостью одной из граней-----------------------------------------------------------------------------------------------------------------------------------------------

std::pair<bool, std::vector<double>> Cube::intersectRayAndPlane(const Vector3& rayOrigin, const Vector3& rayDirection, const Vector3& planeNormal, double planeDistance)
{
    double denominator = dot(rayDirection, planeNormal);
    
    if (std::abs(denominator) < 1e-6) {
        return {false, {}};
    }

    double t = (planeDistance - dot(rayOrigin, planeNormal)) / denominator;
    
    if (t < 0) {
        return {false, {}};
    }
    
    Vector3 intersectionPoint = rayOrigin + rayDirection * t;
    
    return {true, {intersectionPoint.x, intersectionPoint.y, intersectionPoint.z}};
}

//---------------------------------------Проверка пересечения со сферой------------------------------------------------------------------------

bool checkRaySphereIntersection(const Vector3& rayOrigin, const Vector3& rayDirection, const Vector3& sphereCenter, double sphereRadius)
{
    Vector3 oc = rayOrigin - sphereCenter; 
    double a = dot(rayDirection, rayDirection); 
    double b = 2.0 * dot(rayDirection, oc);
    double c = dot(oc, oc) - sphereRadius * sphereRadius;
    double discriminant = b * b - 4 * a * c; 

    return discriminant >= 0;
}

//-----------------------------------Ближайшая точка на сфере--------------------------------------------------------------------------------------------------

Point3 getNearestPointOnSphere (const Vector3& rayOrigin, const Vector3& rayDirection, const Vector3& sphereCenter, double sphereRadius) {
        Vector3 direction = rayDirection.normalized();
        float nul{0.0};

        float t = std::max (nul, dot(direction, (Vector3(sphereCenter.x, sphereCenter.y, sphereCenter.z) - rayOrigin)) / dot(direction, direction));

        Vector3 nearestPoint = rayOrigin + direction * t;


        Vector3 pointOnSphere = Vector3(sphereCenter.x, sphereCenter.y, sphereCenter.z) + (nearestPoint - Vector3(sphereCenter.x, sphereCenter.y, sphereCenter.z)).normalized() * sphereRadius;

        return Point3(pointOnSphere.x, pointOnSphere.y, pointOnSphere.z);
    }


//------------------Отрисовка цифр---------------------------------------------------------------------------------------------------------------------------------------------------
void drawDigit(int digit, const SO3& rotation, const Vector3& position, const std::vector<std::vector<RGB>>& texture, std::vector<std::vector<bool>>& output, double size) {

    std::vector<Vector3> vertices = {
        Vector3(-0.5 * size, -0.5 * size, 0.0),
        Vector3(0.5 * size, -0.5 * size, 0.0),
        Vector3(0.5 * size, 0.5 * size, 0.0),
        Vector3(-0.5 * size, 0.5 * size, 0.0)
    };

    for (const auto& vertex : vertices) {

        Vector3 transformedVertex = rotation * vertex + position;

        int x = static_cast<int>(std::round(transformedVertex.x * (texture[0].size() - 1) + texture[0].size() / 2));
        int y = static_cast<int>(std::round(transformedVertex.y * (texture.size() - 1) + texture.size() / 2));

        if (x >= 0 && x < texture[0].size() && y >= 0 && y < texture.size()) {
            if (texture[y][x].r > 0 && texture[y][x].g > 0 && texture[y][x].b > 0) { 
                output[y][x] = true;
            }
        }
    }
}

//---------------------------------Обработка мыши-----------------------------------------------------------------------------------------------------------

SO3 handleMouseDrag(const Vector3& rayOrigin, const Vector3& rayDirection, SO3& cubeRotation, const Vector3& cubePosition, float sphereRadius) {
    Vector3 normalizedRayDirection = rayDirection.normalized();
    Vector3 sphereCenter = cubePosition + Vector3(sphereRadius / 2.0f, sphereRadius / 2.0f, sphereRadius / 2.0f);
    
    if (checkRaySphereIntersection(rayOrigin, normalizedRayDirection, sphereCenter, sphereRadius)) {
        float angleX = std::atan2(normalizedRayDirection.y, normalizedRayDirection.z);
        float angleY = std::atan2(normalizedRayDirection.x, normalizedRayDirection.z); 
        float angleZ = std::atan2(normalizedRayDirection.y, normalizedRayDirection.x); 

        Quaternion rotationX = fromAxisAngle(Vector3(1, 0, 0), angleX);
        Quaternion rotationY = fromAxisAngle(Vector3(0, 1, 0), angleY);
        Quaternion rotationZ = fromAxisAngle(Vector3(0, 0, 1), angleZ);

        cubeRotation *= SO3::Rotation(rotationX);
        cubeRotation *= SO3::Rotation(rotationY);
    } else {
        Point3 nearestPoint = getNearestPointOnSphere(rayOrigin, normalizedRayDirection, sphereCenter, sphereRadius);
        Vector3 rotationAxis{nearestPoint - sphereCenter}.normalized();
        
        float angle = normalizedRayDirection.len() * 0.01f;
        Quaternion rotationAroundAxis = fromAxisAngle(rotationAxis, angle);
        
        cubeRotation *= SO3::Rotation(rotationAroundAxis);
    }

    return cubeRotation;
}


/*SO3 Cube::rotate(const Point3& ray_origin, const Vector3& ray_direction)
{
    float t=center;
        if (sphere.checkRaySphereIntersection(ray_origin, ray_direction, t, radius)) {
            Point3 intersection_point = ray_origin + ray_direction * t;
            Vector3 axis = intersection_point - center;
            axis = axis.normalize();
            SO3 rotation_quaternion = Rotation(a_cos((axis*=ray_direction)(len(axis)*len(ray_direction))), axis);
            return rotation_quaternion;
        } else {
            Vector3 closest_point = sphere.closestPointOnRay(ray_origin, ray_direction);
            Vector3 axis = closest_point - center;
            SO3 rotation_quaternion = Rotation((axis*=ray_direction)(len(axis)*len(ray_direction)), axis);
            return rotation_quaternion;
        }
}*/

//----------------------------------------------------------------Клетка, на которую ткнули-----------------------------------------------------

std::tuple<int, int, int> Cube::getSelectedCell(const Vector3& rayOrigin, const Vector3& rayDirection,const SO3& rotation,const Vector3& cubeSize,int cellsPerSide) {
              std::vector<Vector3> planeNormals = {
        Vector3(1, 0, 0), Vector3(-1, 0, 0),
        Vector3(0, 1, 0), Vector3(0, -1, 0),
        Vector3(0, 0, 1), Vector3(0, 0, -1)
    };

    std::vector<double> planeDistances(6);
    for (int i = 0; i < 6; ++i) {
        planeDistances[i] = cubeSize.x / 2.0;
    }

    int faceIndex = -1;
    Vector3 intersectionPoint;

    for (int i = 0; i < 6; i++) {
        auto [intersected, point] = intersectRayAndPlane(
            {rayOrigin.x, rayOrigin.y, rayOrigin.z},
            {rayDirection.x, rayDirection.y, rayDirection.z},
            Translation(planeNormals[i])},
            planeDistances[i]
        );
        if (intersected) {
            faceIndex = i;
            intersectionPoint = point;
            break;
        }
    }

    if (faceIndex == -1) {
        return {-1, -1, -1}; 
    }

    Vector3 localPosition = intersectionPoint - cubeSize * 0.5;

    double cellSize = cubeSize.x / cellsPerSide;

    int x = static_cast<int>(std::floor(localPosition.x / cellSize));
    int y = static_cast<int>(std::floor(localPosition.y / cellSize));

    return {faceIndex, x, y};
}
