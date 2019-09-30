#include<iostream>
#include<random>
#include<vector>
#include<string.h>
using namespace std;

#define SENTINEL 0x5a5a5a5a

// When the elements are sorted into sub-arrays , this api acts
// as a helper to merge the same
void MERGE(vector<int>& ArrayTobeSorted , int p ,int q , int r)
{
    int n1 = (q-p)+1;
    int n2 = r-q;
    // Dividing the elements from the main list into sub lists 
    // viz., FirstArray and SecondArray
    vector<int> FirstArray;
    FirstArray.assign(n1,0);
    for(int i=0;i<n1;i++) 
    {
        FirstArray[i] = ArrayTobeSorted[p+i];
    }
    
    vector<int> SecondArray;
    SecondArray.assign(n2,0);
    for(int i=0;i<n2;i++) 
    {
        SecondArray[i] = ArrayTobeSorted[q+1+i];
    }

    int FirstArrayIter = 0;
    int SecondArrayIter = 0;
   
    for(int k=p;k<=r;k++)
    {
        if(FirstArrayIter >= n1)
        {
            memcpy(&ArrayTobeSorted[k] , &SecondArray[SecondArrayIter] ,(n2-SecondArrayIter)*sizeof(int));
            break;
        }
        else if(SecondArrayIter >= n2)
        {
            memcpy(&ArrayTobeSorted[k] , &FirstArray[FirstArrayIter] ,(n1-FirstArrayIter)*sizeof(int));
            break;
        }
        else
        {
            if(FirstArray[FirstArrayIter] <= SecondArray[SecondArrayIter])
            {
                ArrayTobeSorted[k] = FirstArray[FirstArrayIter];
                FirstArrayIter++; 
            }
            else
            {
                ArrayTobeSorted[k] = SecondArray[SecondArrayIter];
                SecondArrayIter++; 
            }
        }
    }
}

// Recursive Merge sort api
void MERGE_SORT(vector<int>& ArrayTobeSorted , int p , int r)
{
    if(p < r)
    {
        int q = (p+r) >> 1;
        MERGE_SORT(ArrayTobeSorted,p,q);        	
        MERGE_SORT(ArrayTobeSorted,q+1,r);
        MERGE(ArrayTobeSorted,p,q,r);
    }
}

int main()
{
    int NumArrayElements = 0;

    cout << " Please enter number of array elements (1,50] : " ;
    cin >> NumArrayElements;
    
    if((NumArrayElements > 1) & (NumArrayElements <= 50))
    {

        random_device rd;  //Will be used to obtain a seed for the random number engine
        mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        uniform_int_distribution<> dis(0, 100);
    
        // Vector container to hold the elements of array to be sorted
        vector<int> A;

        // Preset the array with 0
        A.assign(NumArrayElements,0); 

        for (int n=0; n<NumArrayElements; n++)
        { 
            A[n] = dis(gen);
        }   
        
        // Print elements before sorting begins
        cout << " Elements before sorting happens : " ;
        for (int n=0; n<NumArrayElements; n++)
        { 
            cout <<  A[n] << ",";
        }
        cout << endl;
        MERGE_SORT(A,0,NumArrayElements-1);   
         // Print elements post sorting 
        cout << " Elements post sorting : " ;
        for (int n=0; n<NumArrayElements; n++)
        { 
            cout <<  A[n] << ",";
        }
        cout << endl;

      
    }
    else
    {
        cout << " Incorrect Number of elements entered , exiting program ! " << endl ; 
    }
    return 0;
}
