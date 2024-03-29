﻿#include <CUnit/CUnit.h>

#include <stdio.h>
#include "cmat.h"
#include "test_add.h"

#define N(x)        (sizeof(x) / sizeof(*x))

static int
create_matrix(const matrix_info_t* info, cmat_t** dst)
{
  return cmat_new(info->val, info->rows, info->cols, dst);
}

static void
check_matrix(cmat_t* ptr, const matrix_info_t* info)
{
  int err;
  int res;

  err = cmat_check(ptr, info->val, &res);

  CU_ASSERT(err == 0);
  CU_ASSERT(res == 0);
  CU_ASSERT(ptr->rows == info->rows);
  CU_ASSERT(ptr->cols == info->cols);
}

static void
test_normal_1(void)
{
  cmat_t* m1;
  cmat_t* m2;
  cmat_t* m3;
  int i;
  int err;

  for (i = 0; i < N(data); i++) {
    create_matrix(&data[i].op1, &m1);
    create_matrix(&data[i].op2, &m2);

    err = cmat_add(m1, m2, &m3);
    CU_ASSERT(err == 0);

#if 0
    printf("\n");
    cmat_print(m1, NULL);
    printf("\n");
    cmat_print(m2, NULL);
    printf("\n");
    cmat_print(m3, NULL);
#endif

    check_matrix(m3, &data[i].ans);

    cmat_destroy(m1);
    cmat_destroy(m2);
    cmat_destroy(m3);
  }
}

static void
test_normal_2(void)
{
  cmat_t* m1;
  cmat_t* m2;
  int i;
  int err;

  for (i = 0; i < N(data); i++) {
    create_matrix(&data[i].op1, &m1);
    create_matrix(&data[i].op2, &m2);

#if 0
    printf("\n");
    cmat_print(m1, "src");
    printf("\n");
    cmat_print(m2, "op");
#endif

    err = cmat_add(m1, m2, NULL);
    CU_ASSERT(err == 0);

#if 0
    printf("\n");
    cmat_print(m1, "dst");
#endif

    check_matrix(m1, &data[i].ans);

    cmat_destroy(m1);
    cmat_destroy(m2);
  }
}

static void
test_error_1(void)
{
  int err;
  cmat_t* m;

  double v[] = {
    1, 2,
    3, 4
  };

  cmat_new(v, 2, 2, &m);

  err = cmat_add(m, NULL, NULL);
  
  CU_ASSERT(err == CMAT_ERR_BADDR);

  cmat_destroy(m);
}

static void
test_error_2(void)
{
  int err;
  cmat_t* m;

  double v[] = {
    1, 2,
    3, 4
  };

  cmat_new(v, 2, 2, &m);

  err = cmat_add(NULL, m, NULL);
  
  CU_ASSERT(err == CMAT_ERR_BADDR);

  cmat_destroy(m);
}



void
init_test_add()
{
  CU_pSuite suite;

  suite = CU_add_suite("add", NULL, NULL);
  CU_add_test(suite, "add#1", test_normal_1);
  CU_add_test(suite, "add#2", test_normal_2);
  CU_add_test(suite, "add#E1", test_error_1);
  CU_add_test(suite, "add#E2", test_error_2);
}
