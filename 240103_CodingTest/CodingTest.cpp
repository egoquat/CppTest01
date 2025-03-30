

//#include <map>
//#include <type_traits>
//#include <utility>
//#include <iostream>
//#include <cassert>
//#include <random>
//
//template<typename K, typename V>
//class interval_map {
//    friend void IntervalMapTest();
//    V m_valBegin;
//    std::map<K,V> m_map;
//public:
//    // 생성자는 K의 전체 범위를 val로 연관시킵니다.
//    template<typename V_forward>
//    interval_map(V_forward&& val)
//    : m_valBegin(std::forward<V_forward>(val))
//    {}
//
//    // [keyBegin, keyEnd) 구간에 값 val을 할당합니다.
//    // 이 구간의 이전 값을 덮어씁니다.
//    template<typename V_forward>
//    void assign( K const& keyBegin, K const& keyEnd, V_forward&& val )
//        requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
//    {
//        if (!(keyBegin < keyEnd)) {
//            // 빈 구간이므로 아무것도 하지 않음
//            return;
//        }
//
//        // keyBegin과 keyEnd에 연관된 현재 값을 찾습니다.
//        const V& valBefore = operator[](keyBegin);
//        const V& valAfter = operator[](keyEnd);
//
//        // keyBegin과 keyEnd 사이의 항목을 삭제합니다.
//        auto itBegin = m_map.lower_bound(keyBegin);
//        auto itEnd = m_map.lower_bound(keyEnd);
//        m_map.erase(itBegin, itEnd);
//
//        // valBefore와 val이 다르면 (keyBegin, val)을 삽입합니다.
//        if (!(valBefore == val)) {
//            m_map.insert_or_assign(keyBegin, std::forward<V_forward>(val));
//        }
//
//        // val과 valAfter가 다르면 (keyEnd, valAfter)를 삽입합니다.
//        if (!(val == valAfter)) {
//            m_map.insert_or_assign(keyEnd, valAfter);
//        }
//    }
//
//    // key에 연관된 값을 조회합니다.
//    V const& operator[]( K const& key ) const {
//        auto it = m_map.upper_bound(key);
//        if(it == m_map.begin()) {
//            return m_valBegin;
//        } else {
//            return std::prev(it)->second;
//        }
//    }
//};
//
//// interval_map을 테스트하는 함수
//void main() {
//    // int를 키로, char를 값으로 사용하는 interval_map을 생성
//    interval_map<int, char> imap('A');
//
//    // 참조 구현을 위한 std::map
//    std::map<int, char> ref_map;
//
//    // 키의 범위 설정
//    const int MIN_KEY = -100;
//    const int MAX_KEY = 100;
//
//    // 랜덤 숫자 생성기 설정
//    std::mt19937 rng;
//    rng.seed(std::random_device{}());
//    std::uniform_int_distribution<int> dist_key(MIN_KEY, MAX_KEY);
//    std::uniform_int_distribution<int> dist_char(0, 25);
//
//    // 기본값 설정
//    char default_val = 'A';
//
//    // ref_map을 기본값으로 초기화
//    for (int k = MIN_KEY; k <= MAX_KEY; ++k) {
//        ref_map[k] = default_val;
//    }
//
//    // 테스트 반복 횟수
//    const int NUM_TESTS = 1000;
//
//    for (int i = 0; i < NUM_TESTS; ++i) {
//        // 랜덤한 keyBegin과 keyEnd 생성
//        int keyBegin = dist_key(rng);
//        int keyEnd = dist_key(rng);
//
//        if (keyEnd < keyBegin) std::swap(keyBegin, keyEnd);
//        else if (keyBegin == keyEnd) continue; // 빈 구간은 건너뜀
//
//        // 랜덤한 값 생성
//        char val = 'A' + dist_char(rng);
//
//        // interval_map에 할당
//        imap.assign(keyBegin, keyEnd, val);
//
//        // 참조 구현에 할당
//        for (int k = keyBegin; k < keyEnd; ++k) {
//            ref_map[k] = val;
//        }
//
//        // 검증
//        for (int k = MIN_KEY; k <= MAX_KEY; ++k) {
//            char expected = ref_map[k];
//            char actual = imap[k];
//            if (expected != actual) {
//                std::cerr << "불일치 발견! 키: " << k << ", 예상 값: " << expected << ", 실제 값: " << actual << std::endl;
//                assert(false);
//            }   
//        }
//    }
//
//    std::cout << "모든 테스트를 통과했습니다!" << std::endl;
//}



