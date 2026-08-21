#pragma once

// --- Standard I/O & Streams ---
#include <iostream>
#include <iomanip>
#include <fstream>

// --- Data Structures & Containers ---
#include <vector>
#include <string>
#include <string_view>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <bitset>
#include <tuple>

// --- Algorithms & Mathematics ---
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>

// --- C-Style Utilities & String Operations ---
#include <cctype>
#include <cstring>
#include <cassert>
#include <cstdint>

// --- System, Memory & Functional ---
#include <utility>
#include <chrono>
#include <random>
#include <functional>
#include <memory>
#include <type_traits>
#include <concepts>

// 1. Types and basic definitions

using namespace std;

using ll = long long;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// 2. Group abbreviations based on previous definitions

typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<short> vs;
typedef vector<double> vd;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef set<int> si;
typedef map<int, int> mii;

// 3. Macros and Loops

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define nl '\n'
#define for_n(i, n) for (int i = 0; i < (int)(n); ++i)
#define for_e(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define r_for_n(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define r_for_e(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define each(x, a) for (auto &x : (a))
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);


// --- C++23 Modern Headers ---
#if __has_include(<print>)
#include <print>
#endif

#if __has_include(<expected>)
#include <expected>
#endif

#if __has_include(<mdspan>)
#include <mdspan>
#endif

#if __has_include(<flat_map>)
#include <flat_map>
#include <flat_set>
#endif

#include <optional>

// --- GNU PBDS Support (For Competitive Programming) ---
#if defined(__GNUC__) && __has_include(<ext/pb_ds/assoc_container.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#endif


// ============================================================================
// 1. CORE MODULE (Types, Concepts, Error Handling)
// ============================================================================

using i64 = std::int64_t;
using u64 = std::uint64_t;
using f64 = double;

// Mathematical Constants
constexpr f64 PI_VAL  = 3.14159265358979323846;
constexpr f64 EPS_VAL = 1e-9;
constexpr i64 INF_I64 = 1e18 + 7;
constexpr int INF_I32 = 1e9 + 7;

// Concepts with Backward-Compatibility Layer
#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
template<typename T> concept Numeric = std::is_arithmetic_v<T>;
template<typename T> concept FloatingPoint = std::is_floating_point_v<T>;
template<typename T> concept Integral = std::is_integral_v<T>;
#else
template<typename T> inline constexpr bool Numeric = std::is_arithmetic_v<T>;
template<typename T> inline constexpr bool FloatingPoint = std::is_floating_point_v<T>;
template<typename T> inline constexpr bool Integral = std::is_integral_v<T>;
#endif

// Framework Errors
enum class FrameworkError {
    OutOfBounds,
    PoolExhausted,
    InvalidOperation,
    MathDomainError
};

#if defined(__cpp_lib_expected)
template<typename T>
using Result = std::expected<T, FrameworkError>;
#endif


// ============================================================================
// 2. MATHEMATICS MODULE (2D/3D Vectors, Quaternions, Spatial Geometry)
// ============================================================================

template<typename T = f64>
struct Vec2 {
    T x{0}, y{0};

    constexpr Vec2() = default;
    constexpr Vec2(T _x, T _y) : x(_x), y(_y) {}

    constexpr Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
    constexpr Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
    constexpr Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }
    
    constexpr T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
    constexpr T cross(const Vec2& rhs) const { return x * rhs.y - y * rhs.x; }
    
    f64 length() const { return std::sqrt(static_cast<f64>(dot(*this))); }
    Vec2 normalized() const {
        f64 len = length();
        return len > 0 ? Vec2(static_cast<T>(x / len), static_cast<T>(y / len)) : Vec2();
    }
};

template<typename T = f64>
struct Vec3 {
    T x{0}, y{0}, z{0};

