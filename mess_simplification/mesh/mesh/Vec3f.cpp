#include "stdafx.h"
#include"Vec3f.h"

Vec3f::Vec3f()
{
			x = 0.0;
			y = 0.0;
			z = 0.0;
}
Vec3f::Vec3f(double x1, double y1, double z1)
{
			x=x1;
			y=y1;
			z=z1;
}
Vec3f::Vec3f(const Vec3f& vt)
{
			x = vt.x;
			y = vt.y;
			z = vt.z;
}
		//类的赋值重载一下就好！
Vec3f& Vec3f::operator= (const Vec3f& vt)
{
			x = vt.x;
			y = vt.y;
			z = vt.z;
			return *this;
}
Vec3f& Vec3f::operator+= (const Vec3f& vt)
{
			x += vt.x;
			y += vt.y;
			z += vt.z;
			return *this;
}
Vec3f& Vec3f::operator-= (const Vec3f& vt)
{
			x -= vt.x;
			y -= vt.y;
			z -= vt.z;
			return *this;
}
Vec3f Vec3f::operator- () const
{
			return Vec3f(-x, -y, -z);
}
Vec3f& Vec3f::operator *=(double val)  //x，y，z等比例变化
{
			x *= val;
			y *= val;
			z *= val;
			return *this;
}
const Vec3f operator+ (const Vec3f& vt1, const Vec3f& vt2)
{
			Vec3f orig(vt1);
			orig += vt2;
			return orig;
}
const Vec3f operator- (const Vec3f& vt1, const Vec3f& vt2)
{
			Vec3f orig(vt1);
			orig-=vt2;
			return orig;
}
const Vec3f operator* (const Vec3f& vt1, double val)
{
			Vec3f orig(vt1);
			orig*=val;
			return orig;
}
double operator* (const Vec3f& vt1, const Vec3f& vt2)
{
			return vt1.x * vt2.x + vt1.y * vt2.y + vt1.z * vt2.z;
}
double Vec3f::getX()const
{
			return x;
}
double Vec3f::getY()const
{
			return y;
}
double Vec3f::getZ()const
{
			return z;
}
void Vec3f::set(double x1, double y1, double z1)
{
		x = x1;
		y = y1;
		z = z1;
}
double Vec3f::length()const
{
	return sqrt(x*x+y*y+z*z);  //尽然忘记开根号啊啊啊啊调了好久的说！
}
Vec3f& Vec3f::normal()  //化为单位向量
{
	*this *=1/length();
	return *this;
}