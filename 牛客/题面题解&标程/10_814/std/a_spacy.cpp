#include <bits/stdc++.h>
using namespace std;

char s[100471], t[200471];
int n, k, locs, loct, r[100471], stk[100471], top;

void debug(int l) {
	t[loct++] = '<';
	t[loct++] = s[l];
	t[loct++] = s[l + 1];
	t[loct++] = s[l + 2];
	t[loct++] = s[l + 3];
	t[loct++] = s[l + 4];
	t[loct++] = s[l + 5];
	t[loct++] = s[l + 6];
	t[loct++] = s[l + 7];
	t[loct++] = s[l + 8];
	t[loct++] = s[l + 9];
	t[loct++] = '>';
}

void expression(int l, int r) {
	while (isspace(s[l])) {
		l++;
	}
	while (isspace(s[r])) {
		r--;
	}
//	debug(l);
	for (int i = l; i <= r; i++) {
		if (!isspace(s[i])) {
			if (s[i] == '+' && s[i - 1] != '+' && s[i + 1] != '+' || s[i] == '+' && s[i - 1] == '+' && s[i - 2] == '+' || s[i] == '&' || s[i] == '/' || s[i] == '=' && s[i - 1] != '=') {
				t[loct++] = ' ';
			}
			t[loct++] = s[i];
			if (s[i] == '+' && s[i - 1] != '+' && s[i + 1] != '+' || s[i] == '+' && s[i - 1] == '+' && s[i - 2] == '+' || s[i] == '&' || s[i] == '/' || s[i] == '=' && s[i + 1] != '=' || s[i] == ',') {
				t[loct++] = ' ';
			}
		}
	}
//	debug(r);
}

void declaration(int l, int r) {
	while (isspace(s[l])) {
		l++;
	}
	for (int i = l, j = 0; i < r; i++) {
		if (!j || !isspace(s[i])) {
			t[loct++] = isspace(s[i]) ? ' ' : s[i];
		}
		j |= isspace(s[i]);
	}
}

void signature(int l, int r) {
	while (isspace(s[l])) {
		l++;
	}
	int x = l;
	while (s[x] != '(') {
		x++;
	}
	int y = x - 1;
	while (isspace(s[y])) {
		y--;
	}
	if (y == l + 3 && s[l] == 'm' && s[l + 1] == 'i' && s[l + 2] == 'a' && s[l + 3] == 'n') {
		t[loct++] = 'm';
		t[loct++] = 'i';
		t[loct++] = 'a';
		t[loct++] = 'n';
	} else {
		declaration(l, x);
	}
	t[loct++] = '(';
	while (true) {
		int y = x + 1;
		while (s[y] != ',' && s[y] != ')') {
			y++;
		}
		if (s[x] == ',') {
			t[loct++] = ' ';
		}
		declaration(x + 1, y);
		t[loct++] = s[y];
		x = y;
		if (s[y] == ')') {
			t[loct++] = ' ';
			return;
		}
	}
}

int block(int);

int ifx(int l) {
	t[loct++] = 'i';
	t[loct++] = 'f';
	t[loct++] = ' ';
	t[loct++] = '(';
	while (isspace(s[l])) {
		l++;
	}
	l += 2;
	while (isspace(s[l])) {
		l++;
	}
	int x = r[l];
	expression(++l, x - 1);
	t[loct++] = ')';
	t[loct++] = ' ';
	x = block(x + 1);
	while (isspace(s[x])) {
		x++;
	}
	if (s[x] == 'o' && s[x + 1] == 't' && s[x + 2] == 'h' && s[x + 3] == 'e' && s[x + 4] == 'r' && s[x + 5] == 'w' && s[x + 6] == 'i' && s[x + 7] == 's' && s[x + 8] == 'e' && (s[x + 9] == '{' || isspace(s[x + 9]))) {
		t[loct++] = ' ';
		t[loct++] = 'o';
		t[loct++] = 't';
		t[loct++] = 'h';
		t[loct++] = 'e';
		t[loct++] = 'r';
		t[loct++] = 'w';
		t[loct++] = 'i';
		t[loct++] = 's';
		t[loct++] = 'e';
		t[loct++] = ' ';
		x += 9;
		while (isspace(s[x])) {
			x++;
		}
		if (s[x] == 'i' && s[x + 1] == 'f' && (s[x + 2] == '(' || isspace(s[x + 2]))) {
			return ifx(x);
		} else {
			x = block(x);
		}
	}
	return x;
}

