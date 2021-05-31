#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "doctest.h"
#include "sources/BinaryTree.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Add_root")
{
    BinaryTree<int> tree1;

    CHECK_NOTHROW(tree1.add_root(1));
    CHECK(*tree1.begin_preorder() == 1);

    CHECK_NOTHROW(tree1.add_root(2)); // Change root
    CHECK(*tree1.begin_preorder() == 2);

    CHECK_NOTHROW(tree1.add_root(3)); // Change root
    CHECK(*tree1.begin_preorder() == 3);

    CHECK_NOTHROW(tree1.add_root(4)); // Change root
    CHECK(*tree1.begin_preorder() == 4);

    BinaryTree<string> t1;

    CHECK_NOTHROW(t1.add_root("a"));
    CHECK(*t1.begin_preorder() == "a");

    CHECK_NOTHROW(t1.add_root("b")); // Change root
    CHECK(*t1.begin_preorder() == "b");

    CHECK_NOTHROW(t1.add_root("c")); // Change root
    CHECK(*t1.begin_preorder() == "c");

    CHECK_NOTHROW(t1.add_root("d")); // Change root
    CHECK(*t1.begin_preorder() == "d");
}

TEST_CASE("Add_left")
{
    BinaryTree<int> tree2;

    CHECK_NOTHROW(tree2.add_root(1));

    CHECK_NOTHROW(tree2.add_left(1, 2));
    CHECK(*tree2.begin_inorder() == 2);

    CHECK_NOTHROW(tree2.add_left(1, 3)); // Change left
    CHECK(*tree2.begin_inorder() == 3);

    CHECK_NOTHROW(tree2.add_left(1, 4)); // Change left
    CHECK(*tree2.begin_inorder() == 4);

    CHECK_NOTHROW(tree2.add_left(4, 5));
    CHECK(*tree2.begin_inorder() == 5);

    // The parent node does not exist to create a left child for him
    CHECK_THROWS(tree2.add_left(2, 6));
    CHECK_THROWS(tree2.add_left(3, 7));

    BinaryTree<string> t2;

    CHECK_NOTHROW(t2.add_root("a"));
    CHECK_NOTHROW(t2.add_left("a", "b"));
    CHECK(*t2.begin_inorder() == "b");

    CHECK_NOTHROW(t2.add_left("a", "c")); // Change left
    CHECK(*t2.begin_inorder() == "c");

    CHECK_NOTHROW(t2.add_left("a", "d")); // Change left
    CHECK(*t2.begin_inorder() == "d");

    CHECK_NOTHROW(t2.add_left("d", "e"));
    CHECK(*t2.begin_inorder() == "e");

    // The parent node does not exist to create a left child for him
    CHECK_THROWS(t2.add_left("b", "g"));
    CHECK_THROWS(t2.add_left("c", "t"));
}

TEST_CASE("Add_right")
{
    BinaryTree<int> tree3;

    CHECK_NOTHROW(tree3.add_root(1));
    CHECK_NOTHROW(tree3.add_right(1, 2));

    CHECK_NOTHROW(tree3.add_right(1, 3)); // Change right
    CHECK_NOTHROW(tree3.add_right(1, 4)); // Change right
    // The parent node does not exist to create a right child for him
    CHECK_THROWS(tree3.add_right(3, 7));

    CHECK_NOTHROW(tree3.add_right(4, 5));
    CHECK_NOTHROW(tree3.add_right(4, 6)); // Change right
    //The parent node does not exist to create a right child for him
    CHECK_THROWS(tree3.add_right(5, 8));

    BinaryTree<string> t3;

    CHECK_NOTHROW(t3.add_root("a"));
    CHECK_NOTHROW(t3.add_right("a", "b"));

    CHECK_NOTHROW(t3.add_right("a", "c")); // Change right
    CHECK_NOTHROW(t3.add_right("a", "d")); // Change right
    // The parent node does not exist to create a right child for him
    CHECK_THROWS(t3.add_right("c", "k"));

    CHECK_NOTHROW(t3.add_right("d", "e"));
    CHECK_NOTHROW(t3.add_right("d", "f")); // Change right
    // The parent node does not exist to create a right child for him
    CHECK_THROWS(t3.add_right("e", "h"));
}

