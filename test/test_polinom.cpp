#include <gtest.h>
#include "polinom.h"

TEST(polinom_test, can_create_polinom_of_zero_size)
{
    Polinom p;
    EXPECT_EQ(p.size(), 0);
}
TEST(polinom_test, can_get_monom_from_polinom)
{
    Polinom p;
    Monom m1(1, 111);
    Monom m2(2, 222);

    p = p + m1;
    p = p + m2;

    EXPECT_EQ(p[0], m1);
}
TEST(polinom_test, throws_when_index_of_monom_is_negative)
{
    Polinom p;
    Monom m1(1, 111);

    p = p + m1;

    ASSERT_ANY_THROW(p[-1]);
}
TEST(polinom_test, throws_when_index_of_monom_is_too_big)
{
    Polinom p;
    Monom m1(1, 111);

    p = p + m1;

    ASSERT_ANY_THROW(p[1]);
}
TEST(polinom_test, can_add_monom_to_empty_polinom)
{
    Polinom p;
    Monom m(2, 345);
 
    p = p + m;

    EXPECT_EQ(p[0], m);
}
TEST(polinom_test, can_add_monom_to_not_empty_polinom)
{
    Polinom p;
    Monom m1(2, 345);
    p = p + m1;

    Monom m2(1, 403);
    p = p + m2;

    EXPECT_EQ(p[1],m2);
}
TEST(polinom_test, can_add_monom_in_right_order)
{
    Polinom p;
    Monom m1(2, 777);
    p = p + m1;

    Monom m2(1, 403);
    p = p + m2;

    EXPECT_EQ(p[0], m2);
}
TEST(polinom_test, can_substract_monom_from_empty_polinom)
{
    Polinom p;
    Monom m(3, 777);

    p = p - m;
    Monom test(-3, 777);

    EXPECT_EQ(p[0], test);
}
TEST(polinom_test, can_substract_monom_from_not_empty_polinom)
{
    Polinom p;
    Monom m1(4, 222);
    Monom m2(3, 777);
    p = p + m1;

    p = p - m2;
    Monom test(-3, 777);

    EXPECT_EQ(p[1], test);
}
TEST(polinom_test, can_substract_polinoms_with_eq_monoms)
{
    Polinom p;
    Monom m1(4, 222);
    Monom m2(3, 222);
    p = p + m1;

    p = p - m2;
    Monom test(1, 222);

    EXPECT_EQ(p[0], test);
}
TEST(polinom_test, can_substract_polinoms_in_right_order)
{
    Polinom p;
    Monom m1(4, 222);
    Monom m2(3, 111);
    p = p + m1;

    p = p - m2;
    Monom test(-3, 111);

    EXPECT_EQ(p[0], test);
}
TEST(polinom_test, size_of_polinom_correct_after_substraction_with_eq_monoms)
{
    Polinom p;
    Monom m1(4, 222);
    Monom m2(3, 222);
    p = p + m1;

    p = p - m2;

    EXPECT_EQ(p.size(), 1);
}
TEST(polinom_test, can_add_polinoms)
{
    Monom m1(2, 222);
    Monom m2(3, 333);
    Monom m3(4, 444);
    std::vector<Monom> v1 = { m1,m2,m3 };
    Polinom pol1(v1);

    Monom m4(5, 555);
    Monom m5(1, 111);
    std::vector<Monom> v2 = { m4,m5 };
    Polinom pol2(v2);

    Polinom pol3 = pol1 + pol2;

    EXPECT_EQ(pol3[0], m5);
    EXPECT_EQ(pol3.size(), 5);
}

