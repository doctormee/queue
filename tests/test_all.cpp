#include "gtest/gtest.h"
#include "MainController.h"
#include <iostream>
#include <fstream>
#include <cstdio>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
