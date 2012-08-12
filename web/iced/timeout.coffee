y = 20
while y-=1
  ((x) -> setTimeout (()->console.log "hey #{x}"), y*50) y