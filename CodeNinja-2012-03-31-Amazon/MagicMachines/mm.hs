
import Text.ParserCombinators.Parsec

x (Right a) = a
x (Left _) = 0

prs = x . (parse r "!")

blue = do
         char 'a'
         char 'b'
         n <- many (char 'a')
         return $ 2 + (2 * (length n))

green = do
          char 'b'
          b <- blue
          return $ 2 + b

red = do
        b <- blue
        g <- green
        return $ 3 + b + g

r = red

tst = do
        str <- getLine
        let res = prs str
        putStrLn (if res == 0 then "IMPOSSIBLE" else (show res))

main = do
         t <- getLine
         mapM_ (const tst) [1 .. (read t)]

