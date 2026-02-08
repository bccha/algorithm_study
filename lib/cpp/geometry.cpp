#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

// Point Structure
struct Point {
  long long x, y;
};

// CCW (Counter Clockwise)
// 양수: 반시계, 음수: 시계, 0: 일직선
long long ccw(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Convex Hull (Monotone Chain)
// 반환: 껍질을 구성하는 점들 (반시계 방향 정렬)
vector<Point> convexHank(vector<Point> &points) {
  int n = points.size();
  if (n <= 2)
    return points;

  // x좌표 오름차순 (같으면 y 오름차순) 정렬
  sort(points.begin(), points.end(),
       [](Point a, Point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });

  vector<Point> hull;

  // Lower Hull
  for (int i = 0; i < n; i++) {
    while (hull.size() >= 2 &&
           ccw(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }

  // Upper Hull
  int lower_size = hull.size();
  for (int i = n - 2; i >= 0; i--) {
    while (hull.size() > lower_size &&
           ccw(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }

  hull.pop_back(); // 시작점 중복 제거
  return hull;
}
