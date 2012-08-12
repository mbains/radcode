#number = -42 if opposite
#
## Functions:
#square = (x) -> x * x
#
## Arrays:
#list = [1, 2, 3, 4, 5]
#
## Objects:
#math =
#  root:   Math.sqrt
#  square: square
#  cube:   (x) -> x * square x
#
## Splats:
#race = (winner, runners...) ->
#  print winner, runners
#
## Existence:
#alert "I knew it!" if elvis?

# Array comprehensions:
#cubes = (math.cube num for num in list)

#callback = (x) -> setTimeout ( (x) -> console.log "hey x = #{x}"), 1000
#y = 20
#while y-=1
#  ((x) -> setTimeout (()->console.log "hey #{x}"), y*50) y

func = (x, cb)-> setTimeout (()-> 
  console.log "done #{x}"
  cb(5)
  ), 1000 

getter = (cb)->
  await func 10, defer answer
  console.log "in async func " + answer
  cb answer
  

getter (mine)-> console.log "through async #{mine}"
 
#func(10, -> console.log "finished")

#callback 20
#
#((x)->x*2) 2