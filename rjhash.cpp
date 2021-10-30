#include<iostream>
#include<fstream>
#include<string>
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::default_delete;
using std::hash;
const int HASHSIZE = 4001;

struct entry
{
	string word;
	int freq = 0;           //initalize freq to 0 for all keys
};

class Hash
{
public:
	entry hasharray[HASHSIZE];
	int updates[HASHSIZE] = {};     //initalize both arrays to 0
	int cost[HASHSIZE] = {};
	int size, probe, num = 0;
	Hash() { hasharray; size, probe, num; updates; cost; }
	~Hash() { delete hasharray; }
	int getsize()
	{
		return size;
	}
	int getprobes()
	{
		return probe;
	}
	int hashkey(string str)
	{
		int hk = hash<string>()(str) % HASHSIZE;    //built in hash function
		return hk;
	}
	void update(string str)
	{
		int key = hashkey(str);   //find hashkey of the input string
		probe = 0;
		num = 0;
		size = 0;				  //initalize all stats ints to 0
		if (hasharray[key].freq == 0)   //not present
		{
			hasharray[key].freq++;
			hasharray[key].word = str;
			size++; probe++; num++;
		}
		else if (hasharray[key].word == str)     //word present
		{
			hasharray[key].freq++;
			probe++;
		}
		else 
		{
			while (hasharray[key].freq != 0 && hasharray[key].word != str)    //linear probing
			{                                                                 
				key++;
				probe++;
			}
			if (hasharray[key].word == str) {
				hasharray[key].freq++;
				probe++;
			}
			else
			{
				hasharray[key].word = str;
				hasharray[key].freq++;
				size++; num++; probe++;
			}
		}
		updates[size] = num;  //update the 2 stats arrays
		cost[size] = probe;

	}
	
};

void print(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << endl;
	}
}

int main()
{
	Hash hash1;
	string randj;
	string word, filename;
	fstream myfile;
	filename = "RomeoAndJuliet.txt";
	myfile.open(filename.c_str());
	while (myfile >> word)      //read the file word by word
	{
		hash1.update(word);     //update the hasharray with the word that was just read
	}

	cout << "number of unique words: "; print(hash1.updates, HASHSIZE); cout<<endl;
	cout << "cost: "; print(hash1.cost, HASHSIZE); cout << endl;


	return 0;
}