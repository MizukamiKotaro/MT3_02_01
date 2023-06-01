#pragma once
#include"MyVector2.h"
#include"MyVector3.h"
#include"Line.h"

class Calc
{
public:
	enum class LineType {
		Line, // 直線
		Ray, // 半直線
		Segment //線分 
	};
public:
	//長さを出す
	static float MakeLength(const MyVector2& v);
	static float MakeLength(const MyVector3& v);
	static float MakeLength(const MyVector2& v1, const MyVector2& v2);
	static float MakeLength(const MyVector3& v1, const MyVector3& v2);

	//点v1と線分v1v2の距離
	static float MakeLength(const MyVector2& v1, const MyVector2& v2, const MyVector2& v3);
	static float MakeLength(const MyVector3& v1, const MyVector3& v2, const MyVector3& v3);

	//点v1と線v1v2の距離
	static float MakeLength(const MyVector2& v1, const MyVector2& v2, const MyVector2& v3, LineType linetype);
	static float MakeLength(const MyVector3& v1, const MyVector3& v2, const MyVector3& v3, LineType linetype);

	static MyVector3 Project(const MyVector3& v1, const MyVector3& v2);
	static MyVector3 ClosestPoint(const MyVector3& point, const Segment& segment);

	//正規化
	static MyVector2 Normalize(const MyVector2& v);
	static MyVector3 Normalize(const MyVector3& v);

	//内積
	static float Dot(const MyVector2& v1, const MyVector2& v2);
	static float Dot(const MyVector3& v1, const MyVector3& v2);

	//外積
	static float Outer(const MyVector2& v1, const MyVector2& v2);

	//クロス積
	static MyVector3 Cross(const MyVector3& v1, const MyVector3& v2);
};

