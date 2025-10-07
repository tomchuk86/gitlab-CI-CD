echo Test 1 without flags
./s21_cat cat.h > s21_output.txt
cat  cat.h > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 1 OK
else
    echo Test 1 FAIL && exit 1
fi
echo Test 2 with flag -b
./s21_cat -b cat.h > s21_output.txt
cat -b cat.h > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 2 OK
else
    echo Test 2 FAIL && exit 1
fi
echo Test 3 with flag -e
./s21_cat -e cat.h > s21_output.txt
cat -e cat.h > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 3 OK
else 
    echo Test 3 FAIL && exit 1
fi
echo Test 4 with flag -n
./s21_cat -n cat.h > s21_output.txt
cat -n cat.h > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 4 OK
else
    echo Test 4 FAIL && exit 1
fi
echo Test 5 with flag -s
./s21_cat -s cat.h > s21_output.txt
cat -s cat.h > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 5 OK
else
    echo Test 5 FAIL && exit 1
fi
echo Test 6 with flag -t
./s21_cat -t cat.h > s21_output.txt
cat -t cat.h > bash_output.txt
if diff -q s21_output.txt bash_output.txt >/dev/null; then
    echo Test 6 OK
else
    echo Test 6 FAIL && exit 1
fi