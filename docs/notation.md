#### Description of notation

Im using a sort of system [hungarian notation](https://en.wikipedia.org/wiki/Hungarian_notation)

---
##### Comments at beggining of each file

Should be in following format

```
/*
 *  Filename
 *  
 *  Authors name(or in case of username username[site]) - email
 *  
 *  simple, concise description of contets
 */
```

---
##### All methods and data members have preceding comment(s) describing them and their use

Each method, and data field should have at least a single line comment describing its purpose and use, example:
```
    ...
    /// allocates at least nSize bytes of memory on the heap
    void* heapAllocate(size_t nSize);
    ...
```

---
##### All naming is CamelCase

All names including classes, methods, data fields etc. are camel case, the only difference may be in prefix (see below) or if the first letter is capitalized
Classes have the first letter capitalized, everything else does not

---
##### Data variable names
 All data variables names follow the following format:
    [m_][s_]\<type\>\<identifier\>
 m_ is used for private s_ is used for static class data
 No need to use both m_ and s_
 Type prefixes:
 - short, int -> i
 - long -> l
 - float -> f
 - double -> d
 - bool -> b
 - CString -> str
 - char -> c
 - char* -> sz
 - pointer -> p\<type\>
 - enum -> e
 - size_t -> n
 - uintptr_t -> a
 - uint\<n\>_t -> u\<n\> (example: uint64_t -> u64)
 - int\<n\>_t -> i\<n\>

 Data fields are never public, and only protected in case inheritance will happen

---
##### Class member organization:

 Methods then attributes in following order of protection:

 - public
 - protected
 - private
 
 Methods will always precede attributes
 Example:

 ```
    class MyClass{
    public:
        int publicFunction(uint8_t u8Param);
    protected:
        void protectedFunction();
    ...

    protected:
        int iData;
    private:
        bool bIsValid;
    }
 ```