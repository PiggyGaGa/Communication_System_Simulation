class Fano
{
public:
	struct FanoNode
	{
		unsigned char value; // 字符
		struct FanoNode *Lchild = NULL;  //左孩子
		struct FanoNode *Rchild = NULL;   //右孩子
	};
private:
	struct CountVector
	{
		unsigned char value;
		int frequency = 0;
		struct FanoNode *nodeAddress = NULL;
	};

private:
	struct FanoCode
	{
		unsigned char value;
		int frequency;
		string code;
		int codelen;
	};
private:
	static bool mysortfunction(CountVector A, CountVector B)
	{  //排序函数
		return A.frequency > B.frequency;
	}
public:
	FanoNode *root;  //存储树的结构
	long int NumOfChar;
	vector<CountVector> charFrequency;  //字符频率
	vector<FanoCode> FanoCodeVec;  //存储Fano码， 包括码长，码字
	Fano();
	void CreateTree(vector<CountVector> charFrequency, FanoNode *rootNode);
	void GetFanoCode(FanoNode* root, int depth);
	string WriteCode(vector<FanoCode> HFCode, string sourceStr);
	string decode(string sourcefile, vector <Sign::Freq> data);
public:
	string encode(string src, vector<Sign::Freq> data);
private:
	void splitVec(vector<CountVector> charFr, vector<CountVector> &charFr1, vector<CountVector> &charFr2);
};

Fano::Fano()
{
	NumOfChar = 0;
}
string Fano::encode(string src, vector<Sign::Freq> data)
{
		string result;
		int flag = 0;
		for (int i = 1; i < src.length(); i++)
		{
			if (src.at(i) == src.at(0))
			{
				flag++;
			}
		}
		if (flag == src.length() - 1)
		{
			return src;
		}
		for (int i = 0; i < data.size(); i++)
		{
			CountVector *temp = new CountVector;
			temp->frequency = data[i].fre;
			temp->value = data[i].num;
			this->charFrequency.push_back(*temp);
		}
		this->root = new FanoNode;
		this->CreateTree(this->charFrequency, this->root);
		this->GetFanoCode(this->root, 0);
		result = this->WriteCode(this->FanoCodeVec, src);
		return result;
}
void Fano::CreateTree(vector<CountVector> charFr, FanoNode *rootNode)
{
	vector<CountVector> buildtree = charFr;
	if (buildtree.size() == 1)
	{
		//root->Lchild = new FanoNode;
		//root->Rchild = new FanoNode;
		rootNode->Lchild = NULL;
		rootNode->Rchild = NULL;
		rootNode->value = buildtree[0].value;

	}
	else
	{
		sort(buildtree.begin(), buildtree.end(), mysortfunction);
		vector<CountVector> charFr1, charFr2;
		splitVec(buildtree, charFr1, charFr2);
		rootNode->Lchild = new FanoNode;
		CreateTree(charFr1, rootNode->Lchild);
		rootNode->Rchild = new FanoNode;
		CreateTree(charFr2, rootNode->Rchild);
		rootNode->value = 0;
	}
	return;
}

void Fano::splitVec(vector<CountVector> charFr, vector<CountVector> &charFr1, vector<CountVector> &charFr2)
{
	int length = charFr.size();
	if (length == 1)
	{
		cout << "拆分的数组长度不够" << endl;
	}
	long int NumOfCharf = 0;
	for (int i = 0; i < length; i++)
	{
		NumOfCharf = NumOfCharf + charFr[i].frequency;

	}
	double ratio = 0;
	int splitIndex = 0;  //切割处的索引
	for (int i = 0; i < length; i++)
	{
		ratio = ratio + double(charFr[i].frequency / NumOfCharf);
		if (ratio > 0.5)
		{
			if (i > 0)
			{
				splitIndex = i - 1;
				break;
			}
			else
			{
				splitIndex = i;
				break;
			}

		}
	}

	for (int i = 0; i < splitIndex + 1; i++)
	{
		charFr1.push_back(charFr[i]);
	}
	for (int i = splitIndex + 1; i < charFr.size(); i++)
	{
		charFr2.push_back(charFr[i]);
	}
}

void  Fano::GetFanoCode(FanoNode* root, int depth)
{
	static char code[512];
	//ÅÐ¶Ï×ó¶ù×Ó
	if (root->Lchild != NULL)
	{
		code[depth] = '0';
		code[depth + 1] = '\0';
		GetFanoCode(root->Lchild, depth + 1);
	}
	if (root->Rchild != NULL)
	{
		code[depth] = '1';
		code[depth + 1] = '\0';
		GetFanoCode(root->Rchild, depth + 1);
	}
	else
	{
		FanoCode insertCode;
		int codelength = 0;
		for (int i = 0; i < charFrequency.size(); i++)
		{
			if (root->value == charFrequency[i].value)
			{
				insertCode.code = code;
				insertCode.value = charFrequency[i].value;
				insertCode.frequency = charFrequency[i].frequency;
			}
		}
		for (int j = 0; code[j] != '\0'; j++)
		{
			codelength++;
		}
		insertCode.codelen = codelength;
		FanoCodeVec.push_back(insertCode);

	}

}

string Fano::WriteCode(vector<FanoCode> HFCode, string str)
{

	string result = "";
	for (int i = 0; i < str.length(); i++)
	{
		unsigned char temp;
		temp = str.at(i);
		for (int j = 0; j < HFCode.size(); j++)
		{
			if (temp == HFCode[j].value)
			{
				result = result + HFCode[j].code;
				break;
			}
		}
	}
	return result;
}

string Fano::decode(string sourcefile, vector <Sign::Freq> data)
{
	string result;
	int flag = 0;
	for (int i = 1; i < sourcefile.length(); i++)
	{
		if (sourcefile.at(i) == sourcefile.at(0))
		{
			flag++;
		}
	}
	if (flag == sourcefile.length() - 1)
	{
		return sourcefile;
	}
	for (int i = 0; i < data.size(); i++)
	{
		CountVector *temp = new CountVector;
		temp->frequency = data[i].fre;
		temp->value = data[i].num;
		this->charFrequency.push_back(*temp);
	}
	this->root = new FanoNode;
	this->CreateTree(this->charFrequency, this->root);
	this->GetFanoCode(this->root, 0);
	FanoNode *pNow = this->root;   // 当前所在的位置为root
	for (int i = 0; i < sourcefile.length(); i++)
	{
		unsigned char *temp = new unsigned char;
		if (sourcefile.at(i) == '0')
		{
			pNow = pNow->Lchild;
		}
		else
		{
			pNow = pNow->Rchild;
		}
		if (pNow->Lchild == NULL && pNow->Rchild == NULL)
			{
			result.push_back(pNow->value);
			pNow = this->root;
			}
	}
	return result;
}
