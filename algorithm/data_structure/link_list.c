#include<stdio.h>
#define N 5
typedef struct Node{
    int data;
    struct Node *next;
}Node;

void sort(Node *head)
{
    Node *tail = head;
    while(tail->next)
    {
        tail = tail->next;
    }
    Node *pre = head->next;
    Node *q;
    if(pre != tail)
    {
        q = pre->next;
    }
    else
    {
        return ;
    }
    //头结点之后第一个元素不是最后一个节点
    //说明最少还有两个元素
    Node* pbeforepre;
    while(head->next != tail)
    {
        //pre从头结点开始
        //printf("=====\n");
        pbeforepre = head;
        pre = pbeforepre->next;
        q = pre->next;
        while(pre != tail)
        {
            if(pre->data > q->data)
            {
                int temp_data = pre->data;
                pre->data = q->data;
                q->data = temp_data;
            }
            pbeforepre = pbeforepre->next;
            pre = pbeforepre->next;
            q = pre->next;
        }
        tail = pbeforepre;
    }
}
int main()
{
    ///*动态分配方式初始化
    int date[N] = {5,1,4,2,3};
    int i;
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    Node *h = head;
    Node *temp;
    for(i = 0; i <  N ;i++)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->next = NULL;
        h->next = temp;
        h = h->next;
    }

    h = head->next;
    for(i = 0; i <  N ;i++)
    {
        h->data = date[i];
        h = h->next;
    }
    Node *next = head->next;
    while(next)
    {
        printf("%d ",next->data);
        next = next->next;
    }
    ///*/
    /*静态方式初始化
    Node headNode;
    Node n1;
    Node n2;
    Node n3;
    n1.data = 5;
    n1.next = &n2;
    n2.data = 1;
    n2.next = &n3;
    n3.data = 6;
    n3.next = NULL;
    headNode.next = &n1;
    Node *head = &headNode;
    Node *next = head->next;


    while(next)
    {
        printf("%d ",next->data);
        next = next->next;
    }
    ///*/
    ///*
    sort(head);
    while(next)
    {
        printf("%d ",next->data);
        next = next->next;
    }
    ///*/
    return 0;
}
