Approach 1: Complete Brute Force
Approach 2: Using sets/hash
   ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        set<ListNode*> st;
        ListNode* temp = headA;
        while(temp!=nullptr){
            st.insert(temp);
            temp=temp->next;
        }
        temp=headB;
        while(temp!=nullptr){
            if(st.find(temp) != st.end()){
                return temp;
            }
            temp=temp->next;
        }
        return nullptr;
    }

Approach 3: optimal way , suppose ll1 size = len1 , ll2 size= len2 , cut down the diff of lengths from the starting part from whichever ll is larger.
  and then check nodes by traversal , if same node appear then return it , else nullptr.

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int len1=0, len2=0;
        ListNode* temp = headA;
        while(temp!=nullptr){
            len1++;
            temp=temp->next;
        }
        temp=headB;
        while(temp!=nullptr){
            len2++;
            temp=temp->next;
        }
        ListNode* a=headA , *b=headB;
        if(len1>len2){
            while(len1>len2){
                a=a->next;
                len1--;
            }
        }
        if(len1<len2){
            while(len1<len2){
                b=b->next;
                len2--;
            }
        }


        while(a!=nullptr && b!=nullptr){
            if(a==b) return a;
            a= a->next;
            b= b->next;
        }
        return nullptr;
    }

Approach 4: Best Approach , keep traversing both a(of ll1), b(of ll2) until they dont have the intersecting node, 
  if a reaches nullptr and b doesnot reach , then start a again 
  if b reaches nullptr and b doesnot reach , then start b again
code:
 ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==nullptr || headB== nullptr){
            return nullptr;
        }
        ListNode* a=headA , *b=headB;
        while(a!=b){
            a= a==nullptr ? headA : a->next;
            b= b==nullptr ? headB : b->next;
        }
        return a;
  }