TEST(polinom_test, can_substract_polinoms)
{
    Monom m1(4, 111);
    Monom m2(3, 222);
    Monom m3(4, 303);
    std::vector<Monom> v1 = { m1,m2,m3 };
    Polinom pol1(v1);

    Monom m4(1, 111);
    Monom m5(-2, 222);
    Monom m6(9, 100);
    std::vector<Monom> v2 = { m4,m5,m6 };
    Polinom pol2(v2);

    Polinom pol3 = pol1 - pol2;
    Monom test1(-9, 100);
    Monom test2(3, 111);
    Monom test3(5, 222);

    EXPECT_EQ(pol3.size(), 4);
    EXPECT_EQ(pol3[0], test1);
    EXPECT_EQ(pol3[1], test2);
    EXPECT_EQ(pol3[2], test3);
}

TEST(polinom_test, can_mult_polinoms)
{
    Polinom pol1;
    Polinom pol2;
    pol1 = pol1 + Monom(2, 333);
    pol2 = pol2 + Monom(3, 444);

    Polinom pol3 = pol1 * pol2;
    Monom test(6, 777);

    EXPECT_EQ(pol3.size(), 1);
    EXPECT_EQ(pol3[0], test);
}
TEST(polinom_test, can_mult_and_sort_polinoms)
{
    Monom m1(2, 123);
    Monom m2(4, 203);
    std::vector<Monom> v1 = { m1,m2 };
    Polinom pol1(v1);

    Monom m3(3, 304);
    Monom m4(5, 231);
    std::vector<Monom> v2 = { m3,m4 };
    Polinom pol2(v2);

    Polinom pol3 = pol1 * pol2;

    Monom test1(10, 354);
    Monom test2(6, 427);
    Monom test3(20, 434);

    EXPECT_EQ(pol3.size(), 4);
    EXPECT_EQ(pol3[0], test1);
    EXPECT_EQ(pol3[1], test2);
    EXPECT_EQ(pol3[2], test3);
}
TEST(polinom_test, can_mult_and_delete)
{
    Monom m1(2, 123);
    Monom m2(4, 203);
    std::vector<Monom> v1 = { m1,m2 };
    Polinom pol1(v1);

    Monom m3(3, 304);
    Monom m4(5, 224);
    std::vector<Monom> v2 = { m3,m4 };
    Polinom pol2(v2);

    Polinom pol3 = pol1 * pol2;

    Monom test1(10, 347);
    Monom test2(26, 427);
    Monom test3(12, 507);

    EXPECT_EQ(pol3.size(), 3);
    EXPECT_EQ(pol3[0], test1);
    EXPECT_EQ(pol3[1], test2);
    EXPECT_EQ(pol3[2], test3);
}
TEST(polinom_test, can_mult_polinom_by_scalar)
{
    Polinom p;
    p = p + Monom(2, 333);

    Polinom result = p * 3;
    Monom test(6, 333);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], test);
}

TEST(polinom_test, can_mult_polinom_by_monom)
{
    Polinom p;
    p = p + Monom(2, 321);
    Monom m(3, 444);

    Polinom result = p * m;
    Monom test(6, 765);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], test);
}

TEST(polinom_test, can_remove_monom_with_zero_coef)
{
    Polinom p;
    p = p + Monom(5, 321);
    p = p + Monom(-5, 321);

    EXPECT_EQ(p.size(), 0); 
}
TEST(polinom_test, throws_if_pow_is_too_big)
{
    Polinom p;
    p = p + Monom(5, 555);

    ASSERT_ANY_THROW(p * Monom(5, 500));
}
TEST(monom_test, can_mult_monom_by_polinom)
{
    Monom m(2, 345);
    Polinom p;
    p = p + Monom(3, 222);
    p = p + Monom(2, 221);

    ASSERT_NO_THROW(Polinom pol = m * p);
}
TEST(monom_test, mult_monom_by_polinom_correctly)
{
    Monom m(2, 345);
    Polinom p;
    p = p + Monom(3, 222);
    p = p + Monom(2, 221);

    Polinom pol = m * p;
    Monom test(4, 566);

    EXPECT_EQ(pol.size(), 2);
    EXPECT_EQ(pol[0], test);
}
