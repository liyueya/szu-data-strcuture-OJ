#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct treenode{
	char val;
	int weight;
	treenode* left;
	treenode* right;
	treenode(char x):val(x),weight(0),left(NULL),right(NULL){}
}; 
class Solution{
	public:
		treenode* buildtree(string& preorder,int &index){
			if(index>=preorder.length()||preorder[index]=='0'){
				index++;
				return NULL;
			}
			treenode* root=new treenode(preorder[index]);
			index++;
			root->left=buildtree(preorder,index);
			root->right=buildtree(preorder,index);
			return root;
		}
		void assignweights(treenode* root,vector<int>& weights,int& weightindex){
			if(root==NULL)return;
			root->weight=weights[weightindex++];
			assignweights(root->left,weights,weightindex);
			assignweights(root->right,weights,weightindex);
		}
		void calculatemaxpath(treenode* root,int currentsum,int& maxsum){
			if(root==NULL) return;
			currentsum+=root->weight;
			if(root->left==NULL&&root->right==NULL){
				maxsum=max(maxsum,currentsum);
				return;
			}
			calculatemaxpath(root->left,currentsum,maxsum);
			calculatemaxpath(root->right,currentsum,maxsum);
		}
		int getmaxpatsum(string& preorder,vector<int>& weights){
			int index=0;
			treenode* root=buildtree(preorder,index);
			int weightindex=0;
			assignweights(root,weights,weightindex);
			int maxsum=0;
			calculatemaxpath(root,0,maxsum);
			return maxsum;
		}
};
int main(){
	int t;
	cin>>t;
	while(t--){
		string preorder;
		cin>>preorder;
		int n;
		cin>>n;
		vector<int> weights(n);
		for(int i=0;i<n;i++){
			cin>>weights[i];
		}
		Solution solution;
		int result=solution.getmaxpatsum(preorder,weights);
		cout<<result<<endl;
	}
	return 0;
}