TEST_CASE("Throw exception")
{
    BinaryTree<int> tree4;

    // There is no root for creating children
    CHECK_THROWS(tree4.add_left(1, 2));
    CHECK_THROWS(tree4.add_right(1, 3));
    CHECK_THROWS(tree4.add_left(2, 4));
    CHECK_THROWS(tree4.add_right(2, 5));
    CHECK_THROWS(tree4.add_left(3, 6));
    CHECK_THROWS(tree4.add_right(3, 7));

    CHECK_NOTHROW(tree4.add_root(1));

    // This is not the right root for creating children
    CHECK_THROWS(tree4.add_left(5, 9));
    CHECK_THROWS(tree4.add_right(5, 8));
    CHECK_THROWS(tree4.add_left(9, 11));
    CHECK_THROWS(tree4.add_right(9, 12));

    BinaryTree<string> t4;

    // There is no root for creating children
    CHECK_THROWS(t4.add_left("a", "b"));
    CHECK_THROWS(t4.add_right("a", "c"));
    CHECK_THROWS(t4.add_left("b", "d"));
    CHECK_THROWS(t4.add_right("b", "e"));
    CHECK_THROWS(t4.add_left("c", "f"));
    CHECK_THROWS(t4.add_right("c", "g"));

    CHECK_NOTHROW(t4.add_root("a"));

    // This is not the right root for creating children
    CHECK_THROWS(t4.add_left("e", "i"));
    CHECK_THROWS(t4.add_right("e", "h"));
    CHECK_THROWS(t4.add_left("i", "k"));
    CHECK_THROWS(t4.add_right("i", "l"));
}

TEST_CASE("Bulid tree <int>")
{
    BinaryTree<int> tree5;

    // Bulid
    CHECK_NOTHROW(tree5.add_root(1));
    CHECK_NOTHROW(tree5.add_left(1, 2));
    CHECK_NOTHROW(tree5.add_right(1, 3));
    /* current tree
          1
         / \
        2   3
    */

    // Change
    CHECK_NOTHROW(tree5.add_root(4));
    CHECK_NOTHROW(tree5.add_left(4, 5));
    CHECK_NOTHROW(tree5.add_right(4, 6));
    /* current tree
          4
         / \
        5   6
    */

    // Does not exist
    CHECK_THROWS(tree5.add_left(1, 8));
    CHECK_THROWS(tree5.add_right(1, 12));

    // Bulid
    CHECK_NOTHROW(tree5.add_left(5, 7));
    CHECK_NOTHROW(tree5.add_right(5, 8));
    CHECK_NOTHROW(tree5.add_left(6, 9));
    CHECK_NOTHROW(tree5.add_right(6, 10));
    /* current tree
          4
        /   \
       5     6
      / \   / \
     7   8 9   10
    */

    // Change
    CHECK_NOTHROW(tree5.add_left(5, 1));
    CHECK_NOTHROW(tree5.add_right(5, 2));
    CHECK_NOTHROW(tree5.add_left(6, 3));
    CHECK_NOTHROW(tree5.add_right(6, 11));
    /* current tree
          4
        /   \
       5     6
      / \   / \
     1   2 3   11
    */

    // Does not exist
    CHECK_THROWS(tree5.add_left(7, 12));
    CHECK_THROWS(tree5.add_right(7, 13));
    CHECK_THROWS(tree5.add_left(8, 14));
    CHECK_THROWS(tree5.add_right(8, 15));
    CHECK_THROWS(tree5.add_left(9, 16));
    CHECK_THROWS(tree5.add_right(9, 17));
    CHECK_THROWS(tree5.add_left(10, 18));
    CHECK_THROWS(tree5.add_right(10, 19));

    // Bulid and change
    CHECK_NOTHROW(tree5.add_left(3, 15));
    CHECK_NOTHROW(tree5.add_right(3, 17));
    CHECK_NOTHROW(tree5.add_left(3, 9));
    CHECK_NOTHROW(tree5.add_right(3, 8));
    /* current tree
          4
        /   \
       5     6
      / \   / \
     1   2 3   11
          / \
         9   8
    */
}

