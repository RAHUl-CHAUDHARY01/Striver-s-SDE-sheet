🚀 What is Rabin-Karp Algorithm?
The Rabin-Karp algorithm is a string-searching algorithm used to find a pattern (a substring) inside a larger string (called the text). It uses hashing to efficiently compare substrings of the text with the pattern.

Instead of comparing every character every time, we:

Hash the pattern and the substrings of the text.

Compare the hashes.

If the hashes match, then compare the actual substrings to avoid false positives (called spurious hits).

💡 Analogy
Imagine you're looking for a specific paragraph (needle) in a book (haystack). You can't read every word in the book because it's huge. Instead, you assign a unique code (hash) to your paragraph and slide a "window" across the book, checking if the code matches. If it does, you double-check the text itself (to be sure).

✅ Single Hashing – As in Your Code
In your implementation, you're using:

#define ll long long int
#define MOD 1000000007
#define RADIX 26  // base - size of alphabet
Each character 'a' to 'z' is treated as a digit in base 26, i.e., 'a' = 0, 'b' = 1, ..., 'z' = 25.

You treat the entire string as a number in base-26.

🔢 Hash Function:
For a string s = "abc", you calculate:

hash("abc") = (a * 26² + b * 26¹ + c * 26⁰) % MOD
This makes comparing strings faster, as you're comparing numbers instead of character-by-character strings.

🔁 Rolling Hash
Once you've hashed the first substring, you don’t need to hash the next one from scratch. You use a rolling hash formula to compute the next substring’s hash in O(1) time.

hash_new = ((old_hash * RADIX) - old_char_contribution + new_char) % MOD;
This is what you’re doing in:

hashHay = ((hashHay*RADIX)%MOD - ((haystack[i-1]-'a')*MAX_WEIGHT)%MOD + 
(haystack[i+m-1]-'a') + MOD)%MOD;
MAX_WEIGHT = RADIX^m

Subtract contribution of outgoing character

Add the new character

⚠️ Spurious Hits
Sometimes two different substrings may produce the same hash due to hash collisions.

Example:

needle = "abc"
text = "xyzabc"
Suppose hash("abc") = 12345 and hash("xya") = 12345 (coincidentally). This is a spurious hit.

To avoid errors, after hash matches, you manually compare substrings:


if(hashHay == hashNeedle){
    // double check with actual string
}
🛡️ Double Hashing – To Reduce Spurious Hits
Single hashing is susceptible to collisions. Double hashing uses two different hash functions/moduli to make the collision probability extremely low.

How?
You compute two hashes using:

Two different mod values (e.g., MOD1 = 1e9+7, MOD2 = 1e9+9)

Optionally two different RADIX values too

Then compare both hashes. Only if both match, proceed to check strings.

Double Hash Code Skeleton
pair<ll,ll> hashValue(string s, ll RADIX1, ll RADIX2, ll MOD1, ll MOD2, ll m){
    ll h1 = 0, h2 = 0, f1 = 1, f2 = 1;
    for(ll i = m - 1; i >= 0; i--){
        h1 = (h1 + ((s[i] - 'a') * f1) % MOD1) % MOD1;
        h2 = (h2 + ((s[i] - 'a') * f2) % MOD2) % MOD2;
        f1 = (f1 * RADIX1) % MOD1;
        f2 = (f2 * RADIX2) % MOD2;
    }
    return {h1, h2};
}
Use the same rolling hash logic for both hashes

Compare both (hash1, hash2) pairs for pattern and text substrings

This drastically reduces the chance of spurious hits.

