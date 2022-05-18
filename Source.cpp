#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class BitVector {
	unsigned char* bytes;
	int nbits;//how many bit present logically
public:
	BitVector(int nb = 728000) {
		nbits = nb;
		int n = ceil(nbits / 8.0);
		bytes = new unsigned char[n];
		for (int i = 0; i < n; i++)
			bytes[i] = 0;//clear everything at start
	}

	void set(int bno) {
		int byten = bno / 8;
		bno = bno % 8;
		unsigned char mask = 0x80;//10000000
		mask = mask >> bno;
		bytes[byten] = bytes[byten] | mask;
	}

	void clear(int bno) {
		int byten = bno / 8;
		bno = bno % 8;
		unsigned char mask = 0x80;
		mask = ~(mask >> bno);//000001000 = 111110111
		bytes[byten] = bytes[byten] & mask;
	}

	bool get(int bno) {
		int byten = bno / 8;
		bno = bno % 8;
		unsigned char mask = 0x80;
		mask = mask >> bno;
		int x = bytes[byten] & mask;
		return (x != 0);
	}

	~BitVector() {
		bytes = nullptr;
		nbits = 0;
	}
};



unsigned long long PowerGenerator(int num, int power) {
	int temp = 1;
	int i = 0;
	while (i < power) {
		temp = temp * num;
		i++;
	}
	return temp;
}

void Time(int i) {
	if (i == 0) {
		cout << "LOADING STATUS: ";
		cout << 0 << "%" << endl;
		
	}
	if (i == 18200) {
		cout << "LOADING STATUS: ";
		cout << 20 << "%" << endl;

	}
	if (i == 36400) {
		cout << "LOADING STATUS: ";
		cout << 40 << "%" << endl;
	}
	if (i == 54600) {
		cout << "LOADING STATUS: ";
		cout << 60 << "%" << endl;
	}
	if (i == 72800) {
		cout << "LOADING STATUS: ";
		cout << 80 << "%" << endl;
	}
	if (i == 90999) {
		cout << "LOADING STATUS: ";
		cout << 100 << "%" << endl;
		
	}

}

class BloomFilter {
	BitVector bvt;
	int a[6];
	int p;
	
public:
	BloomFilter() {
		int j = 0;
		while (j < 6) {
			int n = 0;
			int i = 0;
			while (i < 23) {
				int random = rand() % 2;
				random = random << i;
				n = n | random;
				i++;
			}

			a[j] = n;
			j++;
		}
		p = 16777213;
	}

	bool lookup(string s) {
		int i = 0;
		bool var = true;
		while (i < 6) {
			var = var && bvt.get(function(a[i], s) % 91000);
			i++;
		
		}
		return var;
	}

	void Insertion(string n) {
		int i = 0;
		while (i < 6) {
			bvt.set(function(a[i], n) % 91000);
			i++;
		}
		
		/*bvt.set(function(a[1], n) % 91000);
		bvt.set(function(a[2], n) % 91000);
		bvt.set(function(a[3], n) % 91000);
		bvt.set(function(a[4], n) % 91000);
		bvt.set(function(a[5], n) % 91000);
		*/	
		
	}

	int function(int a, string s) {
		
		int pow = s.length() - 1;
		int num = 0;
		int i = 0;
		while (i < s.length()) {
			num = num + ((s[i]) % p + (PowerGenerator(a, pow) % p)) % p;
			pow--, i++;
		}
		num %= p;
		return num;
	}

	void LoadFile(string text) {
		ifstream fin;
		fin.open(text);
		string word;
		for ( int i=0;i<91000;i++){
			Time(i);
			if (fin.is_open()) {
				getline(fin, word, '\n');

				Insertion(word);
				
			}
		}
		
	}

	~BloomFilter() {
		int i = 0;
		while (i < 6) {
			a[i] = 0;
			i++;
		}
		p = 0;
	}

};

void Print(BloomFilter bloomfilter,string text, string wordd) {
	int i = 0;
	while (i < text.length()) {
		if (text[i] != ' ') {
			wordd.push_back(text[i]);
		}

		if (text[i] == ' ') {

			if (bloomfilter.lookup(wordd)) {
				cout << wordd << " ";
			}
			else {
				cout << "[" << wordd << "]" << " ";
			}
			wordd.resize(0);
		}

		i++;
	}

	if (bloomfilter.lookup(wordd)) {
		cout << wordd << " ";
	}
	else {
		cout << "{" << wordd << "}" << " ";
	}

}

int main() {
	BloomFilter bloomfilter;
	bloomfilter.LoadFile("dict.txt");
	string text;
	cout << "Enter the text you want to enter " << endl;
	getline(cin, text);
	
	string wordd;
	Print(bloomfilter,text, wordd);
	cout << endl;
	
	return 0;
}
