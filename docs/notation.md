Comments at beggining of each file(will get to it)

All methods and data members have preceding comment(s) describing them and their use

Classes, methods and functions:	CamelCase

Data variables:	[m_]\<type\>\<identifier\>

> m_ is used for private class data
>
> type:
>
>> - short, int - i
>> - long - l
>> - float - f
>> - double - d
>> - bool - b
>> - CString - str
>> - char - c
>> - char* - sz
>> - pointer  - p\<type\>
>> - enum - e
>> - size_t - n
>> - uintptr_t - a
>> - uint\<n\>_t - u\<n\>
>> - int\<n\>_t - i\<n\>
>>
>
> Data variables are never public, and only protected in case inheritance will happen

Class member organization:

> Methods then attributes in following order of protection:
>
>> - public
>> - protected
>> - private
>>

---
