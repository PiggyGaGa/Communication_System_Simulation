class SourceCodeUtil
{
private:

	string IntToString(int n)
	{
		ostringstream streamm;
		streamm << n;    //n为int类型
		return streamm.str();
	}
public:

	string source;
	vector<Sign::Freq> sourcefrc;
	vector<Sign::Freq> count(string s);
	SourceCodeUtil(string srcStr);
	string encode(int type);
	string decode(string decodeString, int type, vector<Sign::Freq> data);
};

SourceCodeUtil::SourceCodeUtil(string srcStr)
{
	this->source = srcStr;
	this->sourcefrc = this->count(srcStr);
};
string SourceCodeUtil::encode(int type)
{
	vector<Sign::Freq> vdata = this->sourcefrc;
	string sourceStr = this->source;
	string strResult;
	Fano fa;
	Huffman hf;
	switch (type)
	{
	case 1:
		//无编码
		strResult = sourceStr;
		break;
	case 2:
		//二进制fano编码
		strResult = fa.encode(sourceStr, vdata);
		break;
	case 3:
		strResult = hf.encode(sourceStr, vdata);
		break;
	default:
		cout << "没有对应的信道" << endl;
		exit(0);
		break;
	 }

	return strResult;
}

vector<Sign::Freq> SourceCodeUtil::count(string s)
{
	vector<Sign::Freq> re;
	for (int i = 0; i < s.length(); i++)
	{
		int flag = 0; //0表示没出现过
		for (int j = 0; j < re.size(); j++)
		{
			if (s.at(i) == re[j].num)
			{
				re[j].fre++;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			Sign::Freq *single = new Sign::Freq;
			single->fre++;
			single->num = s.at(i);
			re.push_back(*single);
		}
	}
	return re;
}


string SourceCodeUtil::decode(string decodeString, int type, vector<Sign::Freq> data)
{
	string DecodeResult;
	Fano  fa;
	Huffman huf;
	switch (type)
	{
	case 1:
		DecodeResult = decodeString;
		break;
	case 2:
		DecodeResult = fa.decode(decodeString, data);
		break;
	case 3:
		DecodeResult = huf.decode(decodeString, data);
		break;
	default:
		cout << "没有对应的信道"  << endl;
		exit(0);
	}
	return DecodeResult;

}
