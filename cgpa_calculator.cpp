#include<iostream>
using namespace std;

double cgpa_cal(string grade[],double credit[],double tot,int num)
{
    int * point=new int[num];
    double cre_sum=0.0;
    double cgpa=0.0;

    for(int i=0;i<num;i++)
    {
        if(grade[i]=="AA")
        {
            point[i]=10;
        }
        else if(grade[i]=="AB")
        {
            point[i]=9;
        }
        else if(grade[i]=="BB")
        {
            point[i]=8;
        }
        else if(grade[i]=="BC")
        {
            point[i]=7;
        }
        else if(grade[i]=="CC")
        {
            point[i]=6;
        }
        else
        {
            point=0;
        }
    }

    for(int i=0;i<num;i++)
    {
        cre_sum+=point[i]*credit[i];
    }

    cgpa=cre_sum/tot;
    return cgpa;
}

int main()
{
    int num; 
    do
    {
        cout<<"Enter number of courses (if course=0 enter coorect input) :";
        cin>>num;
    }
    while (num==0);

    string * grade = new string[num];
    double * credit = new double[num];
    double cgpa=0.0;
    double tot_credit=0.0;

    cout<<"Enter grades of course(AA,AB,BB,etc...) and credit of that subject(in double) :";
    
    for(int i=0;i<num;i++)
    {
        cin>>grade[i]>>credit[i];
        tot_credit+=credit[i];
    }

    cgpa=cgpa_cal(grade,credit,tot_credit,num);
    
    cout<<"Your CGPA is :"<<cgpa<<endl;
    return 0;
}