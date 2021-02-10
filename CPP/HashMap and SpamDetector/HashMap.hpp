#ifndef EX1_HASHMAP_HPP
#define EX1_HASHMAP_HPP

#include "vector"
#include "list"
#include "string"
#include "iostream"
#include "memory"
#include "iterator"
#include <fstream>
#include <sstream>

using std :: hash;
using std :: vector;
using std :: string;
using std :: pair;
using std :: invalid_argument;
using std :: cout;
using std :: cerr;
using std :: cerr;
using std :: istringstream;
using std :: ifstream;
using std :: unique_ptr;
using std :: hash;

const string invalidError = "Invalid input\n";

/**
* Describes the default lower and higher load
 * factors of a newly created hash set
*/

double DEFAULT_UPPER_FACTOR = 0.75, DEFAULT__LOWER_FACTOR = 0.25, insertionCoefficient = 2.0,
deletionCoefficient = 0.5;

/**
* Describes the capacity of a newly created hash set
*/
int INITIAL_CAPACITY = 16;

/**
 * Class for an object of type a HashMap set of objects
 * @tparam KeyT The object type of the keys in the set
 * @tparam ValueT The object type of the values in the set
 */
template <class KeyT, class ValueT>
class HashMap
{
    using Bucket = vector<pair<KeyT, ValueT>>;
    using Pair = pair<KeyT, ValueT>;

private:
    //lower factor of the set
    double _Lower_Factor;

    //higher factor of the set
    double _Upper_Factor;

    //holds the current number of elements in the set
    int _numElements;

    //holds the current number of Buckets
    // that are contained by the set
    int _capacity;

    //the array of vectors in which the
    // elements of the set are being stored in
    Bucket * _bucketArray;

    /**
     * returns the Hash code of a given KeyT object
     * @param element a KeyT object
     * @return The hashCode of the object
     */
    inline int _hashCode(KeyT element) const
    {
        return hash<KeyT>{}(element);
    }

    /**
     * Method that returns the appropriate index of the HashMap
     * according to a given HashCode
     * @param hashCode the hashCode
     * @return The corresponding hashMap index
     */
    inline int _hashFunc(int hashCode) const
    {
        return (hashCode &(_capacity - 1));
    }

    /**
     * Checks if  there's a deviation from the upper or lower load factors.
     * If there is, will resize and double the array's capacity
     */
    void _resize(double coefficient)
    {
        //checks if the new load factor exceeds from the upper or lower load factors
        double curFactor = getLoadFactor();
        if(((curFactor > _Upper_Factor || curFactor > 1) && coefficient == insertionCoefficient) ||
           ((curFactor < _Lower_Factor && coefficient == deletionCoefficient) || (curFactor == 0
           && capacity() > 1)))
        {
            //convert new size from double to int
            int newSize = (int)(capacity() * coefficient);

            //creates a new array double or half the size
            Bucket* array = new Bucket[newSize];

            //create a backup for the current HashMap called temp and
            // set the new array as the current table for the set in order to
            // rehash all the elements
            HashMap temp = *this;
            delete[] _bucketArray;
            _bucketArray = array;
            _capacity = newSize;
            _numElements = (int)coefficient / 2;

            //rehash all elements in the set
            for(auto it = temp.begin(); it != temp.end(); ++it)
            {
                insert(it->first, it->second);
            }
        }
    }

    /**
     * Custom nested exception class for input that
     * violates one of the exercise's restrictions
     */
    class BadInputException : public invalid_argument
    {
        /**
         * Default constructor
         */
        BadInputException() : invalid_argument(invalidError){};
    };

public:
    /**
     * Default constructor
     */
    HashMap() : _Lower_Factor(DEFAULT__LOWER_FACTOR), _Upper_Factor(DEFAULT_UPPER_FACTOR),
    _numElements(0), _capacity(INITIAL_CAPACITY), _bucketArray(new Bucket[INITIAL_CAPACITY]){}

    /**
     * Constructor. Receives the higher and lower factors of the set
     */
    HashMap(double uf, double lf) : _Lower_Factor(lf) , _numElements(0), _Upper_Factor(uf),
    _capacity(INITIAL_CAPACITY), _bucketArray(new Bucket[INITIAL_CAPACITY])
    {
        if(_Lower_Factor >= _Upper_Factor || _Lower_Factor < 0 || _Upper_Factor > 1)
        {
            throw BadInputException();
        }
    }

