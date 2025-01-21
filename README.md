# Levypy

A Simple Python Driver for LevelDB

It has simple API to  LevelDB like insert key/value, delete key and get key/value
It uses default write/read options for simple access.

It is pretty fast since it is built using cython/c++
It has forward iteration and reverse iteration of keys. During iteration, there are ways to delete Key/Value and modify the Value.

## - Installation
Currently it is a beta version. it is available from testpypi distribution (only linux package).
```shell
pip install -i https://test.pypi.org/simple/ levypy==0.1.0
```

## - How to use
#### To create/open leveldb database
```python
import levypy
db= levypy.DB("t.db")
```
#### Insert or Modify a Key and Value using Put() 
```python
db.Put(b'key',b'value')
db.Put(b'key',b'Modified value')
```
#### Get Key/Value
```python
v=db.Get(b'key')
```

#### Delete Key/Value
```python
db.Del(b'key')
```

#### Forward Iteration
```python
dbi=db.Forward()
for k,v in dbi:
    print(k,'=',v)
```

#### Reverse Iteration
```python
dbi=db.Reverse()
for k,v in dbi:
    print(k,'=',v)
```
    
#### Delete existing Key/Val while on forward/reverse iteration
```python
db.Put(b'delete-key',b'Value will be deleted')
dbi=db.Forward()
#dbi=db.Reverse()
for k,v in dbi:
    if(k==b'delete-key'):
        dbi.Remove(k)
```

#### Modify Value of existing Key while forward/reverse
```python
db.Put(b'key',b'Value')
dbi=db.Forward()
for k,v in dbi:
    if(k==b'key'):
        dbi.Modify(k,b"Modified")
```

#### Insert binary key and binary value 
```python
k=binascii.a2b_hex("01020304")
v=binascii.a2b_hex("b5b6b7b8")
db.Put(k,v)
```
