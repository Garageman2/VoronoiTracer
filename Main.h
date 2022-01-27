#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>

using std::sqrt;

//setup
int ImageWidth = 256;
int ImageHeight = 256;

std::default_random_engine Rd(time(0));

class  Vec3
{
	public:
		Vec3() : e{0,0,0} {}
		Vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
		double operator[](int i) const { return e[i]; }
		double& operator[] (int i) { return e[i]; }

		Vec3& operator+=(const Vec3 &v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		Vec3& operator*=(const double t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		Vec3& operator/=(const double t)
		{
			return *this *= 1 / t;
		}
	
		double Length() const
		{
			return sqrt(LengthSquared());
		}

		double LengthSquared() const
		{
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}


		double e[3];
	
};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(Vec3 &v, double t)
{
	v.e[0] *= t;
	v.e[1] *= t;
	v.e[2] *= t;
	return(v);
}

inline Vec3 operator/(Vec3 v, double t)
{
	return v * (1 / t);
}

inline double dot(const Vec3& u, const Vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

void WriteColor(std::ostream &out, Color PixelColor)
{
	out << static_cast<int>(255.999 * PixelColor.x()) << ' '
		<< static_cast<int>(255.999 * PixelColor.y()) << ' '
		<< static_cast<int>(255.999 * PixelColor.z()) << '\n';
}

 double EucDistance(Vec3 A, Vec3 B)
{
	return sqrt(((B.x() - A.x()) * (B.x() - A.x())) + ((B.y() - A.y()) * (B.y() - A.y())));
}

double ManDistance(Vec3 A, Vec3 B)
{
	return(abs(B.x() - A.x()) + abs(B.y() - A.y()));
}


class Seed
{
	public:
		Seed(Vec3 Loc)
		{
			Location = Loc;
			std::uniform_real_distribution<double> LocDistro(0, 100);
			
			Color = Vec3(LocDistro(Rd)/100, LocDistro(Rd) / 100, LocDistro(Rd) / 100);
		}
	
	public:
		Vec3 Location;
		Vec3 Color;
	

};

template <typename T>
T Clamp(T Value, T Min, T Max)
{
	if (Min > Value) { return Min; }
	if (Max < Value) { return Max; }
	return Value;
}

template <typename T>
void ValidInput(std::string Printout, T &Input)
{
	for (;;)
	{
		std::cout << Printout << std::endl;
		if(std::cin>>Input)
		{
			break;
		}
		else
		{
			std::cout << "Please enter a valid value!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

void ManualSeeds(int &X, int &Y, const int &i)
{
	ValidInput(std::string("Enter an X Location for Seed ").append(std::to_string(i).c_str()), X);
	ValidInput(std::string("Enter a Y Location for Seed ").append(std::to_string(i).c_str()), Y);
}

void RandomSeeds(int &X, int &Y, const int &i)
{

	std::uniform_real_distribution<double> PosDistro(0, ImageHeight);

	X = Clamp(PosDistro(Rd),0.0,(double)ImageWidth);
	Y = Clamp(PosDistro(Rd), 0.0, (double)ImageHeight);
}