    /**
     * Constructor. Receives the higher and lower factors of the set
     */
    HashMap(vector<KeyT> keyVector, vector<ValueT> valueVector) : HashMap()
    {
        if(keyVector.size() != valueVector.size())
        {
            throw BadInputException();
        }

        for(int i = 0; i < keyVector.size(); i++)
        {
            insert(Pair (keyVector[i], valueVector[i]));
        }
    }

    /**
     * Copy Constructor
     */
    HashMap(HashMap<KeyT, ValueT> & map) noexcept
    {
        _Upper_Factor = map._Upper_Factor;
        _Lower_Factor = map._Lower_Factor;
        _numElements = 0;
        _capacity = map._capacity;
        _bucketArray = new Bucket[_capacity];

        for(auto it = map.begin(); it != map.end(); it++)
        {
            insert(it->first, it->second);
        }
    }

    /**
     * Move Constructor
     */
    HashMap(HashMap<KeyT, ValueT> && map) noexcept
    {
        _Upper_Factor = map._Upper_Factor;
        _Lower_Factor = map._Lower_Factor;
        _numElements = map.size();
        _capacity = map.capacity;

        //release the pointer from rvalue unique_ptr and
        //assign it as the bucket array of (*this)
        Bucket* ptr = map._bucketArray.get();
        map._bucketArray.release();

        _bucketArray = unique_ptr<Bucket> (ptr);
    }

    /**
     * The destructor for the class
     */
    ~HashMap(){delete[] _bucketArray; }

    /**
     * @return The number of elements currently in the set
     */
    inline int size()
    {
        return _numElements;
    }

    /**
     * @return The current capacity (number of cells) of the table
     */
    inline int capacity()
    {
        return _capacity;
    }

    /**
     * Gets a key and adds it to the HashMap
     * @param newValue The given key
     * @return True if added successfully, false otherwise
     */
    bool insert(KeyT key, ValueT value)
    {
        //if element is already in the set,returns false
        if(containsKey(key))
        {
            return false;
        }

        Pair newValue (key, value);

        //increases numElement by 1 and checks
        // if a resize of the array is necessary
        _numElements++;
        _resize( insertionCoefficient);

        //adds the element to the set in the appropriate array cell
        int index = _hashFunc(_hashCode(newValue.first));
        _bucketArray[index].push_back(newValue);

        //finally, returns true
        return true;
    }

    /**
     * Remove the input element from the set
     * @param toDelete Value to delete
     * @return True iff toDelete is found and deleted,
     */
    bool erase(KeyT toDelete)
    {
        //if element is not in the set,returns false
        if(!containsKey(toDelete))
        {
            return false;
        }

        //deletes the element by defining an iterator and passing
        //it to the erase function of the Bucket object
        int index = _hashFunc(_hashCode(toDelete));
        typename Bucket :: iterator it = _bucketArray[index].begin();

        while(it != _bucketArray[index].end())
        {
            if((*it).first == toDelete)
            {
                //erase the element
                _bucketArray[index].erase(it);

                //subtracts 1 from elements_in_set and checks
                // if a resize of the array is necessary
                _numElements--;
                _resize(deletionCoefficient);

                //finally, returns true
                return true;
            }

            ++it;
        }
    }

    /**
     * Gets a key and checks if it contained in the HashMap
     * @param searchVal The given key
     * @return True if the HashMap contains the key, false otherwise
     */
    bool containsKey(KeyT searchVal)
    {
        //represents the List in the array to which the value
        //will be inserted according to its hashcode.
        int index = _hashFunc(_hashCode(searchVal));

        //look trough the LinkedList to check if the element is already in the set
        //if so,will return true
        for (Pair element : _bucketArray[index])
        {
            if (_hashCode(searchVal) == _hashCode(element.first))
            {
                return true;
            }
        }
        //if item is not found,returns false
        return false;
    }

    /**
     * Returns the bucket size in which the given key resides
     * @param key A key in the hashMap
     * @return The size of the bucket
     */
    int bucketSize(KeyT key) const
    {
        for(int i = 0; i < capacity() ; i++)
        {
            for(Pair p : _bucketArray[i])
            {
                if(p.first == key.first)
                {
                    return _bucketArray[i].size();
                }
            }
        }

        //if key was not found, throw exception
        throw BadInputException();
    }

    /**
     * Function to check if the HashMap is empty
     * @return True if map is empty, false otherwise
     */
    bool empty() const
    {
        for(int i = 0; i < capacity() ; i++)
        {
            if(!_bucketArray[i].empty())
            {
                return false;
            }
        }
        return true;
    }

    double getLoadFactor()
    {
        return 1.0 * size() / capacity();
    }

