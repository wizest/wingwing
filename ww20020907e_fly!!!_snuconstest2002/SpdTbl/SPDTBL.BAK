#include <stdio.h>
#include <stdlib.h>

#define RADIUS		2.6403585025622	 // cm
#define ONEBLK		18.0		 // cm
#define ANGLE		0.01570796327	 // rad/step  ,M_PI*0.9/180
#define ONESTEP 	(RADIUS * ANGLE) // cm
#define CYCLE		10000000l	 // 10MHz

#define SPD_MIN    	6.5		// cm/s
#define STEP_MAX   	2345//1600	// steps

#define ACCL1      	50.0		// cm/s^2
#define ACCL2	   	450.0		// cm/s^2
#define ACCL3	   	300.0//350.0  	// cm/s^2
#define ACCL4	   	350.0//400.0  	// cm/s^2
#define ACCL5	   	320.0//300.0	// cm/s^2
#define ACCL6		160.0//150.0 	// cm/s^2

#define SECTION1	10		// steps
#define SECTION2	300		// steps
#define SECTION3	600		// steps
#define SECTION4	1000		// steps
#define SECTION5	1300		// steps
#define SECTION6	STEP_MAX	// steps

#define tSPD_MIN	6.5		// cm/s
#define tSTEP_MAX	600		// steps

#define tACCL1		ACCL1		// cm/s^2
#define tACCL2		ACCL2		// cm/s^2
#define tACCL3		(tACCL2/2)	// cm/s^2
#define tACCL4		(tACCL3/2)	// cm/s^2

#define tSECTION1	SECTION1	// steps
#define tSECTION2	SECTION2 	// steps
#define tSECTION3	400      	// steps
#define tSECTION4	tSTEP_MAX	// steps


void make_spd_tbl_F();	// forward
void make_spd_tbl_T();	// turn

void main()
{
	make_spd_tbl_F();
	make_spd_tbl_T();
}

void make_spd_tbl_F()
{
	FILE *fp;
	if ((fp = fopen("speed.tbl","w")) == NULL)	{
		printf("FILE open error\n");
		exit(-1);
	}

	fprintf(fp, "\n   unsigned int fspeed[]= {\n\n");

	fprintf(fp, "		   // Wheel radius  : %g cm \n",RADIUS);
	fprintf(fp, "		   // Oneblock Size : %g cm \n",ONEBLK);
	fprintf(fp, "		   // One angle     : %g rad/step\n",ANGLE);
	fprintf(fp, "		   // Spd Min       : %g cm/s\n",SPD_MIN);
	fprintf(fp, "		   // Step Max      : %d steps\n\n",STEP_MAX);

	fprintf(fp, "		   // Accl1         : %g cm/s^2\n",ACCL1);
	fprintf(fp, "		   // Accl2         : %g cm/s^2\n",ACCL2);
	fprintf(fp, "		   // Accl3         : %g cm/s^2\n",ACCL3);
	fprintf(fp, "		   // Accl4         : %g cm/s^2\n",ACCL4);
	fprintf(fp, "		   // Accl5         : %g cm/s^2\n",ACCL5);
	fprintf(fp, "		   // Accl6         : %g cm/s^2\n\n",ACCL6);

	fprintf(fp, "		   // Section1      : %d steps\n",SECTION1);
	fprintf(fp, "		   // Section2      : %d steps\n",SECTION2);
	fprintf(fp, "		   // Section3      : %d steps\n",SECTION3);
	fprintf(fp, "		   // Section4      : %d steps\n",SECTION4);
	fprintf(fp, "		   // Section5      : %d steps\n",SECTION5);
	fprintf(fp, "		   // Section6      : %d steps\n\n",SECTION6);


	double step;
	double speed      = SPD_MIN;
	double need_time  = ONESTEP 	/ speed;
	double need_count = need_time 	* CYCLE;
	double delta_speed;

	// SECTION 1
	fprintf(fp, "	// SECTION 1\n");
	for( step=0 ; step < SECTION1 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = ACCL1 * need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	// SECTION 2
	fprintf(fp, "	// SECTION 2\n");
	for( step=SECTION1 ; step < SECTION2 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = ACCL2 * need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	// SECTION 3
	fprintf(fp, "	// SECTION 3\n");
	for( step=SECTION2 ; step < SECTION3 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = ACCL3		* need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	// SECTION 4
	fprintf(fp, "	// SECTION 4\n");
	for( step=SECTION3 ; step < SECTION4 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = ACCL4 * need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	// SECTION 5
	fprintf(fp, "	// SECTION 5\n");
	for( step=SECTION4 ; step < SECTION5 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = ACCL5 * need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	// SECTION 6
	fprintf(fp, "	// SECTION 6\n");
	for( step=SECTION5 ; step < SECTION6 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = ACCL6 * need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}

	fprintf(fp,"     };\n\n");

	fclose(fp);
}
void make_spd_tbl_T()
{
	FILE *fp;
	if ((fp = fopen("speed.tbl","a")) == NULL)	{
		printf("FILE open error\n");
		exit(-1);
	}

	fprintf(fp, "\n   unsigned int tspeed[]= {\n\n");

	fprintf(fp, "		   // Wheel radius  : %g cm \n",RADIUS);
	fprintf(fp, "		   // Oneblock Size : %g cm \n",ONEBLK);
	fprintf(fp, "		   // One angle     : %g rad/step\n",ANGLE);
	fprintf(fp, "		   // Spd Min       : %g cm/s\n",tSPD_MIN);
	fprintf(fp, "		   // Step Max      : %d steps\n",tSTEP_MAX);
	fprintf(fp, "		   // Accl1         : %g cm/s^2\n",tACCL1);
	fprintf(fp, "		   // Accl2         : %g cm/s^2\n",tACCL2);
	fprintf(fp, "		   // Accl3         : %g cm/s^2\n",tACCL3);
	fprintf(fp, "		   // Accl4         : %g cm/s^2\n\n",tACCL4);

	fprintf(fp, "		   // Section1      : %d steps\n",tSECTION1);
	fprintf(fp, "		   // Section2      : %d steps\n",tSECTION2);
	fprintf(fp, "		   // Section3      : %d steps\n",tSECTION3);
	fprintf(fp, "		   // Section4      : %d steps\n\n",tSECTION4);

	double step;
	double speed      = tSPD_MIN;
	double need_time  = ONESTEP 	/ speed;
	double need_count = need_time 	* CYCLE;
	double delta_speed;

	fprintf(fp, "	// SECTION 1\n");
	for( step=0 ; step < tSECTION1 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = tACCL1	* need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	fprintf(fp, "	// SECTION 2\n");
	for( step=tSECTION1 ; step < tSECTION2 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = tACCL2	* need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	fprintf(fp, "	// SECTION 3\n");
	for( step=tSECTION2 ; step < tSECTION3 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = tACCL3	* need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}
	fprintf(fp, "	// SECTION 4\n");
	for( step=tSECTION3 ; step < tSECTION4 ; step++ )	{
		fprintf(fp, "		%uu, // %d steps, %g cm/s \n",(unsigned int)need_count,(unsigned int)(step),speed);

		delta_speed = tACCL4	* need_time;
		need_time   = ONESTEP 	/ ( speed + delta_speed );
		need_count  = need_time * CYCLE;
		speed       = ONESTEP 	/ need_time;
	}




	fprintf(fp,"     };\n\n");

	fclose(fp);
}
