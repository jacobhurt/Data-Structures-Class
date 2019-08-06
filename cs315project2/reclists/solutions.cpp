#include "reclists.hpp"
#include "solutions.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

// As you implement functions in this file, you should add the
// function-prototype to the solutions.hpp. The function-prototypes
// for append and reverse are already in solutions.hpp.
list append( list p, list q )
{
     if( is_null( p ) ) return q;
     return cons( car(p), append( cdr(p), q ));
}

list reverse( list p )
{
     if( is_null(p) || is_atom(p) ) return p;
     return append( reverse( cdr(p) ), cons(car(p), null() )) ;
}

int numLs (list p)
{
    if(is_null(p))
        return 0;
    return 1 + numLs(cdr(p));
}

int countAtoms(list p)
{
    if(is_null(p))
        return 0;
    if( is_atom(car(p)))
        return 1 + countAtoms( cdr(p));
    return countAtoms( cdr(p));

}

// p is an atom. q is a list of atoms
// countSimilarAtoms returns the number of times that p appears in q
// Ex:
// p is a
// q is (a a b b c c)
int countSimilarAtoms( list p, list q)
{
    if( is_null(q))
        return 0;
    if(eq(p, car(q) ))
       return 1 + countSimilarAtoms( p, cdr(q));
    return countSimilarAtoms ( p, cdr(q));
}

// p is a recursive list that has at least n LS is it
// nthL returns the n-th l in p
// p = ( a b c d)
// n = 3
// nthL returns c

list nthL(list p, int n)
{
    if ( n ==1 )
        return car(p);
    return nthL(cdr(p),n-1);
}


bool sameSequence( list p, list q)
{
    if ( list(p) != list(q))
        return false;
    return sameSequence(p-1, q-1);
        
}

bool is_lat(list p){
    if(is_null(p)){
        return true;
    }
    if(is_atom(p)){
        return false;
    }
    if(p->type == LISTS && p->first->type==ATOMS && is_null(p->rest)){
        return true;
    }
    return false;
}

bool member(list p, list q){
    if(!is_atom(p) || is_atom(q)){
        exit(1);
    }
    if(is_atom(car(q)) && eq(p, car(q)))	return true;
    if(is_atom(cdr(q)) && eq(p, cdr(q)))	return true;
    if(!is_atom(car(q)) && member(p, car(q)))	return true;
    if(!is_atom(cdr(q)) && member(p, cdr(q)))	return true;
    return false;
}

list last(list p){
    if(is_null(p)){
        exit(1);
    }
    if(is_atom(p)){
        exit(1);
    }
    list temp = cdr(p);
    if(!is_null(temp)){
        return last(temp);
    }
    temp = car(p);
    if(!is_atom(temp)){
        return last(temp);
    }
    list r = new list_node;
    r->type = ATOMS;
    char arr[2];
    arr[0] = car(p)->atom[strlen(car(p)->atom)-1];
    arr[1] = '\0';
    r->atom = arr;
    return r;
}

list list_pair(list p, list q){
    if(is_atom(p) || is_atom(q)){
        exit(1);
    }
    if(!is_atom(car(p)) || !is_atom(car(q))){
        exit(1);
    }
    
    list r = new list_node;
    r->type = ATOMS;
    char *arr = new char[3];
    arr[0] = car(p)->atom[0];
    arr[1] = car(q)->atom[0];
    arr[2] = '\0';
    r->atom = arr;
    
    list ans = new list_node;
    ans->first = r;
    ans->type = LISTS;
    ans->rest = null();
    
    list finalans = new list_node;
    finalans->type = LISTS;
    finalans->first = ans;
    
    if(strlen(car(p)->atom) == 1){
        finalans->rest = null();
    }
    else{
        car(p)->atom = car(p)->atom + 1;
        car(q)->atom = car(q)->atom + 1;
        list temp = list_pair(p, q);
        finalans->rest = temp;
    }
    return finalans;
}

list firsts(list p){
    if(is_null(p)){
        exit(1);
    }
    list r = new list_node;
    r->type = ATOMS;
    char *arr = new char[2];
    arr[0] = car(car(p))->atom[0];
    arr[1] = '\0';
    r->atom = arr;
    
    list ans = new list_node;
    ans->type = LISTS;
    ans->first = r;
    ans->rest = null();
    if(!is_null(cdr(p))){
        list temp = firsts(cdr(p));
        strcat(car(ans)->atom, car(temp)->atom);
    }
    return ans;
}

