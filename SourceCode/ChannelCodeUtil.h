class ChannelCodeUtil
{
public:
	string encode(string src, int type);

	string decode(string channelthrough, int type);
};

string ChannelCodeUtil::encode(string src, int type)
{
	string result;
	ThreeTimes three;
	Hamming ham;
	switch (type)
	{
	case 1:
		//无编码
		result = src;
		break;
	case 2:
		result = three.encode(src);
		break;
	case 3:
		result = ham.encode(src);
		break;
	default:
		cout << "没有对应的信道" << endl;
		exit(0);
		break;
	}
	return result;
}

string ChannelCodeUtil::decode(string channelthrough, int type)
{
	string DecodeResult;
	ThreeTimes three;
	Hamming ham;
	switch (type)
	{
	case 1:
		//无编码
		DecodeResult = channelthrough;
		break;
	case 2:
		//ThreeTimes编码
		DecodeResult = three.decode(channelthrough);
		break;
	case 3:
		DecodeResult = ham.decode(channelthrough);
		break;
	default:
		cout << "没有对应的信道" << endl;
		exit(0);
		break;
	}
	return DecodeResult;

}
