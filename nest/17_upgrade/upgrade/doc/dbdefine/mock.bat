rem  生成数据库表的实体代码
tmg -h 127.0.0.1 -d mock-test -p 3306 -u game -x game123 -e mysql -o ./mocktest --noConfig --cf snake --pv public
