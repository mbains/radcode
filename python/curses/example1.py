import curses


def startCurses():
    screen = curses.initscr()

    curses.noecho()
    curses.cbreak()
    curses.start_color()
    screen.clear()
    screen.refresh()
    return screen

def drawLine(screen, val, pos):
    (x,y) = pos
    screen.addstr(x,y, val)
    screen.refresh()

def endCurses():
    curses.nocbreak()
    curses.echo()
    curses.endwin()

if __name__ == '__main__':
    import time
    screen = startCurses()
    for i in xrange(20):
        drawLine(screen, "blah %s" % "%d".rjust(20) % i, (0,0))
        drawLine(screen, "foo  %s" % "%d".rjust(20) % i, (1,0))
        time.sleep(0.5)
        
    endCurses()