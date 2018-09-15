#include <iostream>
#include <cstring>

using namespace std;

struct listnode {
	bool push;
	int index;
};

struct node {
	int index;
	node * left;
	node * right;
};

listnode * readlist(listnode * list, int k);
node * addtree(listnode * list, int root, int last);
void treeprt(node * root, bool isroot);

int main(int argc, char const *argv[])
{
	int n;cin >> n;
	listnode * list = new listnode [n*2];
	list = readlist(list,n*2);
	node * tree = addtree(list,0,n*2-1);
	treeprt(tree,true);
	return 0;
}

void treeprt(node * root, bool isroot) {
	if(root->left) treeprt(root->left,false);
	if(root->right) treeprt(root->right,false);
	cout << root->index;
	if (!isroot) cout << ' ';
}

node * addtree(listnode * list, int root, int last) {
	int end = root, push = 1, pull = 0;
	while (push>pull && end<last) {
		end++;
		if (list[end].push) {
			push++;
		}else{
			pull++;
		}
	}
	node * rootnode = new node;
	rootnode->index = list[root].index;
	rootnode->left = NULL;
	rootnode->right = NULL;
	if (root+1!=end) rootnode->left = addtree(list,root+1,end-1);
	if (end<last) rootnode->right = addtree(list,end+1,last);
	return rootnode;
}

listnode * readlist(listnode * list, int k) {
	char oper[5] = {0};
	for (int i = 0; i < k; ++i)
	{
		cin >> oper;
		if (!strcmp(oper,"Push"))
		{
			list[i].push = true;
			cin >> list[i].index;
		}else{
			list[i].push = false;
		}
	}
	return list;
}