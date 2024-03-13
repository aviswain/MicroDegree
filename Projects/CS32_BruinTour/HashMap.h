//
//  HashMap.h
//  BruinTour
//
//  Created by Avi Swain on 3/6/24.
//

#ifndef HashMap_h
#define HashMap_h

#include <string>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>

template <typename T>
class HashMap
{
public:
    // CONSTRUCTOR
    HashMap(double max_load = 0.75) : m_hashMap(10), m_numBuckets(10), m_curLoad(0.0) {
        // A newly constructed HashMap must have 10 buckets and no associations (done in initializer list)
        
        /*
         If the caller does not pass an argument to the constructor or passes a value that is
         not positive, then maximum load factor must be 0.75.
         */
        if (max_load <= 0.0)
            m_maxLoad = 0.75;
        else
            m_maxLoad = max_load;
        
    };
    
    // DESTRUCTOR
    ~HashMap() {
        // empty destructor becuase no dynamic allocation
    };
    
    // SIZE METHOD
    int size() const {
        int totalAssociations = 0;
        
        for (int i = 0; i < m_hashMap.size(); i++) {
            totalAssociations += m_hashMap[i].size();
        }
        
        return totalAssociations;
    };
    
    // INSERT METHOD
    void insert(const std::string& key, const T& value) {
        
        typename std::list<association>::iterator it;
        
        it = m_hashMap[getBucketNum(key, m_numBuckets)].begin();
        while (it != m_hashMap[getBucketNum(key, m_numBuckets)].end()) {
            /*
             If there is already an association with that key in the hashmap, then the
             item associated with that key is replaced by the second parameter (value).
             */
            if (it->key == key) {
                it->val = value;
                break;
            }
            it++;
        }

        /*
         If no association currently exists with that key, inserts
         a new association into the hashmap with that key/value pair.
         */
        if (it == m_hashMap[getBucketNum(key, m_numBuckets)].end()) {
          
            // Enlarge the hashmap if adding a new item will surpass the max load
            if (!canHandleLoad()) {
                enlargeHashMap();
            }
            
            // Create a new association
            association newPair;
            newPair.key = key;
            newPair.val = value;
            
            // Insert it into the map
            m_hashMap[getBucketNum(key, m_numBuckets)].push_back(newPair);
            
            // Update the current load
            m_curLoad = ((size())/static_cast<double>(m_numBuckets));
        }
        
        
    }
    
    // OPERATOR OVERLOADING METHOD FOR BRACKETS
    T& operator[](const std::string& key) {
        
        typename std::list<association>::iterator it;
        it = m_hashMap[getBucketNum(key, m_numBuckets)].begin();
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //  I MADE AN ASSUMPTION, BECAUSE IT WAS UNCLEAR WHAT TO DO HERE:
        //      The explanation in the spec did not say anything about how the bracket operators
        //      should work when an a key already exists in the map. I decided that it should
        //      still return a reference to the value. That way the brackets can still be used
        //      to update key-value pairs and not just insert ones that don't exist yet.
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        while (it != m_hashMap[getBucketNum(key, m_numBuckets)].end()) {
            if (it->key == key) {
                return it->val;
            }
            it++;
        }
        
        // Enlarge the hashmap if adding a new item will surpass the max load
        if (!canHandleLoad()) {
            enlargeHashMap();
        }
        
        // Create a new association and insert it into the map
        association newPair;
        newPair.key = key;
        newPair.val = T();
        m_hashMap[getBucketNum(key, m_numBuckets)].push_back(newPair);
        
        // Update the current load
        m_curLoad = ((size())/static_cast<double>(m_numBuckets));
        
        // return a reference to the newly created value in the map.
        it = m_hashMap[getBucketNum(key, m_numBuckets)].end();
        it--;
        return it->val;
        
        
    };
    
    // FIND METHOD
    const T* find(const std::string& key) const {
        
        typename std::list<association>::const_iterator it;
        it = m_hashMap[getBucketNum(key, m_numBuckets)].begin();
        
        // return a pointer to the value associated with the given key
        while (it != m_hashMap[getBucketNum(key, m_numBuckets)].end()) {
            if (it->key == key) {
                return &(it->val);
            }
            it++;
        }
        
        // If no association exists with the given key, return nullptr
        return nullptr;
    };
    
    // If no association exists with the given key, return nullptr; otherwise,
    // return a pointer to the value associated with that key. This pointer can be
    // used to examine that value or modify it directly within the map.
    T* find(const std::string& key) {
        const auto& hm = *this;
        return const_cast<T*>(hm.find(key));
    }
    
private:
    // internal struct for assocations
    struct association {
        std::string key;
        T val;
    };
    
    // hashmap
    std::vector<std::list<association>> m_hashMap;
    
    // hashmap attributes
    double m_maxLoad;
    double m_curLoad;
    int m_numBuckets;
    
    // hashing function for strings
    unsigned int getBucketNum(const std::string &hashMe, int numBuckets) const{
        std::hash<std::string> str_hash;           // creates a string hasher
        unsigned long hashValue = str_hash(hashMe); // hash our string
        
        // use modulo to find bucket
        unsigned int bucketNum = hashValue % numBuckets;
        return bucketNum;
    }
    
    // Checks if, when adding an item to expandable hash map, its load factor would
    // increase above the maximum load specified during construction
    bool canHandleLoad() {
        if (((size() + 1)/static_cast<double>(m_numBuckets)) <= m_maxLoad)
            return true;
        
        return false;
    }
    
    // Used to make the hashmap larger when the maximum load is reached
    void enlargeHashMap() {
        
        // Create a new internal hash map with double the current number of buckets.
        std::vector<std::list<association>> newHashMap(2*m_numBuckets);
        
        // Rehash all items from the current hash map into the new, larger hash map.
        typename std::list<association>::iterator it;
        
        for (int i = 0; i < m_numBuckets; i++) {
            it = m_hashMap[i].begin();
            while (it != m_hashMap[i].end()) {
                association pair;
                pair.key = it->key;
                pair.val = it->val;
                newHashMap[getBucketNum(it->key, 2*m_numBuckets)].push_back(pair);
                it++;
            }
        }
        
        // Replace the current hash map with the new hash map.
        m_hashMap = newHashMap;
        m_numBuckets *= 2;
    }
    
    // Prevent incorrect copying and assignment of HashMap objects
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;
};
#endif /* HashMap_h */
