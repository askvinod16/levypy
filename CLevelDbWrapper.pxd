# cython: language_level=3
# distutils: language = c++
from libcpp.string cimport string
from libcpp cimport bool
cdef extern from "src/levypy/cpp/src/LevelDbWrapper.cpp":
    pass

cdef extern from "src/levypy/cpp/include/LevelDbWrapper.h":
    cdef cppclass CLevelDbIterator:
        bool GetAndNext(string&key, string&value)
        bool GetAndPrev(string&key, string&value)
        bool Put(string&key, string&value)
        bool Del(string&key)
        void WriteBatch()
    cdef cppclass CLevelDbWrapper:
        CLevelDbWrapper() except+
        void Connect(string& dbname)
        void Disconnect()
        bool PutString(string& k,string & v)
        bool PutString(int k,string & v)
        string GetString(string& k)
        string GetString(int k)
        CLevelDbIterator * Begin()
        CLevelDbIterator * End()
        void Delete(string& k)
    