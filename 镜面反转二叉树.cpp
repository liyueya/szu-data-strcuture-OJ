#include<iostream>
#include<cstring>
using namespace std;
struct treenode {
	char data;
	treenode* left;
	treenode* right;
	treenode(char c):data(c),left(nullptr),right(nullptr) {}
};
treenode* buildtree(const string& preorder,int& index) {
	if(index>=preorder.length()||preorder[index]=='#') {
		index++;
		return nullptr;
	}
	treenode* node=new treenode(preorder[index]);
	index++;
	node->left=buildtree(preorder,index);
	node->right=buildtree(preorder,index);
	return node;
}

void mirrortree(treenode* root) {
	if(root==nullptr)return;
	treenode* temp=root->left;
	root->left=root->right;
	root->right=temp;
	mirrortree(root->left);
	mirrortree(root->right);
}
void preordertraversal(treenode* root,bool& first) {
	if(root==nullptr)return;
	cout<<root->data<<" ";
	first=false;
	preordertraversal(root->left,first);
	preordertraversal(root->right,first);
}
void inordertraversal(treenode* root,bool& first) {
	if(root==nullptr)return;
	inordertraversal(root->left,first);
	cout<<root->data<<" ";
	first=false;
	inordertraversal(root->right,first);
}

void postordertraversal(treenode* root,bool& first) {
	if(root==nullptr)return;
	postordertraversal(root->left,first);
	postordertraversal(root->right,first);
	cout<<root->data<<" ";
	first=false;
}

void levelordertraversal(treenode* root) {
	if(root==nullptr)return;
	treenode* queue[1000];
	int front=0,rear=0;
	bool first=true;
	queue[rear++]=root;
	while(front<rear) {
		treenode* current=queue[front++];
		cout<<current->data<<" ";
		first=false;
		if(current->left!=nullptr){
			queue[rear++]=current->left;
		}
		if(current->right!=nullptr){
			queue[rear++]=current->right;
		}
	}
}
void deletetree(treenode* root){
	if(root==nullptr)return;
	deletetree(root->left);
	deletetree(root->right);
	delete root;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		string preorder;
		cin>>preorder;
		if(preorder.empty()||(preorder.length()==1&&preorder[0]=='#')){
			cout<<"NULL"<<endl<<"NULL"<<endl<<"NULL"<<endl<<"NULL"<<endl;
			continue;
		}
		int index=0;
		treenode* root=buildtree(preorder,index);
		mirrortree(root);
		bool first=true;
		preordertraversal(root,first);
		cout<<endl;
		first=true;
		inordertraversal(root,first);
		cout<<endl;
		first=true;
		postordertraversal(root,first);
		cout<<endl;
		levelordertraversal(root);
		cout<<endl;
	}
	return 0;
}

