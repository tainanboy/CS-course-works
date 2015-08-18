//
//  main.cpp
//  towerof_honai
//
//  Created by Frank on 2015/8/18.
//  Copyright © 2015年 code39. All rights reserved.
//

#include <iostream>
using namespace std;

void honai(int n, char a, char b, char c){
    if(n==1) {
        cout << "Move the "<<n<<" disk from " << a << " to " << c << endl;
    }
    else {
        honai(n-1, a, c, b);
        cout << "Move the "<< n<<" disk from " << a << " to " << c << endl;
        honai(n-1, b, a, c);
    }
}

int main(void)
{
    int n;
    
    cout<<"Enter the number of disks：";
    cin>>n;
    honai(n, 'A', 'B', 'C');
}

