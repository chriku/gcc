/* Integration test of how the execution path looks for
   -Wanalyzer-out-of-bounds.  */

/* { dg-additional-options "-fdiagnostics-show-path-depths" } */
/* { dg-additional-options "-fdiagnostics-path-format=inline-events -fdiagnostics-show-caret" } */


#include <stdint.h>

int32_t arr[10];

void int_arr_write_element_after_end_off_by_one(int32_t x)
{
  arr[10] = x;  /* { dg-line line } */
}
/* { dg-warning "buffer overflow" "warning" { target *-*-* } line } */
/* { dg-message "valid subscripts for 'arr' are '\\\[0\\\]' to '\\\[9\\\]'" "valid subscript note" { target *-*-* } line } */


/* { dg-begin-multiline-output "" }
   arr[10] = x;
   ~~~~~~~~^~~
  event 1 (depth 0)
    |
    | int32_t arr[10];
    |         ^~~
    |         |
    |         (1) capacity is 40 bytes
    |
    +--> 'int_arr_write_element_after_end_off_by_one': event 2 (depth 1)
           |
           |   arr[10] = x;
           |   ~~~~~~~~^~~
           |           |
           |           (2) out-of-bounds write from byte 40 till byte 43 but 'arr' ends at byte 40
           |
   { dg-end-multiline-output "" } */
