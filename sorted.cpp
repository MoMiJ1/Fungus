#include<stdlib.h>
#include<limits.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;


struct LinkNode
    {
        int key;
        LinkNode *next;
        LinkNode(int x) : key(x), next(NULL) {}
    }; 


class sort_Insert  //直接插入排序
{   
public:

    /* 一、数组排序 */
    // 基本思想：从有序界开始与当前数字进行比较，如果比当前数字大，有序界数字向后移动
    void sort_InsertArray(int array[],int n) { 
        int i , p;
        for (p = 1; p < n; p++) //排序界从1开始
        {
            int temp = array[p];
            for (i = p-1; i>0 && array[i]>temp ; i--)
            {
                array[i] = array[i-1];  //将比待排序数字大的数字都向后移一位
            }
            array[i] = temp;
        }
    }

    /*二、链表排序*/
    LinkNode* sort_InsertLink(LinkNode* head){
        if(head==NULL || head->next==NULL) return head;

        //定义伪头结点Tower
        LinkNode* Tower = new LinkNode(INT_MIN);
        Tower->next = head;

        //pre指向上一次移动的结点、end指向有序边界结点、now指向正在排序的结点
        LinkNode *pre=Tower, *end=Tower, *now=head;
        while (now)
        {
            if (now->key > end->key) //这种情况不变化
            {
                end = end->next;
                now = now->next;
            }
            else
            {
                if (now->key < pre->key) //正在排序的数比上次排序的数小，说明要进行移动，将pre置于头结点
                {
                    pre = Tower;
                }
                while (pre->next && pre->next->key < now->key) //找到要操作的结点
                {
                    pre = pre->next;
                }
                LinkNode* temp = now->next;  //先保留下一个要操作的结点位置
                now->next = pre->next;       //将正在排序的数与其后面的结点相连
                pre->next = now;             //pre为上次移动的结点，因此置于正在操作的结点处
                end->next = temp;            //有序界向后移动
                now = end->next;             //更新正在操作的结点
            }    
        }
        LinkNode* res = Tower->next;
        delete Tower;
        return res;
    }

    LinkNode* sort_InsertComplex(LinkNode* head){
        if (head==NULL || head->next==NULL) return head;
        LinkNode *Tower = new LinkNode(INT_MIN); // Tower是伪头结点，指向头结点
        Tower->next = head;
        LinkNode *p = Tower, *end = Tower, *cur = head; // p用于从头搜索数值，end用于确定已有序的区间，cur为正在排序的结点
        while (cur)
        {
            if (cur->key > end->key)   // 这种情况顺序是合理的
            {
                end = end->next;
                cur = cur->next;
            }
            else    
            {
                p = Tower;   // 先将用于搜索的指针置于伪头
                while (p->next && p->next->key < cur->key)
                {
                    p = p->next;  // 找到要移动的结点
                }       
                LinkNode *temp = cur->next;  //正在排序部分的局部顺序应该是 head-->...->cur->p->...->end->temp->...
                cur->next = p->next;         
                p->next = cur;
                end->next = temp;
                cur = end->next;    
            }            
        }
        return Tower->next;  // 返回头结点
    }

    LinkNode* creatLink(){
        LinkNode *head = new LinkNode(INT_MIN);
        LinkNode *pre = new LinkNode(INT_MIN);
        pre = head;
        for (int i = 8; i >= 0; i--)
        {
            LinkNode *p = new LinkNode(0);
            p->key = i;
            pre->next = p;
            pre = p;
        }
        return head;
    }
    
    void print(LinkNode *head){
        while (head->next)
        {
            printf("%d ",head->next->key);
            head = head->next;
        }
    }
};

class sort_Bubble  //冒泡排序
{
public:
    /*一、数组排序*/
    void sort_BubbleArray(int array[],int n){
        bool flag;  // 指示是否发生元素移动，如果没发生，说明已经有序，终止排序
        for (int i = n-1; i >= 0; i--)  //由于每轮排序将最大的数排至末尾，因此要指定末尾的位置
        {
            flag = false;
            for (int j = 0; j < i; j++)
            {
                if (array[j]>array[j+1])
                {
                    int temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                    flag = true;
                }               
            }
            if(!flag) break;            
        }                   
    }

