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
