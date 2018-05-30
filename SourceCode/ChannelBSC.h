class ChannelBSC
{
public:
	string through(string src, double p0, double p1);
};

string ChannelBSC::through(string src, double p0, double p1)
{
	string re;
	srand((unsigned)time(NULL));
	for (int i = 0; i < src.length(); i++)
	{
		char temp = src.at(i);
		if (temp == '0')
		{
			double x = double(rand() / (RAND_MAX + 0.0));
			if (x < p0)
			{
				re.push_back('1');
			}
			else
			{
				re.push_back('0');
			}
		}
		else
		{
			double x = double(rand() / (RAND_MAX + 0.0));
			if (x < p1)
			{
				re.push_back('0');
			}
			else
			{
				re.push_back('1');
			}
		}
	}

	return re;
}