    /*二、链表排序*/
    LinkNode* sort_BubbleLink(LinkNode* head){
        LinkNode *pre, *cur, *tail;
        tail = NULL;
        while (head->next != tail)  // 根据冒泡排序的特性，每次会将最大数排至最后，因此设置尾指针区分排序区
        {
            pre = head;
            cur = head->next; // cur表示正在排序的位置
            while (cur->next != tail)  // 在有序区之前
            {
                if (cur->key > cur->next->key)
                {
                    pre->next = cur->next;
                    cur->next = pre->next->next;
                    pre->next->next = cur;
                }
                else cur = cur->next;
                pre = pre->next;                
            }
            tail = cur;  // 每轮排序结束后更新界指针
        }
        return head;        
    }
};

class sort_Heap{   //堆排序
public:
    // 将以root为根的子树调整为大根堆
    void heap_Adjust(int array[],int root,int n){  
        int parent, child;
        int temp;
        temp = array[root];  // 每次比较是用传入的root节点的值与各个孩子节点进行比较
        for (parent = root; parent*2+1 < n; parent=child)
        {
            child = parent * 2 + 1;
            if (child!=n-1 && array[child]<array[child+1])  // 找出左右孩子的最大孩子
                child++;
            if (temp >= array[child]) break;  //判断孩子值是否大于根值
            else
            {
                array[parent] = array[child];
            }                        
        }
        array[parent] = temp;      // 最后剩下的空位就是parent的值应在的位置  
    }

    // 根据堆进行排序
    void sort_heap(int array[], int n){
        int i;
        for (i = n/2-1; i >= 0; i--)  // 无序数组建堆
        {
            heap_Adjust(array,i,n);
        }
        for (i = n-1; i > 0; i--)    // 弹出顶元素（排序过程）
        {
            int temp = array[0];  // 每次将待排序列最大值移至尾部，再重建堆，直到堆清空
            array[0] = array[i];
            array[i] = temp;      
            heap_Adjust(array,0,i);
        }        
    }
};

class sort_Shell  // 希尔排序
{
public:
    void sort_shellArray(int array[],int n){
        int gap = n;
        int i, j, temp;
        for (gap>>=2; gap>0; gap>>=2){
            for (i = gap; i < n; i++)
            {
                j = 0;
                temp = array[i];
                for (j = i-gap; j>=0 && temp<array[j]; j = j-gap)
                {
                    array[j + gap] = array[j];
                }
                array[j + gap] = temp;
            }
        }
    }    
};

class sort_Select  // 直接选择排序
{
public:
    void sort_SelectArray(int array[], int n){
        int index;
        int val;
        for (int i = 0; i < n-1; i++)
        {
            val = array[i];
            index = i;
            for (int j = i;j < n;j++)
            {
                if (array[j] < val)
                {
                    index = j;
                    val = array[j];
                }
            }
            int temp = array[i];
            array[i] = array[index];
            array[index] = temp;
        }       
    }
};

class sort_Quick{  // 快速排序
public:
    // 选定基准值
    int partition(int array[],int low,int high){
        int pivot = array[high]; // 取最后一个值作基准
        int i = low - 1; // i是小元素指针，j是大元素指针
        //j从数组头部开始，每发现一个比基准小的数，就将它换至i处
        //i每接受一个最小数，就+1，可以理解为开新格子放东西
        for (int j = low; j < high; j++)
        {
            if (array[j] <= pivot)
            {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        //在这里，i指向的是最靠近中部的比基准数小的值
        //i+1是第一个比基准数大的值，因此让其与基准交换，便可区分大小
        int temp = array[i+1];
        array[i+1] = array[high];
        array[high] = temp;
        return i+1;         
    }
    // 快速排序 , 递归
    void sort_quick(int array[],int left,int right){
        if (left < right){
            int p = partition(array,left,right);
            sort_quick(array,left,p-1);
            sort_quick(array,p+1,right);
        }   
    }
};

class sort_Bucket{  // 桶排序
public:
    void sort_BucketArray(int array[],int n){
        vector<int> vec[n];
        for (int i = 0; i < n; i++){
            int bi =  array[i];
            vec[bi].push_back(array[i]);
        }
        for (int i = 0; i < n; i++)
            sort(vec[i].begin(),vec[i].end());
        
        int index = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0;j < vec[i].size(); j++)
                array[index++] = vec[i][j];
    }
};
