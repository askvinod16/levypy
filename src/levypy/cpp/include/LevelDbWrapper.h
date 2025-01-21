/**
 * @file LevelDbWrapper.h
 *
 * @author Vinod Kumar E
 * @brief 
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef LEVELDBWRAPPER_H 
#define LEVELDBWRAPPER_H 1

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include <mutex>
#include<iostream>
#include<string>

using namespace std;


class CLevelDbIterator {
    public:
        CLevelDbIterator(leveldb::Iterator *it,leveldb::DB * db);
        bool Next();
        bool Valid();
        bool Previous();
        bool Get(std::string&key, std::string&value);
        bool GetAndNext(std::string&key, std::string&value);
        bool GetAndPrev(std::string&key, std::string&value);
        bool Put(std::string&key, std::string&value);
        bool Del(std::string&key);
        void WriteBatch() {
            if(mIsBatchWritten==true)
                leveldb::Status s = mDb->Write(leveldb::WriteOptions(), &mBatch);
        }

        ~CLevelDbIterator() {
            if(mItr!=NULL) {
                
                delete mItr;
            }
        }
    private:
     leveldb::Iterator* mItr;
     leveldb::DB * mDb; 
     leveldb::WriteBatch mBatch;
     bool mIsBatchWritten;
};

class CLevelDbWrapper {


    public:
        CLevelDbWrapper() {}
        void Connect(std::string& dbname);
        void Disconnect();
        bool PutString(std::string& k,std::string & v);
        bool PutString(int k,std::string & v);
        bool PutBinary(std::string&k,std::string& v);
        std::string GetString(std::string& k);
        std::string GetString(int k);
        std::string GetBinary(std::string& k);
        CLevelDbIterator * Begin();
        CLevelDbIterator * End();
        void Delete(int k);
        void Delete(std::string &k);
        void LoadPrint();
    private:
        leveldb::DB* mDb;
        leveldb::Options mOptions;
        

} ;

#endif