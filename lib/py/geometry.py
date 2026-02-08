# CCW 
def ccw(p1, p2, p3):
    return (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0])

# Convex Hull (Monotone Chain)
def convex_hull(points):
    points = sorted(points) # (x, y) 튜플 기준 정렬
    if len(points) <= 2:
        return points
        
    lower = []
    for p in points:
        while len(lower) >= 2 and ccw(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)
        
    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and ccw(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)
        
    return lower[:-1] + upper[:-1]
