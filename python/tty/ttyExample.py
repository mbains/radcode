def getpass(prompt = "Password: "):
    import termios, sys
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    new = termios.tcgetattr(fd)
    new[3] = new[3] & ~termios.ECHO          # lflags
    try:
        termios.tcsetattr(fd, termios.TCSADRAIN, new)
        passwd = raw_input(prompt)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
    return passwd


import sys, curses
class gb(object):
    boxrows = int(sys.argv[1])
    boxcols = boxrows
    scrn = None
    row = None
    col = None

def draw(ch):
    if gb.row == gb.boxrows-1:
        '''if last row, change colors'''
        gb.scrn.addch(gb.row,gb.col,ch,curses.color_pair(1))
    else:
        gb.scrn.addch(gb.row,gb.col,ch)

    gb.scrn.refresh()
    gb.row += 1
    #if at bottom, goto top, next col
    if gb.row == gb.boxrows:
        gb.row = 0
        gb.col += 1
        if gb.col == gb.boxcols:
            '''if cols == max, overwrite'''
            gb.col = 0

def restorescreen():
    curses.nocbreak()
    curses.echo()
    curses.endwin()

def main():
    gb.scrn = curses.initscr()
    curses.noecho()
    curses.cbreak()

    curses.start_color()
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_WHITE)

    gb.scrn.clear()
    gb.row = 0
    gb.col = 0
    gb.scrn.refresh()

    while True:
        c = gb.scrn.getch()
        c = chr(c)
        if c == 'q':
            break
        draw(c)
    restorescreen()

if __name__ == '__main__':
    try:
        main()
    except:
        restorescreen()

    
        