//#include <iostream>
//#include <map>
//#include <utility> // for std::forward
//
//template<typename K, typename V>
//class interval_map {
//    friend void IntervalMapTest();
//    
//    V m_valBegin; // 첫 번째 값보다 작은 모든 키에 할당된 기본 값
//    std::map<K, V> m_map; // 구간을 저장하는 std::map
//
//public:
//    // 생성자 - lvalue와 rvalue 모두를 처리할 수 있도록 템플릿 사용
//    template<typename V_forward>
//    interval_map(V_forward&& val)
//        : m_valBegin(std::forward<V_forward>(val)) // lvalue일 경우 복사, rvalue일 경우 이동
//    {}
//
//    // Assign value val to interval [keyBegin, keyEnd).
//    // Overwrite previous values in this interval.
//    // Conforming to the C++ Standard Library conventions, the interval
//    // includes keyBegin, but excludes keyEnd.
//    // If !( keyBegin < keyEnd ), this designates an empty interval,
//    // and assign must do nothing.
//
//    
//    template<typename V_forward>
//    void assign( K const& keyBegin, K const& keyEnd, V_forward&& val )
//        requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
//    {
//        // Case 1: If keyBegin is not less than keyEnd, do nothing (empty interval)
//        if (!(keyBegin < keyEnd)) {
//            return;
//        }
//
//        // Step 1: Find the first element that is greater than or equal to keyBegin
//        auto itBegin = m_map.lower_bound(keyBegin);
//    
//        // Step 2: Find the first element that is greater than or equal to keyEnd
//        auto itEnd = m_map.lower_bound(keyEnd);
//
//        // Step 3: Get the current value at keyBegin if keyBegin is outside m_map
//        V currentBeginValue = (itBegin != m_map.begin() ? std::prev(itBegin)->second : m_valBegin);
//    
//        // Step 4: Insert keyBegin with value val if necessary
//        if (currentBeginValue != val) {
//            itBegin = m_map.insert_or_assign(itBegin, keyBegin, std::forward<V_forward>(val));
//        }
//
//        // Step 5: Remove all elements strictly between keyBegin and keyEnd
//        m_map.erase(std::next(itBegin), itEnd);
//
//        // Step 6: Handle the case where keyEnd should restore the original value
//        V currentEndValue = (itEnd != m_map.end() ? itEnd->second : m_valBegin);
//        if (currentEndValue != val) {
//            m_map[keyEnd] = currentEndValue;
//        }
//    }
//
//    // look-up of the value associated with key
//    // 주어진 키에 연결된 값을 찾는 함수
//    V const& operator[]( K const& key ) const {
//        // upper_bound는 key보다 큰 첫 번째 원소를 찾음
//        auto it = m_map.upper_bound(key);
//        if (it == m_map.begin()) {
//            // map의 첫 번째 원소보다 작으면 m_valBegin 값 반환
//            return m_valBegin;
//        } else {
//            // 그렇지 않으면 바로 이전 원소의 값을 반환
//            return (--it)->second;
//        }
//    }
//
//    // 테스트용 출력 함수
//    void print() const {
//        std::cout << "m_valBegin: " << m_valBegin << std::endl;
//        for (const auto& pair : m_map) {
//            std::cout << pair.first << " -> " << pair.second << std::endl;
//        }
//    }
//};
//
//// Test example
//int main() {
//    interval_map<int, char> imap('A');
//    imap.assign(1, 5, 'B');
//    imap.assign(6, 10, 'C');
//
//    std::cout << "Interval Map Contents:\n";
//    imap.print();
//    
//    std::cout << "Lookup key 3: " << imap[3] << std::endl; // Should print 'B'
//    std::cout << "Lookup key 0: " << imap[0] << std::endl; // Should print 'A'
//    std::cout << "Lookup key 8: " << imap[8] << std::endl; // Should print 'C'
//
//    return 0;
//}