    constexpr Vec3() = default;
    constexpr Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    constexpr Vec3 operator+(const Vec3& rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    constexpr Vec3 operator-(const Vec3& rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
    constexpr Vec3 operator*(T scalar) const { return Vec3(x * scalar, y * scalar); }

    constexpr T dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    constexpr Vec3 cross(const Vec3& rhs) const {
        return Vec3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

    f64 length() const { return std::sqrt(static_cast<f64>(dot(*this))); }
    Vec3 normalized() const {
        f64 len = length();
        return len > 0 ? Vec3(static_cast<T>(x / len), static_cast<T>(y / len), static_cast<T>(z / len)) : Vec3();
    }

#if defined(__cpp_explicit_this_parameter)
    template<typename Self>
    constexpr auto&& getComponent(this Self&& self, std::size_t index) {
        if (index == 0) return std::forward<Self>(self).x;
        if (index == 1) return std::forward<Self>(self).y;
        if (index == 2) return std::forward<Self>(self).z;
        std::unreachable();
    }
#endif
};

struct Quaternion {
    f64 w{1.0}, x{0.0}, y{0.0}, z{0.0};

    constexpr Quaternion() = default;
    constexpr Quaternion(f64 _w, f64 _x, f64 _y, f64 _z) : w(_w), x(_x), y(_y), z(_z) {}

    Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }
};

struct AABB {
    Vec3<f64> min_pt;
    Vec3<f64> max_pt;

    constexpr AABB(const Vec3<f64>& min_b, const Vec3<f64>& max_b) : min_pt(min_b), max_pt(max_b) {}

    constexpr bool intersects(const AABB& other) const {
        return (min_pt.x <= other.max_pt.x && max_pt.x >= other.min_pt.x) &&
               (min_pt.y <= other.max_pt.y && max_pt.y >= other.min_pt.y) &&
               (min_pt.z <= other.max_pt.z && max_pt.z >= other.min_pt.z);
    }
};


// ============================================================================
// 3. MEMORY MANAGEMENT MODULE (Object Pool)
// ============================================================================

template<typename T, std::size_t Size>
class ObjectPool {
private:
    alignas(T) std::array<std::byte, sizeof(T) * Size> storage;
    std::array<T*, Size> free_list{};
    std::size_t free_top{Size};

public:
    ObjectPool() {
        T* ptr = reinterpret_cast<T*>(storage.data());
        for (std::size_t i = 0; i < Size; ++i) {
            free_list[i] = ptr + i;
        }
    }

    template<typename... Args>
    T* acquire(Args&&... args) {
        if (free_top == 0) return nullptr;
        T* ptr = free_list[--free_top];
        ::new (static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
        return ptr;
    }

    void release(T* ptr) {
        if (!ptr) return;
        ptr->~T();
        free_list[free_top++] = ptr;
    }
};


// ============================================================================
// 4. DATA STRUCTURES MODULE (DSU, Fenwick, Segment Tree, etc.)
// ============================================================================

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> size_tree;

public:
    explicit DSU(int n) : parent(n + 1), size_tree(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (size_tree[root_i] < size_tree[root_j]) std::swap(root_i, root_j);
            parent[root_j] = root_i;
            size_tree[root_i] += size_tree[root_j];
            return true;
        }
        return false;
    }

    int getSize(int i) { return size_tree[find(i)]; }
};

template<typename T = i64>
class FenwickTree {
private:
    int n;
    std::vector<T> tree;

public:
    explicit FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void add(int i, T delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }

    T query(int i) const {
        T sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }

    T queryRange(int l, int r) const { return query(r) - query(l - 1); }
};

class SegmentTree {
private:
    int n;
    std::vector<i64> tree;

public:
    explicit SegmentTree(int size) : n(size), tree(4 * size, 0) {}

    void update(int node, int start, int end, int idx, i64 val) {
        if (start == end) {
            tree[node] += val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val);
        else update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    i64 query(int node, int start, int end, int l, int r) const {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = start + (end - start) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }
};

// Coordinate Compression
template<typename T>
void coordinate_compress(std::vector<T>& v) {
    std::vector<T> temp = v;
    std::sort(temp.begin(), temp.end());
    temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
    for (auto& x : v) {
        x = std::lower_bound(temp.begin(), temp.end(), x) - temp.begin();
    }
}

// Sparse Table
template<typename T, class F = std::function<T(T, T)>>
class SparseTable {
private:
    int n;
    int logN;
    std::vector<std::vector<T>> st;
    F func;

public:
    SparseTable(const std::vector<T>& a, F f) : func(f) {
        n = a.size();
        logN = std::log2(n) + 1;
        st.assign(logN, std::vector<T>(n));
        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        for (int j = 1; j < logN; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = func(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) const {
        int j = std::log2(r - l + 1);
        return func(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

// Trie & Bitwise Trie
class Trie {
private:
    struct Node {
        Node* children[26];
        int count{0};
        Node() {
            for (int i = 0; i < 26; ++i) children[i] = nullptr;
        }
    };
    Node* root;

public:
    Trie() { root = new Node(); }

    void insert(const std::string& s) {
        Node* curr = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!curr->children[idx]) curr->children[idx] = new Node();
            curr = curr->children[idx];
            curr->count++;
        }
    }

    int countPrefix(const std::string& prefix) const {
        Node* curr = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) return 0;
            curr = curr->children[idx];
        }
        return curr->count;
    }
};

class BitwiseTrie {
private:
    struct Node {
        Node* children[2] = {nullptr, nullptr};
        int cnt = 0;
    };
    Node* root;

public:
    BitwiseTrie() { root = new Node(); }

