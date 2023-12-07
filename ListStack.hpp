#ifndef LISTSTACK_HPP
#define LISTSTACK_HPP
//用List实现栈结构

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "MyList.hpp"

template <typename Param>
class ListStack {

private:
	MyList<Param> liststack;


public:
	//构造
	ListStack()
		:liststack(MyList<Param>()) {
	}

	//拷贝构造
	ListStack(const ListStack& ls)
		:liststack(MyList<Param>(ls)) {
	}

	//移动构造
	ListStack(ListStack&& ls)
		:liststack(MyList<Param>(ls)) {
	}

	//析构
	~ListStack() {

	}


public:
	//获取栈中元素个数
	size_t size() const {
		return liststack.size();
	}

	//判断是否为空
	bool empty() const {
		return liststack.size() == 0;
	}

	//获取栈顶元素
	Param GetTopValue() const {
		return *((liststack.end())--)
	}

	//在栈顶添加元素
	void PushTop(const Param& val) {
		liststack.push_back(val);
	}

	//弹出栈顶元素
	void PopTop() {
		liststack.pop_back();
	}




};
























#endif