int block(int l) {
	while (isspace(s[l])) {
		l++;
	}
	t[loct++] = '{';
	t[loct++] = '\n';
	l++;
	while (true) {
		while (isspace(s[l])) {
			l++;
		}
		if (s[l] == '}') {
			t[loct++] = '}';
			return l + 1;
		} else if (s[l] == 'i' && s[l + 1] == 'f' && (s[l + 2] == '(' || isspace(s[l + 2]))) {
			l = ifx(l);
		} else if (s[l] == 'r' && s[l + 1] == 'e' && s[l + 2] == 'p' && s[l + 3] == 'e' && s[l + 4] == 'a' && s[l + 5] == 't' && (s[l + 6] == '{' || isspace(s[l + 6]))) {
			t[loct++] = 'r';
			t[loct++] = 'e';
			t[loct++] = 'p';
			t[loct++] = 'e';
			t[loct++] = 'a';
			t[loct++] = 't';
			t[loct++] = ' ';
			l = block(l + 6);
			while (isspace(s[l])) {
				l++;
			}
			t[loct++] = ' ';
			t[loct++] = 'w';
			t[loct++] = 'h';
			t[loct++] = 'i';
			t[loct++] = 'l';
			t[loct++] = 'e';
			t[loct++] = ' ';
			t[loct++] = '(';
			l += 5;
			while (isspace(s[l])) {
				l++;
			}
			expression(l + 1, r[l] - 1);
			t[loct++] = ')';
			t[loct++] = '?';
			int x = r[l] - 1;
			while (s[x] != '?') {
				x++;
			}
			l = x + 1;
		} else if (s[l] == 'w' && s[l + 1] == 'h' && s[l + 2] == 'i' && s[l + 3] == 'l' && s[l + 4] == 'e' && (s[l + 5] == '(' || isspace(s[l + 5]))) {
			t[loct++] = 'w';
			t[loct++] = 'h';
			t[loct++] = 'i';
			t[loct++] = 'l';
			t[loct++] = 'e';
			t[loct++] = ' ';
			t[loct++] = '(';
			l += 5;
			while (isspace(s[l])) {
				l++;
			}
			int x = r[l];
			expression(++l, x - 1);
			t[loct++] = ')';
			t[loct++] = ' ';
			l = block(x + 1);
		} else if (s[l] == 'r' && s[l + 1] == 'e' && s[l + 2] == 't' && s[l + 3] == 'u' && s[l + 4] == 'r' && s[l + 5] == 'n' && (s[l + 6] == '(' || isspace(s[l + 6]))) {
			t[loct++] = 'r';
			t[loct++] = 'e';
			t[loct++] = 't';
			t[loct++] = 'u';
			t[loct++] = 'r';
			t[loct++] = 'n';
			t[loct++] = ' ';
			l += 6;
			int x = l;
			while (s[x] != '?') {
				x++;
			}
			expression(l, x - 1);
			t[loct++] = '?';
			l = x + 1;
		} else if (s[l] == '!') {
			t[loct++] = '!';
			l++;
		} else {
			int x = l;
			while (s[x] != '=' && s[x] != '?') {
				x++;
			}
			int a = l, b = x - 1;
			while (isspace(s[a])) {
				a++;
			}
			while (isspace(s[b])) {
				b--;
			}
			if (!isalpha(s[a]) && s[a] != '_') {
				goto aaa;
			}
			while (isalnum(s[a]) || s[a] == '_') {
				a++;
			}
			if (!isspace(s[a])) {
				goto aaa;
			}
			while (isspace(s[a])) {
				a++;
			}
			if (!isalpha(s[a]) && s[a] != '_') {
				goto aaa;
			}
			while (isalnum(s[a]) || s[a] == '_') {
				a++;
			}
			if (a - 1 != b) {
				goto aaa;
			}
			declaration(l, x);
			if (s[x] == '?') {
				l = x + 1;
			} else if (s[x] == '=') {
				t[loct++] = ' ';
				t[loct++] = '=';
				t[loct++] = ' ';
				int y = x;
				while (s[y] != '?') {
					y++;
				}
				expression(x + 1, y - 1);
				l = y + 1;
			} else {
				aaa:
				while (s[x] != '?') {
					x++;
				}
				expression(l, x - 1);
				l = x + 1;
			}
			t[loct++] = '?';
		}
		t[loct++] = '\n';
	}
}

int main() {
	scanf("%d", &k);
	fread(s, 100000, 1, stdin);
	n = strlen(s);
	while (isspace(s[locs])) {
		locs++;
	}
	if (s[locs] == '/') {
		int x = locs;
		while (locs <= x + 1 || s[locs - 1] != '/') {
			t[loct++] = s[locs++];
		}
		t[loct++] = '\n';
	}
	for (int i = locs, j = locs; i < n; i++) {
		if (s[i] == '(') {
			stk[top++] = i;
		} else if (s[i] == ')') {
			r[stk[--top]] = i;
		}
	}
	while (true) {
		int x = locs; // x begin of a codeblock
		while (x < n && s[x] != '{') {
			x++;
		}
		if (x == n) {
			for (int i = 0, j = 0; i < loct - 1; i++) {
				putchar(t[i]);
				if (t[i] == '\n') {
					if (t[i + 1] == '}') {
						j -= k;
					}
					for (int k = 0; k < j; k++) {
						putchar(' ');
					}
				} else if (t[i] == '{') {
					j += k;
				}
			}
			// fprintf(stderr, "%ld", clock());
			return 0;
		}
		signature(locs, x);
		locs = block(x);
		t[loct++] = '\n';
	}
}
