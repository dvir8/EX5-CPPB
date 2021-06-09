#include "BinaryTree.hpp"
#include "doctest.h"
using namespace ariel;

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;

const int max_rand = 1000;
const int div_factor = 100;

double NextDouble() {
    return (double)((unsigned int)rand() % max_rand) / div_factor;
}

int NextInt() {
    return (rand() % max_rand);
}

bool RandomBool() {
    return rand() % 2 == 0;
}

enum class _order {
    inorder,
    postorder,
    preorder,
};

template <typename T>
BinaryTree<T> create_dummy(int adder = 0) {
    BinaryTree<T> tree;

    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1 + adder);
    tree.add_left(1 + adder, 2 + adder);
    tree.add_right(1 + adder, 3 + adder);
    tree.add_left(2 + adder, 4 + adder);
    tree.add_right(2 + adder, 5 + adder);
    tree.add_left(5 + adder, 10 + adder);
    tree.add_right(5 + adder, 11 + adder);
    tree.add_left(10 + adder, 20 + adder);
    tree.add_right(11 + adder, 23 + adder);

    return tree;
}

template <typename T>
bool isEqual(BinaryTree<T> &tree, vector<T> const &v2, _order order) {
    // This function checks if a given tree order is equal to some vector.
    if (order == _order::inorder) {
        auto end = tree.end_inorder();
        auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), v2.begin());
        return (pair.first == end && pair.second == v2.end());
    } else if (order == _order::postorder) {
        auto end = tree.end_postorder();
        auto pair = std::mismatch(tree.begin_postorder(), tree.end_postorder(), v2.begin());
        return (pair.first == end && pair.second == v2.end());
    }
    auto end = tree.end_preorder();
    auto pair = std::mismatch(tree.begin_preorder(), tree.end_preorder(), v2.begin());
    return (pair.first == end && pair.second == v2.end());
}

TEST_CASE("check normal order = inorder") {
    BinaryTree<int> tree = create_dummy<int>();

    auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), tree.begin());
    CHECK(((pair.first == tree.end_inorder()) && (pair.second == tree.end())));
}

TEST_CASE("TEST binary on ints simple") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<int> inorder = {4, 2, 20, 10, 5, 11, 23, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<int> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};
    BinaryTree<int> tree = create_dummy<int>(0);
    for(auto& t :tree){
        cout << t << " ";
    }
    cout<<endl;
    // Test inorder preorder postorder with match.
    for (int i = 0; i < 10; i++) {
        BinaryTree<int> tree = create_dummy<int>(i);

        CHECK(isEqual(tree, inorder, _order::inorder));

        CHECK(isEqual(tree, preorder, _order::preorder));

        CHECK(isEqual(tree, postorder, _order::postorder));

        transform(inorder.begin(), inorder.end(), inorder.begin(), [](int val) { return val + 1; });
        transform(preorder.begin(), preorder.end(), preorder.begin(), [](int val) { return val + 1; });
        transform(postorder.begin(), postorder.end(), postorder.begin(), [](int val) { return val + 1; });
    }
}