    /**
     * Custom swap method for two HashMap objects
     * @param first The first HashMap object
     * @param second The Second HashMap object
     */
    friend void swap(HashMap& first, HashMap& second)
    {
        // enable ADL
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.Upper_Factor, second.Upper_Factor);
        swap(first._Lower_Factor, second._Lower_Factor);
        swap(first.numElements, second.numElements);
        swap(first.capacity(), second.capacity());

        //using the swap function of the unique_ptr object
        first._bucketArray.swap(second._bucketArray);
    }

    /**
     * Method that returns the corresponding
     * value for the given key
     * @param key The given key
     * @return The corresponding value
     */
    ValueT& at(KeyT key)
    {
        for(Pair& p : *this)
        {
            if(p.first == key)
            {
                return p.second;
            }
        }
        //in case the key was not found
        throw BadInputException();
    }

    /**
     * overload for the '=' operator
     */
    HashMap& operator=(HashMap other)
    {
        swap(*this, other);
        return *this;
    }

    /**
     * overload for the '[]' operator
     */
    Pair& operator[](KeyT key) noexcept
    {
        if(containsKey(key))
        {
            return at(key);
        }

        //if map does not contain the given key, add
        // it and return a reference to the created value
        insert(key, ValueT());
        return at(key);
    }

    /**
     * overload for the '[]' operator (const)
     */
    const Pair& operator[](KeyT key) const noexcept
    {
        if(containsKey(key))
        {
            return at(key);
        }
    }

    /**
     * Nested iterator class
     */
    class iterator
    {
    private:
        typedef typename Bucket :: iterator pairIterator;

        //pointer that represent the Bucket array of a given HashMap
        HashMap* _pointer;

        //iterator field that contains a certain pair in a certain bucket
        pairIterator _iter;

        //index representation of the current bucket in the iteration
        int _currentBucket;

    public:
        /**
         * Default constructor
         */
        iterator(HashMap* H = nullptr) : _pointer(H), _currentBucket(0)
        {
            if(_pointer != nullptr)
            {
                _iter = _pointer->_bucketArray[0].begin();

                //searching for the first available pair in the HashMap
                if( _pointer->_bucketArray[0].empty())
                {
                    while(_currentBucket < _pointer->capacity())
                    {
                        if(!_pointer->_bucketArray[_currentBucket].empty())
                        {
                            _iter = _pointer->_bucketArray[_currentBucket].begin();
                            break;
                        }
                        _currentBucket++;
                    }
                    //in case no additional pair was found
                    if(_currentBucket == _pointer->capacity())
                    {
                        _currentBucket = 0;
                    }
                }
            }
        };

        /**
         * '++' operator
         */
        iterator& operator++()
        {
            if(_iter == _pointer->_bucketArray[_currentBucket].end())
            {
                return *this;
            }

            //if current location is in the end of a vector, find the next valid pair
            if(_iter + 1 == _pointer->_bucketArray[_currentBucket].end())
            {
                int originalBucket = _currentBucket;
                _currentBucket++;
                while(_currentBucket < _pointer->capacity())
                {
                    if(!_pointer->_bucketArray[_currentBucket].empty())
                    {
                        _iter = _pointer->_bucketArray[_currentBucket].begin();
                        break;
                    }
                    _currentBucket++;
                }
                //in case no additional pair was found
                if(_currentBucket == _pointer->capacity())
                {
                    _currentBucket = originalBucket;
                    _iter++;
                }
            }
            else
            {
                //increase iterator location by one
                _iter++;
            }

            return *this;
        }

        /**
         * '++(int)' operator
         */
        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }


        /**
         * '*' operator
         */
        Pair& operator*() const { return *_iter; }

        /**
         * '->' operator
         */
        Pair* operator->() const { return &(*_iter); }

        /**
         * '==' operator
         */
        bool operator==(iterator const& rhs) const
        {
            return _iter == rhs._iter;
        }

        /**
         * '!=' operator
         */
        bool operator!=(iterator const& rhs) const
        {
            return !(*this == rhs);
        }
    };

    /**
     * Returns an iterator containing the first Pair in the Map
     */
    iterator begin() { return iterator(this); }

    /**
     * Returns an iterator containing the end of
     * the last iterator (according to index order)
     * which is not empty
     */
    iterator end()
    {
        iterator end = iterator(this);

        //increase iterator until condition is fulfilled,
        //condition indicates that there are no additional
        //pairs, therefore the end of the set is reached
        while(end != end++)
        {
            end++;
        }

        return end;
    }
};
#endif //EX1_HASHMAP_HPP