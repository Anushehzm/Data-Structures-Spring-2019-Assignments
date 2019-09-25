#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include "fstream"
#include "iostream"
#include "chrono"


Dictionary::Dictionary() {
	wordsTree= new BST<string>; 
}

Dictionary::~Dictionary(){
    wordsTree->~BST();
}

void Dictionary::initialize(string wordsFile) {
	ifstream filex (wordsFile);
	string word;
	if (filex.is_open())
	{
		int count=0;
		//cout<<"File " << wordsFile<<" opened. Now populating tree."<<endl;
		while (getline(filex, word))
		{
			count++;
		//	cout<<"Inserting: "<<word<<endl;
			insertWord(word);
		}
		//cout<<"Number of words inserted: "<<count<<endl;
		cout<<"Closing file."<<endl;
		filex.close();
	}
	else
	{
		cout<<"File didn't open."<<endl;
	}
}

bool Dictionary::deleteWord(string word) {
	wordsTree->delete_node(word);
	return false;
}
bool Dictionary::editWord(string oldWord, string newWord) {
	deleteWord(oldWord);
	insertWord(newWord);
	return false;
}
bool Dictionary::insertWord(string word) {
	wordsTree->insert("",word);
	return false;
}

node<string>* Dictionary::findWord(string word) {///return wordsTree->search(word);
	cout<<"Finding "<<word<<endl;
	
    auto start =chrono::steady_clock::now();
    node<string>* w= wordsTree->search(word);
    auto end=chrono::steady_clock::now();
    
    cout << "findWord() took " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds to search for " << word << endl; 
    //cout<<chrono::duration_cast<chrono::nanoseconds>(end-start).count()<<endl;
    return w; // TODO
}

#endif

int main() {
	cout<<"Populating AVL:"<<endl;
	Dictionary dic;
	dic.initialize("words.txt");
	cout<<"AVL Word Time Testing:"<<endl;
	//node<string>* a= dic.findWord("nemoricole");
	dic.findWord("alvarado");
	dic.findWord("baastan");
	dic.findWord("crotalidae");
	dic.findWord("discriminatorily");
	dic.findWord("eee");
	dic.findWord("fingerspin");
	dic.findWord("geognosist");
	dic.findWord("heliometrically");
	dic.findWord("itinerate");
	dic.findWord("jollytail");	
	dic.findWord("kamseen");
	dic.findWord("lokman");
	dic.findWord("muysca");
	dic.findWord("nooksack");
	dic.findWord("oooo");
	dic.findWord("poore");
	dic.findWord("qophs");
	dic.findWord("ruggle");
	dic.findWord("scutibranchia");
	dic.findWord("through-other");
	dic.findWord("unbalanceably");
	dic.findWord("vanmen");
	dic.findWord("waafs");
	dic.findWord("xx");
	dic.findWord("yukoner");
	dic.findWord("zeekoe");
	return 0;
}
