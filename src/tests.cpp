#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <sstream>
#include <iostream>

// ============================================================
// STAGE 0 Tests
// ============================================================

/// Create a LegacyData union with an int (42). Call printLegacyData.
/// Verify the returned string matches "42".
void test_printLegacyData_int(void) 
{
    LegacyData lD;
    lD.i=1;
    TEST_ASSERT_TRUE_MESSAGE("1"==printLegacyData(lD,'i'),"Failed test_printLegacyData_int");
}

/// Create a LegacyData union with a double (3.14). Call printLegacyData.
/// Verify the returned string matches "3.14".
void test_printLegacyData_double(void) 
{
    LegacyData lD;
    lD.d=1.03;
    TEST_ASSERT_TRUE_MESSAGE("1.03"==printLegacyData(lD,'d'),"Failed test_printLegacyData_double");
}

// ============================================================
// STAGE 1 Tests
// ============================================================

/// Call createTwoStructNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoStructNodes_links_correctly(void) 
{
    structNode* head=createTwoStructNodes();
    TEST_ASSERT_TRUE_MESSAGE(printLegacyData(head->value,'i')=="5", "Failed test_createTwoStructNodes_links_correctly Test 1");
    TEST_ASSERT_TRUE_MESSAGE(printLegacyData(head->nextPtr->value,'d')=="3.14", "Failed test_createTwoStructNodes_links_correctly Test 2");
    free(head->nextPtr);
    free(head);
}

// ============================================================
// STAGE 2 Tests
// ============================================================

/// Call createTwoClassNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoClassNodes_links_correctly(void) 
{
    classNode* head=createTwoClassNodes();
    TEST_ASSERT_TRUE_MESSAGE(printLegacyData(head->value,'i')=="5", "Failed test_createTwoClassNodes_links_correctly Test 1");
    TEST_ASSERT_TRUE_MESSAGE(printLegacyData(head->nextPtr->value,'d')=="3.14", "Failed test_createTwoClassNodes_links_correctly Test 2");
    free(head->nextPtr);
    free(head);
}

// ============================================================
// STAGE 3 Tests
// ============================================================

/// Call createTwoTemplateNodes().
/// Verify head->value is 5 and head->nextPtr->value is 3.
/// Clean up allocated memory.
void test_createTwoTemplateNodes_links_correctly(void) 
{
    classNodeT<int>* head=createTwoTemplateNodes();
    TEST_ASSERT_TRUE_MESSAGE(head->value==5, "Failed test_createTwoTemplateNodes_links_correctly Test 1");
    TEST_ASSERT_TRUE_MESSAGE(head->nextPtr->value==3, "Failed test_createTwoTemplateNodes_links_correctly Test 2");
    free(head->nextPtr);
    free(head);
}

// ============================================================
// STAGE 4: LinkedList Tests
// ============================================================

/// Create a LinkedList. Add two nodes using addFirst.
/// Verify listLength() returns 2 after insertions.
void test_linkedList_addFirst_updates_counter(void) 
{

    LinkedList linked=LinkedList();

    ModernData m1 = 1;
    classNodeVariant* n1 = new classNodeVariant(m1);
    linked.addFirst(n1);

    ModernData m2 = 2;
    classNodeVariant* n2 = new classNodeVariant(m2);
    linked.addFirst(n2);

    TEST_ASSERT_TRUE_MESSAGE(linked.listLength()==2, "Failed test_linkedList_addFirst_updates_counter");
}

/// Create a LinkedList. Add nodes (10, then 20) using addLast.
/// Capture std::cout and verify elements appear in order ("10" before "20").
void test_linkedList_addLast_places_at_end(void) 
{
    LinkedList linked=LinkedList();

    ModernData m1 = 10;
    classNodeVariant* n1 = new classNodeVariant(m1);
    linked.addLast(n1);

    ModernData m2 = 20;
    classNodeVariant* n2 = new classNodeVariant(m2);
    linked.addLast(n2);

    linked.printList();

    TEST_ASSERT_TRUE_MESSAGE(false, "I dont know how to capture cout");
}

/// Create a LinkedList with an int, double, and string.
/// Call deleteValue() with the double value (3.14).
/// Verify list length decreases to 2 and second call returns -1.
void test_linkedList_deleteValue_removes_variant(void) 
{
    LinkedList linked=LinkedList();

    ModernData m1 = 10;
    classNodeVariant* n1 = new classNodeVariant(m1);
    linked.addLast(n1);

    ModernData m2 = 3.14;
    classNodeVariant* n2 = new classNodeVariant(m2);
    linked.addLast(n2);

    ModernData m3 = "goober";
    classNodeVariant* n3 = new classNodeVariant(m3);
    linked.addLast(n3);

    linked.printList();

    int test=linked.deleteValue(3.14);

    linked.printList();

    std::cout<<test<<std::endl;

    TEST_ASSERT_TRUE_MESSAGE(test==0, "Failed test_linkedList_deleteValue_removes_variant Test 1");
    TEST_ASSERT_TRUE_MESSAGE(linked.listLength()==2, "Failed test_linkedList_deleteValue_removes_variant Test 2");
}

/// Create a LinkedList and insert three nodes.
/// Call destroyList().
/// Verify listLength() becomes 0.
void test_linkedList_destroyList_clears_all(void) 
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteFirst().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteFirst(void) 
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteLast().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteLast(void) 
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Create a LinkedList with nodes (1, 2.5, "test").
/// Redirect std::cout buffer and call printList().
/// Verify printed output contains "1", "2.5" (or "2.50"), and "test".
void test_linkedList_printList(void) 
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}