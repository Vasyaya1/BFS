#include <iostream>
#include <fstream>

using namespace std;

//очередь
struct node{
	int info;
	node* left, * right;
};
typedef node* tinfo;
struct elem {
	tinfo info;
	elem* next;
	elem* prev;
};
struct Queue {
	elem* first, * last;
};
Queue* create_queue() {
	Queue* q = new Queue;
	q->first = NULL;
	q->last = NULL;
	return q;
}
bool empty(Queue* q) {
	return q->first == NULL;
}
void EnQueue(Queue*& q, tinfo x) {
	elem* p = new elem;
	p->info = x;
	p->next = NULL;
	if (empty(q)) {
		p->next = NULL;
		p->prev = NULL;
		q->last = p;
	}
	else {
		p->next = q->first;
		p->prev = NULL;
		q->first->prev = p;
	}
	q->first = p;
}
tinfo DeQueue(Queue*& q) {
	if (!empty(q)) {
		elem* p = q->last;
		q->last = q->last->prev;
		if (q->last != NULL)
			q->last->next = NULL;
		else
			q->first = q->last;
		tinfo x = p->info;
		delete p;
		return x;
	}
}
void show(node* root) {
	if (root) {
		cout << root->info << " ";
		show(root->left);
		show(root->right);
	}
}

 node* node_create(int x, node* l = NULL, node* r = NULL) {
	node* p = new node;
	p->info = x;
	p->left = l;
	p->right = r;
	return p;
}

 ////////////////////////////////////////
 node* create_tree(ifstream& in) {
	 if (in.eof())
		 return NULL;
	 Queue* q = create_queue();
	 node* root = new node;
	 in >> root->info;
	 root->left = root->right = NULL;
	 EnQueue(q, root);
	 int x;
	 while (in >> x) {
		 node* p = DeQueue(q);
		 p->left = new node;
		 p->left->info = x;
		 p->left->left = p->left->right = NULL;
		 EnQueue(q, p->left);
		 in >> x;
		 if (!in.eof()) {
			 p->right = new node;
			 p->right->left = NULL;
			 p->right->right = NULL;
			 EnQueue(q, p->right);
		 }
	 }
	 while (!empty(q)) {
		 DeQueue(q);
		 return root;
	 }
 }
 //1)
void LR(node* root) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	while (!empty(q)) {
		node* p = DeQueue(q);
		cout << p->info << " ";
		if (p->left)
			EnQueue(q, p->left);
		if (p->right)
			EnQueue(q, p->right);
	}
}

//2)
void H(node* root) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1, next = 0;
	int h = 0;
	while (!empty(q)) {
		node* p = DeQueue(q);
		cur--;
		if (p->left) {
			EnQueue(q, p->left);
			next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
		}
		if (cur == 0) {
			cout << '\n';
			cur = next;
			next = 0;
			h++;
		}
	}
	cout << h;
}

//3)
void length(node* root, int x) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int k = 1;
	while (!empty(q)) {
		node* p = DeQueue(q);
		if (p->info == x) {
			cout << k;
			break;
		}
		if (p->left) {
			EnQueue(q, p->left);
		}
		if (p->right) {
			EnQueue(q, p->right);
		}
		k++;
	}
}
//4)
void vertex_count(node* root, int n) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1, next = 0;
	int k = 0;
	while (!empty(q)) {
		node* p = DeQueue(q);
		if (k == n) {
			cout << cur;
			break;
		}
		cur--;
		if (p->left) {
			EnQueue(q, p->left);
				next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
				next++;
		}
		if (cur == 0) {
			cur = next;
			next = 0;
			k++;
		}
	}
}

//5)
void width(node* root) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
    int max1 = 0;
	int cur = 1, next = 0;
	while (!(empty(q))) {
		node* p = DeQueue(q);
		cur--;
		if (p->left) {
			EnQueue(q, p->left);
			next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
		}
		if (cur == 0) {
			max1 = max(max1, next);
			cur = next;
			next = 0;
		}
	}
	cout << max1;
}

//6)
//void zad6(node*& root, int n) {
//	node* p = new node;
//	p->info = 1;
//	int i = 0;
//	while (i != n) {
//	    root = node_create()
//	}
//}


