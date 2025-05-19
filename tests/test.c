#include <_stdio.h>
#include <stdio.h>
#include <string.h>
#include <unity.h>

#if defined(_WIN32)
  #include <io.h>
  #define dup   _dup
  #define dup2  _dup2
  #define fileno _fileno
#else
  #include <unistd.h>
#endif

// FUNCTION PROTOTYPES
extern int run_app(void);
extern int calc_squares(int);

static void run_app_simulate(const char *txt, int return_val)
{
    FILE *tmp_in = tmpfile();                      
    fputs(txt, tmp_in);
    rewind(tmp_in);

    // Redirect the simulated string to stdin
    int fd_in  = dup(fileno(stdin));
    dup2(fileno(tmp_in), fileno(stdin));       
    clearerr(stdin);     

    // Make sure stdout does not print to the console during the test
    fflush(stdout);
    FILE *tmp_out = tmpfile(); 
    int fd_out = dup(fileno(stdout));
    dup2(fileno(tmp_out),fileno(stdout));            

    // Run the application
    int res = run_app();                         

    // Reset the file descriptors
    fflush(stdout);
    dup2(fd_in,  fileno(stdin));
    dup2(fd_out,  fileno(stdout));

    TEST_ASSERT_EQUAL_INT(return_val, res);

    close(fd_in);
    close(fd_out);
    fclose(tmp_in);
    fclose(tmp_out);
}

static void test_calc_values(void)
{
    printf("\nExecuting test 'test_calc_values'...\n");

    int ref[] = {1,5,14,30,55,91,140,204,285,385};
    for (int n = 1; n <= 10; ++n)
        TEST_ASSERT_EQUAL_INT(ref[n-1], calc_squares(n));
}

static void t_exit_on_zero(void){ 
  printf("\nExecuting test 't_exit_on_zero'...\n");
  run_app_simulate("0\n",     1); 
}

static void t_reject_minus_one(void){
  printf("\nExecuting test 't_reject_minus_one'...\n"); 
  run_app_simulate("-1\n",   -1); 
}

static void t_reject_non_digit(void){ 
  printf("\nExecuting test 't_reject_non_digit'...\n");
  run_app_simulate("a\n",    -1); 
}

static void t_loop_then_exit(void){ 
  printf("\nExecuting test 't_loop_then_exit'...\n");
  run_app_simulate("5\n0\n",  1); 
}

void setUp(void)   {}
void tearDown(void){}

int main(void)
{
    UNITY_BEGIN();

    // Test the error handling
    RUN_TEST(t_exit_on_zero); 
    RUN_TEST(t_loop_then_exit);
    RUN_TEST(t_reject_non_digit);
    RUN_TEST(t_reject_minus_one);

    // Test the calculated values
    RUN_TEST(test_calc_values);

    return UNITY_END();
}
