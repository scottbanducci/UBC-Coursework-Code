module Scratch where

q :: String
q = "hugo"

piyo :: String -> Double
piyo ['_'] = 2.5
piyo ('_':_:_) = 2.5
piyo [p] = 2.5
piyo (p:_:_) = 2.5
piyo [] = 2.5

h :: [Int] -> Int
h [] = 0
h [w] = w
h (w:z:ws) = w - z + h ws

l = 'w'

buildCharacter :: Char -> String -> String
buildCharacter _ [] = "_"
buildCharacter x [xs] = [xs,x]
buildCharacter  x (y:z:_) = [y,z,x]