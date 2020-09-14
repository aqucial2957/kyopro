/*
 * "幾何ライブラリ"
 * last revised on: 2020/03/05
 */
#include "../template.h"

constexpr double eps = 1e-8;
inline constexpr bool eq(double a, double b) { return fabs(a - b) < eps; }

//-----点-----//
struct Point
{
    double x, y;

    constexpr Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Point &operator+=(const Point &p) { x += p.x, y += p.y; return *this; }
    Point &operator-=(const Point &p) { x -= p.x, y -= p.y; return *this; }
    Point &operator*=(const double k) { x *= k, y *= k; return *this; }
    Point &operator/=(const double k) { x /= k, y /= k; return *this; }
};

inline Point operator+(const Point &p, const Point &q) { return Point(p) += q; }
inline Point operator-(const Point &p, const Point &q) { return Point(p) -= q; }
inline Point operator*(const Point &p, const double k) { return Point(p) *= k; }
inline Point operator/(const Point &p, const double k) { return Point(p) /= k; }

inline Point operator+(const Point &p) { return p; }
inline Point operator-(const Point &p) { return Point(-p.x, -p.y); }

inline constexpr bool operator==(const Point &p, const Point &q) { return eq(p.x, q.x) && eq(p.y, q.y); }
inline constexpr bool operator!=(const Point &p, const Point &q) { return !(p == q); }

inline double norm2(const Point &p) { return p.x * p.x + p.y * p.y; }
inline double norm(const Point &p) { return sqrt(p.x * p.x + p.y * p.y); }
inline double arg(const Point &p) { return atan2(p.y, p.x); }

/* 
 * "内積・外積"
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C
 */
inline double dot(const Point &p, const Point &q) { return p.x * q.x + p.y * q.y; }
inline double cross(const Point &p, const Point &q) { return p.x * q.y - p.y * q.x; }

istream &operator>>(istream &is, Point &p) { is >> p.x >> p.y; return is; }

//-----直線-----//
struct Line
{
    Point a, b;
    Line(Point a, Point b) : a(a), b(b) {} /* 2点a, bを通る直線 */
};

/* 
 * "射影" (直線 l に点 p から垂線を引いた交点を求める)
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A
 */
Point projection(const Line &l, const Point &p)
{
    Point d = l.b - l.a; // 直線 l の方向ベクトル
    Point h = d * (dot(p - l.a, d) / norm2(d)); // 正射影ベクトル
    return l.a + h;
}

/* 
 * "反射" (直線 l に関して点 p と対称な点を求める)
 * verified at: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_B
 */
Point reflection(const Line &l, const Point &p) { return p + (projection(l, p) - p) * 2.0; }
