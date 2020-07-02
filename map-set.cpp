#include <set>
#include <iostream>
using namespace std;

/*
֮ǰѧ�Ķ�������/����ʽ����
map/setΪ����ʽ����
�κ����Ͷ�������ֵ, 
set: �ײ���KV��ֵ�ԵĶ��������� 
1. ʵ��: ����ƽ��������(�����)
2. �ײ�ṹ��һ��KV�Ľṹ, ����K��V������ͬ������
3. ����setʱֻ��Ҫ����value, ����Ҫ��key,
4. ������ظ�������
5. ��֧���޸Ĳ���
6. ͨ�����������������޸�����, 
7. ����������: ��������(��Ϊ�ײ�ʵ�����Ƕ��������������������)
8. ��������ʱ, �����ĵ�������λ��ֻ��һ������, ���������Ĳ���λ�ò�һ���ǵ�����ָ���λ��, ��Ҫ�����������Ļ�������(����)
9. ɾ������ʱ, ���ܻᵼ�µ�����ʧЧ, ��Ҫ����ȥ��ȡ������
10. find��������ʱ, �������, �������ݱ���ĵ�����, ���ʧ�ܷ���end������
11. count��ȥ����Ҫ���ҵ����ݸ���, ����set�������ظ�����, ����countֻ���ܷ���0��1, 0������, 1�����

map: 
  m[3]  ==> m.at(3)
  ����k������ʱ
  m[100] = 150 ʵ��Ϊ����
  m.at(200)=200, ���쳣

pair<iterator,bool> insert ( const value_type& x)
	iterator: �����Ѿ��������ݵ�λ��, 
	bool: �����Ƿ�ɹ�
operator[]�ײ���ľ���insert�ӿ�
  map[k] = value    ---> (*((this->insert(make_pair(k, mapped_type())).first)).second
				    1. �����ֵ�� ---> k, value��Ĭ��ֵ
				    2. ��ȡ����������ķ���ֵ, pair<iterator, bool>
					3. ��ȡ����ֵ��first��Ա, ��pair<iterator, bool> --> first --> iterator
					 ��k�����������λ��,
����֮�󷵻�k��Ӧ��value, ��Ĭ��ֵ�ĳɵȺ��ұߵ�ֵ, ִ�в������
���k�������,�����ʧ�� ����֮ǰ��k����Ӧ��value, �ĳɵȺ��ұߵ�ֵ, ִ���޸Ĳ���

operator[]�����ԭ��
��<key, T()>����һ����ֵ�ԣ�Ȼ�����insert()�������ü�ֵ�Բ��뵽map��
���key�Ѿ����ڣ�����ʧ�ܣ�insert�������ظ�key����λ�õĵ�����
���key�����ڣ�����ɹ���insert���������²���Ԫ������λ�õĵ�����
operator[]�������insert����ֵ��ֵ���е�value����

����at����, �������ڵĻ�, �����쳣

map:
	1. ʵ�� ---> ����ƽ��������(�����)
	2. �ײ�ṹ��һ��KV�ṹ, ����k��v��һ����ͬ
	3. ��ֵ�����ظ�, ����value�����ظ�
	4. ��������Ϊpair
	5. ��������, ����ͨ��pair���캯��, ����make_pair�����������������
	6. ����������˳��Ϊkeyֵ�ĵ������ߵݼ�˳��
	7. operator[]����ʵ�ֿɶ�/��д/�������  
	8. mapֻ�����޸�value, �������޸�key
	9. operator��at����: 
		���key������, operatorִ�в������, at���쳣
	
	10. find��������ʱ, �������, �������ݱ���ĵ�����, ���ʧ�ܷ���end������
	11. count��ȥ����Ҫ���ҵ����ݸ���, ����set�������ظ�����, ����countֻ���ܷ���0��1, 0������, 1�����

*/
#include <map>
#include <set>
#include <iostream>
#include <functional>
using namespace std;


void printSet(const set<int>& s)
{
	set<int>::const_iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		//*it = 10;
		++it;
	}
	cout << endl;
}

void printReverseSet(const set<int>& s)
{
	set<int>::const_reverse_iterator cit = s.rbegin();
	while (cit != s.rend())
	{
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
}

void printForSet(const set<int>& s)
{
	for (const auto& e : s)
		cout << e << " ";
	cout << endl;
}

void testSet()
{
	set<int> Set;

	int array[] = { 4, 1, 2, 5, 3, 4, 3, 5 };
	//set������ظ�������
	set<int> Set2(array, array + 5);

	set<int> Set3(Set2.begin(), Set2.end());

	set<int> copy(Set3);

	set<int>::iterator it = copy.begin();
	//�������������򣺶������������������
	while (it != copy.end())
	{
		cout << *it << " ";
		//set�������޸�����
		//*it = 10;
		++it;
	}
	cout << endl;

	printSet(Set2);
	printSet(Set3);
	printSet(copy);
	printReverseSet(copy);
	printForSet(Set2);
}


void testSet2()
{
	set<int> s;
	s.insert(10);
	s.insert(100);
	//insert(iterator, value) : ������ָ����λ��ֻ��һ�����飬��������ݲ�һ��Ϊ������ָ����λ��
	// �²����������Ҫ�����������Ļ�������
	s.insert(s.end(), 30);
	s.insert(s.begin(), 1);
	printForSet(s);

	set<int> s2;
	s2.insert(++s.begin(), --s.end());
	printForSet(s2);

	/*cout << s.erase(50) << endl;
	cout << s.erase(100) << endl;*/
	set<int>::iterator it = s.begin();
	cout << *it << endl;
	set<int>::iterator it2 = --s.end();
	cout << *it2 << endl;
	s.erase(it);
	cout << *it2 << endl;

	cout << "ɾ������ֵ" << endl;
	s.erase(s.begin(), s.end());
	printForSet(s);
}

void testSet3()
{
	//set<int> s;
	set<int, less<int>> s;
	s.insert(10);
	s.insert(100);
	//insert(iterator, value) : ������ָ����λ��ֻ��һ�����飬��������ݲ�һ��Ϊ������ָ����λ��
	// �²����������Ҫ�����������Ļ�������
	s.insert(s.end(), 30);
	s.insert(s.begin(), 1);
	//printForSet(s);
	set<int, less<int>>::const_iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		//*it = 10;
		++it;
	}
	cout << endl;

	//set<int>::iterator it = s.find(100);
	///*cout << *it << endl;
	//it = s.find(5);
	//cout << (it == s.end()) << endl;*/
	//int num = s.count(5);
	//cout << num << endl;
	//num = s.count(30);
	//cout << num << endl;
}


void testMap()
{
	// map: ���kv��ֵ�ԣ� ��ŵ���������Ϊpair
	// map��������ݣ���ֵ�����ظ��� ����value�����ظ�
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));

	m.insert(make_pair(2, 3));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(3, 1));
	m.insert(make_pair(4, 1));
	m.insert(make_pair(5, 1));

	//�����������õ���������Ϊpair
	map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "-->" << it->second << endl;
		++it;
	}

	m[3] = 10;
	cout << m[1] << endl;
	m.at(3) = 100;
	cout << m.at(3) << endl;

	//key�����ڣ� ����
	m[100] = 150;
	cout << m[100] << endl;
	it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "-->" << it->second << endl;
		++it;
	}
	//key�����ڣ� ���쳣
	m.at(200) = 200;
}
int main()
{
	//testSet();
	//testSet2();
	//testSet3();
	testMap();
	return 0;
}