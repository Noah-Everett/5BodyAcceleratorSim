#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

class Vector4D {
private:
    std::array<double, 4> components;
    static constexpr double c = 299792458.0; // Speed of light in m/s

public:
    // Constructor
    Vector4D(double t = 0.0, double x = 0.0, double y = 0.0, double z = 0.0)
        : components{t, x, y, z} {}

    // Access operators
    double& operator[](int index) { return components[index]; }
    const double& operator[](int index) const { return components[index]; }

    // Basic vector operations
    Vector4D operator+(const Vector4D& other) const {
        return Vector4D(components[0] + other[0], components[1] + other[1],
                        components[2] + other[2], components[3] + other[3]);
    }

    Vector4D operator-(const Vector4D& other) const {
        return Vector4D(components[0] - other[0], components[1] - other[1],
                        components[2] - other[2], components[3] - other[3]);
    }

    Vector4D operator*(double scalar) const {
        return Vector4D(components[0] * scalar, components[1] * scalar,
                        components[2] * scalar, components[3] * scalar);
    }

    // Minkowski inner product
    double dot(const Vector4D& other) const {
        return components[0] * other[0] - components[1] * other[1] -
               components[2] * other[2] - components[3] * other[3];
    }

    // Lorentz boost
    void boost(double bx, double by, double bz) {
        double b_squared = bx*bx + by*by + bz*bz;
        if (b_squared >= 1) {
            throw std::invalid_argument("Total velocity must be less than c");
        }
        double gamma = 1.0 / std::sqrt(1.0 - b_squared);
        double bt = gamma * (bx*components[1] + by*components[2] + bz*components[3]) / c;

        double new_t = gamma * (components[0] - c * bt);
        double new_x = components[1] + (gamma - 1) * bx * (bx*components[1] + by*components[2] + bz*components[3]) / b_squared - gamma * bx * components[0];
        double new_y = components[2] + (gamma - 1) * by * (bx*components[1] + by*components[2] + bz*components[3]) / b_squared - gamma * by * components[0];
        double new_z = components[3] + (gamma - 1) * bz * (bx*components[1] + by*components[2] + bz*components[3]) / b_squared - gamma * bz * components[0];

        components = {new_t, new_x, new_y, new_z};
    }

    // Rotation methods
    void rotateX(double angle) {
        double cosA = std::cos(angle);
        double sinA = std::sin(angle);
        double new_y = components[2] * cosA - components[3] * sinA;
        double new_z = components[2] * sinA + components[3] * cosA;
        components[2] = new_y;
        components[3] = new_z;
    }

    void rotateY(double angle) {
        double cosA = std::cos(angle);
        double sinA = std::sin(angle);
        double new_x = components[1] * cosA + components[3] * sinA;
        double new_z = -components[1] * sinA + components[3] * cosA;
        components[1] = new_x;
        components[3] = new_z;
    }

    void rotateZ(double angle) {
        double cosA = std::cos(angle);
        double sinA = std::sin(angle);
        double new_x = components[1] * cosA - components[2] * sinA;
        double new_y = components[1] * sinA + components[2] * cosA;
        components[1] = new_x;
        components[2] = new_y;
    }

    // General rotation using Euler angles
    void rotate(double phi, double theta, double psi) {
        rotateZ(phi);
        rotateY(theta);
        rotateZ(psi);
    }

    // Utility methods
    double magnitude() const {
        return std::sqrt(std::abs(this->dot(*this)));
    }

    Vector4D unitVector() const {
        double mag = magnitude();
        return Vector4D(components[0] / mag, components[1] / mag,
                        components[2] / mag, components[3] / mag);
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Vector4D& v) {
        os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
        return os;
    }
};