# Wav音频格式分析

写了一个类,简单提取wav里的信息和数据


Wave结构:

| 数据类型 | 数据长度 | 功能 |
| :---- | :---- | :---- |
|RIFF层|
|char|4|"RIFF"标志|
|uint32_t|4|剩余文件长度|
|char|4|"WAVE"标志|
|FMT层|
|char|4|"fmt "标志|
|uint32_t|4|音频文件参数的长度|
|uint16_t|2|音频格式类别|
|uint16_t|2|通道数|
|uint32_t|4|采样率|
|uint32_t|4|波形音频数据传送速率|
|uint16_t|2|数据块的调整数|
|uint16_t|2|每样本的数据位数|
|LIST层(可能有,需做判断)|
|uint32_t|4|文件信息长度|
|char|N|文件信息|
|data层|
|char|4|"data"标志|
|uint32_t|4|数据大小|
|char|N|数据内容|


参考:
[[CSDN]Python0019 音频处理（二）.wav文件](https://blog.csdn.net/Moluth/article/details/79820978)
