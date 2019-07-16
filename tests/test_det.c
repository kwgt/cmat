﻿#include <CUnit/CUnit.h>

#include <stdio.h>
#include "cmat.h"
#include "test_det.h"

#define N(x)        (sizeof(x) / sizeof(*x))

static int
create_matrix(const matrix_info_t* info, cmat_t** dst)
{
  return cmat_new2(info->val, info->rows, info->cols, dst);
}

static void
test_normal_1(void)
{
  cmat_t* m1;
  double det;
  int i;

  for (i = 0; i < N(data); i++) {
    create_matrix(&data[i].op, &m1);

    cmat_det(m1, &det);

#if 0
    printf("\n");
    cmat_print(m1, NULL);
    printf("\n");
    cmat_print(m2, NULL);
    printf("\n");
    cmat_print(m3, NULL);
#endif

    CU_ASSERT(det == data[i].ans);

    cmat_destroy(m1);
  }
}

void
init_test_det()
{
  CU_pSuite suite;

  suite = CU_add_suite("det", NULL, NULL);
  CU_add_test(suite, "det#1", test_normal_1);
}
