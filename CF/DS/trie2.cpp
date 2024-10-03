#include <bits/stdc++.h>
using namespace std;

struct node
{
    node *links[26];
    bool isEnd;

    bool containsKey(char ch)
    {
        return links[ch - 'a'] != NULL;
    }

    void put(char ch, node* Node)
    {
        links[ch - 'a'] = Node; 
    }

    node* get(char ch)
    {
        return links[ch - 'a'];
    }

    void setEnd()
    {
        isEnd = true;
    }
};

class trie
{
private:
    node *root;

public:
    trie(){
        root = new node();
    }

    void insert(string word){
        node* root = this->root;
        for(int i=0; i<word.length(); i++)
        {
            if(!root->containsKey(word[i]))
            {
                root->put(word[i], new node());
            }
            root = root->get(word[i]);
        }
        root->setEnd();
    }

    bool search(string word){
        node* root = this->root;
        for(int i=0; i<word.length(); i++)
        {
            if(!root->containsKey(word[i]))
            {
                return false;
            }
            root = root->get(word[i]);
        }
        return root->isEnd; 
    }
};