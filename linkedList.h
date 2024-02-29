//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_LINKEDLIST_H
#define NEETCODE150_LINKEDLIST_H

#include "common.h"

//206. Reverse Linked List
class Solution206 {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return prev;
    }
};

//21. Merge Two Sorted Lists
class Solution21 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == NULL && list2 == NULL) {
            return NULL;
        }
        if (list1 == NULL) {
            return list2;
        }
        if (list2 == NULL) {
            return list1;
        }

        ListNode* dummy = new ListNode();
        ListNode *curr = dummy;
        while (list1 != NULL && list2 != NULL) {
            if (list1->val <= list2->val) {
                curr->next = list1;
                list1 = list1->next;
            } else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }

        if (list1 == NULL) {
            curr->next = list2;
        } else {
            curr->next = list1;
        }

        return dummy->next;
    }
};

//234. Palindrome Linked List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution234 {
    ListNode* reverseList(ListNode* head){
        if(nullptr==head || nullptr==head->next)
            return head;
        ListNode *res = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return res;
    }

    int getListLength(ListNode *head) {
        int len = 0;
        ListNode *node = head;
        while(node->next != nullptr) {
            len++;
            node = node->next;
        }
        return len;
    }

public:
    bool isPalindrome(ListNode* head) {
        if(head == nullptr||head->next== nullptr){
            return true;
        }
        int len = getListLength(head);
        len = len - len/2;
        ListNode *node = head;
        while(len-->0){
            node = node->next;
        }
        ListNode *rhead = reverseList(node);
        if(rhead== nullptr){
            return false;
        }
        while(rhead!=nullptr){
            if(head->val!=rhead->val){
                return false;
            } else{
                head = head->next;
                rhead = rhead->next;
            }
        }
        return true;
    }
};

//203. Remove Linked List Elements
class Solution203_linkedlist {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(nullptr == head) {
            return nullptr;
        }
        while(head != nullptr && val == head->val) {
            head = head->next;
        }
        ListNode *node = head;
        while( nullptr != node) {
            if(nullptr == node->next) {
                return head;
            }
            if(val == node->next->val) {
                node->next = node->next->next;
            } else {
                node = node->next;
            }
        }
        return head;
    }
};

//83. Remove Duplicates from Sorted List
class Solution83 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* cur = head;
        ListNode* prev = new ListNode;
        prev->next = cur;
        ListNode* next = nullptr;
        while (cur != nullptr) {
            next = cur->next;
            while (next != nullptr && next->val == cur->val) {
                next = next->next;
            }
            cur->next = next;
            cur = next;
        }
        return head;
    }
};

//876. Middle of the Linked List
class Solution876 {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

//160. Intersection of Two Linked Lists
class Solution160 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> visited;
        ListNode *temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

//143. Reorder List
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> vec;
        ListNode* itor = head;
        while (itor != nullptr) {
            vec.push_back(itor);
            itor = itor->next;
        }
        int left = 0;
        int right = vec.size() - 1;
        while (left < right) {
            vec[left]->next = vec[right];
            left++;
            if (left == right)
                break;
            vec[right]->next = vec[left];
            right--;
        }
        vec[left]->next = nullptr;
    }
};

//19. Remove Nth Node From End of List
class Solution19 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr)
            return nullptr;
        ListNode* fast = head;
        ListNode* slow = head;
        while (n-->0 && fast != nullptr) {
            fast = fast->next;
        }
        if (fast == nullptr) {
            return head->next;
        }
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }
};

//138. Copy List with Random Pointer
class Solution138 {
    class Node {
    public:
        int val;
        Node* next;
        Node* random;

        Node(int _val) {
            val = _val;
            next = NULL;
            random = NULL;
        }
    };
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> nodeMap;
        Node* h = head;
        while (h != nullptr) {
            nodeMap[h] = new Node(h->val);
            h = h->next;
        }
        h = head;
        while (h != nullptr) {
            nodeMap[h]->next = nodeMap[h->next];
            nodeMap[h]->random = nodeMap[h->random];
            h = h->next;
        }
        return nodeMap[head];
    }
};

//707. Design Linked List
class MyLinkedList {
public:
    MyLinkedList() {
        this->size = 0;
        this->head = new ListNode(0);
    }

    int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        ListNode *cur = head;
        for (int i = 0; i <= index; i++) {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        addAtIndex(0, val);
    }

    void addAtTail(int val) {
        addAtIndex(size, val);
    }

    void addAtIndex(int index, int val) {
        if (index > size) {
            return;
        }
        index = max(0, index);
        size++;
        ListNode *pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        ListNode *toAdd = new ListNode(val);
        toAdd->next = pred->next;
        pred->next = toAdd;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        size--;
        ListNode *pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        ListNode *p = pred->next;
        pred->next = pred->next->next;
        delete p;
    }
private:
    int size;
    ListNode *head;
};

//2. Add Two Numbers
class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum = 0;
        int carry = 0;
        ListNode* l = new ListNode;
        ListNode* node = l;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            sum = (l1 == nullptr ? 0 : l1->val) +
                  (l2 == nullptr ? 0 :l2->val) +
                  carry;
            carry = sum / 10;
            node->next = new ListNode(sum % 10);
            node = node->next;
            if (l1 != nullptr)
                l1 = l1->next;
            if (l2 != nullptr)
                l2 = l2->next;
        }
        return l->next;
    }
};

//141. Linked List Cycle
class Solution141 {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr)
            return false;
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};

//287. Find the Duplicate Number
class Solution287 {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];

        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

//24. Swap Nodes in Pairs
class Solution24 {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        auto next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        return next;
    }
};

