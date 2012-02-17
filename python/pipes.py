import os

if __name__ == '__main__':
    r, w = os.pipe()
    pid = os.fork()
    if pid == 0:
        if os.dup2(w, 1) == -1:
            print "Failed to redirect stdout"
        os.close(r); os.close(w)
        os.execl("/bin/ls", "ls", "-l")
    else:
        print "childpid: " + str(pid)
        print "dup2 %s" % os.dup2(r, 0)
        os.close(r); os.close(w)
        os.execl("/bin/grep", "grep", "c")
      