//7) неправильно
//bool zad7(node* root) {
//	if (!root)
//		return true;
//	Queue* q = create_queue();
//	EnQueue(q, root);
//	node* p0 = DeQueue(q);
//	int cur = 1, next = 0;
//	int min1 = 0;
//	while (!empty(q)) {
//		while (cur != 0) {
//			node* p = DeQueue(q);
//			cur--;
//			min1 = min(p->info, min1);
//		}
//		
//
//			if (p0->info <= p->info) {
//				return false;
//			}
//			if (p->left) {
//				EnQueue(q, p->left);
//			}
//			if (p->right) {
//				EnQueue(q, p->right);
//			}
//			if (cur == 0) {
//				cur = next;
//				next = 0;
//				p0 = p;
//			}
//		
//	}
//	return true;
//}

//7)
//bool zad7(node* root) {
//	if (!root) return 0;
//	Queue* q = create_queue();
//	EnQueue(q, root);
//	int size, k = 1;
//
//	while (!empty(q)) {
//		size = k;
//		int* values = new int[size];
//		int n = 0;
//		for (int i = 0; i < size; i++) {
//			node* p = DeQueue(q);
//			k--;
//			values[i] = p->info;
//
//			if (p->left) {
//				EnQueue(q, p->left);
//				k++;
//			}
//			if (p->right) {
//				EnQueue(q, p->right);
//				k++;
//			}
//		}
//
//		if (!empty(q)) {
//			int* nextValues = new int[k];
//			for (int i = 0; i < k; i++) {
//				node* p = DeQueue(q);
//				nextValues[i] = p->info;
//				EnQueue(q, p);
//			}
//
//
//			for (int i = 0; i < size; i++) {
//				for (int j = 0; j < k; j++) {
//					if (nextValues[j] > values[i])
//						return false;
//				}
//			}
//		}
//	}
//	return true;
//}

//8)
bool summ(node* root) {
	if (!root)
		return 0;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1, next = 0;
	int k = 1;
	while (!empty(q)) {
		int sum = 0;
		k = cur;
		for (int i = 0; i < k; i++) {
			node* p = DeQueue(q);
			cur--;
			sum += p->info;
			if (p->left) {
				EnQueue(q, p->left);
				next++;
			}
			if (p->right) {
				EnQueue(q, p->right);
				next++;
			}

		}

		if (cur == 0) {
			if (!empty(q)) {
				int next_sum = 0;
				for (int i = 0; i < next; i++) {
					node* p = DeQueue(q);
					next_sum += p->info;
					EnQueue(q, p);
					}
				if (sum < next_sum)
					return false;
			}
			cur = next;
			next = 0;

		}
	}
	return true;
}

bool sum2(node* root) {
	if (!root) return 0;
	Queue* q = create_queue();
	EnQueue(q, root);
	int size, k = 1;
	while (!empty(q)) {
		int sum = 0;
		size = k;
		for (int i = 0; i < size; i++) {
			node* p = DeQueue(q);
			k--;
			sum += p->info;

			if (p->left) {
				EnQueue(q, p->left);
				k++;
			}
			if (p->right) {
				EnQueue(q, p->right);
				k++;
			}

		}
		if (!empty(q)) {
			int nextSum = 0;
			for (int i = 0; i < k; i++) {
				node* p = DeQueue(q);
				nextSum += p->info;
				EnQueue(q, p);
			}
			if (sum < nextSum)
				return false;

		}


	}
	return true;
}

//9)
	bool search(node * root) {
		if (!root)
			return true;
		Queue* q = create_queue();
		EnQueue(q, root);
		while (!empty(q)) {
			node* p = DeQueue(q);
			if (p->left->info = p->info) {
				return true;
				break;
			}
			EnQueue(q, p->left);

			if (p->right->info == p->info) {
				return true;
				break;
			}
			EnQueue(q, p->right);
			if (p->left)
				EnQueue(q, p->left);
			if (p->right)
				EnQuefeue(q, p->right);
		}
		return false;
	}
int main() {
	ifstream in("bfs.txt");
		node* root = node_create(10);

		root->left = node_create(3);
		root->right = node_create(7);
     	root->left->left = node_create(2);
		root->left->right = node_create(1);
		root->right->left = node_create(3);
		root->right->right = node_create(2);
	//node* root = create_tree(in);
		if (summ(root)) {
			cout << "yes";
		}
		else cout << "no";
		if (sum2(root))
			cout << "YES";
		else cout << "NO";
}
