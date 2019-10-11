#ifndef WAVE_H0
#define WAVE_H

#include<memory>
#include<string>

//https://blog.csdn.net/Moluth/article/details/79820978

struct WaveInfo
{
    char mRiffFlag[4];//"RIFF"标志
    uint32_t mFileLen;//文件长度
    char mWaveFlag[4];//"WAVE"标志
    char mFmtFlag[4];//"fmt"标志
    uint32_t mAudioParamLen;//音频文件参数的长度
    uint16_t mFormatTag;//格式类别
    uint16_t mChannels;//通道数
    uint32_t mSampleRate;//采样率
    uint32_t mAvgBytesPerSec;//波形音频数据传送速率
    uint16_t mBlockSize;//数据块的调整数
    uint16_t mnBitNumPerSample;//每样本的数据位数
};

class Wave
{
public:
    Wave();
    Wave(std::string path);
    ~Wave();
public:
    bool loadFromFile(std::string path);
    bool isLoad();
public:
    const char * data();
    uint32_t length();
public:
    uint16_t channels();
    uint32_t sampleRate();

private:
    std::unique_ptr<WaveInfo> mInfo;
    char* mData=nullptr;
    uint32_t mDataLen=0;

private:
    void release();
};

#endif // WAVE_H
