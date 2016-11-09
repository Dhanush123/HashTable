// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <list>
#include <queue>
using namespace std;

template <typename K, typename V, int CAP>
class HashTable{
  struct Node
  {
    K key;
    V value;
  };

  list<Node> data[CAP];
  int(*hashCode)(const K&); // alias for hash code function
  int siz;
  Node dummy;

public:
  HashTable(int(*)(const K&)=0); // =0 because we still need a "default constructor" | changed from AA constructor
  V operator[](const K&) const; // getter
  V& operator[](const K&); // setter
  bool containsKey(const K&) const; // getter
  void deleteKey(const K&); // setter
  int size() const {return siz;}
  void clear();
  queue<K> keys() const;
  //----------------------------------------------- all same public interface as HashTable
};

template <typename K, typename V, int CAP> //worked on it
HashTable<K, V, CAP>::HashTable(int(*p)(const K&)){
  siz = CAP;
  hashCode = p;
}

template <typename K, typename V, int CAP> //did this
void HashTable<K, V, CAP>::clear(){
  for(int i = 0; i < siz; i++) {
      data[i].clear();
  }
}

template <typename K, typename V, int CAP>
V HashTable<K, V, CAP>::operator[](const K& key) const {
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::const_iterator it; // getters need to use const_iterator
  for (it = data[index].begin(); it != data[index].end(); it++) {
    if (it->key == key){
      return it->value;
    }
  }
  return dummy.value;
}

template <typename K, typename V, int CAP>
V& HashTable<K, V, CAP>::operator[](const K& key){
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::iterator it;
  for (it = data[index].begin(); it != data[index].end(); it++){
    if (it->key == key) {
      return it->value;
    }
  }
  Node temp;
  temp.key = key;
  temp.value = V();
  data[index].push_back(temp);
  return data[index].back().value;
}

template <typename K, typename V, int CAP> //worked on this
void HashTable<K, V, CAP>::deleteKey(const K& key){
  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::iterator it;
  for (it = data[index].begin(); it != data[index].end(); it++)
    if (it->key == key)
      delete data[index];
}

template <typename K, typename V, int CAP> //worked on this
bool HashTable<K, V, CAP>::containsKey(const K& key) const{

  int index = hashCode(key) % CAP;
  if (index < 0) index += CAP;
  typename list<Node>::const_iterator it; // getters need to use const_iterator
  for (it = data[index].begin(); it != data[index].end(); it++){
    if (it->key == key) {
      return true;
    }
  }

  return false; //technically shouldn't get here
}

template <typename K, typename V, int CAP>
queue<K> HashTable<K, V, CAP>::keys() const{
  queue<K> retQ;
  typename list<Node>::const_iterator it;
  for(int i = 0; i < siz; i++){
    for (it = data[i].begin(); it != data[i].end(); ++it) {
      retQ.push(it->key);
    }
  }
  return retQ;
}

#endif //HASHTABLE_HASHTABLE_H