    void insert(int val) {
        Node* curr = root;
        for (int i = 29; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (!curr->children[bit]) curr->children[bit] = new Node();
            curr = curr->children[bit];
            curr->cnt++;
        }
    }

    void remove(int val) {
        Node* curr = root;
        for (int i = 29; i >= 0; --i) {
            int bit = (val >> i) & 1;
            curr = curr->children[bit];
            curr->cnt--;
        }
    }

    int getMaxXor(int val) const {
        Node* curr = root;
        int res = 0;
        for (int i = 29; i >= 0; --i) {
            int bit = (val >> i) & 1;
            int target = 1 - bit;
            if (curr->children[target] && curr->children[target]->cnt > 0) {
                res |= (1 << i);
                curr = curr->children[target];
            } else {
                curr = curr->children[bit];
            }
        }
        return res;
    }
};

// Policy-Based Data Structures (Ordered Set Integration)
#if defined(__GNUC__) && __has_include(<ext/pb_ds/assoc_container.hpp>)
template<typename T>
using ordered_set = __gnu_pbds::tree<
    T, 
    __gnu_pbds::null_type, 
    std::less<T>, 
    __gnu_pbds::rb_tree_tag, 
    __gnu_pbds::tree_order_statistics_node_update
>;
#endif

// Lazy Propagation Segment Tree
class LazySegmentTree {
private:
    int n;
    std::vector<i64> tree;
    std::vector<i64> lazy;

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            int mid = start + (end - start) / 2;
            tree[2 * node] += lazy[node] * (mid - start + 1);
            lazy[2 * node] += lazy[node];
            tree[2 * node + 1] += lazy[node] * (end - mid);
            lazy[2 * node + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, i64 val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] += val * (end - start + 1);
            lazy[node] += val;
            return;
        }
        push(node, start, end);
        int mid = start + (end - start) / 2;
        updateRange(2 * node, start, mid, l, r, val);
        updateRange(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    i64 queryRange(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        push(node, start, end);
        int mid = start + (end - start) / 2;
        return queryRange(2 * node, start, mid, l, r) + queryRange(2 * node + 1, mid + 1, end, l, r);
    }

public:
    explicit LazySegmentTree(int size) : n(size), tree(4 * size, 0), lazy(4 * size, 0) {}

    void update(int l, int r, i64 val) {
        updateRange(1, 0, n - 1, l, r, val);
    }

    i64 query(int l, int r) {
        return queryRange(1, 0, n - 1, l, r);
    }
};


// ============================================================================
// 5. STRING UTILITIES MODULE (clsString_Methods)
// ============================================================================

class clsString_Methods 
{
private:
    string _Value;

public:
    clsString_Methods() { _Value = ""; }
    clsString_Methods(string Value) { _Value = Value; }

    void SetValue(string Value) { _Value = Value; }
    string GetValue() { return _Value; }

    #ifdef _MSC_VER
    __declspec(property(get = GetValue, put = SetValue)) string Value;
    #endif

    static short CountWords(string S1) {
        string delim = " ";  
        short Counter = 0;
        short pos = 0;
        string sWord;  

        while ((pos = S1.find(delim)) != std::string::npos) {
            sWord = S1.substr(0, pos);  
            if (sWord != "") Counter++;
            S1.erase(0, pos + delim.length());
        }
        if (S1 != "") Counter++; 
        return Counter;
    }

    short CountWords() { return CountWords(_Value); }

    static void print_first_Letter(const string S1) {
        bool isFirstLetter = true;
        cout << "\nFirst letters of this string: \n";
        for (short i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ' && isFirstLetter) {
                cout << S1[i] << endl;
            }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
    }  

    void print_first_Letter() { print_first_Letter(_Value); }

    static void print_Upper(string &S1) {
        for (short i = 0; i < S1.length(); i++) S1[i] = toupper(S1[i]);
        cout << S1;
    }

    void print_Upper() { print_Upper(_Value); }

    static void print_Lower(string &S1) {
        for (short i = 0; i < S1.length(); i++) S1[i] = tolower(S1[i]);
        cout << S1;
    }

    void print_Lower() { print_Lower(_Value); }

