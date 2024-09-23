#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// Function prototypes
void READ(int instructmemloc, vector<int>* mainmemory);
void WRITE(int instructmemloc, vector<int>* mainmemory);

// Mock input and output streams
istringstream input;
ostringstream output;

// Redirect cin and cout
#define cin input
#define cout output

// Function definitions
void READ(int instructmemloc, vector<int>* mainmemory) {
    int tempword;
    cin >> tempword;
    if (instructmemloc >= 0 && instructmemloc < mainmemory->size()) {
        (*mainmemory)[instructmemloc] = tempword;
    } else {
        cerr << "error: memory location out of bounds." << endl;
    }
}

void WRITE(int instructmemloc, vector<int>* mainmemory) {
    if (instructmemloc >= 0 && instructmemloc < mainmemory->size()) {
        cout << (*mainmemory)[instructmemloc];
    } else {
        cerr << "error: memory location out of bounds." << endl;
    }
}

// Unit tests
TEST(MemoryTest, ReadValidLocation) {
    vector<int> memory(10, 0);
    input.str("42");
    READ(5, &memory);
    EXPECT_EQ(memory[5], 42);
}

TEST(MemoryTest, ReadInvalidLocation) {
    vector<int> memory(10, 0);
    input.str("42");
    testing::internal::CaptureStderr();
    READ(15, &memory);
    string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "error: memory location out of bounds.\n");
}

TEST(MemoryTest, WriteValidLocation) {
    vector<int> memory(10, 0);
    memory[5] = 42;
    WRITE(5, &memory);
    EXPECT_EQ(output.str(), "42");
}

TEST(MemoryTest, WriteInvalidLocation) {
    vector<int> memory(10, 0);
    testing::internal::CaptureStderr();
    WRITE(15, &memory);
    string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "error: memory location out of bounds.\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
