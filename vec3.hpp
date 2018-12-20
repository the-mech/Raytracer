#pragma once

#include <math.h>
#include <iostream>

class vec3
{
public:
	vec3() {};

	vec3(double px, double py, double pz) :x(px), y(py), z(pz) {}

	vec3(double t):x(t),y(t),z(t){}

	~vec3() {

	}

	inline const vec3& operator+() { return *this; }
	inline const vec3 operator-() { return vec3(-x, -y, -z); }

	//vector-vector add/sub

	friend vec3 operator+(const vec3& lhs, const vec3& rhs) {
		return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	friend vec3 operator-(const vec3& lhs, const vec3& rhs) {
		return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	//vector-vector mul/div

	friend vec3 operator*(const vec3& lhs, const vec3& rhs) {
		return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	friend vec3 operator/(const vec3& lhs, const vec3& rhs) {
		return vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	//vector-scalar mul/div
	friend vec3 operator*(const vec3& lhs, const double rhs) {
		return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
	}

	friend vec3 operator*(const double lhs, const vec3& rhs) {
		return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	friend vec3 operator/(const vec3& lhs, const double rhs) {
		return vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
	}

	//vector-vector assign add/sub
	inline vec3& operator+=(const vec3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	inline vec3& operator-=(const vec3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	//vector-vector assign mul/div
	inline vec3& operator*=(const vec3& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}
	inline vec3& operator/=(const vec3& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}
	//vector-scalar assign mul/div
	inline vec3& operator*=(const double t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}
	inline vec3& operator/=(const double t) {
		double k = 1.0 / t;
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}




	inline double length() const {
		return sqrt(x*x + y * y + z * z);
	}
	inline double squared_length() const {
		return x * x + y * y + z * z;
	}

	inline void normalize() {

		double inverse_length = 1.0 / length();

		x *= inverse_length;
		y *= inverse_length;
		z *= inverse_length;
	}


	static inline double dot(const vec3& lhs, const vec3& rhs) {
		return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
	}

	static inline vec3 cross(const vec3&lhs, const vec3& rhs) {
		vec3 tmp;

		tmp.x = lhs.y*rhs.z - lhs.z*rhs.y;
		tmp.y = lhs.z*rhs.x - lhs.x*rhs.z;
		tmp.z = lhs.x*rhs.y - lhs.y*rhs.x;

		return tmp;
	}

	//stream operators

	friend std::ostream& operator<<(std::ostream& os, const vec3& v) {
		os << v.x << " " << v.y << " " << v.z;

		return os;
	}

	friend std::istream& operator>>(std::istream& is, vec3& v) {
		is >> v.x >> v.y >> v.z;

		return is;
	}

	static vec3 unit_vector(const vec3& v) {
		return v / v.length();
	}

	// class fields
	// accessible as
	// x or r
	// y or g
	// z or b

	union {
		double x;
		double r;
	};

	union {
		double y;
		double g;
	};
	union {
		double z;
		double b;
	};
};

