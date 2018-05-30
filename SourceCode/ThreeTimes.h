class ThreeTimes
{
public:
	string encode(string src);
	string decode(string src);
private:
	char Correct(char a, char b, char c);
};

string ThreeTimes::encode(string src)
{
	int length = src.length();
	string result;
	for (int i = 0; i < length; i++)
	{
		result.push_back(src.at(i));
		result.push_back(src.at(i));
		result.push_back(src.at(i));
	}
	return result;
}
string ThreeTimes::decode(string src)
{
	string result;
	int length = src.length();
	for (int i = 0; i < length; i = i + 3)
	{
		char temp = this->Correct(src.at(i), src.at(i + 1), src.at(i + 2));
		result.push_back(temp);
	}

	return result;
}
char ThreeTimes::Correct(char a, char b, char c)
{
	int num0 = 0, num1 = 0;
	if (a == '1')
	{
		num1++;
	}
	else
	{
		num0++;
	}
	if (b == '1')
	{
		num1++;
	}
	else
	{
		num0++;
	}
	if (c == '1')
	{
		num1++;
	}
	else
	{
		num0++;
	}

	if (num0 > num1)
	{
		return '0';
	}
	else
		if (num0 < num1)
		{
			return '1';
		}
		else
		{
			cout << "信息错误，出现非0或1的符号";
			exit(0);
		}

}
