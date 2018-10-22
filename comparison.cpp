#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<fstream>
#include<stdio.h>
using namespace std;

int insertion_sort(int arr[],int n)                                    //Objective:To sort the array arr of size n in ascending order
{                                                                      //Input:arr[],size of array
    int pos,j,temp,count=0;                                            //Return value:count value of number of comparisons
    for(int i=1;i<n;i++)
	{
		j=i-1;
		pos=i;
		temp=arr[i];
		while(temp<arr[j])                                             //Approach:
		{                                                             //elements to the left of pointed element are trivially sorted 
	    	count=count+1;                                           //pointed element is compared with them and placed at its right position  
            arr[j+1]=arr[j];
			pos=j;
			j--;
		}
		arr[pos]=temp;
	}
	return count;
}

int partition(int arr[],int lb,int ub,int &count)                       //Objective:to find the index of pivot element
{                                                                      //Input:arr[],starting index and last index in arr,count
    int l= lb + rand() % (ub- lb);//random pivot is selected          //Return value:correct index of pivot
	int pivot=arr[l];
	int up,down,temp;
	up=ub;//last index
	down=lb;//first index of array                                  
    while(down<up)
	{
		while(arr[down]<=pivot&&down<up)//down is incremented each time when we get element less than equal to pivot
		{ 	count++;
		   	down++;
	    }
        while(arr[up]>pivot)//up is decremented each time when we get element greater than pivot
		{ 	count++;
            up--;
		}
		if(down<up)
		{   
		 	temp=arr[up];
		 	arr[up]=arr[down];
		 	arr[down]=temp;
    	}
    }
    temp=arr[l]; //swap pivot with element at up 
	arr[l]=arr[up];
	arr[up]=temp;
    return up;//index of pivot element
}

int quicksort(int arr[],int lb,int ub)                                    //Objective:To sort the arr[] in ascending order
{   int count=0;                                                         //Input:arr[],first index,last index
   	if(lb<ub)                                                           //Return value:number of comparisons
	{
	int index=partition(arr,lb,ub,count);
    count+=	quicksort(arr,lb,index-1);                                 /*Approach:every time a pivot element is picked and is placed at its right position
 	                           											then arr is divided into two parts one upto index-1 and other from index+1 to ub*/
	count+=	quicksort(arr,index+1,ub);                                                                  
	}                                                                                 
	return count;
}                                                                    


void merge(int arr[],int l,int m,int h,int &compM)                          //Objective:merge 2 arrays to form a single sorted array 
{                                                                          //Input:arr[],start index,mid,last index,compM
                                                                          //Return Value:none
	int i, j, k;
    int n1 = m - l + 1;
    int n2 =  h - m;
    int L[n1],R[n2];//creating 2 arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l+i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m+1+j];
    i = 0;  
    j = 0;  
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        compM++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int mergesort(int arr[],int low,int high)                          //Objective:To sort the arr[] in ascending order
{																  //Input:arr[],first index,last index
	int mid,compM=0;                                             //Return value:comparisons takes place in sorting
	if(low<high)
	{
		mid=(low+high)/2;                                       //Approach:every time arr is divided to its half and then merge function combines them
		compM+=mergesort(arr,low,mid);                         //by compairing elements 
		compM+=mergesort(arr,mid+1,high);
		merge(arr,low,mid,high,compM);
	}
	return compM;
}

int main()
{   
	srand(time(NULL));//to generate diffrent random numbers each time
    ofstream outdata;//ofstream object is used to write into excel
    outdata.open("outfile.csv",ios::out);//outfile.csv stores entire input
    outdata<<"n"<<","<<"  insertion"<<","<<" quick"<<","<<" merge  \n";// copying this into outfile.csv using object of ofstream class
    cout<<"           insertionsort quick sort merge sort  \n";
    int n=10;//size of array intially
	do
    {                                                                                     
	    int arr[n];                                                                      
	    int arr2[n];//to keep same elements for quicksort that are previously in arr[n]  
	    int arr3[n];//to keep same elements for mergesort that are previously in arr[n]
	    cout<<"n is: "<<n<<"  --   ";
	    outdata<<n<<",";
	    float count_merge=0.0,count_insert=0.0,count_quick=0.0;//total comparisons in each sorting techniques
        for(int j=0;j<20;j++)
	    {
	  	    for(int i=0;i<n;i++)//array of size n is filled 20 times with random inputs 
	    	{
		    	arr[i]=rand();
		    	arr2[i]=arr[i];
			 	arr3[i]=arr[i];
			}
			//for each value of n these functions are called 20 times and total comparisons are noted
	     	count_insert+=insertion_sort(arr,n);
	  	 	int lb=0,ub=n-1;//lb points to initial element of array and ub points to last element
	     	count_quick+=quicksort(arr2,lb,ub);
            count_merge+=mergesort(arr3,lb,ub);

		}
		cout<<fixed;//float values will not be exponential
	    cout<<setprecision(2);//float value contains exactly 2 digits after decimal
        
		//ouput printing
        cout<<"      "<<count_insert/(20.0)<<"      ";
        outdata<<count_insert/(20.0)<<",";//copying this into outfile.csv
		cout<<count_quick/(20.0)<<"       ";
        outdata<<count_quick/(20.0)<<",";
        cout<<count_merge/20.0<<endl;
        outdata<<count_merge/(20.0)<<","<<endl;

	    n+=10;//array size is incremented by 10
    }while(n<1001);//array size will increase only upto 1000
    system("result.xlsx");//outfile.csv file is imported to result.xlsx
                        //it contains ouput as well as graph
    return 0;
}

