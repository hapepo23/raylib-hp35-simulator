#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hp35.h"

#define M_PI 3.14159265358979323846

// Registers
static double x, y, z, t, s;
// Input
static bool enter_num_pre;
static bool enter_num_post;
static bool enter_exp;
static unsigned long long x_pre, x_post;
static unsigned int x_exp;  // 00..99
static bool x_neg, x_exp_neg;
static unsigned numcount;  // max. 10
// Display
static char display[100];
// Switches
static bool last_enter_sto_clx;  // no stack raise
static bool last_arc;            // asin, acos, atan

static void replace_substring(char* str, const char* old, const char* new) {
  size_t oldlen = strlen(old);
  size_t newlen = strlen(new);
  char* p = strstr(str, old);
  if (!p)
    return;
  if (oldlen != newlen)
    memmove(p + newlen, p + oldlen, strlen(p + oldlen) + 1);
  memcpy(p, new, newlen);
}

static void hp35_convert_input(void) {
  x = x_post;
  while (x >= 1.0)
    x /= 10.0;
  x += x_pre;
  if (x_exp > 0)
    x = x * pow(10., x_exp_neg ? -1. * (double)x_exp : (double)x_exp);
  if (x_neg)
    x = -x;
}

static void hp35_stack_down(void) {
  y = z;
  z = t;
}

static void hp35_stack_up(void) {
  t = z;
  z = y;
  y = x;
}

static void hp35_reset(void) {
  last_enter_sto_clx = false;
  last_arc = false;
  enter_num_pre = false;
  enter_num_post = false;
  enter_exp = false;
  x_pre = 0;
  x_post = 0;
  x_exp = 0;
  x_neg = false;
  x_exp_neg = false;
  numcount = 0;
}

static void hp35_enter_digit(int digit) {
  if (enter_num_pre) {
    if (numcount < 10) {
      x_pre = x_pre * 10 + digit;
      numcount++;
    }
  } else if (enter_num_post) {
    if (numcount < 10) {
      x_post = x_post * 10 + digit;
      numcount++;
    }
  } else if (enter_exp) {
    x_exp = x_exp * 10 + digit;
    if (x_exp > 99)
      x_exp = digit;
  } else {
    if (!last_enter_sto_clx)
      hp35_stack_up();
    enter_num_pre = true;
    enter_num_post = false;
    enter_exp = false;
    x_pre = digit;
    x_post = 0;
    x_exp = 0;
    x_neg = false;
    x_exp_neg = false;
    numcount = 1;
  }
  hp35_convert_input();
}

void hp35_init(void) {
  x = 0.0;
  y = 0.0;
  z = 0.0;
  t = 0.0;
  s = 0.0;
  hp35_reset();
}

void hp35_pow(void) {
  x = pow(x, y);
  hp35_stack_down();
  hp35_reset();
}

void hp35_log10(void) {
  x = log10(x);
  hp35_reset();
}

void hp35_log(void) {
  x = log(x);
  hp35_reset();
}

void hp35_exp(void) {
  x = exp(x);
  hp35_reset();
}

void hp35_clr(void) {
  hp35_init();
}

void hp35_sqrt(void) {
  x = sqrt(x);
  hp35_reset();
}

void hp35_arc(void) {
  last_enter_sto_clx = false;
  last_arc = true;
}

void hp35_sin(void) {
  if (last_arc)
    x = asin(x) * 180. / M_PI;
  else
    x = sin(x * M_PI / 180.);
  hp35_reset();
}

void hp35_cos(void) {
  if (last_arc)
    x = acos(x) * 180. / M_PI;
  else
    x = cos(x * M_PI / 180.);
  hp35_reset();
}

void hp35_tan(void) {
  if (last_arc)
    x = atan(x) * 180. / M_PI;
  else
    x = tan(x * M_PI / 180.);
  hp35_reset();
}

void hp35_reciprocal(void) {
  x = 1. / x;
  hp35_reset();
}

void hp35_exchange(void) {
  double temp = x;
  x = y;
  y = temp;
  hp35_reset();
}

void hp35_rolldown(void) {
  double temp = x;
  x = y;
  y = z;
  z = t;
  t = temp;
  hp35_reset();
}

void hp35_store(void) {
  s = x;
  hp35_reset();
  last_enter_sto_clx = true;
}

