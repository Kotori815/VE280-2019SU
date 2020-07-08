#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

static bool tree_equal(tree_t t1, tree_t t2)
    // EFFECTS: returns true iff t1 == t2
{
    if(tree_isEmpty(t1) && tree_isEmpty(t2))
    {
        return true;
    }
    else if(tree_isEmpty(t1) || tree_isEmpty(t2))
    {
        return false;
    }
    else
    {
        return ((tree_elt(t1) == tree_elt(t2)) 
            && tree_equal(tree_left(t1), tree_left(t2))
            && tree_equal(tree_right(t1), tree_right(t2)));
    }
}

int main()
{   
    tree_t treeA = tree_make(4,
                     tree_make(1, tree_make(), tree_make(3,
                         tree_make(),tree_make())),
                     tree_make(7, tree_make(5,
                         tree_make(),tree_make()), tree_make(9,
                         tree_make(),tree_make())));
    tree_t treeB = tree_make(4,
                     tree_make(), tree_make(7,
                         tree_make(5,tree_make(),tree_make()),tree_make()));
    tree_t treeC = tree_make(7,
                     tree_make(5,tree_make(),tree_make()),
                     tree_make(9,tree_make(),tree_make()));

    tree_print(treeA);
    cout << "sum A: " << tree_sum(treeA) << " depth A: " << depth(treeA) << " max in A: " << tree_max(treeA) << endl;
    cout << "is 2, 7, 9 in A " << tree_search(treeA, 2) << tree_search(treeA, 7) << tree_search(treeA, 9) << endl;
    list_print(traversal(treeA));

    cout << endl;
    
    tree_print(treeB);
    cout << "sum B: " << tree_sum(treeB) << " depth B: " << depth(treeB) << " max in B: " << tree_max(treeB) << endl; 
    cout << "is 2, 7, 9 in B " << tree_search(treeB, 2) << tree_search(treeB, 7) << tree_search(treeB, 9) << endl;
    list_print(traversal(treeB));

    tree_t treeD = tree_make(4,
                    tree_make(1, tree_make(), tree_make(6,
                         tree_make(),tree_make())),
                    tree_make(7, tree_make(2,
                         tree_make(),tree_make()), tree_make()));

    cout << endl;

    tree_print(treeA);
    cout << endl;
    tree_print(treeD);
    cout << endl;

    cout << "monotonic: A and D: " << tree_hasMonotonicPath(treeA) << tree_hasMonotonicPath(treeD) << endl;
    cout << "pathsum A,7; A,12; D,8; D,11: " << tree_allPathSumGreater(treeA, 7) << tree_allPathSumGreater(treeA, 12) << tree_allPathSumGreater(treeD, 8) << tree_allPathSumGreater(treeD, 11) << endl;

    cout << endl;
    cout << "B, C, D covered by A? " << covered_by(treeB, treeA) << covered_by(treeC, treeA) << covered_by(treeD, treeA) << endl;
    cout << "B, C, D contained by A? " << contained_by(treeB, treeA) << contained_by(treeC, treeA) << contained_by(treeD, treeA) << endl;

    cout << "8 into A" << endl;
    tree_print(treeA);
    cout << endl;
    tree_print(insert_tree(8, treeA));
    cout << endl;

    cout << "3 into B" << endl;
    tree_print(treeB);
    cout << endl;
    tree_print(insert_tree(3, treeB));
    cout << endl;

}
