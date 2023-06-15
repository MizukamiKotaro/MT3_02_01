#pragma once
#include"MyVector3.h"
#include"MyMatrix4x4.h"
#include<cstdint>
class Sphere
{
public:
	Sphere(const MyVector3& center, const MyVector3& scale, const MyVector3& rotate, const float& radius);

	static void DrawSphere(const Sphere& sphere, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);

private:
	bool IsCollision(const Sphere& Sphere);

public:
	MyVector3 center_;
	MyVector3 scale_;
	MyVector3 rotate_;
	float radius_;
};

