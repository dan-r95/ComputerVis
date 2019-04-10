
#include <stdio.h>
//#include <string>
//#include <math.h>
#include <ecl/ecl.h>

int main (int argc, char **argv) {
  /* Initialize ECL */
  cl_boot(argc, argv);

  cl_object exp, res, tmp;
  float num;
  char str[100];

  sprintf_s(str, "(print(- 1 2 3))");
  exp = c_string_to_object(str);
  cl_eval(exp);
  printf("\n%d\n",1-2-3);

  sprintf_s(str, "(print(/ 1 2 3))");
  exp = c_string_to_object(str);
  num = ecl_to_float(cl_eval(exp));
  printf("\n%f\n",num);

  sprintf_s(str, "(progn(defun fak(x)(if(= x 0)1(* x(fak(- x 1)))))(print(fak %d)))",100);
  exp = c_string_to_object(str);
  res = cl_eval(exp);
  cl_print(1, res);
  printf("\n");

  res = cl_eval(c_string_to_object("(print(list 0 '(1 2 3)))"));
  cl_print(1,res);
  printf("\n");

  tmp = cl_car(res);
  cl_print(1, tmp);
  tmp = cl_cdr(res);
  cl_print(1, tmp);
  printf("\n\n");

  exp = c_string_to_object("(print(eval(read)))");
  res = cl_eval(exp);
  cl_print(1, res);
  printf("\n");

  exp = cl_list(3,ecl_make_symbol("+","CL"),ecl_make_integer(1),ecl_make_single_float(2));
  cl_print(1, exp);
  res = cl_eval(exp);
  cl_print(1, res);
  printf("\n\n");

// cl_eval(c_string_to_object(
//	"(compile-file \"D:/Test/ECL/ecl-15.3/ecl-15.3.7/examples/ffi/ecl.lsp\" :load t)"
//	));
//  exp(2.0);
//  sin(2.0);

//  cl_shutdown();
  return 0;
}