//148. Sort List
class Solution148 {
private:
    // find middle of LL using slow and fast pointers
    ListNode* findLLMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // merges two sorted LLs
    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummy = new ListNode();
        ListNode* p = dummy;
        ListNode* p1 = head1;
        ListNode* p2 = head2;

        while (p1 != NULL && p2 != NULL) {
            if (p1->val < p2->val) {
                ListNode* temp = p1->next;
                p->next = p1;
                p1->next = NULL;
                p1 = temp;
            } else {
                ListNode* temp = p2->next;
                p->next = p2;
                p2->next = NULL;
                p2 = temp;
            }
            p = p->next;
        }

        if (p1 == NULL) {
            p->next = p2;
        } else if (p2 == NULL) {
            p->next = p1;
        }

        return dummy->next;
    }
public:
    // merge sort implementation
    ListNode* sortList(ListNode* head) {
        // base cases
        if (head == NULL)
            return NULL;
        if (head->next == NULL)
            return head;

        // split LL into two halves
        ListNode* middleOfLL = findLLMid(head);
        ListNode* leftHalf = head;
        ListNode* rightHalf = middleOfLL->next;
        middleOfLL->next = NULL; // this cuts off the right half from the left half

        // sort the two halves seperately and then merge them into one
        leftHalf = sortList(leftHalf);
        rightHalf = sortList(rightHalf);
        head = merge(leftHalf, rightHalf);

        return head;
    }
};

//86. Partition List
class Solution86 {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* p1 = new ListNode;
        ListNode* l1 = p1;
        ListNode* p2 = new ListNode;
        ListNode* l2 = p2;
        while (head != nullptr) {
            if (head->val < x) {
                l1->next = head;
                l1 = l1->next;
            }
            else {
                l2->next = head;
                l2 = l2->next;
            }
            head = head->next;
        }
        l2->next = nullptr;
        l1->next = p2->next;
        return p1->next;
    }
};

//61. Rotate List
class Solution61 {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k==0)
            return head;
        int n = 1;
        ListNode* node = head;
        while (node->next != nullptr) {
            node = node->next;
            n++;
        }
        int add = n- k % n;
        if (add==n) {
            return head;
        }
        node->next = head;
        while (add--) {
            node = node->next;
        }
        ListNode* ret = node->next;
        node->next = nullptr;
        return ret;
    }
};

//92. Reverse Linked List II
class Solution92 {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || head->next == nullptr)
            return head;
        right -= left;
        auto curr = head;
        ListNode* prev = nullptr;
        while(--left && curr != nullptr) {
            prev = curr;
            curr = curr->next;
        }
        auto leftNode = prev;

        while (right-- >= 0 && curr != nullptr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        if (leftNode != nullptr) {
            leftNode->next->next = curr;
            leftNode->next = prev;
        }
        else {
            head->next = curr;
            head = prev;
        }
        return head;
    }
};

//622. Design Circular Queue
class MyCircularQueue {
    int head;
    int count;
    vector<int> data;
    int size;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        head = 0;
        count = 0;
        size = k;
        data.resize(k);
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull())
            return false;
        data[(head + count) % size] = value;
        count++;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty())
            return false;
        head = ++head % size;
        count--;
        return true;
    }

    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty())
            return -1;
        return data[head];
    }

    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty())
            return -1;
        return data[(head + count - 1) % size];
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        if (count == 0) {
            return true;
        } else {
            return false;
        }
    }

    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        if (count == size) {
            return true;
        } else {
            return false;
        }
    }
};

//146. LRU Cache
class LRUCache {
    struct Node {
        int key;
        int value;
        Node(int k, int v):key(k), value(v) {}
    };
public:
    LRUCache(int capacity):cap(capacity) {}

    int get(int key) {
        if (itorMap.find(key) == itorMap.end())
            return -1;
        auto itor = itorMap[key];
        Node node(itor->key, itor->value);
        cacheList.erase(itor);
        cacheList.push_front(node);
        itorMap[key] = cacheList.begin();
        return node.value;
    }

    void put(int key, int value) {
        if (itorMap.find(key) != itorMap.end()) {
            auto itor = itorMap[key];
            cacheList.erase(itor);
        }
        else {
            if (cacheList.size() == cap) {
                itorMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
        }
        Node node(key, value);
        cacheList.push_front(node);
        itorMap[key] = cacheList.begin();
    }

private:
    list<Node> cacheList;
    unordered_map<int, list<Node>::iterator> itorMap;
    int cap;
};

//23. Merge k Sorted Lists
class Solution23 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        map<int, int> valCnt;
        ListNode* node;
        for (auto &list: lists) {
            node = list;
            while (node != nullptr) {
                valCnt[node->val]++;
                node = node->next;
            }
        }
        ListNode* pre = new ListNode;
        node = pre;
        for (auto &[value, count]: valCnt) {
            while(count--) {
                ListNode* newNode = new ListNode(value);
                node->next = newNode;
                node = node->next;
            }
        }
        return pre->next;
    }
};

//25. Reverse Nodes in k-Group
class Solution25 {
public:
    ListNode* reverseList(ListNode* head, ListNode* tail) {
        ListNode* pre = nullptr;
        ListNode* next = nullptr;
        ListNode* cur = head;
        while (cur != tail) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* ret = nullptr;
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* prev = new ListNode;
        while (fast != nullptr) {
            int count = k;
            while (count-- && fast != nullptr) {
                fast = fast->next;
            }
            if (fast == nullptr && count != -1) {
                prev->next = slow;
                break;
            }
            prev->next = reverseList(slow, fast);
            if (ret == nullptr)
                ret = prev->next;
            prev = slow;
            slow = fast;
        }
        return ret;
    }
};

#endif //NEETCODE150_LINKEDLIST_H
