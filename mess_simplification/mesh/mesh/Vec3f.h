#ifndef VEC3F_H
#define VEC3F_H
#include<cmath>

class Vec3f
{
	private:
		double x;
		double y;
		double z;
	public:
		Vec3f();
		Vec3f(double x1, double y1, double z1);
		Vec3f(const Vec3f&);
		//类的赋值重载一下就好！
		Vec3f& operator= (const Vec3f& );
		Vec3f& operator+= (const Vec3f& );
		Vec3f& operator-= (const Vec3f& );
		Vec3f& operator*=(double val);  //x，y，z等比例变化
		
		friend double operator* (const Vec3f& , const Vec3f& );//不设成由友元函数，是不可能访问xyz
		double getX() const;
		double getY() const;
		double getZ()const;
		void set(double x1, double y1, double z1);
		double length() const;
		Vec3f operator- ()const;   //前缀，当此类前面有-，变为相反数  如果括号里面是0，即为后缀
		Vec3f& normal();
};
const Vec3f operator+ (const Vec3f&, const Vec3f& );
const Vec3f operator- (const Vec3f&, const Vec3f& );
const Vec3f operator* (const Vec3f&, double );
#endif