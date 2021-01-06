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

   