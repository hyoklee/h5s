import pymysql.cursors

# Connect to the database.
connection = pymysql.connect(host='10.10.10.82',
                             user='joe_read',
                             password='*******',
                             db='cdash',
                             cursorclass=pymysql.cursors.DictCursor)

try:
    with connection.cursor() as cursor:
        sql = "SELECT buildid, testid FROM build2test LIMIT 10"
        numrows = cursor.execute(sql)
        print(cursor.fetchall())
finally:
    connection.close()
    
