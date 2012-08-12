    
sleep = ((t, cb)->
  setTimeout (()->
    cb()
  ), t
)

test1 = ()->
  console.log "1 going to sleep"
  await sleep 5000, defer dummy
  console.log "1 done sleeping"

test2 = ()->
  console.log "2 going to sleep"
  await sleep 3000, defer dummy
  console.log "2 done sleeping"


test1()
test2()