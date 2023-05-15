rem  生成数据库表的实体代码
tmg -h 127.0.0.1 -d study16db -p 3306 -u game -x game123 -e mysql -o ./study --noConfig --cf snake --pv public
