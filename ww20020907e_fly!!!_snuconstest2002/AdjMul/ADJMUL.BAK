
#include "stdio.h"
#include "stdlib.h"

// cnt values
/*
	#define ABOVE5	37683u	// 32768 * 115 / 100 -> 1.15
	#define ABOVE4	36700u	// 32768 * 112 / 100 -> 1.12
	#define ABOVE3	35717u	// 32768 * 109 / 100 -> 1.09
	#define ABOVE2	34734u	// 32768 * 106 / 100 -> 1.06
	#define ABOVE1	33751u	// 32768 * 103 / 100 -> 1.03
	#define CENTER	32768u	// 32768 * 100 / 100 -> 1.00
	#define BELOW1	31785u	// 32768 *  97 / 100 -> 0.97
	#define BELOW2	30802u	// 32768 *  94 / 100 -> 0.94
	#define BELOW3	29819u	// 32768 *  91 / 100 -> 0.91
	#define BELOW4	28836u	// 32768 *  88 / 100 -> 0.88
	#define BELOW5	27853u	// 32768 *  85 / 100 -> 0.85
*/
	#define ABOVE5	(unsigned int)(32768. * 1.18) // 1.18
	#define ABOVE4	(unsigned int)(32768. * 1.15) // 1.15
	#define ABOVE3	(unsigned int)(32768. * 1.12) // 1.12
	#define ABOVE2	(unsigned int)(32768. * 1.09) // 1.09
	#define ABOVE1	(unsigned int)(32768. * 1.06) // 1.06
	#define CENTER	(unsigned int)(32768. * 1.00) // 1.00
	#define BELOW1	(unsigned int)(32768. * 0.97) // 0.99
	#define BELOW2	(unsigned int)(32768. * 0.94) // 0.98
	#define BELOW3	(unsigned int)(32768. * 0.91) // 0.97
	#define BELOW4	(unsigned int)(32768. * 0.88) // 0.96
	#define BELOW5	(unsigned int)(32768. * 0.85) // 0.95


// index
	#define iA5		254
	#define	iA4     229
	#define	iA3     204
	#define	iA2     178
	#define	iA1     153
	#define	iCT		127
	#define	iB1     101
	#define	iB2     76
	#define	iB3     50
	#define	iB4     25
	#define	iB5     0

void make_tbl(unsigned int *tbl, unsigned int x1, double y1, unsigned int x2, double y2);
void make_adj_mul_tbl();

void main()
{
	make_adj_mul_tbl();
}

void make_adj_mul_tbl()
{
	// KEY CODE ///////////////////
	// asm mov ax,word ptr A;
	// asm mul word ptr B;
	// asm mov word ptr C,dx;

	unsigned int adj_mul[256];
			 int i;

	// generate
	make_tbl(adj_mul,iB5,BELOW5,iB4,BELOW4);
	make_tbl(adj_mul,iB4,BELOW4,iB3,BELOW3);
	make_tbl(adj_mul,iB3,BELOW3,iB2,BELOW2);
	make_tbl(adj_mul,iB2,BELOW2,iB1,BELOW1);
	make_tbl(adj_mul,iB1,BELOW1,iCT,CENTER);
	make_tbl(adj_mul,iCT,CENTER,iA1,ABOVE1);
	make_tbl(adj_mul,iA1,ABOVE1,iA2,ABOVE2);
	make_tbl(adj_mul,iA2,ABOVE2,iA3,ABOVE3);
	make_tbl(adj_mul,iA3,ABOVE3,iA4,ABOVE4);
	make_tbl(adj_mul,iA4,ABOVE4,iA5,ABOVE5);
	make_tbl(adj_mul,iA5,ABOVE5,0xFF,ABOVE5);

	// write
	FILE *fp;
	if ((fp = fopen("adjmul.tbl","w")) == NULL)	{
		printf("FILE open error\n");
		exit(-1);
	}

	fprintf(fp, "\n   unsigned int adj_mul_tbl[]= {\n\n");

	fprintf(fp, "		   // ABOVE5        : %u cnts\n",ABOVE5);
	fprintf(fp, "		   // ABOVE4        : %u cnts\n",ABOVE4);
	fprintf(fp, "		   // ABOVE3        : %u cnts\n",ABOVE3);
	fprintf(fp, "		   // ABOVE2        : %u cnts\n",ABOVE2);
	fprintf(fp, "		   // ABOVE1        : %u cnts\n",ABOVE1);
	fprintf(fp, "		   // CENTER        : %u cnts\n",CENTER);
	fprintf(fp, "		   // BELOW1        : %u cnts\n",BELOW1);
	fprintf(fp, "		   // BELOW2        : %u cnts\n",BELOW2);
	fprintf(fp, "		   // BELOW3        : %u cnts\n",BELOW3);
	fprintf(fp, "		   // BELOW4        : %u cnts\n",BELOW4);
	fprintf(fp, "		   // BELOW5        : %u cnts\n\n",BELOW5);

	fprintf(fp, "		   // iA5           : %u \n",iA5);
	fprintf(fp, "		   // iA4           : %u \n",iA4);
	fprintf(fp, "		   // iA3           : %u \n",iA3);
	fprintf(fp, "		   // iA2           : %u \n",iA2);
	fprintf(fp, "		   // iA1           : %u \n",iA1);
	fprintf(fp, "		   // iCT           : %u \n",iCT);
	fprintf(fp, "		   // iB1           : %u \n",iB1);
	fprintf(fp, "		   // iB2           : %u \n",iB2);
	fprintf(fp, "		   // iB3           : %u \n",iB3);
	fprintf(fp, "		   // iB4           : %u \n",iB4);
	fprintf(fp, "		   // iB5           : %u \n\n",iB5);

	for(i=0;i<256;i++)
		fprintf(fp, "	%uu, // %3u , %1.5g \n",adj_mul[i],i, ((double)adj_mul[i] / (double)adj_mul[iCT]) );

	fprintf(fp,"     };\n\n");

	fclose(fp);
}
void make_tbl(unsigned int *tbl, unsigned int x1, double y1, unsigned int x2, double y2)
{
	double x, y;

	tbl[ x1 ] = (unsigned int)y1;
	tbl[ x2 ] = (unsigned int)y2;

	if ( x1 < x2 )
	{
		for (x = x1+1 ; x < x2 ; x++ )
		{
			y = ( y2 - y1 ) * ( x - x1 ) / ( x2 - x1 ) + y1;
			tbl[ x ] = (unsigned int)y;
		}
	}
	if ( x1 > x2 )
	{
		for (x = x2+1 ; x < x1 ; x++ )
		{
			y = ( y2 - y1 ) * ( x - x1 ) / ( x2 - x1 ) + y1;
			tbl[ x ] = (unsigned int)y;
		}
	}
}
