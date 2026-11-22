#include <catch2/catch_test_macros.hpp>
#include "intvector.hpp"

using intvector::Vector;

TEST_CASE("Konstruktoren und grundlegende Eigenschaften", "[Vector][Constructor]") {
    SECTION("Standardkonstruktor erzeugt leeren Vektor") {
        Vector v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty() == true);
    }

    SECTION("Konstruktor mit übergebenem Array") {
        int data[] = {10, 20, 30, 40};
        Vector v(data, 4);

        REQUIRE(v.size() == 4);
        REQUIRE_FALSE(v.empty());
        REQUIRE(v.at(0) == 10);
        REQUIRE(v.at(1) == 20);
        REQUIRE(v.at(2) == 30);
        REQUIRE(v.at(3) == 40);
    }

    SECTION("Konstruktor mit Nullpointer und Größe 0") {
        Vector v(nullptr, 0);
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty());
    }

    SECTION("Fill-Konstruktor mit Standardwert 0") {
        Vector v(5);
        REQUIRE(v.size() == 5);
        for (size_t i{0}; i < 5; ++i) {
            REQUIRE(v.at(i) == 0);
        }
    }

    SECTION("Fill-Konstruktor mit benutzerdefiniertem Wert") {
        Vector v(3, 42);
        REQUIRE(v.size() == 3);
        REQUIRE_FALSE(v.empty());
        for (size_t i{0}; i < 3; ++i) {
            REQUIRE(v.at(i) == 42);
        }
    }
}

TEST_CASE("Elementzugriff mit at() und operator[]", "[Vector][Access]") {
    int data[] = {-5, 0, 15, 100};
    Vector v(data, 4);

    SECTION("Lesen mit at()") {
        REQUIRE(v.at(0) == -5);
        REQUIRE(v.at(1) == 0);
        REQUIRE(v.at(2) == 15);
        REQUIRE(v.at(3) == 100);
    }

    SECTION("Lesen mit operator[]") {
        REQUIRE(v[1] == 0);
        REQUIRE(v[2] == 15);
        REQUIRE(v[3] == 100);
    }
}

TEST_CASE("Modifikation mit push_back() und pop_back()", "[Vector][Modifiers]") {
    Vector v;

    SECTION("push_back fügt Elemente hinzu und vergrößert Kapazität dynamisch") {
        for (size_t i{1}; i <= 20; ++i) {
            v.push_back(i * 10);
            REQUIRE(v.size() == i);
            REQUIRE(v.at(i - 1) == i * 10);
        }
        REQUIRE_FALSE(v.empty());
    }

    SECTION("pop_back entfernt das letzte Element und gibt es zurück") {
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
}

TEST_CASE("Addition mit operator+", "[Vector][Operators]") {
    int a_data[] = {1, 2, 3};
    int b_data[] = {4, 5};
    Vector a(a_data, 3);
    Vector b(b_data, 2);

    SECTION("Zwei Vektoren addieren") {
        Vector c = a + b;
        REQUIRE(c.size() == 5);
        REQUIRE(c.at(0) == 1);
        REQUIRE(c.at(1) == 2);
        REQUIRE(c.at(2) == 3);
        REQUIRE(c.at(3) == 4);
        REQUIRE(c.at(4) == 5);

        REQUIRE(a.size() == 3);
        REQUIRE(b.size() == 2);
    }

    SECTION("Addition mit leerem Vektor") {
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
