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
		//��ĸ�ֵ����һ�¾ͺã�
		Vec3f& operator= (const Vec3f& );
		Vec3f& operator+= (const Vec3f& );
		Vec3f& operator-= (const Vec3f& );
		Vec3f& operator*=(double val);  //x��y��z�ȱ����仯
		
		friend double operator* (const Vec3f& , const Vec3f& );//���������Ԫ�������ǲ����ܷ���xyz
		double getX() const;
		double getY() const;
		double getZ()const;
		void set(double x1, double y1, double z1);
		double length() const;
		Vec3f operator- ()const;   //ǰ׺��������ǰ����-����Ϊ�෴��  �������������0����Ϊ��׺
		Vec3f& normal();
};
const Vec3f operator+ (const Vec3f&, const Vec3f& );
const Vec3f operator- (const Vec3f&, const Vec3f& );
const Vec3f operator* (const Vec3f&, double );
#endif