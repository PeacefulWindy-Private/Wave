#include "Wave.h"
#include<stdio.h>
#include<string.h>

const int32_t DATA_BLOCK_SIZE = 10240;

Wave::Wave()
{

}

Wave::Wave(std::string path)
{
    this->loadFromFile(path);
}

Wave::~Wave()
{
    this->release();
}

bool Wave::loadFromFile(std::string path)
{
    FILE * file=nullptr;

    if(this->isLoad())
    {
        return false;
    }

    this->mInfo.reset(new WaveInfo);

    file=fopen(path.c_str(),"r");

    if(!file)
        return false;

    auto info=this->mInfo.get();
    fseek(file,0,SEEK_END);
    long fileLen=ftell(file);
    fseek(file,0,SEEK_SET);

    long waveInfoLen=sizeof(WaveInfo);

    if(fileLen<waveInfoLen)
    {
        fclose(file);
        return false;
    }

    fread(info,sizeof(WaveInfo),1,file);

    char head[4]={'\0'};
    int32_t len;
    fread(head,sizeof(char),4,file);
    if(strcmp(head,"LIST")==0)
    {
        fread(&len,sizeof(int32_t),1,file);
        fseek(file,len,SEEK_CUR);
        fread(head,sizeof(char),4,file);
    }
    if(strcmp(head,"data")==0)
    {
        fread(&this->mDataLen,sizeof(int32_t),1,file);
        this->mData=new char[this->mDataLen];
        int32_t len=0;
        while(len+DATA_BLOCK_SIZE<this->mDataLen)
        {
            auto rlen=fread(this->mData+len,sizeof(char),DATA_BLOCK_SIZE,file);
            if(static_cast<int32_t>(rlen)!=DATA_BLOCK_SIZE)
            {
                fclose(file);
                return false;
            }
            len+=DATA_BLOCK_SIZE;
        }
        auto rlen=fread(this->mData,sizeof(char),static_cast<size_t>(this->mDataLen-len),file);

        if(static_cast<int32_t>(rlen)!=this->mDataLen-len)
        {
            fclose(file);
            return false;
        }
    }
    fclose(file);

    return true;
}

bool Wave::isLoad()
{
    return this->mData?true:false;
}

const char *Wave::data()
{
    return this->mData;
}

int32_t Wave::length()
{
    return this->mDataLen;
}

void Wave::release()
{
    if(this->mInfo.get())
    {
        this->mInfo.release();
    }
    if(this->mData)
    {
        delete[] this->mData;
        this->mData=nullptr;
    }
}
