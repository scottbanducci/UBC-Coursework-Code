-- | @getFirstDigit n@ evaluates to the first digit of @n@, which is
-- in 0 for the number 0 and otherwise one of [1..9]. TODO: add the
-- critical missing type of example below and discuss it here.
--
import Data.List
-- >>> getFirstDigit 6
-- 6
--
-- >>> getFirstDigit 0
-- 0
--
-- >>> getFirstDigit 112
-- 1
getFirstDigit :: Integer -> Integer
getFirstDigit n | n >= 10 = getFirstDigit (div n 10)
                | (n<0 && n>=(-9)) = getFirstDigit (-1*n) 
                | (n<(-9)) = getFirstDigit (div (-1*n) 10)
                | otherwise = n


-- | @getFirstDigits ns@ evaluates to a list of the first digits of
-- @ns@, using 'getFirstDigit', described above.
--
-- >>> getFirstDigits []
-- []
--
-- >>> getFirstDigits [15, 0, -4, 728,23,213,123,123,123,123,124,532,5243,764,743,5,33462]
-- WAS WAS WAS WAS WAS WAS [1,0,4,7]
-- WAS WAS WAS WAS WAS NOW [1,0,-4,7]
-- WAS WAS WAS WAS NOW [1,0,-4,7]
-- WAS WAS WAS NOW [1,0,-4,7]
-- WAS WAS NOW parse error on input ‘,’
-- WAS NOW [1,0,-4,7,2,2,1,1,1,1,1,5,5,7,7,5,3]
-- NOW [1,0,-4,7,2,2,1,1,1,1,1,5,5,7,7,5,3]
getFirstDigits :: [Integer] -> [Integer]
getFirstDigits (x:xs) = getFirstDigit (x) : getFirstDigits (xs)
getFirstDigits [] = []


-- >>> countDigits [125,4326,146,4326,1341,614,61,4,6146,141,614,2]
-- [4,1,0,3,0,4,0,0,0]

-- >>> addLists [1,2,3,4,5] [6,7,8]
-- [7,9,11]

-- | @countDigits ns@ returns a list of 9 numbers representing how
-- often each digit [1..9] occurs as the first digit of a number in `ns`.

countDigits :: [Integer] -> [Integer]
countDigits [] = digitToCount 0
countDigits [o] = digitToCount (getFirstDigit o)
countDigits (o:os) = addLists (digitToCount (getFirstDigit o))  (countDigits os)

addLists :: [Integer] -> [Integer] -> [Integer]
addLists [] [] = [] 
addLists [] [_] =  []
addLists [_] [] = []
addLists (x:xs) [] = []
addLists [] (x:xs) = []
addLists [h] (j:js) = [h+j]
addLists (h:hs) [j] = [h+j]
addLists (h:hs) (j:js) = h+j:addLists hs js


digitToCount :: Integer -> [Integer]
digitToCount      1 = [1,0,0,0,0,0,0,0,0]
digitToCount      2 = [0,1,0,0,0,0,0,0,0]
digitToCount      3 = [0,0,1,0,0,0,0,0,0]
digitToCount      4 = [0,0,0,1,0,0,0,0,0]
digitToCount      5 = [0,0,0,0,1,0,0,0,0]
digitToCount      6 = [0,0,0,0,0,1,0,0,0]
digitToCount      7 = [0,0,0,0,0,0,1,0,0]
digitToCount      8 = [0,0,0,0,0,0,0,1,0]
digitToCount      9 = [0,0,0,0,0,0,0,0,1]
digitToCount      _ = [0,0,0,0,0,0,0,0,0]



-- | @barChart c ns@ produces a list of one string per number @n@ in @ns@. Each
-- string is as long as the corresponding number @n@ and made up of copies of @c@.
--
-- >>> barChart '#' []
-- []
--
-- >>> barChart '#' [3, 0, 5, 1]
-- ["###","","#####","#"]
--
-- >>> barChart '-' [2]
-- ["--"]
barChart :: Char -> [Integer] -> [String]
barChart c [] = []
barChart c (x:xs) = drawBar c x : barChart c xs

-- >>> drawBar '#' 89
-- "#########################################################################################"
--


drawBar :: Char -> Integer -> String
drawBar m 0 = ""
drawBar m x = genericReplicate x m 

-- | @genBenChart ns@ produces a list of strings that is a bar
-- chart of '#' characters with 9 bars showing the frequency of 
-- first digits 1 to 9 in @ns@.
--
-- >>> genBenChart [22, 7, 13, 18, 3, 6, 35]
-- ["##","#","##","","","#","#","",""]
genBenChart :: [Integer] -> [String]
genBenChart [] = barChart '#' [0,0,0,0,0,0,0,0,0]
genBenChart [x] = barChart '#' (countDigits [getFirstDigit x])
genBenChart (x:xs) = barChart '#' (countDigits (x:xs))






-- | @extractData s@ requires that @s@ be exactly: a single line (of any text),
-- followed by zero or more lines of data. A line of data starts with an integer
-- followed optionally by a space and any additional text.
--
-- It evaluates to a tuple of the text of the first line and a list of the
-- integers from the subsequent lines.
--
-- >>> extractData "\n"
-- ("",[])
--
-- >>> extractData "Test\n12\n1 is a small number!\n345 45 5\n"
-- WAS WAS WAS ("Test",[12,1,345])
-- WAS WAS NOW Prelude.read: no parse
-- WAS NOW Prelude.read: no parse
-- NOW Prelude.read: no parse
--
-- >>> extractData "123\n-9\n"
-- ("123",[-9])
extractData :: String -> (String, [Integer])
extractData "" = ("",[])
extractData x = (head (lines x), restOfLines (tail (lines x))) 

restOfLines :: [String] -> [Integer]
restOfLines [] = []
restOfLines [x] = [read (head (words x)) :: Integer]
restOfLines (x:xs) = (read (head (words x)) :: Integer) : restOfLines xs


-- | @main@ reads from standard input (and expects data in
-- the format described for 'extractData' above), and prints
-- a bar chart showing frequencies of first digits in the data
-- to standard output.
main :: IO ()
main =
  getContents
    >>= pure . extractData
    >>= pure . (\(title, numLines) -> unlines (title : genBenChart numLines))
    >>= putStr
