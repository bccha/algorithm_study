# 계산 기하 (Computational Geometry)

## 1️⃣ CCW (Counter Clock Wise)
세 점의 방향 판별.

### 💡 CCW (Counter Clockwise)
세 점 A, B, C의 방향 관계 판별
- `(x2-x1)(y3-y1) - (y2-y1)(x3-x1)`
- **양수**: 반시계 방향 (좌회전)
- **음수**: 시계 방향 (우회전)
- **0**: 일직선

### 🎓 실전 팁
1. **오버플로우**: 좌표 곱셈 과정에서 `long long` 필수!
2. **선분 교차 판별**: `CCW(A,B,C)*CCW(A,B,D) <= 0` && `CCW(C,D,A)*CCW(C,D,B) <= 0`
   - 일직선 상에 있을 때 예외 처리 꼼꼼히!
3. **볼록 껍질(Convex Hull)**: 그라함 스캔 or 모노톤 체인 (정렬 기준 중요)
4. **다각형 넓이**: 신발끈 공식 (Shoelace Formula)
```cpp
struct Point { long long x, y; };

// 양수: 반시계, 음수: 시계, 0: 일직선
long long ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
```

---

## 2️⃣ 선분 교차 판정
```cpp
bool onSegment(Point p, Point q, Point r) {
    return min(p.x, r.x) <= q.x && q.x <= max(p.x, r.x) &&
           min(p.y, r.y) <= q.y && q.y <= max(p.y, r.y);
}

bool intersects(Point a, Point b, Point c, Point d) {
    long long d1 = ccw(a, b, c), d2 = ccw(a, b, d);
    long long d3 = ccw(c, d, a), d4 = ccw(c, d, b);
    
    if (((d1 > 0) != (d2 > 0)) && ((d3 > 0) != (d4 > 0)))
        return true;
    
    if (d1 == 0 && onSegment(a, c, b)) return true;
    if (d2 == 0 && onSegment(a, d, b)) return true;
    if (d3 == 0 && onSegment(c, a, d)) return true;
    if (d4 == 0 && onSegment(c, b, d)) return true;
    
    return false;
}
```

---

## 3️⃣ Convex Hull (볼록 껍질)
```cpp
vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    
    vector<Point> hull;
    
    // 하단 껍질
    for (auto& p : points) {
        while (hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }
    
    // 상단 껍질
    int lower = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower && ccw(hull[hull.size()-2], hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    hull.pop_back();
    
    return hull;
}
```

---

## 4️⃣ 다각형 넓이
```cpp
double polygonArea(vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y;
        area -= poly[j].x * poly[i].y;
    }
    return abs(area) / 2.0;
}
```

---

## 📚 연습 문제
- [BOJ 11758 CCW](https://www.acmicpc.net/problem/11758) ⭐⭐
- [BOJ 17387 선분 교차 2](https://www.acmicpc.net/problem/17387) ⭐⭐⭐
- [BOJ 1708 볼록 껍질](https://www.acmicpc.net/problem/1708) ⭐⭐⭐⭐
- [BOJ 2166 다각형의 면적](https://www.acmicpc.net/problem/2166) ⭐⭐