//#include "CodingTestBFS01.h"
//
//int main()
//{
//    vvecs dots = { {0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0}, {1, 1, 0, 0, 0, 1, 1, 0}, {1, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 1, 1} };
//    solution(dots);
//    std::cout << "Hello World!\n";
//}


// Online C++ compiler to run C++ program online
#include <iostream>
#define NONE -1

using namespace std;

template<typename type>
class FNode
{
public:
    type Value = NONE;
    FNode<type>* Next = nullptr;
    FNode<type>* Prev = nullptr;
    
    ~FNode()
    {
    }
    FNode(type value) : Value(value)
    {}
};

template<typename type>
class FList
{
public:
    FNode<type>* Head = nullptr;
    FNode<type>* Tail = nullptr;
    
public:
    void InsertToHead(int value)
    {
        FNode<type>* node = new FNode<type>(value);
        cout << "InsertToHead : " << value << endl;
        if (Head == nullptr)
        {
            Head = node;
            Tail = node;
        }
        else
        {
            FNode<type>* node01 = Head;
            Head = node;
            node->Prev = node01;
            node01->Next = Head;
        }
    }
    
    void InsertToTail(int value)
    {
        cout << "InsertToTail : " << value << endl;
        FNode<type>* node = new FNode<type>(value);
        if (Head == nullptr)
        {
            Head = node;
            Tail = node;
        }
        else
        {
            FNode<type>* node01 = Tail;
            Tail = node;
            node->Next = node01;
            node01->Prev = Tail;
        }
    }
    
    void RemoveHead()
    {
        if (Head == nullptr)
        {
            return;
        }
        
        cout << "RemoveHead:" << Head->Value << endl;
        FNode<type>* nodeToRemove = Head;
        Head = Head->Prev;
        delete nodeToRemove;
    }
    
    void RemoveTail()
    {
        if (Tail == nullptr)
        {
            return;
        }
        
        cout << "RemoveTail:" << Tail->Value << endl;
        FNode<type>* nodeToRemove = Tail;
        Tail = Tail->Next;
        delete nodeToRemove;
    }
    
    void IterationCheck()
    {
        FNode<type>* iter = Head;
        while(iter != nullptr)
        {
            cout << "IterationCheck()HeadToTail:Iter:" << iter->Value << endl;
            iter = iter->Prev;
        }
        
        iter = Tail;
        while(iter != nullptr)
        {
            cout << "IterationCheck()TailToHead:Iter:" << iter->Value << endl;
            iter = iter->Next;
        }
    }
    
    void RemoveAll()
    {
        FNode<type>* iter = Head;
        while(iter != nullptr)
        {
            cout << "RemoveAll():Iter:" << iter->Value << endl;
            FNode<type>* removeNode = iter;
            iter = iter->Prev;
            delete removeNode;
        }
        Head = nullptr;
        Tail = nullptr;
    }
};

#include <vector>

int main() {
    
    FList<uint32_t> list;
    vector<int> testvalues { 10, 4, 2, 8, 7 };
    for (int i = 0; i < testvalues.size(); ++i)
    {
        list.InsertToHead(testvalues[i]);
    }

    list.IterationCheck();
    list.RemoveAll();

    vector<int> testvalues2 { 103, 101, 108, 105, 104, 109 };
    for (int i = 0; i < testvalues2.size(); ++i)
    {
        list.InsertToTail(testvalues2[i]);
    }
    
    list.IterationCheck();
    list.RemoveAll();

    return 0;
}