TEST_CASE("Bulid tree <string>")
{
    BinaryTree<string> t5;

    // Bulid
    CHECK_NOTHROW(t5.add_root("a"));
    CHECK_NOTHROW(t5.add_left("a", "b"));
    CHECK_NOTHROW(t5.add_right("a", "c"));
    /* current tree
          a
         / \
        b   c
    */

    // Change
    CHECK_NOTHROW(t5.add_root("d"));
    CHECK_NOTHROW(t5.add_left("d", "e"));
    CHECK_NOTHROW(t5.add_right("d", "f"));
    /* current tree
          d
         / \
        e   f
    */

    // Does not exist
    CHECK_THROWS(t5.add_left("a", "w"));
    CHECK_THROWS(t5.add_right("a", "q"));

    // Bulid
    CHECK_NOTHROW(t5.add_left("e", "g"));
    CHECK_NOTHROW(t5.add_right("e", "h"));
    CHECK_NOTHROW(t5.add_left("f", "i"));
    CHECK_NOTHROW(t5.add_right("f", "j"));
    /* current tree
          d
        /   \
       e     f
      / \   / \
     g   h i   j
    */

    // Change
    CHECK_NOTHROW(t5.add_left("e", "a"));
    CHECK_NOTHROW(t5.add_right("e", "b"));
    CHECK_NOTHROW(t5.add_left("f", "c"));
    CHECK_NOTHROW(t5.add_right("f", "p"));
    /* current tree
          d
        /   \
       e     f
      / \   / \
     a   b c   p
    */

    // Does not exist
    CHECK_THROWS(t5.add_left("g", "r"));
    CHECK_THROWS(t5.add_right("g", "t"));
    CHECK_THROWS(t5.add_left("h", "y"));
    CHECK_THROWS(t5.add_right("h", "u"));
    CHECK_THROWS(t5.add_left("i", "o"));
    CHECK_THROWS(t5.add_right("i", "z"));
    CHECK_THROWS(t5.add_left("j", "x"));
    CHECK_THROWS(t5.add_right("j", "v"));

    // Bulid
    CHECK_NOTHROW(t5.add_left("b", "g"));
    CHECK_NOTHROW(t5.add_right("b", "h"));
    CHECK_NOTHROW(t5.add_left("p", "i"));
    CHECK_NOTHROW(t5.add_right("p", "j"));
    /* current tree
          d
        /   \
       e     f
      / \   / \
     a   b c   p
        / \   / \
       g   h i   j
    */
}

TEST_CASE("Print - preorder, inorder, postorder")
{
    BinaryTree<int> t6;
    CHECK_NOTHROW(t6.add_root(1));
    CHECK_NOTHROW(t6.add_left(1, 2));
    CHECK_NOTHROW(t6.add_right(1, 3));
    CHECK_NOTHROW(t6.add_left(2, 4));
    CHECK_NOTHROW(t6.add_right(2, 5));
    /* current tree
          1
        /   \
       2     3
      / \   
     4   5
    */

    BinaryTree<string> t7;
    CHECK_NOTHROW(t7.add_root("a"));
    CHECK_NOTHROW(t7.add_left("a", "b"));
    CHECK_NOTHROW(t7.add_right("a", "c"));
    CHECK_NOTHROW(t7.add_left("c", "d"));
    CHECK_NOTHROW(t7.add_right("c", "e"));
    /* current tree
          a
        /   \
       b     c
            / \   
           d   e
    */

    BinaryTree<int> t8;
    CHECK_NOTHROW(t8.add_root(1));
    CHECK_NOTHROW(t8.add_left(1, 2));
    CHECK_NOTHROW(t8.add_left(2, 3));
    CHECK_NOTHROW(t8.add_left(3, 4));
    CHECK_NOTHROW(t8.add_left(4, 5));
    /* current tree
              1
             /   
            2     
           /   
          3   
         /
        4
       /
      5
    */

    BinaryTree<string> t9;
    CHECK_NOTHROW(t9.add_root("a"));
    CHECK_NOTHROW(t9.add_left("a", "b"));
    CHECK_NOTHROW(t9.add_left("b", "c"));
    CHECK_NOTHROW(t9.add_left("c", "e"));
    CHECK_NOTHROW(t9.add_right("c", "d"));
    /* current tree
              a
             /   
            b     
           /   
          c   
         / \
        e   d
    */

    BinaryTree<int> t10;
    CHECK_NOTHROW(t10.add_root(1));
    CHECK_NOTHROW(t10.add_right(1, 2));
    CHECK_NOTHROW(t10.add_left(2, 3));
    CHECK_NOTHROW(t10.add_right(2, 4));
    CHECK_NOTHROW(t10.add_left(3, 5));
    /* current tree
          1
            \
             2
            / \   
           3   4
          /
         5
    */

     string s1;

//     //----------------------------------- PREORDER -----------------------------------

    //*********** Print t6 ***********
    for (auto it = t6.begin_preorder(); it != t6.end_preorder(); ++it)
    {
        // prints: 1 2 4 5 3
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "12453");
    s1 = "";

    //*********** Print t7 ***********
    for (auto it = t7.begin_preorder(); it != t7.end_preorder(); ++it)
    {
        // prints: a b d c e
        CHECK_NOTHROW(cout << (*it) << " ");
        s1.append(*it);
    }
    CHECK(s1 == "abcde");
    s1 = "";

    //********** Print t8 ********
    for (auto it = t8.begin_preorder(); it != t8.end_preorder(); ++it)
    {
        // prints: 1 2 3 4 5
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "12345");
    s1 = "";

    //*********** Print t9 ***********
    for (auto it = t9.begin_preorder(); it != t9.end_preorder(); ++it)
    {
        // prints: a b c e d
        CHECK_NOTHROW(cout << (*it) << " ");
        s1.append(*it);
    }
    CHECK(s1 == "abced");
    s1 = "";

    //********** Print t10 ********
    for (auto it = t10.begin_preorder(); it != t10.end_preorder(); ++it)
    {
        // prints: 1 2 3 5 4
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "12354");
    s1 = "";

    //----------------------------------- INORDER -----------------------------------

    //********** Print t6 ********
    for (auto it = t6.begin_inorder(); it != t6.end_inorder(); ++it)
    {
        // prints: 4 2 5 1 3
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "42513");
    s1 = "";

    //********** Print t7 ********
    for (auto it = t7.begin_inorder(); it != t7.end_inorder(); ++it)
    {
        // prints: b a d c e
        CHECK_NOTHROW(cout << (*it) << " ");
        s1.append(*it);
    }
    CHECK(s1 == "badce");
    s1 = "";

    //********** Print t8 ********
    for (auto it = t8.begin_inorder(); it != t8.end_inorder(); ++it)
    {
        // prints: 5 4 3 2 1
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "54321");
    s1 = "";

    //********** Print t9 ********
    for (auto it = t9.begin_inorder(); it != t9.end_inorder(); ++it)
    {
        // prints: e c d b a
        CHECK_NOTHROW(cout << (*it) << " ");
        s1.append(*it);
    }
    CHECK(s1 == "ecdba");
    s1 = "";

    //********** Print t10 ********
    for (auto it = t10.begin_inorder(); it != t10.end_inorder(); ++it)
    {
        // prints: 1 5 3 2 4
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "15324");
    s1 = "";

    //----------------------------------- POSTORDER -----------------------------------

    //********** Print t6 ********
    for (auto it = t6.begin_postorder(); it != t6.end_postorder(); ++it)
    {
        // prints: 4 5 2 3 1
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "45231");
    s1 = "";

    //********** Print t7 ********
    for (auto it = t7.begin_postorder(); it != t7.end_postorder(); ++it)
    {
        // prints: b d e c a
        CHECK_NOTHROW(cout << (*it) << " ");
        s1.append(*it);
    }
    CHECK(s1 == "bdeca");
    s1 = "";

    //********** Print t8 ********
    for (auto it = t8.begin_postorder(); it != t8.end_postorder(); ++it)
    {
        // prints: 5 4 3 2 1
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "54321");
    s1 = "";

    //********** Print t9 ********
    for (auto it = t9.begin_postorder(); it != t9.end_postorder(); ++it)
    {
        // prints: e d c b a
        CHECK_NOTHROW(cout << (*it) << " ");
        s1.append(*it);
    }
    CHECK(s1 == "edcba");
    s1 = "";

    //********** Print t10 ********
    for (auto it = t10.begin_postorder(); it != t10.end_postorder(); ++it)
    {
        // prints: 5 3 4 2 1
        CHECK_NOTHROW(cout << (*it) << " ");
        int num = *it;
        std::string str = to_string(num);
        s1.append(str);
    }
    CHECK(s1 == "53421");
    s1 = "";

    //------------------------------ this should work like inorder ------------------------------

    //********** Print t6 ********
    for (int element : t6)
    {
        cout << element << " ";
        // prints: 4 2 5 1 3
        std::string str = to_string(element);
        s1.append(str);
    }
    CHECK(s1 == "42513");
    s1 = "";

    //********** Print t7 ********
    for (string element : t7)
    {
        cout << element << " ";
        // prints: b a d c e
        s1.append(element);
    }
    CHECK(s1 == "badce");
    s1 = "";

    //********** Print t8 ********
    for (int element : t8)
    {
        cout << element << " ";
        // prints: 5 4 3 2 1
        std::string str = to_string(element);
        s1.append(str);
    }
    CHECK(s1 == "54321");
    s1 = "";

    //********** Print t9 ********
    for (string element : t9)
    {
        cout << element << " ";
        // prints: e c d b a
        s1.append(element);
    }
    CHECK(s1 == "ecdba");
    s1 = "";

    //********** Print t10 ********
    for (int element : t10)
    {
        cout << element << " ";
        // prints: 15324
        std::string str = to_string(element);
        s1.append(str);
    }
    CHECK(s1 == "15324");
    s1 = "";
}
//------------------------------ Tree of objects ------------------------------

