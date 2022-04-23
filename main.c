#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:6031)
#pragma warning (disable: 4996)

typedef struct Node {
	struct Node* next;
	int num;
}Node;

Node* setNode(int n) {
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	newNode->num = n;
	return newNode;
}

// set the road to S
void markupS(Node** all, Node* root, int S, int front, int* Sarray) {
	while (root != NULL) {
		if (root->num != front) {
			Sarray[root->num - 1] = S;
			markupS(all, all[root->num - 1], root->num, S, Sarray);
		}
		root = root->next;
	}
}

// set the road to R
void markupR(Node** all, Node* root, int R, int front, int* Rarray) {
	while (root != NULL) {
		if (root->num != front) {
			Rarray[root->num - 1] = R;
			markupR(all, all[root->num - 1], root->num, R, Rarray);
		}
		root = root->next;
	}
}

int main() {
	int N, Q, S, R;
	scanf("%d%d%d%d", &N, &Q, &S, &R);
	Node** all = (Node**)calloc(N, sizeof(Node*));
	int* ans = (int*)calloc(N, sizeof(int));
	int a, b;
	if (S == R) {
		ans[0] = R;
		for (int i = 1; i < N; i++) {
			scanf("%d%d", &a, &b);
			ans[i] = R;
		}
	}
	else {
		// connect
		for (int i = 1; i < N; i++) {
			scanf("%d%d", &a, &b);
			Node* x = setNode(b);
			x->next = all[a - 1];
			all[a - 1] = x;
			Node* y = setNode(a);
			y->next = all[b - 1];
			all[b - 1] = y;
		}
		// set Sarray and Rarray
		int* Sarray = (int*)calloc(N, sizeof(int));
		int* Rarray = (int*)calloc(N, sizeof(int));
		// markup S
		markupS(all, all[S - 1], S, -1, Sarray);
		// markup R
		markupR(all, all[R - 1], R, -1, Rarray);
		// set ans
		int answer = 0;
		for (int i = 0; i < N; i++) {
			if (all[i]->next == NULL) {
				answer = all[i]->num;
				if (answer == S || answer == R) {
					ans[i] = all[i]->num;
					continue;
				}
				int* tmpans = (int*)calloc(N, sizeof(int));
				int n = 0;
				while (Sarray[answer - 1] == Rarray[answer - 1]) {
					answer = Sarray[answer - 1];
					if (ans[answer - 1] != 0) {
						answer = ans[answer - 1];
						break;
					}
					tmpans[n] = answer;
					n++;
				}
				ans[i] = answer;
				ans[Sarray[i] - 1] = answer;
				for (int i = 0; i < n; i++) {
					ans[tmpans[i] - 1] = answer;
				}
			}
		}
		ans[S - 1] = S;
		ans[R - 1] = R;
		int tmp = Sarray[R - 1];
		while (tmp != 0) {
			ans[tmp - 1] = tmp;
			tmp = Sarray[tmp - 1];
		}
	}
	// Query
	for (int i = 0; i < Q; i++) {
		int q;
		scanf("%d", &q);
		printf("%d\n", ans[q - 1]);
	}
}