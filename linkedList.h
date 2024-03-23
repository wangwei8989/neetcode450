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

//142. Linked List Cycle II
class Solution142 {
public:
    ListNode *detectCycle(ListNode *head) {
        if ( head== nullptr || head->next== nullptr) {
            return nullptr;
        }
        ListNode *fast = head;
        ListNode *slow = head;
        while(fast->next!= nullptr && fast->next->next!= nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                ListNode *ans = head;
                while(fast != ans) {
                    fast = fast->next;
                    ans = ans->next;
                }
                return ans;
            }
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

//2130. Maximum Twin Sum of a Linked List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution2130 {
public:
    int pairSum(ListNode* head) {
        ListNode *fast = head, *slow = head;

        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        slow = reverseList(slow);

        int mx = 0;
        while(head && slow) {
            mx = max(mx, head->val + slow->val);
            head = head->next;
            slow = slow->next;
        }

        return mx;
    }
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* NEXT = NULL;

        while(curr) {
            NEXT = curr->next;
            curr->next = prev;
            prev = curr;
            curr = NEXT;
        }

        return prev;
    }
};

//1721. Swapping Nodes in a Linked List
class Solution1721 {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        if(head == NULL || head -> next == NULL)
            return head;

        ListNode *ptr = head, *beg = head, *end = head;
        int a = 0;
        while(ptr != NULL) {
            a++;
            if(a == k)
                beg = ptr;
            if(a >= k + 1)
                end = end -> next;
            ptr = ptr -> next;
        }
        int temp = beg -> val;
        beg -> val = end -> val;
        end -> val = temp;
        return head;
    }
};

//460. LFU Cache
// 缓存的节点信息
struct Node {
    int key, val, freq;
    Node(int _key,int _val,int _freq): key(_key), val(_val), freq(_freq){}
};
class LFUCache {
    int minfreq, capacity;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int _capacity) {
        minfreq = 0;
        capacity = _capacity;
        key_table.clear();
        freq_table.clear();
    }

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;
        list<Node>::iterator node = it -> second;
        int val = node -> val, freq = node -> freq;
        freq_table[freq].erase(node);
        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == capacity) {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            }
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            // 与 get 操作基本一致，除了需要更新缓存的值
            list<Node>::iterator node = it -> second;
            int freq = node -> freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) minfreq += 1;
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};

//1472. Design Browser History
class BrowserHistory {
private:
    stack<string> history;
    stack<string> future;

public:
    BrowserHistory(string homepage) {
        history.push(homepage);
    }

    void visit(string url) {
        history.push(url);
        while (!future.empty()) {
            future.pop(); // Clear the forward history
        }
    }

    string back(int steps) {
        while (steps-- && history.size() > 1) {
            future.push(history.top());
            history.pop();
        }
        return history.top();
    }

    string forward(int steps) {
        while (steps-- && !future.empty()) {
            history.push(future.top());
            future.pop();
        }
        return history.top();
    }
};

//147. Insertion Sort List
class Solution1147 {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(head == NULL || head -> next == NULL) {
            return head;
        }

        ListNode *ptr1 = head -> next, *sortedPtr = head;
        while(ptr1 != NULL) {
            if(ptr1 -> val < sortedPtr -> val) {
                ListNode *ptr2 = head, *lagPtr = head;
                while(true) {
                    if(ptr2 -> val > ptr1 -> val) {
                        if(ptr2 == head) {
                            sortedPtr -> next = ptr1 -> next;
                            ptr1 -> next = head;
                            head = ptr1;
                            ptr1 = sortedPtr -> next;
                            break;
                        }
                        else {
                            sortedPtr -> next = ptr1 -> next;
                            ptr1 -> next = ptr2;
                            lagPtr -> next = ptr1;
                            ptr1 = sortedPtr -> next;
                            break;
                        }
                    }
                    lagPtr = ptr2;
                    ptr2 = ptr2 -> next;
                }

            } else {
                sortedPtr = sortedPtr -> next;
                ptr1 = ptr1 -> next;
            }
        }

        return head;
    }
};

//725. Split Linked List in Parts
class Solution725 {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int length = 0;
        ListNode* curr = head;
        while (curr) {
            length++;
            curr = curr->next;
        }

        int partSize = length / k;
        int extra = length % k;

        vector<ListNode*> result;
        curr = head;
        for (int i = 0; i < k; i++) {
            ListNode* dummy = new ListNode(0);
            ListNode* prev = dummy;
            for (int j = 0; j < partSize + (i < extra ? 1 : 0); j++) {
                if (curr) {
                    prev->next = new ListNode(curr->val);
                    prev = prev->next;
                    curr = curr->next;
                }
            }
            result.push_back(dummy->next);
        }

        return result;
    }
};

//328. Odd Even Linked List
class Solution328 {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head== nullptr ){
            return head;
        }
        ListNode *stepOdd = head;
        ListNode *Even = new ListNode(0);
        ListNode *stepEven = Even;
        while(stepOdd->next!= nullptr){
            stepEven->next = stepOdd->next;
            stepEven = stepEven->next;
            stepOdd->next = stepOdd->next->next;
            if(stepOdd->next!= nullptr){
                stepOdd = stepOdd->next;
            }
        }
        stepEven->next = nullptr;
        stepOdd->next = Even->next;
        return head;
    }
};
#endif //NEETCODE150_LINKEDLIST_H
