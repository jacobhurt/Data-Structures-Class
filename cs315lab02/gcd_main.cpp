//
//  gcd_main.cpp
//  cs315lab02
//
//  Created by Jacob Hurt on 9/24/17.
//  Copyright © 2017 Jacob Hurt. All rights reserved.
//

#include <stdio.h>
#include gcd.hpp

//testing the functions
int main()
{
    int n1, n2;
    //prompt the user to enter two numbers
    cout << "Enter two numbers for which GCD is to be found" << endl;
    cin >> n1 >> n2;
    cout << "Iterative version: GCD is " << gcdIterative(n1, n2)<<endl;
    cout << "Recursive version: GCD is " << gcdRecursive(n1, n2)<<endl;
    return 0;
}
