#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

/*
������������Ҫ��������

1. ����һ������ǰ�������������������������
��ǰ���ҵ�����㣬���������ҵ����������ҽڵ�
����һǰ�����������preidx�� ���������ͷ����instartidx����β����inendidx
(1. ����ǰ������е�ÿһ����
��2. ��ǰ������ĵ�Ϊ�磬 ���������ҵ�������������
��3. 
��-��-�ҵĴ���˳��
*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
class Solution{
public:
	// preidx��ָ����ʽ
	TreeNode* _buildTree(vector<int>&preorder, int* preidx, vector<int>& inorder, int inStartidx, int inEndidx){
		// ������ǰ���(ǰ��ĵ�һ����㣩
		TreeNode* cur = new TreeNode(preorder[*preidx]);
		// ���յ�ǰֵ�� ȥ���������������cur��������������
		int curidx = inStartidx;
		for (; curidx <= inEndidx; ++curidx){
			if (inorder[curidx] == cur->val)
				// �Ե�ǰ�ڵ�Ϊ���ķֽ���ҵ���
				break;
		}
		// �ж��Ƿ������������
		// 1. �������� �ҵ��˸���㣬-1������ڵ�
		if (inStartidx < curidx){
			++(*preidx);
			cur->left = _buildTree(preorder, preidx, inorder, inStartidx, curidx - 1);
		}
		else
			cur -> left = nullptr;
		// 2. ������, �����+1�����ҽڵ�
		if (curidx < inEndidx){
			++(*preidx);
			cur->right = _buildTree(preorder, preidx, inorder, curidx + 1, inEndidx);
		}
		else
			cur->right = nullptr;
		return cur; //�������յ�root
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
		if (preorder.empty())
			return nullptr;
		int preidx = 0;
		return _buildTree(preorder, &preidx, inorder, 0, inorder.size() - 1);
	}
};

/*
2. �����������������й��������
���ſ��������, ���һ��Ԫ�ؾ��Ǹ����, ��-1�����������ĸ����,   ��-��-��Ĵ���˳��
*/
class Solution{
public:
	// preidx��ָ����ʽ
	TreeNode* _buildTree(vector<int>&postorder, int* postidx, vector<int>& inorder, int inStartidx, int inEndidx){
		TreeNode* cur = new TreeNode(postorder[*postidx]);
		int curidx = inStartidx;
		for (; curidx <= inEndidx; ++curidx){
			if (inorder[curidx] == cur->val)
				// �Ե�ǰ�ڵ�Ϊ���ķֽ���ҵ���
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
3. ��������ǰ��������ǵݹ����ʵ��
����ջ��ʵ��
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
/* �������
��������Ϊnull�Ҹ�����������Ϊprev,��ʾ����������δ����
��������prev�ѷ���, ֤���������ѷ���
�������ĸ����������� ֤���������������������

