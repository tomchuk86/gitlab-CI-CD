echo Test 1 without flags
./s21_grep grep grep.h Makefile> s21_output.txt
grep grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 1 OK
else
    echo Test 2 FAIL && exit 1
fi
echo Test 2 with flag i
./s21_grep -i grep grep.h Makefile> s21_output.txt
grep -i grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 2 OK
else
    echo Test 2 FAIL && exit 1
fi
echo Test 3 with flag v
./s21_grep -v grep grep.h Makefile> s21_output.txt
grep -v grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 3 OK
else
    echo Test 3 FAIL && exit 1
fi
echo Test 4 with flag c
./s21_grep -c grep grep.h Makefile> s21_output.txt
grep -c grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 4 OK
else
    echo Test 4 FAIL && exit 1
fi
echo Test 5 with flag e
./s21_grep -e gr.p grep.h Makefile> s21_output.txt
grep -e gr.p grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 5 OK
else
    echo Test 5 FAIL && exit 1
fi
echo Test 6 with flag l
./s21_grep -l grep grep.h Makefile> s21_output.txt
grep -l grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 6 OK
else
    echo Test 6 FAIL && exit 1
fi
echo Test 7 with flag n
./s21_grep -n grep grep.h Makefile> s21_output.txt
grep -n grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 7 OK
else
    echo Test 7 FAIL && exit 1
fi
echo Test 8 with flag h
./s21_grep -h grep grep.h Makefile > s21_output.txt
grep -h grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 8 OK
else
    echo Test 8 FAIL && exit 1
fi
echo Test 9 with flag s
./s21_grep -s grep grep.h Makefile > s21_output.txt
grep -s grep grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 9 OK
else
    echo Test 9 FAIL && exit 1
fi
echo Test 10 with flag o
./s21_grep -o include grep.h Makefile > s21_output.txt
grep -o include grep.h Makefile> bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 10 OK
else
    echo Test 10 FAIL && exit 1
fi
echo Test 11 with flag f
echo include >patterns.txt
./s21_grep -f patterns.txt grep.h Makefile > s21_output.txt
grep -f patterns.txt grep.h Makefile > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 11 OK
else
    echo Test 11 FAIL && exit 1
fi
echo Test 12 with flag iv
echo include >patterns.txt
./s21_grep -iv grep grep.h Makefile > s21_output.txt
grep -iv grep grep.h Makefile > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 12 OK
else
    echo Test 12 FAIL && exit 1
fi
echo Test 13 with flag -in
echo include >patterns.txt
./s21_grep -in grep grep.h Makefile > s21_output.txt
grep -in grep grep.h Makefile > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 13 OK
else
    echo Test 13 FAIL && exit 1
fi