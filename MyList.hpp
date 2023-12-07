#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include <stdio.h>

template <typename Param>
class MyList {

public:

	//别名声明	//对模板来说会将元素分为以下5种类型******************************************
	typedef Param value_type;				//值类型***************************************
	typedef Param* pointer;					//指针类型*************************************
	typedef Param const* const_pointer;		//常指针类型***********************************
	typedef Param& reference;				//引用类型*************************************
	typedef Param const& const_reference;	//常引用类型***********************************

private:

	struct _Node;//声明节点类型
	using _NodePtr = _Node*;				//节点指针************************************

	//节点数据的结构
	struct _Node {

		_NodePtr _Prev;						//前驱
		_NodePtr _Next;						//后继
		Param _Value;						//节点数据

	};
    

	//只为struct _Node提供服务
	struct _Acc {
		
		static Param& _Value(_NodePtr ptr) {
			return ptr->_Value;
		}

		typedef _Node*& _Nodepref;			//节点指针的引用(指针的别名)*********************

		static _Nodepref _Prev(_NodePtr ptr) {
			return (ptr->_Prev);
		}

		static _Nodepref _Next(_NodePtr ptr) {
			return (ptr->_Next);
		}

		/*
		_Node* sp = _Acc::_Prev();

		_Node* sn = _Acc::_Next();

		*/
	};


private:

	_NodePtr _Head;							//哨兵节点
	size_t _Size;

	//申请一个节点
	static _NodePtr _Buynode(/*前驱指针*/_NodePtr _Parg = nullptr, /*后驱指针*/_NodePtr _Narg = nullptr) {

		_NodePtr s = (_NodePtr)malloc(sizeof(*s));
		if (s == nullptr) {
			exit(EXIT_FAILURE);
		}
		_Acc::_Prev(s) = (_Parg == nullptr ? s : _Parg);
		_Acc::_Next(s) = (_Narg == nullptr ? s : _Narg);
		return s;
	}


	//释放节点空间（仅仅是释放空间，没有调用存储对象的析构函数
	static void FreeNode(_NodePtr p) {
		free(p);
	}



public:

	//常迭代器
	class const_iterator {

	public:

		_NodePtr _Ptr;

	public:

		const_iterator(_NodePtr _P = nullptr) : _Ptr(_P) {
			//std::cout << "const_iterator create successful" << std::endl;
		}
		~const_iterator() {}

		//Param const&
		const_reference operator*() const {
			return _Acc::_Value(_Ptr);
		}

		//Param const*
		const_pointer operator->() const {
			return &(*(*this));
		}

