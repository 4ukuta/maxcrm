read -p "Enter database user: " user
read -p "Enter database user password: " pass
if mysql -u$user -h'localhost' -p$pass < dump.sql
then
echo "Database for MaxCRM created successfully"
fi
