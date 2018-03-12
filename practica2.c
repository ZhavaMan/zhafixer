#include <stdio.h>

#define TAM 10

typedef char tipoDato;

typedef struct Stack {
	tipoDato pila[TAM];
	int top;
} stack;

int llena(stack *s) {
	return s->top == (TAM - 1) ? 1 : 0;
}

int vacia(stack *s) {
	if ((*s).top == -1) {
		return 1;
	} else {
		return 0;
	}
}

void push(stack *s, tipoDato elem) {
	s->pila[++s->top] = elem;
}

tipoDato pop(stack *s) {
	tipoDato tmp = s->pila[s->top];
	s->top--;
	return tmp;
}

void inicializar(stack *s) {
	s->top = -1;
}

void imprime(stack *s) {
	for (int i = s->top; i > -1; i--)
	{
		printf("%c", s->pila[i]);
	}
	printf("\n");
}

void invierte(stack *s) {
	stack reverse1, reverse2;
	inicializar(&reverse1);
	inicializar(&reverse2);

	for (int i = s->top; i > -1; i--) {
		push(&reverse1, pop(s));
	}

	for (int i = reverse1.top; i > -1; i--) {
		push(&reverse2, pop(&reverse1));
	}

	for (int i = reverse2.top; i > -1; i--) {
		push(s, pop(&reverse2));
	}
}

int clasificador(char element) {
	int f = 0;

	if (element == '(' || element == ')') {
		f = 4;
	} else if (element == '^') {
		f = 3;
	} else if (element == '*' || element == '/') {
		f = 2;
	} else if (element == '+' || element == '-') {
		f = 1;
	}

	return f;
}

int main() {
	int i = 0, f = 0, g = 0, p = 0, q = 0;
	char input[30], e = ' ', w = ' ';
	stack infix,
		operators,
		postfix,
		tmpg;

	inicializar(&infix);
	inicializar(&operators);
	inicializar(&postfix);
	inicializar(&tmpg);

	printf("Infix expression: ");
	scanf("%s", input);

	while (input[i] != '\0') {
		push(&infix, input[i]);
		i++;
	}

	invierte(&infix);

	while (!vacia(&infix)) {
		e = pop(&infix);
		f = clasificador(e);

		if (f) {
			if (f == 4) {
				if ( e == '(') {
					push(&tmpg, g); // tmpg = g;
					g = 0;
					push(&operators, e);
					continue;
				} else if (e == ')') {
					g = pop(&tmpg); // g = tmpg;
					for (int i = operators.top; i > -1; i--) {
						w = pop(&operators);
						if(w == '(') {
							break;
						} else {
							push(&postfix, w);
						}
					}
					continue;
				}
			}

			if (f <= g) {
				push(&postfix, pop(&operators));
				push(&operators, e);
			} else {
				push(&operators, e);
			}
			g = f;
		} else {
			push(&postfix, e);
		}
	}

	if (!vacia(&operators)) {
		for (int i = operators.top; i > -1; i--) {
			push(&postfix, pop(&operators));
		}
	}

	invierte(&postfix);
	printf("Postfix expression: ");
	imprime(&postfix);
	printf("\n");

	return 0;
}