class Shape
{
public:
    string shape_type;
    Shape(string t) : shape_type(t){};
    bool operator==(const Shape &other) const
    {
        return this->shape_type == other.shape_type;
    };
};
TEST_CASE("Bulid tree <Shape>")
{

    BinaryTree<Shape> shapes_tree;
    CHECK_NOTHROW(shapes_tree.add_root(Shape("circle")));
    CHECK_NOTHROW(shapes_tree.add_left(Shape("circle"), Shape("square")));
    CHECK_NOTHROW(shapes_tree.add_right(Shape("circle"), Shape("triangle")));
    CHECK_NOTHROW(shapes_tree.add_left(Shape("square"), Shape("rectangle")));
    CHECK_NOTHROW(shapes_tree.add_right(Shape("square"), Shape("rhombus")));

    /* current tree
               circle
              /      \
            square   triangle
           /     \   
    rectangle   rhombus
    */

    BinaryTree<Shape> shapes_tree1;
    CHECK_NOTHROW(shapes_tree1.add_root(Shape("circle")));
    CHECK_NOTHROW(shapes_tree1.add_right(Shape("circle"), Shape("triangle")));
    CHECK_NOTHROW(shapes_tree1.add_right(Shape("circle"), Shape("rectangle"))); // Change
    /* current tree
             circle
                   \
                 rectangle
    */
    CHECK_THROWS(shapes_tree1.add_left(Shape("triangle"), Shape("rhombus")));
    CHECK_THROWS(shapes_tree1.add_right(Shape("triangle"), Shape("square")));
}
