#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cmath>
#include <string>
#include <fstream>
#include <pthread.h>
using namespace std;

string  mask1,inputname,outputname;
int row , colm, sum;
long thread_count = 10;
int **image;
int **image2;
int flag = 0; 
int mask[3][3];

void * imgPth(void * rank){
	long my_rank = (long)rank;
	int first = int((row/thread_count) * my_rank);
	int last = first + int((row/thread_count));
	int my_sum = 0;
	int i, j, k, z;
	//apply mask on matrex
	for(i=first;i<=last-3;i++)
	{
		
		for(j= 0; j<colm-3; j++)
		{	sum = 0; 
			
			for(z=0;z<3;z++)
			{
				
				for(k=0;k<3;k++)
				{	
					
					my_sum+=image[i+z][j+k]*mask[z][k];
													
				}

			}
		while(flag != my_rank);
		sum += my_sum;
		image2[i][j]=sum;			
		flag = (flag+1)%thread_count; 
		}
	}
	
}

int main(int argc, char* argv[]) {

    if (argc < 5) {
        printf("You must pass 4 parameters inputfilename,mask , and outputfilename, and thread numbers\n");
        return 0;
    }
	
	    
	    
	string s1(argv[1]);
	string s2(argv[2]);
	string s3(argv[3]);
	stringstream er1(s1);
	er1 >> inputname;
	stringstream er2(s2);
	er2 >> mask1;
	stringstream er3(s3);
	er3 >> outputname; 

	 
	long thread; 
	pthread_t * thread_handles;

	thread_count = strtol(argv[4], NULL, 10);
	thread_handles = new pthread_t[thread_count];
	
	int pix;
	
	 ifstream myfile (inputname.c_str());
  	if (myfile.is_open())
 	 {	
		ifstream myfile2 (mask1.c_str());
		if (myfile2.is_open())
		{
	  	   	myfile>>row; 
	  	  	myfile>>colm; 


		//create image matrex
			image=new  int* [row];
			image2=new  int* [row-3];
			for (int i =0; i<row;i++)
			{
				image[i]=new int [colm];
				
			}
			for (int i =0; i<row-3;i++)
			{
				
				image2[i]=new int [colm-3];
			}
		//get value from oimage.txt
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<colm;j++)
				{	
					myfile>>pix;
					image[i][j]=pix;
				}
			}
		//crete mask or kernel matrex
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					myfile2>>pix;
					mask[i][j]=pix;
					
				}
			}
			//open the output file
			// threaded function
			for (thread = 0; thread < thread_count; thread++)
				pthread_create(&thread_handles[thread], NULL, imgPth, (void *)thread);
			 	
			for (thread = 0; thread < thread_count; thread++)			
				pthread_join(thread_handles[thread], NULL);

			free(thread_handles);
	
				ofstream myfile3;
				myfile3.open (outputname.c_str());
				if(myfile3.is_open())
				{
					for(int i=0;i<row-3;i++)
					{
						for(int j=0;j<colm-3;j++)
						{	
							myfile3<<image2[i][j]<<" ";
						}
						myfile3<<"\n";
					}
				}
				 myfile3.close();
			for (int i =0; i<row;i++)
			{
				delete [] image[i];
			}
			for (int i =0; i<row-3;i++)
			{
				delete [] image2[i];
			}
			delete []image;
			delete []image2;
		}
		myfile2.close();
  	  }
	
  	
	  myfile.close();
	  
	return 0;
}
