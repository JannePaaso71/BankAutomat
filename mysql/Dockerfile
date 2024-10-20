FROM mysql:latest
COPY my.cnf /etc/
HEALTHCHECK --interval=15s --start-period=10s --retries=40 CMD mysqladmin -h 127.0.0.1 -u $MYSQL_USER --password=$MYSQL_PASSWORD -P 3306 ping
