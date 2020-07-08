#include <iostream>
#include <cassert>
#include "p2.h"

using namespace std;

int size(list_t list){

    if (list_isEmpty(list)) {return 0;}
    else {return 1 + size(list_rest(list));}
    
    //resursion ends when list is empty, size plus 1 each recursion

}


bool memberOf(list_t list, int val){

    if (list_isEmpty(list)){return false;}
    else if (list_first(list) == val) {return true;}
    else {return memberOf(list_rest(list),val);}

    // see if the first element of list is required value;
    // if not, then find if so for the rest of list

}


int dot(list_t v1, list_t v2){

    if (size(v1) == 0 || size(v2) == 0) {return 0;}
    else {return list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2));}

    // add the first elements of two list to the sum
    // until all the elemtns in one of the list have been used.
}


bool isIncreasing(list_t v){

    if (size(v) <= 1){return true;}
    else if (list_first(v) > list_first(list_rest(v))){return false;}
    else {return isIncreasing(list_rest(v));}

    // see if the fisrt element is smaler than the second
    // if so, keep on testing until the last element
    // exit as long as one exception is found

}   


int list_last(list_t list){
    if (size(list) == 1) {return list_first(list);}
    else {return list_last(list_rest(list));}

    // return the last element
}
list_t list_head(list_t list){
    if (size(list) == 1){return list_make();}
    else {return list_make(list_first(list), list_head(list_rest(list)));}

    // to get the list with last element removed
}

list_t reverse_helper(list_t list, list_t rev){

    if (list_isEmpty(list)) {return rev;}
    else {
        rev = list_make(list_first(list), rev);
        return reverse_helper(list_rest(list), rev);
    }
    // keep on making lists with the last elemnt as the first
}
list_t reverse(list_t list){

    list_t rev = list_make(); // REV the carrier of the answer list
    return reverse_helper(list, rev);

}


list_t append(list_t first, list_t second){

    if (list_isEmpty(first)) {return second;}
    else {return list_make(list_first(first), append(list_rest(first), second));}

    // keep adding the last elements of FIRST as the first of SECOND
    // until all of FIRST elemnts are added
}


bool isArithmeticSequence_helper(list_t list, int diff){

    if (size(list) <= 1){return true;}
    else if (list_first(list)-list_first(list_rest(list)) != diff) {return false;}
    else {return isArithmeticSequence_helper(list_rest(list), diff);}

    // compare the supposed diffence DIFF and the one between first and second element
    // return false as soon as one inequivalence is found
    
}
bool isArithmeticSequence(list_t v){

    if (size(v) < 3){return true;}
    else {
        int diff;
        diff = list_first(v)-list_first(list_rest(v));
        return isArithmeticSequence_helper(list_rest(v), diff);
    }

    return false;

    //suppose the difference between first two element is the common one
    //then test if all such differences equals the supposed one
}


list_t filter_odd_helper(list_t list, list_t filtered){

    if (list_isEmpty(list)){return filtered;}
    else if (list_first(list) % 2 == 0) {return filter_odd_helper(list_rest(list), filtered);}
    else {return list_make(list_first(list), filter_odd_helper(list_rest(list), filtered));}

    // add the element to the first of the FILTERED if it's odd
    // until all the elements are tested
}

list_t filter_odd(list_t list){

    list_t filtered = list_make(); // filtered is the carrier for the answer list
    return filter_odd_helper(list, filtered);

}


list_t filter_helper(list_t list, list_t filtered, bool (*fn)(int)){

    if (list_isEmpty(list)){return filtered;}
    else if (fn(list_first(list)) == false) {return filter_helper(list_rest(list), filtered, fn);}
    else {return list_make(list_first(list), filter_helper(list_rest(list), filtered, fn));}
    
    // same as the FILTER_ODD function
}

list_t filter(list_t list, bool (*fn)(int)){

    list_t filtered = list_make();
    return filter_helper(list, filtered, fn);

}


list_t unique_helper(list_t list, list_t uniq){

    if (list_isEmpty(list)) {return reverse(uniq);}
    else
    {
        if (!memberOf(uniq, list_first(list))) {uniq = list_make(list_first(list), uniq);}
        return unique_helper(list_rest(list), uniq);
    }

    // search each element in the list UNIQ
    // if not exists in UNIQ, then add to UNIQ, vice versa
    // unitil all the elements are tested
    
}
list_t unique(list_t list){

    list_t uniq = list_make(); // UNIQ is the carrier for the answer list
    return unique_helper(list, uniq);

}


list_t insert_list(list_t first, list_t second, unsigned int n){

    if (n == 0) {return append(second, first);}
    else {return list_make(list_first(first), insert_list(list_rest(first), second, n - 1));}

    // exclude the first nth element of SECOND and append FIRST to the beginning
    // then add the excluded elements of SECOND back
}


list_t chop_helper(list_t list, unsigned int n){

    if (n == 0) {return list_make();}
    else {return list_make(list_first(list), chop_helper(list_rest(list), n-1));}

    // take out first n elements and add them to a blank list
}

list_t chop(list_t list, unsigned int n){
    
    return chop_helper(list, size(list) - n);

    // instead of considering excluding the last n elements
    // keeping the first (SIZE(LIST) - n) elements
}


//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree){

    if (tree_isEmpty(tree)) {return 0;}
    else {return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));}

    // the sum of a tree equals is the sum of:
    // sum of left subtree, sum of right subtree and the root 
}


