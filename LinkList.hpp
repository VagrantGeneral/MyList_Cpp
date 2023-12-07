#ifndef LINKLIST_HPP
#define LINKLIST_HPP

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

extern void InitList(LinkList* plist, size_t elemsize);
extern void DestroyList(LinkList* plist);
extern size_t GetSize(const LinkList* plist);
extern bool IsEmpty(const LinkList* plist);
extern void ClearList(LinkList* plist);
//extern static void* GetElemmem(size_t size);
extern ListNode* FindPos(const LinkList* plist, size_t pos);
extern bool InsertList(LinkList* plist, int pos, void* pval);
extern void Push_back(LinkList* plist, void* pval);
extern void Push_front(LinkList* plist, void* pval);
extern ListNode* FindValue(const LinkList* plist, void* pval);
extern bool EraseList(LinkList* plist, int pos);
extern void Pop_back(LinkList* plist);
extern void Pop_Front(LinkList* plist);
extern bool GetFront(const LinkList* plist, void* pval);
extern bool GetBack(const LinkList* plist, void* pval);
extern bool Remove(LinkList* plist, void* pval);

#endif 