		// 前置/后置 ++/--
		const_iterator& operator++() {
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		const_iterator& operator++(int) {
			const_iterator _tmp = *this;
			++(*this);
			return _tmp;
		}
		const_iterator& operator--() {
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		const_iterator& operator--(int) {
			const_iterator _tmp = *this;
			--(*this);
			return _tmp;
		}
		bool operator==(const const_iterator& x) const
		{
			return (this->_Ptr == x._Ptr);
		}
		bool operator!=(const const_iterator& x) const
		{
			return !(*this == x);
		}

		_NodePtr MyNode() const { 
			return _Ptr;
		}

	};

	//普通迭代器
	class iterator : public const_iterator {

	/*
	protected:

		_NodePtr _Ptr;
	*/

	public:

		iterator(_NodePtr _P = nullptr) 
			: const_iterator(_P) {
			//std::cout << "iterator create successful" << std::endl;
		}
		~iterator() {}

		//Param &
		reference operator*() const {
			return _Acc::_Value(const_iterator::_Ptr);
		}

		//Param *
		pointer operator->() const {
			return &(*(*this));
		}

		//
		iterator& operator++() {
			const_iterator::_Ptr = _Acc::_Next(const_iterator::_Ptr);
			return *this;
		}
		iterator& operator++(int) {
			iterator _tmp = *this;
			++(*this);
			return _tmp;
		}
		iterator& operator--() {
			const_iterator::_Ptr = _Acc::_Prev(const_iterator::_Ptr);
			return *this;
		}
		iterator& operator--(int) {
			iterator _tmp = *this;
			--(*this);
			return _tmp;
		}
		bool operator==(const iterator& _X) const
		{
			return (this->_Ptr == _X._Ptr);
		}
		bool operator!=(const iterator& _X) const
		{
			return !(*this == _X);
		}
	};


public:
	//构造
	MyList() 
		: _Head(_Buynode()), 
		_Size(0) {
		std::cout << "create successful" << std::endl;
	}

	//拷贝构造
	MyList(const MyList& x)
		:_Head(_Buynode()), _Size(0) {
		insert(end(), x.begin(), x.end());
	}

	//移动构造
	MyList(MyList&& x)
		:_Head(x._Head), _Size(x.size) {
		x._Head = _Buynode();
		x._Size = 0;
	}

	//拷贝赋值
	MyList& operator=(const MyList& x) {
		_Head = _Buynode();
		_Size = 0;
		insert(end(), x.begin(), x.end());
	}

	//移动赋值
	MyList& operator=(const MyList&& x) {
		_Head = x._Head;
		_Size = x._Size;
		x._Head = _Buynode();
		x._Size = 0;
	}

	//析构
	~MyList() {
		std::cout << "delete successful" << std::endl;
	}

	//获取元素个数
	size_t size() const { return _Size; }

	//判断是否为空
	bool empty() const { return size() == 0; }

	iterator begin() { 
		return iterator(_Acc::_Next(_Head)); 
	}

	iterator end() { 
		return iterator(_Head); 
	}

	const_iterator begin() const { 
		return const_iterator(_Acc::_Next(_Head)); 
	}

	const_iterator end() const { 
		return const_iterator(_Head); 
	}

	//指定位置插入（ 为以后的复用性做准备
	iterator insert(const_iterator pos, const Param& value) {
		_NodePtr p = pos.MyNode();//获取操纵指针

		_Acc::_Prev(p) = _Buynode(_Acc::_Prev(p), p);
		p = _Acc::_Prev(p); 
		_Acc::_Next(_Acc::_Prev(p)) = p;

		new(&_Acc::_Value(p)) Param(value);//构造（避免 值 赋给 空间）

		_Size += 1;

		return iterator(p);
	}

	//指定位置 重复多次 插入
	void insert(const_iterator pos, size_t count, const Param& value) {
		while (count--) {
			insert(pos, value);//**************************************************
		}
	}

	//指定位置 连续多次（连续内存） 插入
	void insert(const_iterator pos, const Param* _F, const Param* _L) {
		for (; _F != _L; ++_F) {
			insert(pos, *_F);  //**************************************************
		}
	}

	//指定位置 插入 其他对象的切片
	void insert(const_iterator pos, const_iterator _F, const_iterator _L) {
		for (; _F != _L; ++_F) {
			insert(pos, *_F);  //**************************************************
		}
	}

	//指定位置删除
	iterator erase(iterator pos) {
		/*
		_NodePtr p = pos.MyNode();

		_Acc::_Next(_Acc::_Prev(p)) = _Acc::_Next(p);
		_Acc::_Prev(_Acc::_Next(p)) = _Acc::_Prev(p);

		_Acc::_Prev(p) = nullptr;
		_Acc::_Next(p) = nullptr;

		~Param(p);
		_Size--;

		//要返回迭代器，不能直接使用以上方法
		*/

		_NodePtr p = (pos++).MyNode();

		_Acc::_Next(_Acc::_Prev(p)) = _Acc::_Next(p);
		_Acc::_Prev(_Acc::_Next(p)) = _Acc::_Prev(p);

		(&_Acc::_Value(p))->~Param();

		FreeNode(p);

		return pos;
	}

	
	void push_back(const Param& value) {
		insert(end(), value);
	}
	void push_front(const Param& value) {
		insert(begin(), value);
	}
	void pop_back() {
		erase(end());
	}
	void pop_front() {
		erase(begin());
	}


	//范围删除
	void erase(iterator _F, iterator _L) {
		for (; _F != _L;) {
			erase(_F++);
		}
	}

	//清空所用
	void clear() {
		erase(begin(), end());
	}

	//
	iterator find(const Param& val) {
		_NodePtr p = begin();
		for (; p != end(); p++) {
			if (_Acc::_Value(p) == val) {
				return iterator(p);
			}
		}
		return end();
	}

	//
	void remove(const Param& val) {
		erase(find(val));
	}

};

#endif