    static char InvertLetterCase(char char1) {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static string InvertAllStringLettersCase(string S1) {
        for (short i = 0; i < S1.length(); i++) S1[i] = InvertLetterCase(S1[i]);
        return S1;
    }

    void InvertAllStringLettersCase() { cout << InvertAllStringLettersCase(_Value); }

    static short CountCapitalLetters(string S1) {
        short Counter = 0;
        for (short i = 0; i < S1.length(); i++) if (isupper(S1[i])) Counter++;
        return Counter;
    }

    short CountCapitalLetters() { return CountCapitalLetters(_Value); }

    static short CountSmallLetters(string S1) {
        short Counter = 0;
        for (short i = 0; i < S1.length(); i++) if (islower(S1[i])) Counter++;
        return Counter;
    }

    short CountSmallLetters() { return CountSmallLetters(_Value); }

    static char ReadChar() { char Ch1; cin >> Ch1; return Ch1; }

    static short CountLetter(string S1, char Letter) {
        short Counter = 0;
        for (short i = 0; i < S1.length(); i++) if (S1[i] == Letter) Counter++;
        return Counter;
    }

    short CountLetter() { return CountLetter(_Value, ReadChar()); }

    static bool IS_vowel(char c) {
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    }

    static void Print_Vowel(string S) {
        for (int i = 0; i < S.length(); i++) {
            if (IS_vowel(S[i])) cout << S[i] << " ";
        }
    }

    void Print_Vowel() { Print_Vowel(_Value); }

    static void PrintEachWordInString(string S1) {
        string delim = " ";
        cout << "\nYour string words are: \n\n";
        short pos = 0;
        string sWord;

        while ((pos = S1.find(delim)) != std::string::npos) {
            sWord = S1.substr(0, pos);
            if (sWord != "") cout << sWord << endl;
            S1.erase(0, pos + delim.length());
        }
        if (S1 != "") cout << S1 << endl; 
    }

    void PrintEachWordInString() { PrintEachWordInString(_Value); }

    static vector<string> Split_String(string S1, string Delim) {
        vector<string> vString;
        short pos = 0;
        string sWord;
        while ((pos = S1.find(Delim)) != std::string::npos) {
            sWord = S1.substr(0, pos);
            if (sWord != "") vString.push_back(sWord);
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "") vString.push_back(S1);
        return vString;
    }

    static string JoinString(vector<string> vString, string Delim) {
        string S1 = "";
        for (string& s : vString) S1 = S1 + s + Delim;
        return S1.substr(0, S1.length() - Delim.length());
    }

    static string ReverseWordsInString(string S1) {
        vector<string> vString = Split_String(S1, " ");
        string S2 = "";
        auto iter = vString.end();
        while (iter != vString.begin()) {
            --iter;
            S2 += *iter + " ";
        }
        S2 = S2.substr(0, S2.length() - 1);
        return S2;
    }

    static string Replace_Word_In_String(string S1, string StringToReplace, string sReplaceTo) {
        short pos = S1.find(StringToReplace);
        while (pos != std::string::npos) {
            S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
            pos = S1.find(StringToReplace);
        }
        return S1;
    }

    string Replace_Word_In_String() {
        string StringToReplace, sReplaceTo;
        getline(cin, StringToReplace);
        getline(cin, sReplaceTo);
        return Replace_Word_In_String(_Value, StringToReplace, sReplaceTo);
    }

    static string RemovePunctuationsFromString(string S1) {
        string S2 = "";
        for (short i = 0; i < S1.length(); i++) {
            if (!ispunct(S1[i])) S2 += S1[i];
        }
        return S2;
    }

    string RemovePunctuationsFromString() { return RemovePunctuationsFromString(_Value); }

    static bool IsPalindrome(string S1) {
        int n = S1.length();
        for (int i = 0; i < n / 2; i++) {
            if (S1[i] != S1[n - i - 1]) return false;
        }
        return true;
    }

    bool IsPalindrome() { return IsPalindrome(_Value); }

    static string TrimLeft(string S1) {
        size_t start = S1.find_first_not_of(" \t\n\r");
        return (start == string::npos) ? "" : S1.substr(start);
    }

    static string TrimRight(string S1) {
        size_t end = S1.find_last_not_of(" \t\n\r");
        return (end == string::npos) ? "" : S1.substr(0, end + 1);
    }

    static string Trim(string S1) { return TrimLeft(TrimRight(S1)); }

    static bool StartsWith(string S1, string Sub) {
        if (Sub.length() > S1.length()) return false;
        return S1.compare(0, Sub.length(), Sub) == 0;
    }

    static bool EndsWith(string S1, string Sub) {
        if (Sub.length() > S1.length()) return false;
        return S1.compare(S1.length() - Sub.length(), Sub.length(), Sub) == 0;
    }

    static bool IsNumeric(string S1) {
        if (S1.empty()) return false;
        for (char c : S1) if (!isdigit(c)) return false;
        return true;
    }

    static string SortString(string S1) { sort(S1.begin(), S1.end()); return S1; }
    string SortString() { return SortString(_Value); }

    static bool AreAnagrams(string S1, string S2) {
        if (S1.length() != S2.length()) return false;
        sort(S1.begin(), S1.end());
        sort(S2.begin(), S2.end());
        return S1 == S2;
    }

    static vector<int> FindAllOccurrences(string S1, string Sub) {
        vector<int> indices;
        if (Sub.empty()) return indices;
        size_t pos = S1.find(Sub);
        while (pos != string::npos) {
            indices.push_back(pos);
            pos = S1.find(Sub, pos + 1);
        }
        return indices;
    }

    static bool IsAlpha(string S1) {
        if (S1.empty()) return false;
        for (char c : S1) if (!isalpha(c)) return false;
        return true;
    }

    static string RemoveChar(string S1, char Target) {
        string result = "";
        for (char c : S1) if (c != Target) result += c;
        return result;
    }

    string RemoveChar(char Target) { return RemoveChar(_Value, Target); }

    static string ToUpper(string S1) {
        for (short i = 0; i < S1.length(); i++) S1[i] = toupper(S1[i]);
        return S1;
    }
    string ToUpper() { return ToUpper(_Value); }

    static string ToLower(string S1) {
        for (short i = 0; i < S1.length(); i++) S1[i] = tolower(S1[i]);
        return S1;
    }
    string ToLower() { return ToLower(_Value); }

    static string ReverseString(string S1) {
        string S2 = "";
        for (int i = S1.length() - 1; i >= 0; i--) S2 += S1[i];
        return S2;
    }
    string ReverseString() { return ReverseString(_Value); }

    static short CountSubstring(string S1, string Sub) {
        short counter = 0;
        size_t pos = S1.find(Sub);
        while (pos != string::npos) {
            counter++;
            pos = S1.find(Sub, pos + Sub.length());
        }
        return counter;
    }

    static string RemoveExtraSpaces(string S1) {
        string result = "";
        bool inSpace = false;
        for (char c : S1) {
            if (isspace(c)) {
                if (!inSpace) { result += ' '; inSpace = true; }
            } else {
                result += c;
                inSpace = false;
            }
        }
        return Trim(result);
    }

    static vector<long long> ExtractNumbers(string S1) {
        vector<long long> numbers;
        string currentNum = "";
        for (char c : S1) {
            if (isdigit(c)) {
                currentNum += c;
            } else {
                if (!currentNum.empty()) {
                    numbers.push_back(stoll(currentNum));
                    currentNum = "";
                }
            }
        }
        if (!currentNum.empty()) numbers.push_back(stoll(currentNum));
        return numbers;
    }

    static string CaesarCipher(string S1, short Shift) {
        for (short i = 0; i < S1.length(); i++) {
            if (isalpha(S1[i])) {
                char base = islower(S1[i]) ? 'a' : 'A';
                S1[i] = (char)(base + (S1[i] - base + (Shift % 26 + 26)) % 26);
            }
        }
        return S1;
    }

    string CaesarCipher(short Shift) { return CaesarCipher(_Value, Shift); }
};


// ============================================================================
// 6. COMPETITIVE PROGRAMMING MODULE (Fast IO, Debugger)
// ============================================================================

struct FastIO {
    FastIO() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    template<typename T>
    static void print(const T& val) {
        std::cout << val << "\n";
    }
};

#ifndef ONLINE_JUDGE
#define FW_DEBUG(x) std::cerr << "[DEBUG] " << #x << " = " << (x) << std::endl;
#else
#define FW_DEBUG(x)
#endif


// ============================================================================
// 7. GAME UTILITIES MODULE (Timers, RNG)
// ============================================================================

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;

public:
    Timer() { reset(); }
    void reset() { start_time = std::chrono::high_resolution_clock::now(); }

