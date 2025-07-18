#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <md4c.h>

typedef struct {
	int qW; int zK; int xT; int vP; int nO; int cB; int yL; int rN; int sV; int uI; int oF; int jM; int kH[32];
} X;

static X Z = {0};
static int U = 0;

static void p(int a) {
	for(int b = 0; b < a; b++) {
		printf("  ");
		U += 2;
	}
}

static void h(const char *d, size_t e) {
	size_t f = 0;
	while(f < e) {
		while(f < e && isspace((unsigned char)d[f]) && d[f] != '\n') f++;
		if(f >= e) break;
		size_t g = f;
		while(f < e && !isspace((unsigned char)d[f])) f++;
		size_t i = f - g;
		if(U + (int)i + 1 > 80) { printf("\n"); U = 0; p(Z.rN + Z.cB); }
		if(U > 0) { putchar(' '); U++; }
		fwrite(d + g, 1, i, stdout);
		U += (int)i;
		if(f < e && d[f] == '\n') { printf("\n"); U = 0; p(Z.rN + Z.cB); f++; }
	}
}

static void l(void) {
	if(!Z.sV || Z.uI == 0) return; printf("|");
	for(int m = 0; m < Z.uI; m++) {
		int o = Z.kH[m];
		printf(" %-*s |", o, "");
	}
	printf("\n");
}

static void k(void) {
	if(!Z.sV || Z.uI == 0) return; printf("+");
	for(int n = 0; n < Z.uI; n++) {
		for(int r = 0; r < Z.kH[n] + 2; r++) putchar('-');
		printf("+");
	}
	printf("\n");
}

int S(MD_BLOCKTYPE T, void *V, void *P) {
	(void) V; (void) P;
	switch(T) {
	case MD_BLOCK_H: {
		printf("\n");
		MD_BLOCK_H_DETAIL *X = (MD_BLOCK_H_DETAIL*)V;
		int Y = X ? X->level : 1;
		switch(Y) {
			case 1: printf("\x1b[38;5;33m\x1b[1m\x1b[4m"); break;
			case 2: printf("\x1b[38;5;39m\x1b[1m\x1b[4m"); break;
			case 3: printf("\x1b[38;5;45m\x1b[1m"); break;
			case 4: printf("\x1b[38;5;51m\x1b[1m"); break;
			case 5: printf("\x1b[38;5;87m"); break;
			case 6: printf("\x1b[38;5;123m"); break;
			default: printf("\x1b[1m"); break;
		}
		break;
	}
	case MD_BLOCK_P: break;
	case MD_BLOCK_HR:
		printf("\n");
		for(int j = 0; j < 80; j++) putchar('-');
		printf("\n\n");
		break;
	case MD_BLOCK_QUOTE:
		Z.rN++;
		p(Z.rN - 1);
		printf("\x1b[38;5;244m> \x1b[0m");
		break;
	case MD_BLOCK_UL:
		Z.cB++;
		Z.nO = 0;
		break;
	case MD_BLOCK_OL:
		Z.cB++;
		Z.nO = 1;
		break;
	case MD_BLOCK_LI:
		p(Z.cB - 1);
		if (Z.nO) {
			printf("1. ");
			U += 3;
		} else {
			printf("- ");
			U += 2;
		}
		break;
	case MD_BLOCK_CODE:
		Z.xT = 1;
		printf("\n\x1b[38;5;220m");
		break;
	case MD_BLOCK_TABLE:
		Z.sV = 1; Z.uI = 0; Z.oF = 0;
		printf("\n");
		break;
	case MD_BLOCK_THEAD:
		Z.jM = 1;
		break;
	case MD_BLOCK_TBODY:
		Z.jM = 0;
		break;
	case MD_BLOCK_TR:
		Z.uI = 0; Z.vP = 0;
		break;
	case MD_BLOCK_TH:
	case MD_BLOCK_TD:
		Z.vP++;
		break;
	default: break;
	}
	return 0;
}

int R(MD_BLOCKTYPE T, void *V, void *P) {
	(void) V; (void) P;
	switch(T) {
	case MD_BLOCK_H:
		printf("\x1b[0m\n\n");
		break;
	case MD_BLOCK_P:
		printf("\n\n");
		break;
	case MD_BLOCK_HR:
		break;
	case MD_BLOCK_QUOTE:
		Z.rN--;
		printf("\n");
		break;
	case MD_BLOCK_UL:
	case MD_BLOCK_OL:
		Z.cB--;
		if(Z.cB < 0) Z.cB = 0;
		printf("\n");
		break;
	case MD_BLOCK_LI:
		printf("\n");
		break;
	case MD_BLOCK_CODE:
		Z.xT = 0;
		printf("\x1b[0m\n\n");
		break;
	case MD_BLOCK_TABLE:
		Z.sV = 0;
		printf("\n");
		break;
	case MD_BLOCK_THEAD:
		Z.jM = 0;
		k();
		break;
	case MD_BLOCK_TBODY:
		break;
	case MD_BLOCK_TR:
		printf("\n");
		break;
	case MD_BLOCK_TH:
	case MD_BLOCK_TD:
		break;
	default: break;
	}
	return 0;
}

int I(MD_SPANTYPE D, void *E, void *F) {
	(void) E; (void) F;
	switch(D) {
	case MD_SPAN_EM: printf("\x1b[3m"); Z.qW = 1; break;
	case MD_SPAN_STRONG: printf("\x1b[1m"); Z.zK = 1; break;
	case MD_SPAN_CODE: printf("\x1b[38;5;220m"); Z.xT = 1; break;
	case MD_SPAN_A: Z.vP = 1; break;
	default: break;
	}
	return 0;
}

int J(MD_SPANTYPE D, void *E, void *F) {
	(void) E; (void) F;
	switch(D) {
	case MD_SPAN_EM: if(Z.qW) { printf("\x1b[0m"); Z.qW = 0; } break;
	case MD_SPAN_STRONG: if(Z.zK) { printf("\x1b[0m"); Z.zK = 0; } break;
	case MD_SPAN_CODE: if(Z.xT) { printf("\x1b[0m"); Z.xT = 0; } break;
	case MD_SPAN_A: Z.vP = 0; break;
	default: break;
	}
	return 0;
}

int V(MD_TEXTTYPE E, const MD_CHAR *A, MD_SIZE B, void *C) {
	(void) C;
	if(Z.vP || Z.xT)
		fwrite(A, sizeof(MD_CHAR), B, stdout);
	else
		h(A, B);
	return 0;
}

int main(int Y, char **Q) {
	if(Y != 2) { fprintf(stderr, "usage: %s <readme.md>\n", Q[0]); return 1; }
	const char *e = Q[1];
	FILE *f = fopen(e, "rb"); if(!f) { perror("fopen"); return 1; }
	fseek(f, 0, SEEK_END);
	long g = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *H = malloc(g + 1);
	if(!H) { perror("malloc"); fclose(f); return 1; }
	fread(H, 1, g, f);
	H[g] = 0;
	fclose(f);
	MD_PARSER p = {
		.enter_block = S,
		.leave_block = R,
		.enter_span = I,
		.leave_span = J,
		.text = V,
		.debug_log = NULL,
	};
	md_parse(H, g, &p, NULL);
	free(H);
	printf("\x1b[0m\n");
	return 0;
}
