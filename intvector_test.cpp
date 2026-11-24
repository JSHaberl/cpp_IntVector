#include <catch2/catch_test_macros.hpp>
#include "intvector.hpp"

using intvector::Vector;

TEST_CASE("Constructor and defaut values", "[Vector][Constructor]") {
    SECTION("Default-Constructor generates empty Vector") {
        Vector v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty() == true);
        REQUIRE(v.capacity() == 100);
    }

    SECTION("Constructor with array") {
        int data[] = {10, 20, 30, 40};
        Vector v(data, 4);

        REQUIRE(v.size() == 4);
        REQUIRE(v.capacity() == 100);
        REQUIRE_FALSE(v.empty());
        REQUIRE(v.at(0) == 10);
        REQUIRE(v.at(1) == 20);
        REQUIRE(v.at(2) == 30);
        REQUIRE(v.at(3) == 40);
    }

    SECTION("Constructor with array of 100"){
        int data[100] = {};
        Vector v(data, 100);
        REQUIRE(v.size() == 100);
        REQUIRE(v.capacity() == 200);
        REQUIRE_FALSE(v.empty());

    }

    SECTION("Constructor with array of 2 and set capacity"){
        int data[2] = {};
        Vector v(data, 2, 3);
        REQUIRE(v.size() == 2);
        REQUIRE(v.capacity() == 3);
        REQUIRE_FALSE(v.empty());

    }

    SECTION("Constructor with array of 2 and insufficient capacity"){
        int data[2] = {};
        Vector v(data, 2, 1);
        REQUIRE(v.size() == 2);
        REQUIRE(v.capacity() == 4);
        REQUIRE_FALSE(v.empty());

    }

    SECTION("Constructor with nullptr and size 0") {
        Vector v(nullptr, 0);
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty());
    }

    SECTION("Fill-Constructor with default fill 0") {
        Vector v(5);
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 100);
        for (size_t i{0}; i < 5; ++i) {
            REQUIRE(v.at(i) == 0);
        }
    }

    SECTION("Fill-Constructor with defined fill") {
        Vector v(3, 42);
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 100);
        REQUIRE_FALSE(v.empty());
        for (size_t i{0}; i < 3; ++i) {
            REQUIRE(v.at(i) == 42);
        }
    }

    SECTION("Fill-Constructor with 100 fills"){
        Vector v(100, 10);
        REQUIRE(v.size() == 100);
        REQUIRE(v.capacity() == 200);
        REQUIRE_FALSE(v.empty());
    }

    SECTION("Fill-Constructor with 10 fills and insufficient capacity"){
        Vector v(10, 53, 9);
        REQUIRE(v.size() == 10);
        REQUIRE(v.capacity() == 20);
        REQUIRE_FALSE(v.empty());
    }
}

TEST_CASE("Accessing elements with at() and operator[]", "[Vector][Access]") {
    int data[] = {-5, 0, 15, 100};
    Vector v(data, 4);

    SECTION("Getting elements with at()") {
        REQUIRE(v.at(0) == -5);
        REQUIRE(v.at(1) == 0);
        REQUIRE(v.at(2) == 15);
        REQUIRE(v.at(3) == 100);
    }

    SECTION("Getting elements with operator[]") {
        REQUIRE(v[1] == 0);
        REQUIRE(v[2] == 15);
        REQUIRE(v[3] == 100);
    }
}

TEST_CASE("Modification with push_back(), pop_back() and copy()", "[Vector][Modifiers]") {
    Vector v;
    int a_data[] = {1, 2, 3, 4};
    int b_data[] = {1, 2, 3};

    SECTION("push_back adds elements and dynamically increases capacity") {
        for (size_t i{1}; i <= 120; ++i) {
            v.push_back(i * 10);
            REQUIRE(v.size() == i);
            REQUIRE(v.at(i - 1) == i * 10);
        }
        REQUIRE(v.capacity() == 200);
        REQUIRE_FALSE(v.empty());
    }

    SECTION("pop_back removes last element and returns it") {
        v.push_back(100);
        v.push_back(200);
        v.push_back(300);

        REQUIRE(v.pop_back() == 300);
        REQUIRE(v.size() == 2);

        REQUIRE(v.pop_back() == 200);
        REQUIRE(v.size() == 1);

        REQUIRE(v.pop_back() == 100);
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty());
    }

    SECTION("copy copies array to Vector") {
        v.copy(a_data, 4);
        REQUIRE(v.size() == 4);
        for (size_t i{0}; i < v.size(); i++){
            REQUIRE( v[i] == a_data[i]);
        }
    }

    SECTION("copying a smaller array on a Vector decreases its size"){
        v.copy(a_data, 4);
        REQUIRE(v.size() == 4);
        REQUIRE(v.capacity() == 100);
        v.copy(b_data, 3);
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 100);
    }

    SECTION("resize increases capacity but not size"){
        v.copy(a_data, 4);
        v.resize(8);
        REQUIRE(v.size() == 4);
        REQUIRE(v.capacity() == 8);

    }

    SECTION("resize cannot increases capacity above size() * 2"){
        v.copy(a_data, 4);
        v.resize(9);
        REQUIRE(v.size() == 4);
        //Default value for capacity, resize did indeed not increase capacity above size if true
        REQUIRE(v.capacity() == 100);

    }
}

TEST_CASE("Addition with operator+", "[Vector][Operators]") {
    int a_data[] = {1, 2, 3};
    int b_data[] = {4, 5};
    Vector a(a_data, 3);
    Vector b(b_data, 2);

    SECTION("Adding two Vectors") {
        Vector c = a + b;
        REQUIRE(c.size() == 5);
        REQUIRE(c.at(0) == 1);
        REQUIRE(c.at(1) == 2);
        REQUIRE(c.at(2) == 3);
        REQUIRE(c.at(3) == 4);
        REQUIRE(c.at(4) == 5);
        REQUIRE(c.capacity() == 100);

        REQUIRE(a.size() == 3);
        REQUIRE(b.size() == 2);
    }

    SECTION("Adding with an empty Vector") {
        Vector empty_vec;
        Vector res1 = a + empty_vec;
        Vector res2 = empty_vec + a;

        REQUIRE(res1.size() == 3);
        REQUIRE(res2.size() == 3);
        for (size_t i{0}; i < 3; ++i) {
            REQUIRE(res1.at(i) == a.at(i));
            REQUIRE(res2.at(i) == a.at(i));
        }
    }
}