    f64 elapsedMs() const {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<f64, std::milli>(now - start_time).count();
    }
};

class FastRNG {
private:
    std::mt19937_64 rng;

public:
    explicit FastRNG(u64 seed = std::chrono::steady_clock::now().time_since_epoch().count())
        : rng(seed) {}

    i64 nextInt(i64 min_val, i64 max_val) {
        std::uniform_int_distribution<i64> dist(min_val, max_val);
        return dist(rng);
    }
};


// ============================================================================
// 8. UNREAL ENGINE INTEGRATION LAYER
// ============================================================================

namespace Integration::Unreal {
template<typename UEVectorType>
constexpr Vec3<f64> FromUEVector(const UEVectorType& ue_vec) {
    return Vec3<f64>(static_cast<f64>(ue_vec.X), static_cast<f64>(ue_vec.Y), static_cast<f64>(ue_vec.Z));
}
} // namespace Integration::Unreal


// ============================================================================
// 9. ADVANCED COMPETITIVE MATHEMATICS (MathUtils)
// ============================================================================

class MathUtils {
private:
    static constexpr unsigned long long safe_mul(unsigned long long a, unsigned long long b, unsigned long long mod) {
        unsigned long long result = 0;
        a %= mod;
        while (b != 0) {
            if (b & 1) {
                result = (result >= mod - a) ? result - (mod - a) : result + a;
            }
            a = (a >= mod - a) ? a - (mod - a) : a + a;
            b >>= 1;
        }
        return result;
    }

