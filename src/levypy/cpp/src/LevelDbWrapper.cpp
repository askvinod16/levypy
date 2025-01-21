/*
 *
 *
 */

#include "../include/LevelDbWrapper.h"



void CLevelDbWrapper::Connect(std::string &dbname)
{
    mOptions.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(mOptions, dbname.c_str(), &mDb);
    if (false == status.ok())
    {
        cerr << "Unable to open/create leveldb database "<< dbname << endl;
        cerr << status.ToString() << endl;
        return ;
    }
}

void CLevelDbWrapper::Disconnect()
{
    delete mDb;
}

bool CLevelDbWrapper::PutString(std::string &k, std::string &v)
{
    leveldb::WriteOptions writeOptions;
    leveldb::Status s;
    s=mDb->Put(writeOptions, k,v );
    return s.ok();
}

bool CLevelDbWrapper::PutString(int k, std::string &v)
{
    std::string kstr;
    kstr.append((char *)(&k) ,sizeof(k));

    return PutString(kstr,v);
}

bool CLevelDbWrapper::PutBinary(std::string &k, std::string &v)
{
    
    return PutString(k,v);
}
std::string  CLevelDbWrapper::GetString(std::string &k)
{
    std::string value;
    leveldb::Status s = mDb->Get(leveldb::ReadOptions(), k, &value);   
    return value;
}

std::string  CLevelDbWrapper::GetString(int k)
{
    std::string kstr;
    kstr.append((char *)(&k),sizeof(k));
    
    return GetString(kstr);
}

std::string CLevelDbWrapper::GetBinary(std::string &k)
{

    return GetString(k);
}

CLevelDbIterator *CLevelDbWrapper::Begin()
{
    leveldb::Iterator* lit = mDb->NewIterator(leveldb::ReadOptions());
    lit->SeekToFirst();
    CLevelDbIterator * itr = new CLevelDbIterator(lit,mDb); 
    return itr;
}

CLevelDbIterator *CLevelDbWrapper::End()
{
    leveldb::Iterator* lit = mDb->NewIterator(leveldb::ReadOptions());
    lit->SeekToLast();
    CLevelDbIterator * itr = new CLevelDbIterator(lit,mDb); 
    return itr;
}

void CLevelDbWrapper::Delete(int k)
{
     std::string kstr;
    kstr.append((char *)(&k),sizeof(k));
    Delete(kstr);
}
void CLevelDbWrapper::Delete(std::string &k)
{
    mDb->Delete(leveldb::WriteOptions(), k);
}
void CLevelDbWrapper::LoadPrint()
{
    cout << "Start iterating\n";
    CLevelDbIterator *itr=Begin();
    std::string key;
    std::string value;
    while ( itr->GetAndNext(key,value)) {
        cout << key << ": "  << value << endl;
    }
    //assert(it->status().ok());  // Check for any errors found during the scan
    delete itr;
}

CLevelDbIterator::CLevelDbIterator(leveldb::Iterator *it,leveldb::DB * db)
{
    mItr =it;
    mDb= db;
    mIsBatchWritten=false;
}

bool CLevelDbIterator::Next()
{
    bool ret=false;
    if(mItr->Valid()) {
        mItr->Next();
        ret=true;
    }
        
    return ret;

}

bool CLevelDbIterator::Valid()
{
    return mItr->Valid();
}

bool CLevelDbIterator::Previous()
{
    bool ret=false;
    if(mItr->Valid()) {
        mItr->Prev();
        ret=true;
    }
    return ret;
    
}

bool CLevelDbIterator::Get(std::string &key, std::string &value)
{
     bool ret=false;
    if(mItr->Valid()) {
       key=mItr->key().ToString();
       value=mItr->value().ToString();
       ret=true;
    }
    return ret;
}

bool CLevelDbIterator::GetAndNext(std::string &key, std::string &value)
{
   bool ret=false;
   if(Get(key,value)) {
    ret=Next();
   }
   return ret;
}

bool CLevelDbIterator::GetAndPrev(std::string &key, std::string &value)
{
   bool ret=false;
   if(Get(key,value)) {
    ret=Previous();
   }
   return ret;
}

bool CLevelDbIterator::Put(std::string &key, std::string &value)
{
    mIsBatchWritten=true;
    mBatch.Put(key,value);
    return true;
}

bool CLevelDbIterator::Del(std::string &key)
{
    mIsBatchWritten=true;
    mBatch.Delete(key);
    return true;
}
