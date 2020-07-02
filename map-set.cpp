#include <set>
#include <iostream>
using namespace std;

/*
之前学的都是序列/线性式容器
map/set为关联式容器
任何类型都可做键值, 
set: 底层是KV键值对的二叉搜索树 
1. 实现: 二叉平衡搜索树(红黑树)
2. 底层结构是一个KV的结构, 但是K和V都是相同的数据
3. 创建set时只需要传入value, 不需要传key,
4. 不存放重复的数据
5. 不支持修改操作
6. 通过迭代器操作不能修改内容, 
7. 迭代器遍历: 数据有序(因为底层实际上是二叉树搜索树的中序遍历)
8. 插入数据时, 给定的迭代器的位置只是一个建议, 数据真正的插入位置不一定是迭代器指向的位置, 需要符合搜索树的基本性质(升序)
9. 删除数据时, 可能会导致迭代器失效, 需要重新去获取迭代器
10. find查找数据时, 如果存在, 返回数据本身的迭代器, 如果失败返回end迭代器
11. count是去计算要查找的数据个数, 但是set不会存放重复数据, 所以count只可能返回0和1, 0表不存在, 1表存在

map: 
  m[3]  ==> m.at(3)
  本身k不存在时
  m[100] = 150 实际为插入
  m.at(200)=200, 抛异常

pair<iterator,bool> insert ( const value_type& x)
	iterator: 插入已经存在数据的位置, 
	bool: 插入是否成功
operator[]底层调的就是insert接口
  map[k] = value    ---> (*((this->insert(make_pair(k, mapped_type())).first)).second
				    1. 插入键值对 ---> k, value的默认值
				    2. 获取到插入操作的返回值, pair<iterator, bool>
					3. 获取返回值的first成员, 即pair<iterator, bool> --> first --> iterator
					 即k所定义的数据位置,
插入之后返回k对应的value, 把默认值改成等号右边的值, 执行插入操作
如果k本身存在,则插入失败 返回之前的k所对应的value, 改成等号右边的值, 执行修改操作

operator[]插入的原理
用<key, T()>构造一个键值对，然后调用insert()函数将该键值对插入到map中
如果key已经存在，插入失败，insert函数返回该key所在位置的迭代器
如果key不存在，插入成功，insert函数返回新插入元素所在位置的迭代器
operator[]函数最后将insert返回值键值对中的value返回

但是at不行, 本身不存在的话, 则抛异常

map:
	1. 实现 ---> 二叉平衡搜索树(红黑树)
	2. 底层结构是一个KV结构, 但是k和v不一定相同
	3. 键值不能重复, 但是value可以重复
	4. 数据类型为pair
	5. 插入数据, 可以通过pair构造函数, 或者make_pair函数创建插入的数据
	6. 迭代器遍历顺序为key值的递增或者递减顺序
	7. operator[]可以实现可读/可写/插入操作  
	8. map只允许修改value, 不允许修改key
	9. operator和at区别: 
		如果key不存在, operator执行插入操作, at抛异常
	
	10. find查找数据时, 如果存在, 返回数据本身的迭代器, 如果失败返回end迭代器
	11. count是去计算要查找的数据个数, 但是set不会存放重复数据, 所以count只可能返回0和1, 0表不存在, 1表存在

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
	//set不存放重复的数据
	set<int> Set2(array, array + 5);

	set<int> Set3(Set2.begin(), Set2.end());

	set<int> copy(Set3);

	set<int>::iterator it = copy.begin();
	//迭代器遍历有序：二叉搜索树的中序遍历
	while (it != copy.end())
	{
		cout << *it << " ";
		//set本身不能修改内容
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
	//insert(iterator, value) : 迭代器指定的位置只是一个建议，插入的数据不一定为迭代器指定的位置
	// 新插入的数据需要符合搜索树的基本性质
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

	cout << "删除所有值" << endl;
	s.erase(s.begin(), s.end());
	printForSet(s);
}

void testSet3()
{
	//set<int> s;
	set<int, less<int>> s;
	s.insert(10);
	s.insert(100);
	//insert(iterator, value) : 迭代器指定的位置只是一个建议，插入的数据不一定为迭代器指定的位置
	// 新插入的数据需要符合搜索树的基本性质
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
	// map: 存放kv键值对， 存放的数据类型为pair
	// map插入的数据，键值不能重复， 但是value可以重复
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));

	m.insert(make_pair(2, 3));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(3, 1));
	m.insert(make_pair(4, 1));
	m.insert(make_pair(5, 1));

	//迭代器解引用的数据类型为pair
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

	//key不存在， 插入
	m[100] = 150;
	cout << m[100] << endl;
	it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "-->" << it->second << endl;
		++it;
	}
	//key不存在， 抛异常
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