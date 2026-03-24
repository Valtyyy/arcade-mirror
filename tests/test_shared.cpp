/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests for shared
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "DlLoader.hpp"

#define TEST_LIB LIB_PATH "libtest_lib.so"
#define INVALID_LIB "./nonexistent_lib.so"

Test(DlLoader, not_loaded_before_load)
{
    DlLoader loader(TEST_LIB);
    cr_assert_eq(loader.is_loaded(), false);
}

Test(DlLoader, loaded_after_load)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    cr_assert_eq(loader.is_loaded(), true);
}

Test(DlLoader, not_loaded_after_unload)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    loader.unload();
    cr_assert_eq(loader.is_loaded(), false);
}

Test(DlLoader, load_invalid_path_throws)
{
    DlLoader loader(INVALID_LIB);
    cr_assert_throw(loader.load(), std::runtime_error);
}

Test(DlLoader, double_load_is_idempotent)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    loader.load();
    cr_assert_eq(loader.is_loaded(), true);
}

Test(DlLoader, unload_when_not_loaded_is_safe)
{
    DlLoader loader(TEST_LIB);
    loader.unload();
    cr_assert_eq(loader.is_loaded(), false);
}

Test(DlLoader, reload_after_unload)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    loader.unload();
    loader.load();
    cr_assert_eq(loader.is_loaded(), true);
}

Test(DlLoader, sym_returns_null_when_not_loaded)
{
    DlLoader loader(TEST_LIB);
    cr_assert_null(loader.sym("sum"));
}

Test(DlLoader, sym_valid_symbol)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    void *s = loader.sym("sum");
    cr_assert_not_null(s);
}

Test(DlLoader, sym_invalid_symbol_throws)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    cr_assert_throw(loader.sym("nonexistent_symbol_xyz"), std::runtime_error);
}

Test(DlLoader, sym_callable_sum)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    auto fn = reinterpret_cast<int(*)(int, int)>(loader.sym("sum"));
    cr_assert_eq(fn(3, 4), 7);
}

Test(DlLoader, sym_callable_mul)
{
    DlLoader loader(TEST_LIB);
    loader.load();
    auto fn = reinterpret_cast<int(*)(int, int)>(loader.sym("mul"));
    cr_assert_eq(fn(3, 4), 12);
}
