/* tested on Fedora 24, 64 bit machine using gcc 6.31 */


#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_HEIGHT 256
#define MAX_WIDTH 256

;

typedef struct BMP{

	unsigned short bType;           /* Magic number for file */
	unsigned int   bSize;           /* Size of file */
	unsigned short bReserved1;      /* Reserved */
	unsigned short bReserved2;      /* ... */
	unsigned int   bOffBits;        /* Offset to bitmap data */

	unsigned int  bISize;           /* Size of info header */
	unsigned int  bWidth;          /* Width of image */
	unsigned int   bHeight;         /* Height of image */
	unsigned short bPlanes;         /* Number of color planes */
	unsigned short bBitCount;       /* Number of bits per pixel */
	unsigned int  bCompression;    /* Type of compression to use */
	unsigned int  bSizeImage;      /* Size of image data */
	int           bXPelsPerMeter;  /* X pixels per meter */
	int      	    bYPelsPerMeter;  /* Y pixels per meter */
	unsigned int   bClrUsed;        /* Number of colors used */
	unsigned int   bClrImportant;   /* Number of important colors */
}BMP;

//void RGB2YUV();
int Read_BMP_Header(char *filename, int *h, int *w,BMP *bmp)
{

	FILE *f;
	int *p;
	f=fopen("test.bmp","r");
	printf("\nReading BMP Header ");
	fread(&bmp->bType,sizeof(unsigned short),1,f);
	p=(int *)bmp;
	fread(p+1,sizeof(BMP)-4,1,f);
	if (bmp->bType != 19778) {
		printf("Error, not a BMP file!\n");
		return 0;
	}

	*w = bmp->bWidth;
	*h = bmp->bHeight;
	return 1;
}

