# 스택, 큐, 덱 (Stack, Queue, Deque)

## 📌 개념
- **스택 (Stack)**: LIFO (Last In, First Out) - 마지막에 넣은 것이 먼저 나옴
  - 접시 쌓기, 브라우저 뒤로가기, 함수 호출 스택
- **큐 (Queue)**: FIFO (First In, First Out) - 먼저 넣은 것이 먼저 나옴
  - 줄서기, 프린터 대기열, BFS
- **덱 (Deque)**: 양쪽에서 삽입/삭제 가능
  - 슬라이딩 윈도우 최대/최소값

## 🎯 언제 사용하나?
| 상황 | 자료구조 |
|------|----------|
| 괄호/태그 매칭 | **Stack** |
| 최근 사용 항목 (Undo/Redo) | **Stack** |
| 순서대로 처리 (BFS, 작업 큐) | **Queue** |
| 슬라이딩 윈도우 최대/최소 | **Deque** (Monotonic) |
| 양쪽에서 삽입/삭제 | **Deque** |

### 문제에서 이렇게 나옵니다
- "괄호가 올바르게 짝지어졌는지" → Stack
- "가장 늦게 들어온 것부터" → Stack
- "먼저 들어온 순서대로" → Queue
- "N개 연속 구간에서 최댓값" → Monotonic Deque

## ⏱️ 시간복잡도
| 연산 | Stack | Queue | Deque |
|------|-------|-------|-------|
| push | O(1) | O(1) | O(1) |
| pop | O(1) | O(1) | O(1) |
| top/front | O(1) | O(1) | O(1) |

## 💻 C++ 코드
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 스택
    stack<int> st;
    st.push(1);
    st.push(2);
    cout << st.top() << endl;  // 2
    st.pop();
    
    // 큐
    queue<int> q;
    q.push(1);
    q.push(2);
    cout << q.front() << endl;  // 1
    q.pop();
    
    // 덱
    deque<int> dq;
    dq.push_front(1);
    dq.push_back(2);
    cout << dq.front() << " " << dq.back() << endl;  // 1 2
    
    return 0;
}
```

## 🐍 Python 코드
```python
from collections import deque

# 스택 (리스트로 구현)
stack = []
stack.append(1)
stack.append(2)
print(stack[-1])  # 2
stack.pop()

# 큐 (deque 사용 - 리스트의 pop(0)은 O(N)이므로 비추!)
queue = deque()
queue.append(1)
queue.append(2)
print(queue[0])  # 1
queue.popleft()

# 덱
dq = deque()
dq.appendleft(1)
dq.append(2)
print(dq[0], dq[-1])  # 1 2
```

## 🎯 핵심 응용
1. **괄호 매칭**: 여는 괄호 push, 닫는 괄호 만나면 pop하여 짝 확인
2. **역순 출력**: 스택에 넣고 전부 pop
3. **BFS**: 큐 사용 (다음 강의에서 다룸)
4. **슬라이딩 윈도우 최대/최소**: 모노톤 덱 (Monotonic Deque)

## 📖 외부 자료
- [C++ STL Container 레퍼런스](https://en.cppreference.com/w/cpp/container)
- [Python collections.deque](https://docs.python.org/3/library/collections.html#collections.deque)
- [VisuAlgo - Stack/Queue 시각화](https://visualgo.net/en/list)

## 📚 연습 문제
- [BOJ 10828 스택](https://www.acmicpc.net/problem/10828)
- [BOJ 10845 큐](https://www.acmicpc.net/problem/10845)
- [BOJ 10866 덱](https://www.acmicpc.net/problem/10866)
- [BOJ 9012 괄호](https://www.acmicpc.net/problem/9012) ⭐ 필수
- [BOJ 1874 스택 수열](https://www.acmicpc.net/problem/1874) ⭐ 필수
