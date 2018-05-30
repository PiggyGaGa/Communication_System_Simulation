class Source
{
private:

public:
	double probability; //信源分布概率
	Source(double probability);
	string generate(int length);  //产生随机信源
};

Source::Source(double probability)
{
	this->probability = probability;
}

string Source::generate(int length)
{
	string result;
	srand((unsigned)time(NULL));
	if (length == 0)
	{
		return "";
	}
	for (int i = 0; i < length; i++)
	{
		double x;
		x = double(rand() / (RAND_MAX + 0.0));
		if (x <= this->probability)
		{
			result.push_back('1');
		}
		else
		{
			result.push_back('0');
		}
	}
	return result;
}
