#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NIL -1

int test_biggest = 0;
int biggest_scc = 0;
int number_connections_scc = 0;
int number_of_scc = 0;
int visited = 0;

typedef struct edge Edge;
typedef struct stack Stack;
typedef struct vertex Vertex;
typedef struct list List;
typedef struct stack_head StackHead;

struct vertex {
	int id;
	int d;
	int low;
	struct edge *connect;
};

struct edge {
    int id;
    struct edge *next;
};

struct stack {
	int stack;
	struct vertex *vertex;	
};

struct stack_head {
	struct list* first;
};

struct list {
	int id;
	struct list* next;
};

void create_edge(Stack* stack, int p1, int target_id);
void print_list(Stack* stack, int n);
Stack* create_stack(int n);
void create_vertex(Stack* stack, int id);
StackHead* create_list();
void push (StackHead* stack, Stack* list, int n);
int pop (StackHead* stack, Stack* list);
void print_stack(StackHead* stack);
void scc_tarjan(Stack *stack, StackHead *head, int number_vertices);
void tarjan_visit(Stack *stack, Vertex *vertex, StackHead *head);



int main() {
	Stack* stack;
	StackHead* stackhead;
	int n_people, n_connections, i, p1, p2;
	scanf("%d %d", &n_people, &n_connections);
	stack = create_stack(n_people);
	stackhead = create_list();
	for( i = 0; i<n_connections; i++) {
		scanf("%d %d", &p1, &p2);
		create_edge(stack, p1, p2);
	}
	scc_tarjan(stack, stackhead, n_people);
	printf("%d\n%d\n%d\n", number_of_scc, biggest_scc, number_connections_scc);
	return 0;	
}

void create_vertex(Stack* stack, int id) {
	Vertex *ptr = (Vertex*)malloc(sizeof(Vertex));
	if(ptr == NULL)
	{
		exit(-1);
	}
	ptr->id = id + 1;
	ptr->connect = NULL;
	ptr->d = NIL;
	ptr->low = NIL;
	stack[id].vertex = ptr;
	stack[id].stack = 0;
}

StackHead* create_list() {
	StackHead *list;
	list = (StackHead*)malloc(sizeof(StackHead));
	list->first = NULL;
	return list;
}

void push (StackHead* stack, Stack* list, int n) {
	List* ptr;
	List* curr;
	curr = stack->first;
	ptr = (List*)malloc(sizeof(List));
	ptr->id = n;
	ptr->next = NULL;
	if (curr == NULL) {
		stack->first = ptr;
	}
	else {
		stack->first = ptr;
		ptr->next = curr;
	}
	list[n-1].stack = 1;
}

int pop (StackHead* stack, Stack* list) {
	int i;
	List* curr = stack->first;
	if (curr != NULL) {
		i = curr->id;
		stack->first = curr->next;
		free(curr);
		list[i-1].stack = 0;
	}
	else if (curr == NULL) {
		stack->first = NULL;
		i = -1;
	}
	return i;
}

void create_edge(Stack* stack, int p1, int target_id) {
	Vertex* v = stack[p1-1].vertex;
	Edge *curr;
	Edge *ptr = (Edge*)malloc(sizeof(Edge));
	if(ptr == NULL)
	{
		exit(-1);
	}
	ptr->id = target_id;
	ptr->next = NULL;
	curr = v->connect;
	if (curr == NULL) {
		v->connect = ptr;
	}
	else {
		v->connect = ptr;
		ptr->next = curr;
	}
}

Stack* create_stack(int n) {
	Stack *stack;
	int i;
	stack = (Stack*)malloc(sizeof(Stack)*n);
	for (i = 0; i < n; i++) {
		create_vertex(stack, i);
	}
	return stack;
}

void print_list(Stack* stack, int n) {
    Vertex *ptr;
		Edge* ptr2;
		int i;
		for (i = 0; i < n; i++) {
			ptr = stack[i].vertex;
			if (ptr->connect != NULL) {
				ptr2 = ptr->connect;
				for( ; ptr2 != NULL; ptr2 = ptr2->next) {
					printf("v:[%d] liga a [%d]\n", ptr->id, ptr2->id);
				}
			}
		}
}

void print_stack(StackHead* stack) {
    List* ptr = stack->first;
		printf("stack: -");
    while(ptr != NULL)
    {
        printf("-[%d]-", ptr->id);
        ptr = ptr->next;
    }
		printf("-\n");
}

void scc_tarjan(Stack *stack, StackHead *head, int number_vertices) {
    int index;
    Vertex *curr;
    for(index = 0; index < number_vertices; index++) {
        curr = stack[index].vertex;
        if(curr->d == NIL) {
            tarjan_visit(stack, curr, head);
        }
    }
}

void tarjan_visit(Stack *stack, Vertex *vertex, StackHead *head) {
	int i;
	Edge* aux;
	Vertex* curr;
	vertex->d = visited;
	vertex->low = visited;
	visited++;
	push(head, stack, vertex->id);
	aux = vertex->connect;
	while(1) {
		if (aux == NULL) { break; }
		curr = stack[((aux->id)-1)].vertex;
		if (curr->d == NIL) {
			tarjan_visit(stack, curr, head);
			if (vertex->low > curr->low) { 
				vertex->low = curr->low; 
			}
		}
		else if (stack[((curr->id)-1)].stack == 1) {
			if (vertex->low > curr->d) { 
				vertex->low = curr->d; 
			} 
		}
		aux = aux->next;
	}
	
	if (vertex->low == vertex->d) {
		i = pop (head, stack);
		if (i != -1) {
			if (i != vertex->id) {
				while(1) {
					test_biggest++;
					i = pop (head, stack);
					if (i == vertex->id) { 
						test_biggest++; 
						if ((head->first != NULL && stack[i-1].vertex->connect == NULL) || head->first == NULL) {
							number_connections_scc++;
						}
						break; 
					}
					if (i == -1) { 
						test_biggest++;
						number_connections_scc++; 
						break; 
					}
				}
			}
			else {
				if ((head->first != NULL && ((stack[i-1].vertex->connect == NULL) || (stack[i-1].vertex->connect->id == i))) || (head->first == NULL && stack[i-1].vertex->connect == NULL)) {
					number_connections_scc++;
				}
				test_biggest++;
			}
		}
		else {
			number_connections_scc++; 
			test_biggest++;
		}
		number_of_scc++;
		if (test_biggest > biggest_scc) { biggest_scc = test_biggest; }
		test_biggest = 0;
	}
}
