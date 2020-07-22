
#include <config.h>
/*
char *int2str(uint16_t n)
{
  static char str[10];
  static uint8_t i = 0;
  if (n >= 10)
  {
    int2str(n / 10);
    n = n % 10;
  }
  str[i++] = n + '0';
  uint8_t j;
  for (j = i; j < 10; j++)
    str[j] = 0;
  return str;
}
*/

/*
 * int/float to string conversion functions
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

/*
 * a function converts an int to string
 * ex: char * str=int2str(1234);
 * return "1234"
 */
char *int2str(uint16_t n)
{
  static char str[10];
  uint8_t i = 0;
  char buffer[10];
  do
  {
    buffer[i] = n % 10 + '0'; // digit
    n = n / 10;
    i++;
  } while (n); // repeat until n==0
  uint8_t j = 0;
  for (j = 0; j < i; j++)
    str[j] = buffer[i - j - 1];
  for (j = i; j < 10; j++)
    str[j] = 0;
  return str;
}
/*
 * a function converts a float value to string
 * ex: char * str=float2str(1234.99,2);
 * return "1234.99"
 */
char *float2str(float n, uint8_t point)
{
  static char float_str[10];
  int8_t i;
  for (i = point; i > 0; i--)
    n = n * 10;
  char *str = int2str(n);
  i = 0;
  while (str[i] != '\0')
  {
    float_str[i] = str[i];
    i++;
  }
  uint8_t j = i - point;
  for (i; i >= j; i--)
  {
    float_str[i] = float_str[i - 1];
  }
  float_str[i + 1] = '.';
  return float_str;
}
