#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long GetFileSize(FILE *dosya);

FILE *input;
FILE *output;

int main(int argc, char *argv[]) {
	char dosyaAdi[100]="\0";
	
	printf("Dosya adi..: "); 	
	scanf("%s",&dosyaAdi);
	
	input=fopen(dosyaAdi, "rw+");
	if(NULL == input)
    {
        printf("%s bulunamadi!!!\r\n",dosyaAdi);
        return 1;
    }
    
    unsigned long long dosyaBoyutu=GetFileSize(input);
	printf("Dosya boyutu: %lu byte \r\n\r\n",dosyaBoyutu);
	
	
	unsigned long long baslangic_adresi=0;
	printf("Baslangic adresi..: ");
	scanf("%lu",&baslangic_adresi);
	printf("\r\n");
	
	unsigned long long kacByte=0;
	printf("Kac Byte[0=EndOfLine]..: ");
	scanf("%lu",&kacByte);
	printf("\r\n");
	if(kacByte==0){
		kacByte=dosyaBoyutu-baslangic_adresi;
	}
	
	
	unsigned int kacKarakterSonraEnterGelsin=0;
	printf("Kac eleman sonra satirbasi yapilsin[0=yapilmasin]..: ");
	scanf("%int",&kacKarakterSonraEnterGelsin);
	printf("\r\n");
	
	
	


	
	unsigned int byteSize=0; //bu char olursa , kacKarakterSonraEnterGelsin deðiþkenini 0 yapýyor nedense
	printf("[1=8bit,2=16bit,4=32bit]..: ");
	scanf("%d",&byteSize);
	printf("\r\n");
	
	
	unsigned int endian=0;
	if(byteSize>1){
		printf("[0=BigEndian,1=LittleEndian]..: ");
		scanf("%int",&endian);
		printf("\r\n");
	}


	char outputFileName[100]="\0";
	sprintf(outputFileName,"%s_array.txt",dosyaAdi);
	output=fopen(outputFileName, "w+");
	if(NULL == output)
    {
        printf("%s olusturulamadi!!!\r\n",outputFileName);
        return 1;
    }	
	
	
	
	if(byteSize==1)	fprintf(output,"unsigned char buffer[%d]={\r\n",kacByte);
	else if(byteSize==2) fprintf(output,"unsigned short buffer[%d]={\r\n",kacByte/2);
	else if(byteSize==4) fprintf(output,"unsigned int buffer[%d]={\r\n",kacByte/4);
	else {
		printf("Bytesize Error! \r\n");
		goto SON;
	}
	
			
			
				
	
	fseek(input,baslangic_adresi, SEEK_SET);
	
	unsigned long long i=0,e=0;
	while(i<kacByte){
		unsigned char oku1[1]={0};
		unsigned short oku_2[1]={0};
		unsigned int oku_4[1]={0};
		
		
		fseek(input, i+baslangic_adresi, SEEK_SET); //bunu koymayince yanlis veri okuyor
			
		//fread(oku,byteSize,byteSize,input); //fread(oku,sizeof(char),byteSize,input);
		if(byteSize==1)	fread(oku1,sizeof(char),1,input);
		if(byteSize==2) fread(oku_2,sizeof(short),1,input);
		if(byteSize==4) fread(oku_4,sizeof(int),1,input);
	
		
			
		if(endian==0){
			unsigned char a,b,c,d;
	

			a=(oku_2[0])&0x00FF;
			b=(oku_2[0]&0xFF00)>>8;
			
			oku_2[0]=(a<<8)|b;
			
			a=oku_4[0]&0x000000FF;
			b=(oku_4[0]&0x0000FF00)>>8;
			c=(oku_4[0]&0x00FF0000)>>16;
			d=(oku_4[0]&0xFF000000)>>24;
			
			
			
			oku_4[0]=(a<<24) | (b<<16) | (c<<8) | d;	
			
		}
	
	
		if(byteSize==1)	fprintf(output,"0x%02X",oku1[0]);
		if(byteSize==2) fprintf(output,"0x%04X",oku_2[0]);
		if(byteSize==4) fprintf(output,"0x%08X",oku_4[0]);
	
		if(i<kacByte-1)fprintf(output,",");
		
		e++;

		if(kacKarakterSonraEnterGelsin!=0 && e>=kacKarakterSonraEnterGelsin){ 
			e=0;
			fprintf(output,"\n");
		}
		
		i+=byteSize;
	}
	
	fprintf(output,"\n};\n");
	
	
	printf("islem tamamlanmistir\r\n");


	
	SON:
	
	fclose(input);
	fclose(output);


	while(!getch());
			
  	return 0;
}

unsigned long long GetFileSize(FILE *dosya){
	unsigned long long dosyaBoyutu=0, kaldigiYer=0;
	kaldigiYer=ftell(dosya);
	fseek(dosya, 0L, SEEK_END);
	dosyaBoyutu=ftell(dosya);
	fseek(dosya,kaldigiYer, SEEK_SET);
	return dosyaBoyutu;
}


