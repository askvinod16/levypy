
from libcpp.string cimport string
from CLevelDbWrapper cimport CLevelDbWrapper
from CLevelDbWrapper cimport CLevelDbIterator

cdef class DB:
    cdef CLevelDbWrapper*db  # db instance
    cdef CLevelDbIterator * itr

    def __cinit__(self,dname):
        self.db = new CLevelDbWrapper()
        cdef string dn=dname.encode('utf-8')
        self.db.Connect(dn)
    
    def Put(self,bytes key, bytes value):
        cdef string k=key
        cdef string v=value
       
        self.db.PutString(k,v)
    def Get(self,bytes key):
        cdef string k=key
        cdef string v
        v = self.db.GetString(k)
        return bytes(v)
    def Del(self,bytes key):
        cdef string k=key
        self.db.Delete(k)
    

    def __del__(self):
        #print("Disconnecting from leveldb")
        self.db.Disconnect()
        del self.db
    

    def Forward(self):
        it=levypyForwardIterator()
        it.itr=self.db.Begin()
        return it
    def Reverse(self):
        it=levypyReverseIterator()
        it.itr=self.db.End()
        return it

    
        
cdef class  levypyForwardIterator:
    cdef CLevelDbIterator * itr
    
    
    def __iter__(self):        
        return self
    def __next__(self):        
        if(self.itr==NULL):
            raise StopIteration
        cdef string k
        cdef string v
        
        if(self.itr.GetAndNext(k,v)):
            return bytes(k),bytes(v)
        else:
            self.itr.WriteBatch()
            del self.itr  
            self.itr=NULL          
            raise StopIteration
    def Modify(self,bytes key, bytes value):
        if(self.itr==NULL):
            return
        cdef string k=key
        cdef string v=value
        self.itr.Put(k,v)
    def Remove(self,bytes key):
        if(self.itr==NULL):
            return
        cdef string k=key
        self.itr.Del(k)
        

cdef class  levypyReverseIterator:
    cdef CLevelDbIterator * itr
    
    
    def __iter__(self):
        
        return self
    def __next__(self):
        if(self.itr==NULL):
            raise StopIteration        
        cdef string k
        cdef string v
        if(self.itr.GetAndPrev(k,v)):
            return bytes(k),bytes(v)
        else:
            self.itr.WriteBatch()
            del self.itr
            raise StopIteration
    def Modify(self,bytes key, bytes value):
        if(self.itr==NULL):
            return
        cdef string k=key
        cdef string v=value
        self.itr.Put(k,v)
    def Remove(self,bytes key):
        if(self.itr==NULL):
            return
        cdef string k=key
        self.itr.Del(k)

    #def __dealloc__(self):
    #    del self.c_rect
