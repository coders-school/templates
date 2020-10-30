#include <gtest/gtest.h>

#include "make_unique.hpp"

// constexpr int testValue = 10;
// constexpr int secondTestValue = 666;

// struct MakeUniqueTest : ::testing::Test {
//     SharedPointerTest()
//         : sharedPtr(new int(testValue)) {}
//     coders::shared_ptr<int> sharedPtr;
// };

// TEST_F(SharedPointerTest, ShouldCreateNullptrSharedPointerToIntegerUsingDefaultConstructor) {
//     // Given
//     size_t sharedPtrCnt = 1;

//     // When
//     coders::shared_ptr<int> emptySharedPtr{};

//     // Then
//     ASSERT_FALSE(emptySharedPtr);
//     ASSERT_EQ(emptySharedPtr.get(), nullptr);
//     ASSERT_EQ(emptySharedPtr.operator->(), nullptr);
//     ASSERT_EQ(emptySharedPtr.use_count(), sharedPtrCnt);
// }

// TEST(SharedPointerTestWithDeleter, ShouldUseGivenDeleter) {
//     // Given
//     struct testStruct {
//         int a = 20;
//     };
//     testStruct* tStruct = new testStruct();
//     auto testDeleter = [](testStruct* p) {
//         std::cout << "My deleter!\n";
//         p->a = -1;
//     };

//     // When
//     {
//         coders::shared_ptr<testStruct> testPtr(tStruct, testDeleter);
//     }

//     // Then
//     ASSERT_EQ(tStruct->a, -1);
//     delete tStruct;
// }