    static long long mul_mod(long long a, long long b, long long mod) {
        return (long long)safe_mul((unsigned long long)a, (unsigned long long)b, (unsigned long long)mod);
    }

    static long long mod_inverse_internal(long long a, long long m) {
        long long x0 = 1, x1 = 0, temp_m = m;
        while (m != 0) {
            long long q = a / m;
            a %= m;
            std::swap(a, m);
            long long nx = x0 - q * x1;
            x0 = x1;
            x1 = nx;
        }
        return (x0 % temp_m + temp_m) % temp_m;
    }

    static void factorize_recursive(long long n, std::vector<long long>& factors) {
        if (n == 1) return;
        if (is_prime(n)) {
            factors.push_back(n);
            return;
        }
        if (n % 2 == 0) { factors.push_back(2); factorize_recursive(n / 2, factors); return; }
        if (n % 3 == 0) { factors.push_back(3); factorize_recursive(n / 3, factors); return; }
        
        auto pollard_rho = [](long long n) {
            if (n % 2 == 0) return 2LL;
            long long x = 2, y = 2, d = 1, c = 1;
            auto f = [&](long long x_val, long long n_val, long long c_val) {
                return (mul_mod(x_val, x_val, n_val) + c_val) % n_val;
            };
            while (d == 1) {
                x = f(x, n, c);
                y = f(f(y, n, c), n, c);
                long long diff = x > y ? x - y : y - x;
                d = gcd(diff, n);
                if (d == n) {
                    x = rand() % (n - 2) + 2;
                    y = x;
                    c = rand() % (n - 1) + 1;
                    d = 1;
                }
            }
            return d;
        };

        long long divisor = pollard_rho(n);
        factorize_recursive(divisor, factors);
        factorize_recursive(n / divisor, factors);
    }

public:
    struct EGCDResult {
        long long gcd;
        long long x;
        long long y;
    };

    static long long gcd(long long a, long long b) {
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        return a < 0 ? -a : a;
    }

    static long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    static EGCDResult extgcd(long long a, long long b) {
        long long x0 = 1, y0 = 0, x1 = 0, y1 = 1;
        long long sign_a = (a < 0) ? -1 : 1;
        long long sign_b = (b < 0) ? -1 : 1;
        a = a < 0 ? -a : a;
        b = b < 0 ? -b : b;
        while (b != 0) {
            long long q = a / b;
            a %= b;
            std::swap(a, b);
            long long nx = x0 - q * x1;
            long long ny = y0 - q * y1;
            x0 = x1; y0 = y1;
            x1 = nx; y1 = ny;
        }
        x0 *= sign_a;
        y0 *= sign_b;
        return {a, x0, y0};
    }

    static long long mod_normalize(long long x, long long mod) {
        if (mod <= 0) return 0;
        x %= mod;
        if (x < 0) x += mod;
        return x;
    }

    static long long mod_add(long long a, long long b, long long mod) {
        return (mod_normalize(a, mod) + mod_normalize(b, mod)) % mod;
    }

    static long long mod_sub(long long a, long long b, long long mod) {
        return (mod_normalize(a, mod) - mod_normalize(b, mod) + mod) % mod;
    }

    static long long mod_mul(long long a, long long b, long long mod) {
        a = mod_normalize(a, mod);
        b = mod_normalize(b, mod);
        return (long long)(((unsigned long long)a * b) % mod);
    }

    static long long mod_pow(long long base, long long exponent, long long mod) {
        if (mod <= 0) return 0;
        if (mod == 1) return 0;
        base = mod_normalize(base, mod);
        long long res = 1;
        long long b = base;
        unsigned long long exp = exponent;
        while (exp > 0) {
            if (exp & 1) res = mod_mul(res, b, mod);
            b = mod_mul(b, b, mod);
            exp >>= 1;
        }
        return res;
    }

    static std::optional<long long> mod_inverse(long long a, long long mod) {
        if (mod <= 0) return std::nullopt;
        EGCDResult res = extgcd(a, mod);
        if (res.gcd != 1) return std::nullopt;
        return mod_normalize(res.x, mod);
    }

