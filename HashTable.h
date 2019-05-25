#ifndef HASHTABLE_H
#define HASHTABLE_H

/// Clasa Template HashTable

#define NDEBUG
#include <vector>
#include <list>
#include <assert.h>
#include <utility>

using namespace std;

#define TABLE_SIZE 1000

template <typename K>
struct KeyHash { // functia default KeyHash
unsigned long operator() (const K &key) const {
    return reinterpret_cast<unsigned long>(&key) % 111;
    }
};


template <class K, class V, class F = KeyHash<K> >
class HashTable {
private:
    vector <list <pair <K, V> > > TABLE;
    int DistinctKeys;
public:
    HashTable();
    HashTable(const HashTable<K, V, F>& other);
    HashTable& operator=(const HashTable<K, V, F>&);
    V& operator[](K&);
    inline void AddValue(const K&, const V&);
    void DeleteValues(const K&);
    vector <V> GetAllValues(const K&);
    bool Search(const K&, const V&) const;
    unsigned GetDistinctKeys() const;
    template <class Q, class W, class E>
    friend ostream& operator<<(ostream&, HashTable<Q, W, E>&);
};

template <class K, class V, class F>
HashTable<K, V, F>::HashTable() :
    DistinctKeys(0) {
    TABLE.resize(TABLE_SIZE);
}

template <class K, class V, class F>
HashTable<K, V, F>::HashTable(const HashTable<K, V, F>& other) :
    DistinctKeys(other.DistinctKeys) {
    TABLE.resize(TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; ++i) {
        TABLE[i] = other.TABLE[i];
    }
}

template <class K, class V, class F>
HashTable<K, V, F>& HashTable<K, V, F>::operator=(const HashTable<K, V, F>& other) {

    for (int i = 0; i < TABLE_SIZE; ++i) {
        TABLE[i] = other.TABLE[i];
    }
    return *this;
}

template <class K, class V, class F>
void HashTable<K, V, F>::AddValue(const K& Key, const V& Val) {
    F Func;
    int Index = Func(Key);
    assert(Index < 1000);
    bool isKey = 0;
    for (typename list <pair <K, V> > :: iterator it = TABLE[Index].begin(); it != TABLE[Index].end(); ++it) {
        if (it->first == Key) isKey = 1;
    }
    TABLE[Index].push_back(make_pair(Key, Val));
    if (isKey == 0) DistinctKeys++;

}

template <class K, class V, class F>
bool HashTable<K, V, F>::Search(const K& Key, const V& Value) const {
    F Func;
    unsigned Index = Func(Key);

        for (typename list <pair <K, V> > :: const_iterator it = TABLE[Index].begin(); it != TABLE[Index].end(); ++it)
            if (it->second == Value)
                return 1;

    return 0;
}

template <class K, class V, class F>
void HashTable<K, V, F>::DeleteValues(const K& Key) {
    F Func;
    int Index = Func(Key);

    typename list <pair <K, V> >::iterator it = TABLE[Index].begin();
    while (it != TABLE[Index].end()) {
        if (it->first == Key) it = TABLE[Index].erase(it);
    }
    DistinctKeys--;
}

template <class K, class V, class F>
unsigned HashTable<K, V, F>::GetDistinctKeys() const {
    return DistinctKeys;
}

template <class K, class V, class F>
vector <V> HashTable<K, V, F>::GetAllValues(const K& Key) {
    F Func;
    vector <V> Result;
    int Index = Func(Key);
    for (typename list <pair <K, V> > :: iterator it = TABLE[Index].begin(); it != TABLE[Index].end(); ++it) {
        if (it->first == Key) {
            Result.push_back(it->second);
        }
    }
    return Result;
}
template <class K, class V, class F>
V& HashTable<K, V, F> :: operator[] (K& Key) { // supraincarcarea operatorului de indexare
        F Func;
        int Index = Func(Key);
        for (typename list <pair <K, V> > :: iterator it = TABLE[Index].begin(); it != TABLE[Index].end(); ++it) {
            if (it->first == Key) return it->second;
        }
    throw Key;
}

template <class K, class V, class F>
ostream& operator<<(ostream& out, HashTable<K, V, F>& A) { // supraincarcarea operatorului de afisare
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (A.TABLE[i].empty()) continue;
        out << i << ":\n";
        for (typename list <pair <K, V> > :: iterator it = A.TABLE[i].begin(); it != A.TABLE[i].end(); ++it) {
            out << "    Key: " << it->first << ", value: " << it->second << "\n";
        }
    }
    return out;
}

#endif // HASHTABLE_H