void hp35_recall(void) {
  if (!last_enter_sto_clx)
    hp35_stack_up();
  x = s;
  hp35_reset();
}

void hp35_enter(void) {
  hp35_stack_up();
  hp35_reset();
  last_enter_sto_clx = true;
}

void hp35_clx(void) {
  x = 0.;
  hp35_reset();
  last_enter_sto_clx = true;
}

void hp35_add(void) {
  x = y + x;
  hp35_stack_down();
  hp35_reset();
}

void hp35_sub(void) {
  x = y - x;
  hp35_stack_down();
  hp35_reset();
}

void hp35_mul(void) {
  x = y * x;
  hp35_stack_down();
  hp35_reset();
}

void hp35_div(void) {
  x = y / x;
  hp35_stack_down();
  hp35_reset();
}

void hp35_pi(void) {
  if (!last_enter_sto_clx)
    hp35_stack_up();
  x = M_PI;
  hp35_reset();
}

void hp35_num0(void) {
  hp35_enter_digit(0);
}

void hp35_num1(void) {
  hp35_enter_digit(1);
}

void hp35_num2(void) {
  hp35_enter_digit(2);
}

void hp35_num3(void) {
  hp35_enter_digit(3);
}

void hp35_num4(void) {
  hp35_enter_digit(4);
}

void hp35_num5(void) {
  hp35_enter_digit(5);
}

void hp35_num6(void) {
  hp35_enter_digit(6);
}

void hp35_num7(void) {
  hp35_enter_digit(7);
}

void hp35_num8(void) {
  hp35_enter_digit(8);
}

void hp35_num9(void) {
  hp35_enter_digit(9);
}

void hp35_decimal_point(void) {
  if (enter_num_pre) {
    enter_num_pre = false;
    enter_num_post = true;
  } else if (enter_num_post) {
    // ignore
  } else if (enter_exp) {
    // ignore
  } else {
    if (!last_enter_sto_clx)
      hp35_stack_up();
    enter_num_post = true;
  }
  hp35_convert_input();
}

void hp35_eex(void) {
  if (enter_num_pre || enter_num_post) {
    enter_num_pre = false;
    enter_num_post = false;
    enter_exp = true;
  } else if (enter_exp) {
    // ignore
  } else {
    if (!last_enter_sto_clx)
      hp35_stack_up();
    enter_num_pre = false;
    enter_num_post = false;
    enter_exp = true;
  }
  if (x_pre == 0 && x_post == 0) {
    x_pre = 1;
  }
  hp35_convert_input();
}

void hp35_chs(void) {
  if (enter_num_pre || enter_num_post) {
    x_neg = !x_neg;
    hp35_convert_input();
  } else if (enter_exp) {
    x_exp_neg = !x_exp_neg;
    hp35_convert_input();
  } else {
    x = -x;
    hp35_reset();
  }
}

char* hp35_display(void) {
  if (enter_num_pre || enter_num_post || enter_exp) {
    char buf[20];
    sprintf(buf, "%llu", x_post);
    char buf2[20];
    sprintf(buf2, "%02u", x_exp);
    sprintf(display, "%s%llu%s%s%s%s", x_neg ? "-" : " ", x_pre,
            x_post == 0 ? "" : ".", x_post == 0 ? "" : buf,
            x_exp != 0 && x_exp_neg ? "E-" : "E+", x_exp != 0 ? buf2 : "");
  } else {
    if (x > 9.999999999e+99)
      x = 9.999999999e+99;
    if (x < -9.999999999e+99)
      x = -9.999999999e+99;
    if (x > -9.999999999e-99 && x < 9.999999999e-99)
      x = 0;
    sprintf(display, "%.10G", x);
    if (display[0] != '-') {
      memmove(display + 1, display, strlen(display) + 1);
      display[0] = ' ';
    }
    replace_substring(display, " INF", " 1NF");
    replace_substring(display, "-NAN", " NAN");
  }
  size_t l = strlen(display);
  if (l < 16) {
    if (l > 4 && display[l - 4] == 'E') {
      while (strlen(display) < 16)
        replace_substring(display, "E", " E");
    }
  }
  replace_substring(display, "E+", " ");
  replace_substring(display, "E-", "-");
  replace_substring(display, ".", " .");
  return display;
}
