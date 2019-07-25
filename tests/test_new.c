﻿#include <CUnit/CUnit.h>

#include <stdio.h>
#include "cmat.h"
#include "test_add.h"

static void
test_normal_1(void)
{
  int err;

  cmat_t* m;

  m   = NULL;

  err = cmat_new(10, &m);

  CU_ASSERT(err == 0);
  CU_ASSERT(m != NULL);

  if (m != NULL) {
    CU_ASSERT(m->rows == 0);
    CU_ASSERT(m->cols == 10);
  }

  cmat_destroy(m);
}

static void
test_normal_2(void)
{
  int err;
  cmat_t* m;
  double v[] = {
    1, 2, 3,
    4, 5, 6,
  };

  m   = NULL;
  err = cmat_new2(v, 2, 3, &m);

  CU_ASSERT(err == 0);
  CU_ASSERT(m != NULL);

  if (m != NULL) {
    CU_ASSERT(m->rows == 2);
    CU_ASSERT(m->cols == 3);
  }

  cmat_destroy(m);
}

static void
test_error_e1(void)
{
  int err;
  cmat_t* m;

  err = cmat_new(-1, &m);
  CU_ASSERT(err == CMAT_ERR_BSIZE);
}

static void
test_error_e2(void)
{
  int err;
  cmat_t* m;

  err = cmat_new(5, NULL);
  CU_ASSERT(err == CMAT_ERR_BADDR);
}

void
init_test_new()
{
  CU_pSuite suite;

  suite = CU_add_suite("create object", NULL, NULL);
  CU_add_test(suite, "new#1", test_normal_1);
  CU_add_test(suite, "new#2", test_normal_2);
  CU_add_test(suite, "new#E1", test_error_e1);
  CU_add_test(suite, "new#E2", test_error_e2);
}
