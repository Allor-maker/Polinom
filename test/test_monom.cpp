#include <gtest.h>
#include "polinom.h"

TEST(monom_test, can_create_monom)
{
    Monom m(2, 3);

    EXPECT_EQ(m.get_k(), 2);
    EXPECT_EQ(m.get_value(), 3);
}

TEST(monom_test, can_add_monoms)
{
    Monom m1(2, 3);
    Monom m2(3, 3);
    Monom result = m1 + m2;
    EXPECT_EQ(result.get_k(), 5);
    EXPECT_EQ(result.get_value(), 3);
}

TEST(monom_test, cant_add_monoms_with_diff_pow)
{
    Monom m1(2, 3);
    Monom m2(3, 4);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(monom_test, can_sub_monoms)
{
    Monom m1(5, 3);
    Monom m2(3, 3);
    Monom result = m1 - m2;
    EXPECT_EQ(result.get_k(), 2);
    EXPECT_EQ(result.get_value(), 3);
}

TEST(monom_test, cant_sub_monom_with_diff_pow)
{
    Monom m1(5, 3);
    Monom m2(3, 4);
    ASSERT_ANY_THROW(m1 - m2);
}

TEST(monom_test, can_mult_monoms)
{
    Monom m1(2, 3);
    Monom m2(3, 4);
    Monom result = m1 * m2;
    EXPECT_EQ(result.get_k(), 6);
    EXPECT_EQ(result.get_value(), 7);
}

TEST(monom_test, cant_mult_monoms_with_too_big_pows)
{
    Monom m1(2, 123);
    Monom m2(3, 237);
    ASSERT_ANY_THROW(m1 * m2);
}

