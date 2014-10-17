#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH		64.65			 // mm
#define RADIUS		26.403585025622	 // mm
#define ONEBLK		180			 	 // mm
#define ANGLE		0.01570796327	 // rad/step  ,M_PI*0.9/180

void make_swing_S_tbl();
void main()
{
	make_swing_S_tbl();
}

void make_swing_S_tbl()
{
	FILE *fp;
	if ((fp = fopen("swing_S.tbl","w")) == NULL)	{
		printf("FILE open error\n");
		exit(-1);
	}

	fprintf(fp, "\n   unsigned int swing_S_tbl[]= {\n\n");

	fprintf(fp, "		   // Width			: %g mm \n",WIDTH);
	fprintf(fp, "		   // Wheel radius  : %g mm \n",RADIUS);
	fprintf(fp, "		   // Oneblock Size : %d mm \n",ONEBLK);
	fprintf(fp, "		   // One angle     : %g rad/step\n\n",ANGLE);

	double x;
	double steps;
	/*
	for( x=0; x < 20; x++ )	{
		steps = WIDTH / ANGLE / RADIUS * acos( 1 - x / WIDTH );
		fprintf(fp, "		   %d, // %d mm\n",(int)steps,(int)x);
	}
	for( x=20; x <= 90; x++ )	{
		fprintf(fp, "		   %d, // %d mm\n",(int)steps,(int)x);
	}
	*/
	for( x=0; x < 42; x++ )	{
		steps = WIDTH / ANGLE / RADIUS * acos( 1 - x / WIDTH );
		fprintf(fp, "		   %d, // %d mm\n",(int)steps,(int)x);
	}
	for( x=42; x <= 90; x++ )	{
		fprintf(fp, "		   %d, // %d mm\n",(int)steps,(int)x);
	}

	fprintf(fp,"     };\n\n");

	fclose(fp);
}
