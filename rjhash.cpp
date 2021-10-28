#include<iostream>
#include<fstream>
#include<string>
using std::cout;
using std::endl;
using std::string;
using std::fstream;

const int HASHSIZE = 4001;
struct entry
{
	string word;
	int freq;
};

class Hash
{
public:
	entry hasharray[HASHSIZE];
	int updates[HASHSIZE];
	int cost[HASHSIZE];
	int size, probe, num = 0;
	Hash() { hasharray; }
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
		std::hash<string>()(str);    //built in hash function
	}
	void update(string str)
	{
		int key = hashkey(str);   //find hashkey of the input string
		size = 0;
		probe = 0;				  //initalize probe to 0
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
			{                                                                 //should be key instead of str
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
				size++; num++; probe++;
			}
		}
		updates[size] = num;  //update the 2 stats arrays
		cost[size] = probe;

	}
	
};

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
		hash1.update(word);   //update the hasharray with the word that was just read
	}

	cout << "number of unique words: " << hash1.updates << endl;
	cout << "cost: " << hash1.cost;


	return 0;
}