# 투 포인터 (Two Pointers)

## 📌 개념
**두 개의 포인터**를 사용하여 배열을 효율적으로 탐색.
O(N²) → O(N) 최적화 가능.

## ⏱️ 시간복잡도: O(N)

---

## 1️⃣ 같은 방향 이동 (슬라이딩 윈도우)
```cpp
// 연속 부분 배열의 합이 S 이상인 최소 길이
int minLength(vector<int>& arr, int S) {
    int n = arr.size();
    int left = 0, sum = 0, ans = INF;
    
    for (int right = 0; right < n; right++) {
        sum += arr[right];
        
        while (sum >= S) {
            ans = min(ans, right - left + 1);
            sum -= arr[left++];
        }
    }
    return ans == INF ? 0 : ans;
}
```

---

## 2️⃣ 반대 방향 이동
```cpp
// 정렬된 배열에서 합이 X인 쌍 찾기
int twoSum(vector<int>& arr, int X) {
    int left = 0, right = arr.size() - 1;
    int count = 0;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == X) {
            count++;
            left++;
            right--;
        }
        else if (sum < X) left++;
        else right--;
    }
    return count;
}
```

---

## 3️⃣ 세 수의 합 (3Sum)
```cpp
// 정렬 + 투 포인터
vector<vector<int>> threeSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    
    for (int i = 0; i < nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;  // 중복 스킵
        
        int left = i + 1, right = nums.size() - 1;
        int want = target - nums[i];
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == want) {
                result.push_back({nums[i], nums[left], nums[right]});
                left++; right--;
                while (left < right && nums[left] == nums[left-1]) left++;
            }
            else if (sum < want) left++;
            else right--;
        }
    }
    return result;
}
```

---

## 🐍 Python
```python
# 연속 부분합이 S 이상인 최소 길이
def min_length(arr, S):
    left = 0
    total = 0
    ans = float('inf')
    
    for right in range(len(arr)):
        total += arr[right]
        
        while total >= S:
            ans = min(ans, right - left + 1)
            total -= arr[left]
            left += 1
    
    return 0 if ans == float('inf') else ans
```

---

## 📖 외부 자료
- [Two Pointers - GeeksforGeeks](https://www.geeksforgeeks.org/two-pointers-technique/)
- [투 포인터 테크닉](https://blog.encrypted.gg/1004)

## 📚 연습 문제
- [BOJ 2003 수들의 합 2](https://www.acmicpc.net/problem/2003) ⭐ 기본
- [BOJ 1806 부분합](https://www.acmicpc.net/problem/1806) ⭐⭐
- [BOJ 2470 두 용액](https://www.acmicpc.net/problem/2470) ⭐⭐ 반대 방향
- [BOJ 1644 소수의 연속합](https://www.acmicpc.net/problem/1644) ⭐⭐
- [BOJ 2473 세 용액](https://www.acmicpc.net/problem/2473) ⭐⭐⭐