    static bool is_prime(long long n) {
        if (n < 2) return false;
        if (n == 2 || n == 3 || n == 5 || n == 7) return true;
        if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
        
        auto check_composite = [](long long n, long long a, long long d, int s) {
            long long x = mod_pow(a, d, n);
            if (x == 1 || x == n - 1) return false;
            for (int r = 1; r < s; r++) {
                x = mul_mod(x, x, n);
                if (x == n - 1) return false;
            }
            return true;
        };

        long long d = n - 1;
        int s = 0;
        while (!(d & 1)) {
            d >>= 1;
            s++;
        }

        long long bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        for (long long a : bases) {
            if (a % n == 0) continue;
            if (check_composite(n, a, d, s)) return false;
        }
        return true;
    }

    static std::vector<bool> sieve(int n) {
        std::vector<bool> is_p(n + 1, true);
        if (n >= 0) is_p[0] = false;
        if (n >= 1) is_p[1] = false;
        for (int p = 2; p * p <= n; p++) {
            if (is_p[p]) {
                for (int i = p * p; i <= n; i += p)
                    is_p[i] = false;
            }
        }
        return is_p;
    }

    static std::vector<int> spf_sieve(int n) {
        std::vector<int> spf(n + 1);
        for (int i = 0; i <= n; i++) spf[i] = i;
        for (int i = 2; i * i <= n; i++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= n; j += i) {
                    if (spf[j] == j) spf[j] = i;
                }
            }
        }
        return spf;
    }

    static std::vector<std::pair<long long, int>> factorize(long long n) {
        if (n <= 0 || n == 1) return {};
        std::vector<long long> raw_factors;
        factorize_recursive(n, raw_factors);
        std::sort(raw_factors.begin(), raw_factors.end());
        std::vector<std::pair<long long, int>> result;
        for (long long p : raw_factors) {
            if (!result.empty() && result.back().first == p) {
                result.back().second++;
            } else {
                result.push_back({p, 1});
            }
        }
        return result;
    }

    static long long phi(long long n) {
        if (n <= 0) return 0;
        long long result = n;
        auto facts = factorize(n);
        for (auto& f : facts) {
            result -= result / f.first;
        }
        return result;
    }

    static std::vector<long long> phi_sieve(int n) {
        std::vector<long long> phi_arr(n + 1);
        for (int i = 0; i <= n; i++) phi_arr[i] = i;
        for (int i = 2; i <= n; i++) {
            if (phi_arr[i] == i) {
                for (int j = i; j <= n; j += i)
                    phi_arr[j] -= phi_arr[j] / i;
            }
        }
        return phi_arr;
    }

    static std::vector<long long> divisors(long long n) {
        if (n <= 0) return {};
        std::vector<long long> divs;
        for (long long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                divs.push_back(i);
                if (i * i != n) divs.push_back(n / i);
            }
        }
        std::sort(divs.begin(), divs.end());
        return divs;
    }

