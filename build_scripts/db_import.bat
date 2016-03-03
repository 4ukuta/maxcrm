set /p user_name="Enter login: "

echo %user_name%

mysql -u %user_name% -p < dump.sql

pause