
#include "treetype.h"

using namespace std;

int main()
{
    TreeType tree = TreeType();
    tree.insertItem(2);
    tree.insertItem(1);
    tree.insertItem(5);
    cout << tree.numberOfNodes()<< endl;
    return 0;
}
