//
//  BinarySearch_main.cpp
//  cs315lab02
//
//  Created by Jacob Hurt on 9/24/17.
//  Copyright © 2017 Jacob Hurt. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "isMemberBinarySearch.hpp" 

int main()
{
    int A[] = {2, 5, 6, 8, 9, 10};
    int N = 6;
    int target = 6;
    
    bool index = isMemberBinarySearchRecursive(A, N, target);
    
    if (index)
      std::cout << "Element found ";
    else
      std::cout << "Element not found in the array";
    
    return 0;
}
