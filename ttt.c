/* Tic-Tac-Toe 超簡易版 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Title()
{
	printf("+-------------------------------+\n");
	printf("| The Most Simplest TIC-TAC-TOE |\n");
	printf("+-------------------------------+\n");
	printf("\n");
	printf("  位置の指定は行番号y，列番号x の順ね．\n");
	printf("    （番号は 0 から数えるよ．）\n");
	printf("  勝敗については自分達で判定すれや．\n");
	printf("  終了するには [Ctrl]+[D]．\n");
	printf("\n");
}

int Get(int *bd, int y, int x, int n)  
{
	if (x < 0) return (-1);		/* ハミ出し禁止 */
	if (x >= n) return (-1);	/* （バッファオーバラン防止） */
	if (y < 0) return (-1);
	if (y >= n) return (-1);

	return (bd[(y*n)+x]);
}

void Set(int *bd, int y, int x, int v, int n)
{ 
	if (x < 0) return;		/* ハミ出し禁止 */
	if (x >= n) return;		/* （バッファ−バラン防止） */
	if (y < 0) return;
	if (y >= n) return;

	bd[(y*n)+x] = v;
}

void Clear(int *bd, int n)
{
	for (int i = 0; i < n*n; i++)
			bd[i] = 0;
}

void Draw(int *bd, int n)
{
	printf("\n");
	for(int i = 0; i < n*n; i++){
		printf("%2d", bd[i]);
		if((i+1) % n == 0) printf("\n");
	}
	printf("\n");
}

int conv_y(int a, int n)
{
	int y;
	y = a/n;
	return y;
}

int conv_x(int a, int n)
{
	int x;
	x = a%n;
	return x;
}

int win(int *bd, int n)
{
	int x, y;
	int winner = 0;
	for(y = 0; y < n; y++){
		for(x = 0; x < n; x++){
			if(conv_y(((y*n)+x+2),n) == conv_y(((y*n)+x), n) ){
				if(bd[(y*n)+x] == 1 && bd[(y*n)+x+1] == 1 && bd[(y*n)+x+2] == 1){
					winner = 1;
					break;
				}
				else if(bd[(y*n)+x] == 2 && bd[(y*n)+x+1] == 2 && bd[(y*n)+x+2] == 2){
					winner = 2;
					break;
				}
			}

			if(conv_y(((y*n)+x+n+n), n) - conv_y(((y*n)+x), n) == 2){
				if(bd[(y*n)+x] == 1 && bd[(y*n)+x+n] == 1 && bd[(y*n)+x+n+n] == 1){
					winner = 1;
					break;
				}
				else if(bd[(y*n)+x] == 2 && bd[(y*n)+x+n] == 2 && bd[(y*n)+x+n+n] == 2){
					winner = 2;
					break;
				}
			}

			if(conv_y(((y*n)+x+n+n+2), n) - conv_y(((y*n)+x), n) == 2){
				if(bd[(y*n)+x] == 1 && bd[(y*n)+x+n+1] == 1 && bd[(y*n)+x+n+n+2] == 1){
					winner = 1;
					break;
				}
				else if(bd[(y*n)+x] == 2 && bd[(y*n)+x+n+1] == 2 && bd[(y*n)+x+n+n+2] == 2){
					winner = 2;
					break;
				}
			}

			if(conv_y(((y*n)+x+n+n-2), n) - conv_y(((y*n)+x), n) == 2){
				if(bd[(y*n)+x] == 1 && bd[(y*n)+x+n-1] == 1 && bd[(y*n)+x+n+n-2] == 1){
					winner = 1;
					break;
				}
				else if(bd[(y*n)+x] == 2 && bd[(y*n)+x+n-1] == 2 && bd[(y*n)+x+n+n-2] == 2){
					winner = 2;
					break;
				}
			}
		}
	}
	return winner;
}

void comp(int *bd, int n)
{
	srand(time(NULL));
	int p, q;

	while(1){
		p = rand()%n;
		q = rand()%n;

		if( Get(bd, p, q, n) == 0 ) break;
	}

	Set(bd, p, q, 2, n);
}

int main(void)
{
	int n, m;
	do{
		printf("ゲームモード　( 1. VS player || 2. VS COM ) >  ");
		scanf("%d", &m);
		if(m < 1 || m > 2) printf("もう一度入力してください。\n");
	}while(m < 1 || m > 2);

	do{
		printf("ゲーム盤のサイズ（３以上）>  ");
		scanf("%d", &n);
		if(n<3) printf("もう一度入力してください。\n");
	}while(n<3);

	int *board;
	board = (int *)malloc(sizeof(int)*n*n);

	int	y, x, player;

	Title();

	Clear(board, n);

	player = 1;
	while (1) {
		Draw(board, n);
		
		if(win(board, n)==1){
			printf("1P win!\n");
			goto END;
		}
		else if(win(board, n)==2){
			printf("2P win!\n");
			goto END;
		}

		while (1) {
			printf("%dP の番 > ", player);
			if (scanf("%d %d", &y, &x) == EOF) goto END;

			if (Get(board, y, x, n) == 0) break; 
			printf("nilai : %d\n", Get(board, y, x, n)  );
			printf("そこには置けません!!\nもう一度 ");
		}
		Set(board, y, x, player, n);

		if(m == 1) player = player%2 + 1;		/* 1→ 2，2→ 1 */
		else{
			if(win(board, n) != 1) comp(board, n);
		}	
	}

END:
	free(board);
	return (0);
}