bool tree_search(tree_t tree, int val){

    if(tree_isEmpty(tree)) {return false;}
    else if (tree_elt(tree) == val) {return true;}
    else {return tree_search(tree_left(tree), val) || tree_search(tree_right(tree), val);}

    // see if the root is the required number
    // if not, try finding them in the left and right subtree
}


int max(int a, int b){
    if (a < b){return b;}
    else {return a;}
    // find bigger value in A and B, for later use
}

int depth(tree_t tree){

    if (tree_isEmpty(tree)){return 0;}
    else if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))){return 1;}
    else {return 1 + max(depth(tree_left(tree)), depth(tree_right(tree)));}

    // each root means 1 depth
    // count with the deeper one of left and right subtree

}

int tree_max(tree_t tree){

    if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {return tree_elt(tree);}
    else if (tree_isEmpty(tree_left(tree))) {return max(tree_elt(tree),tree_max(tree_right(tree)));}
    else if (tree_isEmpty(tree_right(tree))) {return max(tree_elt(tree),tree_max(tree_left(tree)));}
    else {return max(tree_elt(tree), max(tree_max(tree_left(tree)), tree_max(tree_right(tree))));}

    //maximum in a tree is the maximum in 
    // maximum of left subtree, maximum of right subtree and the root
}


list_t traversal(tree_t tree){

    if (tree_isEmpty(tree)) {return list_make();}
    else {return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));}

    // traversal is made up of traversal of left, the root an travesal of right
}

bool tree_hasIncreasePath(tree_t tree){

    if (depth(tree) == 1) {return true;}
    if (depth(tree) == 2) {
        if (tree_isEmpty(tree_left(tree))) {return tree_elt(tree_right(tree)) >= tree_elt(tree);}
        else if (tree_isEmpty(tree_right(tree))) {return tree_elt(tree_left(tree)) >= tree_elt(tree);}
        else {return (tree_elt(tree_left(tree)) >= tree_elt(tree)) || (tree_elt(tree_right(tree)) >= tree_elt(tree));}
    }
    else
    {
        if (tree_isEmpty(tree_left(tree))) {return tree_hasIncreasePath(tree_right(tree));}
        else if (tree_isEmpty(tree_right(tree))) {return tree_hasIncreasePath(tree_left(tree));}
        else {return tree_hasIncreasePath(tree_left(tree)) || tree_hasIncreasePath(tree_right(tree));}
    }

    // see if there exist the root of a subtree that is smaller than the root
    // if so keep on seeing for the subtrees

}    
bool tree_hasDecreasePath(tree_t tree){

    if (depth(tree) == 1) {return true;}
    if (depth(tree) == 2) {
        if (tree_isEmpty(tree_left(tree))) {return tree_elt(tree_right(tree)) <= tree_elt(tree);}
        else if (tree_isEmpty(tree_right(tree))) {return tree_elt(tree_left(tree)) <= tree_elt(tree);}
        else {return (tree_elt(tree_left(tree)) >= tree_elt(tree)) || (tree_elt(tree_right(tree)) <= tree_elt(tree));}
    }
    else
    {
        if (tree_isEmpty(tree_left(tree))) {return tree_hasDecreasePath(tree_right(tree));}
        else if (tree_isEmpty(tree_right(tree))) {return tree_hasDecreasePath(tree_left(tree));}
        else {return tree_hasDecreasePath(tree_left(tree)) || tree_hasDecreasePath(tree_right(tree));}
    }

    // the same as increasing path detecting function
}

bool tree_hasMonotonicPath(tree_t tree){
    
    return tree_hasDecreasePath(tree) || tree_hasIncreasePath(tree);

    // both increasing and decreasing are monotonic

}


bool tree_allPathSumGreater(tree_t tree, int sum){

    if (tree_isEmpty(tree)) {
        if (sum < 0) {return true;}
        else {return false;}
    }
    else if (tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree))) {return tree_allPathSumGreater(tree_right(tree), sum - tree_elt(tree));}
    else if (!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {return tree_allPathSumGreater(tree_left(tree), sum - tree_elt(tree));}
    else {return (tree_allPathSumGreater(tree_left(tree), sum - tree_elt(tree)) && tree_allPathSumGreater(tree_right(tree), sum - tree_elt(tree)));}

    // if all paths greater than a number SUM,
    // all the roots in one path should have sum larger than SUM
    // and it should be true for all paths
}


bool covered_by(tree_t A, tree_t B){

    if (tree_isEmpty(A)) {return true;}
    else if (tree_isEmpty(B)) {return false;}
    else if (tree_elt(A) != tree_elt(B)) {return false;}
    else {return covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));}

    // empty tree is covered by all tree;
    // A is vovered by B if
    // roots of A and B equals, 
    // and left of A is covered by left of B; so for the right 
}


bool contained_by(tree_t A, tree_t B){

    if (depth(A) > depth(B)) {return false;} //  if A is contained by B, then depth of A is smaller than B
    else if (covered_by(A,B)) {return true;}
    else {return contained_by(A, tree_left(B)) || contained_by(A, tree_right(B));}

    // A is contained by B if
    // A is covered by B or
    // A is covered by left or right subtree of B
}
    

tree_t insert_tree(int elt, tree_t tree){

    if (tree_isEmpty(tree)) {return tree_make(elt, tree_make(), tree_make());}
    else
    {
        if (elt < tree_elt(tree)){return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));}
        else if (elt >= tree_elt(tree)) {return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));}
    }

    // If ELT is smaller than root os the tree, then it should belongs to the left subtree
    // if not, then the right one
    // When the tree is a leaf, than insert a new leaf with ELT as root as left or right subtree
}