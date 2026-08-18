#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <utility>
#include <stack>
#include <queue>
#include <numeric>
#include <unordered_map>
#include <bitset>
#include <tuple>
#include <climits>
#include <cstring>
#include <cassert>
#include <random>
#include <functional>
#include <memory>

// --- PBDS (GNU GCC / Codeforces Only) ---
#if defined(__GNUC__) && __has_include(<ext/pb_ds/assoc_container.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using pbds_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

using namespace std;

// 1. Types and basic definitions
using ll = long long;
using ull = unsigned long long;
using ld = long double;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// 2. Group abbreviations
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<short> vs;
typedef vector<double> vd;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef set<int> si;
typedef map<int, int> mii;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef unordered_map<int, int> umii;
typedef unordered_set<int> usi;

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

#define rall(x) (x).rbegin(), (x).rend()
#define popcnt(x) __builtin_popcountll(x)
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define precision(x) fixed << setprecision(x)

const int INF = 1e9 + 7;
const ll LINF = 1e18 + 7;
const double EPS = 1e-9;

// 4. Short-hand IF & Branch Optimizations
template<typename T> inline bool chmin(T& a, const T& b) { return b < a ? a = b, true : false; }
template<typename T> inline bool chmax(T& a, const T& b) { return b > a ? a = b, true : false; }

#define iff(cond, a, b) ((cond) ? (a) : (b))

// 5. Anti-Hack Custom Hash (Unbreakable O(1) unordered_map on Codeforces)
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename K, typename V>
using safe_map = unordered_map<K, V, custom_hash>;

template<typename K>
using safe_set = unordered_set<K, custom_hash>;

// 6. I/O Overloads
template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& p) { return in >> p.fi >> p.se; }
template<typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) { return out << "{" << p.fi << ", " << p.se << "}"; }

template<typename T>
istream& operator>>(istream& in, vector<T>& v) { for (auto& x : v) in >> x; return in; }
template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (int i = 0; i < sz(v); ++i) out << v[i] << (i + 1 == sz(v) ? "" : " ");
    return out;
}

// 7. Local Debugger
#ifndef ONLINE_JUDGE
#define dbg(x) cerr << #x << " = " << (x) << nl
#else
#define dbg(x)
#endif

// 8. Math, Grid & Fast Modular Arithmetic
const int dx4[] = {-1, 1, 0, 0};
const int dy4[] = {0, 0, 1, -1};
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

inline ll mod_add(ll a, ll b, ll m = INF) { return (a % m + b % m + m) % m; }

inline ll mod_mul(ll a, ll b, ll m = INF) {
#if defined(__GNUC__)
    return (ll)((__int128)a * b % m);
#else
    ull u_a = (a % m + m) % m;
    ull u_b = (b % m + m) % m;
    return (ll)((u_a * u_b) % m);
#endif
}

inline ll power(ll base, ll exp, ll mod = INF) {
    ll res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = mod_mul(res, base, mod);
        base = mod_mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// 9. Game Dev & Physics Utilities (Lerp, Clamp & Vector2D)
template<typename T> inline T lerp_val(T a, T b, double t) { return a + (b - a) * t; }
template<typename T> inline T clamp_val(T val, T low, T high) { return min(max(val, low), high); }

template<typename T = double>
struct Vec2 {
    T x, y;
    Vec2() : x(0), y(0) {}
    Vec2(T _x, T _y) : x(_x), y(_y) {}

    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
    Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
    Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }

    T dot(const Vec2& v) const { return x * v.x + y * v.y; }
    T sqrMagnitude() const { return x * x + y * y; }
    double magnitude() const { return sqrt(sqrMagnitude()); }
    Vec2 normalized() const { double m = magnitude(); return m > 0 ? *this * (1.0 / m) : Vec2(); }
};

// 10. Precision Timer
struct Timer {
    chrono::high_resolution_clock::time_point start;
    Timer() { start = chrono::high_resolution_clock::now(); }
    void reset() { start = chrono::high_resolution_clock::now(); }
    double elapsed_ms() const {
        return chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count();
    }
};