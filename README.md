# http-server-c

1. parser
   request_parse
   send_response
   
2. network
    open
   accept
   close
   
3. process
    daemonize
            hserver (pid : hserver_pid, ppid: bash_pid, stdin, stdout, stderr)  
            close(stdin), close(stdout), close(stderr)  
            fork -> hserver_child(pid: hserver_child-pid, ppid: 1 (init_pid))  
            setsid();  
   setup_signals  
            SIGTERM -> exit  
     
4. hserver  

Обычный GET-запрос

Запрос клиента:

GET /wiki/страница HTTP/1.1
Host: ru.wikipedia.org
User-Agent: Mozilla/5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5
Accept: text/html
Connection: close
(пустая строка)

Ответ сервера:

HTTP/1.1 200 OK
Date: Wed, 11 Feb 2009 11:20:59 GMT
Server: Apache
X-Powered-By: PHP/5.2.4-2ubuntu5wm1
Last-Modified: Wed, 11 Feb 2009 11:20:59 GMT
Content-Language: ru
Content-Type: text/html; charset=utf-8
Content-Length: 1234
Connection: close
(пустая строка)
(запрошенная страница в HTML)

   