# Screening Interview Answer Notes

1. Build the Program.
   Run `make all` to build.
   You will see `screen`, `screen_asan` and a few relevant .o files.
   `screen` is the intended executable, while `screen_asan` can be used for memory debugging.

2. Implementation of parse_query_string()

   Done with only basic functionality and handling of things like 0 or multiple '?' in url, as I'm not very familiar with URI protocol (what should be valid; what shouldn't), etc.

3. Testcases.

   Here I use doctrines of input partition, test template tree and boundary value analysis to implement testing module. Since url in realistic scenarios are prone to exploitation, I consider invalid cases in testing.

   It's still far away from complete.

   Test template tree:

   ​														ID

   ​											/			|				\

   ​										V_1	has 1 '?'			I_2

   ​												/		|		\

   ​										V_3	has 1 k-v	V_4

   ​												/		|		\

   ​										I_5		has 1 '='	I_6

   ​													/		\

   ​									key is notempty		I_7

   ​											/		\

   ​									V_8			V_9

   V_1: has 0 '?' in url 

   I_2: has multiple '?' in url

   V_3: has no key-value pair in query string

   V_4: has multiple key-value pairs in query string

   I_5: has no '=' k-v pair

   I_6: has multiple '='s k-v pair

   I_7: key is empty

   V_8: value is ""

   V_9: value is not ""

   I denotes invalid equivalent class; V denotes valid equivalent class.

4. Fix memory errors in main.c.
   I use address sanitiser to detect memory errors. ASAN is totally competent for detecting memory leak, access after free, etc. However, ASAN built in clang on MacOS seems to be unreliable for now.
   Run `screen_asan`, we can see report of memory errors encountered.
