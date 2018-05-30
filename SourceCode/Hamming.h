
class Hamming
{
public:
	string encode(string src);
	string decode(string src);
private:
	int row;
	int message[4];//信息位
	int S[3]; //校正子
	int e[7]; //纠正子
	int send[7]; //发送的七位码字
	int Y[7]; //收到的七位码字
	int C[7]; //接收到的七位代码
	int get_code[4]; //接收到的四位信息
	int G[4][7] = { { 1,1,0,1,0,0,0 },{ 0,1,1,0,1,0,0 },{ 1,1,1,0,0,1,0 },{ 1,0,1,0,0,0,1 } };
	int H[3][7] = { { 1,0,0,1,0,1,1 },{ 0,1,0,1,1,1,0 },{ 0,0,1,0,1,1,1 } };
	void CreateCode(int array1[4], int array2[4][7]) //生成七位发送的代码
	{
		int i, j, m = 0;
		for (j = 0; j<7; j++)
		{
			for (i = 0; i<4; i++)
			{
				m = (array1[i] * array2[i][j]) ^ m;
			}
			this->send[j] = m;
			m = 0;
		}
	}
	void Syndrome(int array[7], int array1[3][7]) //得出矫正子S
	{
		int k = 0, a, b;
		for (a = 0; a<3; a++)
		{
			for (b = 0; b<7; b++)
			{
				k = k ^ (array1[a][b] * array[b]);
			}
			this->S[a] = k;
			k = 0;
		}
	}
	void Comp(int array1[3], int array[3][7]) //得出纠正子e
	{
		int i = 0, j = 0, m = 1, p;
		while (m)
		{//j=j+1;
			if ((array1[0] == array[0][i]) && (array1[1] == array[1][i]) && (array1[2] == array[2][i]))
			{
				m = 0;
				row = j;
				for (p = 0; p<7; p++)
				{
					if (p == row)
					{
						this->e[p] = 1;
					}
					else
					{
						this->e[p] = 0;
					}
				}
			}
			else
			{
				j = j + 1; i++;
				if (i == 7)
				{
					for (p = 0; p<7; p++)
					{
						this->e[p] = 0;
					}
					m = 0;
				}
			}
		}
	}
	void CorrectCode(int array3[7], int array4[7]) //得出正确的码字
	{
		int z;
		for (z = 0; z<7; z++)
		{
			this->C[z] = this->Y[z] ^ this->e[z];
		}
		for (z = 0; z<4; z++)
		{
			this->get_code[z] = this->C[z + 3];
		}
	}
	string IntToString(int n)
	{
		ostringstream stream;
		stream << n;    //n为int类型
		return stream.str();
	}
};

string Hamming::encode(string src)
{
	string  result;  //存储结果
	int length = src.length();  //字符串长度
	int segment = length / 4;  //每四个分成一段共有多少整段
	for (int i = 0; i < segment; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (src.at(4 * i + j) == '0')
			{
				this->message[j] = 0;
			}
			else
			{
				this->message[j] = 1;
			}
		}
		this->CreateCode(this->message, this->G);
		for (int j = 0; j < 7; j++)
		{
			result = result + this->IntToString(this->send[j]);
		}
	}
	//不足思位的后面余数位不进行编码，直接传输
	for (int i = 4 * segment; i < length; i++)
	{
		result.push_back(src.at(i));
	}

	return result;
}

string Hamming::decode(string src)
{
	string result;
	int length = src.length();  //通过信道后的码长
	int segment = length / 7;   //每7位作为一段，一共有几段

	for (int i = 0; i < segment; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (src.at(4 * i + j) == '0')
			{
				this->Y[j] = 0;
			}
			else
			{
				this->Y[j] = 1;
			}
		}
		this->Syndrome(this->Y, this->H);
		this->Comp(this->S, this->H);
		this->CorrectCode(this->Y, this->e);
		for (int j = 0; j < 4; j++)
		{
			result = result + this->IntToString(get_code[j]);
		}
	}
	//将剩余的不足7位的(其实只有不到4位的数)原样送回。
	for (int i = 7 * segment; i < length; i++)
	{
		result.push_back(src.at(i));
	}
	return result;
}
