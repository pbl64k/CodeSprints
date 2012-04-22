
import Data.List

rep n c = take n $ repeat c

repsp n = rep n ' '

repst n = rep n '*'

avgtri n = (n + 1) ^ 2 `div` 2

maxWidth n = ((avgtri n) + n + 3) * 2 + 1

lvl mw n = let stars = 2 * n + 1 in (repsp ((mw - stars) `div` 2)) ++ (repst stars)

bunch mw n = let st = avgtri n in concat $ intersperse "\n" (map (lvl mw) [st .. (st + n + 3)])

trp mw n = let w = if n `mod` 2 == 0 then n + 1 else n in (repsp ((mw - w) `div` 2)) ++ (rep w '|')

trunk mw n = take n $ repeat (trp mw n)

tree n = let mw = maxWidth $ n - 1
             in concat $ intersperse "\n" ((map (bunch mw) [0 .. (n - 1)]) ++ (trunk mw n))

main = getLine >>= (\n -> putStrLn $ tree (read n))

