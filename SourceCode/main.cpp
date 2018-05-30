#include "headers.h"
struct InputType
{
	double OriginProbabilityDistribution; //信源的概率分布
	int originLength; //信源长度

	int SourceCodeType; //信源编码类型
	int ChannelCodeType; //信道编码类型

	int ChannelType; //信道类型，1表示理想不出错信道，2表示BSC信道
	double ChannelErrorP0; //信道传输字符0的错误概率
	double ChannelErrorP1; //信道传输字符1的错误概率
};
void ProgramExplain(InputType I); //程序的运行说明
InputType InputInformation();
void run();
void PutResult();
string IntToString(int n);


int main()
{
	InputType InputInfo;  //存储输入信息的变量
	InputInfo = InputInformation();
	ProgramExplain(InputInfo);  //程序运行说明
	cout << endl << endl << endl;
	Source source(InputInfo.OriginProbabilityDistribution);
	string original = source.generate(InputInfo.originLength);  //产生随机信源
	string originStr = original;
	cout << "!---随机信源产生" << InputInfo.originLength << "长的信息为---!" << endl;
	cout << originStr << endl << endl;
	//计算各个字符的频数给Huffman 和fano编码
	SourceCodeUtil sourcecode(originStr);
	ChannelCodeUtil channel;
	ChannelBSC BSC;
	string sourceEncodeResult = sourcecode.encode(InputInfo.SourceCodeType);
	//信源编码
	cout << "!---信源编码后的信息为---!" << endl << endl;
	cout << sourceEncodeResult << endl << endl;
	string ChannelEnCodeResult = channel.encode(sourceEncodeResult, InputInfo.ChannelCodeType);
	//信道编码
	cout << "!---信道编码后的信息为---!" << endl << endl;
	cout << ChannelEnCodeResult << endl << endl;
	string ChannelResult = BSC.through(ChannelEnCodeResult, InputInfo.ChannelErrorP0, InputInfo.ChannelErrorP1);
	//通过BSC信道后的信号
	cout << "!---通过有误差信道后的的信息为---!" << endl << endl;
	cout << ChannelResult << endl << endl;
	string ChannelDecodeResult = channel.decode(ChannelResult, InputInfo.ChannelCodeType);
	cout << "!---信道解码后的信息为---!" << endl << endl;
	cout << ChannelDecodeResult << endl << endl;
	string SourceDecodeResult = sourcecode.decode(ChannelDecodeResult, InputInfo.SourceCodeType, sourcecode.sourcefrc);
	cout << "!---信源解码后的信息为---!" << endl << endl;
	cout << SourceDecodeResult << endl << endl;
	cout << "!---谢谢使用-----通信系统仿真结束---!" << endl << endl;
	cout << "!---小猪嘎嘎---!" << endl << endl;
	cout << "!---掌管天堂的空之王者，于地狱唱响荣光之歌---!" << endl << endl;


}

void ProgramExplain(InputType In)
{
	cout << endl << endl;
	cout << "!------------------分割线---------------------!"<< endl ;
	if (In.SourceCodeType == 1)
	{
		cout << "!---您选择的是无编码类型信源编码---!" << endl;
	}
	else
		if (In.SourceCodeType == 2)
		{
			cout << "!---您选择的是二进制的Fano编码器---!" << endl;
		}
		else
			if (In.SourceCodeType == 3)
			{
				cout << "!---您选择的是Huffman编码器---!" << endl;
			}
	if (In.ChannelCodeType == 1)
	{
		cout << "!---您选择的是：无编码信道编码器---!" << endl;
	}
	else
		if (In.ChannelCodeType == 2)
		{
			cout << "!---您选择的是：3次重复信道编码器---!" << endl;
		}
		else
		{
			cout << "!---您选择的是：Hamming(7, 4)信道编码器---!" << endl;
		}
	if (In.ChannelType == 1)
	{
		cout << "!---您选择的是：理想信道---!" << endl;
	}
	else
	{
		cout << "!---您选择的是：BSC信道---!" << endl<< endl;
	}
	cout << "程序输入完成是否继续执行" << endl << "继续执行：y" << endl << "退出：n" << endl;
	char c = getchar();
        c = getchar();
	if (c == 'y' || c == 'Y')
	{
		cout << "!---程序继续执行---!" << endl;
	}
	else
	{
		cout << "!---退出程序---!" << endl;
		exit(0);
	}

}

InputType InputInformation()
{
	InputType result;
	cout << "!---1.  请输入离散信源的分布概率---!" << endl;
	//cout << "Huffman压缩编码";
	cout << "!---此概率表示信源产生0符号的概率---!" << endl;
	cin >> result.OriginProbabilityDistribution;

	cout << "!---2. 请输入信源长度---!" << endl;
	cin >> result.originLength;

	cout << "!---3. 请输入信源编码器类型---!" << endl;
	cout << "!---1代表：无编码直接传输---!" << endl;
	cout << "!---2代表：二进制香农费诺编码---!" << endl;
	cout << "!---3代表：二进制Huffman编码---!" << endl;
	cin >> result.SourceCodeType;

	cout << "!---4. 请输入信道编码类型---!" << endl;
	cout << "!---1代表：无编码---!" << endl;
	cout << "!---2代表：3次重复编码---!" << endl;
	cout << "!---3代表：Hamming(7, 4)编码---!" << endl;
	cin >> result.ChannelCodeType;

	cout << "!---5. 请输入信道类型---!" << endl;
	cout << "!---1代表：理想信道---!" << endl;
	cout << "!---2代表：BSC信道---!" << endl;
	cin >> result.ChannelType;

	cout << "!---6. 请输入信道对符号0的错误概率---!" << endl;
	cin >> result.ChannelErrorP0;

	cout << "!---7. 请输入信道对符号1的错误概率---!" << endl;
	cin >> result.ChannelErrorP1;

	return result;
}
void run()
{

}
void PutResult()
{

}

string IntToString(int n)
{
	ostringstream streamm;
	streamm << n;    //n为int类型
	return streamm.str();
}