list flat(list p){
    if(is_null(p) || is_atom(p)){
        exit(1);
    }
    list r = new list_node;
    r->type = ATOMS;
    char *arr = new char[1];
    arr[0] = '\0';
    r->atom = arr;
    
    list ans = new list_node;
    ans->type = LISTS;
    ans->first = r;
    ans->rest = null();
    if(!is_null(car(p)) && is_atom(car(p))){
        strcat(car(ans)->atom, car(p)->atom);
    }
    else{
        strcat(car(ans)->atom, car(flat(car(p)))->atom);
    }
    if(!is_null(cdr(p)) && is_atom(cdr(p))){
        strcat(car(ans)->atom, cdr(p)->atom);
    }
    else if(!is_null(cdr(p))){
        strcat(car(ans)->atom, car(flat(cdr(p)))->atom);
    }
    return ans;
}


bool two_the_same(list p, list q){
    if(is_null(p) || is_null(q)){
        return false;
    }
    p = flat(p);
    q = flat(q);
    if(strlen(car(p)->atom) == 0){
        return false;
    }
    list r = new list_node;
    r->type = ATOMS;
    char *arr = new char[2];
    arr[0] = car(p)->atom[0];
    arr[1] = '\0';
    r->atom = arr;
    if(member(r, q)){
        return true;
    }
    car(p)->atom = car(p)->atom + 1;
    return two_the_same(p, q);
}

bool equal(list p, list q){
    if(is_null(p) && is_null(q)){
        return true;
    }
    if(is_null(p) || is_null(q)){
        return false;
    }
    if(is_atom(p) && is_atom(q)){
        return eq(p, q);
    }
    if(is_atom(p) || is_atom(q)){
        return false;
    }
    return equal(car(p), car(q)) && equal(cdr(p), cdr(q));
}

list total_reverse(list p){
    if(is_null(p)){
        return p;
    }
    if(is_atom(p)){
        if(strlen(p->atom) <= 1){
            return p;
        }
        char start = p->atom[0];
        char end = p->atom[strlen(p->atom) - 1];
        p->atom = p->atom + 1;
        p->atom[strlen(p->atom) - 1] = '\0';
        list temp = total_reverse(p);
        char* arr = new char[2];
        arr[0] = end;
        arr[1] = '\0';
        strcat(arr, temp->atom);
        char *x = new char[2];
        x[0] = start;
        x[1] = '\0';
        strcat(arr, x);
        p->atom = arr;
        return p;
    }
    return append( total_reverse( cdr(p) ), cons(total_reverse(car(p)), null() )) ;
}

list shape(list p){
    if(is_null(p)){
        return p;
    }
    if(is_atom(p)){
        strcpy(p->atom, "");
        return p;
    }
    if(!is_null(car(p))){
        p->first = shape(car(p));
    }
    if(!is_null(cdr(p))){
        p->rest = shape(cdr(p));
    }
    return p;
}

list intersection(list p, list q){
    list r = new list_node;
    r->type = ATOMS;
    char *arr = new char[1];
    arr[0] = '\0';
    r->atom = arr;
    
    list ans = new list_node;
    ans->type = LISTS;
    ans->first = r;
    ans->rest = null();
    if(strlen(car(p)->atom) == 0){
        return ans;
    }
    
    list r1 = new list_node;
    r1->type = ATOMS;
    char *arr1 = new char[2];
    arr1[0] = car(p)->atom[0];
    arr1[1] = '\0';
    r1->atom = arr1;
    
    if(member(r1, q)){
        strcat(car(ans)->atom, arr1);
    }
    car(p)->atom = car(p)->atom + 1;
    list temp = intersection(p, q);
    strcat(car(ans)->atom, car(temp)->atom);
    return ans;
}

list list_union(list p, list q){
    list r = new list_node;
    r->type = ATOMS;
    char *arr = new char[1];
    arr[0] = '\0';
    r->atom = arr;
    
    list ans = new list_node;
    ans->type = LISTS;
    ans->first = r;
    ans->rest = null();
    
    if(!is_null(p)){
        strcat(car(ans)->atom, car(p)->atom);
    }
    
    if(is_null(q) || strlen(car(q)->atom) == 0){
        return ans;
    }
    
    list r1 = new list_node;
    r1->type = ATOMS;
    char *arr1 = new char[2];
    arr1[0] = car(q)->atom[0];
    arr1[1] = '\0';
    r1->atom = arr1;
    
    if(!member(r1, ans)){
        strcat(car(ans)->atom, arr1);
    }
    
    car(q)->atom = car(q)->atom + 1;
    list temp = list_union(ans, q);
    return temp;
}
