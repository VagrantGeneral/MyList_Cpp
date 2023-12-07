#include<stdlib.h>  // malloc free;	  exit;
#include<string.h> // memset;
#include<assert.h>


#include"LinkList.hpp"
/*
typedef struct ListNode
{
	struct ListNode* prev;
	struct ListNode* next;
	void* data; // double // struct Student;
}ListNode, * pListNode;
typedef struct
{
	pListNode Head;
	int cursize;
	size_t elemsize;  // char  , short , int ; // long int; long long; float; double; long double;
}LinkList;
*/


//购买节点
static ListNode* Buynode()
{
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	if (nullptr == s) exit(1);
	memset(s, 0, sizeof(ListNode));
	return s;
}
//释放节点
static void Freenode(ListNode* p)
{
	free(p);
}
//将s设置为p的前驱
static void InserPrev(ListNode* p, ListNode* s) {
	s->next = p;
	s->prev = p->prev;
	p->prev = s;
	s->prev->next = s;
}
//
static void* GetElemmem(size_t size) {
	void* s = malloc(size);
	if (nullptr == s) exit(1);
	memset(s, 0, size);
	return s;
}









//初始化List
void InitList(LinkList* plist, size_t elemsize)
{
	assert(plist != nullptr);
	plist->Head = Buynode();
	plist->Head->next = plist->Head->prev = plist->Head;
	plist->cursize = 0;
	plist->elemsize = elemsize;
}
//摧毁List
void DestroyList(LinkList* plist) {

}
//获取元素个数
size_t GetSize(const LinkList* plist)
{
	assert(plist != nullptr);
	return plist->cursize;
}
//判断是否为空
bool IsEmpty(const LinkList* plist)
{
	assert(plist != nullptr);
	return GetSize(plist) == 0;
}
//清空List
void ClearList(LinkList* plist) {

}
//定位指定位置的节点
ListNode* FindPos(const LinkList* plist, size_t pos) {
	assert(plist != nullptr);
	if (pos == 0) return nullptr;
	if (pos == 1) return plist->Head->next;
	if (GetSize(plist) == pos) return plist->Head->prev;
	if (GetSize(plist) < pos) return nullptr;
	ListNode* p = plist->Head;
	while (pos--) {
		p = p->next;
	}
	return p;
}
//指定位置插入新节点
bool InsertList(LinkList* plist, int pos, void* pval) {
	assert(plist != nullptr);
	assert(pval != nullptr);
	ListNode* p = FindPos(plist, pos);
	if (nullptr == p) return false;
	ListNode* s = Buynode();
	InserPrev(p, s);
	if (plist->elemsize <= 4) {
		memmove(&s->data, pval, plist->elemsize);
	}
	else {
		void* newval = GetElemmem(plist->elemsize);
		s->data = newval;
	}
	plist->cursize += 1;

	return true;
}
//尾插
void Push_back(LinkList* plist, void* pval) {

}
//头插
void Push_front(LinkList* plist, void* pval) {

}
//查找元素
//ListNode* FindValue(const LinkList* plist, void* pval) {
//
//}

//删除指定位置节点
//bool EraseList(LinkList* plist, int pos) {
//
//}
//尾删
void Pop_back(LinkList* plist) {

}
//头删
void Pop_Front(LinkList* plist) {

}
////获取头
//bool GetFront(const LinkList* plist, void* pval) {
//
//}
////获取尾
//bool GetBack(const LinkList* plist, void* pval) {
//
//}
////移除指定节点
//bool Remove(LinkList* plist, void* pval) {
//
//}