void Read_BMP_Data(char *filename,int *h,int *w,BMP *bmp)
{

	int i,j,i1,H,W,Wp,PAD;
	unsigned char *RGB;
	FILE *f;
	printf("\nReading BMP Data ");
	f=fopen(filename,"r");
	fseek(f, 0, SEEK_SET);
	fseek(f, bmp->bOffBits, SEEK_SET);
	W = bmp->bWidth;
	H = bmp->bHeight;
	printf("\nheight = %d width= %d \n",H,W);
	PAD = (3 * W) % 4 ? 4 - (3 * W) % 4 : 0;
	Wp = 3 * W + PAD;
	RGB = (unsigned char *)malloc(Wp*H *sizeof(unsigned char));
	for(i=0;i<Wp*H;i++) RGB[i]=0;
	fread(RGB, sizeof(unsigned char), Wp * H, f);

//	for(i=0;i<256;i++)
//	printf("%d ",RGB[i]);

	FILE **output=(FILE**)malloc(sizeof(FILE*));
	char hex[3][3]; //hex[0] means B hex[1] means G hex[2] means R
	output[0]=fopen("string0.sh","w");
	output[1]=fopen("string1.sh","w");
	output[2]=fopen("string2.sh","w");
	if(output[0]==NULL || output[1]==NULL || output[2]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}
	
	fprintf(output[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(output[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(output[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	//traversing row wise starting from (1,1) to (256,256)
	//string0 blue
	//string1 green
	//string2 red
	
	i1=0;
	fprintf(output[0],"./win32/rel/flcli -v 1443:0007 -a \"w1 ");
	fprintf(output[1],"./win32/rel/flcli -v 1443:0007 -a \"w11 ");
	fprintf(output[2],"./win32/rel/flcli -v 1443:0007 -a \"w21 ");
	for (i = 0; i < H; i+=3){
		for (j = 0; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w2 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w12 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w22 ");
	for (i = 1; i < H; i+=3){
		for (j = 0; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w3 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w13 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w23 ");
	for (i = 2; i < H; i+=3){
		for (j = 0; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w4 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w14 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w24 ");
	for (i = 0; i < H; i+=3){
		for (j = 1; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w5 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w15 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w25 ");
	for (i = 1; i < H; i+=3){
		for (j = 1; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w6 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w16 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w26 ");
	for (i = 2; i < H; i+=3){
		for (j = 1; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w7 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w17 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w27 ");
	for (i = 0; i < H; i+=3){
		for (j = 2; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w8 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w18 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w28 ");
	for (i = 1; i < H; i+=3){
		for (j = 2; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}

	i1=0;
	fprintf(output[0],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w9 ");
	fprintf(output[1],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w19 ");
	fprintf(output[2],"\"\n./win32/rel/flcli -v 1443:0007 -a \"w29 ");
	for (i = 2; i < H; i+=3){
		for (j = 2; j < W; j+=3){
			i1=i*(Wp)+j*3;
			sprintf(hex[0],"%02x",RGB[i1]);
			fprintf(output[0],hex[0]);

			sprintf(hex[1],"%02x",RGB[i1+1]);
			fprintf(output[1],hex[1]);

			sprintf(hex[2],"%02x",RGB[i1+2]);
			fprintf(output[2],hex[2]);
		}
	}
	fprintf(output[0],"\"");
	fprintf(output[1],"\"");
	fprintf(output[2],"\"");

	
	fclose(output[0]);
	fclose(output[1]);
	fclose(output[2]);

	//Start connection with FPGA
	char cmd[]="sh fpga-link_init.sh";
	system(cmd);
	//Send data to FPGA
	char cmd0[]="sh string0.sh";
	system(cmd0);
	char cmd1[]="sh string1.sh";
	system(cmd1);
	char cmd2[]="sh string2.sh";
	system(cmd2);

	fclose(f);
	free(RGB);
}

///void YUV2RGB();
int write_BMP_Header(char *filename,int *h,int *w,BMP *bmp)
{
	FILE *f;
	int *p;
	f=fopen(filename,"w");
	printf("\n Writing BMP Header ");
	fwrite(&bmp->bType,sizeof(unsigned short),1,f);
	p=(int *)bmp;
	fwrite(p+1,sizeof(BMP)-4,1,f);
	return 1;
}




void write_BMP_Data(char *filename,int *h,int *w,BMP *bmp){

	int i,j,i1,H,W,Wp,PAD;
	unsigned char *RGB;
	FILE *f;
	printf("\nWriting BMP Data\n");
	f=fopen(filename,"w");
	fseek(f, 0, SEEK_SET);
	fseek(f, bmp->bOffBits, SEEK_SET);
	W = bmp->bWidth;
	H = bmp->bHeight;
	printf("\nheight = %d width= %d ",H,W);
	PAD = (3 * W) % 4 ? 4 - (3 * W) % 4 : 0;
	Wp = 3 * W + PAD;
	RGB = (unsigned char *)malloc(Wp* H * sizeof(unsigned char));
	fread(RGB, sizeof(unsigned char), Wp * H, f);


	///////////////////////////// 	COMMANDS FOR READING DATA FROM FPGA /////////////////////
	FILE **read=(FILE**)malloc(sizeof(FILE*));
	FILE **outputfinal=(FILE**)malloc(sizeof(FILE*));
	int temp;
	char cmd0[]="sh blue_read.sh";
	char cmd1[]="sh green_read.sh";
	char cmd2[]="sh red_read.sh";

		//		File i correspond to RAM i of that color  //
////////////	File 1 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r1 1ce5 \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r11 1ce5 \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r21 1ce5 \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	unsigned char hexb[8000] = "";
    size_t bytesb = 0;
    bytesb = fread ( &hexb, 1, 8000, outputfinal[0]);
	unsigned char hexg[8000] = "";
    size_t bytesg = 0;
    bytesg = fread ( &hexg, 1, 8000, outputfinal[1]);
	unsigned char hexr[8000] = "";
    size_t bytesr = 0;
    bytesr = fread ( &hexr, 1, 8000, outputfinal[2]);

    int b=1,g=1,r=1;
	for (i = 0; i < H; i+=3){
		for (j = 0; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb[b++]);
			RGB[i1+1] = (int)hexg[g++];
			RGB[i1+2] = (int)(hexr[r++]);
		}
	}

	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 2 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r2 1c8f \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r12 1c8f \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r22 1c8f \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	unsigned char hexb1[8000] ="";
	unsigned char hexg1[8000] ="";
	unsigned char hexr1[8000] ="";	
    bytesb = 0;
    bytesb = fread ( &hexb1, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg1, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr1, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 1; i < H; i+=3){
		for (j = 0; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb1[b++]); 
			RGB[i1+1] = (int)(hexg1[g++]);
			RGB[i1+2] = (int)(hexr1[r++]);
		}
	}

	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 3 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r3 1c8f \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r13 1c8f \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r23 1c8f \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}


	unsigned char hexb2[8000] ="";
	unsigned char hexg2[8000] ="";
	unsigned char hexr2[8000] ="";
	
    bytesb = 0;
    bytesb = fread ( &hexb2, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg2, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr2, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 2; i < H; i+=3){
		for (j = 0; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb2[b++]); 
			RGB[i1+1] = (int)(hexg2[g++]);
			RGB[i1+2] = (int)(hexr2[r++]);
		}
	}
	
	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 4 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r4 1c8f \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r14 1c8f \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r24 1c8f \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	;

	unsigned char hexb3[8000] ="";
	unsigned char hexg3[8000] ="";
	unsigned char hexr3[8000] ="";
	
    bytesb = 0;
    bytesb = fread ( &hexb3, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg3, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr3, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 0; i < H; i+=3){
		for (j = 1; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb3[b++]); 
			RGB[i1+1] = (int)(hexg3[g++]);
			RGB[i1+2] = (int)(hexr3[r++]);
		}
	}
	

	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 5 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r5 1c3a \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r15 1c3a \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r25 1c3a \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	;
	
	unsigned char hexb4[8000] ="";
	unsigned char hexg4[8000] ="";
	unsigned char hexr4[8000] ="";

	
    bytesb = 0;
    bytesb = fread ( &hexb4, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg4, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr4, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 1; i < H; i+=3){
		for (j = 1; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb4[b++]); 
			RGB[i1+1] = (int)(hexg4[g++]);
			RGB[i1+2] = (int)(hexr4[r++]);
		}
	}
	
	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 6 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r6 1c3a \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r16 1c3a \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r26 1c3a \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	;

	unsigned char hexb5[8000] ="";
	unsigned char hexg5[8000] ="";
	unsigned char hexr5[8000] ="";
	
    bytesb = 0;
    bytesb = fread ( &hexb5, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg5, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr5, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 2; i < H; i+=3){
		for (j = 1; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb5[b++]); 
			RGB[i1+1] = (int)(hexg5[g++]);
			RGB[i1+2] = (int)(hexr5[r++]);
		}
	}

	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 7 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r7 1c8f \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r17 1c8f \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r27 1c8f \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	;

	unsigned char hexb6[8000] ="";
	unsigned char hexg6[8000] ="";
	unsigned char hexr6[8000] ="";
	
    bytesb = 0;
    bytesb = fread ( &hexb6, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg6, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr6, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 0; i < H; i+=3){
		for (j = 2; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb6[b++]); 
			RGB[i1+1] = (int)(hexg6[g++]);
			RGB[i1+2] = (int)(hexr6[r++]);
		}
	}

	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 8 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r8 1c3a \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r18 1c3a \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r28 1c3a \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	;
	
	unsigned char hexb7[8000] ="";
	unsigned char hexg7[8000] ="";
	unsigned char hexr7[8000] ="";

	
    bytesb = 0;
    bytesb = fread ( &hexb7, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg7, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr7, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 1; i < H; i+=3){
		for (j = 2; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb7[b++]); 
			RGB[i1+1] = (int)(hexg7[g++]);
			RGB[i1+2] = (int)(hexr7[r++]);
		}
	}
	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);

////////////	File 9 	//////////

	read[0]=fopen("blue_read.sh","w");
	read[1]=fopen("green_read.sh","w");
	read[2]=fopen("red_read.sh","w");
	if(read[0]==NULL || read[1]==NULL || read[2]==NULL)
	{
		puts("Cannot open read file");
		exit(1);
	}
	fprintf(read[0],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[1],"cd C:/makestuff/libs/libfpgalink-20120621\n");
	fprintf(read[2],"cd C:/makestuff/libs/libfpgalink-20120621\n");


	fprintf(read[0],"./win32/rel/flcli -v 1443:0007 -a \"r9 1c3a \\\"blue_write.txt\\\"\"");
	fprintf(read[1],"./win32/rel/flcli -v 1443:0007 -a \"r19 1c3a \\\"green_write.txt\\\"\"");
	fprintf(read[2],"./win32/rel/flcli -v 1443:0007 -a \"r29 1c3a \\\"red_write.txt\\\"\"");

	fclose(read[0]);
	fclose(read[1]);
	fclose(read[2]);

	//Read data from FPGA
	
	system(cmd0);
	system(cmd1);
	system(cmd2);

	//Read from text file and write to image
	outputfinal[0]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\blue_write.txt","rb");
	outputfinal[1]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\green_write.txt","rb");
	outputfinal[2]=fopen("C:\\makestuff\\libs\\libfpgalink-20120621\\red_write.txt","rb");
	if(outputfinal[0]==NULL || outputfinal[1]==NULL || outputfinal[1]==NULL)
	{
		puts("Cannot open output file");
		exit(1);
	}

	unsigned char hexb8[8000] ="";
	unsigned char hexg8[8000] ="";
	unsigned char hexr8[8000] ="";

	
    bytesb = 0;
    bytesb = fread ( &hexb8, 1, 8000, outputfinal[0]);
	
    bytesg = 0;
    bytesg = fread ( &hexg8, 1, 8000, outputfinal[1]);
	
    bytesr = 0;
    bytesr = fread ( &hexr8, 1, 8000, outputfinal[2]);

    b=g=r=1;
	for (i = 2; i < H; i+=3){
		for (j = 2; j < W; j+=3){
			i1=i*(Wp)+j*3;
			RGB[i1] = (int)(hexb8[b++]); 
			RGB[i1+1] = (int)(hexg8[g++]);
			RGB[i1+2] = (int)(hexr8[r++]);
		}
	}

	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);
//	for(i=0;i<256;i++)
//	printf("%d ",RGB[i]);

	fwrite(RGB, sizeof(unsigned char), Wp * H, f);
	fclose(f);
	fclose(outputfinal[0]);
	fclose(outputfinal[1]);
	fclose(outputfinal[2]);
	free(RGB);
}


int main(){

	int PERFORM;
	int h,w;
	BMP b;
	int i,j;
	BMP *bmp=&b;

	Read_BMP_Header("test.bmp",&h,&w,bmp);
	Read_BMP_Data("test.bmp",&h,&w,bmp);


	write_BMP_Header("lowpass.bmp",&h,&w,bmp);
	write_BMP_Data("lowpass.bmp",&h,&w,bmp);
	printf("\n");
	return 0;
}
