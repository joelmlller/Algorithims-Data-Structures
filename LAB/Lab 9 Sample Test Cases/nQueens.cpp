/*
 * Name: Joel Miller
 * Date Submitted: 04/17/2023
 * Lab Section: 02
 * Assignment Name: N Queens
 */

#include<iostream>

using namespace std;

//if  you can place the queen at a position or not
bool secluded(int**queen,int num,int c,int r)
{
    //row
    for(int i=0;i<num;i++)
    {
        if(queen[r][i]==1)
            return false;
    }
    //left upper diagonal
    int j;
    for(int i=r,j=c;i>=0&&j>=0;i--,j--)
    {
        if(queen[i][j]==1)
            return false;
    }
    //left lower diagonal
    for(int i=r,j=c;i<num&&j>=0;i++,j--)
    {
        if(queen[i][j]==1)
            return false;
    }
    //return true if all met
    return true;
}
int find(int ** queen,int num,int c)
{
    int r;

    int numCounter=0;


    if(c==num)
    {

        return 1;
    }

    for(int i=0;i<num;i++)
        {
            r=i;
            if(secluded(queen,num,c,r)==true)
            {
                //if we can place the queen there then place it
                queen[r][c]=1; 
                numCounter+=find(queen,num,c+1); 
                queen[r][c]=0; 
            }
        }
        return numCounter;
}

int nQueens(int num){

    int ** queen=new int *[num];


    for(int i=0;i<num;i++)
    {
        queen[i]= new int[num];
        for(int j=0;j<num;j++)
        {
            queen[i][j]=0;
        }
    }
    return find(queen,num,0);
}

/*int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}*/