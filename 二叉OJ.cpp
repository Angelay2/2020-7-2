#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

/*
二叉搜索树主要用来查找

1. 根据一棵树的前序遍历与中序遍历构造二叉树。
在前序找到根结点，在中序中找到根结点的左右节点
定义一前序遍历的索引preidx， 中序遍历的头索引instartidx，和尾索引inendidx
(1. 创建前序遍历中的每一个点
（2. 以前序遍历的点为界， 在中序中找到他的左右子树
（3. 
根-左-右的创建顺序
*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
class Solution{
public:
	// preidx给指针形式
	TreeNode* _buildTree(vector<int>&preorder, int* preidx, vector<int>& inorder, int inStartidx, int inEndidx){
		// 创建当前结点(前序的第一个结点）
		TreeNode* cur = new TreeNode(preorder[*preidx]);
		// 按照当前值， 去中序的搜索区间找cur左右子树的区间
		int curidx = inStartidx;
		for (; curidx <= inEndidx; ++curidx){
			if (inorder[curidx] == cur->val)
				// 以当前节点为根的分界点找到了
				break;
		}
		// 判断是否存在左右子树
		// 1. 左子树， 找到了根结点，-1就是左节点
		if (inStartidx < curidx){
			++(*preidx);
			cur->left = _buildTree(preorder, preidx, inorder, inStartidx, curidx - 1);
		}
		else
			cur -> left = nullptr;
		// 2. 右子树, 根结点+1就是右节点
		if (curidx < inEndidx){
			++(*preidx);
			cur->right = _buildTree(preorder, preidx, inorder, curidx + 1, inEndidx);
		}
		else
			cur->right = nullptr;
		return cur; //返回最终的root
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
		if (preorder.empty())
			return nullptr;
		int preidx = 0;
		return _buildTree(preorder, &preidx, inorder, 0, inorder.size() - 1);
	}
};

/*
2. 从中序与后序遍历序列构造二叉树
反着看后序遍历, 最后一个元素就是根结点, 根-1等于右子树的根结点,   根-右-左的创建顺序
*/
class Solution{
public:
	// preidx给指针形式
	TreeNode* _buildTree(vector<int>&postorder, int* postidx, vector<int>& inorder, int inStartidx, int inEndidx){
		TreeNode* cur = new TreeNode(postorder[*postidx]);
		int curidx = inStartidx;
		for (; curidx <= inEndidx; ++curidx){
			if (inorder[curidx] == cur->val)
				// 以当前节点为根的分界点找到了
				break;
		}
		if (curidx < inEndidx){
			--(*postidx);
			cur->right = _buildTree(postorder, postidx, inorder, curidx + 1, inEndidx);
		}
		else
			cur->right = nullptr;

		if (inStartidx < curidx){
			--(*postidx);
			cur->left = _buildTree(postorder, postidx, inorder, inStartidx, curidx - 1);
		}
		else
			cur->left = nullptr;
		return cur;
	}
	TreeNode* buildTree(vector<int>& postorder, vector<int>& inorder){
		if (postorder.empty())
			return nullptr;
		int postidx = postorder.size() - 1;
		return _buildTree(postorder, &postidx, inorder, 0, inorder.size() - 1);
	}
};

/* 
3. 二叉树的前序遍历，非递归迭代实现
借助栈来实现
*/

class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		stack<TreeNode*> st;
		vector<int> ret;
		TreeNode* cur = root;
		while (cur || !st.empty())
		while (cur){
			ret.push_back(cur->val);
			st.push(cur);
			cur = cur->left;
		}
		cur = st.top();
		st.pop();
		cur = cur->right;


	}
};
/* 后序遍历
右子树不为null且根的右子树不为prev,表示根的右子树未访问
右子树的prev已访问, 证明右子树已访问
右子树的根都访问完了 证明整个右子树多访问完了

