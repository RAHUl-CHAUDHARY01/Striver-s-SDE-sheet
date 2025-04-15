---

# 🔍 Rabin-Karp String Matching Algorithm (Single and Double Hashing)

The **Rabin-Karp algorithm** is a powerful and efficient string-searching algorithm that uses **hashing** to find a pattern (substring) within a larger text. It's especially useful when you need to search for multiple patterns or perform fast comparisons.

---

## 🚀 How Rabin-Karp Works

1. Treat the substring as a **number** using a base (RADIX), typically based on the alphabet size (e.g., 26 for 'a'–'z').
2. Compute the **hash** of the pattern and compare it with the hash of each substring in the text.
3. Use **rolling hash** to compute hashes efficiently for all substrings of the same length.
4. When a hash matches, do a **string comparison** to confirm the match (due to possible collisions).

---

## ⚠️ Spurious Hits

Sometimes, two different substrings may have the same hash. These are **spurious hits** or **hash collisions**. That's why we always confirm a match by comparing the actual strings when hashes match.

---

## 🛡️ Double Hashing

To reduce the chances of spurious hits, **double hashing** uses two different hash functions/moduli. This greatly minimizes collision probability.

---

## ✅ Single Hashing – C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007

class Solution {
public:
    ll hashValue(string s, ll RADIX, ll m) {
        ll ans = 0, factor = 1;
        for (ll i = m - 1; i >= 0; i--) {
            ans = (ans + ((s[i] - 'a') * factor) % MOD) % MOD;
            factor = (factor * RADIX) % MOD;
        }
        return ans;
    }

    int strStr(string haystack, string needle) {
        ll n = haystack.length(), m = needle.length();
        if (m > n) return -1;

        ll RADIX = 26;
        ll MAX_WEIGHT = 1;

        for (ll i = 1; i <= m; i++) {
            MAX_WEIGHT = (MAX_WEIGHT * RADIX) % MOD;
        }

        ll hashNeedle = hashValue(needle, RADIX, m);
        ll hashHay = 0;

        for (ll i = 0; i <= n - m; i++) {
            if (i == 0) {
                hashHay = hashValue(haystack.substr(0, m), RADIX, m);
            } else {
                hashHay = (hashHay * RADIX) % MOD;
                hashHay = (hashHay - ((haystack[i - 1] - 'a') * MAX_WEIGHT) % MOD + MOD) % MOD;
                hashHay = (hashHay + (haystack[i + m - 1] - 'a')) % MOD;
            }

            if (hashHay == hashNeedle) {
                if (haystack.substr(i, m) == needle)
                    return i; // match found
            }
        }
        return -1; // not found
    }
};
```

---

## 🔒 Double Hashing – C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD1 1000000007
#define MOD2 1000000009

class Solution {
public:
    pair<ll, ll> hashValue(string s, ll RADIX1, ll RADIX2, ll m) {
        ll h1 = 0, h2 = 0, f1 = 1, f2 = 1;
        for (ll i = m - 1; i >= 0; i--) {
            h1 = (h1 + ((s[i] - 'a') * f1) % MOD1) % MOD1;
            h2 = (h2 + ((s[i] - 'a') * f2) % MOD2) % MOD2;
            f1 = (f1 * RADIX1) % MOD1;
            f2 = (f2 * RADIX2) % MOD2;
        }
        return {h1, h2};
    }

    int strStr(string haystack, string needle) {
        ll n = haystack.length(), m = needle.length();
        if (m > n) return -1;

        ll RADIX1 = 31, RADIX2 = 53;
        ll MAX_WEIGHT1 = 1, MAX_WEIGHT2 = 1;

        for (ll i = 1; i <= m; i++) {
            MAX_WEIGHT1 = (MAX_WEIGHT1 * RADIX1) % MOD1;
            MAX_WEIGHT2 = (MAX_WEIGHT2 * RADIX2) % MOD2;
        }

        auto hashNeedle = hashValue(needle, RADIX1, RADIX2, m);
        pair<ll, ll> hashHay = {0, 0};

        for (ll i = 0; i <= n - m; i++) {
            if (i == 0) {
                hashHay = hashValue(haystack.substr(0, m), RADIX1, RADIX2, m);
            } else {
                hashHay.first = (hashHay.first * RADIX1) % MOD1;
                hashHay.first = (hashHay.first - ((haystack[i - 1] - 'a') * MAX_WEIGHT1) % MOD1 + MOD1) % MOD1;
                hashHay.first = (hashHay.first + (haystack[i + m - 1] - 'a')) % MOD1;

                hashHay.second = (hashHay.second * RADIX2) % MOD2;
                hashHay.second = (hashHay.second - ((haystack[i - 1] - 'a') * MAX_WEIGHT2) % MOD2 + MOD2) % MOD2;
                hashHay.second = (hashHay.second + (haystack[i + m - 1] - 'a')) % MOD2;
            }

            if (hashHay == hashNeedle) {
                if (haystack.substr(i, m) == needle)
                    return i;
            }
        }
        return -1;
    }
};
```

---

## 🧠 Key Concepts Summary

| Concept            | Description |
|--------------------|-------------|
| **Rolling Hash**   | Efficient way to calculate next hash in O(1) time |
| **Single Hashing** | One hash function; simpler but has collision risk |
| **Spurious Hit**   | Hash match but actual string mismatch |
| **Double Hashing** | Two hash functions; reduces chance of spurious hits |
| **Final Check**    | Always confirm with actual string match |

---

## 🧪 Sample Usage

```cpp
int main() {
    Solution sol;
    string haystack = "abxabcabcaby";
    string needle = "abcaby";
    
    int index = sol.strStr(haystack, needle);
    cout << "Pattern found at index: " << index << endl;
}
```

---
