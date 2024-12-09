#include "Phyz.h"
bool Cube::checkCubeTouch(const std::vector<double>& fingerPosition, const Cube& cube)
{
const Quaternion Quat=cube.orientation.Rotation(cube.orientation.Q).Q;
std::vector<float> translatedPosition = { Quat.x, Quat.y, Quat.z};
double distance = std::sqrt(std::pow(fingerPosition[0] - translatedPosition[0], 2) +std::pow(fingerPosition[1] - translatedPosition[1], 2) +std::pow(fingerPosition[2] - translatedPosition[2], 2));
return distance <= 0.5;
}
std::pair<bool, std::vector<double>> Cube::intersectRayAndPlane(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection,const std::vector<double>& planeNormal, double planeDistance)
{
double denominator = std::inner_product(rayDirection.begin(), rayDirection.end(), planeNormal.begin(), 0.0);
if (std::fabs(denominator) < 1e-6) return {false, {}};  
}
Sphere::checkRaySphereIntersection(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection, const std::vector<double>& sphereCenter, double sphereRadius)
{
    std::vector<double> oc = rayOrigin - sphereCenter;
    double a = std::dot(rayDirection, rayDirection);
    double b = 2.0 * std::dot(oc, rayDirection);
    double c = std::dot(oc, oc) - sphereRadius * sphereRadius;
    double discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}
std::tuple<int, int, int> Sphere::getNearestPointOnSphere(const std::vector<double>& rayOrigin, const std::vector<double>& rayDirection, const std::vector<double>& sphereCenter, double sphereRadius){
    double t = std::max(0.0, std::dot(sphereCenter - rayOrigin, rayDirection) / std::dot(rayDirection, rayDirection));
    std::vector<double> nearestPoint = rayOrigin + t * rayDirection;
    double distance = std::sqrt(std::pow(nearestPoint[0] - sphereCenter[0], 2) + std::pow(nearestPoint[1] - sphereCenter[1], 2) + std::pow(nearestPoint[2] - sphereCenter[2], 2));
    return {sphereCenter[0] + (nearestPoint[0] - sphereCenter[0]) * sphereRadius / distance,sphereCenter[1] + (nearestPoint[1] - sphereCenter[1]) * sphereRadius / distance,sphereCenter[2] + (nearestPoint[2] - sphereCenter[2]) * sphereRadius / distance}}
    
void drawDigit(int digit, const SO3& rotation, const DigitTexture& texture, std::vector<std::vector<bool>>& output)
{
std::vector<std::vector<double>> vertices = {
{-0.5, -0.5, 0.0},
{0.5, -0.5, 0.0},
{0.5, 0.5, 0.0},
{-0.5, 0.5, 0.0}
};
for (int i = 0; i < 4; i++) {
std::vector<double> rotatedVertex = rotation.Rotation(vertices[i]);
int x = static_cast<int>(std::round(rotatedVertex[0] * (texture.width - 1) + texture.width / 2));
int y = static_cast<int>(std::round(rotatedVertex[1] * (texture.height - 1) + texture.height / 2));
if (x >= 0 && x < texture.width && y >= 0 && y < texture.height && texture.data[y][x]) {
output[y][x] = true;
}
}
}
void handleMouseDrag(float deltaX, float deltaY, SO3& cubeRotation, const Vector3& cubePosition, float sphereRadius) {
    Vector3 rayOrigin = cubePosition; 
    Vector3 ray=deltaX, deltaY, -1.0f};
    Vector3 rayDirection = ray.normalize();
    Vector3 sphereCenter = cubePosition + Vector3(sphereRadius / 2.0f, sphereRadius / 2.0f, sphereRadius / 2.0f);
    if (checkRaySphereIntersection(rayOrigin, rayDirection, sphereCenter, sphereRadius)) {
        float angleX = deltaY * 0.01f;
        float angleY = deltaX * 0.01f;
        float angle = std::sqrt(delta_x * delta_x + delta_y * delta_y) * 0.01f;
        Quaternion rotationX = Quaternion::fromAxisAngle(Vector3(1, 0, 0), angleX);
        Quaternion rotationY = Quaternion::fromAxisAngle(Vector3(0, 1, 0), angleY);
        cubeRotation *= SO3::Rotation(rotationX);
        cubeRotation *= SO3::Rotation(rotationY);
    } else {
        Vector3 nearestPoint = getNearestPointOnSphere(rayOrigin, rayDirection, sphereCenter, sphereRadius);
        Vector3 rotationAxis = (nearestPoint - sphereCenter).normalize();
        Quaternion rotationAroundAxis = Quaternion::fromAxisAngle(rotationAxis, angle);
        cubeRotation *= SO3::Rotation(rotationAroundAxis);
    }
}

void Cube::rotate(const Vector3& ray_origin, const Vector3& ray_direction)
{
    float t;
        if (Sphere.checkRaySphereIntersection(ray_origin, ray_direction, t)) {
            Vector3 intersection_point = ray_origin + ray_direction * t;
            Vector3 axis = intersection_point - center;
            axis = axis.normalize();
            float angle = 0.05f;
            Quaternion rotation_quaternion = Quaternion::fromAxisAngle(axis, angle);
            rotation = rotation * rotation_quaternion;
        } else {
            Vector3 closest_point = sphere.closestPointOnRay(ray_origin, ray_direction);
            Vector3 axis = closest_point - center;
            float angle = 0.05f;
            Quaternion rotation_quaternion = Quaternion::fromAxisAngle(axis, angle);
            rotation = rotation * rotation_quaternion;
        }
    }
}
