#include <cmath>
#include <string>
#include <iostream>

#ifndef HELPER_H
#define HELPER_H

const float M_PI = 3.14159265358979323846f;

struct CustomVector3 {
    float x, y, z;

    CustomVector3() : x(0), y(0), z(0) {}
    CustomVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    CustomVector3 operator+(const CustomVector3& rhs) const {
        return CustomVector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    CustomVector3 operator-(const CustomVector3& rhs) const {
        return CustomVector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    CustomVector3& operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    CustomVector3 operator/(float rhs) const {
        return CustomVector3(x / rhs, y / rhs, z / rhs);
    }

    float Dot(const CustomVector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    static float Dot(const CustomVector3& v1, const CustomVector3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    CustomVector3 Cross(const CustomVector3& other) const {
        return CustomVector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float Magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    void Normalize() {
        float mag = Magnitude();
        x = x / mag;
        y = y / mag;
        z = z / mag;
    }
};



struct Matrix3 {
    float m00, m01, m02; // local x-axis
    float m10, m11, m12; // local y-axis
    float m20, m21, m22; // local z-axis

    Matrix3() : m00(0), m01(0), m02(0), m10(0), m11(0), m12(0), m20(0), m21(0), m22(0) {}

    Matrix3(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12, float _m20, float _m21, float _m22)
        : m00(_m00), m01(_m01), m02(_m02), m10(_m10), m11(_m11), m12(_m12), m20(_m20), m21(_m21), m22(_m22) {}

    static Matrix3 identity;

    Matrix3(const CustomVector3& X, const CustomVector3& Y, const CustomVector3& Z)
        : m00(X.x), m01(X.y), m02(X.z), m10(Y.x), m11(Y.y), m12(Y.z), m20(Z.x), m21(Z.y), m22(Z.z) {}

    Matrix3(float uniformScale)
        : m00(uniformScale), m01(0), m02(0), m10(0), m11(uniformScale), m12(0), m20(0), m21(0), m22(uniformScale) {}

    /*Matrix3& operator*(const Matrix3& other) {
        m00 = m00 * other.m00 + m10 * other.m01 + m20 * other.m02;
        m01 = m01 * other.m00 + m11 * other.m01 + m21 * other.m02;
        m02 = m02 * other.m00 + m12 * other.m01 + m22 * other.m02;

        m10 = m00 * other.m10 + m10 * other.m11 + m20 * other.m12;
        m11 = m01 * other.m10 + m11 * other.m11 + m21 * other.m12;
        m12 = m02 * other.m10 + m12 * other.m11 + m22 * other.m12;

        m20 = m00 * other.m20 + m10 * other.m21 + m20 * other.m22;
        m21 = m01 * other.m20 + m11 * other.m21 + m21 * other.m22;
        m22 = m02 * other.m20 + m12 * other.m21 + m22 * other.m22;

        return *this;
    }*/
    Matrix3& operator*(const Matrix3& other) {
        float parentScaleX = m00;
        float parentScaleY = m11;
        float childScaleX = other.m00;
        float childScaleY = other.m11;

        m00 = m00 * other.m00 + m10 * other.m01 + m20 * other.m02;
        m01 = m01 * other.m00 + m11 * other.m01 + m21 * other.m02;
        m02 = m02 * other.m00 + m12 * other.m01 + m22 * other.m02;

        m10 = m00 * other.m10 + m10 * other.m11 + m20 * other.m12;
        m11 = m01 * other.m10 + m11 * other.m11 + m21 * other.m12;
        m12 = m02 * other.m10 + m12 * other.m11 + m22 * other.m12;

        m20 = other.m20 + m10 * other.m21 + m20 * other.m22;
        m21 = m01 * other.m20 + other.m21 + m21 * other.m22;
        m22 = m02 * other.m20 + m12 * other.m21 + m22 * other.m22;

        return *this;
    }

    CustomVector3 operator*(const CustomVector3& V) const {
        return CustomVector3(
            V.x * m00 + V.y * m10 + V.z * m20,
            V.x * m01 + V.y * m11 + V.z * m21,
            V.x * m02 + V.y * m12 + V.z * m22
        );
    }

    void SetRotateX(float radians) {
        float c = std::cos(radians);
        float s = std::sin(radians + M_PI);

        m00 = 1; m10 = 0; m20 = 0;
        m01 = 0; m11 = c; m21 = s;
        m02 = 0; m12 = -s; m22 = c;
    }

    void SetRotateY(float radians) {
        float c = std::cos(radians);
        float s = std::sin(radians + M_PI);

        m00 = c; m10 = 0; m20 = -s;
        m01 = 0; m11 = 1; m21 = 0;
        m02 = s; m12 = 0; m22 = c;
    }

    void SetRotateZ(float radians) {
        float c = std::cos(radians);
        float s = std::sin(radians + M_PI);

        m00 = c; m10 = s; m20 = 0;
        m01 = -s; m11 = c; m21 = 0;
        m02 = 0; m12 = 0; m22 = 1;
    }

    void RotateZ(float radians) {
        Matrix3 m;
        m.SetRotateZ(radians);
        *this = *this * m;
    }

    void SetTranslation(float x, float y) {
        m20 = x; m21 = y;
    }

    void Translate(float dx, float dy) {
        m20 += dx; m21 += dy;
    }

    void SetScaled(float x, float y, float z) {
        m00 = x; m10 = 0; m20 = 0;
        m01 = 0; m11 = y; m21 = 0;
        m02 = 0; m12 = 0; m22 = z;
    }

    void Scale(float x, float y, float z) {
        Matrix3 m;
        m.SetScaled(x, y, z);
        *this = *this * m;
    }

    std::string debug() {
        std::string s = "";
        s += std::to_string(m00) + " | " + std::to_string(m01) + " | " + std::to_string(m02) + " | \n";
        s += std::to_string(m10) + " | " + std::to_string(m11) + " | " + std::to_string(m12) + " | \n";
        s += std::to_string(m20) + " | " + std::to_string(m21) + " | " + std::to_string(m22) + " | \n";
        return s;
    }
};
#endif