    static long long divisor_count(long long n) {
        if (n <= 0) return 0;
        long long count = 0;
        for (long long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                count++;
                if (i * i != n) count++;
            }
        }
        return count;
    }

    static long long sum_of_divisors(long long n) {
        if (n <= 0) return 0;
        long long sum = 0;
        for (long long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                sum += i;
                if (i * i != n) sum += n / i;
            }
        }
        return sum;
    }

    static long long floor_div(long long a, long long b) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        long long res = a / b;
        long long rem = a % b;
        if (rem != 0 && ((a < 0) ^ (b < 0))) res--;
        return res;
    }

    static long long ceil_div(long long a, long long b) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        long long res = a / b;
        long long rem = a % b;
        if (rem != 0 && !((a < 0) ^ (b < 0))) res++;
        return res;
    }

    static long long isqrt(long long n) {
        if (n <= 0) return 0;
        long long x = std::sqrt(n);
        while ((x + 1) * (x + 1) <= n) x++;
        while (x * x > n) x--;
        return x;
    }

    static bool is_square(long long n) {
        if (n < 0) return false;
        long long r = isqrt(n);
        return r * r == n;
    }

    static int floor_log2(unsigned long long n) {
        if (n == 0) return -1;
        return 63 - __builtin_clzll(n);
    }

    static int ceil_log2(unsigned long long n) {
        if (n <= 1) return 0;
        return floor_log2(n - 1) + 1;
    }

    static bool is_power_of_two(unsigned long long n) {
        return n && !(n & (n - 1));
    }

    static unsigned long long next_power_of_two(unsigned long long n) {
        if (n == 0) return 1;
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        n |= n >> 32;
        return n + 1;
    }

    static int highest_bit(unsigned long long n) { return floor_log2(n); }
    static int lowest_bit(unsigned long long n) {
        if (n == 0) return -1;
        return __builtin_ctzll(n);
    }
    static int popcount(unsigned long long n) { return __builtin_popcountll(n); }

    static long long fib(int n) {
        if (n < 0) return 0;
        if (n == 0) return 0;
        if (n == 1) return 1;
        long long a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            long long c = a + b;
            a = b;
            b = c;
        }
        return b;
    }

    static long long fib_mod(long long n, long long mod) {
        if (mod <= 0 || mod == 1 || n <= 0) return 0;
        if (n == 1) return 1;
        
        auto mul = [mod](long long x, long long y) {
            unsigned long long a = (unsigned long long)x;
            unsigned long long b = (unsigned long long)y;
            const unsigned long long m = (unsigned long long)mod;
            unsigned long long result = 0;
            while (b != 0) {
                if (b & 1) {
                    result = (result >= m - a) ? result - (m - a) : result + a;
                }
                b >>= 1;
                if (b != 0) {
                    a = (a >= m - a) ? a - (m - a) : a + a;
                }
            }
            return (long long)result;
        };

        auto fib_pair = [&](long long n_val, auto& self) -> std::pair<long long, long long> {
            if (n_val == 0) return {0, 1};
            auto p = self(n_val >> 1, self);
            long long c = mul(p.first, (2 * p.second - p.first + mod) % mod);
            long long d = (mul(p.first, p.first) + mul(p.second, p.second)) % mod;
            if (n_val & 1) return {d, (c + d) % mod};
            else return {c, d};
        };
        return fib_pair(n, fib_pair).first;
    }

    class Combinatorics {
    private:
        int max_n;
        long long mod;
        std::vector<long long> fact_arr;
        std::vector<long long> inv_fact_arr;

    public:
        Combinatorics(int n, long long m) : max_n(n), mod(m) {
            fact_arr.resize(n + 1);
            inv_fact_arr.resize(n + 1);
            fact_arr[0] = 1;
            inv_fact_arr[0] = 1;
            auto mul = [m](long long x, long long y) {
                const unsigned long long modulus = static_cast<unsigned long long>(m);
                unsigned long long a = static_cast<unsigned long long>(x) % modulus;
                unsigned long long b = static_cast<unsigned long long>(y) % modulus;
                unsigned long long result = 0;
                while (b != 0) {
                    if (b & 1) {
                        result = result >= modulus - a ? result - (modulus - a) : result + a;
                    }
                    b >>= 1;
                    if (b != 0) {
                        a = a >= modulus - a ? a - (modulus - a) : a + a;
                    }
                }
                return static_cast<long long>(result);
            };
            for (int i = 1; i <= n; i++) {
                fact_arr[i] = mul(fact_arr[i - 1], i);
            }
            inv_fact_arr[n] = MathUtils::mod_inverse_internal(fact_arr[n], mod);
            for (int i = n - 1; i >= 1; i--) {
                inv_fact_arr[i] = mul(inv_fact_arr[i + 1], i + 1);
            }
        }

        long long factorial(int n) const {
            if (n < 0 || n > max_n) return 0;
            return fact_arr[n];
        }

        long long permutation(int n, int r) const {
            if (r < 0 || r > n || n > max_n) return 0;
            auto mul = [this](long long x, long long y) {
                const unsigned long long modulus = static_cast<unsigned long long>(mod);
                unsigned long long a = static_cast<unsigned long long>(x) % modulus;
                unsigned long long b = static_cast<unsigned long long>(y) % modulus;
                unsigned long long result = 0;
                while (b != 0) {
                    if (b & 1) {
                        result = result >= modulus - a ? result - (modulus - a) : result + a;
                    }
                    b >>= 1;
                    if (b != 0) {
                        a = a >= modulus - a ? a - (modulus - a) : a + a;
                    }
                }
                return static_cast<long long>(result);
            };
            return mul(fact_arr[n], inv_fact_arr[n - r]);
        }

        long long nCr(int n, int r) const {
            if (r < 0 || r > n || n > max_n) return 0;
            auto mul = [this](long long x, long long y) {
                const unsigned long long modulus = static_cast<unsigned long long>(mod);
                unsigned long long a = static_cast<unsigned long long>(x) % modulus;
                unsigned long long b = static_cast<unsigned long long>(y) % modulus;
                unsigned long long result = 0;
                while (b != 0) {
                    if (b & 1) {
                        result = result >= modulus - a ? result - (modulus - a) : result + a;
                    }
                    b >>= 1;
                    if (b != 0) {
                        a = a >= modulus - a ? a - (modulus - a) : a + a;
                    }
                }
                return static_cast<long long>(result);
            };
            return mul(mul(fact_arr[n], inv_fact_arr[r]), inv_fact_arr[n - r]);
        }
    };
};