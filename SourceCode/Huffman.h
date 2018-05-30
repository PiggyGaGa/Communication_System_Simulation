class Huffman
{
public:
	struct HuffmanNode
	{
		unsigned char value; //节点值
		int frequency = 0; //节点频数
		struct HuffmanNode *Lchild = NULL;
		struct HuffmanNode *Rchild = NULL;

	};
private:
	struct CountVector
	{
		unsigned char value; //字符
		int frequency = 0;  //字符频数
		struct HuffmanNode *nodeAddress = NULL;
	};
	struct HuffmanCode
	{
		unsigned char value;
		int frequency = 0;
		string code;
		int codelen;
	};
	static bool mysortfunction(CountVector A, CountVector B)
	{  //用于sort排序算法
		return A.frequency < B.frequency;
	}
public:
	HuffmanNode *root;
	long int NumOfChar;
	vector<CountVector> charCountFrequency;  //用于存储字符频数
	vector<HuffmanCode> HuffmanCodeVec;
	Huffman();  //构造函数
	string encode(string src, vector<Sign::Freq> data);  //编码函数
	void CreateHuffmanTree(vector<CountVector> charFrequency);  //创建huffman树
	void GetHuffmanCode(HuffmanNode *root, int len);
	string WriteCode(vector<HuffmanCode> hfCode, string str);
	string decode(string src, vector<Sign::Freq>  data);
};

Huffman::Huffman()
{
	NumOfChar = 0;
}

string Huffman::encode(string src, vector<Sign::Freq> data)
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
		this->charCountFrequency.push_back(*temp);
	}
	this->CreateHuffmanTree(this->charCountFrequency);
	this->GetHuffmanCode(this->root, 0);
	result = this->WriteCode(this->HuffmanCodeVec, src);
	return result;
}
void Huffman::CreateHuffmanTree(vector<CountVector> charFrequency)
{
	vector<CountVector>  buildtree;
	//HuffmanNode newNode;
	HuffmanNode *rootnode = new HuffmanNode;
	buildtree = charFrequency;
	sort(buildtree.begin(), buildtree.end(), mysortfunction);
	int treedepth = 0;
	while (buildtree.size() > 1)
	{
		HuffmanNode *nodeLeft = new HuffmanNode,
			*nodeRight = new HuffmanNode,
			*newNode = new HuffmanNode;
		CountVector insertnew;
		if (buildtree[0].nodeAddress != NULL)
		{  //如果是叶子节点的话  左右子树的地址都为NULL
			nodeLeft->Lchild = buildtree[0].nodeAddress->Lchild;
			nodeLeft->Rchild = buildtree[0].nodeAddress->Rchild;
		}
		else
		{
			nodeLeft->Lchild = NULL;
			nodeLeft->Rchild = NULL;
		}
		if (buildtree[1].nodeAddress != NULL)
		{
			nodeRight->Lchild = buildtree[1].nodeAddress->Lchild;
			nodeRight->Rchild = buildtree[1].nodeAddress->Rchild;
		}
		else
		{
			nodeRight->Lchild = NULL;
			nodeRight->Rchild = NULL;
		}
		nodeLeft->frequency = buildtree[0].frequency;
		nodeLeft->value = buildtree[0].value;
		nodeRight->frequency = buildtree[1].frequency;
		nodeRight->value = buildtree[1].value;
		newNode->frequency = nodeRight->frequency + nodeLeft->frequency;
		newNode->Lchild = nodeLeft;
		newNode->Rchild = nodeRight;
		insertnew.frequency = newNode->frequency;
		insertnew.value = 0;
		insertnew.nodeAddress = newNode;
		//vector<CountVector>::iterator it = buildtree.begin();
		buildtree.erase(buildtree.begin());
		//vector<CountVector>::iterator it = buildtree.begin();
		buildtree.erase(buildtree.begin());
		//vector<CountVector>::iterator it = buildtree.begin();
		buildtree.insert(buildtree.begin(), insertnew);
		sort(buildtree.begin(), buildtree.end(), mysortfunction);   //每次更新完要排序
		rootnode = newNode;
		treedepth++;

	}
	//cout << treedepth;
	this->root = rootnode;
}

void  Huffman::GetHuffmanCode(HuffmanNode* root, int depth)
{
	static char code[512];
	//判断左儿子
	if (root->Lchild != NULL)
	{
		code[depth] = '0';
		code[depth + 1] = '\0';
		GetHuffmanCode(root->Lchild, depth + 1);
	}
	if (root->Rchild != NULL)
	{
		code[depth] = '1';
		code[depth + 1] = '\0';
		GetHuffmanCode(root->Rchild, depth + 1);
	}
	else
	{
		HuffmanCode insertCode;
		int codelength = 0;
		for (int i = 0; i < charCountFrequency.size(); i++)
		{
			if (root->value == charCountFrequency[i].value)
			{
				insertCode.code = code;
				insertCode.value = charCountFrequency[i].value;
				insertCode.frequency = charCountFrequency[i].frequency;
			}
		}
		for (int j = 0; code[j] != '\0'; j++)
		{
			codelength++;
		}
		insertCode.codelen = codelength;
		HuffmanCodeVec.push_back(insertCode);

	}

}

string Huffman::WriteCode(vector<HuffmanCode> HFCode, string str)
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

string Huffman::decode(string src, vector<Sign::Freq>  data)
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
		this->charCountFrequency.push_back(*temp);
	}
	this->CreateHuffmanTree(this->charCountFrequency);
	this->GetHuffmanCode(this->root, 0);
	HuffmanNode *pNow = this->root;   // 当前所在的位置为root
	for (int i = 0; i < src.length(); i++)
	{
		unsigned char *temp = new unsigned char;
		if (src.at(i) == '0')
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
