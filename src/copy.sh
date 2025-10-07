echo "Deploying to pupok@192.168.31.223"

scp src/cat/s21_cat pupok@192.168.31.223:/usr/local/bin/
scp src/grep/s21_grep pupok@192.168.31.223:/usr/local/bin/
ssh pupok@192.168.31.223 "chmod +x /usr/local/bin/*"

echo "Deploy finished"